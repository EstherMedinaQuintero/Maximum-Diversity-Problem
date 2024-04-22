#include "local-search.h"

/**
 * @brief Resuelve el problema greedy
 */
void LocalSearch::solve() {
  std::vector<Point> solution_points;
  solution_points.reserve(number_of_points_);

  // Obtener el punto inicial más alejado del centro de gravedad de todos los puntos
  Point gravity_center_point = get_gravity_center(points_);
  auto max_iter = std::max_element(points_.begin(), points_.end(),
    [&gravity_center_point](const Point& a, const Point& b) {
      return gravity_center_point.distance_to(a) < gravity_center_point.distance_to(b);
    });

  solution_points.push_back(*max_iter);
  points_.erase(max_iter); // Elimina el punto más alejado de la lista de puntos

  // Repetir hasta que la cantidad de puntos en solution_points sea igual a number_of_points_
  while ((int)solution_points.size() < number_of_points_) {
    gravity_center_point = get_gravity_center(solution_points);
    max_iter = std::max_element(points_.begin(), points_.end(),
      [&gravity_center_point](const Point& a, const Point& b) {
        return gravity_center_point.distance_to(a) < gravity_center_point.distance_to(b);
      });
    solution_points.push_back(*max_iter);
    points_.erase(max_iter); // Elimina el punto más alejado de la lista de puntos
  }

  solution_points_ = Solution(solution_points);
  // Mejora con local search (intercambios)
  // Buscamos maximizar la suma de las distancias
  double actual_value = solution_points_.get_value();
  Solution actual_solution = solution_points_;

  // Recorremos los puntos de la solución
  for (int i = 0; i < number_of_points_; i++) {
    // Recorremos los puntos generales
    for (int j = 0; j < (int)points_.size(); j++) {
      // Hacemos swap
      Point temp = solution_points_.get_point(i);
      solution_points_.set_point(points_[j], i);
      points_.erase(points_.begin() + j);
      points_.push_back(temp);
      // Comprobamos que el swap se ha hecho
      if (solution_points_.get_value() > actual_value) {
        actual_value = solution_points_.get_value();
        actual_solution = solution_points_;
      } else {
        // Si no se ha mejorado, volvemos a la solución anterior
        solution_points_.set_point(temp, i);
        points_.pop_back();
        points_.push_back(points_[j]);
      }
    }
  }
  solution_points_ = actual_solution;
}
