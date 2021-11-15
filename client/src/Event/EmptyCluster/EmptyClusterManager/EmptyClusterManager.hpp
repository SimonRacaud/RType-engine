/*
** EPITECH PROJECT, 2021
** EmptyClusterManager
** File description:
** EmptyClusterManager.hpp
*/

#ifndef EMPTYCLUSTERMANAGER_HPP
#define EMPTYCLUSTERMANAGER_HPP

#include "Event/EmptyCluster/EmptyCluster.hpp"
#include "Event/EventCallBackRegister/EventCallbackRegister.hpp"

class EmptyClusterManager
{
	public:
        EmptyClusterManager();
        ~EmptyClusterManager() = default;

    private:
        static void doWork(const EmptyCluster *);
};

#endif