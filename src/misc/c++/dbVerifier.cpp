/***************************************************************************************/
// This class verifies the fields within the phone configuration file, ClarinoxBlue.cfg.
// The format of this file is broken into 4 fields per configuration line as follows:
// 
// Field 1:
//         One of the following textual tags:"BtAddr"
//                                           "LinkKey"
//                                           "LinkKeyType"
//                                           "DevName"
//                                           "DevClass0"
//                                           "DevClass1"
//                                           "DevClass2" 
//
// Field 2:
//        The '-' dash character
//         
// Field 3:
//        The '=' equal character
//
// Field 4:
//        The value associated with the named tag.
//
//                   e
//               d   q
//               a s u
//               s e a
//          tag  h q l    value
//          
// example: BtAddr-0 = 90a0e5b72dcc

#include <iostream>
#include <fstream>
#include <cstring>
#include "dbVerifier.hpp"

using namespace std;

// Constant values used to control phone/phone element status
//
    const int EMPTY_PHONE = 0;
    const int VALID_PHONE = 1;
    const int VALID_SPECIAL_PHONE = 2;
    const int INVALID_PHONE = 3;
    const int DUPLICATE_PHONE = 4;

    const int EMPTY_ELEMENT = 0;
    const int VALID_ELEMENT = 1;
    const int INVALID_ELEMENT = 2;
    const int DUPLICATE_ELEMENT = 3;

    const int NUM_ELEMENTS = 7;
    const int MIN_LINE_LENGTH = 10;
    const int MAX_DEVICE_NAME_SIZE = 240;

    const char *resetCode = "7877CFA6C0D8";
    const char *validEntries[NUM_ELEMENTS] = { "BtAddr-",
                                               "LinkKey-",
                                               "LinkKeyType-",
                                               "DevName-",
                                               "DevClass0-",
                                               "DevClass1-",
                                               "DevClass2-" };


// Data structure to hold the defined phone data structure 
// as well as the status of the element, (valid, invalid, duplicate...)
struct parsedLine {
  char  seq[5];
  char  name[25];
  char  value[250];
};

// Data structure to hold the defined phone data structure 
// as well as the status of the element, (valid, invalid, duplicate...)
struct phoneElement {
  int   valid;
  char  name[25];
  char  value[250];
};

// Data structure to define a list of phones uniquely identifief
// by the sequence number.
struct phone {
  int                  seq;
  int                  verified;
  struct phone        *next;
  struct phoneElement  phoneElements[NUM_ELEMENTS];
};
phone *phoneList;

// Constructor (init w/file path)
dbVerifier::dbVerifier(char *dbFile) {
  dbFilePath = dbFile;
  phoneList = NULL;
};

// Destructor (free phone list)
dbVerifier::~dbVerifier() {
  freePhoneList (phoneList);
};

// Validate a hexidecimal string
bool dbVerifier::isValidNumberString(char *str) {
  bool flag = VALID_ELEMENT;

  for (int i=0; i<(int)strlen(str); i++) {
    if (!isxdigit(str[i]) && !isspace(str[i])) {
      flag = 0;
      break;
    }
  }
  return flag;
}

// Validate an Extended ASCII string
bool dbVerifier::isValidString(char *str) {
  bool flag = VALID_ELEMENT;
  if (strlen(str) > MAX_DEVICE_NAME_SIZE) {
      flag = 0;
      cout << "Bad Device Name String" << endl;
  }
  return flag;
}

// Allocate a new phone data structure
//
phone *dbVerifier::makeNewPhone(phone *head, char *seqNum, char* ptr) {
   // If head is NULL we have reached the end of  // If head is NULL we have reached the end of the list
   // make a new phone.
   //
   if (head == NULL) {
    head = (phone *) malloc(sizeof(phone));
    memset (head, 0, sizeof(phone));
    head->seq = atoi(seqNum);
    head->next = NULL;
    head->verified = 0;
  } else {
    head->next = makeNewPhone(head->next, seqNum, ptr);
  }
  return head;
}

// Find a phone in the list using the sequence number of the phone
// as the key.
phone *dbVerifier::findPhone(phone *head, int element, char *seqNum, char *ptr) {
  int seq;
  phone *foundPhone;
  seq = atoi (seqNum);
  // If head is NULL we have reached the end of the list
  // return NULL.
  //
  if (head == NULL) {
    foundPhone = NULL;
  // If head->seq == seq then we have found the phone
  // return phone pointer.
  //
  } else if (head->seq == seq) {
    foundPhone = head;
  } else {
    foundPhone = findPhone (head->next, element, seqNum, ptr);
  }
  return foundPhone;
}

// Add a phone attribute to an existing phone or
// create a new phone if the sequence number is not found.
phone *dbVerifier::addToPhone(phone *head, int element, char *seqNum, char* ptr) {
  int seq;
  int valid;
  phone *thisPhone;

  // Find the phone associated with the sequence number.
  // if the phone is not found make a new phone and add 
  // the element to new phone
  //
  seq = atoi (seqNum);
  if ((thisPhone = findPhone (head, element, seqNum, ptr)) == NULL) {
    head = makeNewPhone(head, seqNum, ptr);
    thisPhone = findPhone (head, element, seqNum, ptr);
  }
  // Validate the value for the element.
  //
  strcpy (thisPhone->phoneElements[element].name, validEntries[element]);
  if (element == 3) {
    valid = isValidString(&ptr[0]);
  } else { 
    valid = isValidNumberString(&ptr[0]);
  }
  // assign the element if the element is empty (0)
  // else declare the element duplicate.
  if (thisPhone->phoneElements[element].valid == EMPTY_ELEMENT) {
    thisPhone->phoneElements[element].valid = valid;
    strcpy (thisPhone->phoneElements[element].value, &ptr[0]);
  } else {
    thisPhone->phoneElements[element].valid = DUPLICATE_ELEMENT;
    cout << "Found duplicate element for phone id: " << seq << " Entry: " << validEntries[element] << " value: " << ptr << endl;
  }
  
  return head;
}

// Print the list
phone *dbVerifier::printPhoneList(phone *head) {
  char valid[10];
  if (head == NULL) {
    return NULL;
  } else {
    for (int idx=0; idx<NUM_ELEMENTS; idx++) {
      if (*head->phoneElements[idx].name != 0) {
	strcpy(valid, (head->phoneElements[idx].valid == 1) ? "true" : "false");
        cout  << head->phoneElements[idx].name << head->seq << ": " << head->phoneElements[idx].value << " Valid => " << valid << endl;
      }
    }
    return printPhoneList(head->next);
  }
}

// Free the list
void dbVerifier::freePhoneList(phone *head) {
    if(head != NULL){
      freePhoneList(head->next);
      free(head);
    }
}

// Verify the list
int dbVerifier::verifyPhoneList(phone *head, int valid) {
  bool validPhone = INVALID_PHONE;
  if (head != NULL) {
    if (head->verified == VALID_SPECIAL_PHONE) {
      valid = VALID_PHONE;
    } else {
      for(int i=0; i<NUM_ELEMENTS; i++) {
        validPhone = (head->phoneElements[i].valid == VALID_ELEMENT);
        if (validPhone != 1) {
          valid = INVALID_PHONE;
          break;
        }
      }
      if (validPhone == 1) {
        head->verified = VALID_PHONE;
        valid = VALID_PHONE;
      }
      if (valid == VALID_PHONE) {
        valid = verifyPhoneList (head->next, valid);
      }
    }
  }
  return valid;
}

parsedLine *dbVerifier::parseLine (char *line) {
int len        = 0;

char *namePtr = NULL;
char *valPtr  = NULL;
char *seqPtr  = NULL;

parsedLine *parsed = NULL;

  if (line != NULL && strlen(line) != 0) {
    namePtr = line;
    valPtr  = strchr (line, *eqDelim);
    seqPtr  = strchr (line, *dashDelim);
    if (valPtr != NULL && seqPtr != NULL) {
      valPtr += 2;
      seqPtr += 1;
      parsed = (parsedLine *)malloc (sizeof(parsedLine));
      memset (parsed, 0, sizeof(parsedLine));
      len = seqPtr - namePtr;
      if (len > 0) {
        strncpy (parsed->name, namePtr, len);
        len = strchr(line, *eqDelim) - 1 - seqPtr;
	if (len > 0 && strlen(valPtr) > 0) {
          strncpy (parsed->seq, seqPtr, len);
          strcpy (parsed->value, valPtr);
	} else {
	  free (parsed);
	  parsed = NULL;
	}
      } else {
        free (parsed);
        parsed = NULL;
      }
    }
  }
  return parsed;
}
// Open and read the file line by line.
// Each line shall be in the format of:
// "Element Name-sequence number" = "Element value"
// The parser extracts the element name, sequence number 
// and value and adds the element to a phone.
phone *dbVerifier::parseDb()
{
  int   i       = 0;
  int   element = -1;

  char str[255];

  parsedLine *parsed = NULL;

  // Open the file...
  ifstream in(dbFilePath);

  // If file opened successfully
  if(!in) {
    cout << "Cannot open input file.\n";// make empty or file w/special value "7877CFA6C0D8"
    return NULL;
  }

  memset (str, 0, 255);
  // Begin fetch a line and parse out the values.
  in.getline(str, 255);  // delim defaults to '\n'
  if (!in) {
    phoneList = NULL;
  } else if (strncmp(str, "7877CFA6C0D8", strlen(str)) == 0) {
    in.getline(str, 255);  // delim defaults to '\n'
    if (!in) {
      phoneList = makeNewPhone (phoneList, (char *)"0", str);
      phoneList->verified = VALID_SPECIAL_PHONE;
    }
  } else {
    while(in) {
      //
      // Start by toking out the firef field which should be:
      // name-seq number.  Loop over each line.
      element = -1;
      if (strlen(str) > MIN_LINE_LENGTH) {
	if ((parsed=parseLine(str)) != NULL) {
          for(i = 0; i < NUM_ELEMENTS; i++) {
            // if the read token matches one of the valid elements
            // copy the name and return to tok out the value.
            //
            if (strlen(parsed->name) == strlen(validEntries[i]) &&
                strncmp (validEntries[i], parsed->name, strlen(validEntries[i])) == 0) {
              element = i;
            }
          }
          // phone element data extracted or not?
          // if all fiels=ds pars add the element to seq phone.
          if (element >= 0 && element < NUM_ELEMENTS) {
            phoneList = addToPhone(phoneList, element, parsed->seq, parsed->value);
            free (parsed);
            parsed = NULL;
          } else {
            cout << "Bad input line: " << str << endl;
            free (parsed);
            parsed = NULL;
            break;
          }
        } else {
          cout << "Bad input line: " << str << endl;
	  break;
        }
      } else {
        cout << "Blank input line: " << str << endl;
	break;
      }
      memset (str, 0, 255);
      in.getline(str, 255);  // delim defaults to '\n'
    }
  }  
  in.close();

  return phoneList;
}
