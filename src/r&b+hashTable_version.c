#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct entityTree entityTree;
typedef struct relationshipTree relationshipTree;
typedef struct relationship relationship;
typedef struct idToRelationatedTreeNum idToRelationatedTreeNum;
typedef struct idToRelationatedTreeID idToRelationatedTreeID;
typedef struct node node;

struct entityTree{
    char* entityID;
    entityTree* father;
    entityTree* right;
    entityTree* left;
};

struct relationship{
    char* keyRelationshipID;
    node* node;
};

struct relationshipTree{
    char* keyRelationshipID;
    node* node;

    relationshipTree* right;
    relationshipTree* left;
    relationshipTree* father;
};

struct idToRelationatedTreeID{
    char* idTo;
    char** idFrom;

    node* node;

    idToRelationatedTreeID* father;
    idToRelationatedTreeID* right;
    idToRelationatedTreeID* left;
};

struct idToRelationatedTreeNum{
    int number;

    node* node;

    idToRelationatedTreeNum* father;
    idToRelationatedTreeNum* right;
    idToRelationatedTreeNum* left;

};

struct node{
    idToRelationatedTreeNum* num;
    idToRelationatedTreeID* id;
};

void addrel(char* idRel, char* idFrom, char* idTo, char** entities, relationshipTree** relationships, int numOfEntities);
void delent(char* idEnt, char*** entities, relationshipTree** relationships, int* numOfEntities);
void delrel(char* idRel, char* idFrom, char* idTo, char** entities, relationshipTree** relationships, int numOfEntities);
int addStringToEntityTree(char* string, entityTree** entities);
void deleteEntityTreeHelper(char* idEnt, entityTree** entities);
char* entityIDResearch(char* idEnt, entityTree* entities);
entityTree* entityNodeResearch(char* idEnt, entityTree* entities);
void entityDelete(entityTree* toDelete, entityTree** entities);
entityTree* treeSuccessor(entityTree* entities);
entityTree* treeMinimum(entityTree* box);
void printEntityTree(entityTree* tree);
void addNodeToRelationshipTree(relationshipTree* node, relationshipTree** relationships);
relationshipTree* relationshipNodeResearch(char* relationshipID, relationshipTree* relationshipTree);
relationshipTree* deleteRelationship(relationshipTree* toDelete, relationshipTree** tree);
relationshipTree* relationshipTreeSuccessor(relationshipTree* node);
relationshipTree* relationshipTreeMinimum(relationshipTree* box);
void printRelationshipTree(relationshipTree* tree);
idToRelationatedTreeID* relationshipNodeResearchID(char* idTo, idToRelationatedTreeID* tree);
void addNodeToIdToTreeID(idToRelationatedTreeID* node, idToRelationatedTreeID** tree);
void addNodeToIdToTreeNum(idToRelationatedTreeNum* node, idToRelationatedTreeNum** tree);
idToRelationatedTreeNum* idToRelationatedTreeNodeDeleteNum(idToRelationatedTreeNum* toDelete, idToRelationatedTreeNum** tree);
idToRelationatedTreeID* idToRelationatedTreeNodeDeleteID(idToRelationatedTreeID* toDelete, idToRelationatedTreeID** tree);
idToRelationatedTreeNum* idToTreeSuccessorNum(idToRelationatedTreeNum* node);
idToRelationatedTreeID* idToTreeSuccessorID(idToRelationatedTreeID* node);
idToRelationatedTreeNum* idToTreeMinimumNum(idToRelationatedTreeNum* box);
idToRelationatedTreeID* idToTreeMinimumID(idToRelationatedTreeID* box);
void printIdToRelationatedTreeID(idToRelationatedTreeID* tree);
void printIdToRelationatedTreeNum(idToRelationatedTreeNum* tree);
void delentHelperRel(char* idEnt, relationshipTree** relationships, relationshipTree* rel);
void recursiveDeleter(char* idEnt, idToRelationatedTreeID* idToTreeID, relationshipTree** relationships, relationshipTree* rel);
void delentHelperIdTo(char* idEnt, idToRelationatedTreeID* idToTreeID, relationshipTree** relationships, relationshipTree* rel);
char* treeMaximumRelID(relationshipTree* tree);
void report(relationshipTree* rel);
void reportRels(relationship* rel);
void reportHelper(relationshipTree* rel, char* lastRel);
int treeMaximum(idToRelationatedTreeNum* tree);
void recursiveReporter(idToRelationatedTreeNum* tree, int max);
int addStringToHashTable(char* string, char*** entities, int* length, int start);
char* deleteStringFromHashTable(char* string, char*** entities, int* length);
int searchIndexOfStringToInsertFromHashTable(char** entities, int length, int start, char* string);
int searchIndexOfStringFromHashTable(char** entities, int length, int start, char* string);
char* searchStringFromHashTable(char** entities, int length, int start, char* string);
int addStringToHashTableNoSize(char* string, char*** entities, int size, int start);
char* deleteStringFromHashTableNoSize(char* string, char*** entities, int size);
char* deleteStringFromHashTableNoSize(char* string, char*** entities, int size);
int addStringToHashTableRels(char* string, relationship** entities, int* length, int start, node* node);
relationship* deleteStringFromHashTableRels(char* string, relationship** entities, int* length);
int searchIndexOfStringToInsertFromHashTableRels(relationship* entities, int length, int start, char* string);
int searchIndexOfStringFromHashTableRels(relationship* entities, int length, int start, char* string);
relationship* searchStringFromHashTableRels(relationship* entities, int length, int start, char* string);
char* read();

int main() {

    int numOfEntities = 0;

    char** entities = NULL;
	relationship* relationships = NULL;

    char* command;
    while(1) {
        command = read();
        if(strcmp(command, "addent") == 0) {
            char* idEnt = read();
            int success = addStringToHashTable(idEnt, &entities, &numOfEntities, 0);
            if(success != 1) free(idEnt);
        } else if(strcmp(command, "addrel") == 0) {
            char* idFrom = read();
            char* idTo = read();
            char* idRel = read();
            addrel(idRel, idFrom, idTo, entities, &relationships, numOfEntities);
        } else if(strcmp(command, "delrel") == 0) {
            char* idFrom = read();
            char* idTo = read();
            char* idRel = read();
            delrel(idRel, idFrom, idTo, entities, &relationships, numOfEntities);
        } else if(strcmp(command, "delent") == 0) {
            char* idEnt = read();
            delent(idEnt, &entities, &relationships, &numOfEntities);
        } else if(strcmp(command, "report") == 0) {}//report(relationships);
        else if(strcmp(command, "end") == 0) return 0;
        else if(strcmp(command, "debug") == 0) {
            printf("\nentities:\n");
            //printEntityTree(entities);
            printf("\nrelationships\n");
            printRelationshipTree(relationships);
            printf("\n");
        }
    }
	return 0;
}

char* read() {
    char* string = calloc(30, sizeof(char));
    scanf("%s", string);
    int lenght = strlen(string);
    string = realloc(string, (lenght+1)*sizeof(char));
    return string;
}

int treeMaximum(idToRelationatedTreeNum* tree) {
    while((*tree).right != NULL) tree = (*tree).right;
    return (*tree).number;
}

char* treeMaximumRelID(relationshipTree* tree) {
    if(tree == NULL) return NULL;
    while((*tree).right != NULL) tree = (*tree).right;
    return (*tree).keyRelationshipID;
}

void report(relationshipTree* rel) {
    if(rel == NULL) {
        printf("none\n");
        return;
    }
    char* lastRel = treeMaximumRelID(rel);
    reportHelper(rel, lastRel);
}

void reportHelper(relationshipTree* rel, char* lastRel) {
    if(rel == NULL) return;
    int max = treeMaximum((*(*rel).node).num);
    reportHelper((*rel).left, lastRel);
    printf("%s", (*rel).keyRelationshipID);
    recursiveReporter((*(*rel).node).num, max);
    if(strcmp((*rel).keyRelationshipID, lastRel) != 0) printf(" %d; ", max);
    else printf(" %d;\n", max);
    reportHelper((*rel).right, lastRel);
}

void recursiveReporter(idToRelationatedTreeNum* tree, int max) {
    if(tree == NULL) return;
    recursiveReporter((*tree).left, max);
    if((*tree).number == max) printf(" %s", (*(*(*tree).node).id).idTo);
    recursiveReporter((*tree).right, max);
}

void addrel(char* idRel, char* idFrom, char* idTo, char** entities, relationshipTree** relationships, int numOfEntities) {
    char* trueIdFrom = searchStringFromHashTable(entities, numOfEntities, 0, idFrom);
    char* trueIdTo = searchStringFromHashTable(entities, numOfEntities, 0, idTo);
    free(idFrom);
    free(idTo);
    if(trueIdFrom == NULL || trueIdTo == NULL) {
        free(idRel);
        return;
    }
    relationshipTree* rel = relationshipNodeResearch(idRel, *relationships);
    if(rel == NULL) {

        //non esiste alcuna relazione di questo tipo
        relationshipTree* toInsert = calloc(1, sizeof(relationshipTree));
        (*toInsert).keyRelationshipID = idRel;
        idToRelationatedTreeID* relsByID = calloc(1, sizeof(idToRelationatedTreeID));
        idToRelationatedTreeNum* relsByNum = calloc(1, sizeof(idToRelationatedTreeNum));
        node* nRel = malloc(sizeof(node));
        (*nRel).id = relsByID;
        (*nRel).num = relsByNum;
        node* nBind = malloc(sizeof(node));
        (*nBind).id = relsByID;
        (*nBind).num = relsByNum;
        (*relsByNum).number = 1;
        (*relsByID).idTo = trueIdTo;
        (*relsByID).node = nBind;
        (*relsByNum).node = nBind;
        (*toInsert).node = nRel;
        addStringToHashTableNoSize(trueIdFrom, &((*relsByID).idFrom), 0, 0);
        addNodeToRelationshipTree(toInsert, relationships);
        return;
    } else {
        
        //esistono già relazioni di questo tipo
        free(idRel);
        idToRelationatedTreeID* idToTreeID = relationshipNodeResearchID(trueIdTo, (*(*rel).node).id);
        if(idToTreeID == NULL) {
            //è la prima relazione di questo tipo per il to
            idToRelationatedTreeID* toInsertID = calloc(1, sizeof(idToRelationatedTreeID));
            idToRelationatedTreeNum* toInsertNum = calloc(1, sizeof(idToRelationatedTreeNum));
            (*toInsertID).idTo = trueIdTo;
            (*toInsertNum).number = 1;
            node* n = malloc(sizeof(node));
            (*n).id = toInsertID;
            (*n).num = toInsertNum;
            (*toInsertID).node = n;
            (*toInsertNum).node = n;
            addStringToHashTableNoSize(trueIdFrom, &((*toInsertID).idFrom), 0, 0);
            addNodeToIdToTreeID(toInsertID, &((*(*rel).node).id));
            addNodeToIdToTreeNum(toInsertNum, &((*(*rel).node).num));
            return;
        } else {
            //il to ha già relazioni
            char* fromString = searchStringFromHashTable((*idToTreeID).idFrom, (*(*(*idToTreeID).node).num).number, 0, trueIdFrom);
            if(fromString != NULL) return;
            idToRelationatedTreeNum* box = idToRelationatedTreeNodeDeleteNum((*(*idToTreeID).node).num, &((*(*rel).node).num));
            addStringToHashTableNoSize(trueIdFrom, &((*idToTreeID).idFrom), (*box).number, 0);
            (*box).number++;
            addNodeToIdToTreeNum(box, &((*(*rel).node).num));
            return;
        }
    }
}

void delrel(char* idRel, char* idFrom, char* idTo, char** entities, relationshipTree** relationships, int numOfEntities) {
    char* trueIdFrom = searchStringFromHashTable(entities, numOfEntities, 0, idFrom);
    char* trueIdTo = searchStringFromHashTable(entities, numOfEntities, 0, idTo);
    free(idFrom);
    free(idTo);
    if(trueIdFrom == NULL || trueIdTo == NULL) {
        free(idRel);
        return;
    }
    relationshipTree* rel = relationshipNodeResearch(idRel, *relationships);
    free(idRel);
    if(rel == NULL) return;
    idToRelationatedTreeID* idToTreeID = relationshipNodeResearchID(trueIdTo, (*(*rel).node).id);
    if(idToTreeID == NULL) return;
    char* fromString = searchStringFromHashTable((*idToTreeID).idFrom, (*(*(*idToTreeID).node).num).number, 0, trueIdFrom);
    if(fromString == NULL) return;
    deleteStringFromHashTableNoSize(trueIdFrom, &((*idToTreeID).idFrom), (*(*(*idToTreeID).node).num).number);
    idToRelationatedTreeNum* boxNum = idToRelationatedTreeNodeDeleteNum((*(*idToTreeID).node).num, &((*(*rel).node).num));
    (*boxNum).number--;

    if((*boxNum).number != 0) {
        addNodeToIdToTreeNum(boxNum, &((*(*rel).node).num));
        return;
    }
    free(boxNum);
    idToRelationatedTreeID* boxID = idToRelationatedTreeNodeDeleteID(idToTreeID, &((*(*rel).node).id));
    free((*boxID).idFrom);
    free(boxID);
    if((*(*rel).node).id != NULL) return;
    relationshipTree* deleted = deleteRelationship(rel, relationships);
    free((*deleted).keyRelationshipID);
    free(deleted);
    return;
}

void delent(char* idEnt, char*** entities, relationshipTree** relationships, int* numOfEntities) {
    char* trueID = searchStringFromHashTable(*entities, *numOfEntities, 0, idEnt);
    free(idEnt);
    if(trueID == NULL) return;
    delentHelperRel(trueID, relationships, (*relationships));
    deleteStringFromHashTable(trueID, entities, numOfEntities);
    free(trueID);
}

void delentHelperRel(char* idEnt, relationshipTree** relationships, relationshipTree* rel) {
    if(rel == NULL) return;
    delentHelperRel(idEnt, relationships, (*rel).right);
    delentHelperRel(idEnt, relationships, (*rel).left);
    recursiveDeleter(idEnt, (*(*rel).node).id, relationships, rel);
}

void recursiveDeleter(char* idEnt, idToRelationatedTreeID* idToTreeID, relationshipTree** relationships, relationshipTree* rel) {
    if(idToTreeID == NULL) return;
    recursiveDeleter(idEnt, (*idToTreeID).right, relationships, rel);
    recursiveDeleter(idEnt, (*idToTreeID).left, relationships, rel);
    delentHelperIdTo(idEnt, idToTreeID, relationships, rel);
}

void delentHelperIdTo(char* idEnt, idToRelationatedTreeID* idToTreeID, relationshipTree** relationships, relationshipTree* rel) {

    node* node = (*rel).node;
    if(strcmp((*idToTreeID).idTo, idEnt) == 0) {
        idToRelationatedTreeNum* boxNum = idToRelationatedTreeNodeDeleteNum((*(*idToTreeID).node).num, &(*node).num);
        free(boxNum);
        idToRelationatedTreeID* boxID = idToRelationatedTreeNodeDeleteID(idToTreeID, &((*node).id));
        free((*boxID).idFrom);
        free(boxID);
        if((*node).id != NULL) return;
        relationshipTree* deleted = deleteRelationship(rel, relationships);
        free((*deleted).keyRelationshipID);
        free(deleted);
    } else {
        char* fromString = searchStringFromHashTable((*idToTreeID).idFrom, (*(*(*idToTreeID).node).num).number, 0, idEnt);
        if(fromString == NULL) return;
        deleteStringFromHashTableNoSize(idEnt, &((*idToTreeID).idFrom), (*(*(*idToTreeID).node).num).number);
        idToRelationatedTreeNum* boxNum = idToRelationatedTreeNodeDeleteNum((*(*idToTreeID).node).num, &((*node).num));
        (*boxNum).number--;
        if((*boxNum).number != 0) {
        addNodeToIdToTreeNum(boxNum, &((*node).num));
        return;
        }

        free(boxNum);
        idToRelationatedTreeID* boxID = idToRelationatedTreeNodeDeleteID(idToTreeID, &((*node).id));
        free((*boxID).idFrom);
        free(boxID);

        if((*node).id != NULL) return;
        relationshipTree* deleted = deleteRelationship(rel, relationships);
        free((*deleted).keyRelationshipID);
        free(deleted);

    }

}

//Box of operations for the Dynamic Array

//inserts in the table
int addStringToHashTable(char* string, char*** entities, int* length, int start) {
    if((*entities) == NULL) {
        (*entities) = malloc(sizeof(char*));
        (*entities)[0] = string;
        (*length)++;
        return 1;
    }
    int size = (*length);
    int indexWhereInsert = searchIndexOfStringToInsertFromHashTable(*entities, size, 0, string);
    if(indexWhereInsert == -1) return -1;
    (*length)++;
    (*entities) = realloc((*entities), (*length)*sizeof(char*));
    int i;
    for(i = size; i > indexWhereInsert; i--) {
        (*entities)[i] = (*entities)[i-1];
    }
    (*entities)[indexWhereInsert] = string;
    return 1;
}

//inserts in the table without changing its size
int addStringToHashTableNoSize(char* string, char*** entities, int size, int start) {
    if((*entities) == NULL) {
        (*entities) = malloc(sizeof(char*));
        (*entities)[0] = string;
        return 1;
    }
    int indexWhereInsert = searchIndexOfStringToInsertFromHashTable(*entities, size, 0, string);
    if(indexWhereInsert == -1) return -1;
    size++;
    (*entities) = realloc((*entities), (size)*sizeof(char*));
    int i;
    for(i = size-1; i > indexWhereInsert; i--) {
        (*entities)[i] = (*entities)[i-1];
    }
    (*entities)[indexWhereInsert] = string;
    return 1;
}

//deletes from the table
char* deleteStringFromHashTable(char* string, char*** entities, int* length) {
    int indexWhereDelete = searchIndexOfStringFromHashTable(*entities, *length, 0, string);
    int size = (*length);
    if(indexWhereDelete == -1) return NULL;
    char* box = (*entities)[indexWhereDelete];
    int i;
    for(i = indexWhereDelete; i < size-1; i++) {
        (*entities)[i] = (*entities)[i+1];
    }
    (*length)--;
    (*entities) = realloc((*entities), (*length)*sizeof(char*));
    return box;
}

//deletes from the table without changing its size
char* deleteStringFromHashTableNoSize(char* string, char*** entities, int size) {
    int indexWhereDelete = searchIndexOfStringFromHashTable(*entities, size, 0, string);
    if(indexWhereDelete == -1) return NULL;
    char* box = (*entities)[indexWhereDelete];
    int i;
    for(i = indexWhereDelete; i < size-1; i++) {
        (*entities)[i] = (*entities)[i+1];
    }
    size--;
    if(size == 0) {
        free((*entities));
        (*entities) = NULL;
    }
    else (*entities) = realloc((*entities), (size)*sizeof(char*));
    return box;
}

//looks up in the table for the index to insert
int searchIndexOfStringToInsertFromHashTable(char** entities, int length, int start, char* string) {
    int box = length;
    length--;
    while(start <= length) {
        int middle = start + (length-start)/2;

        if(strcmp(entities[middle], string) == 0) return -1;
        if(strcmp(entities[middle], string) > 0) {
            if(middle == 0) return 0;
            if((middle-1) >= 0 && strcmp(entities[middle-1], string) < 0) return middle;
            else length = middle - 1;
        }
        else {
            if((middle+1) == box) return box;
            if((middle+1) < box && strcmp(entities[middle+1], string) > 0) return middle+1;
            else start = middle + 1;
        }
    }
    return -1;
}

//looks up in the table for the index
int searchIndexOfStringFromHashTable(char** entities, int length, int start, char* string) {
    length--;
    while(start <= length) {
        int middle = start + (length-start)/2;

        if(strcmp(entities[middle], string) == 0) return middle;
        if(strcmp(entities[middle], string) > 0) length = middle - 1;
        else start = middle + 1;
    }
    return -1;
}

//looks up in the table
char* searchStringFromHashTable(char** entities, int length, int start, char* string) {
    length--;
    if(entities == NULL) return NULL;
    while(start <= length) {
        int middle = start + (length-start)/2;
        if(strcmp(entities[middle], string) == 0) {
            return entities[middle];
        }
        if(strcmp(entities[middle], string) > 0) length = middle - 1;
        else start = middle + 1;
    }
    return NULL;
}

//Box of operations for the Dynamic Array of rels

//inserts in the table
int addStringToHashTableRels(char* string, relationship** entities, int* length, int start, node* node) {
    if((*entities) == NULL) {
        (*entities) = malloc(sizeof(relationship*));
        (*entities)[0].keyRelationshipID = string;
        (*entities)[0].node = node;
        (*length)++;
        return 1;
    }
    int size = (*length);
    int indexWhereInsert = searchIndexOfStringToInsertFromHashTableRels(*entities, size, 0, string);
    if(indexWhereInsert == -1) return -1;
    (*length)++;
    (*entities) = realloc((*entities), (*length)*sizeof(relationship*));
    int i;
    for(i = size; i > indexWhereInsert; i--) {
        (*entities)[i].keyRelationshipID = (*entities)[i-1].keyRelationshipID;
        (*entities)[i].node = (*entities)[i-1].node;
    }
    (*entities)[indexWhereInsert].keyRelationshipID = string;
    (*entities)[indexWhereInsert].node = node;
    return 1;
}

//deletes from the table
relationship deleteStringFromHashTableRels(char* string, relationship** entities, int* length) {
    int indexWhereDelete = searchIndexOfStringFromHashTableRels(*entities, *length, 0, string);
    int size = (*length);
    if(indexWhereDelete == -1) return NULL;
    relationship box = (*entities)[indexWhereDelete];
    int i;
    for(i = indexWhereDelete; i < size-1; i++) {
        (*entities)[i].keyRelationshipID = (*entities)[i+1].keyRelationshipID;
        (*entities)[i].node = (*entities)[i+1].node;
    }
    (*length)--;
    (*entities) = realloc((*entities), (*length)*sizeof(relationship*));
    return box;
}

//looks up in the table for the index to insert
int searchIndexOfStringToInsertFromHashTableRels(relationship* entities, int length, int start, char* string) {
    int box = length;
    length--;
    while(start <= length) {
        int middle = start + (length-start)/2;

        if(strcmp(entities[middle].keyRelationshipID, string) == 0) return -1;
        if(strcmp(entities[middle].keyRelationshipID, string) > 0) {
            if(middle == 0) return 0;
            if((middle-1) >= 0 && strcmp(entities[middle-1].keyRelationshipID, string) < 0) return middle;
            else length = middle - 1;
        }
        else {
            if((middle+1) == box) return box;
            if((middle+1) < box && strcmp(entities[middle+1].keyRelationshipID, string) > 0) return middle+1;
            else start = middle + 1;
        }
    }
    return -1;
}

//looks up in the table for the index
int searchIndexOfStringFromHashTableRels(relationship* entities, int length, int start, char* string) {
    length--;
    while(start <= length) {
        int middle = start + (length-start)/2;

        if(strcmp(entities[middle].keyRelationshipID, string) == 0) return middle;
        if(strcmp(entities[middle].keyRelationshipID, string) > 0) length = middle - 1;
        else start = middle + 1;
    }
    return -1;
}

//looks up in the table
relationship* searchStringFromHashTableRels(relationship* entities, int length, int start, char* string) {
    length--;
    if(entities == NULL) return NULL;
    while(start <= length) {
        int middle = start + (length-start)/2;
        if(strcmp(entities[middle].keyRelationshipID, string) == 0) {
            return entities[middle];
        }
        if(strcmp(entities[middle].keyRelationshipID, string) > 0) length = middle - 1;
        else start = middle + 1;
    }
    return NULL;
}

//Box of operations for the Entity Tree

//Adds a string to the tree in an ordered way.
int addStringToEntityTree(char* string, entityTree** entities) {
    entityTree* boxTree = (*entities);
    entityTree* boxFather = NULL;

    while(boxTree != NULL) {
        boxFather = boxTree;
        int cmp = strcmp(string, (*boxTree).entityID);
        if(cmp == 0) {
            return -1;
        }
        if(cmp < 0) boxTree = (*boxTree).left;
        else boxTree = (*boxTree).right;
    }

    entityTree* node = calloc(1, sizeof(entityTree));
    (*node).entityID = string;
    (*node).father = boxFather;

    if(boxFather == NULL) {
        (*entities) = node;
        return 1;
    }

    int cmp = strcmp(string, (*boxFather).entityID);

    if(cmp < 0) (*boxFather).left = node;
    else (*boxFather).right = node;

    return 1;
}

//Deletes an entity from the tree of entities
void deleteEntityTreeHelper(char* idEnt, entityTree** entities) {
    entityTree* toDelete = entityNodeResearch(idEnt, (*entities));
    entityDelete(toDelete, entities);
}

//Looks for an entity ID in the tree of entities, returns null if the entities does not exists
char* entityIDResearch(char* idEnt, entityTree* entities) {
    if(entities == NULL) return NULL;
    int cmp = strcmp(idEnt, (*entities).entityID);
    if(cmp == 0) return (*entities).entityID;
    if(cmp < 0) return entityIDResearch(idEnt, (*entities).left);
    return entityIDResearch(idEnt, (*entities).right);
}

//Looks for a node with a specific entity ID in the tree of entities, returns null if the entities does not exists
entityTree* entityNodeResearch(char* idEnt, entityTree* entities) {
    if(entities == NULL) return NULL;
    int cmp = strcmp(idEnt, (*entities).entityID);
    if(cmp == 0) return entities;
    if(cmp < 0) return entityNodeResearch(idEnt, (*entities).left);
    return entityNodeResearch(idEnt, (*entities).right);
}

//Deletes an ID in the tree of entities
void entityDelete(entityTree* toDelete, entityTree** entities) {
    entityTree* ybox;
    entityTree* xbox;
    if((*toDelete).left == NULL || (*toDelete).right == NULL)
        ybox = toDelete;
    else ybox = treeSuccessor(toDelete);
    if((*ybox).left != NULL) xbox = (*ybox).left;
    else xbox = (*ybox).right;
    if(xbox != NULL) (*xbox).father = (*ybox).father;
    if((*ybox).father == NULL) (*entities) = xbox;
    else if(ybox == (*(*ybox).father).left) (*(*ybox).father).left = xbox;
    else (*(*ybox).father).right = xbox;
    if(ybox != toDelete) {
        char* stringToDelete = (*toDelete).entityID;
        (*toDelete).entityID = (*ybox).entityID;
    }
    free(ybox);
}

//Looks for the tree successor of the provided node
entityTree* treeSuccessor(entityTree* entities) {
    if((*entities).right != NULL)
        return treeMinimum((*entities).right);
    entityTree* box = (*entities).father;
    while(box != NULL && entities == (*box).right) {
        entities = box;
        box = (*box).father;
    }
    return box;
}

//Looks for a the minimum in a tree
entityTree* treeMinimum(entityTree* box) {
    while((*box).left != NULL)
        box = (*box).left;
    return box;    
}

//prints the entity tree
void printEntityTree(entityTree* tree) {
    if(tree != NULL) {
    	printEntityTree((*tree).left);
        printf((*tree).entityID);
        printf("; ");
        printEntityTree((*tree).right);
	}
}

//Box of operations for the Relationship Tree

//Adds a node to the tree in an ordered way.
void addNodeToRelationshipTree(relationshipTree* node, relationshipTree** relationships) {
    
    relationshipTree* boxTree = (*relationships);
    relationshipTree* boxFather = NULL;

    while(boxTree != NULL) {
        boxFather = boxTree;
        int cmp = strcmp((*node).keyRelationshipID, (*boxTree).keyRelationshipID);
        if(cmp == 0) {
            return;
        }
        if(cmp < 0) boxTree = (*boxTree).left;
        else boxTree = (*boxTree).right;
    }

    (*node).father = boxFather;

    if(boxFather == NULL) {
        (*relationships) = node;
        return;
    }

    int cmp = strcmp((*node).keyRelationshipID, (*boxFather).keyRelationshipID);

    if(cmp < 0) (*boxFather).left = node;
    else (*boxFather).right = node;

}

//Looks for a node with a specific relationship ID in the tree of relationships, returns null if the relationship does not exists
relationshipTree* relationshipNodeResearch(char* relationshipID, relationshipTree* relationshipTree) {
    if(relationshipTree == NULL) return NULL;
    int cmp = strcmp(relationshipID, (*relationshipTree).keyRelationshipID);
    if(cmp == 0) return relationshipTree;
    if(cmp < 0) return relationshipNodeResearch(relationshipID, (*relationshipTree).left);
    return relationshipNodeResearch(relationshipID, (*relationshipTree).right);
}

//Deletes a relationship in the tree of relationships
relationshipTree* deleteRelationship(relationshipTree* toDelete, relationshipTree** tree) {
    relationshipTree* ybox;
    relationshipTree* xbox;
    if((*toDelete).left == NULL || (*toDelete).right == NULL)
        ybox = toDelete;
    else ybox = relationshipTreeSuccessor(toDelete);
    if((*ybox).left != NULL) xbox = (*ybox).left;
    else xbox = (*ybox).right;
    if(xbox != NULL) (*xbox).father = (*ybox).father;
    if((*ybox).father == NULL) (*tree) = xbox;
    else if(ybox == (*(*ybox).father).left) (*(*ybox).father).left = xbox;
    else (*(*ybox).father).right = xbox;
    if(ybox != toDelete) {
        //conservo i valori
        (*toDelete).keyRelationshipID = (*ybox).keyRelationshipID;
        (*toDelete).node = (*ybox).node;
    }
    return ybox;
}

//Looks for the tree successor of the provided node
relationshipTree* relationshipTreeSuccessor(relationshipTree* node) {
    if((*node).right != NULL)
        return relationshipTreeMinimum((*node).right);
    relationshipTree* box = (*node).father;
    while(box != NULL && node == (*box).right) {
        node = box;
        box = (*box).father;
    }
    return box;
}
//Looks for a the minimum in a tree
relationshipTree* relationshipTreeMinimum(relationshipTree* box) {
    while((*box).left != NULL)
        box = (*box).left;
    return box;    
}

//prints the entity tree
void printRelationshipTree(relationshipTree* tree) {
    if(tree != NULL) {
    	printRelationshipTree((*tree).left);
        printf("[rel:\n");
        printf((*tree).keyRelationshipID);
        printf("\trelsByID -> ");
        printIdToRelationatedTreeID((*(*tree).node).id);
        printf("\n\trelsByNum -> ");
        printIdToRelationatedTreeNum((*(*tree).node).num);
        printf("];\n");
        printRelationshipTree((*tree).right);
	}
}

//Box of operations for the idToRelationed Tree 

//Looks for a node with a specific relationship ID in the tree of relationships, returns null if the relationship does not exists
idToRelationatedTreeID* relationshipNodeResearchID(char* idTo, idToRelationatedTreeID* tree) {
    if(tree == NULL) return NULL;
    int cmp = strcmp(idTo, (*tree).idTo);
    if(cmp == 0) return tree;
    if(cmp < 0) return relationshipNodeResearchID(idTo, (*tree).left);
    return relationshipNodeResearchID(idTo, (*tree).right);
}

//Adds a node to the tree in an ordered way (id).
void addNodeToIdToTreeID(idToRelationatedTreeID* node, idToRelationatedTreeID** tree) {
    
    idToRelationatedTreeID* boxTree = (*tree);
    idToRelationatedTreeID* boxFather = NULL;

    while(boxTree != NULL) {
        boxFather = boxTree;
        int cmp = strcmp((*node).idTo, (*boxTree).idTo);
        if(cmp == 0) {
            return;
        }
        if(cmp < 0) boxTree = (*boxTree).left;
        else boxTree = (*boxTree).right;
    }

    (*node).father = boxFather;

    if(boxFather == NULL) {
        (*tree) = node;
        return;
    }

    int cmp = strcmp((*node).idTo, (*boxFather).idTo);

    if(cmp < 0) (*boxFather).left = node;
    else (*boxFather).right = node;

}

//Adds a node to the tree in an ordered way (num).
void addNodeToIdToTreeNum(idToRelationatedTreeNum* node, idToRelationatedTreeNum** tree) {
    
    idToRelationatedTreeNum* boxTree = (*tree);
    idToRelationatedTreeNum* boxFather = NULL;

    while(boxTree != NULL) {
        boxFather = boxTree;
        if((*node).number < (*boxTree).number) boxTree = (*boxTree).left;
        else if((*node).number == (*boxTree).number && strcmp((*(*(*node).node).id).idTo, (*(*(*boxTree).node).id).idTo) < 0) boxTree = (*boxTree).left;
        else boxTree = (*boxTree).right;
    }

    (*node).father = boxFather;

    if(boxFather == NULL) {
        (*tree) = node;
        return;
    }

    if((*node).number < (*boxFather).number) (*boxFather).left = node;
    else if((*node).number == (*boxFather).number && strcmp((*(*(*node).node).id).idTo, (*(*(*boxFather).node).id).idTo) < 0) (*boxFather).left = node;
    else (*boxFather).right = node;

}

//Deletes an idToNum in the tree of relationatedNum
idToRelationatedTreeNum* idToRelationatedTreeNodeDeleteNum(idToRelationatedTreeNum* toDelete, idToRelationatedTreeNum** tree) {

    idToRelationatedTreeNum* point = (*(*toDelete).node).num;
    idToRelationatedTreeID* pointID = (*(*point).node).id;

    idToRelationatedTreeNum* ybox;
    idToRelationatedTreeNum* xbox;
    if((*toDelete).left == NULL || (*toDelete).right == NULL)
        ybox = toDelete;
    else ybox = idToTreeSuccessorNum(toDelete);
    if((*ybox).left != NULL) xbox = (*ybox).left;
    else xbox = (*ybox).right;
    if(xbox != NULL) (*xbox).father = (*ybox).father;
    if((*ybox).father == NULL) (*tree) = xbox;
    else if(ybox == (*(*ybox).father).left) (*(*ybox).father).left = xbox;
    else (*(*ybox).father).right = xbox;

    point = (*(*toDelete).node).num;
    pointID = (*(*point).node).id;

    if(ybox != toDelete) {
        if((*toDelete).father == NULL) {
            (*tree) = ybox;
        }
        if(ybox != (*toDelete).right) {
            (*ybox).right = (*toDelete).right;
            (*ybox).left = (*toDelete).left;
            (*ybox).father = (*toDelete).father;
            if((*toDelete).right != NULL) (*(*toDelete).right).father = ybox;
            if((*toDelete).left != NULL) (*(*toDelete).left).father = ybox;
            if((*toDelete).father != NULL) {
                if((*(*toDelete).father).left == toDelete) (*(*toDelete).father).left = ybox;
                else (*(*toDelete).father).right = ybox;
            }
        } else {
            (*ybox).left = (*toDelete).left;
            (*ybox).father = (*toDelete).father;
            if((*toDelete).left != NULL) (*(*toDelete).left).father = ybox;
            if((*toDelete).father != NULL) {
                if((*(*toDelete).father).left == toDelete) (*(*toDelete).father).left = ybox;
                else (*(*toDelete).father).right = ybox;
            }
        }
    }
    (*toDelete).right = NULL;
    (*toDelete).left = NULL;
    (*toDelete).father = NULL;
    
    return toDelete;
}

//Deletes an idToID in the tree of relationatedId
idToRelationatedTreeID* idToRelationatedTreeNodeDeleteID(idToRelationatedTreeID* toDelete, idToRelationatedTreeID** tree) {
    idToRelationatedTreeID* ybox;
    idToRelationatedTreeID* xbox;
    if((*toDelete).left == NULL || (*toDelete).right == NULL)
        ybox = toDelete;
    else ybox = idToTreeSuccessorID(toDelete);
    if((*ybox).left != NULL) xbox = (*ybox).left;
    else xbox = (*ybox).right;
    if(xbox != NULL) (*xbox).father = (*ybox).father;
    if((*ybox).father == NULL) (*tree) = xbox;
    else if(ybox == (*(*ybox).father).left) (*(*ybox).father).left = xbox;
    else (*(*ybox).father).right = xbox;
    if(ybox != toDelete) {
        if((*toDelete).father == NULL) (*tree) = ybox;
        if(ybox != (*toDelete).right) {
            (*ybox).right = (*toDelete).right;
            (*ybox).left = (*toDelete).left;
            (*ybox).father = (*toDelete).father;
            if((*toDelete).right != NULL) (*(*toDelete).right).father = ybox;
            if((*toDelete).left != NULL) (*(*toDelete).left).father = ybox;
            if((*toDelete).father != NULL) {
                if((*(*toDelete).father).left == toDelete) (*(*toDelete).father).left = ybox;
                else (*(*toDelete).father).right = ybox;
            }
        } else {
            (*ybox).left = (*toDelete).left;
            (*ybox).father = (*toDelete).father;
            if((*toDelete).left != NULL) (*(*toDelete).left).father = ybox;
            if((*toDelete).father != NULL) {
                if((*(*toDelete).father).left == toDelete) (*(*toDelete).father).left = ybox;
                else (*(*toDelete).father).right = ybox;
            }
        }
    }
    (*toDelete).right = NULL;
    (*toDelete).left = NULL;
    (*toDelete).father = NULL;
    return toDelete;

    idToRelationatedTreeNum* point = (*(*toDelete).node).num;
    idToRelationatedTreeID* pointID = (*(*point).node).id;

    idToRelationatedTreeNum* apoint = (*(*ybox).node).num;
    idToRelationatedTreeID* apointID = (*(*apoint).node).id;
}

//Looks for the tree successor of the provided node
idToRelationatedTreeNum* idToTreeSuccessorNum(idToRelationatedTreeNum* node) {
    if((*node).right != NULL)
        return idToTreeMinimumNum((*node).right);
    idToRelationatedTreeNum* box = (*node).right;
    while(box != NULL && node == (*box).right) {
        node = box;
        box = (*box).father;
    }
    return box;
}

//Looks for the tree successor of the provided node
idToRelationatedTreeID* idToTreeSuccessorID(idToRelationatedTreeID* node) {
    if((*node).right != NULL)
        return idToTreeMinimumID((*node).right);
    idToRelationatedTreeID* box = (*node).father;
    while(box != NULL && node == (*box).right) {
        node = box;
        box = (*box).father;
    }
    return box;
}

//Looks for a the minimum in a tree
idToRelationatedTreeNum* idToTreeMinimumNum(idToRelationatedTreeNum* box) {
    while((*box).left != NULL)
        box = (*box).left;
    return box;    
}

//Looks for a the minimum in a tree
idToRelationatedTreeID* idToTreeMinimumID(idToRelationatedTreeID* box) {
    while((*box).left != NULL)
        box = (*box).left;
    return box;    
}

//prints the entity tree
void printIdToRelationatedTreeID(idToRelationatedTreeID* tree) {
    if(tree != NULL) {
    	printIdToRelationatedTreeID((*tree).left);
        printf("[to: ");
        printf((*tree).idTo);
        printf(", from: {");
        printf("}; ");
        printIdToRelationatedTreeID((*tree).right);
	}
}

//prints the entity tree
void printIdToRelationatedTreeNum(idToRelationatedTreeNum* tree) {
    if(tree != NULL) {
    	printIdToRelationatedTreeNum((*tree).left);
        printf("[to: ");
        printf((*(*(*tree).node).id).idTo);
        printf(", number: %d]; ", (*tree).number);
        printIdToRelationatedTreeNum((*tree).right);
	}
}
