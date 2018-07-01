#pragma once
#include <pthread.h>
#include <vector>
#include "config.h"
#include "http_client.h"
namespace k{
using std::vector;
typedef vector<pthread_t> PTHREADS;

/* 
线程池内置了一个队列 保存工作队列
由 两个 Job指针记录
class Job 为队列节点
*/
/*

扩展的方法 
1  将要添加进队列的类型typdef ** OBJ


2  类型里面要有一个虚函数
   handler(); 
   线程会自动调用此函数

  咱不能传参 参数先放对象中以后再改

*/
typedef  Http_Handler OBJ;
class Job; 
class Pthread_pool {
public:
   int Init();
   // must call Init() before use Add_work
   int Add_Work(OBJ*obj,void *arg);
private:
   PTHREADS  save_ID; //save pthread ID
   Job  *  point;   
   Job  *  reac;   

   pthread_mutex_t mutex;
   pthread_cond_t  no_empty;

   int Job_count; 
   int create_pthread();
   Job* Pop_work();

public:
static void * P_Function(void *);
static void   For_SIGPIPE(int n);     
~Pthread_pool();
};
//   node for Job queue
class Job {
public:
  OBJ  *obj;
  void  *arg;
  Job * next; 
};

} //namespace
