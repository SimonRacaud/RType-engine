/*
** EPITECH PROJECT, 2021
** Button
** File description:
** Button.cpp
*/

#include "Button.hpp"
#include "GameCore/GameCore.hpp"

#include "TextManager/TextManager.hpp"
#include "SpriteManager/SpriteManager.hpp"

#include "Component/Render.hpp"
#include "Component/InputEvent.hpp"

#include "System/RenderSystem/RenderSystem.hpp"
#include "System/InputEventSystem/InputEventSystem.hpp"

Button::Button(
    const std::string &text,
    const vector2D &position,
    const vector2f &scale,
    std::shared_ptr<Engine::Event::IEvent> event,
    const std::string &none,
    const std::string &isOn,
    const std::string &isClick
)
{
    Engine::IEntityManager &entityManager = GameCore::engine.getEntityManager();
    Engine::ComponentManager &componentManager = GameCore::engine.getComponentManager();
    Engine::Entity entity = entityManager.create(nullptr, Engine::ClusterName::START, Engine::EntityName::TEST);
    const vector2D size(scale.x, scale.y);

    std::vector<size_t> pos;
    std::vector<Engine::DrawableObj> renderList;

    renderList.push_back(std::make_unique<SpriteManager>(position, scale, none));
    renderList.push_back(std::make_unique<SpriteManager>(position, scale, isOn));
    renderList.push_back(std::make_unique<SpriteManager>(position, scale, isClick));
    renderList.push_back(std::make_unique<TextManager>(
        vector2D(position.x + 73 * (0.1 * scale.x), position.y + 30 * (0.1 * scale.y)),
        size, color_e::WHITE, text, "asset/font/Code-Pro.otf"));
    pos.push_back(3);
    pos.push_back(0);

    componentManager.add<Engine::Render>(entity, renderList, pos);
    componentManager.add<Engine::InputEvent>(entity, [position, size, event](const Engine::Entity &local) {
        if (GameCore::event->mouseIsOnClick(surface(position, vector2D(73 * size.x, 30 * size.y)), IEventManager<renderToolSfml>::keyEvent_e::MOUSE_CLICK_LEFT)) {
            GameCore::engine.getComponentManager().get<Engine::Render>(local).replaceLastRender(2);
            GET_EVENT_REG.registerEvent(event);
        } else if (GameCore::event->mouseIsOn(surface(position, vector2D(73 * size.x, 30 * size.y)))) {
            GameCore::engine.getComponentManager().get<Engine::Render>(local).replaceLastRender(1);
        } else {
            GameCore::engine.getComponentManager().get<Engine::Render>(local).replaceLastRender(0);
        }
    });
}