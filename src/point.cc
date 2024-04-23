/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y análisis de algoritmos
 *
 * @author Esther M. Quintero
 * @date 20 Apr 2024
 * @brief Implementación de la clase Point
 */

#include "point.h"

#include <cmath>
#include <iostream>

/**
 * @brief Constructor de un punto
 * @param[in] coordinates Coordenadas del punto
 * @param[in] id Identificador del punto
 */
Point::Point(std::vector<double> coordinates, int id) {
  id_ = id;
  coordinates_ = coordinates;
  dimension_ = coordinates_.size();
}

/**
 * @brief Calcula la distancia entre dos puntos
 * @param[in] other El otro punto
 * @return Distancia entre los dos puntos
 */
double Point::distance_to(const Point& other) const {
  double sum = 0;
  for (int i = 0; i < dimension_; i++) {
    sum += pow(coordinates_[i] - other.coordinates_[i], 2);
  }
  return sqrt(sum);
}

/**
 * @brief Calcula la distancia entre un punto y un vector de puntos
 * @param[in] centroids Vector de puntos
 * @return Distancia entre un punto y un vector de puntos
 */
double Point::distance_to(const std::vector<Point>& centroids) const {
  double min_distance = distance_to(centroids[0]);
  for (int point = 1; point < (int)centroids.size(); point++) {
    double distance = distance_to(centroids[point]);
    if (distance < min_distance) {
      min_distance = distance;
    }
  }
  return min_distance;
}

/**
 * @brief Conversión a string del punto
 * @return Una string de los atributos del punto
 */
std::string Point::to_string() const {
  std::string result;
  for (int point = 0; point < (int)coordinates_.size(); point++) {
    result += std::to_string(coordinates_[point]) + " ";
  }
  result.pop_back();
  return result;
}

/**
 * @brief Sobrecarga del operador ==
 * @param[in] other El otro punto con el que comparar
 * @return True si son iguales, false si no
 */
bool Point::operator==(const Point& other) const {
  if (dimension_ == other.dimension_ && id_ == other.id_) {
    return true;
  }
  return false;
}