#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SOUND_FILE "/home/hakob/mixkit-alert-alarm-1005.wav"

void(*ptr)(int);

void sigalrm_handle(int sig){
	pid_t pid = fork();
	if(pid < 0) {
		printf(" \a ");
	}else if(pid == 0){
		execlp("aplay","aplay",SOUND_FILE,(char*)NULL);
		printf("execlp failed");
		printf("\a");
		exit(EXIT_FAILURE);
	}else{
		int status;
		waitpid(pid,&status,0);
	}
}
int main(){
	unsigned int seconds;
	printf("Enter seconds for alarm");
	if(scanf("%u",&seconds)!=1){
		printf("wrong input");
		return EXIT_FAILURE;
	}
	ptr=sigalrm_handle;
	if(signal(SIGALRM,ptr)==SIG_ERR){
		printf("signal failed");
		return EXIT_FAILURE;
	}
	alarm(seconds);
	printf("Alarm is set for %u seconds",seconds);
	pause();
	return 0;
}


