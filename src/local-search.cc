#include <algorithm>
#include <vector>
#include <numeric>

#include "local-search.h"

/**
 * @brief Resuelve el problema con búsqueda local
 */
Solution LocalSearch::Search(std::vector<Point>& points) {
  int iterations = 0;
  Solution best_solution = solution_;
  do {
    solution_ = best_solution;
    double current_value = solution_.Value();
    std::vector<std::pair<Solution, double>> neighbors = GetNeighborhood(points);
    for (auto neighbor : neighbors) {
      double neighbor_value = neighbor.second;
      if (neighbor_value > current_value) {
        best_solution = neighbor.first;
      }
    }
    ++iterations;
  } while (Solution(best_solution).Value() > solution_.Value() && iterations < iterations_);
  return best_solution;
}

std::vector<std::pair<Solution, double>> LocalSearch::GetNeighborhood(std::vector<Point>& points) {
  std::vector<std::pair<Solution, double>> neighborhood;
  double current_value = solution_.Value();
  for (int i = 0; i < solution_.GetPoints().size(); ++i) {
    for (int j = 0; j < points.size(); ++j) {
      // comprobar que point[j] no esta en solution_
      bool found = false;
      for (int k = 0; k < solution_.GetPoints().size(); ++k) {
        if (solution_.GetPoints()[k].GetId() == points[j].GetId()) {
          found = true;
          break;
        }
      }
      if (!found) {
        std::vector<Point> new_solution = solution_.GetPoints();
        new_solution[i] = points[j];
        double new_value = current_value;
        for (int k = 0; k < new_solution.size(); ++k) {
          if (k != i) {
            new_value += new_solution[i].Distance(new_solution[k]);
            new_value -= solution_.GetPoints()[i].Distance(solution_.GetPoints()[k]);
          }
        }
        neighborhood.push_back(std::pair<Solution, double>(Solution(new_solution), new_value));
      }   
    }
  }
  return neighborhood;
}

/**
 * @brief Obtiene la primera solución
 */
void LocalSearch::GetFirstSolution() {
  std::vector<Point> solution_points;
  solution_points.reserve(number_of_points_);

  // Obtener el punto inicial más alejado del centro de gravedad de todos los puntos
  Point gravity_center_point = GetGravityCenterPoint(points_);
  auto max_iter = std::max_element(points_.begin(), points_.end(),
    [&gravity_center_point](const Point& a, const Point& b) {
      return gravity_center_point.Distance(a) < gravity_center_point.Distance(b);
    });

  solution_points.push_back(*max_iter);
  points_.erase(max_iter); // Elimina el punto más alejado de la lista de puntos

  // Repetir hasta que la cantidad de puntos en solution_points sea igual a number_of_points_
  while ((int)solution_points.size() < number_of_points_) {
    gravity_center_point = GetGravityCenterPoint(solution_points);
    max_iter = std::max_element(points_.begin(), points_.end(),
      [&gravity_center_point](const Point& a, const Point& b) {
        return gravity_center_point.Distance(a) < gravity_center_point.Distance(b);
      });
    solution_points.push_back(*max_iter);
    points_.erase(max_iter); // Elimina el punto más alejado de la lista de puntos
  }

  solution_points_ = Solution(solution_points);
}

/**
 * @brief Resuelve el problema con búsqueda local
 */
void LocalSearch::Solve() {
  GetFirstSolution();
  std::vector<Point> points = points_;
  Solution solution = Search(points);
  ChangeSolution(solution);
}