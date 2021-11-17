/*
** EPITECH PROJECT, 2021
** RType
** File description:
** IEnemyApi
*/

#ifndef IENEMYAPI_HPP_
#define IENEMYAPI_HPP_

#include "EngineCore.hpp"
#include "Components/Velocity.hpp"
#include "Components/Position.hpp"
#include "Components/Health.hpp"
#include "Components/AnimationInfo.hpp"

class IEnemyApi {
	public:
		~IEnemyApi() = default;
		
		virtual void idle(const IEnemyApi *ptr) = 0;
		virtual void move(const IEnemyApi *ptr) = 0;
		virtual void attack(const IEnemyApi *ptr) = 0;
		virtual Engine::Position &getPosition() = 0;
		virtual Engine::Velocity &getVelocity() = 0;
		virtual float getShootingSpeed() const = 0;
		virtual Component::Health &getHealth() = 0;
		virtual Component::AnimationInfo getAnimInfo() const = 0;
		virtual std::pair<float, float> getHitboxSize() const = 0;
};

#endif /* !IEnemyApi_HPP_ */
