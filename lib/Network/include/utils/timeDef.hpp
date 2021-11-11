/*
** EPITECH PROJECT , 2021
** time
** File description:
** \file time.hpp
** \author simon
** \brief
** \date 11/11/2021
*/

#ifndef TIME_HPP
#define TIME_HPP

#include <chrono>

using Time = std::chrono::milliseconds;
using DurationCast = std::chrono::duration<Time>;
using steadyClock = std::chrono::steady_clock;
using TimePoint = std::chrono::time_point<steadyClock>;

#endif // TIME_HPP