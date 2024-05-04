#pragma once

#include "grasp.h"
#include "greedy.h"

class RamificacionPodaMDP : public Algorithm {
 public:
  /**
   * @brief Constructor of the grasp algorithm class
   * 
   * @param points points of the problem
   * @param number_of_iterations number of iterations of the algorithm
   * @param number_of_points number of points of the problem
   */
  RamificacionPodaMDP(std::vector<Point> points, int number_of_points, std::string search_strategy, std::string initial_solution_strategy)
      : Algorithm(points, number_of_points), search_strategy_(search_strategy) {
    for (auto point : points_) {
      for (auto point2 : points_) {
        if (point.distance_to(point2) > highest_distance_) {
          highest_distance_ = point.distance_to(point2);
        }
      }
    }

    if (initial_solution_strategy == "greedy") {
      Greedy greedy(points_, number_of_points_);
      greedy.solve();
      initial_solution_ = greedy.get_solution();
    } else if (initial_solution_strategy == "grasp") {
      Grasp grasp(points_, number_of_points_, 3, 20);
      initial_solution_ = grasp.constructive();
    }
  }

  /**
   * @brief Solve the problem using deep search
   */
  void DeepSolver();

  /**
   * @brief Solve the problem exploring the tree by high value nodes
   */
  void HighValueSolver();

  void solve() override {
    if (search_strategy_ == "deep") {
      DeepSolver();
    } else {
      HighValueSolver();
    }
  }

  int GetNodesGenerated() { return nodes_generated_; }

 private:
  double GetNodeSolutionValue(Solution node_solution);
  double highest_distance_ = 0;
  std::string search_strategy_;
  Solution initial_solution_;
  int nodes_generated_ = 0;
};