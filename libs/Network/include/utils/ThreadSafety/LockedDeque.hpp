/*
** EPITECH PROJECT, 2021
** LockedDeque.hpp
** File description:
** std::deque but thread safe
*/

#ifndef R_TYPE_LOCKEDDEQUE_HPP
#define R_TYPE_LOCKEDDEQUE_HPP

#include <deque>
#include <mutex>

namespace ThreadSafety
{
    template <class T> class LockedDeque : public std::deque<T> {
        using iterator = typename std::deque<T>::iterator;
        using const_iterator = typename std::deque<T>::const_iterator;
        using reference = typename std::deque<T>::reference;

      public:
        LockedDeque() = default;
        ~LockedDeque() = default;

        // Capacity
        [[nodiscard]] bool empty() const noexcept
        {
            std::scoped_lock lock(_mutex);
            return std::deque<T>::empty();
        }
        std::size_t size() const noexcept
        {
            std::scoped_lock lock(_mutex);
            return std::deque<T>::size();
        }
        // Modifiers
        void clear() noexcept
        {
            std::scoped_lock lock(_mutex);
            std::deque<T>::clear();
        }
        template <class... Args> reference emplace_back(Args &&...args)
        {
            std::scoped_lock lock(_mutex);
            return std::deque<T>::emplace_back(args...);
        }
        // Iterators
        iterator begin() noexcept
        {
            std::scoped_lock lock(_mutex);
            return std::deque<T>::begin();
        }
        const_iterator begin() const noexcept
        {
            std::scoped_lock lock(_mutex);
            return std::deque<T>::begin();
        }
        iterator end() noexcept
        {
            std::scoped_lock lock(_mutex);
            return std::deque<T>::end();
        }
        const_iterator end() const noexcept
        {
            std::scoped_lock lock(_mutex);
            return std::deque<T>::end();
        }

        const_iterator erase(const_iterator pos)
        {
            std::scoped_lock lock(_mutex);
            return std::deque<T>::erase(pos);
        }



      private:
        /**
         * @brief mutex should make this class thread safe
         * @note mutable means modifiable in const method
         */
        mutable std::mutex _mutex{};
    };
} // namespace ThreadSafety
#endif // R_TYPE_LOCKEDDEQUE_HPP