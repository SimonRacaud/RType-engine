/*
** EPITECH PROJECT, 2021
** LockedUnorderedMultimap.hpp
** File description:
** std::unordered_multimap but thread safe
*/
#ifndef R_TYPE_LOCKED_UNORDERED_MULTIMAP_HPP
#define R_TYPE_LOCKED_UNORDERED_MULTIMAP_HPP

#include <mutex>
#include <unordered_map>

namespace ThreadSafety
{
    /**
     * @brief A thread safe unordered multimap, with only used methods
     */
    template <class Key, class T, class Hash = std::hash<Key>>
    class LockedUnorderedMultimap : public std::unordered_multimap<Key, T, Hash> {
        using iterator = typename std::unordered_multimap<Key, T, Hash>::iterator;
        using const_iterator = typename std::unordered_multimap<Key, T, Hash>::const_iterator;

      public:
        LockedUnorderedMultimap() = default;
        ~LockedUnorderedMultimap() = default;

        // Capacity
        [[nodiscard]] bool empty() const noexcept
        {
            std::scoped_lock lock(_mutex);

            return std::unordered_multimap<Key, T, Hash>::empty();
        }
        std::size_t size() const noexcept
        {
            std::scoped_lock lock(_mutex);

            return std::unordered_multimap<Key, T, Hash>::size();
        }
        // Modifiers
        void clear() noexcept
        {
            std::scoped_lock lock(_mutex);

            std::unordered_multimap<Key, T, Hash>::clear();
        }

        iterator erase(iterator pos)
        {
            std::scoped_lock lock(_mutex);

            return std::unordered_multimap<Key, T, Hash>::erase(pos);
        }
        std::size_t erase(const Key &key)
        {
            std::scoped_lock lock(_mutex);

            return std::unordered_multimap<Key, T, Hash>::erase(key);
        }
        iterator erase(const_iterator pos)
        {
            std::scoped_lock lock(_mutex);

            return std::unordered_multimap<Key, T, Hash>::erase(pos);
        }

        template <class... Args> iterator emplace(Args &&...args)
        {
            std::scoped_lock lock(_mutex);

            return std::unordered_multimap<Key, T, Hash>::emplace(args...);
        }
        // Iterators
        iterator begin() noexcept
        {
            std::scoped_lock lock(_mutex);

            return std::unordered_multimap<Key, T, Hash>::begin();
        }
        const_iterator begin() const noexcept
        {
            std::scoped_lock lock(_mutex);

            return std::unordered_multimap<Key, T, Hash>::begin();
        }
        iterator end() noexcept
        {
            std::scoped_lock lock(_mutex);

            return std::unordered_multimap<Key, T, Hash>::end();
        }
        const_iterator end() const noexcept
        {
            std::scoped_lock lock(_mutex);

            return std::unordered_multimap<Key, T, Hash>::end();
        }

        std::pair<Key, T> extract(const_iterator position)
        {
            std::scoped_lock lock(_mutex);
            
            auto nodeHandle(std::unordered_multimap<Key, T, Hash>::extract(position));
            auto extracted(std::make_pair(std::move(nodeHandle.key()), std::move(nodeHandle.mapped())));

            return extracted;
        }

      private:
        /**
         * @brief multimap is able to contain duplicates
         */
        //    std::unordered_multimap<Key, T, Hash> my_multiMap;
        /**
         * @brief mutex should make this class thread safe
         * @note mutable means modifiable in const method
         */
        mutable std::mutex _mutex;
    };
} // namespace ThreadSafety
#endif // R_TYPE_LOCKED_UNORDERED_MULTIMAP_HPP