/*
** EPITECH PROJECT, 2021
** RType
** File description:
** Player
*/

#include "Player.hpp"
#include "Component/Render.hpp"
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"
#include "Components/Hitbox.hpp"
#include "Components/EntityLinkComponent.hpp"
#include "Components/ScoreComponent.hpp"
#include "Component/InputEvent.hpp"
#include "Component/Shooting.hpp"
#include "AnimationManager/AnimationManager.hpp"

#include "GameCore/GameCore.hpp"
#include "SpriteManager/SpriteManager.hpp"
#include "System/InputEventSystem/InputEventSystem.hpp"
#include "Event/MoveEvents/MoveEvents.hpp"
#include "Event/MoveEvents/MoveHandler/MoveHandler.hpp"
#include "Event/ShootEvents/ShootEvents.hpp"
#include "Event/ShootEvents/ShootEventsManager/ShootEventsManager.hpp"

void hit(Engine::Entity, Engine::Entity)
{
	std::cout << "PLAYER HITBOX HAS BEEN HIT" << std::endl;
}

Player::Player(ClusterName cluster,
    const vector2D &position, const vector2f &size, const vector2D &hitboxSize, const std::string &sprite)
{
	MoveHandler handler;
	ShootEventsManager shootEventsManager;
	Engine::IEntityManager &entityManager = GameCore::engine.getEntityManager();
	Engine::ComponentManager &componentManager = GameCore::engine.getComponentManager();
	Engine::Entity entity = entityManager.create(nullptr, cluster, Engine::EntityName::EMPTY);

	std::vector<size_t> ps;
	std::vector<Engine::DrawableObj> renderList;
	std::shared_ptr<AnimationManager> anim = std::make_shared<AnimationManager>();

	vector2D playerEntitySize(34, 16);

	anim->setFocus(surface(vector2D(100, 2), playerEntitySize));
	anim->setNbMember(2);
	anim->setPosition(position);
	anim->setSrcPath("asset/sprites/r-typesheet1.gif");


	// CHARGE SHOT START
	std::shared_ptr<AnimationManager> chargeShot = std::make_shared<AnimationManager>();
	vector2D shotEntitySize(30, 32);

	chargeShot->setFocus(surface(vector2D(1, 51), shotEntitySize));
	chargeShot->setNbMember(8);
	chargeShot->setPosition(position);
	chargeShot-> setOffsetPosition(vector2D(playerEntitySize.x - shotEntitySize.x / 2, playerEntitySize.y / 2 - shotEntitySize.y / 2));
	chargeShot->setSrcPath("asset/sprites/r-typesheet1.gif");
	// END

	// PROPULSOR START
	std::shared_ptr<AnimationManager> propulsor = std::make_shared<AnimationManager>();
	vector2D propEntitySize(34, 29);

	propulsor->setFocus(surface(vector2D(199, 18), propEntitySize));
	propulsor->setNbMember(2);
	propulsor->setPosition(position);
	propulsor-> setOffsetPosition(vector2D(-propEntitySize.x, playerEntitySize.y / 2 - propEntitySize.y / 2));
	propulsor->setSrcPath("asset/sprites/r-typesheet1.gif");
	// END

	renderList.push_back(anim);
	renderList.push_back(propulsor);
	renderList.push_back(chargeShot);
	ps.push_back(0);
	ps.push_back(1);

	componentManager.add<Engine::Render>(entity, renderList, ps);
	componentManager.add<Engine::Position>(entity, position.x, position.y);
	componentManager.add<Engine::Velocity>(entity, 0, 0);
	componentManager.add<Engine::Hitbox>(entity, hitboxSize.x, hitboxSize.y, hit);
	componentManager.add<Engine::ScoreComponent>(entity);
	componentManager.add<Engine::EquipmentComponent>(entity);
	componentManager.add<Component::Shooting>(entity);
	//componentManager.add<Engine::EntityLinkComponent>();
	componentManager.add<Engine::InputEvent>(entity, [](const Engine::Entity &local) {
		auto &shooting = GET_COMP_M.get<Component::Shooting>(local);
		auto &render = GET_COMP_M.get<Engine::Render>(local);

		//TODO when adding keybindings change it here with GameCore setting
		if (GameCore::event->isKeyPressed(IEventManager<renderToolSfml>::keyEvent_e::KEY_UP)) {
			GET_EVENT_REG.registerEvent<MoveUp>(local, 10);
		}
		if (GameCore::event->isKeyPressed(IEventManager<renderToolSfml>::keyEvent_e::KEY_LEFT)) {
			GET_EVENT_REG.registerEvent<MoveLeft>(local, 10);
		}
		if (GameCore::event->isKeyPressed(IEventManager<renderToolSfml>::keyEvent_e::KEY_RIGHT)) {
			GET_EVENT_REG.registerEvent<MoveRight>(local, 10);
		}
		if (GameCore::event->isKeyPressed(IEventManager<renderToolSfml>::keyEvent_e::KEY_DOWN)) {
			GET_EVENT_REG.registerEvent<MoveDown>(local, 10);
		}
		if (!GameCore::event->isStateChange(IEventManager<renderToolSfml>::keyEvent_e::KEY_SPACE) && GameCore::event->isKeyPressed(IEventManager<renderToolSfml>::keyEvent_e::KEY_SPACE) && !shooting._isCharging) {
			shooting._isCharging = true;
			render.setRender(2);
			GET_EVENT_REG.registerEvent<ChargeShot>(local);
		} else if (GameCore::event->isKeyReleased(IEventManager<renderToolSfml>::keyEvent_e::KEY_SPACE) && shooting._isCharging) {
			shooting._isCharging = false;
			render.removeRender(2);
			GET_EVENT_REG.registerEvent<ReleaseChargedShot>(local);
		}
		GET_EVENT_REG.registerEvent<NotMoving>(local);
	});
}

Player::~Player()
{
}

