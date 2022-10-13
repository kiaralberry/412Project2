#define LOADBALANCER_H_

#ifndef REQUEST_CPP
#include "request.cpp"
#endif

#include <iostream>
#include <queue>

using namespace std;


class LoadBalancer{
private:
    int lbTime;
    queue<request> reqsQueue;
public:
    LoadBalancer() {
        lbTime = 0;
    }
    int currTime();
    void incTime();
    void addNewReq(request r);
    request getRequest();
    bool isRequestQueueEmpty();
    int getQueueSize();
};
