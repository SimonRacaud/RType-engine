/*
** EPITECH PROJECT, 2021
** SyncSend
** File description:
** SyncSend.hpp.h
*/

#ifndef SYNCSEND_HPP
#define SYNCSEND_HPP

#include "build.hpp"
#include "Components/EntityMask.hpp"
#include "BaseComponent/BaseComponent.hpp"

namespace Component
{
    enum toSync
    {
        VELOCITY = 0x1,
        POSITION = 0x2,
        SCORE = 0x4,
    };
    struct SyncSend : public Engine::BaseComponent<SyncSend> {
        SyncSend(Component::MASK type, int syncFlag) : _type(type), _syncFlag(syncFlag) {}
        virtual ~SyncSend() = default;

        Component::MASK _type;
        int _syncFlag;
    };
}

#endif