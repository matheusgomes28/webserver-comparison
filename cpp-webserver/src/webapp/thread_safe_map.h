#ifndef THREAD_SAFE_MAP_H
#define THREAD_SAFE_MAP_H

#include <map>
#include <mutex>
#include <optional>

#include <iostream>

template <typename K, typename V>
class ThreadSafeMap {
public:
    bool add_item(K const& key, V const& value) {
        std::lock_guard<std::mutex> map_lock{_map_mutex};
        
        // do not change item value if it exists
        auto const found = _map.find(key);
        if (found != end(_map)) {
            std::cout << "item already in the map\n";
            return false;
        }

        _map.insert({key, value});
        return true;
    }

    std::optional<V> remove_item(K const& key) {
        std::lock_guard<std::mutex> map_lock{_map_mutex};

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
        std::lock_guard<std::mutex> map_lock{_map_mutex};

        auto const found = _map.find(key);
        if (found == end(_map)) {
            return std::nullopt;
        }

        return found->second;
    }

    std::map<K, V> get_items() {
        std::lock_guard<std::mutex> map_lock{_map_mutex};
        return _map; // Copy to return value
    }

private:
    std::mutex _map_mutex;
    std::map<K, V> _map;
};

#endif // THREAD_SAFE_MAP_
