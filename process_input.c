#include "process_input.h"



List* insertEntry(List *l,Wiki_Entry *e) {

	l = insertHead(l, e);

	return l;

}

Wiki_Entry* initEntry() {

	Wiki_Entry *e = (Wiki_Entry*) malloc(sizeof(Wiki_Entry));

	e->ext_links = init(150*sizeof(char*), NULL);
	e->int_links = init(150*sizeof(char*), NULL);
	e->sections = init(150*sizeof(char*), NULL);

	return e;
}

void destroyEntry(Wiki_Entry *e) {

	free(e->last_rev_aut);
	free(e->title);
	free(e->last_rev_date);
	listDestroy(e->ext_links,NULL);
	listDestroy(e->int_links,NULL);
	listDestroy(e->sections,NULL);
	free(e);
}

void destroyEntryList(List *l) {

	listDestroy(l,(void*)&destroyEntry);

}

Wiki_Entry* insertTitle(Wiki_Entry* e, char* s) {

	e->title = strdup(s);

	return e;
}

Wiki_Entry* insertAuthor(Wiki_Entry* e, char* s) {

	e->last_rev_aut = strdup(s);

	return e;
}

Wiki_Entry* insertRevisionDate(Wiki_Entry* e, char* s) {

	e->last_rev_date = strdup(s);

	return e;
}


Wiki_Entry* insertInternLink(Wiki_Entry* e, char* s) {

	e->int_links = insertHead(e->int_links, strdup(s));

	return e;
}

Wiki_Entry* insertExternLink(Wiki_Entry* e, char* s) {

	e->ext_links = insertTail(e->ext_links, strdup(s));

	return e;
}


Wiki_Entry* insertSection(Wiki_Entry* e, char* s) {

	e->sections = insertTail(e->sections, strdup(s));

	return e;

}