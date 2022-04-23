#pragma once
#include "types.hpp"
#include <utility>
#include <optional>

using namespace intercept::types;

namespace intercept {
    namespace sqf {
        class rv_hashmap_values {
        public:
            explicit rv_hashmap_values(game_value value, bool split);
            inline const game_value& value() const { return _value; }
            inline bool is_split() const { return _split; }
            size_t count() const;
            std::optional<std::pair<r_string, const game_value&>> get(const size_t idx) const;
            inline std::pair<r_string, const game_value&> operator[](const size_t idx) const {
                return std::move(get(idx).value());
            }
        private:
            inline auto_array<game_value>& split_keys() const {
                return _value[0].to_array();
            }
            inline auto_array<game_value>& split_values() const {
                return _value[1].to_array();
            }
            game_value _value;
            bool _split;
        };

        rv_hashmap_values to_array(const game_value& m, bool split);
        inline rv_hashmap_values to_array(const game_value& m) {
            return to_array(m, true);
        }
    }
}
