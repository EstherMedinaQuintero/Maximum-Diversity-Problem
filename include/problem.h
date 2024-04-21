#ifndef PROBLEM_H
#define PROBLEM_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "point.h"

class Problem {
 private:
  std::vector<Point> points_;

 public:
  /// Constructor y destructor
  Problem(std::string name);
  Problem() = default;

  /// Getters
  std::vector<Point>& GetPoints() { return points_; }
};

#endif