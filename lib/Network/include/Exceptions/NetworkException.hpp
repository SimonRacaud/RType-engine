/*
** EPITECH PROJECT, 2021
** NetworkException.hpp
** File description:
** Facilitate exception handling for network classes
*/
#ifndef R_TYPE_NETWORKEXCEPTION_HPP
#define R_TYPE_NETWORKEXCEPTION_HPP

#include <exception>
#include <string>
#include "utils/formatString.hpp"

namespace Network
{
    class invalidConnection : public std::exception {
      public:
        /**
         * @brief Initialize an exception and format the error message
         * @param message The error message, with two "{}" where ip and port should be placed
         * @param ip The ip of the non-connected machine
         * @param port The port of the non-connected machine
         */
        explicit invalidConnection(
            const std::string &message = _baseMessage, const std::string &ip = "", std::size_t port = 0);
        ~invalidConnection() override = default;

        [[nodiscard]] const char *what() const noexcept override;

      private:
        std::string _message;

      public:
        static const std::string _baseMessage;
        static const std::string _baseMessageFormat;
    };

    inline const std::string invalidConnection::_baseMessage = "Machine not connected";
    inline const std::string invalidConnection::_baseMessageFormat =
        invalidConnection::_baseMessage + " -> ip : {}, port : {}";

    class connectionFailed : public std::exception {
      public:
        /**
         * @brief Initialize an exception and format the error message
         * @param message The error message, with two "{}" where ip and port should be placed
         * @param ip The ip of the non-connected machine
         * @param port The port of the non-connected machine
         */
        explicit connectionFailed(
            const std::string &message = _baseMessage, const std::string &ip = "", std::size_t port = 0);
        ~connectionFailed() override = default;

        [[nodiscard]] const char *what() const noexcept override;

      private:
        std::string _message;

      public:
        static const std::string _baseMessage;
        static const std::string _baseMessageFormat;
    };

    inline const std::string connectionFailed::_baseMessage = "Cannot connect to machine";
    inline const std::string connectionFailed::_baseMessageFormat =
        connectionFailed::_baseMessage + " -> ip : {}, port : {}";

} // namespace Network

#endif // R_TYPE_NETWORKEXCEPTION_HPP