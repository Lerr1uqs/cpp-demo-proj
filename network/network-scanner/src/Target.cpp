#include "Target.hpp"
#include <arpa/inet.h>
#include <sys/select.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>


namespace {
    // mutex alarm_mutex;// 多线程连接 connect_timeout 但是单线程扫描的时候不允许别人再进入alarm
    // using std::lock_guard;

    // void connect_alarm(int sig) {
    //     return;
    // }

    // bool signaled = false;

    int connect_timeout(int sockfd, const sockaddr* paddr, socklen_t salen, int nsec) {
        
        int ret = 0;

        // 将 socket 设置为非阻塞模式
        int flags = fcntl(sockfd, F_GETFL, 0);
        fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);

        if ((ret = connect(sockfd, paddr, salen)) < 0) {
            if (errno == EINTR) {
                errno = ETIMEDOUT;
            }
        }

        // 尝试连接
        ret = connect(sockfd, paddr, sizeof(paddr));
        if (ret == 0) {
            // 连接成功，恢复 socket 的阻塞模式
            // cout << "连接成功，恢复 socket 的阻塞模式" << endl;
            fcntl(sockfd, F_SETFL, flags);
            return sockfd;
        } else if (ret < 0 && errno != EALREADY) {
            // 连接出错，可能是出错了
            close(sockfd);
            return -1;
        }

        // 准备超时时间
        struct timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = 100000; // 0.1秒

        // 设置 select 监听的文件描述符集
        fd_set writefds;
        FD_ZERO(&writefds);
        FD_SET(sockfd, &writefds);

        // 监听连接是否已建立
        ret = select(sockfd + 1, NULL, &writefds, NULL, &tv);
        if (ret <= 0) {
            // 超时或出错
            close(sockfd);
            return -1;
        }

        // 连接已经建立，恢复 socket 的阻塞模式
        fcntl(sockfd, F_SETFL, flags);
        return ret;
    }
}

Target::Target(string _ip, int _port, int _pnum) 
    : port(_port), pnum(_pnum), ip(_ip), bs(_pnum, false)
{}

// test whether this port is open
fn Target::test_one(i32 port) -> bool {

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        cerr << "Failed to create socket" << endl;
        exit(1);
    }

    struct sockaddr_in target_addr;
    std::memset(&target_addr, '\x00', sizeof(target_addr));

    target_addr.sin_family = AF_INET;
    target_addr.sin_port = htons(port);
    inet_pton(AF_INET, self.ip.c_str(), &target_addr.sin_addr);

    bool successful = true;

    if (connect_timeout(sockfd, (struct sockaddr*)&target_addr, sizeof(target_addr), 1) < 0) {
        // std::cerr << "[-] timeout with ip " << self.ip << " port " << port << std::endl;
        successful = false;
    }

    close(sockfd);
    return successful;
}

fn Target::test_all_ports() -> Target& {

    for(usize p = self.port; p < self.port + self.pnum; p++) {
        bool is_open = test_one(p);
        if(is_open) {
            self.bs[p - self.port] = true;
        }
    }

    return self;
}

fn Target::generate_report() -> string {

    std::stringstream ss;

    for(usize p = self.port; p < self.port + self.pnum; p++) {

        if(self.bs[p - self.port]) {

            struct in_addr addr;
            inet_pton(AF_INET, self.ip.c_str(), &addr);


            struct hostent* host = gethostbyaddr(&addr, sizeof(addr), AF_INET);
            if(host == nullptr){
                cerr << "err ip is " << self.ip << endl;
                throw std::logic_error("Function not implemented");
            }

            ss << std::setw(25) << std::left << host->h_name
               << std::setw(15) << std::left << self.ip
               << std::setw(10) << std::left << p
               << endl;
        }
    }

    return ss.str();
}

fn Target::get_ip() -> string& {
    return self.ip;
}