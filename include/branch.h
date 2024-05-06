#ifndef BRANCH_H
#define BRANCH_H

#include "grasp.h"
#include "greedy.h"

class BranchSearch: public Algorithm {
 private:
  double get_node_solution_value(Solution node_solution);
  double highest_distance_ = 0;
  std::string search_strategy_;
  Solution initial_solution_;
  int nodes_generated_ = 0;

 public:
  /// Constructor
  BranchSearch(std::vector<Point> points, int number_of_points, std::string search_strategy, std::string initial_solution_strategy);

  /// Métodos
  void deep_solve();
  void high_value_solve();
  void solve() override;
  int get_generated_nodes() { return nodes_generated_; }
};

#endif