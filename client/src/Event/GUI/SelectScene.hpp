/*
** EPITECH PROJECT , 2021
** SelectScene
** File description:
** \file SelectScene.hpp
** \author simon
** \brief
** \date 13/11/2021
*/

#ifndef SELECTSCENE_HPP
#define SELECTSCENE_HPP

#include "Event/IEvent.hpp"
#include "CustomCluster.hpp"

class SelectScene : public Engine::Event::IEvent
{
  public:
    SelectScene(Engine::ClusterName cluster, bool closeCurrent = true)
        : _cluster(cluster), _closeCurrent(closeCurrent)
    {}
    virtual ~SelectScene() = default;

    std::type_index getType() const override {
        return std::type_index(typeid(this));
    }

    Engine::ClusterName getCluster() const
    {
        return _cluster;
    }

    bool getCloseCurrent() const
    {
        return _closeCurrent;
    }

  private:
    Engine::ClusterName _cluster;
    bool _closeCurrent;
};

#endif // SELECTSCENE_HPP
