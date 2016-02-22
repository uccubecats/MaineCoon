// Multithreading implementation

void *altimeterMonitor(void *mux){
  // Cast mux from void pointer to class
  Mux* altimeter = (Mux *) mux;
  // Infinite loop for constant retrieval of temperatures and setting to global variables
  while(true){
    // All retrievals. Setting to globals is handled by function.
    altimeter -> getTemperature(0);
    altimeter -> getTemperature(1);
    altimeter -> getPressure(0);
    altimeter -> getPressure(1);
    altimeter -> getOrientation(0);
    // Selects different delay function based off of POSIX/UNIX (__GNUC__) or Windows _WIN32
    #ifdef __GNUC__
    // usleep: microseconds (1,000,000 per second)
    usleep(delayTime * 1000);
    #endif
    #ifdef _WIN32
    // Sleep: milliseconds (1,000 per second), casts to DWORD
    Sleep(<static_cast>(DWORD)delayTime);
    #endif
    // Prints all globals
    cout << "\n" << temperatureInside << " " << temperatureOutside
         << " " << pressureInside << " " << pressureOutside
         << " " << orientation << endl;
  }
  return;
}

pthread_t initializeAltimeterThread(){
  // Initializes pthread construct to store thread address
  pthread_t threads[1];
  // Error code
  int rc = 0;
  // Initializes altimeter mux
  Mux* mux = new Mux();
  /* Create thread (thread construct, thread configuration,
   * argument passed to function)
   */
  rc = pthread_create(&threads[1], NULL, altimeterMonitor, (void *)mux);
  if (rc){
    printf("Error; return code is %d\n", rc);
    return 1;
  }
  // Return thread construct to be used by caller
  return threads;
}