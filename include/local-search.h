/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y análisis de algoritmos
 *
 * @author Esther M. Quintero
 * @date 20 Apr 2024
 * @brief Cabecera de la clase LocalSearch
 */

#ifndef LOCAL_SEARCH_H
#define LOCAL_SEARCH_H

#include "algorithm.h"
#include "utilities.h"

class LocalSearch: public Algorithm {
 public:
  /// Constructor
  LocalSearch(std::vector<Point> points, int number_of_points): Algorithm(points, number_of_points) {}

  /// Sobrecarga del método virtual
  void solve() override;
  void silent_solve();
};

#endif // LOCAL_SEARCH_H