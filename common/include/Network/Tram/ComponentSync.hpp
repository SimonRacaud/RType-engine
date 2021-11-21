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
#include "Network/Serializable.hpp"
#include "utils/timeDef.hpp"

namespace Tram
{
    class ComponentSync : public Tram::Serializable {
      public:
        ComponentSync();
        ComponentSync(size_t roomId, uint32_t networkId, Time timestamp, std::type_index const &componentType,
            size_t componentSize, void *component);
        ComponentSync(size_t roomId, uint32_t networkId, Time timestamp, size_t componentType, size_t componentSize,
            void *component);
        ComponentSync &operator=(const ComponentSync &other);

        ~ComponentSync() override;

        size_t roomId{0};
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