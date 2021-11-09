/*
** EPITECH PROJECT, 2021
** GameEngine
** File description:
** 27/05/2021 env.hpp.h
*/

#ifndef ENV_HPP
#define ENV_HPP

#include <cstdint>

/**
 * @brief display debug information on stderr
 */
#define ENABLE_DEBUG
#define DEBUG_COMPONENT true

/**
 * @brief Size of the component manager container
 */
#define MAX_COMPONENT_TYPE 512

/**
 * @brief Default size of a component type register container
 */
#define ALLOC_COMPONENT_INSTANCE 8

/**
 * @brief Default size of the entity register container
 */
#define ALLOCATE_NB_ENTITY 512

/**
 *  @brief Unique ids for networking purpose
 */
#define NO_NET_ID 0
#define INIT_NET_ID 1

/**
 * @brief Default system running frequency
 */
#define DEF_SYSTEM_RUN_FREQ (const Time)10

/**
 * @brief SceneManager refresh scene change frequency
 */
#define SCENE_MANAG_FREQ_FLUSH_CHANGE (const Time)500

#define MAX_THROW_EXIT 20

#endif // ENV_HPP
