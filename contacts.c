#include "contacts.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct lpers
{
    char nom[50];
    char prenom[50];
    int age;
    char genre;
    char email[50] ;
    struct lpers*next;
}
        LPERS;

LPERS* rep[26];


void instialRep()
{
    int i;
    for(i=0;i<26;i++)
    {
        rep[i]=NULL;
    }
    return;
}


int check_validity(char email[50])
{
    int i=0,z;
    int l=strlen(email);

    while(islower(email[i])!=0 || isdigit(email[i])!=0)
        i++;
    if (email[i]!='@')
        return 0;
    for(z=i+1;z<=l-5;z++)
    {
        if (islower(email[z])!=0)
            continue;
        else
            return 0;
    }
    if((email[l-4]=='.' && email[l-3]=='c' && email[l-2]=='o' && email[l-1]=='m')|| (islower(email[l-4])!=0 && email[l-3]=='.' && email[l-2]=='f' && email[l-1]=='r'))
        return 1;
    return 0;
}


LPERS* create_Contact(char*nom,char*prenom,int age,char genre,char*email )
{
    LPERS *pers;

    pers=(LPERS*)malloc(sizeof(LPERS));
    strcpy(pers->nom,nom);
    strcpy(pers->prenom,prenom);
    strcpy(pers->email,email);
    if(check_validity( pers->email)==0)
    {
        do{
            printf("The email is invalid, please enter the email again (try to respect the form abc@def.fr||.com):  ");
            scanf("%s",pers->email);
        }while(check_validity(pers->email)==0);
    }
    pers->age=age;
    pers->genre=genre ;
    pers->next=NULL;
    return pers ;

}


void add_person(LPERS*pers)
{
    LPERS*current=rep[pers->nom[0]-65];
    //empty list
    if (rep[pers->nom[0]-65]==NULL)
    {
        pers->next=NULL;
        rep[pers->nom[0]-65]=pers;
        return;
    }
        //1 single cell
    else if (rep[pers->nom[0]-65]->next==NULL)
    {
        if (strcmp((rep[pers->nom[0]-65]->nom),pers->nom)<0)
        {
            pers->next=NULL;
            rep[pers->nom[0]-65]->next=pers;

            return;
        }
        else if (strcmp(rep[pers->nom[0]-65]->nom,pers->nom)>0)
        {
            pers->next=rep[pers->nom[0]-65];
            rep[pers->nom[0]-65]=pers;
            return;
        }
        else
        {
            if (strcmp(rep[pers->nom[0]-65]->prenom,pers->prenom)<0)
            {
                pers->next=NULL;
                rep[pers->nom[0]-65]->next=pers;
                return;
            }
            else
            {
                pers->next=rep[pers->nom[0]-65];
                rep[pers->nom[0]-65]=pers;
                return;
            }
        }
    }
        //More than 2 cells
    else
    {
        if(strcmp(rep[pers->nom[0]-65]->nom,pers->nom)>=0)
        {
            if(strcmp(rep[pers->nom[0]-65]->nom,pers->nom)>0)
            {
                pers->next=rep[pers->nom[0]-65];
                rep[pers->nom[0]-65]=pers;
                return;
            }
            else
            {
                if(strcmp(rep[pers->nom[0]-65]->prenom,pers->prenom)>=0)
                {
                    pers->next=rep[pers->nom[0]-65];
                    rep[pers->nom[0]-65]=pers;
                    return;
                }
                else
                {
                    pers->next=rep[pers->nom[0]-65]->next;
                    rep[pers->nom[0]-65]->next=pers;
                    return;
                }
            }
        }
        else
        {
            while(current->next!=NULL )
            {
                if (strcmp(current->next->nom,pers->nom)<0)
                {
                    current=current->next;
                    //continue;
                }
                else
                    break;
            }

            if(current->next!=NULL)
            {
                if(strcmp(current->next->nom,pers->nom)>0)
                {
                    pers->next=current->next;
                    current->next=pers;
                    return;
                }
                else
                {
                    if(strcmp(current->next->prenom,pers->prenom)>=0)
                    {
                        pers->next=current->next;
                        current->next=pers;
                        return;
                    }
                    else
                    {
                        if(current->next->next!=NULL)
                        {
                            do
                            {

                                if(strcmp(current->next->prenom,pers->prenom)<0)
                                    current=current->next;
                                else
                                    break;

                            }while (current->next!=NULL);
                            if(current->next==NULL)
                            {
                                pers->next=NULL;
                                current->next=pers;
                                return;
                            }
                            else
                            {
                                pers->next=current->next;
                                current->next=pers;
                                return;
                            }
                        }
                        else
                        {
                            pers->next=NULL;
                            current->next->next=pers;
                            return;
                        }


                        return;
                    }
                }
            }
            else
            {
                pers->next=NULL;
                current->next=pers;
                return;
            }
        }
    }
}


void display_persons_starting_with_letter(char lettre)
{

    LPERS* debut=rep[lettre-65];
    if(debut==NULL)
    {
        printf("Nothing to show.\n");
        return;
    }
    else
    {
        while(debut!=NULL)
        {
            printf("Nom: %s\n", debut->nom);
            printf("First name: %s\n", debut->prenom);
            printf("Age: %d\n", debut->age);
            printf("Gender: %c\n", debut->genre);
            printf("Email: %s\n" ,debut->email);
            debut=debut->next;
        }
        return;
    }

}


void delete_a_person_from_their_name(char*nom)
{
    LPERS* prec=NULL;
    LPERS* current=rep[nom[0]-65];
    LPERS* reserv=NULL;

    if (rep[nom[0]-65]==NULL)
    {
        printf("This list is empty.\n");
        return;
    }
    else if (strcmp(rep[nom[0]-65]->nom,nom)==0)
    {
        reserv=rep[nom[0]-65];
        rep[nom[0]-65]=rep[nom[0]-65]->next;
        free(reserv);
        while(rep[nom[0]-65]!=NULL && strcmp(rep[nom[0]-65]->nom,nom)==0)
        {
            reserv=rep[nom[0]-65];
            rep[nom[0]-65]=rep[nom[0]-65]->next;
            free(reserv);
            if(rep[nom[0]-65]==NULL)
            {
                printf("all the persons with the name %s are deleted",nom);
                return;
            }
        }
        printf("the person is deleted successfully");
        return;
    }
    else
    {
        while(current!=NULL && strcmp(current->nom,nom)!=0)
        {
            prec=current;
            current=current->next;
            if (current==NULL)
            {
                printf("The name you entered does not exist.\n");
                return;
            }
        }
        if(current!=NULL)
        {
            reserv=current;
            current=current->next;
            prec->next=current;
            free(reserv);
            while(current!=NULL && strcmp(current->nom,nom)==0)
            {
                reserv=current;
                current=current->next;
                prec->next=current;
                free(reserv);
            }
            printf("all the persons with the name %s are deleted",nom);
            return;
        }
    }
}


void quit()
{
    exit(0);
}


LPERS* search(char *nom)
{
    LPERS* debut= rep[nom[0]-65];
    int i, rang,c;
    LPERS* prem;
    while(debut!=NULL)
    {
        if(strcmp(debut->nom,nom)!=0)
        {
            debut=debut->next;
        }
        else
        {
            c=1;
            prem=debut;
            debut=debut->next;

            if( debut!=NULL && strcmp(debut->nom,nom)!=0)
            {
                return prem;
            }
            else if (debut==NULL)
            {
                return prem;
            }
            else
            {
                printf("%d\n", c);
                printf("Nom: %s\n", prem->nom);
                printf("First name: %s\n", prem->prenom);
                printf("Age: %d\n",prem->age);
                printf("Gender: %c\n", prem->genre);
                printf("Email: %s\n", prem->email);
                c=c+1;
                while(debut!=NULL && strcmp(debut->nom,nom)==0)
                {
                    printf("%d\n", c);
                    printf("Nom: %s\n", debut->nom);
                    printf("First name: %s\n", debut->prenom);
                    printf("Age: %d\n",debut->age);
                    printf("Gender: %c\n", debut->genre);
                    printf("Email: %s\n", debut->email);
                    c++;
                    debut=debut->next;
                }
                printf("Choose the rank of the person you are looking for: ");
                scanf("%d", &rang);
                for(i=2;i<=rang;i++)
                {
                    prem=prem->next;
                }
                return prem;
            }
        }
    }
    printf("The person you are looking for does not exist.\n");
    return NULL;
}


void modify_person(LPERS*y,char*nom, char*prenom,int age, char genre, char*email)
{
    LPERS* debut=rep[y->nom[0]-65];
    if(y!=NULL && debut!=NULL)
    {
        if(rep[y->nom[0]-65]==y)
        {
            strcpy(y->nom,nom);
            strcpy(y->prenom,prenom);
            y->age=age;
            y->genre=genre;
            strcpy(y->email,email);
            rep[y->nom[0]-65]=rep[y->nom[0]-65]->next;
            y->next=NULL;
            add_person(y);
            return;

        }
        else
        {
            while(debut->next!=NULL && debut->next!=y)
            {
                debut=debut->next;
            }
            if(debut->next==NULL)
            {
                printf("The person you are looking for does not exist\n");
                return;
            }
            else
            {
                strcpy(y->nom,nom);
                strcpy(y->prenom,prenom);
                y->age=age;
                y->genre=genre;
                strcpy(y->email,email);
                debut->next=y->next;
                y->next=NULL;
                add_person(y);
                return;
            }
        }
    }
    else
    {
        printf("The person you are looking to modify does not exist\n");
        return;
    }
}


void show_person(LPERS*y)
{
    printf("Nom: %s\n", y->nom);
    printf("First name: %s\n", y->prenom);
    printf("Age: %d\n", y->age);
    printf("Gender: %c\n", y->genre);
    printf("Email: %s\n" ,y->email);

}
