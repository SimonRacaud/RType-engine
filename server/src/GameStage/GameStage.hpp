/*
** EPITECH PROJECT, 2021
** GameStage
** File description:
** GameStage.hpp
*/

#ifndef GAMESTAGE_HPP
#define GAMESTAGE_HPP

#include "IGameStage.hpp"
#include "Tools/EndedData.hpp"
#include "Tools/HeaderData.hpp"

class GameStage : public IGameStage
{
    public:
        GameStage(const std::string &path);
        GameStage(std::vector<std::string> file);
        ~GameStage();

        // HEADER DATA
        std::size_t getStageLvl() const;
        std::string getStageBackground() const;

        // STEP DATA
        bool isStageEnd() const;
        StageStep getStageStep(bool move = true);
        std::queue<StageStep> getStagePrevious(std::size_t nb) const;
        std::queue<StageStep> getStageStepAt(std::size_t time, bool move = true);

        // ENDED DATA
        std::string getStageNext() const;

    protected:
        void sort();
        void extract();
        void applyFormat();
        void checkFormat() const;
        void extractStep();
        void extractEnded();
        void extractHeader();
        EntityType extractEntityType(const std::string &) const;
        std::vector<std::string> splitToken(const std::string &, char) const;
        std::vector<std::string> readFile(const std::string &) const;
        static bool matchWithRegex(const std::string &sample, const std::string &regex);

    private:
        std::vector<std::string> _content;
        std::vector<StageStep> _step;
        HeaderData _header;
        EndedData _ended;
        size_t _pos;
        const std::vector<std::pair<std::string, EntityType>> _link = {
            {"BONUS_HP", EntityType::BONUS_HP},
            {"BONUS_SPEED", EntityType::BONUS_SPEED},
            {"ENEMY_PLANE_1", EntityType::ENEMY_PLANE_1},
            {"ENEMY_PLANE_2", EntityType::ENEMY_PLANE_2},
            {"ENEMY_ALIEN_EASY", EntityType::ENEMY_ALIEN_EASY},
            {"ENEMY_ALIEN_HARD", EntityType::ENEMY_ALIEN_HARD},
        };
};

#endif