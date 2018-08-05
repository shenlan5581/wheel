#include <fcntl.h>
#include <unistd.h>

#include "file.h"

namespace File{

File_S::File_S(string path){
  obj = new model(path.c_str());
}
File_S::~File_S(){
  delete obj;
}
string File_S::GetContent(){
   CHAR *p = obj->GetContent(); 
   string str;
   p=p->next;
   while(p !=nullptr){
     str=str+(p->str);
     p = p->next;
   }
   return str;
};

int File_S::Addition(string str){
   return  obj->Addition(str.c_str(),str.length());
};
int File_S::Change(string str,int len,int seek){
   return  obj->Change(
};



// inside file;
File_S::model::model(const char * path){
  fd = open(path,O_RDWR);
  if(fd)
    build();
}
File_S::model::~model(){
  if(fd){
     close(fd); 
  }
}

File_S::CHAR* File_S::model::GetContent(){
   return content;
}
/*
* addition str to the end of content
*/
int File_S::model::Addition(const char *str,int len){
    int i;
    for(i=0;i<len;i++){
       push(str[i],model_len+i);  
    }
    model_len+=i;
 return i;
}
/*
*  str:a new str you need to change
*  len:length of str
*  len:a position of you need to change
*  size:change length on the  old contnet
*/
int File_S::model::Change(const char *str,int len,int seek , int size){
    CHAR * p = find(seek);
    if(p){
       //pause    


    }

}
//build model from file
int File_S::model:: build(){
    int flag,i=0;
    char buf;
    content = new struct CHAR;
    end = content;
    end->seek=-1;
    end->next=nullptr;
    while(1){
      flag = read(fd,&buf,1);
      if(flag == 1 ){
        push(buf,i);
        i++;
      } else {
        model_len =i; 
        break;
      }
   }
}
int File_S::model::push(char c,int i){
    end->next = new struct CHAR;
    end=end->next;
		end->next=nullptr;
		end->seek=i;
		end->str=c;
}
CHAR * File_S::model::find(int seek){
    CHAR * p=content; 
    while( p !=nullptr && p->seek != seek ){
      p = p-next;
    }
    return p;                                                      
}

}//namespace end
