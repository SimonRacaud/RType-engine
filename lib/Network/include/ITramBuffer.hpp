/*
** EPITECH PROJECT, 2021
** ITramBuffer.hpp
** File description:
** Interface for class to ensure trams are sent and received correctly (with the good size) through network
*/
#ifndef R_TYPE_ITRAMBUFFER_HPP
#define R_TYPE_ITRAMBUFFER_HPP

#include <memory>
#include "Concepts/Pointerable.hpp"
#include "INetwork.hpp"

namespace Network
{
    // todo template with constraint ?
    class ITramBuffer {
        /**
         * @brief Set data to the buffer, in order to complete a tram's data
         * @param data
         */
        virtual void SetData(uint8_t *data, size_t size) = 0;
        /**
         * @brief Tells if the received data is one piece (can be used to create at least one tram)
         * @return True if data can be used to create at least one tram, false otherwise
         */
        virtual bool isTramComplete() = 0;
        /**
         * @brief
         * @return The raw tram, nullptr if tram is not complete
         */
        virtual uint8_t *receiveTram() = 0;
    };
} // namespace Network

#endif // R_TYPE_ITRAMBUFFER_HPP