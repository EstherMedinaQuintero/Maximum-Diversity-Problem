/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y análisis de algoritmos
 *
 * @author Esther M. Quintero
 * @date 20 Apr 2024
 * @brief Programa principal
 */

#include <iostream>
#include <chrono>
#include <fstream>
#include "greedy.h"
#include "local-search.h"
#include "utilities.h"

void print_solution(std::string algorithm, std::string input_file, int m);

/**
 * @brief Ejecuta el algoritmo seleccionado
 * @param[in] algorithm Algoritmo a ejecutar
 * @param[in] input_file Fichero de entrada
 */
void execute(std::string algorithm, std::string input_file) {
  srand(time(NULL));
  std::cout << PINK "Processing input file: " NC << input_file << std::endl;
  /// Probamos con varios m
  for (int m = 2; m <= 6; m++) {
    std::cout << BLUE "\n\t--> Processing " NC << "m = " << m << std::endl;
    print_solution(algorithm, input_file, m);
  }
}

/**
 * @brief Imprime la solución en consola y en un archivo CSV
 * @param[in] algorithm Algoritmo a ejecutar
 * @param[in] input_file Fichero de entrada
 * @param[in] m Número de puntos a seleccionar
 */
void print_solution(std::string algorithm, std::string input_file, int m) {
  std::ofstream output_file;
  std::string line;
  output_file.open("./results.csv", std::ios::app); 
  std::string labels = "Problema,n,K,m,z,S,CPU";
  Problem problem(input_file);
  std::vector<Point> points = problem.get_points();
  
  if (algorithm == "greedy") {
    Greedy greedy(points, m); 
    auto start = std::chrono::high_resolution_clock::now();
    greedy.solve();
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

    /// Resultados en archivo CSV
    line += input_file + "," + std::to_string(points.size()) + "," + std::to_string(points[0].get_dimension())
    + "," + std::to_string(m) + "," + std::to_string(greedy.get_solution().get_value()) + "," + greedy.get_solution().to_string()
    + "," + std::to_string(elapsed_seconds.count());
    
    /// Resulados en consola
    std::cout << BLUE "\t\t- Value: " NC << greedy.get_solution().get_value() << std::endl;
    std::cout << BLUE "\t\t- Vector: " NC << greedy.get_solution().to_string() << std::endl;
    std::cout << BLUE "\t\t- Time: " NC << elapsed_seconds.count() << " seconds" << std::endl;

  } else if (algorithm == "local-search") {
    LocalSearch local_search(points, m);
    auto start = std::chrono::high_resolution_clock::now();
    local_search.solve();
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

    /// Resultados en archivo CSV
    line += input_file + "," + std::to_string(points.size()) + "," + std::to_string(points[0].get_dimension())
    + "," + std::to_string(m) + "," + std::to_string(local_search.get_solution().get_value()) + "," + local_search.get_solution().to_string()
    + "," + std::to_string(elapsed_seconds.count());
    
    /// Resulados en consola
    std::cout << BLUE "\t\t- Value: " NC << local_search.get_solution().get_value() << std::endl;
    std::cout << BLUE "\t\t- Vector: " NC << local_search.get_solution().to_string() << std::endl;
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
  std::cout << PINK "\n------------------------- Greedy -------------------------\n" NC << std::endl;
  std::string algorithm = "greedy";
  std::string input_file = "./inputs/max_div_30_3.txt";
  execute(algorithm, input_file);
  std::cout << PINK "\n---------------------- Local Search ----------------------\n" NC << std::endl;
  algorithm = "local-search";
  input_file = "./inputs/max_div_30_3.txt";
  execute(algorithm, input_file);
  return 0;
}
