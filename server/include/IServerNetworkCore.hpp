/*
** EPITECH PROJECT , 2021
** IServerNetworkCore
** File description:
** \file IServerNetworkCore.hpp
** \author simon
** \brief
** \date 16/11/2021
*/

#ifndef ISERVERNETWORKCORE_HPP
#define ISERVERNETWORKCORE_HPP

#include <stddef.h>
#include <string>
#include "globalServer.hpp"
#include "utils/netVector2f.hpp"

class IServerNetworkCore {
  public:
    virtual ~IServerNetworkCore() = default;

    /**
     * @brief Broadcast entity creation request
     * @param roomId
     * @param id
     * @param type
     */
    virtual void createEntity(size_t roomId, std::string const &type, Network::netVector2f const& position, Network::netVector2f const& velocity) = 0;
    /**
     * @brief Broadcast entity destruction request
     * @param roomId
     * @param id
     */
    virtual void destroyEntity(size_t roomId, NetworkId id) = 0;
    /**
     * @brief Broadcast component synchronization request
     * @param roomId
     * @param id
     * @param componentType
     * @param componentSize
     * @param component
     */
    virtual void syncComponent(size_t roomId, NetworkId id, std::type_index const &componentType,
        size_t componentSize, void *component) = 0;

    /**
     * @brief Broadcast end of game
     * @param roomId
     */
    virtual void endGame(size_t roomId) = 0;
    virtual void receiveLoop() = 0;
};

#endif // ISERVERNETWORKCORE_HPP
