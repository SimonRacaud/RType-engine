/*
** EPITECH PROJECT , 2021
** DestroyEntity
** File description:
** \file DestroyEntity.hpp
** \author simon
** \brief
** \date 11/11/2021
*/

#ifndef DESTROYENTITY_HPP
#define DESTROYENTITY_HPP

#include <cinttypes>
#include <cstddef>
#include <cstring>
#include "Tram/Serializable.hpp"

namespace Tram
{
    class DestroyEntity : public Tram::Serializable {
      public:
        DestroyEntity();
        explicit DestroyEntity(uint32_t networkId);
        /**
         * @brief Network id of the entity
         */
        uint32_t networkId{0};

        [[nodiscard]] uint8_t *serialize() const override;
        void deserialize(uint8_t *buffer) override;
        explicit DestroyEntity(uint8_t *buffer);
        [[nodiscard]] size_t length() const override;
    };

} // namespace Tram

#endif // DESTROYENTITY_HPP