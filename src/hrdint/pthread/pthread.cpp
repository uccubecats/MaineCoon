// PThread testing implementation

#include <pthread.h>
#include <stdio.h>

const static int NUM_THREADS = 5;
int value = 0;


void *printHello(void *threadid){
  while(true){
    int tid = (int)threadid;
    value = tid;
    printf("Woo! #%d\n", tid);
  }
}

int main(int argc, char *argv[]){
  pthread_t threads[NUM_THREADS];
  int rc = 0;
  for(unsigned int i = 0; i < NUM_THREADS; i++){
    printf("Creating thread %i\n", i);
    rc = pthread_create(&threads[i], NULL, printHello, (void *)i);
    printf("Value: %i\n", value);
    pthread_cancel(threads[i]);
    if (rc){
      printf("Error; return code is %d\n", rc);
      return 1;
    }
  }
  pthread_exit(NULL);
  return 0;
}