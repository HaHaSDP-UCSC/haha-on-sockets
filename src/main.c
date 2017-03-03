/* Main program */
#include "devtools.h"
#include "hahaProgram.h"
/* Base */
#include "basecomm.h"
#include "networkdevice.h"
/* Button */
#include "buttoncomm.h"
#include "buttondevice.h"
/* Other */
#include "storage.h"
#include "storagedevice.h"

/* The specifics of this part of the program will be different on the uC
*  We will probably register some interrupts and interrupt timers. For the
*  socket version we will have to poll.
*/

void init(){
   //Setup everything
   //Load stored information
   //
}


int main(int argc, char** argv){
   int error = FALSE; //correct this later
   //Initialize
   //Register interrupts

   //Forever Loop
   for(;;){
      //etc

   }


   return error;
}
