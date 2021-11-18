/*
** EPITECH PROJECT, 2021
** RType
** File description:
** AnimationInfo
*/

#ifndef ANIMATIONINFO_HPP_
#define ANIMATIONINFO_HPP_

#include <cstring>
#include "BaseComponent/BaseComponent.hpp"
#include "Item/vector2D.hpp"

#define ANIM_INFO_PATH_SIZE 128

namespace Component {
	class AnimationInfo : public Engine::BaseComponent<AnimationInfo> {
		public:
			AnimationInfo(std::string path, int nbFrames, vector2D animPos, vector2D animSize)
				: _nbFrames(nbFrames), _animPos(animPos), _animSize(animSize) {
					try {
						std::memcpy(_path, path.c_str(), path.length());
					} catch (...) {
						throw std::runtime_error("Could not load Animation info path may be too long");
					}
				}
			virtual ~AnimationInfo() = default;

        char _path[ANIM_INFO_PATH_SIZE];
        int _nbFrames;
        vector2D _animPos;
        vector2D _animSize;
    };
} // namespace Component

#endif /* !ANIMATIONINFO_HPP_ */
