#include "request.cpp"
#include "webserver.cpp"
#include "LoadBalancer.cpp"

#include <iostream>
#include <ctime>
#include <cstdlib> //for random
#include <sstream> 
using namespace std;


request genRandRequest(int range_task_time) {
    //source string and destination string for IP addresses
    stringstream ip_source, ip_dest;
    request r;
    //ip addresses are octet of 255 possibilities 
    ip_source << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256);
    ip_dest << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256);

    r.source = ip_source.str();
    r.destination = ip_dest.str();
    r.processTime = rand()%range_task_time; //can take up to 200 units of time to process webpage

    return r;
}

int main() {

    int num_clock_cycles;
    int num_servers;
    int range_task_time;
    cout << "Enter number of webservers: ";
    cin >> num_servers;
    cout << "Enter number of clock cycles: ";
    cin >> num_clock_cycles;
    cout << "Enter range of task time for request to be completed: ";
    cin >> range_task_time;

    //random number generator - srand
    srand(time(0));
    LoadBalancer lb;

    //start with a "full" queue
    for (int i = 0; i < 700; i++) {
        request r  = genRandRequest(range_task_time);
        lb.addNewReq(r);
    }

    cout << "Starting queue size: " << lb.getQueueSize() << endl;

    //set an array of webservers
    webserver webarray[num_servers];
    for (int i = 0; i < num_servers; i++) {
        int rand_askii = i + 65;
        webserver w((char)(rand_askii)); //65 because askii - initializing name of webserver
        webarray[i] = w;
        //get time of lb (start time for webserver) so we can keep track of when request is finished
        webarray[i].addNewReq(lb.getRequest(), lb.currTime());
    }
    
    while (lb.currTime() < num_clock_cycles) {
        //exit loop once queue becomes empty
        if (lb.isRequestQueueEmpty()) {
            break;
        }

        int currTime = lb.currTime();

        //check each webserver if it's done.
        if (webarray[currTime % num_servers].isRequestDone(currTime)) {
            request r = webarray[currTime % num_servers].getRequest();
            cout << "At " << currTime << " " << webarray[currTime % num_servers].getServerName() << " finished processing request from " << r.source << " to " << r.destination << endl;
            //now that webserver is done, give a new request from lb
            webarray[currTime % num_servers].addNewReq(lb.getRequest(), currTime);
        }
        
        //every random number amount of time, we need to stimulate getting new requests
        //1/10 time in loop we add a request
        int rand_iteration = rand() % 10;
        if (rand_iteration == 0) {
            request r = genRandRequest(range_task_time);
            lb.addNewReq(r);
        }
        //need to inctime for iteration for loop
        lb.incTime();

    }

    cout << "Remaining queue size: " << lb.getQueueSize() << endl;

    return 0;

}

