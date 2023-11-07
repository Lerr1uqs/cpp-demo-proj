#ifndef __TARGET_H__
#define __TARGET_H__
#include "Common.hpp"
#include <arpa/inet.h>
#include <netdb.h>
#include <bitset>
#include <stdexcept>
#include <memory>
// using std::bitset;


class Target {
    // a network target for single IP and multi ports
    private:
        bool test_one(i32 port);
        string ip;
        static const u32 MAX_PORT_COUNT = 0x100;
        int port;
        int pnum;
        vector<bool> bs;
    public:
        Target(string ip, int port, int pnum);
        Target &test_all_ports();
        string generate_report();
        string &get_ip();
        // struct sockaddr_in sa;
};

#endif