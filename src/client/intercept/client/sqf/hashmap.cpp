#include "hashmap.hpp"
#include "client/pointers.hpp"
#include "common_helpers.hpp"
#include <algorithm>
#include <iostream>

using namespace intercept::types;

size_t intercept::sqf::rv_hashmap_values::count() const {
    if (is_split()) {
        return std::min(split_keys().count(), split_values().count());
    } else {
        return _value.to_array().count();
    }
}

intercept::sqf::rv_hashmap_values::rv_hashmap_values(game_value value, bool split):
    _value(std::move(value)),
    _split(split)
{
}

intercept::sqf::rv_hashmap_values intercept::sqf::to_array(const game_value& m, bool split) {
    return rv_hashmap_values(host::functions.invoke_raw_binary(__sqf::binary__toarray__hashmap__bool__ret__array, m, split), split);
}

std::optional<std::pair<r_string, game_value&>> intercept::sqf::rv_hashmap_values::get(const size_t idx) const {
    if (idx >= count()) {
        return std::nullopt;
    }
    if (is_split()) {
        auto key = split_keys()[idx];
        const game_value& value = split_values()[idx];
        fprintf(stderr, "k[%d], v[%d]\n", key.type_enum(), value.type_enum());
        std::pair<r_string, game_value&> ret = { static_cast<r_string>(split_keys()[idx]), split_values()[idx] };
        return ret;
    } else {
        auto a = _value[idx].to_array();
        std::pair<r_string, game_value&> ret = { static_cast<r_string>(a[0]), a[1] };
        return ret;
    }
}
