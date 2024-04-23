/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y análisis de algoritmos
 *
 * @author Esther M. Quintero
 * @date 20 Apr 2024
 * @brief Implementación de la clase Algorithm
 */

#include "algorithm.h"

/**
 * @brief Constructor de un algoritmo
 * @param[in] points Vector de puntos
 * @param[in] number_of_points Número de puntos
 */
Algorithm::Algorithm(std::vector<Point> points, int number_of_points) {
  points_ = points;
  number_of_points_ = number_of_points;
}

/**
 * @brief Getter del centro de gravedad de un vector de puntos
 * @param[in] points Vector de puntos
 * @return Centro de gravedad
 */
Point Algorithm::get_gravity_center(std::vector<Point> points) {
  int dimension = points[0].get_dimension();
  std::vector<double> gravity_center_point_coordinates(dimension, 0.0);
  for (auto point : points) {
    for (int i = 0; i < dimension; i++) {
      gravity_center_point_coordinates[i] += point.get_coordinates()[i];
    }
  }
  for (int i = 0; i < dimension; i++) {
    gravity_center_point_coordinates[i] /= points.size();
  }
  return Point(gravity_center_point_coordinates, -1);
}