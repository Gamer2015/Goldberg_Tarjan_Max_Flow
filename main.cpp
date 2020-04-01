/*  */

// general file and execution information
#include "config.h"

// exceptions
#include <exception>

// streams
#include <fstream>

// containers & algorithms
#include <map>

// types
#include <string>
#include "Graph.h"

#include "goldberg_tarjan_max_flow.h"
enum class PrimitiveException { no_input };

// writes the output, which depends on the parameters
// ostream depends on if the parameter --outfile was used
void _write_output(Graph& g, std::ostream& output, std::map<std::string,std::string> parameters, ExecutionData data) {
    output << g.nvertices << ", " << g.nedges << ", " << g.source << ", " << g.target << std::endl;
    output << "max-flow: " << g.vertices[g.target].excess() << std::endl;

    if (parameters.find("--show_max_flow") != parameters.end()) {
        output << "flow: " << std::endl;
        for(const auto& edge : g.edges) {
            output << edge << std::endl;
        }
    }
    if (parameters.find("--show_min_cut") != parameters.end()) {
        output << "min-cut: ";
        Graph residual = g.residual();
        for(auto& edge : g.edges) {
            edge.weight = 1;
        }

        std::map<int, int> distances = residual.dijkstra(g.source);
        for(const auto& vertex : g.vertices) {
            if(distances.find(vertex.index) != distances.end()) {
                output << vertex.index << ", ";
            }
        }
        output << std::endl;
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

void write_output(Graph& g, std::ostream& output, std::map<std::string,std::string> parameters, ExecutionData data) {
    if(parameters.find("--outfile") != parameters.end()) { 
        std::ofstream ofs(parameters["--outfile"], std::ofstream::out);
        _write_output(g, ofs, parameters, data);
    }
    _write_output(g, std::cout, parameters, data);
}

void read_input(std::map<std::string,std::string> parameters, Graph &g) {
    bool done = false;
    if(parameters.find("--infile") != parameters.end()) { 
        std::ifstream ifs(parameters["--infile"], std::ifstream::in);
        ifs >> g;
        done = true;
    }
    if(parameters.find("--console") != parameters.end()) {
        std::cin >> g;
        done = true;
    }
    if(done == false) {
        throw PrimitiveException::no_input;
    }
}

int main(int argc, char** argv)
{
    auto parameters = parse_parameters(argc, argv);

    bool need_help = argc == 1;
    need_help |= parameters.find("-h") != parameters.end();
    need_help |= parameters.find("--help") != parameters.end();

    if(need_help) {
        show_helptext();
    } else {
        try {
            Graph g;
            read_input(parameters, g);

            auto data = run(g);
            
            write_output(g, std::cout, parameters, data);
        } catch (PrimitiveException e) { 
            show_helptext();
        }
    }

    return 0;
}



