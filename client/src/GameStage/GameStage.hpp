/*
** EPITECH PROJECT, 2021
** GameStage
** File description:
** GameStage.hpp
*/

#ifndef GAMESTAGE_HPP
#define GAMESTAGE_HPP

#include "IGameStage.hpp"

class GameStage : public IGameStage
{
    public:
        GameStage();
        ~GameStage();

        // HEADER DATA
        std::size_t getStageLvl() const;
        std::string getStageBackground() const;

        // STEP DATA
        StageStep getStageStep(bool move = true);
        std::queue<StageStep> getStagePrevious(std::size_t nb) const;
        std::queue<StageStep> getStageStepAt(std::size_t time, bool move = true);

        // ENDED DATA
        std::string getStageNext() const;
};

#endif