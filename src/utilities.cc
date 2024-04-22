/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y análisis de algoritmos
 *
 * @author Esther M. Quintero
 * @date 29 Mar 2024
 * @brief Funciones auxiliares
 */

#include "../include/utilities.h"

/**
 * @brief Muestra el manual de ayuda
 * @param program_name Nombre del programa
 */
void usage(const std::string& program_name) {
  std::cout << GREEN << "\n--> Sinopsis:" << NC << "\n";
  std::cout << "\t" << program_name << "\n";
  std::cout << GREEN << "\n--> Descripción:" << NC << "\n";
  std::cout << "\tEste programa soluciona el problema de maximum diversity," << "\n"
            << "\tbuscando maximizar la suma de las distancias de m puntos." << "\n\n"
            << GREEN "\tAlgoritmos implementados:" NC << "\n"
            << "\t\tGreedy" << "\n"
            << "\t\tBúsqueda local" << "\n";
  std::cout << std::endl;
}