#ifndef GRAPH_H_
#define GRAPH_H_

#include <string>
#include <vector>

enum class GraphNodeType { Area, Project, Task, Note, Resource };

struct GraphNode {
    int id;

    int input_pin;
    int output_pin;

    std::string uuid;
    std::string label;

    GraphNodeType type;
};

struct GraphEdge {
    int id;

    int from_pin;
    int to_pin;
};

struct Graph {
    std::vector<GraphNode> nodes;
    std::vector<GraphEdge> edges;
};

#endif