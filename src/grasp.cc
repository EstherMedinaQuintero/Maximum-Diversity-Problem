#include "grasp.h"

Solution Grasp::constructive() {
  // First, we calculate the gravity center point of the points and add the farthest point to the solution
  Point gravity_center_point = get_gravity_center(points_);
  std::vector<Point> solution_points;
  double max_distance = -9999999999;
  int max_distance_point_index = -1;
  for (int i = 0; i < (int)points_.size(); ++i) {
    double distance = gravity_center_point.distance_to(points_[i]);
    if (distance > max_distance) {
      max_distance = distance;
      max_distance_point_index = i;
    }
  }
  solution_points.push_back(points_[max_distance_point_index]);

  max_distance = -9999999999;
  max_distance_point_index = -1;
  for (int i = 1; i < number_of_points_; ++i) {
    std::vector<Point> lrc(lrc_size_);
    gravity_center_point = get_gravity_center(solution_points);
    for (int j = 0; j < (int)points_.size(); ++j) {
      if (std::find(solution_points.begin(), solution_points.end(), points_[j]) == solution_points.end()) {
        double distance = gravity_center_point.distance_to(points_[j]);
        for (int k = 0; k < (int)lrc.size(); ++k) {
          if (distance > lrc[k].distance_to(gravity_center_point)) {
            lrc.insert(lrc.begin() + k, points_[j]);
            if ((int)lrc.size() > lrc_size_) {
              lrc.pop_back();
            }
            break;
          }
        }
      }
    }
    int rand_index = rand() % lrc.size();
    while (lrc[rand_index].get_dimension() == 0) {
      rand_index = rand() % lrc.size();
    }
    solution_points.push_back(lrc[rand_index]);
  }
  return Solution(solution_points);
}

std::vector<std::pair<Solution, double>> Grasp::local_search(Solution& solution, const std::vector<Point>& points) {
  std::vector<std::pair<Solution, double>> neighborhood;
  double current_value = solution.get_value();
  for (int i = 0; i < (int)solution.get_points().size(); ++i) {
    for (int j = 0; j < (int)points.size(); ++j) {
      if (!std::any_of(solution.get_points().begin(), solution.get_points().end(), [&](const Point& p) { return p.get_id() == points[j].get_id(); })) {
        std::vector<Point> new_solution_points = solution.get_points();
        new_solution_points[i] = points[j];
        double new_value = current_value - solution.get_points()[i].distance_to(points[i]) + points[i].distance_to(points[j]);
        neighborhood.push_back({Solution(new_solution_points), new_value});
      }
    }
  }
  return neighborhood;
}

void Grasp::solve() {
  Solution current_solution = constructive();
  int iterations = 0;
  Solution best_solution = current_solution;
  double old_value = current_solution.get_value();
  double best_value = current_solution.get_value();
  double current_value = current_solution.get_value();
  do {
    current_solution = best_solution;
    current_value = current_solution.get_value();
    LocalSearch local_search(points_, number_of_points_);
    local_search.silent_solve();
    if (local_search.get_solution().get_value() > best_value) {
      best_solution = local_search.get_solution();
      best_value = local_search.get_solution().get_value();
    }
    iterations++;
  } while (best_value > current_value && iterations < iterations_);
  solution_points_ = best_solution;
  double actual_value = best_solution.get_value();
  std::cout << YELLOW "\t\t- Porcentaje de mejora: " NC << (actual_value - old_value) / old_value * 100 << "%" << std::endl;
}