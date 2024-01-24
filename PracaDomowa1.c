/*
    Damian Stania
    Zajęcia: 7.12.2023 Zadanie oddane: 16.12.2023
    Sito Eratostenesa
*/

#include <stdio.h>
#include <stdlib.h>

int lastNumber;
typedef struct Numbers {
    int number;
    int ifDeleted;//Czy liczba jest pierwsza
    struct Numbers * next;
}Numbers;

void addMemory(Numbers** list, int newNumber);
void addElement(Numbers** list, Numbers* newElement);
void showList(Numbers* list);
void freeMemory(Numbers** list);
void checkIfPrimeNumber(Numbers** list);
void saveOnFile(Numbers** list);

int mainn() {
    Numbers* head = NULL;
    printf("Sito Eratostenesa\n"
           "Prosze wpisac ostatnia liczbe przedzialu: ");
    if(scanf("%i", &lastNumber)){
        int i;
        for (i=3; i<=lastNumber; i++){
            addMemory(&head, i);
        }
    }
    checkIfPrimeNumber(&head);
    showList(head);
    saveOnFile(&head);
    freeMemory(&head);
}

//Dodaje dane do nowego punktu w liscie
void addMemory(Numbers** list, int newNumber){
    Numbers* newElement = (Numbers *)
            malloc(sizeof(Numbers));
    newElement->number = newNumber;
    newElement->ifDeleted = 0;
    newElement->next = NULL;
    addElement(list, newElement);
}

//Dodaje nowy punkt do listy
void addElement(Numbers** list, Numbers* newElement){
    //Lista jest pusta
    if(*list == NULL){
        *list = newElement;
    }
        //Lista ma w sobie coś
    else {
        for(Numbers* i = *list; i != NULL; i = i->next){
            if(i->next == NULL){
                i->next = newElement;
                break;
            }
        }
    }
}

//wyswietla aktualny stan listy
void showList(Numbers* list){
    for(Numbers* i = list; i != NULL; i = i->next){
        printf("%d - %d\n", i->number, i->ifDeleted);
    }
}

//uwalnia pamiec zarezerwowana wczesniej przez malloc
void freeMemory(Numbers** list){
    for(Numbers* i = *list; i != NULL; i = i->next){
        free(i);
    }
}

//sprawdza i ew. usuwa(zamienia ifDeleted na 1), jesli liczba nie jest pierwsza
void checkIfPrimeNumber(Numbers** list){
    for(Numbers* i = *list; i != NULL; i = i->next){
        if(i->number%2 == 0){
            i->ifDeleted = 1;
        }
        for(Numbers* a = *list; a != NULL; a = a->next){
            if(i->number%a -> number == 0){
                if(i->number == a->number){
                    break;
                }else{
                    i->ifDeleted = 1;
                }
            }
        }
    }
}

//zapisuje liczby pierwsze(te z ifDeleted=0) na pliku liczby.txt
void saveOnFile(Numbers** list){
    FILE* file;
    file = fopen("liczby.txt", "w");
    fprintf(file, "%d\n", 2);
    for(Numbers *i = *list; i != NULL; i = i->next){
        if(i->ifDeleted == 0){
            fprintf(file, "%d\n", i->number);
        }
    }
    fclose(file);
}
