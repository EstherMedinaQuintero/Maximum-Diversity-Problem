/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y análisis de algoritmos
 *
 * @author Esther M. Quintero
 * @date 20 Apr 2024
 * @brief Cabecera de la clase TabuSearch
 */

#ifndef TABU_SEARCH_H
#define TABU_SEARCH_H

#include "algorithm.h"
#include "utilities.h"
#include "grasp.h"
#include <list>

class TabuSearch: public Algorithm {
 public:
  /// Constructor
  TabuSearch(std::vector<Point> points, int number_of_points): Algorithm(points, number_of_points) {}

  /// Sobrecarga del método virtual
  void solve() override;

  /// Métodos
  void update_tabu_list(std::list<Solution>& tabu_list, const Solution& solution, int tenure);
  Solution get_best_neighbor_not_in_tabu(const Solution& current_solution, const std::list<Solution>& tabu_list);
  bool is_in_tabu(const Solution& solution, const std::list<Solution>& tabu_list);
  Solution generate_initial_solution();
};

#endif // TABU_SEARCH_H