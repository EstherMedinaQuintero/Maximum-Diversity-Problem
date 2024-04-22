#ifndef GREEDY_H
#define GREEDY_H

#include "algorithm.h"

class Greedy: public Algorithm {
 public:
  /// Constructor
  Greedy(std::vector<Point> points, int number_of_points): Algorithm(points, number_of_points) {}

  /// Sobrecarga del método virtual
  void solve() override;
};

#endif