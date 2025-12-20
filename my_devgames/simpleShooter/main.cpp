#include "raylib.h"
#include "raymath.h"
#include <cmath>
#include <vector>
#include <list>
using namespace std;


typedef struct Projectile {
	Vector3 position{};
	Vector3 velocity{};
	float lifetime{};
	float radius{};
	Color color{};
	bool active{};
} Projectile;

int main(){


	const int windowWidht{1200};
	const int windowHeight{720};

	InitWindow(windowWidht,windowHeight,"my first 3D");

	DisableCursor();


	Camera3D camera = {0};

	camera.fovy = 60.f;


	camera.projection = CAMERA_PERSPECTIVE;

	const float terrainWorldWidth{500.f};
	const float terrainWorldDepth{500.f};
	const float terrainMaxHeight{20.0f};
	const int terrainImageWidth{200};
	const int terrainImageHeight{200};


	Image heightMapImage = GenImageCellular(terrainImageWidth, 
			terrainImageHeight, 16);
	// Alternative: GenImagePerLinNoise(width,height, offsetX,offsetY,scale) 
	// for smoother more organic terrain
	//Image heightMapImage = GenImagePerLinNoise(terrainImageWidth, terrainImageHeight,0,0,20.f);


	Mesh terrainMesh = GenMeshHeightmap(heightMapImage, {terrainWorldWidth, 
			terrainMaxHeight,terrainWorldDepth});


	UnloadImage(heightMapImage);

	Model terrainModel = LoadModelFromMesh(terrainMesh);
	

	terrainModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].color = GRAY;
	// Texture2D terrainTex = LOadTexture("");
	//terrainModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].color = terrainTex;
	


	Mesh cubeMesh = GenMeshCube(2.f, 2.f,2.f);
	// Model myModel = LoadModel("")


	Model shipModel = LoadModelFromMesh(cubeMesh);
	shipModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].color = MAROON;


	Vector3 shipPosition {terrainWorldWidth/2.f,terrainMaxHeight + 10.f,terrainWorldDepth/2.f};

	float shipYaw {0.f};
	float shipPitch{0.f};
	

	const float mouseSensitivity{0.003f};
	const float moveSpeed{25.f};


	list<Projectile> projectiles;
	// List of active projectiles
	//
	//
	const int MAX_PROJECTILES{50};



	const float PROJECTILE_SPEED{70.f}; // speed of projectiles to the world units per second
	const float PROJECTILE_LIFETIME{3.f}; // projectile lifespans
										  //
	const float PROJECTILE_RADIUS{0.2f}; // visual represention of the projectile
	Color PROJECTILE_COLOR = ORANGE;


	float shootCoolDown{0.f}; // Shooting interval;
	const float SHOOT_RATE{0.15f};


	SetTargetFPS(60);




	while(!WindowShouldClose()){
		float dt = GetFrameTime();
//  times of mouse movement since last frame
		Vector2 mouseDelta = GetMouseDelta();

		//Update ships's yaw(left/right rotation) based on mouse movement
		//Subtract because typically moving mouse right increases x, which we map to clock wise yaw
		shipYaw -= mouseDelta.x * mouseSensitivity;


		//Update ships's yaw(up/down rotation) based on mouse movement
		//Subtract because typically moving mouse right decreases y, (screen coordinates)
		//which we map to pitching up
		shipPitch -= mouseDelta.y * mouseSensitivity;


		// clamp the pitch to prevent the ship from flipping upside down
		// angles are in radians. PI/2 radians is 90 degrees
		// we clamp slighlty less that 90 degrees to avoid gimbal lock issues or visual glitches
		shipPitch = Clamp(shipPitch, -PI / 2.f + 0.01f, PI / 2.f - 0.0f);


		Matrix shipRotationMatrix = MatrixMultiply(
				MatrixRotateX(shipPitch), MatrixRotateY(shipYaw));
		// if roll is involved 
		// Matrix shipRotationMatrix = 
		// MatrixMultiply(MatrixRotateZ(shipRool), MatrixMultiply(MatrixRotateX(shipPitch),
		// MatrixRotateY(shipYaw)))
		//

		//Calculate the ship's forward direction in world space.
		//(0,0,1) is typically for in model space (allong positive z)
		//Tranform this local forward vector by the ship's rotation Matrix
		Vector3 shipForward = Vector3Transform({0,0,1}, shipRotationMatrix);



		//Calculate the ship's forward direction in world space.
		//(1,0,0) is typically for in model space (allong positive x)
		Vector3 shipRight = Vector3Transform({1,0,0}, shipRotationMatrix);

		
		//Calculate the ship's forward direction in world space.
		//(0,1,0) is typically for in model space (allong positive y)
		Vector3 shipUp = Vector3Transform({0,1,0}, shipRotationMatrix);

		// if roll too complex  derive from cross product
		//shipUp = Vector3Normalize(Vector3CrossProduct(shipRight, shipForward))


		// Ship Control Movement(Position)
		//Initialze movement direction vector for this frame
		Vector3 moveDirection = {0};

		
		if(IsKeyDown(KEY_W)) moveDirection = Vector3Add(moveDirection, shipForward);
		if(IsKeyDown(KEY_S)) moveDirection = Vector3Subtract(moveDirection, shipForward);
		if(IsKeyDown(KEY_A)) moveDirection = Vector3Subtract(moveDirection, shipRight);
		if(IsKeyDown(KEY_S)) moveDirection = Vector3Subtract(moveDirection, shipRight);


		if(IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_E)) moveDirection.y += 1.f;
		if(IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_Q)) moveDirection.y -= 1.f;

		if (Vector3LengthSqr(moveDirection) > 0.001f){
			moveDirection = Vector3Normalize(moveDirection);

			shipPosition = Vector3Add(shipPosition, 
					Vector3Scale(moveDirection,moveSpeed ));
		}



		if(shootCoolDown > 0) shootCoolDown -= dt;

		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && shootCoolDown <= 0){

			if (projectiles.size() < MAX_PROJECTILES){
				 Projectile newProjectile{};

				 newProjectile.position = Vector3Add(shipPosition,
						 Vector3Scale(shipForward, 1.1f));

				 newProjectile.velocity = Vector3Scale(shipForward, PROJECTILE_SPEED);

				 newProjectile.lifetime = PROJECTILE_LIFETIME;
				 newProjectile.radius = PROJECTILE_RADIUS;
				 newProjectile.color = PROJECTILE_COLOR;
				 newProjectile.active = true;



				 projectiles.push_back(newProjectile);

				 shootCoolDown = SHOOT_RATE;

				 
			}

			for(auto it = projectiles.begin(); it != projectiles.end();){
				if (it->active){
					it->position = Vector3Add(it->position, 
							Vector3Scale(it->velocity, dt));
					it->lifetime -= dt;

					if (it->lifetime <= 0){
						it->active = false;
					}

				}
				if(it -> active){
					it = projectiles.erase(it);

				}else {
					++it;
				}
				
			}

			// CameraUpdate
			// This creates a third-person camera that follows the ship
			// How far behind the ship the camera should be
			float cameraDistance {15.f};
			

			// How high above the ship's centerline the camera should be
			float cameraHeightOffset{5.0f};

			//Calculate the desired offset from the ship's position
			//Start by going backward from the ship along its forward vector
			Vector3 cameraOffset{Vector3Scale(shipForward, -cameraDistance)};


			// Then , add some height (global Y-axis)
			camera.position = Vector3Add(shipPosition, cameraOffset);

			// Make the look ar the ship's currect position
			// using global up(0,1,0) provides a stable horizon
			camera.up = {0, 1,0};
			// Alternative: Use ship's local up vector for a camera that rolls with the ship
			// This can be wore immersive for flight sims but alse more disorienting
			// camera.up = shipUp
		}



		

		BeginDrawing();
		ClearBackground(SKYBLUE);

		//Enter 3D mode. ALL drawing functions between BeginMode3D and EndMode3D
		//will be renderred using the specified camera's perspective
		BeginMode3D(camera);


		//Draw Terrain
		// The currect order draws  wires first, then the solid model
		// This might result in the solid model mostly obsuring the wires
		// unless there's z-fighting or the wireframe is slighlty offset/larger
		DrawModelWires(terrainModel,Vector3Zero(),1.0f, LIME);
		// draw solid terrain (white tint doesn;t overide material color)
		DrawModel(terrainModel, Vector3Zero(),1.f,WHITE);
		

		//draw ship
		//to correctily orient and position the ship
		//1 create a rotation matrix(shipRotaion , already calculated in update)
		//2 create a tranlation matrix for ship world position
		//3 multiply these to get the final tranforamtion matrix for the model
		//the model's tranform field stores the Matrix
		//order for model transform : scale -. rotate -> translate
		//since we're not scaling the model here. it's rotate -> translate
		shipModel.transform = MatrixMultiply(
				shipRotationMatrix,
				MatrixTranslate(shipPosition.x, shipPosition.y, shipPosition.z));

		// Draw the ship Model
		// since its transform is set, we draw it at world origin (0,.0,0) with scale1 
		// The tranform matrix handles its actual position and oriention
		DrawModel(shipModel,Vector3Zero(), 1.f, WHITE);


		// Draw projectiles
		// iterates through all active projectiles and draw lifespans
		for(const auto& proj: projectiles){
			DrawSphere(proj.position, proj.radius, proj.color);

			//Alternative : DrawBillboard() for a 2d sprite that always face the camera
			//Alternative : DrawModel() with own 3D model projectiles
		}

		// Draw Helper Grid
		// Draw a 3d grid on xZ plane for spatial reference
		// Arguments: number of slices, spaceing between slices
		DrawGrid(100, 10.f);
		EndMode3D();
		DrawText("Spaceship Demo -wasd,mouse,LMB to shoot",
				10, 10, 20, DARKGRAY);
		DrawText(TextFormat("Ship position : (%.1f, %.1f, %.1f)",
					shipPosition.x,shipPosition.y,shipPosition.z),
				10, 60, 10, DARKGRAY);

		DrawText(TextFormat("Projectiles : %zu",projectiles.size()), 
				10, 60, 10, GRAY);

		DrawText(TextFormat("Yaw: %.2f Pitch: %.2f (deg)", shipYaw*RAD2DEG,shipPitch*RAD2DEG), 
				10 , 40, 10, GRAY);
		DrawFPS(windowWidht - 90,10); // curren frame per second


		EndDrawing();
	}

	UnloadModel(terrainModel);
	UnloadModel(shipModel);
	CloseWindow();
	return 0;
}
