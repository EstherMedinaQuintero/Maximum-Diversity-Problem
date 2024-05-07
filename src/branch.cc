#include "branch.h"
#include <algorithm>

/**
 * @brief Constructor de la clase Ramificacion
 * @param points puntos del problema
 * @param number_of_iterations número de iteraciones
 * @param number_of_points número de puntos a seleccionar
 */
BranchSearch::BranchSearch(std::vector<Point> points, int number_of_points, std::string search_strategy, std::string initial_solution_strategy):
  Algorithm(points, number_of_points), search_strategy_(search_strategy) {
  // Cálculo de la distancia máxima entre puntos
  for (auto point : points_) {
    for (auto point2 : points_) {
      if (point.distance_to(point2) > highest_distance_) {
        highest_distance_ = point.distance_to(point2);
      }
    }
  }
  // Inicialización de la solución según la estrategia elegida
  if (initial_solution_strategy == "greedy") {
    Greedy greedy(points_, number_of_points_);
    greedy.solve();
    initial_solution_ = greedy.get_solution();
  } else if (initial_solution_strategy == "grasp") {
    Grasp grasp(points_, number_of_points_, 3, 20);
    grasp.solve();
    initial_solution_ = grasp.get_solution();
  }
}

/**
 * @brief Resuelve el problema de ramificación y poda
 */
void BranchSearch::solve() {
  if (search_strategy_ == "deep") {
    deep_solve();
  } else {
    high_value_solve();
  }
}

// Estructura de un nodo
struct Node {
  Solution solution;
  double upper_bound;
  bool operator<(Node& other) {
    return upper_bound < other.upper_bound;
  }
};

/**
 * @brief Imprime la solución de un nodo
 * @param node Nodo a imprimir
 */
void PrintNodeSolution(Node node) {
  std::cout << "Solution: ";
  for (auto point : node.solution.get_points()) {
    std::cout << point.get_id() << " ";
  }
  std::cout << "Upper bound: " << node.upper_bound << std::endl;
}

/**
 * @brief Devuelve el valor de una solución
 * @param node_solution Solución a evaluar
 * @return Valor de la solución
 */
double BranchSearch::get_node_solution_value(Solution node_solution) {
  // Calcula el valor de la solución sumando distancias
  int number_of_points = node_solution.get_points().size();
  std::vector<Point> solution_points = node_solution.get_points();
  int point_dimension = solution_points[0].get_dimension();
  // introduce puntos con id -1 en la solucion hasta que tenga el mismo numero de nodos que el problema
  while (number_of_points < number_of_points_) {
    std::vector<double> coordinates;
    for (int i = 0; i < point_dimension; i++) {
    coordinates.push_back(-1);
    }
    Point point(coordinates, -1);
    solution_points.push_back(point);
    number_of_points++;
  }
  
  double value = 0;
  // The value is the sum of the distances between all the points of the solution
  for (int i = 0; i < (int)solution_points.size(); i++) {
    for (int j = i + 1; j < (int)solution_points.size(); j++) {
      if (solution_points[i].get_id() != -1 && solution_points[j].get_id() != -1) {
        value += solution_points[i].distance_to(solution_points[j]);
      } else {
        value += highest_distance_;
      }
    }
  }
  return value;
}

/**
 * @brief Resuelve el problema usando la estrategia de ramificación con cota superior
 * @details Las cotas superiores se calculan sumando las distancias entre los puntos seleccionados, 
 *          incluyendo el peor caso (distancia máxima) para puntos no seleccionados aún. 
 */
void BranchSearch::high_value_solve() {
  std::vector<Node> nodes;
  int number_of_points = initial_solution_.get_points().size();
  double best_solution_value_ = get_node_solution_value(initial_solution_);
  Solution best_solution_ = initial_solution_;

  for (int i = 0; i < (int)points_.size(); i++) {
    std::vector<Point> points;
    points.push_back(points_[i]);
    Solution solution(points);
    Node node;
    node.solution = solution;
    node.upper_bound = get_node_solution_value(solution);
    nodes.push_back(node);
    ++nodes_generated_;
  }

  while (!nodes.empty()) {
    // Sort the nodes by upper bound
    std::sort(nodes.begin(), nodes.end());

    // Expandir el nodo con mayor cota superior
    Node node = nodes.back();
    nodes.pop_back();
    std::vector<Point> node_points = node.solution.get_points();
    int node_id = node_points.back().get_id();

    if ((int)node_points.size() < number_of_points) {
      for (int i = node_id + 1; i < (int)points_.size(); i++) {
        std::vector<Point> new_node_points = node_points;
        new_node_points.push_back(points_[i]);
        Solution new_node_solution(new_node_points);
        Node new_node;
        new_node.solution = new_node_solution;
        new_node.upper_bound = get_node_solution_value(new_node_solution);
        nodes.push_back(new_node);
        ++nodes_generated_;
      }
    } else {
      if (get_node_solution_value(node.solution) > best_solution_value_) {
        best_solution_value_ = get_node_solution_value(node.solution);
        best_solution_ = node.solution;
      }
    }
    // Podar nodos cuya cota superior no mejora la mejor solución actual
    for (int nodo = 0; nodo < (int)nodes.size(); nodo++) {
      if ((int)nodes[nodo].solution.get_points().size() == number_of_points) {
        if (nodes[nodo].upper_bound < best_solution_value_) {
          nodes.erase(nodes.begin() + nodo);
          --nodo;
        }
      }
    }
  
  }
  solution_points_ = best_solution_;
}

/**
 * @brief Resuelve el problema usando la estrategia de ramificación en profundidad
 */
void BranchSearch::deep_solve() {
  std::vector<Node> nodes;
  int number_of_points = initial_solution_.get_points().size();
  double best_solution_value_ = get_node_solution_value(initial_solution_);
  Solution best_solution_ = initial_solution_;

  for (int i = 0; i < (int)points_.size(); i++) {
    std::vector<Point> points;
    points.push_back(points_[i]);
    Solution solution(points);
    Node node;
    node.solution = solution;
    node.upper_bound = get_node_solution_value(solution);
    nodes.push_back(node);
    ++nodes_generated_;
  }

  while (!nodes.empty()) {

    // Expandir el nodo con mayor cota superior
    Node node = nodes.back();
    nodes.pop_back();
    std::vector<Point> node_points = node.solution.get_points();
    int node_id = node_points.back().get_id();

    if ((int)node_points.size() < number_of_points) {
      for (int i = node_id + 1; i < (int)points_.size(); i++) {
        std::vector<Point> new_node_points = node_points;
        new_node_points.push_back(points_[i]);
        Solution new_node_solution(new_node_points);
        Node new_node;
        new_node.solution = new_node_solution;
        new_node.upper_bound = get_node_solution_value(new_node_solution);
        nodes.push_back(new_node);
        ++nodes_generated_;
      }
    } else {
      if (get_node_solution_value(node.solution) > best_solution_value_) {
        best_solution_value_ = get_node_solution_value(node.solution);
        best_solution_ = node.solution;
      }
    }

    for (int nodo = 0; nodo < (int)nodes.size(); nodo++) {
      if ((int)nodes[nodo].solution.get_points().size() == number_of_points) {
        if (nodes[nodo].upper_bound < best_solution_value_) {
          nodes.erase(nodes.begin() + nodo);
          --nodo;
        }
      }
    }
  
  }
  solution_points_ = best_solution_;
}