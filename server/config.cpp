#include "config.hpp"

bool INGAME_TIME = 0;
int32_t TURNTIME = 600; // 10 minutes
uint32_t MAX_CLIENTS = 32;
uint16_t PORT = 1234;

#include <iostream>
#include <fstream>
#include <vector>
using namespace std; // iostream heavy

vector<string> split(const char *str, char c = ' ')
{
    vector<string> result;
    do {
        const char *begin = str;

        while(*str != c && *str)
            str++;

        result.push_back(string(begin, str));
    } while (0 != *str++);

    return result;
}

bool load_text_file()
{
	ifstream f("data/init/webfort.txt");
	if (!f.is_open()) {
		cerr << "Webfort failed to open config file, skipping." << endl;
		return false;
	}

	string line;
	while(getline(f, line)) {
		size_t b = line.find("[");
		size_t e = line.rfind("]");

		if (b == string::npos || e == string::npos || line.find_first_not_of(" ") < b)
			continue;

		line = line.substr(b+1, e-1);
		vector<string> tokens = split(line.c_str(), ':');
		const string& key = tokens[0];
		const string& val = tokens[1];

		if (key == "PORT") {
			PORT = (uint16_t)std::stol(val);
		}
		if (key == "TURNTIME") {
			TURNTIME = (int64_t)std::stol(val);
		}
		if (key == "MAX_CLIENTS") {
			MAX_CLIENTS = (uint32_t)std::stol(val);
		}
		if (key == "INGAME_TIME") {
			INGAME_TIME = val == "YES";
		}
	}
	return true;
}

bool load_env_vars()
{
    char* tmp;
	if ((tmp = getenv("WF_PORT"))) {
		PORT = (uint16_t)std::stol(tmp);
	}
	if ((tmp = getenv("WF_TURNTIME"))) {
		TURNTIME = (int64_t)std::stol(tmp);
	}
	if ((tmp = getenv("WF_MAX_CLIENTS"))) {
		MAX_CLIENTS = (uint32_t)std::stol(tmp);
	}
	if ((tmp = getenv("WF_INGAME_TIME"))) {
		INGAME_TIME = std::stol(tmp) != 0;
	}
	return true;
}

bool load_config()
{
	return load_text_file() && load_env_vars();
}
