/*
** EPITECH PROJECT, 2021
** SyncSend
** File description:
** SyncSend.hpp.h
*/

#ifndef SYNCSEND_HPP
#define SYNCSEND_HPP

#include "build.hpp"
#include "BaseComponent/BaseComponent.hpp"

namespace Component
{
    enum SyncComponentType : int
    {
        VELOCITY = 0b1,
        POSITION = 0b11,
        SCORE = 0b100,
        EQUIPMENT_COMP = 0b1000,
        HEALTH = 0b10110,
        ANIMATION_INFO = 0b100000,
    };
    /**
     * @brief Entities which posses that component will be synchronized on the network
     */
    struct SyncSend : public Engine::BaseComponent<SyncSend> {
        /**
         * @param syncFlag : the components of the entity to sync.
         */
        SyncSend(int syncFlag) : _syncFlag(syncFlag) {}
        virtual ~SyncSend() = default;

        int _syncFlag;
    };
}

#endif