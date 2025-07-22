/****************************************
 ********      Include files     ********
 ****************************************/

#include <io.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
/****************************************
 ********      Enumerations      ********
 ****************************************/

// The type of arguments supported
typedef enum {
	  IsString      = 0x1,
	  IsInteger     = 0x2,
	  IsHexidecimal = 0x3,
	  IsNone        = 0x4,
	  Invalid       = 0x5

} argTypes_e;


/****************************************
 ********       Structures       ********
 ****************************************/
typedef struct {
    char        *token;
	argTypes_e   type;
	bool         found;
	void        *value;

} argDesc_t;

/****************************************
 ********       Prototypes       ********
 ****************************************/
argDesc_t *
parseArgs ( int, char **, argDesc_t *, int );
