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
			AnimationInfo(std::string const &path, int nbFrames, vector2D animPos, vector2D animSize)
				: _nbFrames(nbFrames), _animPos(animPos), _animSize(animSize) {
                    std::strncpy(_path, path.c_str(), ANIM_INFO_PATH_SIZE - 1);
				}
			virtual ~AnimationInfo() = default;

        int _nbFrames;
        vector2D _animPos;
        vector2D _animSize;
        char _path[ANIM_INFO_PATH_SIZE]{0};
    };
} // namespace Component

#endif /* !ANIMATIONINFO_HPP_ */
