/*  */

// general file and execution information
#include "config.h"

// streams
#include <fstream>

// containers & algorithms
#include <map>

// types
#include <string>
#include "Graph.h"

#include "goldberg_tarjan_max_flow.h"


void output(Graph& g, std::ostream& output, std::map<std::string,std::string> parameters, ExecutionData data) {
    output << g.nvertices << ", " << g.nedges << ", " << g.source << ", " << g.target << std::endl;
    output << "max-flow: " << g.vertices[g.target].excess() << std::endl;

    if (parameters.find("--show_max_flow") != parameters.end()) {
        output << "flow: " << std::endl;
        for(const auto& edge : g.edges) {
            output << edge << std::endl;
        }
    }
    if (parameters.find("--show_min_cut") != parameters.end()) {
        output << "min-cut: " << std::endl;
        output << " - to be done" << std::endl;
    }
    if (parameters.find("--show_calc_time") != parameters.end()) {
        output << "calculation time: " << data.duration.count() << "s" << std::endl;
    }
    if (parameters.find("--show_step_counts") != parameters.end()) {
        output << "steps: " << std::endl;
        output << " - relabels: " << data.relabels << std::endl;
        output << " - saturated pushes: " << data.saturated_pushes << std::endl;
        output << " - unsaturated pushes: " << data.unsaturated_pushes << std::endl;
    }
}

void populate_graph(std::map<std::string,std::string> parameters, Graph &g) {
    if(parameters.find("--infile") != parameters.end()) { 
        std::ifstream ifs(parameters["--infile"], std::ifstream::in);
        ifs >> g;
    }
    if(parameters.find("--console") != parameters.end()) {
        std::cin >> g;
    }
}

int main(int argc, char** argv)
{
    auto parameters = parse_parameters(argc, argv);

    bool need_help = false;
    need_help |= parameters.find("-h") != parameters.end();
    need_help |= parameters.find("--help") != parameters.end();

    if(need_help) {
        show_helptext();
    } else {
        try {
            Graph g;
            populate_graph(parameters, g);

            auto data = run(g);
            
            output(g, std::cout, parameters, data);
        } catch (const std::exception &e) { 
            show_helptext();
        }
    }

    return 0;
}



