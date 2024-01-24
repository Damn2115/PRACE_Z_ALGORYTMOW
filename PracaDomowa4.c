/*
    Damian Stania
    Zajęcia: 18.01.2024 Data oddania 23.01.2024
    Kopiec
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    char arr[40];
    int dlugosc;
} N;

void heapify(N *nodes, int size, int i) {
    int largest = i;
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;

    if (leftChild < size && nodes[leftChild].dlugosc > nodes[largest].dlugosc) {
        largest = leftChild;
    }

    if (rightChild < size && nodes[rightChild].dlugosc > nodes[largest].dlugosc) {
        largest = rightChild;
    }

    if (largest != i) {
        N temp = nodes[i];
        nodes[i] = nodes[largest];
        nodes[largest] = temp;
        heapify(nodes, size, largest);
    }
}

void printHeap(N *nodes, int size) {
    for (int i = 0; i < size; i++) {
        printf("Dlugosc: %d, Ciag znakow: %s\n", nodes[i].dlugosc, nodes[i].arr);
    }
}

void heapSort(N *nodes, int size) {
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(nodes, size, i);
    }

    for (int i = size - 1; i > 0; i--) {
        N temp = nodes[0];
        nodes[0] = nodes[i];
        nodes[i] = temp;

        heapify(nodes, i, 0);
    }
}

int my_menu() {
    int opt = 0;
    printf("\n[1] - wyswietl drzewo VLR\n");
    printf("[2] - wyswietl drzewo LVR\n");
    printf("[3] - wyswietl drzewo LRV\n");
    printf("[4] - sortuj kopiec\n");
    printf("[0] - zakoncz program\n");
    printf("?> ");
    scanf("%i", &opt);
    while (opt < 0 || opt > 4) {
        printf("---!!!---\nNiepoprawny wybor - popraw:\n---!!!---\n");
        printf("[1] - wyswietl drzewo VLR\n");
        printf("[2] - wyswietl drzewo LVR\n");
        printf("[3] - wyswietl drzewo LRV\n");
        printf("[4] - sortuj kopiec\n");
        printf("[0] - zakoncz program\n");
        printf("?> ");
        scanf("%i", &opt);
    }
    return opt;
}

void vlr(N *nodes, int index, int size) {
    if (index < size) {
        printf("Dlugosc: %d, Ciag znakow: %s\n", nodes[index].dlugosc, nodes[index].arr);
        vlr(nodes, 2 * index + 1, size);
        vlr(nodes, 2 * index + 2, size);
    }
}

void lvr(N *nodes, int index, int size) {
    if (index < size) {
        lvr(nodes, 2 * index + 1, size);
        printf("Dlugosc: %d, Ciag znakow: %s\n", nodes[index].dlugosc, nodes[index].arr);
        lvr(nodes, 2 * index + 2, size);
    }
}

void lrv(N *nodes, int index, int size) {
    if (index < size) {
        lrv(nodes, 2 * index + 1, size);
        lrv(nodes, 2 * index + 2, size);
        printf("Dlugosc: %d, Ciag znakow: %s\n", nodes[index].dlugosc, nodes[index].arr);
    }
}

int main() {
    srand(time(NULL));
    printf("Kopiec i sortowanie przez kopcowanie\n");
    printf("Oznaczenia w algorytmach przejscia drzewa:\n");
    printf("V - odwiedzenie wezla\nL - przejscie do lewego poddrzewa\nR - przejscie do prawego poddrzewa\n----\n");

    int liczba;
    printf("Podaj ilosc elementow do wygenerowania: ");
    scanf("%d", &liczba);

    N *nodes = (N *)malloc(liczba * sizeof(N));
    for (int i = 0; i < liczba; i++) {
        int val = rand() % 39 + 2;
        for (int j = 0; j < val; j++) {
            nodes[i].arr[j] = 'A' + rand() % 26;
        }
        nodes[i].arr[val] = '\0';
        nodes[i].dlugosc = val;
    }

    int my_opt = my_menu();
    do {
        switch (my_opt) {
            case 1:
                if (liczba == 0) {
                    printf("Drzewo jest puste\n");
                } else {
                    printf("Przejscie drzewa algorytmem VLR:\n");
                    vlr(nodes, 0, liczba);
                }
                my_opt = my_menu();
                break;

            case 2:
                if (liczba == 0) {
                    printf("Drzewo jest puste\n");
                } else {
                    printf("Przejscie drzewa algorytmem LVR:\n");
                    lvr(nodes, 0, liczba);
                }
                my_opt = my_menu();
                break;

            case 3:
                if (liczba == 0) {
                    printf("Drzewo jest puste\n");
                } else {
                    printf("Przejscie drzewa algorytmem LRV:\n");
                    lrv(nodes, 0, liczba);
                }
                my_opt = my_menu();
                break;

            case 4:
                if (liczba == 0) {
                    printf("Drzewo jest puste\n");
                } else {
                    printf("Posortowany kopiec:\n");
                    heapSort(nodes, liczba);
                    printHeap(nodes, liczba);
                }
                my_opt = my_menu();
                break;
        }
    } while (my_opt != 0);

    free(nodes);

    return 0;
}
