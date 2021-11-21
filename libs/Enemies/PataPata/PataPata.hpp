/*
** EPITECH PROJECT, 2021
** RType
** File description:
** PataPata
*/

#ifndef PATAPATA_HPP_
#define PATAPATA_HPP_

#include "IEnemyApi.hpp"

class PataPata : public IEnemyApi {
	public:
		PataPata();
		virtual ~PataPata() = default;

		virtual void idle(const IEnemyApi *ptr) override;
		virtual void move(const IEnemyApi *ptr) override;
		virtual void attack(const IEnemyApi *ptr) override;
		virtual Engine::Position &getPosition();
        virtual void setPosition(vector2D const &position);
		virtual Engine::Velocity &getVelocity();
		virtual float getShootingSpeed() const;
		virtual Component::Health &getHealth();
		virtual Component::AnimationInfo getAnimInfo() const;
		virtual std::pair<float, float> getHitboxSize() const;

		private:
			Engine::Position _position;
			Engine::Velocity _velocity;
			Component::Health _health;
};

#endif /* !PATAPATA_HPP_ */
