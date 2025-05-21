1.Headers and Macros

        #include <stdlib.h>-for exit macros

        #include <unistd.h>-for fork,execlp,alarm,pause

        #include <signal.h>-for signal,SIGALRM
  
        #include <sys/types.h>-for pid_t

        #include <sys/wait.h>-for waitpid

        #define SOUND_FILE ""/home/hakob/mixkit-alert-alarm-1005.wav"-Defines the path to the sound file to play when the alarm triggers

2.Function Pointer

        void(*ptr)(int)-pointer that shows to a function which return type is void and gets an int as argument

3.Alarm-Handler Function-when SIGALRM is recieved,this function runs.
                         fork() creates a new process(pid<0-for failed,pid==0-child process,pid>0-parent process).
                         execlp is used for changing the process image with aplay to play the file.if fails,it prints an error and beeps(\a).
                         waitpid()-parent process waits for the child process to finish.
           
                        void alarm_handler(int sig) {
                        pid_t pid = fork();
                        execlp("aplay","aplay",SOUND_FILE,(char*)NULL);
                        waitpid(pid,&status,0);

4.Main Function`

                        ptr=sigalrm_handle; //assgns the handler to function pointer.
                        signal(SIGALRM,ptr); //registers it as handler for SIGALRM using signal()
                        alarm(seconds); //Schedules the alarm for seconds in the future
                        pause(); //suspends the process untill a signal is caught
