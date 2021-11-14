/*
** EPITECH PROJECT, 2021
** TramBuffer.hpp
** File description:
** Ensure trams are sent and received correctly (with the good size) through network
*/
#ifndef R_TYPE_TRAMBUFFER_HPP
#define R_TYPE_TRAMBUFFER_HPP

#include <iostream>
#include "ITramBuffer.hpp"
#include "Tram/Serializable.hpp"

namespace Tram
{
    class TramBuffer {
      public:
        TramBuffer() = default;
        ~TramBuffer() = default;

        /**
         * @brief Set data to the buffer, in order to complete a tram's data
         * @param data
         */
        void SetData(uint8_t *data, size_t size);
        /**
         * @brief Tells if the received data is one piece (can be used to create at least one tram)
         * @return True if data can be used to create at least one tram, false otherwise
         */
        bool isTramComplete();
        /**
         * @brief
         * @return The raw tram, nullptr if tram is not complete
         */
        uint8_t *receiveTram();

      private:
        /**
         * @brief Get the size of the tram, stored in the data, in the form of a standardized header
         * @return The size of the tram in bytes
         */
        std::size_t getTramSize();

      private:
        uint8_t *_data{nullptr};
        std::size_t _dataLength{0};
    };
} // namespace Tram

#endif // R_TYPE_TRAMBUFFER_HPP