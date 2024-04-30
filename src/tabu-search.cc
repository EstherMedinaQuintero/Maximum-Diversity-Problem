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


/**
 * @brief Resuelve el problema de búsqueda tabú
 * @note Añadir multiarranque (y nos quedamos con la mejor)
 */
void TabuSearch::solve() {
  int max_iterations = 1000;
  int num_iterations_no_improve = 0;
  int tabu_tenure = 5; // Tamaño de la lista tabú
  std::list<Solution> tabu_list;
  // Inicialización de la solución (añadir multiarranque)
  solution_points_ = generate_initial_solution(); // Greedy --> Cambiar a GRASP (hecho)
  Solution best_solution = solution_points_;
  double old_value = solution_points_.get_value();
  // Búsqueda de la mejor solución
  for (int iter = 0; iter < max_iterations; ++iter) {
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
  double actual_value = solution_points_.get_value();
  std::cout << YELLOW "\t\t- Porcentaje de mejora: " NC << (actual_value - old_value) / old_value * 100 << "%" << std::endl;
}

/**
 * @brief Actualiza la lista tabú
 * @param tabu_list Lista tabú
 * @param solution Solución a añadir a la lista tabú
 * @param tenure Tamaño de la lista tabú
 */
void TabuSearch::update_tabu_list(std::list<Solution>& tabu_list, const Solution& solution, int tenure) {
  if ((int)tabu_list.size() >= tenure) tabu_list.pop_front();
  tabu_list.push_back(solution);
}

/**
 * @brief Obtiene el mejor vecino que no está en la lista tabú
 * @param current_solution Solución actual
 * @param tabu_list Lista tabú
 * @return Mejor vecino
 */
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

/**
 * @brief Comprueba si una solución está en la lista tabú
 * @param solution Solución a comprobar
 * @param tabu_list Lista tabú
 * @return true si la solución está en la lista tabú, false en caso contrario
 */
bool TabuSearch::is_in_tabu(const Solution& solution, const std::list<Solution>& tabu_list) {
  for (const auto& tabu_solution : tabu_list) {
    if (solution == tabu_solution) {
      return true;
    }
  }
  return false;
}

/**
 * @brief Genera una solución inicial
 * @note Cambiar a GRASP
 * @return Solución inicial
 */
Solution TabuSearch::generate_initial_solution() {
  /// Generar con grasp
  Grasp grasp(points_, number_of_points_, 3, 100);
  grasp.solve();
  return grasp.get_solution();
  // std::vector<Point> shuffled_points = points_;
  // std::random_shuffle(shuffled_points.begin(), shuffled_points.end());
  // shuffled_points.resize(number_of_points_);
  // return Solution(shuffled_points);
}
