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



void populate_graph(std::map<std::string,std::string> parameters, Graph& g) {
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
        } catch (const std::exception& e) { 
            show_helptext();
        }
    }
    return 0;

/*
    bool show_helptext = false;

    bool read_parameter = true;
    bool read_data = false;

    bool parameter_position = -1;
    std::string parameter_data = "";
    for(int i = 0; i < argc; ++i) {
        std::string arg = argv[i];
        show_helptext |= arg.compare("-h");
        show_helptext |= arg.compare("--help");

        if(read_parameter) {
            for(auto parameter : parameters_without_data) {
                if(parameter.compare(arg)) {
                    parameter_position = i;
                }
            }
            for(auto parameter : parameters_with_data) {
                if(parameter.compare(arg) && argc > i+1) {
                    parameter_position = i;
                    read_data = true;
                }
            }
        }
        if(read_parameter) {
        }
    }

    std::cout << "help: " << show_helptext << std::endl;
    if(show_helptext) {
        std::cout << "Use the program as follows " << std::endl; 
        return 0;
    } 
    return 0;
*/
/*
    typedef double T;
    std::array<std::string const, 2> const files = {"input_1_x.txt", "input_2_x.txt"};
    std::array<std::function<double(double)> const, 3> const functions = {p, q, s};
    std::array<std::string const, 3> const functionNames = {"p", "q", "s"};

    std::vector<std::string> outputFileNames;

    for(unsigned int ci = 0; ci < files.size(); ++ci) { // ci : count of input file
        // iterating over input files 
        std::string const& inputFileName = files[ci];
        std::vector<T> x;
        read_vector_from_file(inputFileName, x);
        std::cout << "file: " << inputFileName << std::endl;

        for(unsigned int cf = 0; cf < functions.size(); ++cf) {
            // iterating over functions 
            std::function<T(T)> const& func = functions[cf];
            std::vector<T> values(x.size());
            std::vector<T> diffValues(x.size());
            std::vector<T> intValues(x.size());

            for(unsigned int cx = 0; cx < x.size(); ++cx) {
            // calculating values 
                values[cx] = func(x[cx]);
                diffValues[cx] = diff_num(func, x[cx], 1e-5);
                intValues[cx] = int_num(func, 0, x[cx], 1e-5);
            }
            std::string tmpStrOutput = std::string("output") + inputFileName.substr(5) + std::string("_");
            std::cout << "write data: " << tmpStrOutput << std::endl;
            std::string tmpStr = tmpStrOutput + functionNames[cf] + std::string("_values.txt");
            outputFileNames.push_back(tmpStr);
            write_vector_to_file(tmpStr, values);
            tmpStr = tmpStrOutput + functionNames[cf] + std::string("_diffs.txt");
            outputFileNames.push_back(tmpStr);
            write_vector_to_file(tmpStr, diffValues);
            tmpStr = tmpStrOutput + functionNames[cf] + std::string("_ints.txt");
            outputFileNames.push_back(tmpStr);
            write_vector_to_file(tmpStr, intValues);
            outputFileNames.push_back("");
        }
    }
*/
    /*
    std::string outputSummaryFileName = "outputFileNames.txt";
    std::ofstream ofs(outputSummaryFileName);
    if(ofs.is_open()) {
        for(auto const& str : outputFileNames) {
            ofs << str << std::endl;
        }
    }
    else
    {
        cout << "\nFile " << outputSummaryFileName << " has not been opened.\n\n" ;
    }
    */

    return 0;
}



