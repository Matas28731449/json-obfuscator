#ifndef UTILS_HPP
#define UTILS_HPP

#include "nlohmann/json.hpp"
#include <sstream>
#include <fstream>

using json = nlohmann::ordered_json;
using std::stringstream;
using std::string;
using std::hex;
using std::setw;
using std::move;
using std::setfill;
using std::ifstream;
using std::ofstream;

#endif