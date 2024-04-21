#include "solution.h"

/**
 * @brief Calcula la función objetivo
 * @return Suma de todas las distancias
 */
double Solution::Value() {
  double value = 0;
  for (int i = 0; i < (int)solution_points_.size(); i++) {
    for (int j = i + 1; j < (int)solution_points_.size(); j++) {
      value += solution_points_[i].Distance(solution_points_[j]);
    }
  }
  return value;
}

/**
 * @brief Conversión a string de la solución
 * @return Una string de los atributos de la solución
 */
std::string Solution::ToString() {
  std::string solution_string = "";
  for (int i = 0; i < (int)solution_points_.size(); i++) {
    solution_string += std::to_string(solution_points_[i].GetId());
    if (i != (int)solution_points_.size() - 1) {
      solution_string += " ";
    }
  }
  return solution_string;
}