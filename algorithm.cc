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
Algorithm::Point GetGravityCenterPoint(std::vector<Point> points) {
  int dimension = points[0].GetDimension();
  std::vector<double> gravity_center_point_coordinates(dimension, 0.0);
  for (auto point : points) {
    for (int i = 0; i < dimension; i++) {
      gravity_center_point_coordinates[i] += point.GetCoordinates()[i];
    }
  }
  for (int i = 0; i < dimension; i++) {
    gravity_center_point_coordinates[i] /= points.size();
  }
  return Point(gravity_center_point_coordinates, -1);
}