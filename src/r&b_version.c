#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRLEN 30

typedef struct entityTree entityTree;
typedef struct relationshipTree relationshipTree;
typedef struct idToRelationatedTreeNum idToRelationatedTreeNum;
typedef struct idToRelationatedTreeID idToRelationatedTreeID;
typedef struct node node;

struct entityTree{
    char* entityID;
    entityTree* father;
    entityTree* right;
    entityTree* left;
};

struct relationshipTree{
    char* keyRelationshipID;
    
    node* node;

    relationshipTree* father;
    relationshipTree* right;
    relationshipTree* left;
};

struct idToRelationatedTreeID{
    char* idTo;
    entityTree* idFrom;

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

void addrel(char* idRel, char* idFrom, char* idTo, entityTree** entities, relationshipTree** relationships);
void delrel(char* idRel, char* idFrom, char* idTo, entityTree** entities, relationshipTree** relationships);
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
void delent(char* idEnt, entityTree** entities, relationshipTree** relationships);
void delentHelperRel(char* idEnt, relationshipTree** relationships, relationshipTree* rel);
void recursiveDeleter(char* idEnt, idToRelationatedTreeID* idToTreeID, relationshipTree** relationships, relationshipTree* rel);
void delentHelperIdTo(char* idEnt, idToRelationatedTreeID* idToTreeID, relationshipTree** relationships, relationshipTree* rel);
char* treeMaximumRelID(relationshipTree* tree);
void report(relationshipTree* rel);
void reportHelper(relationshipTree* rel, char* lastRel);
int treeMaximum(idToRelationatedTreeNum* tree);
void recursiveReporter(idToRelationatedTreeNum* tree, int max);
char* read();

int main() {

    entityTree* entities = NULL;
    relationshipTree* relationships = NULL;

    char* command;
    while(1) {
        command = read();
        if(strcmp(command, "addent") == 0) {
            char* idEnt = read();
            int success = addStringToEntityTree(idEnt, &entities);
            if(success != 1) free(idEnt);
        } else if(strcmp(command, "addrel") == 0) {
            char* idFrom = read();
            char* idTo = read();
            char* idRel = read();
            addrel(idRel, idFrom, idTo, &entities, &relationships);
        } else if(strcmp(command, "delrel") == 0) {
            char* idFrom = read();
            char* idTo = read();
            char* idRel = read();
            delrel(idRel, idFrom, idTo, &entities, &relationships);
        } else if(strcmp(command, "delent") == 0) {
            char* idEnt = read();
            delent(idEnt, &entities, &relationships);
        } else if(strcmp(command, "report") == 0) report(relationships);
        else if(strcmp(command, "end") == 0) return 0;
        else if(strcmp(command, "debug") == 0) {
            printf("\nentities:\n");
            printEntityTree(entities);
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

void addrel(char* idRel, char* idFrom, char* idTo, entityTree** entities, relationshipTree** relationships) {
    char* trueIdFrom = entityIDResearch(idFrom, *entities);
    char* trueIdTo = entityIDResearch(idTo, *entities);
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
        addStringToEntityTree(trueIdFrom, &((*relsByID).idFrom));
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
            addStringToEntityTree(trueIdFrom, &((*toInsertID).idFrom));
            addNodeToIdToTreeID(toInsertID, &((*(*rel).node).id));
            addNodeToIdToTreeNum(toInsertNum, &((*(*rel).node).num));
            return;
        } else {
            //il to ha già relazioni
            entityTree* fromNode = entityNodeResearch(trueIdFrom, (*idToTreeID).idFrom);
            if(fromNode != NULL) return;
            addStringToEntityTree(trueIdFrom, &((*idToTreeID).idFrom));

            idToRelationatedTreeNum* point = (*(*idToTreeID).node).num;
            idToRelationatedTreeID* pointID = (*(*point).node).id;
            idToRelationatedTreeNum* box = idToRelationatedTreeNodeDeleteNum((*(*idToTreeID).node).num, &((*(*rel).node).num));
            (*box).number++;
            addNodeToIdToTreeNum(box, &((*(*rel).node).num));
            return;
        }
    }
}

void delrel(char* idRel, char* idFrom, char* idTo, entityTree** entities, relationshipTree** relationships) {
    char* trueIdFrom = entityIDResearch(idFrom, *entities);
    char* trueIdTo = entityIDResearch(idTo, *entities);
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
    entityTree* fromNode = entityNodeResearch(trueIdFrom, (*idToTreeID).idFrom);
    if(fromNode == NULL) return;
    deleteEntityTreeHelper(trueIdFrom, &((*idToTreeID).idFrom));
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

void delent(char* idEnt, entityTree** entities, relationshipTree** relationships) {
    char* trueID = entityIDResearch(idEnt, *entities);
    free(idEnt);
    if(trueID == NULL) return;
    delentHelperRel(trueID, relationships, (*relationships));
    deleteEntityTreeHelper(trueID, entities);
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
        entityTree* fromNode = entityNodeResearch(idEnt, (*idToTreeID).idFrom);
        if(fromNode == NULL) return;
        deleteEntityTreeHelper(idEnt, &((*idToTreeID).idFrom));
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
        printEntityTree((*tree).idFrom);
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
