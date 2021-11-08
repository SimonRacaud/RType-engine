/*
** EPITECH PROJECT , 2021
** SignalManager
** File description:
** \file SignalManager.hpp
** \author simon
** \brief
** \date 08/11/2021
*/

#ifndef SIGNALMANAGER_HPP
#define SIGNALMANAGER_HPP

namespace Engine
{
    class SignalManager {
      public:
        SignalManager() = delete;
        virtual ~SignalManager() = delete;

        static void apply();

      private:
        static void handler(int);
    };
}

#endif // SIGNALMANAGER_HPP
