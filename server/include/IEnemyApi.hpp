/*
** EPITECH PROJECT, 2021
** RType
** File description:
** IEnemyApi
*/

#ifndef IENEMYAPI_HPP_
#define IENEMYAPI_HPP_

#include "EngineCore.hpp"
#include "Item/vector2D.hpp"

class IEnemyApi {
	public:
		virtual ~IEnemyApi() = 0;
		
		virtual void idle(const IEnemyApi *ptr) = 0;
		virtual void move(const IEnemyApi *ptr) = 0;
		virtual void attack(const IEnemyApi *ptr) = 0;
		virtual float getMoveSpeed() const = 0;
		virtual float getShootingSpeed() const = 0;
		virtual int getHealth() const = 0;
		virtual std::string getSpriteSheet() const = 0;
		virtual int getAnimationNbFrames() const = 0;
		virtual vector2D getIdleAnimPos() const = 0;
		virtual vector2D getMoveAnimPos() const = 0;
		virtual vector2D getAttackAnimPos() const = 0;
};

#endif /* !IEnemyApi_HPP_ */
