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

#include <stdint.h>

namespace Network {
    template <class Model>
    class ISerializable {
      public:
        virtual ~ISerializable() = default;

        virtual uint8_t *deserialize() = 0;
        virtual void serialize(uint8_t *buffer) = 0;
    };
}

#endif // ISERIALIZABLE_HPP
