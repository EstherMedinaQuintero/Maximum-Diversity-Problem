/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y análisis de algoritmos
 *
 * @author Esther M. Quintero
 * @date 20 Apr 2024
 * @brief Implementación de la clase Solution
 */

#include "solution.h"

/**
 * @brief Calcula la función objetivo
 * @return Suma de todas las distancias
 */
double Solution::get_value() {
  double value = 0;
  for (int i = 0; i < (int)solution_points_.size(); i++) {
    for (int j = i + 1; j < (int)solution_points_.size(); j++) {
      value += solution_points_[i].distance_to(solution_points_[j]);
    }
  }
  return value;
}

/**
 * @brief Calcula la función objetivo
 * @return Suma de todas las distancias
 */
double Solution::get_new_value(int old_point, Point new_point) {
  // Evaluamos el movimiento de retirar old_point y añadir new_point
  double value = get_value();
  // Restamos las distancias de old_point
  for (int i = 0; i < (int)solution_points_.size(); i++) {
    if (i != old_point) {
      value -= solution_points_[i].distance_to(solution_points_[old_point]);
    }
  }
  // Añadimos las distancias de new_point
  for (int i = 0; i < (int)solution_points_.size(); i++) {
    if (i != old_point) {
      value += new_point.distance_to(solution_points_[i]);
    }
  }
  return value;
}

/**
 * @brief Conversión a string de la solución
 * @return Una string de los atributos de la solución
 */
std::string Solution::to_string() {
  std::string solution_string = "";
  for (int i = 0; i < (int)solution_points_.size(); i++) {
    solution_string += std::to_string(solution_points_[i].get_id());
    if (i != (int)solution_points_.size() - 1) {
      solution_string += " ";
    }
  }
  return solution_string;
}