#ifndef THREAD_SAFE_MAP_H
#define THREAD_SAFE_MAP_H

#include <optional>
#include <shared_mutex>

#ifdef BUILD_STD_MAP
#include <map>
template <typename K, typename V>
using Map = std::map<K, V>;
#endif // BUILD_STD_MAP
#ifdef BUILD_STD_UNORDERED_MAP
#include <unordered_map>
template <typename K, typename V>
using Map = std::unordered_map<K, V>;
#endif // BUILD_STD_UNORDERED_MAP
#ifdef BUILD_DENSE_MAP
#include <ankerl/unordered_dense.h>
template <typename K, typename V>
using Map = ankerl::unordered_dense::map<K, V>;
#endif // BUILD_DENSE_MAP


template <typename K, typename V>
class ThreadSafeMap {
public:
    bool add_item(K const& key, V const& value) {
        std::unique_lock<std::shared_mutex> map_lock{_map_mutex};
        
        // do not change item value if it exists
        auto const found = _map.find(key);
        if (found != end(_map)) {
            return false;
        }

        _map.insert({key, value});
        return true;
    }

    std::optional<V> remove_item(K const& key) {
        std::unique_lock<std::shared_mutex> map_lock{_map_mutex};

        auto const found = _map.find(key);
        if (found == end(_map)) {
            // cannot remove the item
            return std::nullopt;
        }

        auto const value = std::move(found->second);
        _map.erase(found);
        return value;
    }

    std::optional<V> get_item(K const& key) {
        std::unique_lock<std::shared_mutex> map_lock{_map_mutex};

        auto const found = _map.find(key);
        if (found == end(_map)) {
            return std::nullopt;
        }

        return found->second;
    }

    Map<K, V> get_items() {
        std::shared_lock<std::shared_mutex> map_lock{_map_mutex};
        return _map; // Copy to return value
    }

private:
    std::shared_mutex _map_mutex;
    Map<K, V> _map;
};

#endif // THREAD_SAFE_MAP_
