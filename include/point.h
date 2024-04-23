/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y análisis de algoritmos
 *
 * @author Esther M. Quintero
 * @date 20 Apr 2024
 * @brief Cabecera de la clase Point
 */

#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <string>
#include <vector>

class Point {
 private:
  int id_;                           // Identificador del punto
  int dimension_;                    // Dimensión del punto
  std::vector<double> coordinates_;  // Coordenadas del punto

 public:
  /// Constructor y destructor
  Point(std::vector<double> coordinates, int id);
  Point() = default;
  
  /// Getters
  inline int get_dimension() const { return dimension_; }
  inline std::vector<double> get_coordinates() const { return coordinates_; }
  inline int get_id() const { return id_; }

  /// Métodos
  double distance_to(const Point& other) const;
  double distance_to(const std::vector<Point>& centroids) const;
  std::string to_string() const;

  /// Sobrecarga de operadores
  bool operator==(const Point& other) const;

};

#endif // POINT_H