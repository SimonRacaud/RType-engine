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
#include "AnimationManager/AnimationManager.hpp"

#include "GameCore/GameCore.hpp"
#include "SpriteManager/SpriteManager.hpp"
#include "System/InputEventSystem/InputEventSystem.hpp"
#include "Event/MoveEvents/MoveEvents.hpp"

Player::Player(const vector2D &position, const vector2D &size, const vector2D &hitboxSize, const std::string &sprite)
{
	Engine::IEntityManager &entityManager = GameCore::engine.getEntityManager();
	Engine::ComponentManager &componentManager = GameCore::engine.getComponentManager();
	Engine::Entity entity = entityManager.create(nullptr, Engine::ClusterName::GAME, Engine::EntityName::TEST);

	std::vector<size_t> ps;
	std::vector<Engine::DrawableObj> renderList;
	std::shared_ptr<AnimationManager> anim = std::make_shared<AnimationManager>();

	anim->setFocus(surface(vector2D(100, 2), vector2D(34, 16)));
	anim->setNbMember(2);
	anim->setPosition(position);
	anim->setSrcPath("asset/sprites/r-typesheet1.gif");

	renderList.push_back(anim);
	renderList.push_back(std::make_shared<SpriteManager>(position, size, "asset/sprites/r-typesheet1.gif"));
	ps.push_back(3);
	ps.push_back(0);
	componentManager.add<Engine::Render>(entity, renderList, ps);
	componentManager.add<Engine::Position>(entity, 30, 30);
	componentManager.add<Engine::Velocity>(entity, 1, 1);
	// componentManager.add<Engine::Hitbox>(entity, hitboxSize.x, hitboxSize.y, [](Engine::Entity, Engine::Entity) {
	// 	std::cout << "PLAYER HITBOX HAS BEEN HIT" << std::endl;
	// });
	//componentManager.add<Engine::EntityLinkComponent>();
	//componentManager.add<Engine::ScoreComponent>(entity);
	/*componentManager.add<Engine::InputEvent>(entity, [position, size](const Engine::Entity &local) {
		//TODO when adding keybindings change it here with GameCore setting
		if (GameCore::event->isKeyPressed(IEventManager<renderToolSfml>::keyEvent_e::KEY_RIGHT)) {
			GET_EVENT_REG.registerEvent<MoveUp>(local);
		} else if (GameCore::event->isKeyPressed(IEventManager<renderToolSfml>::keyEvent_e::KEY_LEFT)) {
			GET_EVENT_REG.registerEvent<MoveLeft>(local);
		} else if (GameCore::event->isKeyPressed(IEventManager<renderToolSfml>::keyEvent_e::KEY_UP)) {
			GET_EVENT_REG.registerEvent<MoveRight>(local);
		} else if (GameCore::event->isKeyPressed(IEventManager<renderToolSfml>::keyEvent_e::KEY_DOWN)) {
			GET_EVENT_REG.registerEvent<MoveDown>(local);
		}
	});*/
}

Player::~Player()
{
}

