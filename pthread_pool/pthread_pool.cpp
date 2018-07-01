

#include <unistd.h>
#include <signal.h>
#include <iostream>
#include "pthread_pool.h"

namespace PTHREAS{
using namespace std;
/*
* set signal for sigpipi
* initialize mutex and cond
*/

Pthread_pool::Ptheead_pool(int maxjobs,int maxthreads)::MaxJobs(maxjobs),MaxThreads(maxthreads){} 

int Pthread_pool::Init(int maxjobs,int maxthreads) {
 signal(SIGPIPE,For_SIGPIPE);    // sigpipe
 pthread_mutex_init(&mutex,NULL); 
 pthread_cond_init(&no_empty,NULL);
 // for quere
 int flag = create_pthread();  //call function  create_pthread
 if(!flag){
   cout<<"#pthread pool init failed"<<endl; //test
   return -1;
 }
}
// create pthread
int Pthread_pool::create_pthread() {
 int i,err;
 for(i =0;i<MaxThreads;i++) {
    pthread_t id;
    pthread_create(&id,NULL,P_Function,this);
    PID.push_back(id);
}
return 1;
}

// static 
void * Pthread_pool::P_Function(void * obj) {   
class Pthread_pool *pool = (class Pthread_pool*)obj;     
  Job *  cur_Job = NULL;
while(1) {   
      pthread_mutex_lock(&pool->mutex);
      while((pool->point)==NULL) {         
           pthread_cond_wait(&pool->no_empty,&pool->mutex);        
         }
         cur_Job = pool->Pop_work();           // get work from queue
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
