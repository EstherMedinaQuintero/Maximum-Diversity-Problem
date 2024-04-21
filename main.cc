#include <iostream>
#include <chrono>
#include <fstream>
#include "greedy.h"

void printSolution(std::string algorithm, std::string input_file, int m);

void execute() {
  srand(time(NULL));
  std::string algorithm; 
  std::cout << "Algorithm: ";
  std::cin >> algorithm;
  
  std::string input_file;
  std::cout << "Input file: ";
  std::cin >> input_file;
  std::cout << "Processing input file: " << input_file << std::endl;
  
  /// Probamos con varios m
  for (int m = 2; m <= 5; m++) {
    std::cout << "Processing m = " << m << std::endl;
    printSolution(algorithm, input_file, m);
  }
}

void printSolution(std::string algorithm, std::string input_file, int m) {
  std::ofstream output_file;
  std::string line;
  output_file.open("./results.csv", std::ios::app); 
  std::string labels = "Problema,n,K,m,z,S,CPU";
  Problem problem(input_file);
  std::vector<Point> points = problem.GetPoints();
  
  if (algorithm == "greedy") {
    Greedy greedyMDP(points, m); 
    auto start = std::chrono::high_resolution_clock::now();
    greedyMDP.Solve();
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(end - start)

    /// Resultados en archivo CSV
    line += input_file + "," + std::to_string(points.size()) + "," + std::to_string(points[0].GetDimension())
    + "," + std::to_string(m) + "," + std::to_string(greedyMDP.GetSolution().Value()) + "," + greedyMDP.GetSolution().ToString()
    + "," + std::to_string(elapsed_seconds.count());
    
    /// Resulados en consola
    std::cout << "Value: " << greedyMDP.GetSolution().Value() << std::endl;
    std::cout << "Vector: " << greedyMDP.GetSolution().ToString() << std::endl;
    std::cout << "Time: " << elapsed_seconds.count() << " seconds" << std::endl;
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
  execute(); 
  return 0;
}