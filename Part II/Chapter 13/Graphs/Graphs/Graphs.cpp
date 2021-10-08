#define CATCH_CONFIG_MAIN
#include <boost/graph/adjacency_list.hpp>
#include <catch.hpp>
#include <set>
using namespace boost;

TEST_CASE("adjacency_list stores graph data") {
    adjacency_list<> graph{};
    auto vertex_1 = add_vertex(graph);
    auto vertex_2 = add_vertex(graph);
    auto vertex_3 = add_vertex(graph);
    auto vertex_4 = add_vertex(graph);
    auto edge_12 = add_edge(vertex_1, vertex_2, graph);
    auto edge_13 = add_edge(vertex_1, vertex_3, graph);
    auto edge_21 = add_edge(vertex_2, vertex_1, graph);
    auto edge_24 = add_edge(vertex_2, vertex_4, graph);
    auto edge_43 = add_edge(vertex_4, vertex_3, graph);

    REQUIRE(num_vertices(graph) == 4);
    REQUIRE(num_edges(graph) == 5);

    auto [begin, end] = adjacent_vertices(vertex_1, graph);
    std::set<decltype(vertex_1)> neighbours_1{ begin, end };
    REQUIRE(neighbours_1.count(vertex_2) == 1);
    REQUIRE(neighbours_1.count(vertex_3) == 1);
    REQUIRE(neighbours_1.count(vertex_4) == 0);
}