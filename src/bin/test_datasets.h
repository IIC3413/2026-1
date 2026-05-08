#pragma once

namespace datasets {

constexpr auto INSERT_1 = "insert_basic";
constexpr auto INSERT_2 = "insert_large";

constexpr auto DELETE_1 = "delete_single";
constexpr auto DELETE_2 = "delete_sparse";
constexpr auto DELETE_3 = "delete_duplicate_chain";

constexpr auto REDISTRIBUTE_1 = "redistribute_basic";
constexpr auto REDISTRIBUTE_2 = "redistribute_large";
constexpr auto REDISTRIBUTE_3 = "redistribute_skewed";
constexpr auto REDISTRIBUTE_4 = "redistribute_boundary";

} // namespace datasets