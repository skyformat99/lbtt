#ifndef __WORKER_H__
#define __WORKER_H__

#include <iostream>
#include <fcntl.h>
#include <ev++.h>
#include <queue>
#include <sstream>
#include "Tracker.h"
#include "scoped_lock.hpp"

using namespace std;

class Worker{
public:
        Worker(Tracker &);
        void run();
        void add_session(int cfd);
        void idle(ev::idle &,int);
        void pqueue(ev::async &,int);
        void process(ev::io &,int);
		stringstream m_output;
protected:
        void closecleanup(ev::io &);
		bool processRequest(ev::io &);
		bool setError(const char *);
        std::queue<int> que;
        ev::async asyncw;
        ev::idle idlew;
        ev::dynamic_loop loop;
        pthread_mutex_t io_mutex ;
		ssize_t nread;
        char m_read_b[4 << 10]; //thanks xbtt :)
        
		Request req;
		Tracker &m_tracker;
};

#endif