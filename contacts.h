#ifndef contacts_H
#define contacts_H

typedef struct lpers LPERS;

extern LPERS* rep[26];

void instialRep();
int check_validity(char email[50]);
LPERS* create_Contact(char*nom,char*prenom,int age,char genre,char*email );
void add_person(LPERS*pers);
void display_persons_starting_with_letter(char lettre);
void delete_a_person_from_their_name(char*nom);
void quit();
LPERS* search(char *nom);
void modify_person(LPERS*y,char*nom, char*prenom,int age, char genre, char*email);
void show_person(LPERS*y);


#endif