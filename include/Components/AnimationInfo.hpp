/*
** EPITECH PROJECT, 2021
** RType
** File description:
** AnimationInfo
*/

#ifndef ANIMATIONINFO_HPP_
#define ANIMATIONINFO_HPP_

#include "BaseComponent/BaseComponent.hpp"
#include "Item/vector2D.hpp"

namespace Component {
	class AnimationInfo : public Engine::BaseComponent<AnimationInfo> {
		public:
			AnimationInfo(std::string path, int nbFrames, vector2D animPos, vector2D animSize)
				: _path(path), _nbFrames(nbFrames), _animPos(animPos), _animSize(animSize) {}
			virtual ~AnimationInfo() = default;

			std::string _path;
			int _nbFrames;
			vector2D _animPos;
			vector2D _animSize;
	};
}

#endif /* !ANIMATIONINFO_HPP_ */
