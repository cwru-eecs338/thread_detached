#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int MAX=5;
inline int my_rand(int, int);
void *say_it(void *);

int main(int argc, char *argv[]){
	pthread_t thread_id[MAX];
	int status, *p_status=&status;
	int i;
	pthread_attr_t attr_obj;
	pthread_attr_init(&attr_obj);
	pthread_attr_setdetachstate(&attr_obj, PTHREAD_CREATE_DETACHED);

	if(argc>MAX+1){
		printf("%s arg1, arg2, ..., arg %d\n",*argv,MAX);
		return 1;
	}
	printf("Displaying\n");
	for(i=0;i<argc-1;++i){
		if(pthread_create(&thread_id[i],NULL,say_it,(void *)argv[i+1])>0){
//		if(pthread_create(&thread_id[i], &attr_obj, say_it, (void *)argv[i+1])>0){
			printf("pthread_create failure\n");
			return 2;
		}
	}
	pthread_detach(thread_id[2]);
	for(i=0;i<argc-1;++i){
		if(pthread_join(thread_id[i],(void **)p_status)>0){
			printf("pthread_join failure\n");
			return 3;
		}
		printf("\nThread %u returns %d",(unsigned int)thread_id[i],status);
	}
	
	printf("\nDone\n");
	return 0;
}

void *say_it(void *word){

	int numb=5;
	int j;
	printf("%s \t to be printed %d times.\n",(char *)word, numb);
	for(j=0;j<numb;++j){
		sleep(1);
		printf("%s ",(char *)word);
		fflush(stdout);
	}
	return (void *)NULL;
}

