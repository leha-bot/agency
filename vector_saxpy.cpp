#include <execution_policy>
#include <algorithm>
#include <cassert>
#include <iostream>

int main()
{
  size_t n = 1 << 16;
  std::vector<float> x(n, 1), y(n, 2), z(n);
  float a = 13.;

  std::bulk_invoke(std::vec(n), [&](std::vector_agent<> &g)
  {
    int i = g.index();
    z[i] = a * x[i] + y[i];
  });

  float expected  = a * 1. + 2.;
  assert(std::all_of(z.begin(), z.end(), [=](float x){ return expected == x; }));

  std::cout << "OK" << std::endl;

  return 0;
}
