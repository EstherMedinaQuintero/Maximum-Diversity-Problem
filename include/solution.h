#ifndef SOLUTION_H
#define SOLUTION_H

#include <fstream>
#include <string>
#include "point.h"

class Solution {
 private:
  std::vector<Point> solution_points_;

 public:
  /// Constructor y destructor
  Solution(std::vector<Point> point) : solution_points_(point) {}
  Solution() {}
  
  /// Getters
  std::vector<Point> GetPoints() { return solution_points_; }

  /// Métodos
  double Value();
  std::string ToString();
};

#endif