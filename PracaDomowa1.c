#include <stdio.h>
#include <stdlib.h>

int lastNumber;
typedef struct numbers {
    int number;
    int ifDeleted;
    struct numbers * next;
}numbers;

void addMemory(numbers** list, int newNumber);
void addElement(numbers** list, numbers* newElement);
void showList(numbers* list);
void freeMemory(numbers** list);
void checkIfPrimeNumber(numbers** list);
void saveOnFile(numbers** list);

int main() {
    numbers* head = NULL;
    printf("Sito Eratostenesa\n"
           "Prosze wpisac ostatnia liczbe przedzialu: ");
    if(scanf("%i", &lastNumber)){
        int i;
        for (i=3; i<=lastNumber; i++){
            addMemory(&head, i);
        }
    }
    checkIfPrimeNumber(&head);
    saveOnFile(&head);
    showList(head);
    freeMemory(&head);//PRZEZ TO FREE MEMORY USUWA MI MOJE DANE Z PLIKU,
    // idk dlaczego
}

//Dodaje dane do nowego punktu w liscie
void addMemory(numbers** list, int newNumber){
    numbers* newElement = (numbers *)
            malloc(sizeof(numbers));
    newElement->number = newNumber;
    newElement->ifDeleted = 0;
    newElement->next = NULL;
    addElement(list, newElement);
}

//Dodaje nowy punkt do listy
void addElement(numbers** list, numbers* newElement){
    //Lista jest pusta
    if(*list == NULL){
        *list = newElement;
    }
        //Lista ma w sobie coś
    else {
        for(numbers* i = *list; i != NULL; i = i->next){
            if(i->next == NULL){
                i->next = newElement;
                break;
            }
        }
    }
}

//wyswietla aktualny stan listy
void showList(numbers* list){
    for(numbers* i = list; i != NULL; i = i->next){
        printf("%d - %d\n", i->number, i->ifDeleted);
    }
}

//uwalnia pamiec zarezerwowana wczesniej przez malloc
void freeMemory(numbers** list){
    for(numbers* i = *list; i != NULL; i = i->next){
        free(i);
    }
}

//sprawdza i ew. usuwa(zamienia isDeleted na 1), jesli liczba nie jest pierwsza
void checkIfPrimeNumber(numbers** list){
    for(numbers* i = *list; i != NULL; i = i->next){
        if(i->number%2 == 0){
            i->ifDeleted = 1;
        }
        for(numbers* a = *list; a != NULL; a = a->next){
            if(i->number%a->number == 0){
                if(i->number == a->number){
                    break;
                }else{
                    i->ifDeleted = 1;
                }
            }
        }
    }
}

//zapisuje liczby pierwsze(te z isDeleted=0) na pliku liczby.txt
void saveOnFile(numbers** list){
    FILE* save;
    save = fopen("liczby.txt", "w");
    fprintf(save, "%d\n", 2);
    for(numbers* i = *list; i != NULL; i = i->next){
        if(i->ifDeleted == 0){
            fprintf(save, "%d\n", i->number);
        }
    }
}
