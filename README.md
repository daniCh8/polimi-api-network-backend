# [Algorithms and Data Structures](https://www4.ceda.polimi.it/manifesti/manifesti/controller/ManifestoPublic.do?EVN_DETTAGLIO_RIGA_MANIFESTO=EVENTO&c_insegn=086067&aa=2018&k_cf=225&k_corso_la=358&ac_ins=0&k_indir=IT1&lang=EN&tipoCorso=ALL_TIPO_CORSO&semestre=2&idItemOfferta=139718&idRiga=234137&codDescr=086067) 2019, Course Project

## Project Description

The goal of this project was to apply the knowledge acquired through the course to build the backend of a (not too advanced) social network in C. Such backend should be as efficient as possible, both in terms of memory and speed.

More specifically, the aim was to code a mechanism able to monitor dynamic relationships between different entities. The social network comparison comes handy: new entities can register to the program, but also old entities may delete their account. Entities can also start new _relationships_ between them, or end old ones. Such relationships may not be symmetric (X may be friend of Y, but not viceversa). Also, such relationships are not static: any new type of relationship between two entities can be added on the fly.

## Possible Actions

Here is a table with all the possible inputs of the program, together with a short description of each one.

| Input Code | Description                    |
| ------------- | ------------------------------ |
| `addent <id_ent>` | Adds an entity with name _id_ent_; if an entity with the same _id_ent_ already exists, nothing happens. |
| `delent <id_ent>` | Deletes the entity with name _id_ent_ and all the relationships where such entity was involved. |
| `addrel <id_orig> <id_dest> <id_rel>` | Adds the relationship with name _id_rel_ from _id_orig_ to _id_dest_. If such relationship already exists or one of the two entities doesn't exist, nothing happens. |
| `delrel <id_orig> <id_dest> <id_rel>` | Deletes the relationship with name _id_rel_ from _id_orig_ to _id_dest_. If such relationship doesn't exist, nothing happens. |
| `report` | Outputs the list of active relationships, reporting for each one the entities with the maximum number of relationships of that type received. |
| `end` | Ends the program. |

## Sample Output

```sh
> addent "alice"
> addent "bruno"
> addent "carlo"
> addent "dario"
> report
none
> addrel "carlo" "bruno" "amico_di"
> report 
"amico_di" "bruno" 1;
> addrel "carlo" "alice" "amico_di"
> report
"amico_di" "alice" "bruno" 1;
> addrel "alice" "bruno" "amico_di"
> report
"amico_di" "bruno" 2;
> addrel "bruno" "dario" "compagno_di"
> report 
"amico_di" "bruno" 2; "compagno_di" "dario" 1;
> delrel "carlo" "alice" "amico_di"
> report
"amico_di" "bruno" 2; "compagno_di" "dario" 1;
> addrel "carlo" "alice" "compagno_di"
> report
"amico_di" "bruno" 2; "compagno_di" "alice" "dario" 1;
> addrel "carlo" "bruno" "compagno_di"
> report
"amico_di" "bruno" 2; "compagno_di" "alice" "bruno" "dario" 1;
> delent "alice"
> report
"amico_di" "bruno" 1; "compagno_di" "bruno" "dario" 1;
> end
```

## Implementations

There are three variants I coded to solve this project. The first two are more a textbook-solution and are very similar between each others whereas the other one is slightly more an out-of-the box one.

### `r&b` Variant

This solution uses only red and black trees to tackle the problem: [here](/src/r&b_version.c) is the code. There are two r&b trees: one that saves the relationships and one that saves the entities. Every node inside the relationships tree has a reference to the entities that are involved inside the relationship. Every inner relationship tree is also ordered in terms of number of relationship receiver in order to speed-up the reports. If you want to dig deeper, the code is quite documented.

### `r&b+hashTable` Variant

This solution is almost the same as the one above, but uses hash tables instead of red and black trees to save the entities. This resulted in a slight improvement in terms of performances with respect to the solution that only used red and black trees. [Here](/src/r&b+hashTable_version.c) is the code: as the one above, the functions are moderately documented if you'd like to take a peek of the code.

### `final` Variant

This solution does not use many structures taught in the course, but achieves satisfying results. The code is built around the `Relationship` struct, which is an ad-hoc structure that captures all the relevant information of a relationship (its `id`, its `max` number, the most entities that receive it and all the couples that have a relationship of such type). A vector of such structures is built at the beginning and kept sorted throughout the execution of the program. Every operation is very efficient using this arrangement but the `delent`: this one requires a full search for the entities that are involved in every relationship. However, the overall performances of this solution show that `delent` doesn't slow too much the executions (also because it's by far the least used command in the system). [Here](/src/final_version.c) is the code, documented as the ones above.