#pragma once

#include "ofTypes.h"
#include "ofThread.h"
#include <string>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>

#define MAX_LOG_TAIL_SIZE 150

struct popen2 {
    pid_t child_pid;
    int   from_child, to_child;
};

class luvSC : private ofThread {

  public:    
    
    struct popen2 kid;
    char buffer[1000];
    std::string result = "";
    
    void init() {
       startThread();
    }
    
    void evaluate(std::string eval) {
        eval += "\x0c";  
        write(kid.to_child, eval.c_str(), eval.length());  
    }
    
    int popen2(const char *cmdline, struct popen2 *childinfo) {
        pid_t p;
        int pipe_stdin[2], pipe_stdout[2];

        if(pipe(pipe_stdin)) return -1;
        if(pipe(pipe_stdout)) return -1;
        
        p = fork();
        if(p < 0) return p;
        if(p == 0) {
            close(pipe_stdin[1]);
            dup2(pipe_stdin[0], 0);
            close(pipe_stdout[0]);
            dup2(pipe_stdout[1], 1);
            execl("/bin/sh", "sh", "-c", cmdline, 0);
            perror("execl"); exit(99);
        }
        childinfo->child_pid = p;
        childinfo->to_child = pipe_stdin[1];
        childinfo->from_child = pipe_stdout[0];
        return 0; 
    }
    
    void threadedFunction(){
      popen2("sclang -i sced", &kid);
      while(1) {
        memset(buffer, 0, 1000);
        if(read(kid.from_child, buffer, 1000) > 0) {
            result += buffer;
            result = result.substr(std::max<int>(result.length()-MAX_LOG_TAIL_SIZE,0));
        }
        sleep(200);    
      }
      close(kid.from_child);
      stopThread();
    }

};
