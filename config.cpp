#include "config.h"
// streams
#include <iostream>

// containers & algorithms
#include <algorithm>
#include <vector>

using namespace std;

map<string,string> parameters_with_description() {
    map<string,string> valid_parameters;
    valid_parameters["--infile"] = "Takes the data from the file passed to this parameter. Usage: --infile=\"text.txt\" or even --in";
    valid_parameters["--console"] = "Use the console as input stream. Usage: Write the input in the same format as the data in an input-file. Write \"end\" to finish data input.";
    
    valid_parameters["--outfile"] = "Writes the output in a file. Usage: --outfile=\"output.txt\"";
    valid_parameters["--show_max_flow"] = "Shows the calculated max flow. Usage: --show_max_flow";
    valid_parameters["--show_min_cut"] = "Shows a min cut. Usage: --show_min_cut";
    valid_parameters["--show_calculation_time"] = "Shows the calculation time. Usage: --show_calculation_time";
    valid_parameters["--show_step_counts"] = "Shows the amount of saturated pushes, unsaturated pushes and relabels. Usage: --show_step_counts";

    return valid_parameters;
}


vector<pair<string,string> > parameters_with_description2() {
    vector<pair<string,string> > valid_parameters;
    valid_parameters.emplace_back("--infile", "Takes the data from the file passed to this parameter. Usage: --infile=\"text.txt\" or even --in");
    valid_parameters.emplace_back("--console", "Use the console as input stream. Usage: Write the input in the same format as the data in an input-file. Write \"end\" to finish data input.");
    
    valid_parameters.emplace_back("--outfile", "Writes the output in a file. Usage: --outfile=\"output.txt\"");
    valid_parameters.emplace_back("--show_max_flow", "Shows the calculated max flow. Usage: --show_max_flow");
    valid_parameters.emplace_back("--show_min_cut", "Shows a min cut. Usage: --show_min_cut");
    valid_parameters.emplace_back("--show_calculation_time", "Shows the calculation time. Usage: --show_calculation_time");
    valid_parameters.emplace_back("--show_step_counts", "Shows the amount of saturated pushes, unsaturated pushes and relabels. Usage: --show_step_counts");

    return valid_parameters;
}

void show_helptext() {
    auto valid_parameters = parameters_with_description2();
    // get a nice spacing in between
    size_t min_space_size = 8;
    size_t max_param_length = (*max_element(valid_parameters.begin(),valid_parameters.end(), [](
        pair<string, string> i1, pair<string, string> i2) { 
        return i1.first.length() < i2.first.length();
    })).first.length();
    size_t description_start = min_space_size + max_param_length;

    cout << "Usage: exe [--console|--infile] [OPTIONS]" << endl;
    cout << endl;
    cout << "Options:" << endl;
    for (auto param_iter=valid_parameters.begin(); param_iter!=valid_parameters.end(); ++param_iter) {

        cout << param_iter->first << string(description_start - param_iter->first.length(), ' ') << param_iter->second << endl;
    }
}


map<string,string> parse_parameters(int argc, char** argv) {
    map<string,string> parameters;
    for(int i = 0; i < argc; ++i) {
        string arg = argv[i];

        string param = "";
        string data = "";

        size_t found = arg.find("=");
        if(found == -1) {
            param = arg;
        } else {
            param = arg.substr(0, found);
            data = arg.substr(found+1, arg.length());
        }

        parameters[param] = data;
    }
    return parameters;
}