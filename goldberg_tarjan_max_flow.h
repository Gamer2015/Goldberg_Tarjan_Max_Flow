#ifndef GOLDBERG_TARJAN_MAX_FLOW_H_INCLUDED
#define GOLDBERG_TARJAN_MAX_FLOW_H_INCLUDED

// streams
#include <iostream>

// containers & algorithms
#include <algorithm>
#include <map>

// types
#include <string>
#include "Graph.h"

void run();

void push(Graph& g, Vertex& v); 

void relabel(Graph& g, Vertex& v);

void push_or_relabel(Graph& g, Vertex& v);

#endif // GOLDBERG_TARJAN_MAX_FLOW_H_INCLUDED