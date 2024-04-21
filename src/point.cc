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
double Point::Distance(const Point& other) const {
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
double Point::Distance(const std::vector<Point>& centroids) const {
  double min_distance = Distance(centroids[0]);
  for (int i = 1; i < (int)centroids.size(); i++) {
    double distance = Distance(centroids[i]);
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
std::string Point::ToString() const {
  std::string result;
  for (int i = 0; i < (int)coordinates_.size(); i++) {
    result += std::to_string(coordinates_[i]) + " ";
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