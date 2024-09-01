#include "pch.h"
#include "CppUnitTest.h"
#include <cassert>
#include <string>
#include "..\lab3sem3\Graph.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testlab3sem3
{
	TEST_CLASS(Testlab3sem3)
	{
	public:
		TEST_METHOD(Paths)
		{
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
			g2.add_edge_between_vertices(45, g2.get_vertice("v4"), g2.get_vertice("v5"));
			vector<Vertice<string, int>*> res_w = g2.warshall_floyd_shortest_path("v1", "v5");
			vector<Vertice<string, int>*> res_b = g2.bellman_ford_shortest_path("v1", "v5");
			vector<Vertice<string, int>*> res_d = g2.dijkstra_shortest_path("v1", "v5");
			vector<string> res;
			res.push_back("v1");
			res.push_back("v2");
			res.push_back("v4");
			res.push_back("v5");
			for (int i = 0; i < res.size(); i++) {
				assert(res_w[i]->get_data() == res[i]);
				assert(res_d[i]->get_data() == res[i]);
				assert(res_b[i]->get_data() == res[i]);

			}
			g2.add_edge_between_vertices(15, g2.get_vertice("v1"), g2.get_vertice("v5"));
			vector<Vertice<string, int>*> res_w1 = g2.warshall_floyd_shortest_path("v1", "v5");
			vector<Vertice<string, int>*> res_b1 = g2.bellman_ford_shortest_path("v1", "v5");
			vector<Vertice<string, int>*> res_d1 = g2.dijkstra_shortest_path("v1", "v5");
			vector<string> res1;
			res1.push_back("v1");
			res1.push_back("v5");
			for (int i = 0; i < res1.size(); i++) {
				assert(res_w1[i]->get_data() == res1[i]);
				assert(res_d1[i]->get_data() == res1[i]);
				assert(res_b1[i]->get_data() == res1[i]);

			}
		}
		TEST_METHOD(SCC) {
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
			g2.add_edge_between_vertices(31, g2.get_vertice("v3"), g2.get_vertice("v1"));
			g2.add_edge_between_vertices(24, g2.get_vertice("v2"), g2.get_vertice("v4"));
			g2.add_edge_between_vertices(15, g2.get_vertice("v1"), g2.get_vertice("v5"));
			g2.add_edge_between_vertices(45, g2.get_vertice("v4"), g2.get_vertice("v5"));
			g2.add_edge_between_vertices(-12, g2.get_vertice("v2"), g2.get_vertice("v1"));
			g2.add_edge_between_vertices(41, g2.get_vertice("v4"), g2.get_vertice("v1"));
			g2.add_edge_between_vertices(1, g2.get_vertice("v6"), g2.get_vertice("v7"));
			g2.add_edge_between_vertices(2, g2.get_vertice("v7"), g2.get_vertice("v6"));
			g2.kosaraju();
			assert(g2.get_scc("v1") == g2.get_scc("v2"));
			assert(g2.get_scc("v1") == g2.get_scc("v3"));
			assert(g2.get_scc("v1") == g2.get_scc("v4"));
			assert(g2.get_scc("v1") != g2.get_scc("v5"));
			assert(g2.get_scc("v1") != g2.get_scc("v6"));
			assert(g2.get_scc("v6") == g2.get_scc("v7"));
			assert(g2.get_scc("v6") != g2.get_scc("v5"));
		}
		TEST_METHOD(TopoSort) {
			Graph<string, int> g2 = Graph<string, int>();
			g2.add_vertice("v1");
			g2.add_vertice("v2");
			g2.add_vertice("v3");
			g2.add_vertice("v4");
			g2.add_vertice("v5");
			g2.add_edge_between_vertices(12, g2.get_vertice("v1"), g2.get_vertice("v2"));
			g2.add_edge_between_vertices(23, g2.get_vertice("v2"), g2.get_vertice("v3"));
			g2.add_edge_between_vertices(13, g2.get_vertice("v1"), g2.get_vertice("v3"));
			g2.add_edge_between_vertices(24, g2.get_vertice("v2"), g2.get_vertice("v4"));
			g2.add_edge_between_vertices(15, g2.get_vertice("v1"), g2.get_vertice("v5"));
			g2.add_edge_between_vertices(45, g2.get_vertice("v4"), g2.get_vertice("v5"));
			g2.topo_sort();
			assert(g2.get_topo_idx("v1") < g2.get_topo_idx("v2"));
			assert(g2.get_topo_idx("v1") < g2.get_topo_idx("v3"));
			assert(g2.get_topo_idx("v1") < g2.get_topo_idx("v4"));
			assert(g2.get_topo_idx("v1") < g2.get_topo_idx("v5"));
			assert(g2.get_topo_idx("v2") < g2.get_topo_idx("v3"));
			assert(g2.get_topo_idx("v2") < g2.get_topo_idx("v4"));
			assert(g2.get_topo_idx("v4") < g2.get_topo_idx("v5"));
		}
	};
}