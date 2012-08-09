#include "toHTML.h"
#include <stdio.h>
#include <sys/dir.h>
#include <sys/stat.h>


void generateHTML(List* l, char* filename) {

	Node* aux = l->list;
	Wiki_Entry* article;
	
	char* path = malloc(200*sizeof(char ));

	strcat(path,filename);
	strcat(path,".html");
	generateAuxFiles(l,path);
	FILE* f = fopen(path, "w+");

	fprintf(f, "<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" /><title>Index</title></head>");
	fprintf(f, "<body bgcolor=\"silver\"><h1 align=CENTER>Index</h1>");
		
	fprintf(f, "<table align=CENTER border=\"1\" cellspacing=0 bgcolor=\"#FFFFFF\">");

	char *files;

	while(aux){
		article = (Wiki_Entry*)aux->data;
		files = strdup(article->title);
		processPath(files);
		fprintf(f, "<tr><td><a target=\"_parent\" href=files/%s.html target=\"_blank\" >%s </a></td></tr>\n",files, article->title);
		aux = aux->next;
	}
	fprintf(f, "</table>");			
	fprintf(f, "</body></html>");	

	fclose(f);
}


void generateAuxFiles(List* l, char* origin) {

	Node* aux = l->list;
	Wiki_Entry* article;

	mkdir("files", 0755);
	char *path;
	char *section;
	Node* links;
	while(aux) {
		article = (Wiki_Entry*) aux->data;
		path = (char*) malloc(200*sizeof(char));
		strcat(path, "files/");
		strcat(path, article->title);
		strcat(path, ".html");
		processPath(path);
		FILE* fout = fopen(path, "w+");

		if(fout) {

			fprintf(fout,"<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" /><title>%s</title></head>",article->title);
			fprintf(fout, "<body bgcolor=\"silver\"><h1 align = center style=\"font-family: Courier;\"><a href=\"http://pt.wikipedia.org/wiki/%s\" target=\"_blank\" >%s </a></h1>", 
				article->title,article->title);

			if(article->last_rev_aut == NULL)
				fprintf(fout, "<h3 style=\"font-family: Courier;\">Last Revision Author: Anonymous </h3>");		
			else
				fprintf(fout, "<h3 style=\"font-family: Courier;\">Last Revision Author: %s </h3>", article->last_rev_aut);		
			if(article->last_rev_date == NULL)
				fprintf(fout, "<h3 style=\"font-family: Courier;\">Last Revision Date: Unknown </h3>");
			else
				fprintf(fout, "<h3 style=\"font-family: Courier;\">Last Revision Date: %s </h3>", article->last_rev_date);



			fprintf(fout, "<table WIDTH=100%%><tr><td ALIGN=RIGTH, VALIGN=TOP>");
			fprintf(fout, "<table border=\"1\" cellspacing=0 bgcolor=\"#FFFFFF\">");
			fprintf(fout, "<th><font color=\"#000000\"> %d Internal Links</font></th>", article->int_links->size);
			links = article->int_links->list;

			while(links) {
				fprintf(fout, "<tr><td><a href=\"http://pt.wikipedia.org/wiki/%s\" target=\"_blank\" >%s </a></td></tr>\n", (char*)links->data,(char*)links->data);
				links = links->next;
			}
			fprintf(fout, "</table>");		


			fprintf(fout, "</td><td ALIGN=CENTER, VALIGN=TOP>");
			fprintf(fout, "<table border=\"1\" cellspacing=0 bgcolor=\"#FFFFFF\">");	
			fprintf(fout, "<th><font color=\"#000000\"> %d External Links</font></th>", article->ext_links->size);
			links = article->ext_links->list;
			while(links){		
				fprintf(fout, "<tr><td><a href=\"http://%s\" target=\"_blank\" >%s </a></td></tr>\n", (char*)links->data,(char*)links->data);		
				links=links->next;
			}
			fprintf(fout, "</table>");



			fprintf(fout, "</td><td ALIGN=LEFT, VALIGN=TOP>");
			fprintf(fout, "<table border=\"1\" cellspacing=0 bgcolor=\"#FFFFFF\">");	
			fprintf(fout, "<th><font color=\"#000000\"> %d Sections </font></th>", article->sections->size);
			links = article->sections->list;
			while(links){
				section = strdup((char*)links->data);
				processPath(section);
				section[strlen(section)-1] = '\0';		
				fprintf(fout, "<tr><td><a href=\"http://pt.wikipedia.org/wiki/%s#%s\" target=\"_blank\" >%s </a></td></tr>\n", 
					(char*)article->title,section,(char*)links->data);		
				links=links->next;
			}
			fprintf(fout, "</table>");

			fprintf(fout,"</td></tr></table>");
			fprintf(fout, "<p style=\"text-align:center\"> <a href=\"../%s\"\n>Return to index</a> </p>\n",origin );
			fprintf(fout, "</body></html>");	
			
			fclose(fout);

		}
		
		aux = aux->next;
	}
	

}


void processPath(char *link) {

	int i;

	for (i = 0; i < (int)strlen(link); ++i)
	{
		if(link[i] == ' ')
			link [i] = '_';
	}

}

char* catInternalLinks(char *linkname) {

	char *wikilink = (char*) malloc(100*sizeof(char));
	strcat(wikilink,"pt.wikipedia.org/wiki/");	
	strcat(wikilink,linkname);

	return wikilink;
}