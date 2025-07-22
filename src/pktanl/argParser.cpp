/****************************************
 ********  System Include files  ********
 ****************************************/
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/****************************************
 ********   Local Include files  ********
 ****************************************/
#include "argParser.h"

argDesc_t *
parseArgs ( int argc, char **argv, argDesc_t *desc, int count) {

  int argCnt  = 0;
  int descCnt = 0;

  bool Usage = true;

  // Does this request make sense?
  if ( count > 0 ) {

     // Loop over the args.  Skip argv[0] since it is the program name.
     // i.e. start at 1.
     for (argCnt=1; argCnt<argc && Usage;) {

        // Loop over our descriptors looking for a match
        for (descCnt=0; descCnt<count; descCnt++) {

           // Match?
           if ( !(strncmp(argv[argCnt],desc[descCnt].token,strlen(argv[argCnt]))) ) {

              // Good move to next arg and mark this one found.
              argCnt++;
              desc[descCnt].found = true;

              // What is the next arg:
              //      string - get memory and copy
              //      int    - convert
              //      next token (i.e. token flag only)
              switch (desc[descCnt].type) {
                case IsNone:
                   // Do nothing only mark present
                   break;
                case IsString:
                  // allocate memory and copy string
                  desc[descCnt].value = (void *)malloc (strlen(argv[argCnt])+1);
                  strcpy ((char *)desc[descCnt].value, argv[argCnt]);
                  argCnt++;
                  break;
                case IsInteger:
                  // allocate memory and copy string
                  desc[descCnt].value = (void *)malloc (sizeof(int));
                  *(int *)(desc[descCnt].value) = atoi(argv[argCnt]);
                  argCnt++;
                  break;
                case IsHexidecimal:
                  // allocate memory and copy string
                  desc[descCnt].value = (void *)malloc (sizeof(unsigned int));
                  sscanf ( argv[argCnt], "%x", (unsigned int *)(desc[descCnt].value));
                  argCnt++;
                  break;
                default:
                  // Error...
                  Usage = false;
                  break;
              }
              // Found item so bail this loop iteration.
              break;
           }
        }
     }
  } else {
     return NULL;
  }
  return desc;
}

