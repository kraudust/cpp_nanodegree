#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
    // Convert inputs to percentage:
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

    start_node = &(m_Model.FindClosestNode(start_x, start_y));
    end_node = &(m_Model.FindClosestNode(end_x, end_y));
}

float RoutePlanner::CalculateHValue(RouteModel::Node const* node) {
  return node->distance(*end_node);
}

void RoutePlanner::AddNeighbors(RouteModel::Node* current_node) {
  current_node->FindNeighbors();
  for (RouteModel::Node* p_node: current_node->neighbors){
    p_node->h_value = CalculateHValue(p_node);
    p_node->g_value = current_node->g_value + p_node->distance(*current_node);
    p_node->parent = current_node;
    p_node->visited = true;
    open_list.push_back(p_node);
  }
}

RouteModel::Node* RoutePlanner::NextNode() {
  // Sort list by f value which is g value + h value
  // Use lambda function with std::sort to sort the list
  std::sort(open_list.begin(), open_list.end(),
            [](RouteModel::Node* node1, RouteModel::Node* node2)
            {return node1->g_value + node1->h_value > node2->g_value + node2->h_value;});

  // Grab a pointer to the node with the lowest f value then remove that node from open list
  RouteModel::Node* next_node = open_list.back();
  open_list.pop_back();

  return next_node;
}

std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node* current_node) {
    // Create path_found vector
    distance = 0.0f;
    std::vector<RouteModel::Node> path_found;
    while (current_node != start_node){
      path_found.push_back(*current_node);
      distance += current_node->distance(*(current_node->parent));
      current_node = current_node->parent;
    }
    // Add the start node
    path_found.push_back(*(start_node));
    // Reverse order of vector so it is start to end order
    std::reverse(path_found.begin(), path_found.end());

    distance *= m_Model.MetricScale(); // Multiply the distance by the scale of the map to get meters.
    return path_found;
}

void RoutePlanner::AStarSearch() {
    RouteModel::Node* current_node = nullptr;
    current_node = start_node;
    start_node->visited = true;
    while (current_node != end_node){
      AddNeighbors(current_node);
      current_node = NextNode();
    }
    m_Model.path = ConstructFinalPath(current_node);
    std::cout << "Finished search algorithm\n";
}
