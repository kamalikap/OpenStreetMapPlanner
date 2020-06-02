#ifndef ROUTE_PLANNER_H
#define ROUTE_PLANNER_H

#include <iostream>
#include <vector>
#include <string>
#include "route_model.h"


class RoutePlanner {
  public:
  //Route Planner constructor which takes RouteModel, co-ordinates start, end

    RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y);
    // Add public variables or methods declarations here.
  // GetDistance method which returns the distance which is stored as a private variable in the model.
    // GetDistance is used to store the complete distance of the path that is found from strating point to the end point.
    float GetDistance() const {return distance;}
    void AStarSearch();

    // The following methods have been made public so we can test them individually.
    void AddNeighbors(RouteModel::Node *current_node);
    float CalculateHValue(RouteModel::Node const *node);
    std::vector<RouteModel::Node> ConstructFinalPath(RouteModel::Node *current_node);
    RouteModel::Node *NextNode();
  	

  private:
    // Add private variables or methods declarations here.
    std::vector<RouteModel::Node*> open_list; //vector pointer to open_list

    RouteModel::Node *start_node; // pointer to start node

    RouteModel::Node *end_node; // pointer to end node


    float distance = 0.0f;
    RouteModel &m_Model;
};

#endif