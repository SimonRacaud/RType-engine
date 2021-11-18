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
        VELOCITY = 0x1,
        POSITION = 0x2,
        SCORE = 0x4,
        EQUIPMENT_COMP = 0x8,
        HEALTH = 0x16,
        ANIMATION_INFO = 0x32,
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