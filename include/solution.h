/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y análisis de algoritmos
 *
 * @author Esther M. Quintero
 * @date 20 Apr 2024
 * @brief Cabecera de la clase Solution
 */

#ifndef SOLUTION_H
#define SOLUTION_H

#include <fstream>
#include <string>
#include "point.h"

class Solution {
 private:
  std::vector<Point> solution_points_;

 public:
  /// Constructor y destructor
  Solution(std::vector<Point> point) : solution_points_(point) {}
  Solution() {}
  
  /// Getters
  inline std::vector<Point> get_points() { return solution_points_; }
  inline Point get_point(int pos) { return solution_points_[pos]; }
  double get_value();
  double get_new_value(int old_point, Point new_point);

  /// Setters
  inline void set_point(Point point, int pos) { solution_points_[pos] = point;}

  /// Métodos
  std::string to_string();

  /// Sobrecarga del ==
  bool operator==(const Solution& solution) const {
    return solution_points_ == solution.solution_points_;
  }
};

#endif // SOLUTION_H