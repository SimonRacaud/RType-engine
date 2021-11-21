/*
** EPITECH PROJECT , 2021
** Serializable
** File description:
** \file Serializable.hpp
** \author simon
** \brief
** \date 11/11/2021
*/

#ifndef HEADER_HPP
#define HEADER_HPP

#include <cinttypes>
#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <string>
#include "Data/Serialization/ISerializable.hpp"
#include "Network/Tram/TramType.hpp"
#include <unordered_map>

#define MAGIC 4242424242

namespace Tram
{
    // todo passer à travers tout les types pour init le header
    class Serializable : public Network::ISerializable {
      public:
        explicit Serializable() = default;
        explicit Serializable(TramType type, size_t size = sizeof(Serializable));
        explicit Serializable(uint8_t *data);

        /**
         * @brief magic number to check the data type
         */
        const size_t magic{MAGIC};
        /**
         * @brief Serialization total size
         */
        size_t size{sizeof(Serializable)};
        /**
         * @brief Serialization type
         */
        TramType type{Tram::TramType::NONE};

        [[nodiscard]] uint8_t *serialize() const override;
        /**
         * @throws InvalidArgument : invalid magic number
         * @param buffer
         */
        void deserialize(uint8_t *buffer) override;
        [[nodiscard]] size_t length() const override;
    };

} // namespace Tram

#endif // HEADER_HPP