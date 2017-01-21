#include <stddef.h>
#include <kernel.h>

  /*Global variable for producer consumer*/
   extern int n; /*this is just declaration*/

  /*function Prototype*/
  void consumer(int count);
  void producer(int count);

  /* Semaphore Declaration */
  extern sid32 produced,consumed;
