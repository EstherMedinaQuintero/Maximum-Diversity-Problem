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
  int GetDimension() const { return dimension_; }
  std::vector<double> GetCoordinates() const { return coordinates_; }
  int GetId() const { return id_; }

  /// Métodos
  double Distance(const Point& other) const;
  double Distance(const std::vector<Point>& centroids) const;
  std::string ToString() const;

  /// Sobrecarga de operadores
  bool operator==(const Point& other) const;

};

#endif