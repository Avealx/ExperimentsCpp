/* Basic usage of views in the ranges library to avoid copies
 *
 * ranges, views
 *
 * motivation: C++ High Performance
 */

#include <algorithm>
#include <iostream>
#include <optional>
#include <ranges>
#include <vector>
using namespace std;

struct Point {
    int x, y;
    double time;
};

auto points = vector{Point{1, -1, 1.0}, Point{2, -2, 2.0}, Point{3, -3, 3.0}, Point{4, -4, 4.0}};

// We need a dedicated function because we want access to the sentinel to check if a max_value
// was found. (I.e. we want the intermediate range `range` to have a name so that we
// can call `std::end(range)` and compare against it.
auto max_value(auto&& range) {
    const auto it = std::ranges::max_element(range);
    return it != std::end(range) ? *it : 0;
}

auto get_max_x(vector<Point> const & points) {
    auto const in_time = [](auto&& p){ return 2.0 <= p.time && p.time <= 3.0; };
    return max_value(points | std::views::filter(in_time) | std::views::transform(&Point::x));
}

int main() {
    cout << get_max_x(points) << endl;  // 3
}
