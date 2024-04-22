#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <algorithm>

#include "problem.h"
#include "solution.h"
#include "point.h"

class Algorithm {
 protected:
  int number_of_points_;
  std::vector<Point> points_;
  Solution solution_points_;

 public:
  /// Constructor
  Algorithm(std::vector<Point> points, int number_of_points);

  /// Getters
  inline Solution get_solution() { return solution_points_; }
  Point get_gravity_center(std::vector<Point> points);

  /// Métodos virtuales
  virtual void solve() = 0;
};

#endif 