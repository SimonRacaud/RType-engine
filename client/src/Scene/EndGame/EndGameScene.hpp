/*
** EPITECH PROJECT , 2021
** EndGameScene
** File description:
** \file EndGameScene.hpp
** \author simon
** \brief
** \date 18/11/2021
*/

#ifndef ENDGAMESCENE_HPP
#define ENDGAMESCENE_HPP

#include "CustomCluster.hpp"
#include "CustomEntityName.hpp"
#include "EngineCore.hpp"
#include <vector>

namespace Scene
{
    class EndGameScene : public Engine::AbstractScene<EndGameScene> {
      public:
        EndGameScene();
        virtual ~EndGameScene() = default;

        virtual void open();

        void setInput(std::vector<size_t> const& scores, size_t myScoreIndex, bool isFail);

      private:
        std::vector<size_t> _scores;
        size_t _myScoreIndex{0};
        bool _isFail{false};
    };
}

#endif // ENDGAMESCENE_HPP
