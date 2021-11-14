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
#include <cstdint>

template <typename T>
/**
 * @brief When this concept is applied to a template variable, this variable must be pointer friendly
 * @tparam T The class to be templated with this concept
 * @note Pointerable is the concept,
 *          what's after the '=' operator are the constraints,
 *          meaning that the class must respect what's specified in it (implement the methods)
 */
concept Pointerable = requires(const T a, uint8_t *b)
{
    /**
     * @brief Constraint to have an operator& in order to get raw data of the class
     */
    {
        a.serialize()
        } -> std::convertible_to<uint8_t *>;
    /**
     * @brief constructable from raw data
     */
    T(b);
    T();

    /**
     * @brief Constraint to have a size method, in order to get the size of the variable in bytes
     * @attention Size in bytes
     */
    {
        a.length()
        } -> std::integral;
};
template <typename T>
/**
 * @brief When this concept is applied to a template variable, this variable must be pointer friendly
 * @tparam T The class to be templated with this concept
 * @note Pointerable is the concept,
 *          what's after the '=' operator are the constraints,
 *          meaning that the class must respect what's specified in it (implement the methods)
 */
concept PointerableUnknownLen = requires(const T a, uint8_t *b, const std::size_t len)
{
    /**
     * @brief Constraint to have an operator& in order to get raw data of the class
     */
    {
        a.serialize()
        } -> std::convertible_to<uint8_t *>;
    /**
     * @brief constructable from raw data
     */
    T(b, len);
    T();

    /**
     * @brief Constraint to have a size method, in order to get the size of the variable in bytes
     * @attention Size in bytes
     */
    {
        a.length()
        } -> std::integral;
};

//#endif // __cplusplus
#endif // R_TYPE_POINTERABLE_HPP