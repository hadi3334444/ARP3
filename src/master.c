#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


int spawn(const char * program, char * arg_list[]) {

  pid_t child_pid = fork();

  if(child_pid < 0) {
    perror("Error while forking...");
    return 1;
  }

  else if(child_pid != 0) {
    return child_pid;
  }

  else {
    if(execvp (program, arg_list) == 0);
    perror("Exec failed");
    return 1;
  }
}

int main() {
  printf("choose which mode you prefer\n");
  printf("1. Server Mode.\n2. Client Mode.\n3.Exit.\n"); 
  int ch;
  scanf("%d",&ch);
  if(ch==1){
      char * arg_list_A[] = {"/usr/bin/konsole", "-e", "./bin/processAs", NULL };
      char *  arg_list_B[] = { "/usr/bin/konsole", "-e", "./bin/processB", NULL };
      pid_t pid_procA = spawn("/usr/bin/konsole", arg_list_A);
      pid_t pid_procB = spawn("/usr/bin/konsole", arg_list_B);
  int status;
  waitpid(pid_procA, &status, 0);
  waitpid(pid_procB, &status, 0);
  printf ("Main program exiting with status %d\n", status);
  }else if(ch==2){
      char * arg_list_A[] = { "/usr/bin/konsole", "-e", "./bin/processAc", NULL };
      char *  arg_list_B[] = { "/usr/bin/konsole", "-e", "./bin/processB", NULL };
      pid_t pid_procA = spawn("/usr/bin/konsole", arg_list_A);
      pid_t pid_procB = spawn("/usr/bin/konsole", arg_list_B);
  int status;
  waitpid(pid_procA, &status, 0);
  waitpid(pid_procB, &status, 0);
  printf ("Main program exiting with status %d\n", status);
  }else{
      return 0;
  }
  

  
  
  
  return 0;
}

