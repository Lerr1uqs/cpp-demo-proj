#include "ArgParser.hpp"
using std::runtime_error;

ArgParser::ArgParser(int argc, char *argv[]) {
    string addr = "127.0.0.1";
    string mask = "255.255.255.0";
    args_list["address"] = addr;
    args_list["mask"] = mask;

    vector<string> args(argv + 1, argv + argc);

    for (size_t i = 0; i < args.size(); ++i) {
        if (args[i] == "-a" or args[i] == "--address") {
            // check whether have next argu
            if (i + 1 >= args.size()) {
                throw runtime_error("Missing argument for option " + args[i]);
            }
            args_list["address"] = args[++i];
        } else if (args[i] == "-m" or args[i] == "--mask") {
            // check whether have next argu
            if (i + 1 >= args.size()) {
                throw runtime_error("Missing argument for option " + args[i]);
            }
            args_list["mask"] = args[++i];
        } else if (args[i] == "-p" or args[i] == "--port") {
            // check whether have next argu
            if (i + 1 >= args.size()) {
                throw runtime_error("Missing argument for option " + args[i]);
            }
            args_list["port"] = args[++i];
        } else if (args[i] == "-n" or args[i] == "--num") {
            // check whether have next argu
            if (i + 1 >= args.size()) {
                throw runtime_error("Missing argument for option " + args[i]);
            }
            args_list["num"] = args[++i];
        } else {
            throw runtime_error("Unknown option " + args[i]);
        }
    }
}

// get argument by name
string ArgParser::get_arg(string s) {
    return args_list[s];
}