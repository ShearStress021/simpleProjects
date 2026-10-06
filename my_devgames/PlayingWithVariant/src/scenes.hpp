#include "startScene.hpp"
#include "gameScene.hpp"
#include <variant>


using Scene = std::variant<std::monostate,StartScene,GameScene>;

inline void switchTo(Scene& scene, SceneId id){
	switch(id){
		case SceneId::Start: scene.emplace<StartScene>(); break;
		case SceneId::Game: scene.emplace<GameScene>() ;break;
		case SceneId::Quit: break;
	}

}


inline Next updateScene(Scene& scene , float dt){
	return std::visit([dt](auto& s) ->Next {
			if constexpr (std::is_same_v<std::decay_t<decltype(s)>, std::monostate>)  return {};
			else return s.update(dt);

			}, scene);

}

inline void renderScene(const Scene& scene){
	std::visit([](const auto& s) {
			if constexpr (!std::is_same_v<std::decay_t<decltype(s)>, std::monostate>) s.render();

			}, scene);
}




