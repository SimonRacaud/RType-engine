/*
** EPITECH PROJECT , 2021
** CreateEntityRequest
** File description:
** \file CreateEntityRequest.hpp
** \author simon
** \brief
** \date 11/11/2021
*/

#ifndef CREATEENTITYREQUEST_HPP
#define CREATEENTITYREQUEST_HPP

#include <inttypes.h>
#include <stddef.h>
#include <string>
#include "utils/timeDef.hpp"

namespace Tram {
    struct CreateEntityRequest {
        /**
         * @brief private id of the entity
         */
        uin32_t entityPrivate;
        /**
         * @brief type of the entity factory ex: "player", "enemy"
         * @brief a confirmer
         */
        std::string entityType;
        /**
         * @brief timestamp de creation de l'entité (rollback)
         */
        Time timestamp;
    };
}

#endif // CREATEENTITYREQUEST_HPP