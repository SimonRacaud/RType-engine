/*
** EPITECH PROJECT , 2021
** CreateEntityReply
** File description:
** \file CreateEntityReply.hpp
** \author simon
** \brief
** \date 11/11/2021
*/

#ifndef CREATEENTITYREPLY_HPP
#define CREATEENTITYREPLY_HPP

#include <inttypes.h>

namespace Tram {
    struct CreateEntityReply {
        /**
         * @brief if the request was accepted
         */
        bool accept;
        /**
         * @brief private id of the local entity
         */
        uint32_t entityPrivate;
        /**
         * @brief new network id of the entity
         */
        uint32_t networkId;
    };
}

#endif // CREATEENTITYREPLY_HPP
