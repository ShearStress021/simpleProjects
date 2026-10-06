#pragma once
#include <raylib.h>
#include <optional>
#include <filesystem>
#include <unordered_map>



enum class SceneId  {Start,Game, Quit};
using Next = std::optional<SceneId>;


static std::unordered_map<std::string, Texture> textures;



