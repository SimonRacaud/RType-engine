/*
** EPITECH PROJECT , 2021
** GameEngine
** File description:
** \file GameEngine.hpp
** \author simon
** \brief
** \date 04/11/2021
*/

#ifndef ENGINECORE_HPP
#define ENGINECORE_HPP

#include "Engine/EngineFactory.hpp"
#include "AbstractScene/AbstractScene.hpp"
#include "SceneManager/SceneManager.hpp"
#include "Event/EventCallBackRegister/EventCallbackRegister.hpp"

#include "Systems/PhysicsSystem/PhysicsSystem.hpp"
#include "Systems/TimerSystem/TimerSystem.hpp"
#include "Systems/ColliderSystem/ColliderSystem.hpp"

#include "Components/Position.hpp"
#include "Components/Timer.hpp"
#include "Components/Hitbox.hpp"
#include "Components/EntityLinkComponent.hpp"
#include "Components/NumberComponent.hpp"
#include "Components/ScoreComponent.hpp"
#include "Components/Velocity.hpp"

#include "Utils/display.hpp"

#endif // ENGINECORE_HPP
