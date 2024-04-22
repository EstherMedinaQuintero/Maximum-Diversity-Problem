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
  std::cout << "Solución inicial: ";
  std::cout << solution_points_.to_string() << std::endl;
  std::cout << "Valor de la solución inicial: ";
  std::cout << solution_points_.get_value() << std::endl;
  std::cout << "Puntos sin usar: ";
  for (int i = 0; i < (int)points_.size(); i++) {
    std::cout << points_[i].get_id() << " ";
  }
  std::cout << std::endl;

  // Mejora con local search (intercambios)
  // Buscamos maximizar la suma de las distancias
  double actual_value = solution_points_.get_value();
  Solution actual_solution = solution_points_;

  // Recorremos los puntos de la solución
  for (int i = 0; i < number_of_points_; i++) {
    std::cout << "--> Cambiando el punto " << solution_points_.get_point(i).get_id() << " de la solución\n";
    // Recorremos los puntos generales
    for (int j = 0; j < (int)points_.size(); j++) {
      std::cout << "\t - Probando con el punto " << points_[j].get_id() << "\n";
      // Hacemos swap
      Point temp = solution_points_.get_point(i);
      solution_points_.set_point(points_[j], i);
      points_.erase(points_.begin() + j);
      points_.push_back(temp);
      // Comprobamos que el swap se ha hecho
      std::cout << "\t\t - Solución actual: " << solution_points_.to_string() << "\n";
      std::cout << "\t\t - Valor de la solución actual: " << solution_points_.get_value() << "\n";
      // if (solution_points_.get_value() > actual_value) {
      //   actual_value = solution_points_.get_value();
      //   actual_solution = solution_points_;
      //   std::cout << "\t\t - Mejora encontrada\n";
      // } else {
      //   // Si no se ha mejorado, volvemos a la solución anterior
        solution_points_.set_point(temp, i);
        points_.pop_back();
        points_.push_back(points_[j]);
      //   std::cout << "\t\t - No se ha mejorado\n";
      // }
    }
  }
  solution_points_ = actual_solution;
}
