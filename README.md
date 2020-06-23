# [Algorithms and Data Structures](https://www4.ceda.polimi.it/manifesti/manifesti/controller/ManifestoPublic.do?EVN_DETTAGLIO_RIGA_MANIFESTO=evento&aa=2018&k_cf=225&k_corso_la=358&k_indir=IT1&codDescr=086067&lang=IT&semestre=2&anno_corso=2&idItemOfferta=139718&idRiga=234137) 2019, Course Project

## Project Description
The goal of this project was to apply the knowledge acquired through the course to build the backend of a (not too advanced) social network in C. Such backend should be as efficient as possible, both in terms of memory and speed.

More specifically, the aim was to code a mechanism able to monitor dynamic relationship between different entities. The social network comparison comes handy: new entities can register to the program, but also old entities may delete their account. Entities can also start new _relationships_ between them, or end old ones. Such relationships may not be symmetric (X may be friend of Y, but not viceversa). Also, such relationships are not static: any new type of relationship between two entities can be added on the fly.

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