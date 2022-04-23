#include "hashmap.hpp"
#include "client/pointers.hpp"
#include "common_helpers.hpp"

using namespace intercept::types;

size_t intercept::sqf::rv_hashmap_values::count() const {
    if (is_split()) {
        return split_keys().count();
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

std::optional<std::pair<r_string, const game_value&>> intercept::sqf::rv_hashmap_values::get(const size_t idx) const {
    if (idx >= count()) {
        return std::nullopt;
    }
    if (is_split()) {
        return std::make_pair(static_cast<r_string>(split_keys()[idx]), split_values()[idx]);
    } else {
        auto a = _value[idx].to_array();
        return std::make_pair(static_cast<r_string>(a[0]), a[1]);
    }
}
