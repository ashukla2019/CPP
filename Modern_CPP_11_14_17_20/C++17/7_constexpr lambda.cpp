Compile-time lambdas using constexpr.

auto identity = [](int n) constexpr { return n; };
static_assert(identity(123) == 123);
constexpr auto add = [](int x, int y) {
  auto L = [=] { return x; };
  auto R = [=] { return y; };
  return [=] { return L() + R(); };
};
