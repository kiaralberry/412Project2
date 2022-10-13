#ifndef LOADBALANCER_H
#include "LoadBalancer.h"
#endif

int LoadBalancer::currTime() {
    return lbTime;
}

void LoadBalancer::incTime() {
    lbTime = lbTime + 1;
}

void LoadBalancer::addNewReq(request r) {
    reqsQueue.push(r);
    incTime(); //takes time to put in queue
}

request LoadBalancer::getRequest() {
    //check if any in queue
    incTime();
    if (reqsQueue.size() != 0) {
        request r = reqsQueue.front();
        reqsQueue.pop();
        return r;
    }
    
}

bool LoadBalancer::isRequestQueueEmpty() {
    if (reqsQueue.size() == 0) {
        return true;
    }
    return false;
}

int LoadBalancer::getQueueSize() {
    return reqsQueue.size();
}


