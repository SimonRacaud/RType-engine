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

		virtual void idle(const Engine::Entity e);
		virtual void move(const Engine::Entity e);
		virtual void attack(const Engine::Entity e);
		virtual float getMoveSpeed() const;
		virtual float getShootingSpeed() const;
		virtual int getHealth() const;
		virtual std::string getSpriteSheet() const;
		virtual int getAnimationNbFrames() const;
		virtual vector2D getIdleAnimPos() const;
		virtual vector2D getMoveAnimPos() const;
		virtual vector2D getAttackAnimPos() const;

	protected:
	private:
};

#endif /* !PATAPATA_HPP_ */
