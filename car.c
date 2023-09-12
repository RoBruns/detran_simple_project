//Modulo car (car.c)
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string.h>
#include <ctype.h>
#include "car.h"

void receiveCarData(Car *car){
    printf("Placa: ");
    scanf("%s", car->tag);
    printf("Modelo: ");
    scanf("%s", car->model);
    printf("Cor: ");
    scanf("%s", car->color);
}

void clearCarVars(Car *car){
    strcpy(car->owner, "");
    strcpy(car->tag, "");
    strcpy(car->model, "");
    strcpy(car->color, "");
}

void saveCarToFile(const Car *car) {
    FILE *file = fopen("carros.txt", "a"); // Abre o arquivo para escrita no modo append
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de carros.\n");
        return;
    }
    fprintf(file, "Proprietário (CPF): %s\nPlaca: %s\nModelo: %s\nCor: %s\n", car->owner, car->tag, car->model, car->color);
    fprintf(file, "\n============================================\n");
    fclose(file);
}