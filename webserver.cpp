#ifndef REQUEST_CPP
#include "request.cpp"
#endif

class webserver {

    private:
        request r;
        int reqStartTime;
        char serverName;
        
    public:
        webserver() {
            reqStartTime = 0;
            serverName = ' ';
        }
        //creates a webserver with a specific name - 2 constructors total
        webserver (char c) {
            reqStartTime = 0;
            serverName = c;
        }

        char getServerName() {
            return serverName;
        }
        void addNewReq(request req, int currTime) {
            r = req;
            reqStartTime = currTime;
        }
        request getRequest() {
            return r;
        }

        //will be used to determine when to add another request to server
        bool isRequestDone(int currTime) {
            return (currTime >= (reqStartTime + r.processTime));
        }

};