//Header do car (car.h)
#ifndef CAR_H
#define CAR_H

typedef struct {
    char owner[13];
    char tag[100];
    char model[100];
    char color[100];
} Car;

void receiveCarData(Car *car);
void clearCarVars(Car *car);
void saveCarToFile(const Car *car);

#endif

