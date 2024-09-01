#include "Graph.h"
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

template <class V, class E>
const V& Vertice<V, E>:: get_data() const { 
	return data; 
}

template <class V, class E>
const vector<Edge<V, E>*>& Vertice<V, E>::get_incident_edges() const { 
	return outcoming_edges; 
}

template <class V, class E>
Edge<V,E>* Vertice<V, E>::add_ordered_edge(const E& weight, Vertice<V, E>* target) {
	Edge<V, E>* edge = new Edge<V, E>(weight, this, target);
	this->outcoming_edges.push_back(edge);
	target->incoming_edges.push_back(edge);
	return edge;
}

template <class V, class E>
void Vertice<V, E>::output_adjacent_vertices() {
	for (int i = 0; i < outcoming_edges.size(); i++) cout << outcoming_edges[i]->get_ending()->data << " ";
	cout << endl;
}

template <class V, class E>
Vertice<V, E>* Edge<V, E>::get_beginning() const {
	return beginning;
}

template <class V, class E>
Vertice<V, E>* Edge<V, E>::get_ending() const {
	return ending;
}

template <class V, class E>
const E& Edge<V, E>::get_weight() const {
	return weight;
}

template <class V, class E>
void Graph<V, E>::add_vertice(const V& data) {
	bool vertice_exists = false;
	try {
		for (int i = 0; i < vertices.size(); i++) if (vertices[i].data == data) {
			vertice_exists = true;
			throw true;
		}
		if (!vertice_exists) vertices.push_back(Vertice<V, E>(data));
	}
	catch (bool vertice_exists) {
		cout << "Similar vertice has alredy been added" << endl;
		return;
	}
	return;
}

template <class V, class E>
void Graph<V, E>::add_edge_between_vertices(const E& weight, Vertice<V, E>* beginning, Vertice<V, E>* ending) {
	bool edge_exists = false;
	try {
		for (int i = 0; i < beginning->outcoming_edges.size(); i++) if (beginning->outcoming_edges[i]->ending == ending) {
			edge_exists = true;
			throw true;
		}
		if (!edge_exists) {
			Edge<V,E>* add_edge = beginning->add_ordered_edge(weight, ending);
			edges.push_back(*add_edge);
		}
	}
	catch (bool edge_exists) {
		cout << "Similar edge between vertices " << beginning->data << " and " << ending->data <<" has alredy been added" << endl;
		return;
	}
	return;
}

template <class V, class E>
Vertice<V, E>* Graph<V, E>::get_vertice(const V& data) {
	for (int i = 0; i < vertices.size(); i++) {
		if (vertices[i].data == data) return &vertices[i];
	}
	return nullptr;
}

template <class V, class E>
void Graph<V, E>::output_adjacent_vertices(const V& data) {
	Vertice<V, E>* v1 = get_vertice(data);
	if (v1 == nullptr) {
		cout << "Vertice doesn't exist" << endl;
		return;
	}
	else v1->output_adjacent_vertices();
	return;
}

template <class V, class E>
void Graph<V, E>::output_incoming() {
	for (int i = 0; i < vertices.size(); i++) {
		cout << "Incoming vertices for " << vertices[i].data << ": ";
		for (int j = 0; j < vertices[i].incoming_edges.size(); j++) {
			cout << vertices[i].incoming_edges[j]->get_beginning()->data << " (weight "
				<< vertices[i].incoming_edges[j]->get_weight() << ") ";
				
		}
		cout << endl;
	}
}

template <class V, class E>
void Graph<V, E>::output_outcoming() {
	for (int i = 0; i < vertices.size(); i++) {
		cout << "Outcoming vertices for " << vertices[i].data << ": ";
		for (int j = 0; j < vertices[i].outcoming_edges.size(); j++) {
			cout << vertices[i].outcoming_edges[j]->get_ending()->data << " (weight "
				<< vertices[i].outcoming_edges[j]->get_weight() << ") ";

		}
		cout << endl;
	}
}

template <class V, class E>
void Graph<V, E>::output_vertices() {
	for (int i = 0; i < vertices.size(); i++) {
		cout << vertices[i].data << " (dijkstra_len: " << vertices[i].dijkstra_len <<
			", bellman_len: " << vertices[i].bellman_len <<
			", warshall_len: " << vertices[i].warshall_len <<
			", topo_idx: " << vertices[i].topo_idx << ", scc: "
			<< vertices[i].scc_number << ")" << endl;
	}
}

template <class V, class E>
void Graph<V, E>::set_dijkstra_len(const V& data) {
	clear_dijkstra_len();
	Vertice<V, E>* v = this->get_vertice(data);
	v->dijkstra_len = 0;
	queue<Vertice<V, E>*> q;
	q.push(v);
	Vertice<V, E>* cur;
	while (!q.empty()) {
		cur = q.front();
		q.pop();
		if (cur->used == false && cur->outcoming_edges.empty() == false) {
			priority_queue<Edge<V, E>*, vector<Edge<V, E>*>, compare_edges<V, E> > heap(cur->outcoming_edges.begin(), cur->outcoming_edges.end());
			for (int i = 0; i < cur->outcoming_edges.size(); i++) {
				if (!heap.empty()) {
					Edge<V, E>* lesser_weight = heap.top();
					heap.pop();

					while (lesser_weight->ending->used == true && heap.empty() == false) {
						lesser_weight = heap.top();
						heap.pop();
					}
					if (lesser_weight->ending->used == false) {
						q.push(lesser_weight->ending);
						lesser_weight->ending->used == true;
						lesser_weight->ending->dijkstra_len = cur->dijkstra_len + lesser_weight->weight;
					}
				}
			}
		}
		cur->used = true;
		
	}
}

template <class V, class E>
void Graph<V, E>::clear_dijkstra_len() {
	for (int i = 0; i < vertices.size(); i++) {
		vertices[i].used = false;
		vertices[i].dijkstra_len = INT32_MAX;
	}
}

template <class V, class E>
vector<Vertice<V, E>*> Graph<V, E>::dijkstra_shortest_path(const V& start_data, const V& end_data) {
	clear_dijkstra_len();
	Vertice<V, E>* start = this->get_vertice(start_data);
	Vertice<V, E>* end = this->get_vertice(end_data);
	set_dijkstra_len(start_data);
	start->dijkstra_len = 0;
	vector<Vertice<V, E>*> backwards;
	if (end->dijkstra_len == INT32_MAX) {
		cout << "Can't reach " << end_data << " from " << start_data << endl;
		return backwards;
	}	
	queue<Vertice<V, E>*> q;
	q.push(end);
	Vertice<V, E>* cur = end;
	while (q.empty() == false && cur->data != start->data) {
		cur = q.front();
		q.pop();
		backwards.push_back(cur);
		priority_queue<Vertice<V, E>*, vector<Vertice<V, E>*>, compare_vertices_d<V, E> > heap;
		for (int i = 0; i < cur->incoming_edges.size(); i++) {
			heap.push(cur->incoming_edges[i]->beginning);
		}
		if (!heap.empty()) {
			cur = heap.top();
			heap.pop();
			q.push(cur);
		}
	}
	backwards.push_back(start);
	std::reverse(backwards.begin(), backwards.end());
	return backwards;
}

template <class V, class E>
void Graph<V, E>::topo_sort() {
	for (int i = 0; i < this->vertices.size(); i++) vertices[i].used = false;
	int cpy = this->vertices.size();
	int& cur_idx = cpy;
	for (int i = 0; i < this->vertices.size(); i++) {
		if (!vertices[i].used) topo(&vertices[i], cur_idx);
	}
	return;
}

template <class V, class E>
void Graph<V, E>::topo(Vertice<V, E>* s, int& cur_idx) {
	s->used = true;
	for (int i = 0; i < s->outcoming_edges.size(); i++) {
		if (!s->outcoming_edges[i]->ending->used) topo(s->outcoming_edges[i]->ending, cur_idx);
	}
	s->topo_idx = cur_idx;
	cur_idx--;
	return;
}

template <class V, class E>
void Graph<V, E>::topo_sort_rev() {
	reverse();

	for (int i = 0; i < this->vertices.size(); i++) vertices[i].used = false;
	int cpy = this->vertices.size();
	int& cur_idx = cpy;
	for (int i = 0; i < this->vertices.size(); i++) {
		if (!vertices[i].used) topo(&vertices[i], cur_idx);
	}
	return;
}

template <class V, class E>
void Graph<V, E>::reverse() {
	vector<Edge<V, E>> edges_rev;
	for (int i = 0; i < edges.size(); i++) {
		Edge<V, E> rev_edgei = Edge<V, E>(edges[i].weight, edges[i].ending, edges[i].beginning);
		edges_rev.push_back(rev_edgei);
	}
	std::swap(edges, edges_rev);
	for (int i = 0; i < vertices.size(); i++) {
		vertices[i].outcoming_edges.clear();
		vertices[i].incoming_edges.clear();
	}
	for (int i = 0; i < edges.size(); i++) {
		edges[i].beginning->outcoming_edges.push_back(&edges[i]);
		edges[i].ending->incoming_edges.push_back(&edges[i]);
	}
	return;
}

template <class V, class E>
void Graph<V, E>::output_edges() {
	for (int i = 0; i < edges.size(); i++) cout << edges[i].beginning->data << "-" << edges[i].ending->data << endl;
	return;
}

template <class V, class E>
void Graph<V, E>::kosaraju() {
	this->topo_sort_rev();
	for (int i = 0; i < this->vertices.size(); i++) vertices[i].used = false;
	int num_scc = 0;
	priority_queue<Vertice<V, E>*, vector<Vertice<V, E>*>, compare_vertices_scc<V, E> > heap;
	for (int i = 0; i < vertices.size(); i++) heap.push(&vertices[i]);
	while (!heap.empty()) {
		Vertice<V, E>* v = heap.top();
		if (v->used == false) {
			num_scc++;
			this->scc(v, num_scc);
		}
		heap.pop();
	}
	for (int i = 0; i < this->vertices.size(); i++) {
		vertices[i].used = false;
		vertices[i].topo_idx = -1;
	}
	reverse();
	return;
}

template <class V, class E>
void Graph<V, E>::scc(Vertice<V, E>* s, int num_scc) {
	s->used = true;
	s->scc_number = num_scc;
	for (int i = 0; i < s->outcoming_edges.size(); i++) {
		if (s->outcoming_edges[i]->ending->used == false) scc(s->outcoming_edges[i]->ending, num_scc);
	}
	return;
}

template <class V, class E>
void Graph<V, E>::bellman_ford(const V& data) {
	for (int i = 0; i < vertices.size(); i++) vertices[i].bellman_len = 1e9; //INT32_MAX; плохая идея брать максимальный int в качестве бесконечности, тк идёт при +(>0) переход в -
	Vertice<V, E>* s = get_vertice(data);
	s->bellman_len = 0;
	for (int i = 1; i < vertices.size() ; i++) {
		for (auto& edge: edges) {
			if (edge.ending->bellman_len > edge.beginning->bellman_len + edge.get_weight()) {
				edge.ending->bellman_len = edge.beginning->bellman_len + edge.get_weight();
			}
		}
	}
	for (auto& edge : edges) {
		if (edge.ending->bellman_len > edge.beginning->bellman_len + edge.get_weight()) {
			cout << "This graph has a cicle with a negative weight!" << endl;
			return;
		}
	}
	return;
}

template <class V, class E>
vector<Vertice<V, E>*> Graph<V, E>::bellman_ford_shortest_path(const V& start_data, const V& end_data) {
	for (int i = 0; i < vertices.size(); i++) vertices[i].used = false;
	Vertice<V, E>* start = this->get_vertice(start_data);
	Vertice<V, E>* end = this->get_vertice(end_data);
	bellman_ford(start_data);
	start->bellman_len = 0;
	vector<Vertice<V, E>*> backwards;
	if (end->bellman_len == 10e9) {
		cout << "Can't reach " << end_data << " from " << start_data << endl;
		return backwards;
	}
	queue<Vertice<V, E>*> q;
	q.push(end);
	Vertice<V, E>* cur = end;
	while (q.empty() == false && cur->data != start->data) {
		cur = q.front();
		q.pop();
		backwards.push_back(cur);
		priority_queue<Vertice<V, E>*, vector<Vertice<V, E>*>, compare_vertices_b<V, E> > heap;
		for (int i = 0; i < cur->incoming_edges.size(); i++) {
			heap.push(cur->incoming_edges[i]->beginning);
		}
		if (!heap.empty()) {
			cur = heap.top();
			heap.pop();
			q.push(cur);
		}
	}
	backwards.push_back(start);
	std::reverse(backwards.begin(), backwards.end());
	return backwards;
}

template <class V, class E>
vector3d Graph<V, E>::warshall_floyd() {
	int n = vertices.size();
	vector3d A(n + 1, vector<vector<int>>(n + 1, vector<int>(n + 1, 1000000000))); //заполнен сначала 10е9
	for (int v = 1; v <= n; v++) {
		for (int w = 1; w <= n; w++) {
			if (v == w) A[0][v-1][w-1] = 0;
			else {
				Vertice<V, E> v_ver = vertices[v-1];
				Vertice<V, E> w_ver = vertices[w-1];
				for (auto& edge : v_ver.outcoming_edges) {
					if (edge->ending->data == w_ver.data) A[0][v-1][w-1] = edge->weight;
				}
			}
		}
	}
	for (int k = 1; k < n + 1; k++) {
		for (int v = 1; v <= n; v++) {
			for (int w = 1; w <= n; w++) {
				if (A[k - 1][v-1][w-1] < A[k - 1][v-1][k-1] + A[k - 1][k-1][w-1])
					A[k][v-1][w-1] = A[k - 1][v-1][w-1];
				else A[k][v-1][w-1] = A[k - 1][v-1][k-1] + A[k - 1][k-1][w-1];
			}
		}
	}
	for (int v = 1; v <= n; v++) {
		if (A[n][v][v] < 0) cout << "This graph has a cicle with a negative weight!" << endl;
	}
	return A;
}

template <class V, class E>
void Graph<V, E>::set_warshall_floyd_len(const V& data) {
	int start_idx = 0;
	for (int i = 0; i < vertices.size(); i++) {
		if (vertices[i].data == data) start_idx = i;
	}
	if (start_idx == -1) {
		cout << "No such vertex" << endl;
		return;
	}
	vector3d A = warshall_floyd();
	for (int i = 0; i < vertices.size(); i++) {
		vertices[i].warshall_len = A[vertices.size()][start_idx][i];
	}
	return;
}

template <class V, class E>
vector<Vertice<V, E>*> Graph<V, E>::warshall_floyd_shortest_path(const V& start_data, const V& end_data) {
	for (int i = 0; i < vertices.size(); i++) vertices[i].used = false;
	Vertice<V, E>* start = this->get_vertice(start_data);
	Vertice<V, E>* end = this->get_vertice(end_data);
	set_warshall_floyd_len(start_data);
	start->warshall_len = 0;
	vector<Vertice<V, E>*> backwards;
	if (end->warshall_len == 10e9) {
		cout << "Can't reach " << end_data << " from " << start_data << endl;
		return backwards;
	}
	queue<Vertice<V, E>*> q;
	q.push(end);
	Vertice<V, E>* cur = end;
	while (q.empty() == false && cur->data != start->data) {
		cur = q.front();
		q.pop();
		backwards.push_back(cur);
		priority_queue<Vertice<V, E>*, vector<Vertice<V, E>*>, compare_vertices_w<V, E> > heap;
		for (int i = 0; i < cur->incoming_edges.size(); i++) {
			heap.push(cur->incoming_edges[i]->beginning);
		}
		if (!heap.empty()) {
			cur = heap.top();
			heap.pop();
			q.push(cur);
		}
	}
	backwards.push_back(start);
	std::reverse(backwards.begin(), backwards.end());
	return backwards;
}

template <class V, class E>
vector2d Graph<V, E>::convert_to_matrix() {
	int n = vertices.size();
	vector2d A(n, vector<int>(n, 1000000000));
	for (int v = 0; v < n; v++) {
		for (int w = 0; w < n; w++) {
			if (v == w) A[v][w] = 0;
			else {
				Vertice<V, E> v_ver = vertices[v];
				Vertice<V, E> w_ver = vertices[w];
				for (auto& edge : v_ver.outcoming_edges) {
					if (edge->ending->data == w_ver.data) A[v][w] = edge->weight;
				}
			}
		}
	}
	cout << "Order of edges in adjacency matrix:" << endl << "	";
	for (int i = 0; i < vertices.size(); i++) cout << vertices[i].data << " ";
	return A;
}

template<class V, class E>
int Graph<V, E>::get_scc(const V& data) const {
	Vertice<V, E> res;
	for (int i = 0; i < vertices.size(); i++) {
		if (vertices[i].data == data) res = vertices[i];
	}
	return res.scc_number;
}

template<class V, class E>
int Graph<V, E>::get_topo_idx(const V& data) const {
	Vertice<V, E> res;
	for (int i = 0; i < vertices.size(); i++) {
		if (vertices[i].data == data) res = vertices[i];
	}
	return res.topo_idx;
}