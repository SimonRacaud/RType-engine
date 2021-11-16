/*
** EPITECH PROJECT, 2021
** EmptyCluster
** File description:
** EmptyCluster.hpp
*/

#ifndef EMPTYCLUSTER_HPP
#define EMPTYCLUSTER_HPP

#include "Event/IEvent.hpp"
#include <functional>

class EmptyCluster : public Engine::Event::IEvent
{
	public:
		EmptyCluster(Engine::ClusterName cluster, std::function<void (void)> func = nullptr) : _cluster(cluster), _func(func)
        {
        }
		~EmptyCluster() = default;

		std::type_index getType() const override {
			return std::type_index(typeid(this));
		}

    public:
        Engine::ClusterName _cluster;
		std::function<void (void)> _func;
};

#endif