#include <algorithm>
#include <vector>
#include <numeric>

#include "local-search.h"

/**
 * @brief Resuelve el problema con búsqueda local
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

  std::cout << "Solución inicial: ";
  for (auto point : solution_points) {
    std::cout << point.GetId() << " ";
  }
  std::cout << std::endl;

  std::cout << "Valor de la solución inicial: ";
  Solution first_solution = Solution(solution_points);
  std::cout << first_solution.Value() << std::endl;
  
  // Búsqueda local de intercambio para mejorar la solución inicial
  // Recorremos los puntos de la solución actual
  for (int i = 0; i < number_of_points_; i++) {
    // Recorremos los puntos restantes
    for (int j = 0; j < (int)points_.size(); j++) {
      // Intercambiamos los puntos
      std::swap(solution_points[i], points_[j]);
      // Calculamos el valor de la nueva solución
      Solution new_solution = Solution(solution_points);
      double new_value = new_solution.Value();
      // Si la nueva solución es mejor que la anterior, la actualizamos
      Solution old_solution = Solution(points_);
      double old_value = old_solution.Value();
      if (new_value < old_value) {
        // std::cout << "Mejora: " << old_value << " -> " << new_value << std::endl;
        solution_points_ = Solution(solution_points);
      } else {
        // Si no, volvemos a intercambiar los puntos
        std::swap(solution_points[i], points_[j]);
      }
    }
  }
  
  solution_points_ = Solution(solution_points);
}