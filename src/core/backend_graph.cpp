#include "core/backend.h"
#include "core/graph.h"
#include "imnodes.h"
#include "imgui.h"
#include <unordered_map>

Graph &Backend::get_graph() {
    if (queried_graph)
        return graph;

    queried_graph = true;

    graph.nodes.clear();
    graph.edges.clear();

    std::unordered_map<std::string, size_t> node_index;

    int nextNode = 1;
    int nextPin = 10000;
    int nextEdge = 1;

    for (const auto &area : curr_areas) {
        graph.nodes.push_back({nextNode++, nextPin++, nextPin++, area.id,
                               area.text.empty() ? "Untitled Area" : area.text,
                               GraphNodeType::Area});

        node_index[area.id] = graph.nodes.size() - 1;
    }

    for (const auto &project : curr_projects) {
        graph.nodes.push_back(
            {nextNode++, nextPin++, nextPin++, project.id,
             project.text.empty() ? "Untitled Project" : project.text,
             GraphNodeType::Project});

        size_t projectIndex = graph.nodes.size() - 1;
        node_index[project.id] = projectIndex;

        auto parent = node_index.find(project.area_id);

        if (parent != node_index.end()) {
            graph.edges.push_back({nextEdge++,
                                   graph.nodes[parent->second].output_pin,
                                   graph.nodes[projectIndex].input_pin});
        }
    }

    for (const auto &task : curr_tasks) {
        graph.nodes.push_back({nextNode++, nextPin++, nextPin++, task.id,
                               task.text.empty() ? "Untitled Task" : task.text,
                               GraphNodeType::Task});

        size_t taskIndex = graph.nodes.size() - 1;
        node_index[task.id] = taskIndex;

        auto parent = node_index.find(task.project_id);

        if (parent != node_index.end()) {
            graph.edges.push_back({nextEdge++,
                                   graph.nodes[parent->second].output_pin,
                                   graph.nodes[taskIndex].input_pin});
        }
    }

    for (const auto &resource : curr_resources) {
        graph.nodes.push_back(
            {nextNode++, nextPin++, nextPin++, resource.id,
             resource.text.empty() ? "Untitled Resource" : resource.text,
             GraphNodeType::Resource});

        size_t resourceIndex = graph.nodes.size() - 1;
        node_index[resource.id] = resourceIndex;

        auto parent = node_index.find(resource.area_id);

        if (parent != node_index.end()) {
            graph.edges.push_back({nextEdge++,
                                   graph.nodes[parent->second].output_pin,
                                   graph.nodes[resourceIndex].input_pin});
        }
    }

    return graph;
}

void Backend::layout_graph() {
    Graph &graph = get_graph();

    const float X_AREA = 0.f;
    const float X_RESOURCE = 250.f;
    const float X_PROJECT = 500.f;
    const float X_TASK = 750.f;
    const float X_NOTE = 1000.f;

    float yArea = 0.f;
    float yResource = 0.f;
    float yProject = 0.f;
    float yTask = 0.f;
    float yNote = 0.f;

    for (auto &node : graph.nodes) {
        ImVec2 pos;

        switch (node.type) {
        case GraphNodeType::Area:
            pos = {X_AREA, yArea};
            yArea += 120.f;
            break;

        case GraphNodeType::Resource:
            pos = {X_RESOURCE, yResource};
            yResource += 90.f;
            break;

        case GraphNodeType::Project:
            pos = {X_PROJECT, yProject};
            yProject += 120.f;
            break;

        case GraphNodeType::Task:
            pos = {X_TASK, yTask};
            yTask += 90.f;
            break;

        case GraphNodeType::Note:
            pos = {X_NOTE, yNote};
            yNote += 90.f;
            break;
        }

        ImNodes::SetNodeGridSpacePos(node.id, pos);
    }
}