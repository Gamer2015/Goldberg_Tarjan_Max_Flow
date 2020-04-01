#include "goldberg_tarjan_max_flow.h"

// streams
#include <iostream>

// containers & algorithms
#include <algorithm>
#include <map>

// types
#include <string>
enum class StepType { relabel, saturated_push, unsaturated_push };


using namespace std;

StepType push(Vertex &active_vertex, Edge* edge, int capacity) {
	int delta = min(active_vertex.excess(), capacity);
	bool saturated = delta == active_vertex.excess();

	if(&active_vertex == &edge->end_vertex()) {
		delta *= -1;
	}

	edge->flow(edge->flow() + delta);

	if(saturated) {
		return StepType::saturated_push; // saturated push
	} else {
		return StepType::unsaturated_push; // unsaturated push
	}
}

void relabel(Graph &g, Vertex &active_vertex) {
	unsigned int min_distance = -1;

	for(auto edge : active_vertex.outbound_edges) {
		if(edge->is_residual_forward_arc()) {
			min_distance = min(min_distance, edge->end_vertex().distance + 1);
		}
	}
	for(auto edge : active_vertex.inbound_edges) {
		if(edge->is_residual_backward_arc()) {
			min_distance = min(min_distance, edge->start_vertex().distance + 1);
		}
	}
	active_vertex.distance = min_distance;
}

StepType push_or_relabel(Graph &g, Vertex &active_vertex) {
	// cout << "push_or_relabel: " << active_vertex << endl;
	// for(auto edge : active_vertex.outbound_edges) {
	// 	cout << *edge << endl;
	// }

	for(auto edge : active_vertex.outbound_edges) {
		if(edge->is_residual_forward_arc() && edge->is_residual_forward_admissible()) {
			return push(active_vertex, edge, edge->residual_forward_capacity() );
		}
	}
	for(auto edge : active_vertex.inbound_edges) {
		if(edge->is_residual_backward_arc() && edge->is_residual_backward_admissible()) {
			return push(active_vertex, edge, edge->residual_backward_capacity() );
		}
	}
	relabel(g, active_vertex);
	return StepType::relabel; // relabel
}

ExecutionData run(Graph &graph) {
	ExecutionData data;
	data.relabels = 0;
	data.saturated_pushes = 0;
	data.unsaturated_pushes = 0;

	chrono::high_resolution_clock::time_point t_start = chrono::high_resolution_clock::now();

	// initialize flow
	for(auto &edge : graph.edges) {
		if(edge.start == graph.source) {
			edge.flow(edge.capacity);
		} else {
			edge.flow(0);
		}
	}

	// initialize distances
	for(auto &vertex : graph.vertices) {
		int distance = 1;
		if(vertex.index == graph.source) {
			distance = graph.nvertices;
		}
		if(vertex.index == graph.target) {
			distance = 0;
		}
		vertex.distance = distance;
	}

	string line;
	while(true) {
		auto iter = find_if(graph.vertices.begin(), graph.vertices.end(), [graph] (const Vertex &v) { return v.index != graph.target && v.index != graph.source && v.active() && v.distance < graph.nvertices; });
		if(iter != graph.vertices.end()) {
			Vertex &active_vertex = *iter;

			StepType step = push_or_relabel(graph, active_vertex);
			if(step == StepType::relabel) {
				++(data.relabels);
			} else if(step == StepType::saturated_push) {
				++(data.saturated_pushes);
			} else if(step == StepType::unsaturated_push) {
				++(data.unsaturated_pushes);
			}
		} else {
			break;
		}
	}

	// send back what cannot not reach the target
	vector<Vertex>::iterator iter = graph.vertices.end();
	do {
		if(iter != graph.vertices.end()) {
			Vertex &active_vertex = *iter;
			push_or_relabel(graph, active_vertex);
		}
		iter = find_if(graph.vertices.begin(), graph.vertices.end(), [graph] (const Vertex &v) { return v.index != graph.target && v.index != graph.source && v.active(); });
	} while(iter != graph.vertices.end());

	chrono::high_resolution_clock::time_point t_end = chrono::high_resolution_clock::now();
	data.duration = chrono::duration_cast<chrono::duration<double>>(t_end - t_start);
	return data;
}