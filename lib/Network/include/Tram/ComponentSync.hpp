/*
** EPITECH PROJECT , 2021
** ComponentSync
** File description:
** \file ComponentSync.hpp
** \author simon
** \brief
** \date 11/11/2021
*/

#ifndef COMPONENTSYNC_HPP
#define COMPONENTSYNC_HPP

#include <inttypes.h>
#include <stddef.h>
#include "timeDef.hpp"

namespace Tram {
    struct ComponentSync {
        /**
         * @brief network id of the entity
         */
        uint32_t networkId;
        /**
         * @brief action timestamp (rollback)
         */
        Time timestamp;
        /**
         * @brief size of the component
         */
        size_t size;
        /**
         * @brief component serialized struct
         */
        void *component;
    };
}

#endif // COMPONENTSYNC_HPP
