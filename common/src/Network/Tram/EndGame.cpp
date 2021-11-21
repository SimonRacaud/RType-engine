/*
** EPITECH PROJECT, 2021
** RType
** File description:
** EndGame
*/

#include "Network/Tram/EndGame.hpp"

using namespace Tram;

EndGame::EndGame()
{
}

EndGame::EndGame(size_t roomId, bool win)
    : Tram::Serializable(Tram::TramType::END_GAME, sizeof(EndGame)), roomId(roomId), win(win)
{
}

uint8_t *EndGame::serialize() const
{
    size_t len = sizeof(EndGame);
    auto *buffer = new uint8_t[len];

    std::memset(buffer, 0, len);
    std::memcpy(buffer, (void *) this, len);
    return buffer;
}

void EndGame::deserialize(uint8_t *buffer)
{
    auto *ptr = reinterpret_cast<EndGame *>(buffer);

    this->roomId = ptr->roomId;
}

size_t EndGame::length() const
{
    return sizeof(EndGame);
}

EndGame::EndGame(uint8_t *buffer) : Tram::Serializable(Tram::TramType::END_GAME, sizeof(EndGame))
{
    EndGame::deserialize(buffer);
}