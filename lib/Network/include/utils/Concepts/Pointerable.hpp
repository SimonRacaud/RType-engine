/*
** EPITECH PROJECT, 2021
** Pointerable.hpp
** File description:
** TODO: add description
*/
#ifndef R_TYPE_POINTERABLE_HPP
#define R_TYPE_POINTERABLE_HPP

//#if __cplusplus > 201703L && __cpp_concepts >= 201907L

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
        //        &a
        a.data()
        } -> std::convertible_to<T *>;

    {
        // todo realy necessary ?
        //  the receive is automatic
        //  the send does not need to be precised ? yes
        //        sizeof(a) // todo find a way to make that viable with dynamic size variables (arrays ...)
        a.size() // todo find a way to make that viable with dynamic size variables (arrays ...)
                 //        } -> std::convertible_to<std::size_t>;
        } -> std::integral;
    {
        a.getVal() // todo remove after debug
        } -> std::integral;
    {
        *b
        } -> std::convertible_to<T>;
};

//#endif // __cplusplus
#endif // R_TYPE_POINTERABLE_HPP