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
 * Size of the component manager container
 */
#define MAX_COMPONENT_TYPE 512

/**
 * Default size of a component type register container
 */
#define ALLOC_COMPONENT_INSTANCE 8

/**
 * Default size of the entity register container
 */
#define ALLOCATE_NB_ENTITY 512

/**
 *  Unique ids for networking purpose
 */
#define NO_NET_ID 0
#define INIT_NET_ID 1

/**
 * Default system running frequency
 */
#define DEF_SYSTEM_RUN_FREQ 10

#endif // ENV_HPP
