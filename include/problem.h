/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y análisis de algoritmos
 *
 * @author Esther M. Quintero
 * @date 20 Apr 2024
 * @brief Cabecera de la clase Problem
 */

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
  int number_of_points_;

 public:
  /// Constructor y destructor
  Problem(std::string name);
  Problem() = default;

  /// Getters
  std::vector<Point>& get_points() { return points_; }
};

#endif // PROBLEM_H