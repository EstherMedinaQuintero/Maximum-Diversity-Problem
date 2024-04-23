/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y análisis de algoritmos
 *
 * @author Esther M. Quintero
 * @date 20 Apr 2024
 * @brief Implementación de la clase Greedy
 */

#include "greedy.h"

/**
 * @brief Resuelve el problema greedy
 */
void Greedy::solve() {
  std::vector<Point> solution_points;
  solution_points.reserve(number_of_points_);

  // Obtener el punto inicial más alejado del centro de gravedad de todos los puntos
  Point gravity_center_point = get_gravity_center(points_);
  auto max_iter = std::max_element(points_.begin(), points_.end(),
    [&gravity_center_point](const Point& first, const Point& second) {
      return gravity_center_point.distance_to(first) < gravity_center_point.distance_to(second);
    });

  solution_points.push_back(*max_iter);
  points_.erase(max_iter); // Elimina el punto más alejado de la lista de puntos

  // Repetir hasta que la cantidad de puntos en solution_points sea igual a number_of_points_
  while ((int)solution_points.size() < number_of_points_) {
    gravity_center_point = get_gravity_center(solution_points);
    max_iter = std::max_element(points_.begin(), points_.end(),
      [&gravity_center_point](const Point& first, const Point& second) {
        return gravity_center_point.distance_to(first) < gravity_center_point.distance_to(second);
      });
    solution_points.push_back(*max_iter);
    points_.erase(max_iter); // Elimina el punto más alejado de la lista de puntos
  }

  solution_points_ = Solution(solution_points);
}
