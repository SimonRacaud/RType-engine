/*
** EPITECH PROJECT , 2021
** GuiEventManager
** File description:
** \file GuiEventManager.cpp
** \author simon
** \brief
** \date 13/11/2021
*/

#include "GuiEventManager.hpp"
#include "GameCore/GameCore.hpp"
#include "EngineCore.hpp"
#include "Component/Render.hpp"
#include "Interface/IShapeManager.hpp"

GuiEventManager::GuiEventManager()
{
    Engine::Event::EventCallbackRegister &reg = Engine::EngineFactory::getInstance().getEventRegister();

    reg.registerCallback<SetProgressBarValue>([this] (const Engine::Event::IEvent *e) {
        this->setProgressBarValue(static_cast<const SetProgressBarValue *>(e));
    });
}

void GuiEventManager::setProgressBarValue(const SetProgressBarValue *evt)
{
    try {
        if (evt->getName() == Engine::EntityName::EMPTY) {
            throw std::invalid_argument("Empty entity name");
        } else if (evt->getValue() > 100) {
            throw std::invalid_argument("The value must be between 0 and 100");
        }
        Engine::Entity entity = GameCore::engine.getEntityManager().getId(evt->getName());
        Engine::ComponentManager &cm = GameCore::engine.getComponentManager();
        auto [render, value] = cm.getList<Engine::Render, Engine::NumberComponent>(entity);

        if (render._src.size() == 2) {
            value.value = evt->getValue();
            IShapeManager<renderToolSfml> *shapeFor = dynamic_cast<IShapeManager<renderToolSfml> *>(render._src[0].get());
            IShapeManager<renderToolSfml> *shapeBack = dynamic_cast<IShapeManager<renderToolSfml> *>(render._src[1].get());
            if (shapeFor != nullptr && shapeBack != nullptr) {
                size_t maxWidth = shapeBack->getSize().x;
                size_t newWidth = static_cast<int>((float)maxWidth * ((float)evt->getValue() / 100.0f));

                shapeFor->setSize(vector2D(newWidth, shapeFor->getSize().y));
                shapeFor->refresh();
            } else {
                throw std::invalid_argument("Render layers are not shape");
            }
        }
    } catch (std::exception const &e) {
        std::cerr << "GuiEventManager::setProgressBarValue : " << e.what() << std::endl;
    }
}