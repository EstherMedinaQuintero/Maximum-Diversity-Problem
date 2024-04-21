#include "greedy.h"

/**
 * @brief Resuelve el problema greedy
 */
void Greedy::Solve() {
  std::vector<Point> solution_points;
  solution_points.reserve(number_of_points_);

  // Obtener el punto inicial más alejado del centro de gravedad de todos los puntos
  Point gravity_center_point = GetGravityCenterPoint(points_);
  auto max_iter = std::max_element(points_.begin(), points_.end(),
    [&gravity_center_point](const Point& a, const Point& b) {
      return gravity_center_point.Distance(a) < gravity_center_point.Distance(b);
    });

  solution_points.push_back(*max_iter);
  points_.erase(max_iter); // Elimina el punto más alejado de la lista de puntos

  // Repetir hasta que la cantidad de puntos en solution_points sea igual a number_of_points_
  while ((int)solution_points.size() < number_of_points_) {
    gravity_center_point = GetGravityCenterPoint(solution_points);
    max_iter = std::max_element(points_.begin(), points_.end(),
      [&gravity_center_point](const Point& a, const Point& b) {
        return gravity_center_point.Distance(a) < gravity_center_point.Distance(b);
      });
    solution_points.push_back(*max_iter);
    points_.erase(max_iter); // Elimina el punto más alejado de la lista de puntos
  }

  solution_points_ = Solution(solution_points);
}
