#include "problem.h"

/**
 * @brief Constructor de un problema
 * @param[in] name Nombre del fichero con el problema
 */
Problem::Problem(std::string name) {
  std::ifstream file(name);
  std::string line;
  std::getline(file, line);
  int number_of_points = std::stoi(line);
  number_of_points_ = number_of_points;
  std::getline(file, line);
  int dimension = std::stoi(line);
  int id = 0;
  while (std::getline(file, line)) {
    std::vector<double> coordinates(dimension);
    std::stringstream ss(line);
    for (int i = 0; i < dimension; i++) {
      ss >> coordinates[i];
    }
    points_.push_back(Point(coordinates, id));
    id++;
  }
}