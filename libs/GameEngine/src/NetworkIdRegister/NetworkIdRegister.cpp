/*
** EPITECH PROJECT , 2021
** NetworkIdRegister
** File description:
** \file NetworkIdRegister.cpp
** \author simon
** \brief
** \date 01/11/2021
*/

#include "NetworkIdRegister.hpp"

using namespace Engine;

NetworkId NetworkIdRegister::reserveId()
{
    NetworkId id;

    if (this->_freeIds.size() != 0) {
        id = _freeIds.back();
        _freeIds.pop_back();
    } else {
        id = _counter;
        this->_counter++;
    }
    return id;
}

NetworkId NetworkIdRegister::reserveId(NetworkId id)
{
   if (_counter > id) {
       auto it = std::find(_freeIds.begin(), _freeIds.begin(), id);

       if (it == _freeIds.end()) {
           throw FatalErrorException("Network id " + std::to_string(id) +
               " already reserved");
       } else {
           _freeIds.erase(it);
       }
   } else {
       for (NetworkId i = _counter; i < id; i++) {
           _freeIds.push_back(i);
       }
       _counter = id + 1;
   }
    return id;
}

void NetworkIdRegister::releaseId(NetworkId id)
{
    if (this->isReserved(id)) {
        if (id == (_counter - 1)) {
            this->_counter--;
        } else {
            _freeIds.push_back(id);
        }
    }
}

bool NetworkIdRegister::isReserved(NetworkId id)
{
    if (_counter > id) {
        auto it = std::find(_freeIds.begin(), _freeIds.begin(), id);

        if (it == _freeIds.end()) {
            return true;
        }
    }
    return false;
}
