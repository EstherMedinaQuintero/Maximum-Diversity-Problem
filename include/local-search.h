#ifndef LOCAL_SEARCH_H
#define LOCAL_SEARCH_H

#include "algorithm.h"

class LocalSearch: public Algorithm {
 private:
  Solution solution_;  // Solución actual
  int iterations_ = 1000;     // Número de iteraciones

 public:
  LocalSearch(std::vector<Point> points, int number_of_points): Algorithm(points, number_of_points) {}
  std::vector<std::pair<Solution, double>> GetNeighborhood(std::vector<Point>& points);
  void ChangeSolution(Solution solution) { solution_ = solution;}
  Solution Search(std::vector<Point>& points);
  void GetFirstSolution();
  void Solve() override;

};

#endif