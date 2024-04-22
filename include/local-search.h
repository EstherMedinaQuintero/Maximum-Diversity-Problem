#ifndef LOCAL_SEARCH_H
#define LOCAL_SEARCH_H

#include "algorithm.h"

class LocalSearch: public Algorithm {
 public:
  /// Constructor
  LocalSearch(std::vector<Point> points, int number_of_points): Algorithm(points, number_of_points) {}

  /// Sobrecarga del método virtual
  void solve() override;
};

#endif