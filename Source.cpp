#include <iostream>
#include <string>
#include "Graph.cpp"

using namespace std;

int main() {
	Graph<string, int> g2 = Graph<string, int>();

	g2.add_vertice("v1");
	g2.add_vertice("v2");
	g2.add_vertice("v3");
	g2.add_vertice("v4");
	g2.add_vertice("v5");
	g2.add_vertice("v6");
	g2.add_vertice("v7");
	g2.add_edge_between_vertices(12, g2.get_vertice("v1"), g2.get_vertice("v2"));
	g2.add_edge_between_vertices(23, g2.get_vertice("v2"), g2.get_vertice("v3"));
	g2.add_edge_between_vertices(13, g2.get_vertice("v1"), g2.get_vertice("v3"));
	g2.add_edge_between_vertices(24, g2.get_vertice("v2"), g2.get_vertice("v4"));
	//g2.add_edge_between_vertices(15, g2.get_vertice("v1"), g2.get_vertice("v5"));
	g2.add_edge_between_vertices(45, g2.get_vertice("v4"), g2.get_vertice("v5"));
	g2.add_edge_between_vertices(0, g2.get_vertice("v2"), g2.get_vertice("v1"));
	g2.add_edge_between_vertices(1, g2.get_vertice("v1"), g2.get_vertice("v6"));
	g2.set_dijkstra_len("v2");
	g2.kosaraju();
	g2.topo_sort();
	g2.bellman_ford("v2");
	g2.set_warshall_floyd_len("v2");
	g2.output_outcoming();
	cout << endl << endl;
	g2.output_incoming();
	cout << endl << endl;
	g2.output_vertices();
	cout << endl;
	vector<Vertice<string, int>*> res = g2.warshall_floyd_shortest_path("v1", "v5");
	for (int i = 0; i < res.size(); i++) cout << res[i]->get_data() << " ";
	cout << endl;
	return 0;
}