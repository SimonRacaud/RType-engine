/*
** EPITECH PROJECT , 2021
** ClusterName
** File description:
** simon
*/

#ifndef CLUSTERNAME_HPP
#define CLUSTERNAME_HPP

namespace Engine {
    enum class ClusterName {
        GLOBAL = 0,

        #ifdef CUSTOM_CLUSTERS
            CUSTOM_CLUSTERS
        #endif
    };
}

#endif // CLUSTERNAME_HPP
