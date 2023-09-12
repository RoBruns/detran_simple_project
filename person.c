//Modulo person (person.c)
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "person.h"

bool isNumeric(const char *str) {
    for (int i = 0; str[i]; i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

bool validateCPF(const char *cpf) {
    if (strlen(cpf) != 11 || !isNumeric(cpf)) {
        printf("CPF inválido. O CPF deve conter 11 dígitos.\n");
        return false;
    }

    int digits[11];
    for (int i = 0; i < 11; i++) {
        digits[i] = cpf[i] - '0';
    }

    int sum1 = 0, sum2 = 0;
    int digit1 = 0, digit2 = 0;

    for (int i = 0, j = 10; i < 9; i++, j--) {
        sum1 += digits[i] * j;
    }
    digit1 = (sum1 * 10) % 11;

    if (digit1 == 10) {
        digit1 = 0;
    }

    for (int i = 0, j = 11; i < 10; i++, j--) {
        sum2 += digits[i] * j;
    }
    digit2 = (sum2 * 10) % 11;

    if (digit2 == 10) {
        digit2 = 0;
    }

    if ((digit1 == digits[9]) && (digit2 == digits[10])) {
        return true;
    }

    printf("CPF inválido.\n");
    return false;
}


void receivePersonData(Person *person) {
    char inputCPF[12];
    do {
        printf("CPF: ");
        scanf("%s", inputCPF);
    } while (!validateCPF(inputCPF));

    strcpy(person->cpf, inputCPF);

    printf("Nome: ");
    scanf("%s", person->name);
}

void clearPersonVars(Person *person) {
    strcpy(person->cpf, "");
    strcpy(person->name, "");
}

void savePersonToFile(const Person *person) {
    FILE *file = fopen("clients.txt", "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de clientes.\n");
        return;
    }
    fprintf(file, "CPF: %s\nNome: %s\n", person->cpf, person->name);
    fprintf(file, "\n============================================\n");
    fclose(file);
}


