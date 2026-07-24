#include <imgui.h>
#include <imnodes.h>

#include "gui/pages.h"

static ImU32 node_color(GraphNodeType type) {
    switch (type) {
    case GraphNodeType::Area:
        return IM_COL32(66, 133, 244, 255); // Blue
    case GraphNodeType::Project:
        return IM_COL32(76, 175, 80, 255); // Green
    case GraphNodeType::Task:
        return IM_COL32(255, 167, 38, 255); // Orange
    case GraphNodeType::Resource:
        return IM_COL32(0, 188, 212, 255); // Cyan
    case GraphNodeType::Note:
        return IM_COL32(171, 71, 188, 255); // Purple
    }

    return IM_COL32(120, 120, 120, 255);
}

static const char *node_type_name(GraphNodeType type) {
    switch (type) {
    case GraphNodeType::Area:
        return "Area";
    case GraphNodeType::Project:
        return "Project";
    case GraphNodeType::Task:
        return "Task";
    case GraphNodeType::Note:
        return "Note";
    case GraphNodeType::Resource:
        return "Resource";
    }

    return "";
}

void IUIPages::draw_page_graph() {
    Graph &graph = backend->get_graph();

    ImNodes::BeginNodeEditor();

    //-------------------------------------------------
    // Nodes
    //-------------------------------------------------

    for (auto &node : graph.nodes) {
        ImU32 color = node_color(node.type);

        ImNodes::PushColorStyle(ImNodesCol_TitleBar, color);
        ImNodes::PushColorStyle(ImNodesCol_TitleBarHovered, color);
        ImNodes::PushColorStyle(ImNodesCol_TitleBarSelected, color);

        ImNodes::BeginNode(node.id);

        ImNodes::BeginNodeTitleBar();
        ImGui::TextUnformatted(node.label.c_str());
        ImNodes::EndNodeTitleBar();

        ImGui::TextDisabled("%s", node_type_name(node.type));

        ImNodes::BeginInputAttribute(node.input_pin);
        ImGui::Dummy(ImVec2(1.f, 10.f));
        ImNodes::EndInputAttribute();

        ImNodes::BeginOutputAttribute(node.output_pin);
        ImGui::Indent(70.f);
        ImGui::Dummy(ImVec2(1.f, 10.f));
        ImNodes::EndOutputAttribute();

        ImNodes::EndNode();

        ImNodes::PopColorStyle();
        ImNodes::PopColorStyle();
        ImNodes::PopColorStyle();
    }

    //-------------------------------------------------
    // Links
    //-------------------------------------------------

    for (auto &edge : graph.edges)
        ImNodes::Link(edge.id, edge.from_pin, edge.to_pin);

    ImNodes::MiniMap(0.2f);

    ImNodes::EndNodeEditor();

    //-------------------------------------------------
    // Selection -> Inspector
    //-------------------------------------------------

    int count = ImNodes::NumSelectedNodes();

    if (count > 0) {
        std::vector<int> selected(count);
        ImNodes::GetSelectedNodes(selected.data());

        // Use the first selected node
        int selectedNode = selected.front();

        for (const auto &node : graph.nodes) {
            if (node.id != selectedNode)
                continue;

            switch (node.type) {
            case GraphNodeType::Area:
                backend->open_area(node.uuid);
                break;

            case GraphNodeType::Project:
                backend->open_project(node.uuid);
                break;

            case GraphNodeType::Task:
                backend->open_task(node.uuid);
                break;

            case GraphNodeType::Resource:
                backend->open_resource(node.uuid);
                break;

            case GraphNodeType::Note:
                // ->open_note(node.uuid);
                break;
            }

            break;
        }
    }
}