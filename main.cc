#include <iostream>
#include <chrono>
#include <fstream>
#include "greedy.h"
#include "local-search.h"
#include "utilities.h"

void print_solution(std::string algorithm, std::string input_file, int m);

void execute(std::string algorithm, std::string input_file) {
  srand(time(NULL));
  std::cout << PINK "Processing input file: " NC << input_file << std::endl;
  /// Probamos con varios m
  for (int m = 3; m <= 6; m++) {
    std::cout << BLUE "\n\t--> Processing " NC << "m = " << m << std::endl;
    print_solution(algorithm, input_file, m);
  }
}

void print_solution(std::string algorithm, std::string input_file, int m) {
  std::ofstream output_file;
  std::string line;
  output_file.open("./results.csv", std::ios::app); 
  std::string labels = "Problema,n,K,m,z,S,CPU";
  Problem problem(input_file);
  std::vector<Point> points = problem.get_points();
  
  if (algorithm == "greedy") {
    Greedy greedyMDP(points, m); 
    auto start = std::chrono::high_resolution_clock::now();
    greedyMDP.solve();
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

    /// Resultados en archivo CSV
    line += input_file + "," + std::to_string(points.size()) + "," + std::to_string(points[0].get_dimension())
    + "," + std::to_string(m) + "," + std::to_string(greedyMDP.get_solution().get_value()) + "," + greedyMDP.get_solution().to_string()
    + "," + std::to_string(elapsed_seconds.count());
    
    /// Resulados en consola
    std::cout << BLUE "\t\t- Value: " NC << greedyMDP.get_solution().get_value() << std::endl;
    std::cout << BLUE "\t\t- Vector: " NC << greedyMDP.get_solution().to_string() << std::endl;
    std::cout << BLUE "\t\t- Time: " NC << elapsed_seconds.count() << " seconds" << std::endl;

  } else if (algorithm == "local-search") {
    LocalSearch localSearch(points, m);
    auto start = std::chrono::high_resolution_clock::now();
    localSearch.solve();
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

    /// Resultados en archivo CSV
    line += input_file + "," + std::to_string(points.size()) + "," + std::to_string(points[0].get_dimension())
    + "," + std::to_string(m) + "," + std::to_string(localSearch.get_solution().get_value()) + "," + localSearch.get_solution().to_string()
    + "," + std::to_string(elapsed_seconds.count());
    
    /// Resulados en consola
    std::cout << BLUE "\t\t- Value: " NC << localSearch.get_solution().get_value() << std::endl;
    std::cout << BLUE "\t\t- Vector: " NC << localSearch.get_solution().to_string() << std::endl;
    std::cout << BLUE "\t\t- Time: " NC << elapsed_seconds.count() << " seconds" << std::endl;
    
  } else if (algorithm == "grasp") {
    std::cout << "GRASP no está implementado aún" << std::endl;
  } else if (algorithm == "poda") {
    std::cout << "Branch no está implementado aún" << std::endl;
  }
  output_file << labels << std::endl;
  output_file << line << std::endl;
  output_file.close();
}

int main() {
  std::string algorithm = "local-search";
  std::string input_file = "./inputs/max_div_15_2.txt";
  execute(algorithm, input_file);
  return 0;
}
