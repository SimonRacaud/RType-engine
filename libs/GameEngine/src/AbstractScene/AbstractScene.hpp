/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** AbstractScene
*/

#ifndef ABSTRACTSCENE_HPP_
#define ABSTRACTSCENE_HPP_

#include "IScene.hpp"

namespace Engine
{
    template <class SceneType>
    class AbstractScene : public IScene {
      public:
        AbstractScene(ClusterName cluster);
        virtual ~AbstractScene() = default;

        virtual void close();
        virtual void open() = 0;

        ClusterName getCluster() const;
        TypeIdx getType() const;
        bool isClosed() const;

        static const TypeIdx type;

      protected:
        ClusterName _cluster;
        bool _closed{false};
    };

    template <class SceneType>
    AbstractScene<SceneType>::AbstractScene(ClusterName cluster)
        : _cluster(cluster)
    {}

    template <class SceneType>
    void AbstractScene<SceneType>::close()
    {
        // TODO
        this->_closed = true;
    }

    template <class SceneType>
    ClusterName AbstractScene<SceneType>::getCluster() const
    {
        return _cluster;
    }

    template <class SceneType>
    TypeIdx AbstractScene<SceneType>::getType() const
    {
        return AbstractScene<SceneType>::type;
    }

    template <class SceneType>
    bool AbstractScene<SceneType>::isClosed() const
    {
        return _closed;
    }
}

#endif /* !ABSTRACTSCENE_HPP_ */