/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y análisis de algoritmos
 *
 * @author Esther M. Quintero
 * @date 20 Apr 2024
 * @brief Cabecera de la clase Greedy
 */

#ifndef GREEDY_H
#define GREEDY_H

#include "algorithm.h"

class Greedy: public Algorithm {
 public:
  /// Constructor
  Greedy(std::vector<Point> points, int number_of_points): Algorithm(points, number_of_points) {}

  /// Sobrecarga del método virtual
  void solve() override;
};

#endif // GREEDY_H