#include "extended_euclidean.hpp"
#include <chrono>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<long> fibonacci(size_t size) {
  if (size == 0)
    return {};
  if (size == 1)
    return {1};
  vector<long> fib;
  fib.reserve(size);
  fib.emplace_back(1);
  fib.emplace_back(1);
  for (size_t i = 2; i < size; i++)
    fib.emplace_back(fib[i - 1] + fib[i - 2]);
  return fib;
}

template <typename T> vector<T> concat(size_t times, const vector<T> &vec) {
  vector<T> res;
  res.reserve(times * vec.size());
  for (size_t i = 0; i < times; i++)
    res.insert(res.end(), vec.begin(), vec.end());
  return res;
}

template <typename T> string test(const vector<T> &coef, T rhs) {
  auto start = chrono::high_resolution_clock::now();
  auto vars = ExtendedEuclidean::find_any_solution(coef, rhs);
  auto end = chrono::high_resolution_clock::now();
  auto diff = end - start;
  string takenTime =
      " in " + to_string(chrono::nanoseconds(diff).count() / 1'000'000) + " ms";
  if (vars.empty())
    return "Empty  : Did not find a valid solution" + takenTime;
  T lhs = 0;
  size_t size = coef.size();
  for (size_t i = 0; i < size; i++)
    lhs += coef[i] * vars[i];
  if (lhs != rhs)
    return "Error  : " + to_string(lhs) + " != " + to_string(rhs) + takenTime;
  return "Success: Found " + to_string(rhs) + " for a vector of size " +
         to_string(coef.size()) + takenTime;
}

int main() {
  cout << test({1, 2}, 3) << endl;
  cout << test({12, 22}, 5) << endl;
  cout << test({1, 2, 3}, 11) << endl;
  ofstream outFile("Test_Results.out");
  auto fib90 = fibonacci(90);
  outFile << test(fib90, 5L) << endl;
  outFile << test(concat(10, fib90), 5L) << endl;
  outFile << test(concat(100, fib90), 5L) << endl;
  outFile << test(concat(1'000, fib90), 5L) << endl;
  outFile << test(concat(10'000, fib90), 5L) << endl;
  outFile << test(concat(20'000, fib90), 5L) << endl;
  outFile << test(concat(40'000, fib90), 5L) << endl;
  return 0;
}
