/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y análisis de algoritmos
 *
 * @author Esther M. Quintero
 * @date 20 Apr 2024
 * @brief Implementación de la clase LocalSearch
 */

#include "local-search.h"

/**
 * @brief Resuelve el problema de búsqueda local
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

  // solution_points_ = Solution(solution_points);
  // // Mejora con local search (intercambios)
  // // Buscamos maximizar la suma de las distancias
  // double actual_value = solution_points_.get_value();
  // double old_value = actual_value; // Para comprobar si se ha mejorado
  // Solution actual_solution = solution_points_;

  // // Recorremos los puntos de la solución
  // for (int i = 0; i < number_of_points_; i++) {
  //   // Recorremos los puntos generales
  //   for (int j = 0; j < (int)points_.size(); j++) {
  //     // Hacemos swap
  //     Point temp = solution_points_.get_point(i);
  //     solution_points_.set_point(points_[j], i);
  //     points_.erase(points_.begin() + j);
  //     points_.push_back(temp);
  //     // Comprobamos que el swap se ha hecho
  //     if (solution_points_.get_value() > actual_value) {
  //       actual_value = solution_points_.get_value();
  //       actual_solution = solution_points_;
  //     } else {
  //       // Si no se ha mejorado, volvemos a la solución anterior
  //       solution_points_.set_point(temp, i);
  //       points_.pop_back();
  //       points_.push_back(points_[j]);
  //     }
  //   }
  // }

  // ------------------------- Cálculo de movimientos -----------------------------
  solution_points_ = Solution(solution_points);
  double actual_value = solution_points_.get_value();
  double old_value = actual_value;
  Solution actual_solution = solution_points_;

  // Recorremos los puntos de la solución
  for (int i = 0; i < number_of_points_; i++) {
    // Recorremos los puntos generales
    for (int j = 0; j < (int)points_.size(); j++) {
      // Calculamos el nuevo valor potencial con el punto j
      double new_value = solution_points_.get_new_value(i, points_[j]);
      // Si el nuevo valor es mejor, realizamos el swap
      if (new_value > actual_value) {
        Point temp = solution_points_.get_point(i);
        solution_points_.set_point(points_[j], i);
        points_[j] = temp;
        actual_value = new_value; // actualizamos el valor actual de la solución
        actual_solution = solution_points_;
      }
    }
  }
  solution_points_ = actual_solution;
  std::cout << YELLOW "\t\t- Porcentaje de mejora: " NC << (actual_value - old_value) / old_value * 100 << "%" << std::endl;
}

/**
 * @brief Resuelve el problema de búsqueda local
 */
void LocalSearch::silent_solve() {
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
