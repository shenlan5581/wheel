#include <unistd.h>
#include <signal.h>
#include <iostream>
#include "pthread_pool.h"
#include "log.h"

namespace k {
using namespace std;
static int MAX_PTHREADS =4;
static int MAX_JOBS =10000;

/*
1 set signal for sigpipi
2 initialize mutex and cond
*/
int Pthread_pool::Init() {
signal(SIGPIPE,For_SIGPIPE);    // sigpipe

//MAX_PTHREADS =atoi((config->GetValue("max_pthreads")).c_str());
//MAX_JOBS =atoi((config->GetValue("max_Jobs")).c_str());

pthread_mutex_init(&mutex,NULL); 
pthread_cond_init(&no_empty,NULL);

// for quere
point = NULL;   
reac  = NULL;  
Job_count = 0;
int err = create_pthread();  //call function  create_pthread
if(err){
  cout<<"#pthread pool init success:Max pthreads "<<MAX_PTHREADS<<" jobs:"<<MAX_JOBS<<endl; //test
  log_info("pthread pool init success");
  return 0;
} else { 
  cout<<"#pthread pool init failed"<<endl; //test
  log_error("pthread pool init failed");
  return -1;
}
}
// create pthread
int Pthread_pool::create_pthread() {
 int i,err;
 for(i =0;i<MAX_PTHREADS;i++) {
    pthread_t id;
    pthread_create(&id,NULL,P_Function,this);
    save_ID.push_back(id);
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
