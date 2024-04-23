/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y análisis de algoritmos
 *
 * @author Esther M. Quintero
 * @date 20 Apr 2024
 * @brief Implementación de la clase Problem
 */

#include "problem.h"

/**
 * @brief Constructor de un problema
 * @param[in] name Nombre del fichero con el problema
 */
Problem::Problem(std::string name) {
  std::ifstream file_input(name);
  std::string line;
  std::getline(file_input, line);
  int number_of_points = std::stoi(line);
  number_of_points_ = number_of_points;
  std::getline(file_input, line);
  int dimension = std::stoi(line);
  int id = 0;
  while (std::getline(file_input, line)) {
    std::vector<double> coordinates(dimension);
    std::stringstream ss(line);
    for (int i = 0; i < dimension; i++) {
      ss >> coordinates[i];
    }
    points_.push_back(Point(coordinates, id));
    id++;
  }
}