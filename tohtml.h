#ifndef PROCESS_INPUT
#include "process_input.h"
#endif

#define TOHTML


void processPath(char *link);

void generateHTML(List* l, char* filename);

void generateAuxFiles(List* l,char *origin);

char* catInternalLinks(char *linkname);