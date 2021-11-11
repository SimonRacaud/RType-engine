/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** AbstractScene
*/

#ifndef ABSTRACTSCENE_HPP_
#define ABSTRACTSCENE_HPP_

#include "IScene.hpp"
#include "Engine/EngineFactory.hpp"

namespace Engine
{
    #define GET_ENTITY_M Engine::EngineFactory::getInstance().getEntityManager()

    template <class SceneType>
    class AbstractScene : public IScene {
      public:
        AbstractScene(ClusterName cluster);
        AbstractScene();
        virtual ~AbstractScene() = default;

        virtual void close();
        virtual void open() = 0;

        ClusterName getCluster() const;
        TypeIdx getType() const;
        bool isClosed() const;

        static const TypeIdx type;

      protected:
        ClusterName _cluster;
        bool _closed{true};
    };

    template <class SceneType>
    const TypeIdx AbstractScene<SceneType>::type = GET_TYPE_IDX(AbstractScene<SceneType>);

    template <class SceneType>
    AbstractScene<SceneType>::AbstractScene(ClusterName cluster)
        : _cluster(cluster)
    {}

    template <class SceneType>
    void AbstractScene<SceneType>::close()
    {
        SHOW_DEBUG("Will clear scene cluster:");
        GET_ENTITY_M.remove(_cluster); // remove owned entities
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