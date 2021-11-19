/*
** EPITECH PROJECT , 2021
** ScoreSystem
** File description:
** \file ScoreSystem.cpp
** \author simon
** \brief
** \date 19/11/2021
*/

#include "ScoreSystem.hpp"
#include "Components/ScoreComponent.hpp"
#include "Component/Render.hpp"

using namespace Engine;
using namespace System;

static const Engine::Time freq = static_cast<Engine::Time>(800);

ScoreSystem::ScoreSystem()
    : Engine::AbstractSystem<ScoreSystem>(freq, SystemPriority::LOW)
{
    this->setRequirements<ScoreComponent>();
}

void ScoreSystem::run(const vector<Engine::Entity> &)
{
    if (_labelTextManager == nullptr) {
        try {
            Engine::Entity label = GET_ENTITY_M.getId(EntityName::SCORE);
            auto &render = GET_COMP_M.get<Engine::Render>(label);
            if (render._src.empty() == false) {
                _labelTextManager = reinterpret_cast<ITextManager *>(render._src[0].get());
            }
        } catch (Engine::NotFoundException const&) {
            _labelTextManager = nullptr;
        }
    }
    /// UPDATE SCORE
    if (_playerFound) {
        try {
            auto &score = GET_COMP_M.get<ScoreComponent>(_player);
            if (_labelTextManager) {
                _labelTextManager->setContent(std::to_string(score.value));
            }
        } catch (Engine::NotFoundException const &) {
            this->_playerFound = false;
        }
    }
}

void ScoreSystem::onManagedEntityRemoved(Entity)
{
    try {
        _player = GET_ENTITY_M.getId(EntityName::LOCAL_PLAYER);
        this->_playerFound = true;
    } catch (Engine::NotFoundException const&) {
        this->_playerFound = false;
    }
}

void ScoreSystem::onManagedEntityAdded(Entity)
{
    try {
        _player = GET_ENTITY_M.getId(EntityName::LOCAL_PLAYER);
        this->_playerFound = true;
    } catch (Engine::NotFoundException const&) {
        this->_playerFound = false;
    }
}