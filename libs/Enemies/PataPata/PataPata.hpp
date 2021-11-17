/*
** EPITECH PROJECT, 2021
** RType
** File description:
** PataPata
*/

#ifndef PATAPATA_HPP_
#define PATAPATA_HPP_

#include "IEnemyApi.hpp"
#include "Event/AbstractEvent/AbstractEvent.hpp"

struct IdlePata : public Engine::Event::AbstractEvent<IdlePata> {
	IdlePata(Engine::Entity e) : _entity(e) {}
	virtual ~IdlePata() = default;

	Engine::Entity _entity;
};

struct MovePata : public Engine::Event::AbstractEvent<MovePata> {
	MovePata(Engine::Entity e) : _entity(e) {}
	virtual ~MovePata() = default;

	Engine::Entity _entity;
};

struct AttackPata : public Engine::Event::AbstractEvent<AttackPata> {
	AttackPata(Engine::Entity e) : _entity(e) {}
	virtual ~AttackPata() = default;

	Engine::Entity _entity;
};

class PataPata : public IEnemyApi {
	public:
		PataPata();
		~PataPata();

		virtual void idle(const IEnemyApi *ptr) override;
		virtual void move(const IEnemyApi *ptr) override;
		virtual void attack(const IEnemyApi *ptr) override;
		virtual Engine::Position &getPosition();
		virtual Engine::Velocity &getVelocity();
		virtual float getShootingSpeed() const;
		virtual Component::Health &getHealth();
		virtual Component::AnimationInfo getAnimInfo() const;
		virtual std::pair<float, float> getHitboxSize() const;
		virtual void closeApi(IEnemyApi *ptr);
		private:
			Engine::Position _position;
			Engine::Velocity _velocity;
			Component::Health _health;
};

#endif /* !PATAPATA_HPP_ */
