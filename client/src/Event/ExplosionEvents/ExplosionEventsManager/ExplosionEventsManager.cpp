/*
** EPITECH PROJECT, 2021
** RType
** File description:
** ExplosionEventsManager
*/

#include "ExplosionEventsManager.hpp"
#include "Entities/Explosion/Explosion.hpp"

ExplosionEventsManager::ExplosionEventsManager()
{
	GET_EVENT_REG.registerCallback(std::function<void(const BulletExplosion *)>(bulletExplosion));
}

void bulletExplosion(const BulletExplosion *e)
{
    try {
        static auto last = std::chrono::system_clock::from_time_t(0);
        auto &pos = GET_COMP_M.get<Engine::Position>(e->_entity);

        std::chrono::duration<double> tmp = std::chrono::system_clock::now() - last;
        size_t nb_sec = (size_t)tmp.count();
        std::cout << "EXPLOSION -----------------------> " << nb_sec << " && "
                  << std::chrono::duration<double>(1).count() << std::endl;
        if (nb_sec > std::chrono::duration<double>(1).count()) {
            Explosion(GET_ENTITY_M.getCluster(e->_entity), vector2D((float)pos.x, pos.y));
            last = std::chrono::system_clock::now();
        }
    } catch (std::exception) {}
}