#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Couple Couple;
typedef struct Relationship Relationship;

struct Couple {
    char** from; //array of the ids of the formers relationers;
    int num; // number of relationships;
    char* to; //id of the latter relationer;
};

struct Relationship {
    Couple* to; //couple dynamic vector ordered with [to]
    char* idRel; //id of the relationship
    int max; //max number of this relationship to an id
    int numTot; //tot number of entities that receive this relationship
    int numBests; //num of entities that are most relationed
    char** bests; // dynamic vector of the best relationers
};

/**
 * Dynamic scanning methods.
 */
char* dynamicWordify(char** string);
char* dynamicScan();

/**
 * Back-end methods.
 */
int insertInOrderInAStringArrayHelper(int first, int last, char* toInsert, char** array, int length);
char* deleteInOrderInAStringArray(int first, int last, char* toDelete, char*** arrayPointer, int* length);
int insertCoupleInOrder(Couple** arrayTo, char* from, char* to, int* length);
int positionToInsertFinderTo(Couple* array, char* to, int first, int last, int size);
int deleteCoupleInOrder(Couple** arrayTo, char* from, char* to, int* numOfRelationships);
int positionToDeleteFinderTo(Couple* array, char* to, int first, int last, int size);
int insertRelationshipInOrder(char* from, char* to, char* idRel, Relationship** relationships, int* relationshipsCounter);
int positionRelationshipChecker(Relationship* array, char* idRel, int first, int last, int size);
int positionRelationshipFounder(Relationship* array, char* idRel, int first, int last, int size);
int deleteRelationshipInOrder(char* from, char* to, char* idRel, Relationship** relationships, int* relationshipsCounter);
int findPositionInAStringArray(int first, int last, char* toFind, char** array);
int deleteRelationshipInPosition(int position, char* from, char* to, Relationship** relationships, int* relationshipsCounter);
int insertInAStringArray(char*** arrayPointer, char* idEnt, int* length);

/**
 * Leading methods.
 */
void addent(char*** arrayPointer, char* idEnt, int* length);
void delent(char* idEnt, char*** entitiesPointer, Relationship** relationships, int* entitiesNumber, int* relationshipsNumber);
void addrel(char* from, char* to, char* idRel, Relationship** relationships, int* relationshipsCounter, char*** entitiesPointer, int* entitiesNumber);
void delrel(char* from, char* to, char* idRel, Relationship** relationships, int* relationshipsCounter, char*** entitiesPointer, int* entitiesNumber);
void report(Relationship* relationships, int numOfRelationships);

/**
 * Debugging methods.
 */
void printCharAtArray(char** array, int length);
void printCoupleArray(Couple* array, int length);
void printRelationshipArray(Relationship* array, int length);


int main() {
    int numOfObservedEntities = 0;
    char** observedEntities = NULL;
    int numOfObservedRelationships = 0;
    Relationship* relationships = NULL;
    
    while(1) {

    	char* line;
    	char* command;
    	line = dynamicScan();
    	char* box = line;
    	command = dynamicWordify(&line);
    
        if(strcmp(command, "addent") == 0) {
            char* idEnt = dynamicWordify(&line);
            //printf("\naddent %s\n", idEnt);
            addent(&observedEntities, idEnt, &numOfObservedEntities);
		}
		else if(strcmp(command, "delent") == 0) {
			char* idEnt = dynamicWordify(&line);
            //printf("\ndelent %s\n", idEnt);
            delent(idEnt, &observedEntities, &relationships, &numOfObservedEntities, &numOfObservedRelationships);
		}
		else if(strcmp(command, "addrel") == 0) {
			char* idOrig = dynamicWordify(&line);
			char* idDest = dynamicWordify(&line);
			char* idRel = dynamicWordify(&line);
            //printf("\naddrel %s %s %s\n", idOrig, idDest, idRel);
            addrel(idOrig, idDest, idRel, &relationships, &numOfObservedRelationships, &observedEntities, &numOfObservedEntities);
		}
		else if(strcmp(command, "delrel") == 0) {
			char* idOrig = dynamicWordify(&line);
			char* idDest = dynamicWordify(&line);
			char* idRel = dynamicWordify(&line);
            //printf("\ndelrel %s %s %s\n", idOrig, idDest, idRel);
            delrel(idOrig, idDest, idRel, &relationships, &numOfObservedRelationships, &observedEntities, &numOfObservedEntities);
		}
		else if(strcmp(command, "report") == 0) {
            //printf("\nreport\n");
            report(relationships, numOfObservedRelationships);
		}
		//added for debugging purposes
		else if(strcmp(command, "debug") == 0) {
			printf("Observed Entities: ");
            printCharAtArray(observedEntities, numOfObservedEntities);
            printf("\n");
            printf("Observed Relationships:\n");
            printRelationshipArray(relationships, numOfObservedRelationships);
            printf("\n");
		}
		//end of debugging
		else if(strcmp(command, "end") == 0) return 0;

		free(box);
        free(command); //may crash
	}
}

/**
 * Scans a word from a line dynamically allocating memory;
 */
char* dynamicWordify(char** string) {
	char* line = *string;
	char* word;
	int i = 1;
	word = malloc(i*sizeof(char));
	word[0] = line[0];
	line = &(line[1]);
	while(line[0] != ' ' && line[0] != '\0') {
		i++;
		word = realloc(word, (i+1)*sizeof(char));
		word[i-1] = line[0];
		line = &(line[1]);
	}
	line = &(line[1]);
	word[i] = '\0';
	*string = line;
	return word;
}

/**
 * Scans a line dynamically allocating memory;
 */
char* dynamicScan() {
	char* string;
	char c = getchar();
	string = malloc(sizeof(char));
	string[0] = c;
	int i = 0;
	c = getchar();
	while(c != '\n') {
		i++;
		string = realloc(string, (i+1)*sizeof(char));
		string[i] = c;
		c = getchar();
	}
	string = realloc(string, (i+2)*sizeof(char));
	string[i+1] = '\0';
	return(string);
}

/**
 * Deletes an entity from the database.
 * [fixed]
 */
void delent(char* idEnt, char*** entitiesPointer, Relationship** relationships, int* entitiesNumber, int* relationshipsNumber) {
    char* toFree = deleteInOrderInAStringArray(0, (*entitiesNumber)-1, idEnt, entitiesPointer, entitiesNumber);
    if(strcmp(toFree, "-1") == 0) return;
    int i = 0;
    while(i < (*relationshipsNumber)) {
        int boxRelNum = (*relationshipsNumber);
        int j = 0;
        int boxMax = 0;
        int boxNumOfBests = 0;
        char** boxBests = NULL;

        while(j < (*relationships)[i].numTot) {
            int boxToNum = (*relationships)[i].numTot;
            if(strcmp((*relationships)[i].to[j].to, idEnt) == 0) {
                //Caso in cui il [to] è l'entità da cancellare.
                free((*relationships)[i].to[j].from);
                (*relationships)[i].numTot--;
                if((*relationships)[i].numTot > 0) {
                    //Caso in cui questa relazione esiste ancora;
                    int k = j;
                    while(k < (*relationships)[i].numTot) {
                        (*relationships)[i].to[k] = (*relationships)[i].to[k+1];
                        k++;
                    }
                    (*relationships)[i].to = realloc((*relationships)[i].to, sizeof(Couple)*((*relationships)[i].numTot));
                }
                else {
                    //Caso in cui questa relazione non esista più;
                    free((*relationships)[i].to);
                    free((*relationships)[i].bests);
                    free((*relationships)[i].idRel);
                    (*relationshipsNumber)--;
                    if((*relationshipsNumber) > 0) {
                        //Caso in cui esistano altre relazioni.
                        if(boxBests != NULL) free(boxBests);
                        j = (*relationships)[i].numTot + 1;
                        int k = i;
                        while(k < (*relationshipsNumber)) {
                            (*relationships)[k] = (*relationships)[k+1];
                            k++;
                        }
                        (*relationships) = realloc((*relationships), sizeof(Relationship)*(*relationshipsNumber));
                    }
                    else {
                        //Caso in cui non esistano più relazioni.
                        free((*relationships));
                        (*relationships) = NULL;
                        if(boxBests != NULL) free(boxBests);
                        free(toFree);
                        free(idEnt);
                        return;
                    }
                }          
            }
            else {
                //Caso in cui il [to] non è l'entità da cancellare.
                deleteInOrderInAStringArray(0, (*relationships)[i].to[j].num-1, idEnt, &((*relationships)[i].to[j].from), &((*relationships)[i].to[j].num));
                if((*relationships)[i].to[j].num == 0) {
                    //Caso in cui non ci siano più relazioni di questo [to];
                    (*relationships)[i].numTot--;
                    if((*relationships)[i].numTot > 0) {
                    //Caso in cui questa relazione esiste ancora;
                    int k = j;
                    while(k < (*relationships)[i].numTot) {
                        (*relationships)[i].to[k] = (*relationships)[i].to[k+1];
                        k++;
                    }
                    (*relationships)[i].to = realloc((*relationships)[i].to, sizeof(Couple)*((*relationships)[i].numTot));
                    }
                    else {
                        //Caso in cui questa relazione non esiste più;
                        free((*relationships)[i].to);
                        free((*relationships)[i].bests);
                        free((*relationships)[i].idRel);
                        (*relationshipsNumber)--;
                        if((*relationshipsNumber) > 0) {
                            //Caso in cui esistano altre relazioni.
                            j = (*relationships)[i].numTot + 1;
                            if(boxBests != NULL) free(boxBests);
                            int k = i;
                            while(k < (*relationshipsNumber)) {
                                (*relationships)[k] = (*relationships)[k+1];
                                k++;
                            }
                            (*relationships) = realloc((*relationships), sizeof(Relationship)*(*relationshipsNumber));
                        }
                        else {
                            //Caso in cui non esistano più relazioni.
                            free((*relationships));
                            (*relationships) = NULL;
                            if(boxBests != NULL) free(boxBests);
                            free(toFree);
                            free(idEnt);
                            return;
                        }
                    }
                }
                else if(boxMax < (*relationships)[i].to[j].num) {
                    boxMax = (*relationships)[i].to[j].num;
                    if(boxBests == NULL) boxBests = malloc(sizeof(char*));
                    else boxBests = realloc(boxBests, sizeof(char*));
                    boxNumOfBests = 1;
                    boxBests[0] = (*relationships)[i].to[j].to;
                } else if(boxMax == (*relationships)[i].to[j].num) {
                    insertInAStringArray(&boxBests, (*relationships)[i].to[j].to, &boxNumOfBests);
                }
            }
            if(boxToNum == (*relationships)[i].numTot) j++;
        }

        if((*relationshipsNumber) == boxRelNum) {
            (*relationships)[i].max = boxMax;
            (*relationships)[i].numBests = boxNumOfBests;
            free((*relationships)[i].bests);
            (*relationships)[i].bests = boxBests;
            i++;
        }
    }
    free(toFree);
    free(idEnt);
}


/**
 * Inserts a  string in an ordered array;
 * NB: length is the size of the array+1 BEFORE THE INSERTION (human size); it must be updated as done in the function! (it may be done by passing the length pointer)
 */
void addent(char*** arrayPointer, char* idEnt, int* length) {
    (*length)++;
    char** box = *arrayPointer;
    if((*length) == 1) {
        box = malloc(sizeof(char*));
        box[0] = idEnt;
        (*arrayPointer) = box;
        return;
    }
    box = realloc(box, (*length)*sizeof(char*));
    box[(*length)-1] = "z";
    int check = insertInOrderInAStringArrayHelper(0, (*length)-1, idEnt, box, (*length));
    if(check == -1) {
    	(*length)--;
    	box = realloc(box, (*length)*sizeof(char*));
    	free(idEnt);
	}
    (*arrayPointer) = box;
    return;
}

/**
 * Inserts a  string in an ordered array and doesn't free anything;
 * NB: length is the size of the array+1 BEFORE THE INSERTION (human size); it must be updated as done in the function! (it may be done by passing the length pointer)
 * @return 1 if the insertion went fine; -1 otherwise.
 */
int insertInAStringArray(char*** arrayPointer, char* idEnt, int* length) {
    (*length)++;
    char** box = *arrayPointer;
    if((*length) == 1) {
        box = malloc(sizeof(char*));
        box[0] = idEnt;
        (*arrayPointer) = box;
        return 1;
    }
    box = realloc(box, (*length)*sizeof(char*));
    box[(*length)-1] = "z";
    int check = insertInOrderInAStringArrayHelper(0, (*length)-1, idEnt, box, (*length));
    if(check == -1) {
    	(*length)--;
    	box = realloc(box, (*length)*sizeof(char*));
	}
    (*arrayPointer) = box;
    return check;
}

/**
 * Adds a relationship if it exists.
 * [fixed]
 */
void addrel(char* from, char* to, char* idRel, Relationship** relationships, int* relationshipsCounter, char*** entitiesPointer, int* entitiesNumber) {
    if((*entitiesPointer) == NULL) {
        free(from);
        free(to);
        free(idRel);
        return;
    }
    int positionFrom = findPositionInAStringArray(0, (*entitiesNumber)-1, from, *entitiesPointer);
    int positionTo = findPositionInAStringArray(0, (*entitiesNumber)-1, to, *entitiesPointer);
    free(from);
    free(to);
    if(positionFrom == -1 || positionTo == -1) {
        free(idRel);
        return;
    }
    insertRelationshipInOrder((*entitiesPointer)[positionFrom], (*entitiesPointer)[positionTo], idRel, relationships, relationshipsCounter);
}

/**
 * Deletes a relationship if it exists.
 */
void delrel(char* from, char* to, char* idRel, Relationship** relationships, int* relationshipsCounter, char*** entitiesPointer, int* entitiesNumber) {
    int positionFrom = findPositionInAStringArray(0, (*entitiesNumber)-1, from, *entitiesPointer);
    int positionTo = findPositionInAStringArray(0, (*entitiesNumber)-1, to, *entitiesPointer);
    free(from);
    free(to);
    if(positionFrom == -1 || positionTo == -1) {
        free(idRel);
        return;
    }
    deleteRelationshipInOrder((*entitiesPointer)[positionFrom], (*entitiesPointer)[positionTo], idRel, relationships, relationshipsCounter);
    free(idRel);
}

/**
 * Reports the situation.
 */
void report(Relationship* relationships, int numOfRelationships) {
	if(relationships == NULL) {
		printf("none\n");
		return;
	}
    int i = 0;
    while(i < numOfRelationships) {
        if(i > 0) printf(" ");
        printf("%s", relationships[i].idRel);
        int j = 0;
        while(j < relationships[i].numBests) {
            printf(" %s", relationships[i].bests[j]);
            j++;
        }
        printf(" %d;", relationships[i].max);
        i++;
    }
    printf("\n");
}

/**
 * Inserts a string in an ordered string array (helper method for the recursion);
 * NB: length is the size of the array + 1 (human size);
 * @return 1 if the insertion ended fine; -1 otherwise;
 */
int insertInOrderInAStringArrayHelper(int first, int last, char* toInsert, char** array, int length) {
	int i = (first+last)/2;
    int comparison = strcmp(array[i], toInsert);
    if(comparison == 0) return -1;
    if(comparison < 0) {
        if(i == length-2 || strcmp(array[i+1], toInsert) > 0) {
            i++;
            while(i < length) {
                char* temp = array[i];
                array[i] = toInsert;
                toInsert = temp;
                i++;
            }
            return 1;
        }
        first = i+1;
        return insertInOrderInAStringArrayHelper(first, last, toInsert, array, length);
    }
    if(i == 0 || strcmp(array[i-1], toInsert) < 0) {
        while(i < length) {
            char* temp = array[i];
            array[i] = toInsert;
            toInsert = temp;
            i++;
        }
        return 1;
    }
    last = i-1;
    return insertInOrderInAStringArrayHelper(first, last, toInsert, array, length);
}

/**
 * Deletes a string in an ordered string array;
 * NB: length is the size of the array + 1 (human size);
 * @return 1 if the deletion ended fine; -1 otherwise;
 * [fixed]
 */
char* deleteInOrderInAStringArray(int first, int last, char* toDelete, char*** arrayPointer, int* length) {
	if(last < first) return "-1";
	char** array = *arrayPointer;
	int i = (first+last)/2;
    int comparison = strcmp(array[i], toDelete);
    if(comparison == 0) {
        (*length)--;
        char* toFree = array[i];
    	while(i < (*length)) {
    		array[i] = array[i+1];
    		i++;
		}
        if((*length) > 0) array = realloc(array, (*length)*sizeof(char*));
		else {
            free(array);
            array = NULL;
        }
		*arrayPointer = array;
		return toFree;
	}
    if(comparison < 0) {
        first = i+1;
        return deleteInOrderInAStringArray(first, last, toDelete, arrayPointer, length);
    }
    last = i-1;
    return deleteInOrderInAStringArray(first, last, toDelete, arrayPointer, length);
}

/**
 * Finds the index of a string in an array of string.
 */
int findPositionInAStringArray(int first, int last, char* toFind, char** array) {
    if(last < first) return -1;
	int i = (first+last)/2;
    int comparison = strcmp(array[i], toFind);
    if(comparison == 0) return i;
    if(comparison < 0) return findPositionInAStringArray(i+1, last, toFind, array);
    return findPositionInAStringArray(first, i-1, toFind, array);
}

/**
 * Adds a couple in an ordered array of couples.
 * @return the number of to Relationships for that toEntity; -1 otherwise (couple already exists).
 * [fixed]
 */
int insertCoupleInOrder(Couple** arrayTo, char* from, char* to, int* length) {
    
    int positionTo = positionToInsertFinderTo(*arrayTo, to, 0, (*length)-1, (*length)-1);
    if(positionTo < 0) {
        int i = (positionTo * (-1)) - 1;
        int insertion = insertInAStringArray(&((*arrayTo)[i].from), from, &((*arrayTo)[i].num));
        if(insertion != -1) return (*arrayTo)[i].num;
        return -1;
    }

    int box = (*length);
    (*length)++;
    (*arrayTo) = realloc((*arrayTo), (*length)*sizeof(Couple));
    while(box > positionTo) {
        (*arrayTo)[box].num = (*arrayTo)[box-1].num;
        (*arrayTo)[box].from = (*arrayTo)[box-1].from;
        (*arrayTo)[box].to = (*arrayTo)[box-1].to;
        box--;
    }
    (*arrayTo)[positionTo].from = malloc(sizeof(char*));
    (*arrayTo)[positionTo].from[0] = from;
    (*arrayTo)[positionTo].num = 1;
    (*arrayTo)[positionTo].to = to;

    return 1;
}

/**
 * Returns the position where a Couple should be inserted in a [to] ordered Couple array.
 * NB: size is the cpu size of the array.
 * @return -1 if the couple already exists, the position looked for otherwise.
 * [fixed]
 */
int positionToInsertFinderTo(Couple* array, char* to, int first, int last, int size) {
    int i = (first+last)/2;
    int comparison = strcmp(array[i].to, to);
    if(comparison == 0) {
        return (-1)*(i+1);
    }
    if(comparison < 0) {
        if((i+1) > size || strcmp(array[i+1].to, to) > 0) return i+1;
        return positionToInsertFinderTo(array, to, i+1, last, size);
    }
    if(i == 0 || strcmp(array[i-1].to, to) < 0) return i;
    return positionToInsertFinderTo(array, to, first, i-1, size);
}

/**
 * Deletes a couple in an ordered array of couples.
 * @return the (number of relationships remaining)+1 if the deletion went fine; -1 otherwise (couple doesn't exists).
 * [fixed]
 */
int deleteCoupleInOrder(Couple** arrayTo, char* from, char* to, int* numOfRelationships) {
    if((*numOfRelationships) == 0) {
        return -1;
    }
    
    int positionTo = positionToDeleteFinderTo(*arrayTo, to, 0, (*numOfRelationships)-1, (*numOfRelationships)-1);
    if(positionTo == -1) return -1;
    char* deletion = deleteInOrderInAStringArray(0, (*arrayTo)[positionTo].num-1, from, &((*arrayTo)[positionTo].from), &((*arrayTo)[positionTo].num));
    if(strcmp(deletion, "-1") == 0) return -1;

    if((*arrayTo)[positionTo].num == 0) {

        (*numOfRelationships)--;

        if((*numOfRelationships) == 0) {
        free((*arrayTo));
        (*arrayTo) = NULL;
        return 1;
        }

        while(positionTo < (*numOfRelationships)) {
            (*arrayTo)[positionTo].from = (*arrayTo)[positionTo+1].from;
            (*arrayTo)[positionTo].to = (*arrayTo)[positionTo+1].to;
            (*arrayTo)[positionTo].num = (*arrayTo)[positionTo+1].num;
            positionTo++;
        }
        (*arrayTo) = realloc((*arrayTo), (*numOfRelationships)*sizeof(Couple));
        return 1;
    }

    return (*arrayTo)[positionTo].num+1;
}

/**
 * Returns the position where a Couple is stored in a [to] ordered Couple array.
 * NB: size is the cpu size of the array.
 * @return -1 if the couple don't exists, the position looked for otherwise.
 * [fixed]
 */
int positionToDeleteFinderTo(Couple* array, char* to, int first, int last, int size) {
    if(first > last) return -1;
    int i = (first+last)/2;
    int comparison = strcmp(array[i].to, to);
    if(comparison == 0) return i;
    if(comparison < 0) {
    	if((i+1) > size) return -1;
        return positionToDeleteFinderTo(array, to, i+1, last, size);
    }
    if(i == 0) return -1;
    return positionToDeleteFinderTo(array, to, first, i-1, size);
}

/**
 * Inserts a relationship in the relationships.
 * @return 1 if the insertion went fine; -1 otherwise.
 * [fixed]
 */
int insertRelationshipInOrder(char* from, char* to, char* idRel, Relationship** relationships, int* relationshipsCounter) {
    //Caso in cui non ci siano relazioni.
    if((*relationshipsCounter) == 0) {
        (*relationships) = malloc(sizeof(Relationship));
        (*relationships)[0].numTot = 1;
        (*relationships)[0].max = 1;
        (*relationships)[0].numBests = 1;
        (*relationships)[0].idRel = idRel;
        (*relationships)[0].bests = malloc(sizeof(char*));
        (*relationships)[0].bests[0] = to;
        (*relationships)[0].to = malloc(sizeof(Couple));
        (*relationships)[0].to[0].num = 1;
        (*relationships)[0].to[0].to = to;
        (*relationships)[0].to[0].from = malloc(sizeof(char*));
        (*relationships)[0].to[0].from[0] = from;
        (*relationships)[0].to[0].from = realloc((*relationships)[0].to[0].from, 2*sizeof(char*));
        (*relationshipsCounter) = 1;
        return 1;
    }

    int position = positionRelationshipChecker((*relationships), idRel, 0, (*relationshipsCounter)-1, (*relationshipsCounter)-1);

    if(position != -1) {
        //Caso in cui la relazione sia già sotto osservazione.
        free(idRel);
        int addCouple = insertCoupleInOrder(&((*relationships)[position].to), from, to, &((*relationships)[position].numTot));
        if(addCouple == -1) return -1;
        if(addCouple > (*relationships)[position].max) {
            //Caso in cui la relazione sia la nuova massima.
            (*relationships)[position].max = addCouple;
            (*relationships)[position].numBests = 1;
            (*relationships)[position].bests[0] = to;
            (*relationships)[position].bests = realloc((*relationships)[position].bests, sizeof(char*));
            return 1;
        }
        if(addCouple == (*relationships)[position].max) {
            //caso in cui la relazione sia pari al massimo.
            insertInAStringArray(&((*relationships)[position].bests), to, &((*relationships)[position].numBests));
            return 1;
        }
        return 1;
    }

    //Caso in cui la relazione sia una nuova.
    position = positionRelationshipFounder((*relationships), idRel, 0, (*relationshipsCounter)-1, (*relationshipsCounter)-1);
    int box = (*relationshipsCounter);
    (*relationshipsCounter)++;
    (*relationships) = realloc((*relationships), (*relationshipsCounter)*sizeof(Relationship));
    while(box > position) {
        (*relationships)[box].bests = (*relationships)[box-1].bests;
        (*relationships)[box].idRel = (*relationships)[box-1].idRel;
        (*relationships)[box].max = (*relationships)[box-1].max;
        (*relationships)[box].numBests = (*relationships)[box-1].numBests;
        (*relationships)[box].numTot = (*relationships)[box-1].numTot;
        (*relationships)[box].to = (*relationships)[box-1].to;
        box--;
    }

    (*relationships)[position].numTot = 1;
    (*relationships)[position].max = 1;
    (*relationships)[position].numBests = 1;
    (*relationships)[position].idRel = idRel;
    (*relationships)[position].bests = malloc(sizeof(char*));
    (*relationships)[position].bests[0] = to;
    (*relationships)[position].to = malloc(sizeof(Couple));
    (*relationships)[position].to[0].num = 1;
    (*relationships)[position].to[0].to = to;
    (*relationships)[position].to[0].from = malloc(sizeof(char*));
    (*relationships)[position].to[0].from[0] = from;
    return 1;
}

/**
 * Finds the position of a relationship; returns (-1) if the relationship doesn't exists.
 * @param size it's the cpu size of the array.
 * [fixed]
 */
int positionRelationshipChecker(Relationship* array, char* idRel, int first, int last, int size) {
    if(first > last) return -1;
    int i = (first+last)/2;
    int comparison = strcmp(array[i].idRel, idRel);
    if(comparison == 0) return i;
    if(comparison < 0) {
        return positionRelationshipChecker(array, idRel, i+1, last, size);
    }
    return positionRelationshipChecker(array, idRel, first, i-1, size);
}

/**
 * Finds the position where to add the relationship.
 * @param size it's the cpu size of the array.
 * [fixed]
 */
int positionRelationshipFounder(Relationship* array, char* idRel, int first, int last, int size) {
    int i = (first+last)/2;
    int comparison = strcmp(array[i].idRel, idRel);
    if(comparison < 0) {
    	if((i+1) > size || strcmp(array[i+1].idRel, idRel) > 0) return i+1;
        return positionRelationshipFounder(array, idRel, i+1, last, size);
    }
    if(i == 0 || strcmp(array[i-1].idRel, idRel) < 0) return i;
    return positionRelationshipFounder(array, idRel, first, i-1, size);
}

/**
 * Deletes a relationship in the relationships.
 * @return 1 if the deletion went fine; -1 otherwise.
 * [fixed]
 */
int deleteRelationshipInOrder(char* from, char* to, char* idRel, Relationship** relationships, int* relationshipsCounter) {
    if((*relationshipsCounter) == 0) return -1; 
    int position = positionRelationshipChecker((*relationships), idRel, 0, (*relationshipsCounter)-1, (*relationshipsCounter)-1);
    if(position == -1) return -1;
    return deleteRelationshipInPosition(position, from, to, relationships, relationshipsCounter);
}

/**
 * Deletes a relationship in a precise position.
 * @return 1 if the deletion went fine; -1 otherwise.
 * idRel is freed inhere.
 * [fixed]
 */
int deleteRelationshipInPosition(int position, char* from, char* to, Relationship** relationships, int* relationshipsCounter) {
    int delFromCouples = deleteCoupleInOrder(&((*relationships)[position].to), from, to, &((*relationships)[position].numTot));
    if(delFromCouples == -1) return -1;
    
    //Caso in cui il relazionato non era compreso tra i migliori.
    if(delFromCouples != (*relationships)[position].max) return 1;

    //Caso in cui il relazionato era tra i migliori, ma ce n'erano comunque altri.
    if((*relationships)[position].numBests > 1) {
        char* string = deleteInOrderInAStringArray(0, (*relationships)[position].numBests-1, to, (&(*relationships)[position].bests), (&(*relationships)[position].numBests));
        if(strcmp(string, "-1") == 0) return -1;
        return 1;
    }

    //Caso in cui il relazionato era l'unico migliore.
    (*relationships)[position].max--;
    if((*relationships)[position].numTot == 0) {
        //Caso in cui non ci siano più relazioni di questo tipo.
        (*relationshipsCounter)--;
        free((*relationships)[position].idRel);
        free((*relationships)[position].bests);
        //Caso in cui quella da eliminare fosse l'unica relazione osservata.
        if((*relationshipsCounter) == 0) {
            free((*relationships));
            (*relationships) = NULL;
            return 1;
        }
        //Caso in cui ci siano altre relazioni.
        while(position < (*relationshipsCounter)) {
            (*relationships)[position].bests = (*relationships)[position+1].bests;
            (*relationships)[position].idRel = (*relationships)[position+1].idRel;
            (*relationships)[position].max = (*relationships)[position+1].max;
            (*relationships)[position].numBests = (*relationships)[position+1].numBests;
            (*relationships)[position].numTot = (*relationships)[position+1].numTot;
            (*relationships)[position].to = (*relationships)[position+1].to;
            position++;
        }
        (*relationships) = realloc((*relationships), (*relationshipsCounter)*sizeof(Relationship));
        return 1;
    }

    //Caso in cui esistano ancora relazioni di questo tipo.
    int relCounter = 0;
    while(relCounter < (*relationships)[position].numTot) {
        if((*relationships)[position].max == (*relationships)[position].to[relCounter].num && strcmp((*relationships)[position].to[relCounter].to, to) != 0)
            insertInAStringArray(&((*relationships)[position].bests), (*relationships)[position].to[relCounter].to, &((*relationships)[position].numBests));
        relCounter++;
    }
    return 1;
}

/**
 * Prints an array of string. Inserted for debugging purposes.
 */
void printCharAtArray(char** array, int length) {
	if(array == NULL) {
		printf("La lista e' vuota;");
		return;	
	}
    int i = 0;
    printf("[");
    printf("(%d): %s;", i, array[i]);
    i++;
    while(i < length) {
        printf(" (%d): %s;", i, array[i]);
        i++;
    }
    printf("]");
}

/**
 * Prints an array of Couples. Inserted for debugging purposes.
 */
void printCoupleArray(Couple* array, int length) {
	if(array == NULL) {
		printf("La lista e' vuota;");
		return;	
	}
    int i = 0;
    printf("\n\t\t{(%d): to -> %s; num -> %d; from -> [%s", i, array[i].to, array[i].num, array[i].from[0]);
    int j;
    for(j = 1; j < array[i].num; j++) printf("; %s", array[i].from[j]);
    printf("]}");
    i++;
    while(i < length) {
        printf("\n\t\t{(%d): to -> %s; num -> %d; from -> [%s", i, array[i].to, array[i].num, array[i].from[0]);
        for(j = 1; j < array[i].num; j++) printf("; %s", array[i].from[j]);
        printf("]}");
        i++;
    }
    printf("\n");
}

/**
 * Prints an array of Relationships. Inserted for debugging purposes.
 */
void printRelationshipArray(Relationship* array, int length) {
	if(array == NULL) {
		printf("La lista e' vuota;");
		return;	
	}
    int i = 0;
    printf("(%d):", i);
    printf("\n\tidRel: %s", array[i].idRel);
    printf("\n\tnumTot: %d", array[i].numTot);
    printf("\n\tto: ");
    printCoupleArray(array[i].to, array[i].numTot);
    printf("\n\tmax: %d", array[i].max);
    printf("\n\tnumBests: %d", array[i].numBests);
    printf("\n\tbests: ");
    printCharAtArray(array[i].bests, array[i].numBests);
    i++;
    while(i < length) {
        printf("\n(%d):", i);
        printf("\n\tidRel: %s", array[i].idRel);
        printf("\n\tnumTot: %d", array[i].numTot);
        printf("\n\tto: ");
        printCoupleArray(array[i].to, array[i].numTot);
        printf("\n\tmax: %d", array[i].max);
        printf("\n\tnumBests: %d", array[i].numBests);
        printf("\n\tbests: ");
        printCharAtArray(array[i].bests, array[i].numBests);
        i++;
    }
}
