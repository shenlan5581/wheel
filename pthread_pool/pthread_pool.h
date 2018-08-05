/*
* This is a simple thread pool
* Inside it is a queue that saves working objects.  
* The default processing macro specifies the function that will be called in the thread, 
* Of course, you can reassign it.
* When instancing you must specifies max jobs and max pthreads in addition call Init()
* It will create threads and complete the initialization.
* When
*/
#pragma once
#include <pthread.h>
#include <vector>
#include <queue>

namespace PTHREAD{
//in process this function will be calling
#define DEFAULT_HANDLE handle()
using std::vector;
using std::queue;
//the vector for save pid
class Pthread_pool {
 public:
    Pthread_pool(int MaxJob,int Maxthread);
   ~Pthread_pool();
    int Init();    
    int Add_Work(void *obj);
 private:
    int  MaxJobs
    int  MaxThreads
    vector<pthread_t>   PID;   //save pthread ID
    queue<void*>        Job;   //job queue

    pthread_mutex_t mutex;
    pthread_cond_t  no_empty;
    int create_pthread(); 
 public:
    static void * P_Function(void *);   //thread function
    static void   For_SIGPIPE(int n);   //ignore this signal
};

} //namespace
