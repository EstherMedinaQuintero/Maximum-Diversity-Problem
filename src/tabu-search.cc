/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y análisis de algoritmos
 *
 * @author Esther M. Quintero
 * @date 20 Apr 2024
 * @brief Implementación de la clase TabuSearch
 */

#include "tabu-search.h"
#include <set>
#include <algorithm>
#include <cmath>
#include <list>

void TabuSearch::solve() {
  int max_iterations = 1000;
  int num_iterations_no_improve = 0;
  int tabu_tenure = 20;
  std::list<Solution> tabu_list;

  // Inicialización de la solución
  solution_points_ = generate_initial_solution();
  Solution best_solution = solution_points_;

  for (int iter = 0; iter < max_iterations && num_iterations_no_improve < 100; ++iter) {
    Solution neighbor = get_best_neighbor_not_in_tabu(solution_points_, tabu_list);

    if (neighbor.get_value() > best_solution.get_value()) {
      best_solution = neighbor;
      num_iterations_no_improve = 0;
    } else {
      num_iterations_no_improve++;
    }

    // Actualizar la lista tabú
    update_tabu_list(tabu_list, neighbor, tabu_tenure);

    // Movimiento a la nueva solución
    solution_points_ = neighbor;
  }

  // Configuración de la mejor solución encontrada como la solución del algoritmo
  solution_points_ = best_solution;
}

void TabuSearch::update_tabu_list(std::list<Solution>& tabu_list, const Solution& solution, int tenure) {
  if ((int)tabu_list.size() >= tenure) {
    tabu_list.pop_front();
  }
  tabu_list.push_back(solution);
}

Solution TabuSearch::get_best_neighbor_not_in_tabu(const Solution& current_solution, const std::list<Solution>& tabu_list) {
  Solution best_neighbor;
  double best_value = -std::numeric_limits<double>::infinity();

  for (int i = 0; i < number_of_points_; ++i) {
    Solution neighbor = current_solution;
    std::vector<Point> points = neighbor.get_points();
    std::random_shuffle(points.begin(), points.end());
    neighbor = Solution(points);

    if (!is_in_tabu(neighbor, tabu_list) && neighbor.get_value() > best_value) {
      best_neighbor = neighbor;
      best_value = neighbor.get_value();
    }
  }

  return best_neighbor;
}

bool TabuSearch::is_in_tabu(const Solution& solution, const std::list<Solution>& tabu_list) {
  for (const auto& tabu_solution : tabu_list) {
    if (solution == tabu_solution) {
      return true;
    }
  }
  return false;
}

Solution TabuSearch::generate_initial_solution() {
  std::vector<Point> shuffled_points = points_;
  std::random_shuffle(shuffled_points.begin(), shuffled_points.end());
  shuffled_points.resize(number_of_points_); // Assuming we want a subset
  return Solution(shuffled_points);
}
