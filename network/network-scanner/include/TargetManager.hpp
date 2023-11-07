#ifndef __TARGET_MANAGER_H__
#define __TARGET_MANAGER_H__
#include "Common.hpp"
#include "Target.hpp"

// generate all targets
class TargetManager {
    private:
        string addr;
        string mask;
        int port;
        int pnum;
        vector<string> subnets;
        vector<Target> targets;
    public:
        TargetManager(string &addr_given, string &mask_given, string &port, string &pnum);
        void scan_all_targets();
};


#endif