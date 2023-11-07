#ifndef __ARG_PARSER_H__
#define __ARG_PARSER_H__
#include <map>
#include <string>
#include <vector>
#include <iostream>

using std::map;
using std::string;
using std::vector;
using std::cerr;
using std::endl;

class ArgParser {
    private:
        map<string, string> args_list;
    public:
        ArgParser(int argc, char *argv[]);
        string get_arg(string s);
};


#endif