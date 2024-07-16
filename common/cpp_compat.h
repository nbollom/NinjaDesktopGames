//
// Created by nbollom on 4/07/24.
//

#pragma once
#include <ranges>

namespace ndg::common {
#ifdef __cpp_lib_ranges_enumerate
    constexpr auto enumerate = std::ranges::views::enumerate;
#else
    template <std::ranges::viewable_range R>
    constexpr auto enumerate(R&& r) {
        return std::views::zip(std::views::iota(0), (R&&)r);
    }
#endif
}
