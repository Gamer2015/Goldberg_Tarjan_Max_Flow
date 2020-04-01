#include "config.h"



std::map<std::string,std::string> parameters_with_description() {
    std::map<std::string,std::string> valid_parameters;
    valid_parameters["--infile"] = "usage: --file=\"text.txt\"";
    valid_parameters["--console"] = "usage: Write lines as input that would represent the data as we would have them in the input-file. Write \"end\" to finish data input.";

    valid_parameters["--outfile"] = "usage: --outfile=\"output.txt\"";
    valid_parameters["--show_max_flow"] = "usage: --show_max_flow";
    valid_parameters["--show_min_cut"] = "usage: --show_min_cut";
    valid_parameters["--show_calculation_time"] = "usage: --show_calculation_time";
    valid_parameters["--show_step_counts"] = "usage: --show_step_counts";

    return valid_parameters;
}

void show_helptext() {
    auto valid_parameters = parameters_with_description();
    // get a nice spacing in between
    std::size_t min_space_size = 8;
    std::size_t max_param_length = (*std::max_element(valid_parameters.begin(),valid_parameters.end(), [](
        std::pair<std::string, std::string> i1, std::pair<std::string, std::string> i2) { 
        return i1.first.length() < i2.first.length();
    })).first.length();
    std::size_t description_start = min_space_size + max_param_length;

    std::cout << "max param length: " << max_param_length << std::endl;
    std::cout << "Usage: exe [--file | --console]" << std::endl << std::endl;

    for (auto param_iter=valid_parameters.begin(); param_iter!=valid_parameters.end(); ++param_iter) {
        std::cout << param_iter->first << std::string(description_start - param_iter->first.length(), ' ') << param_iter->second << std::endl;
    }
}


std::map<std::string,std::string> parse_parameters(int argc, char** argv) {
    std::map<std::string,std::string> parameters;
    for(int i = 0; i < argc; ++i) {
        std::string arg = argv[i];

        std::string param = "";
        std::string data = "";

        std::size_t found = arg.find("=");
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