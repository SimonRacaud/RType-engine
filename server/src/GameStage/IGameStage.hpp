/*
** EPITECH PROJECT, 2021
** IGameStage
** File description:
** IGameStage.hpp
*/

#ifndef IGAMESTAGE_HPP
#define IGAMESTAGE_HPP

#include <queue>
#include <iostream>
#include "Tools/StageStep.hpp"

class IGameStage
{
    public:
        ~IGameStage() = default;

        // HEADER DATA
        virtual std::size_t getStageLvl() const = 0;
        virtual std::string getStageBackground() const = 0;

        // STEP DATA
        virtual bool isStageEnd() const = 0;
        virtual StageStep getStageStep(bool move = true) = 0;
        virtual std::queue<StageStep> getStagePrevious(std::size_t nb) const = 0;
        virtual std::queue<StageStep> getStageStepAt(std::size_t time, bool move = true) = 0;

        // ENDED DATA
        virtual std::string getStageNext() const = 0;
};

#endif