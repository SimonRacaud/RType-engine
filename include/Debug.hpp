/*
** EPITECH PROJECT , 2021
** Debug
** File description:
** \file Debug.hpp
** \author simon
** \brief
** \date 18/11/2021
*/

#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <iostream>
using std::to_string;

    /**
     * @brief Comment that line to disable the debug mode
     */
    #define ENABLE_DEBUG

    #ifdef ENABLE_DEBUG
        #define PUT_DEBUG(message) std::cerr << "[DEBUG] " << message << std::endl;
    #else
    #define PUT_DEBUG(message)
    #endif

#endif // DEBUG_HPP
