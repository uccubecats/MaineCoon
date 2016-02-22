#include <pthread.h>
#include <stdio.h>
#include "tempPress.h"
#include "threads.h"
#include <iostream>

// Time for delay in ms
const static unsigned long delayTime = 250;

void *altimeterMonitor(void *mux);
pthread_t initializeAltimeterThread();