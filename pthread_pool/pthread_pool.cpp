

#include <unistd.h>
#include <signal.h>
#include <iostream>
#include "pthread_pool.h"

namespace PTHREAD{
using namespace std;
/*
* set signal for sigpipi
* initialize mutex and cond
*/

Pthread_pool::Ptheead_pool(int maxjobs,int maxthreads)::
               MaxJobs(maxjobs),MaxThreads(maxthreads){} 

//Return:flag it's a number of how many thread created
int Pthread_pool::Init() {
    signal(SIGPIPE,For_SIGPIPE);
    pthread_mutex_init(&mutex,NULL); 
    pthread_cond_init(&no_empty,NULL);
  return create_pthread();
}

int Pthread_pool::create_pthread() {
    pthread_t id;
    for(int i = 0;i < MaxThreads;i++) {
       if(pthread_create(&id,NULL,P_Function,this)=0)
          PID.push_back(id);
       else
          break;
    }
  return i;
}

void * Pthread_pool::P_Function(void * obj) {   
       Pthread_pool *pool = (class Pthread_pool*)obj;     
      while(1) {   
         pthread_mutex_lock(&pool->mutex);
         while(pool->Job.empty()) {         
           pthread_cond_wait(&pool->no_empty,&pool->mutex);        
         }
         ???? = pool->Job.front();           // get work from queue
         pool->Job.pop();
         pthread_mutex_unlock(&pool->mutex);   // free mutex
         pthread_cond_signal(&pool->no_empty); // send signal
         OBJ * job = cur_Job->obj;
         job->handler();
         delete job;
         delete cur_Job; 
     }
} 

int Pthread_pool::Add_Work(OBJ *obj,void *arg) {      
    if(save_ID.empty())
       return -1;
    if(Job_count == MAX_JOBS)
       return  -1;  // pool is full
    Job * node = new Job;             
    node->obj =obj ;
    node->arg = arg; 
    pthread_mutex_lock(&mutex);
    if(point == NULL) {    //queue empty
        point = node;    
        node->next = point;         
    } else {               //
        node->next = point->next;    //新节点指向   队列头
        point->next = node;          //添加到当前节点的下一个
        point = node;                //重新定位指针
    } 
   Job_count++;    
   pthread_mutex_unlock(&mutex);
   pthread_cond_signal(&no_empty);  
   log_debug("current Job_count %d",Job_count);  
   return 1;
}

Job * Pthread_pool::Pop_work() {    
     Job * work ;
     if(point == point->next) { //last work
         work = point ;
         point = NULL;
         Job_count=0;
         return work;        
     } else {
           work = point->next;
           point->next = work->next;
           Job_count--;
     }
     return work;
}

Pthread_pool::~Pthread_pool() {  
  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&no_empty);
}

/*
when the socket closed
*/
void Pthread_pool::For_SIGPIPE(int n) { 
log_warn(" signal SIGPIPE");
}

} // namespace end
