/*
** EPITECH PROJECT , 2021
** ScoreSystem
** File description:
** \file ScoreSystem.hpp
** \author simon
** \brief
** \date 19/11/2021
*/

#ifndef SCORESYSTEM_HPP
#define SCORESYSTEM_HPP

#include "CustomEntityName.hpp"
#include "EngineCore.hpp"
#include "Interface/ITextManager.hpp"

namespace System
{
    using std::vector;

    /**
     * @brief Refresh player score in the game GUI
     */
    class ScoreSystem : public Engine::AbstractSystem<ScoreSystem> {
      public:
        ScoreSystem();
        virtual ~ScoreSystem() = default;

        virtual void run(const vector<Engine::Entity> &entities);

        virtual void onManagedEntityRemoved(Engine::Entity);
        virtual void onManagedEntityAdded(Engine::Entity);

      private:
        bool _playerFound{false};
        Engine::Entity _player{0};
        ITextManager *_labelTextManager{nullptr};
    };
}

#endif // SCORESYSTEM_HPP
