#include "jsmn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*input the api json code*/

static const char *JSON_STRING  ;

void readfile(char* filepath, char* fileContent)
{
    FILE *f;
    char c;
    int index;
    f = fopen("jsonSearch.json", "rt");
    while((c = fgetc(f)) != EOF){
        fileContent[index] = c;
        index++;
    }
    fileContent[index] = '\0';
}

/*code to parse the json*/
static int json(const char *json, jsmntok_t *tok, const char *s) {
	if (tok->type == JSMN_STRING && (int) strlen(s) == tok->end - tok->start &&
			strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
		return 0;
	}
	return -1;
}

int main() {
	int i;
	int j;
	jsmn_parser p;
	
	jsmntok_t t[index];

	/*testing to make sure it does not fail*/
	
	j = jsmn_parse(&p, JSON_STRING, strlen(JSON_STRING), t, sizeof(t)/sizeof(t[index]));
	if (j < 0) {
		printf("Failed to parse JSON: %d\n", j);
		return 1;
	}
	
	/* Assume that there is something there and if not return that */
	if (j < 1 || t[0].type != JSMN_OBJECT) {
		printf("Object expected\n");
		return 1;
	}
	/* Loop over the keys to get the object */
	for (i = 1; i < j; i++) {
		if (json(JSON_STRING, &t[i], "id") == 0) {
			printf("The ID is: %.*s\n", t[i+1].end-t[i+1].start,
					JSON_STRING + t[i+1].start);
			i++;
		}
	}
}
