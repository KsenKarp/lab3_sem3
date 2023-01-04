#pragma once
#include <iostream>
#include <vector>
#ifndef GRAPH
#define GRAPH

using namespace std;
using vector3d = vector<vector<vector<int>>>;
using vector2d = vector<vector<int>>;

template <class V, class E>
class Edge;
template <class V, class E>
class Graph;
template <class V, class E>
struct compare_vertices_d;
template <class V, class E>
struct compare_vertices_b;
template <class V, class E>
struct compare_vertices_w;
template <class V, class E>
struct compare_vertices_scc;

template <class V, class E>
class Vertice {
	friend class Graph<V, E>;
	friend struct compare_vertices_b<V, E>;
	friend struct compare_vertices_d<V, E>;
	friend struct compare_vertices_w<V, E>;
	friend struct compare_vertices_scc<V,E>;
	V data;
	vector<Edge<V, E>*> outcoming_edges;
	vector<Edge<V, E>*> incoming_edges;
	int topo_idx;
	int scc_number;
	E dijkstra_len;
	E bellman_len;
	E warshall_len;
	bool used;
public:
	Vertice() : data(V()), dijkstra_len(INT32_MAX), used(false), topo_idx(-1), scc_number(0), bellman_len(10e9), warshall_len(10e9) {};
	Vertice(const V& data_) : data(data_), dijkstra_len(INT32_MAX), used(false), topo_idx(-1), scc_number(0), 
		bellman_len(10e9), warshall_len(10e9) {};
	const V& get_data() const;
	const vector<Edge<V, E>*>& get_incident_edges() const;  //outcoming ones
	Edge<V,E>* add_ordered_edge(const E& data, Vertice<V, E>* target);
	void output_adjacent_vertices(); //"outcoming" ones
};

template <class V, class E>
struct compare_edges {
	bool operator()(Edge<V, E>* l, Edge<V, E>* r) {
		return l->get_weight() < r->get_weight();
	}
};

template <class V, class E>
struct compare_vertices_d {
	bool operator()(Vertice<V, E>* l, Vertice<V, E>* r) {
		return l->dijkstra_len > r->dijkstra_len;
	}
};

template <class V, class E>
struct compare_vertices_b {
	bool operator()(Vertice<V, E>* l, Vertice<V, E>* r) {
		return l->bellman_len > r->bellman_len;
	}
};

template <class V, class E>
struct compare_vertices_w {
	bool operator()(Vertice<V, E>* l, Vertice<V, E>* r) {
		return l->warshall_len > r->warshall_len;
	}
};

template <class V, class E>
struct compare_vertices_scc {
	bool operator()(Vertice<V, E>* l, Vertice<V, E>* r) {
		return l->topo_idx < r->topo_idx;
	}
};

template <class V, class E> 
class Edge {
	friend class Graph<V, E>;
	E weight;
	Vertice<V, E>* beginning;
	Vertice<V, E>* ending;
public:
	Edge() : weight(E()), beginning(nullptr), ending(nullptr) {};
	Edge(const E& weight_, Vertice<V, E>* beginning_, Vertice<V, E>* ending_) : weight(weight_), beginning(beginning_),
		ending(ending_) {};
	Vertice<V, E>* get_beginning() const;
	Vertice<V, E>* get_ending() const;
	const E& get_weight() const;
};


template <class V, class E>
class Graph {
	vector<Vertice<V, E>> vertices;
	vector<Edge<V, E>> edges;
	
	void topo(Vertice<V, E>* s, int& cur_idx);
	void scc(Vertice<V,E>* v, int scc_num);
	void clear_dijkstra_len();
	vector3d warshall_floyd();
public:
	void topo_sort_rev();
	Graph() : vertices(vector<Vertice<V, E>>()), edges(vector<Edge<V, E>>()) {};
	Graph(int number_of_vertices, int number_of_edges) : vertices(vector<Vertice<V, E>>(number_of_vertices)),
		edges(vector<Edge<V, E>>(number_of_edges)) {};
	void add_vertice(const V& data);
	void add_edge_between_vertices(const E& weight, Vertice<V, E>* beginning, Vertice<V, E>* ending);
	Vertice<V, E>* get_vertice(const V& data);
	void output_adjacent_vertices(const V& data);
	void output_incoming();
	void output_outcoming();
	void output_vertices();
	void output_edges();
	void set_dijkstra_len(const V& data);
	vector<Vertice<V, E>*> dijkstra_shortest_path(const V& start_data, const V& end_data);
	void topo_sort();
	void kosaraju();
	void reverse();
	void bellman_ford(const V& data);
	vector<Vertice<V, E>*> bellman_ford_shortest_path(const V& start_data, const V& end_data);
	void set_warshall_floyd_len(const V& data);
	vector<Vertice<V, E>*> warshall_floyd_shortest_path(const V& start_data, const V& end_data);
	vector2d convert_to_matrix();
	int get_scc(const V& data) const;
	int get_topo_idx(const V& data) const;
};

#endif