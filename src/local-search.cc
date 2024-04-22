#include "local-search.h"

/**
 * @brief Resuelve el problema greedy
 */
void LocalSearch::Solve() {
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
  std::cout << "Solución inicial: ";
  std::cout << solution_points_.ToString() << std::endl;
  std::cout << "Valor de la solución inicial: ";
  std::cout << solution_points_.Value() << std::endl;
  std::cout << "Puntos sin usar: ";
  for (int i = 0; i < (int)points_.size(); i++) {
    std::cout << points_[i].GetId() << " ";
  }
  std::cout << std::endl;

  // Mejora con local search (intercambios)
  // Buscamos maximizar la suma de las distancias
  double best_value = solution_points_.Value();

  // Recorremos los puntos de la solución
  for (int i = 0; i < number_of_points_; i++) {
    std::cout << "--> Cambiando el punto " << solution_points_[i].GetId() << " de la solución\n";
    // Recorremos los puntos generales
    for (int j = 0; j < (int)points_.size(); j++) {
      std::cout << "\t - Probando con el punto " << points_[j].GetId() << "\n";
    }
  }

}
