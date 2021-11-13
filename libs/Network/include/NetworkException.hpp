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
        explicit invalidConnection(const std::string &message = "Machine not connected" /* todo change by
                                                                                         * _baseMessage*/
            ,
            const std::string &ip = "", std::size_t port = 0);
        ~invalidConnection() override = default;

        [[nodiscard]] const char *what() const noexcept override;

      private:
        std::string _message;

      public:
        //        static const std::string _baseMessage;
        //        static const std::string _baseMessageFormat;
    };
} // namespace Network

// inline const std::string _baseMessage = "Machine not connected";
// inline const std::string _baseMessageFormat = _baseMessage + " -> ip : {}, port : {}";

#endif // R_TYPE_NETWORKEXCEPTION_HPP