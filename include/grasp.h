/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y análisis de algoritmos
 *
 * @author Esther M. Quintero
 * @date 27 Apr 2024
 * @brief Cabecera de la clase Grasp
 */

#ifndef GRASP_H
#define GRASP_H

#include "algorithm.h"
#include "utilities.h"
#include "local-search.h"
#include <vector>

class Grasp: public Algorithm {
 private:
  int lrc_size_;
  int iterations_;

 public:
  Grasp(std::vector<Point> points, int number_of_points, int lrc_size, int iterations) : Algorithm(points, number_of_points), lrc_size_(lrc_size), iterations_(iterations) {}
  void solve();
  Solution constructive();
};

#endif