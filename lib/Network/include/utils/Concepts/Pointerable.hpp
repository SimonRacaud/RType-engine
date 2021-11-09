/*
** EPITECH PROJECT, 2021
** Pointerable.hpp
** File description:
** TODO: add description
*/
#ifndef R_TYPE_POINTERABLE_HPP
#define R_TYPE_POINTERABLE_HPP

#include <concepts>

template <typename T>
/**
 * @brief When this concept is applied to a template variable, this variable must be pointer friendly
 * @tparam T The class to be templated with this concept
 * @note Pointerable is the concept,
 *          what's after the '=' operator is the constraint, meaning that the class must respect what's specified in it
 */
concept Pointerable = requires(T a, T *b)
{
    {
        &a
        } -> std::convertible_to<T *>;

    {
        *b
        } -> std::convertible_to<T>;
};

#endif // R_TYPE_POINTERABLE_HPP