#ifndef LINKEDLIST
#include "linkedlist.h"
#endif
#define PROCESS_INPUT
#include <string.h>

typedef struct wiki_entry {

	char* title;
	char* last_rev_aut;
	char* last_rev_date;
	List* ext_links;
	List* int_links;
	List* sections;

}Wiki_Entry;

List* insertEntry(List*,Wiki_Entry*);

Wiki_Entry* initEntry();

Wiki_Entry* insertTitle(Wiki_Entry*, char*);

Wiki_Entry* insertAuthor(Wiki_Entry*, char*);

Wiki_Entry* insertRevisionDate(Wiki_Entry*, char*);

Wiki_Entry* insertInternLink(Wiki_Entry*, char*);

Wiki_Entry* insertExternLink(Wiki_Entry*, char*);

Wiki_Entry* insertSection(Wiki_Entry*, char*);



