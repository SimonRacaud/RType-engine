/*
** EPITECH PROJECT, 2021
** LockedUnorderedMultimap.hpp
** File description:
** TODO: add description
*/
#ifndef R_TYPE_LOCKED_UNORDERED_MULTIMAP_HPP
#define R_TYPE_LOCKED_UNORDERED_MULTIMAP_HPP

#include <mutex>
#include <unordered_map>

namespace ThreadSafety
{
    template <class Key, class T, class Hash = std::hash<Key>>
    using iterator = typename std::unordered_multimap<Key, T, Hash>::iterator;
    template <class Key, class T, class Hash = std::hash<Key>>
    using const_iterator = typename std::unordered_multimap<Key, T, Hash>::const_iterator;

    /**
     * @brief A thread safe unordered multimap, with only used methods
     * @tparam Key
     * @tparam T
     * @tparam Hash
     */
    template <class Key, class T, class Hash = std::hash<Key>>
    class LockedUnorderedMultimap : public std::unordered_multimap<Key, T, Hash> {
        using iterator = typename std::unordered_multimap<Key, T, Hash>::iterator;
        using const_iterator = typename std::unordered_multimap<Key, T, Hash>::const_iterator;

      public:
        LockedUnorderedMultimap() = default;
        ~LockedUnorderedMultimap() = default;

        // Capacity
        [[nodiscard]] bool empty() const noexcept;
        std::size_t size() const noexcept;
        // Modifiers
        void clear() noexcept;

        iterator erase(iterator pos);
        std::size_t erase(const Key &key);
        iterator erase(const_iterator pos);

        template <class... Args> iterator emplace(Args &&...args);
        // Iterators
        iterator begin() noexcept;
        const_iterator begin() const noexcept;
        iterator end() noexcept;
        const_iterator end() const noexcept;

      private:
        /**
         * @brief multimap is able to contain duplicates
         */
        //    std::unordered_multimap<Key, T, Hash> my_multiMap;
        /**
         * @brief mutex should make this class thread safe
         */
        std::mutex _mutex;
    };

    template <class Key, class T, class Hash> bool LockedUnorderedMultimap<Key, T, Hash>::empty() const noexcept
    {
        std::scoped_lock lock(_mutex);
        return std::unordered_multimap<Key, T, Hash>::empty();
    }
    template <class Key, class T, class Hash> std::size_t LockedUnorderedMultimap<Key, T, Hash>::size() const noexcept
    {
        std::scoped_lock lock(_mutex);
        return std::unordered_multimap<Key, T, Hash>::size();
    }
    template <class Key, class T, class Hash> void LockedUnorderedMultimap<Key, T, Hash>::clear() noexcept
    {
        std::scoped_lock lock(_mutex);

        std::unordered_multimap<Key, T, Hash>::clear();
    }
    template <class Key, class T, class Hash>
    iterator<Key, T, Hash> LockedUnorderedMultimap<Key, T, Hash>::erase(iterator pos)
    {
        std::scoped_lock lock(_mutex);
        return std::unordered_multimap<Key, T, Hash>::erase(pos);
    }
    template <class Key, class T, class Hash> std::size_t LockedUnorderedMultimap<Key, T, Hash>::erase(const Key &key)
    {
        std::scoped_lock lock(_mutex);
        return std::unordered_multimap<Key, T, Hash>::erase(key);
    }
    template <class Key, class T, class Hash>
    iterator<Key, T, Hash> LockedUnorderedMultimap<Key, T, Hash>::erase(const_iterator pos)
    {
        std::scoped_lock lock(_mutex);
        return std::unordered_multimap<Key, T, Hash>::erase(pos);
    }
    template <class Key, class T, class Hash>
    template <class... Args>
    iterator<Key, T, Hash> LockedUnorderedMultimap<Key, T, Hash>::emplace(Args &&...args)
    {
        std::scoped_lock lock(_mutex);
        return std::unordered_multimap<Key, T, Hash>::emplace(args...);
    }
    template <class Key, class T, class Hash>
    iterator<Key, T, Hash> LockedUnorderedMultimap<Key, T, Hash>::begin() noexcept
    {
        std::scoped_lock lock(_mutex);
        return std::unordered_multimap<Key, T, Hash>::begin();
    }
    template <class Key, class T, class Hash>
    const_iterator<Key, T, Hash> LockedUnorderedMultimap<Key, T, Hash>::begin() const noexcept
    {
        std::scoped_lock lock(_mutex);
        return std::unordered_multimap<Key, T, Hash>::begin();
    }
    template <class Key, class T, class Hash>
    iterator<Key, T, Hash> LockedUnorderedMultimap<Key, T, Hash>::end() noexcept
    {
        std::scoped_lock lock(_mutex);
        return std::unordered_multimap<Key, T, Hash>::end();
    }
    template <class Key, class T, class Hash>
    const_iterator<Key, T, Hash> LockedUnorderedMultimap<Key, T, Hash>::end() const noexcept
    {
        std::scoped_lock lock(_mutex);
        return std::unordered_multimap<Key, T, Hash>::end();
    }
} // namespace ThreadSafety

#endif // R_TYPE_LOCKED_UNORDERED_MULTIMAP_HPP