#ifndef ROUTE_MODEL_H
#define ROUTE_MODEL_H

#include <limits>
#include <cmath>
#include <unordered_map>
#include "model.h"
#include <iostream>

class RouteModel : public Model {

  public:
  // RouteModel has a subclass Node which also inherits from Model struct Node.  Model struct Node provided x and y co-ordinates.

    class Node : public Model::Node {
      public:
        Node * parent = nullptr;
        float h_value = std::numeric_limits<float>::max();
        float g_value = 0.0;
        bool visited = false;
        std::vector<Node *> neighbors;

        void FindNeighbors();
      	// distance calculated here is euclidean.
        float distance(Node other) const {
            return std::sqrt(std::pow((x - other.x), 2) + std::pow((y - other.y), 2));
        }

      	//Default constructor

        Node(){}
      
      	// Use Model Node to construct RouteModel Node. idx helps keep track of the nodes and also the model where these nodes belong.

        Node(int idx, RouteModel * search_model, Model::Node node) : Model::Node(node), parent_model(search_model), index(idx) {}

      private:
        int index;
        Node * FindNeighbor(std::vector<int> node_indices);
        RouteModel * parent_model = nullptr;
    };
	
  // RouteModel constructor takes in the xml file which has the open street map data.

    RouteModel(const std::vector<std::byte> &xml);
  
  	// Method FindClosest Node allows us to find closest x and y co-ordinates.
    Node &FindClosestNode(float x, float y);
    
  	// gettr function which returns vector of nodes. m_Nodes.
  	auto &SNodes() { return m_Nodes; }
  
  	// Vector to store the final path. Starting to end path.
    std::vector<Node> path;
    
  private:
    void CreateNodeToRoadHashmap();
    std::unordered_map<int, std::vector<const Model::Road *>> node_to_road;
    std::vector<Node> m_Nodes;

};

#endif
