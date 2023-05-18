#include "contacts.h"
#include <stdio.h>


int main()
{

    instialRep();

    LPERS *pers=NULL;
    LPERS *pointpers=NULL;
    char nom[50], prenom[50], genre ,let, email[50];
    int age, choix;

    do
    {
        do
        {
            printf("\nWhat do you want to do?\n\n");
            printf(" \t \tMenu \n");
            printf("1- Add a person\n");
            printf("2- Remove a person\n");
            printf("3- Search for a person\n");
            printf("4- Modify a person\n");
            printf("5- Display the list of people whose names start with the same letter\n");
            printf("6- Quit\n");
            printf("Enter your choice: ");
            scanf(" %d", &choix);
        }while(choix<1 || choix >6);
        switch (choix)
        {
            case 1 :
                printf("Enter all the information of the person\n");
                printf("Enter the name (the first letter in capital):  ");
                scanf(" %s", nom);
                printf("Enter the first name: ");
                scanf(" %s", prenom);
                printf("Enter the age: ");
                scanf(" %d",&age);
                printf("Enter your gender: ");
                scanf(" %c", &genre);
                printf("Enter email: ");
                scanf(" %s", email);
                pers=create_Contact(nom,prenom,age,genre,email);
                add_person(pers);
                break;

            case 2 : 	printf("Enter the name of the person you want to delete: \n");
                scanf("%s", nom);
                delete_a_person_from_their_name(nom);
                break;

            case 3 : 	printf("Enter the name of the person you want to search: ");
                scanf(" %s", nom);
                pointpers=search(nom);
                show_person(pointpers);
                break;

            case 4 :	printf("Enter the name of the person you want to modify: ");
                scanf(" %s", nom);
                pointpers=search(nom);
                printf("Enter the name: ");
                scanf(" %s", nom);
                printf("Enter the new first name: ");
                scanf(" %s", prenom);
                printf("Enter the new email: ");
                scanf(" %s", email);
                printf("Enter the new age: ");
                scanf(" %d", &age);
                printf("Enter the new gender: ");
                scanf(" %c",&genre);
                modify_person(pointpers,nom, prenom,age, genre, email);
                break;

            case 5 : 	printf("Enter the letter: ");
                scanf(" %c" ,&let);
                display_persons_starting_with_letter(let);
                break;

            case 6 :	quit();
        }
    }while(choix!=6);
    return 0;
}
