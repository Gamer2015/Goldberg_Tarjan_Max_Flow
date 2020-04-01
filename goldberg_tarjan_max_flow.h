#ifndef GOLDBERG_TARJAN_MAX_FLOW_H_INCLUDED
#define GOLDBERG_TARJAN_MAX_FLOW_H_INCLUDED

// streams
#include <iostream>

// containers & algorithms
#include <algorithm>
#include <map>

// timing
#include <chrono>

// types
#include <string>
#include "Graph.h"

struct ExecutionData {
	std::chrono::duration<double> duration;
	unsigned int relabels;
	unsigned int saturated_pushes;
	unsigned int unsaturated_pushes;
};

ExecutionData run(Graph &graph);

#endif // GOLDBERG_TARJAN_MAX_FLOW_H_INCLUDED