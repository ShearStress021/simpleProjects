#include "raylib.h"
#include "raymath.h"



int main(){
	const int screenWidth{1200};
	const int screenHeight{720};
	InitWindow(screenWidth,screenHeight,"3D game");


	Camera3D camera = {0};
	 camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
   // camera.fovy = 45.0f;                                // Camera field-of-view Y
    //camera.projection = CAMERA_PERSPECTIVE;
	camera.fovy = 60.f;
	camera.projection = CAMERA_PERSPECTIVE;
	

	const float terrainWorldWidth{500.f};
	const float terrainWorldDepth{500.f};
	const float terrainMaxHeight{20.0f};
	const int terrainImageWidth{200};
	const int terrainImageHeight{200};


	Image heightMapImage = GenImageCellular(terrainImageWidth,
			terrainImageHeight, 16);

	Mesh terrainMesh = GenMeshHeightmap(heightMapImage, {terrainWorldWidth,
			terrainMaxHeight,terrainWorldDepth});
	
	UnloadImage(heightMapImage);

	Model terrainModel = LoadModelFromMesh(terrainMesh);


	terrainModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].color = GRAY;

	while(!WindowShouldClose()){
		UpdateCamera(&camera,CAMERA_THIRD_PERSON);

		BeginDrawing();

		ClearBackground(SKYBLUE);
		BeginMode3D(camera);
		DrawModelWires(terrainModel,Vector3Zero(),1.0f, LIME);
		DrawModel(terrainModel, Vector3Zero(),1.f,WHITE);


		EndMode3D();
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
