#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

// streams
#include <iostream>

// containers & algorithms
#include <algorithm>
#include <map>

// types
#include <string>


void show_helptext(); 

std::map<std::string,std::string> parameters_with_description();

std::map<std::string,std::string> parse_parameters(int argc, char** argv);

#endif // CONFIG_H_INCLUDED