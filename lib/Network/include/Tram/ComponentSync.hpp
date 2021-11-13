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

#include <cinttypes>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <typeindex>
#include "ISerializable.hpp"
#include "utils/timeDef.hpp"

namespace Tram
{
#define COMP_SYNC_HEAD_SIZE \
    (sizeof(size_t) + sizeof(uint32_t) + sizeof(Time) + sizeof(size_t) + sizeof(size_t) + sizeof(void *))

    class ComponentSync : public Network::ISerializable {
      public:
        ComponentSync() = default;
        ComponentSync(uint32_t networkId, Time timestamp, std::type_index const &componentType, size_t componentSize,
            void *component);
        ~ComponentSync() override;

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

        [[nodiscard]] uint8_t *serialize() const override;
        void deserialize(uint8_t *buffer) override;
        explicit ComponentSync(uint8_t *buffer);
        [[nodiscard]] std::size_t length() const override;
    };
} // namespace Tram

#endif // COMPONENTSYNC_HPP