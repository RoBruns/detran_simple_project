//Header person (person.h)
#ifndef PERSON_H
#define PERSON_H
#include <stdbool.h>

typedef struct {
    char cpf[13];
    char name[100];
} Person;

void receivePersonData(Person *person);
void clearPersonVars(Person *person);
void savePersonToFile(const Person *person);
bool validateCPF(const char *cpf);
bool inNumeric(const char *str);

#endif