/*
** EPITECH PROJECT , 2021
** ISerializable
** File description:
** \file ISerializable.hpp
** \author simon
** \brief
** \date 12/11/2021
*/

#ifndef ISERIALIZABLE_HPP
#define ISERIALIZABLE_HPP

#include <cstdint>

namespace Network
{
    class ISerializable {
      public:
        virtual ~ISerializable() = default;

        /**
         * @brief compile data in a buffer
         * @return
         */
        [[nodiscard]] virtual uint8_t *serialize() const = 0;
        /**
         * @brief extract data from the buffer
         * @param buffer
         */
        virtual void deserialize(uint8_t *buffer) = 0;
        /**
         * @brief Tram data size
         * @return
         */
        [[nodiscard]] virtual size_t length() const = 0;
    };
} // namespace Network

#endif // ISERIALIZABLE_HPP