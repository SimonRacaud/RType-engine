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
#include <iostream>
#include "ISerializable.hpp"

namespace Network
{
    namespace Tram
    {
        #define COMP_SYNC_HEAD_SIZE (sizeof(size_t) + sizeof(uint32_t) + sizeof(Time) \
                                + sizeof(size_t) + sizeof(size_t) + sizeof(void *))

        class ComponentSync : public ISerializable<ComponentSync> {
          public:
            ComponentSync() = default;
            ComponentSync(uint32_t networkId, Time timestamp, std::type_index const &componentType,
                size_t componentSize, void *component);
            virtual ~ComponentSync();

            /**
              * @brief total size
             */
            size_t size{0};
            /**
              * @brief network id of the entity
             */
            uint32_t networkId{0};
            /**
              * @brief action timestamp (rollback)
             */
            Time timestamp{0};
            /**
              * @brief Component type
             */
            size_t componentType{0};
            /**
              * @brief size of the component
             */
            size_t componentSize{0};
            /**
              * @brief component serialized struct
             */
            void *component{nullptr};
            // <- after deserializing, the component is after in memory

            virtual uint8_t *deserialize();
            virtual void serialize(uint8_t *buffer);
            ComponentSync &operator=(ComponentSync &other);
            virtual size_t length() const;
        };
    }
}

#endif // COMPONENTSYNC_HPP