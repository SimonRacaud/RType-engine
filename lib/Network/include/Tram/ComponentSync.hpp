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
#include <cstring>
#include <stdexcept>
#include <stddef.h>
#include "utils/timeDef.hpp"
#include <typeindex>
#include "ISerializable.hpp"

namespace Network
{
    namespace Tram
    {
        #define COMP_SYNC_HEAD_SIZE (sizeof(uint32_t) + sizeof(Time) + sizeof(size_t) * 3) \
            + sizeof(void *)

        class ComponentSync : public ISerializable<ComponentSync> {
          public:
            ComponentSync() = default;
            virtual ~ComponentSync();

            /**
              * @brief total size
             */
            size_t size;
            /**
              * @brief network id of the entity
             */
            uint32_t networkId;
            /**
              * @brief action timestamp (rollback)
             */
            Time timestamp;
            /**
              * @brief Component type
             */
            size_t componentType;
            /**
              * @brief size of the component
             */
            size_t componentSize;
            /**
              * @brief component serialized struct
             */
            void *component;
            // <- after deserializing, the component is after in memory

            virtual uint8_t *deserialize();
            virtual void serialize(uint8_t *buffer);
            ComponentSync &operator=(ComponentSync &other);
        };
    }
}

#endif // COMPONENTSYNC_HPP