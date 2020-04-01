#include "goldberg_tarjan_max_flow.h"

enum class StepType { relabel, saturated_push, unsaturated_push };


StepType push(Vertex &active_vertex, Edge* edge, int capacity); 

void relabel(Graph &g, Vertex &v);

StepType push_or_relabel(Graph &g, Vertex &v);

ExecutionData run(Graph &graph) {
	ExecutionData data;
	data.relabels = 0;
	data.saturated_pushes = 0;
	data.unsaturated_pushes = 0;

	std::chrono::high_resolution_clock::time_point t_start = std::chrono::high_resolution_clock::now();

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

	std::string line;
	while(true) {
		auto iter = std::find_if(graph.vertices.begin(), graph.vertices.end(), [graph] (const Vertex &v) { return v.index != graph.target && v.index != graph.source && v.active() && v.distance < graph.nvertices; });
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
	std::vector<Vertex>::iterator iter = graph.vertices.end();
	do {
		if(iter != graph.vertices.end()) {
			Vertex &active_vertex = *iter;
			push_or_relabel(graph, active_vertex);
		}
		iter = std::find_if(graph.vertices.begin(), graph.vertices.end(), [graph] (const Vertex &v) { return v.index != graph.target && v.index != graph.source && v.active(); });
	} while(iter != graph.vertices.end());

	std::chrono::high_resolution_clock::time_point t_end = std::chrono::high_resolution_clock::now();
	data.duration = std::chrono::duration_cast<std::chrono::duration<double>>(t_end - t_start);
	return data;
}

StepType push(Vertex &active_vertex, Edge* edge, int capacity) {
	int delta = std::min(active_vertex.excess(), capacity);
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
			min_distance = std::min(min_distance, edge->end_vertex().distance + 1);
		}
	}
	for(auto edge : active_vertex.inbound_edges) {
		if(edge->is_residual_backward_arc()) {
			min_distance = std::min(min_distance, edge->start_vertex().distance + 1);
		}
	}
	active_vertex.distance = min_distance;
}

StepType push_or_relabel(Graph &g, Vertex &active_vertex) {
	// std::cout << "push_or_relabel: " << active_vertex << std::endl;
	// for(auto edge : active_vertex.outbound_edges) {
	// 	std::cout << *edge << std::endl;
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
