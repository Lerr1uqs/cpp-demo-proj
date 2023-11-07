#include <iostream>
#include <string>
#include <bitset>
#include "ArgParser.hpp"
#include "Target.hpp"
#include "TargetManager.hpp"

using std::cout;
using std::endl;
using std::string;

void test_bs() {
    using std::bitset;
    bitset<8> bs;
    bs.reset();

    bs.set(1);
    cout << bs[1] << endl;
}

// void test_target(int argc, char** argv) {
//     // test_bs();
//     auto argparser = ArgParser(argc, argv);
//     Target target(argparser.get_arg(string("address")));
//     target.test_all_ports()
//           .generate_report();
//     cout << "hello world!" << endl;
// }

void test_TargetManager(int argc, char** argv) {

}

int main(int argc, char** argv)
{
    auto argparser = ArgParser(argc, argv);

    auto addr = argparser.get_arg("address");
    auto mask = argparser.get_arg("mask");
    auto port = argparser.get_arg("port");
    auto pnum = argparser.get_arg("num");// 端口从port开始到port+pnum

    TargetManager tm(addr, mask, port, pnum);    
    tm.scan_all_targets();
    
    return 0;
}
