#pragma once

#include <list>
#include <vector>

namespace ExtendedEuclidean {
  using std::list;
  using std::next;
  using std::size_t;
  using std::vector;

  // 0-based implementation; unlike the README
  template <typename T> T extended_euclidean(const list<T> &cof, list<T> &var) {
    if (cof.back() == 0) {
      // Get number of zero coefficients, and one of the non-zero's
      size_t cntZeros = 0;
      auto itCof = cof.begin(), nonZeroCof = cof.begin();
      auto itVar = var.begin(), nonZeroVar = var.begin();
      for (; itCof != cof.end(); ++itCof, ++itVar)
        if (*itCof == 0) {
          cntZeros++;
          *itVar = 0;
        } else {
          nonZeroCof = itCof;
          nonZeroVar = itVar;
        }
      // Base case
      if (cntZeros + 1 >= cof.size()) {
        *nonZeroVar = 1;
        return *nonZeroCof;
      }
      // Move non-zeros to new containers
      list<T> newCof, newVar;
      itCof = cof.begin();
      itVar = var.begin();
      for (; itCof != cof.end(); ++itCof, ++itVar)
        if (*itCof) {
          newCof.push_back(*itCof);
          newVar.push_back(*itVar);
        }
      // Run the algorithm on the new containers
      T gcd = extended_euclidean(newCof, newVar);
      // Transfer back the results
      itCof = cof.begin();
      itVar = var.begin();
      for (; !newVar.empty(); ++itCof, ++itVar)
        if (*itCof) {
          *itVar = newVar.front();
          newVar.pop_front();
        }
      return gcd;
    }
    // Create the new right-cyclic shifted container with the same coefficients
    // and taking the modulo
    list<T> newCof = cof;
    newCof.push_front(newCof.back());
    newCof.pop_back();
    for (auto it = next(newCof.begin()); it != newCof.end(); ++it)
      *it %= newCof.front();
    // Right-cyclic shift for the variables' container
    var.push_front(var.back());
    var.pop_back();
    // Run the algorithm on the new containers
    T gcd = extended_euclidean(newCof, var);
    // Infer the variables
    auto itCof = cof.begin();
    auto itVar = next(var.begin());
    for (; itVar != var.end(); ++itCof, ++itVar)
      var.front() -= *itCof / cof.back() * *itVar;
    // Do a left-cyclic shift to restore the variables' container
    var.push_back(var.front());
    var.pop_front();
    return gcd;
  }

  template <typename T>
  vector<T> find_any_solution(const vector<T> &cof, T rhs) {
    if (cof.empty())
      return {};
    list<T> listCof(cof.begin(), cof.end()), listVar(cof.size());
    T gcd = extended_euclidean(listCof, listVar);
    // Handle the case where there is no solution to the equation
    if (gcd && rhs % gcd)
      return {};
    vector<T> var(listVar.begin(), listVar.end());
    if (gcd) {
      rhs /= gcd;
      for (auto &it : var)
        it *= rhs;
    }
    return var;
  }
} // namespace ExtendedEuclidean
