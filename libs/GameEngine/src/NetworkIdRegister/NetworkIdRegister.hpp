/*
** EPITECH PROJECT , 2021
** NetworkIdRegister
** File description:
** \file NetworkIdRegister.hpp
** \author simon
** \brief
** \date 01/11/2021
*/

#ifndef NETWORKIDREGISTER_HPP
#define NETWORKIDREGISTER_HPP

#include "global.hpp"
#include "Exception/FatalErrorException.hpp"

namespace Engine
{
    using std::vector;

    /**
     * \brief Is responsible to assign the network ids. To avoid collision.
     */
    class NetworkIdRegister {
      private:
        NetworkId _counter{INIT_NET_ID};
        vector<NetworkId> _freeIds;

      public:
        NetworkIdRegister() = default;
        virtual ~NetworkIdRegister() = default;

        NetworkId reserveId();
        NetworkId reserveId(NetworkId id);
        bool isReserved(NetworkId id);
        void releaseId(NetworkId id);
    };
}

#endif // NETWORKIDREGISTER_HPP
