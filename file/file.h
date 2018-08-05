/*
*  operation for file
*/
// 缓冲区长度
#pragma once
#include <string>
#include <iostream>

namespace File{
using namespace std;

class File{
   public:
    virtual string GetContent()=0;
    virtual int Addition(string str)=0;
    virtual int Change(string str,int len,int seek)=0;
};
/* 
* This when you instating a new object It need a file path
* And it only one file object represent , 
* all operate just only for this file
*/

class File_S: public File{
   public:
            File_S(string path); 
            ~File_S(); 
    virtual string GetContent();
    virtual int Addition(string str);
    virtual int Change(string str,int len,int seek);
   private:
    struct CHAR {
         CHAR * next; 
         int    seek;
         char   str;
    };

    class model{
        public:
              model(const char* path);
              ~model();
					CHAR * GetContent();
					int Addition(const char *str,int len);
          int File_S::model::Change(const char *str,int len,int seek , int size);
        private:
          CHAR *content;
          CHAR *end;
          int  model_len;
          int  fd;
 
          int push(char c,int i);
          int build();         
          int Save();         
          int Clean();         
          int find(int);         
    };
    model * obj;
};





}//namespace end
