#pragma once

// GLM
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>



struct Vertex {
	glm::vec3 position{glm::vec3(0.0f)};
	glm::vec3 color{glm::vec3(1.0f)};
	glm::vec3 normal{glm::vec3(0.0f)};
	glm::vec2 uv{glm::vec2(0.0f)};
};


struct Image {
	int width{};
	int height{};
	int channels{};
	unsigned char *data{};

};


