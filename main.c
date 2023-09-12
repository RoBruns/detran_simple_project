// Modulo main (main.c)
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "person.h" //Importa o modulo person
#include "car.h" //Importa o modulo car
#define INITIAL_CAPACITY 10 // Capacidade inicial dos arrays

Person *people = NULL;
int peopleCount = 0;
int peopleCapacity = 0;

Car *cars = NULL;
int carsCount = 0;
int carsCapacity = 0;

void addPerson(const Person *person) {
    if (peopleCount == peopleCapacity) {
        // Aumente a capacidade do array dinamicamente
        if (peopleCapacity == 0) {
            peopleCapacity = INITIAL_CAPACITY;
        } else {
            peopleCapacity *= 2;
        }
        people = realloc(people, peopleCapacity * sizeof(Person));
    }

    // Adicione a pessoa ao array
    people[peopleCount] = *person;
    peopleCount++;
}

void addCar(const Car *car) {
    if (carsCount == carsCapacity) {
        // Aumente a capacidade do array dinamicamente
        if (carsCapacity == 0) {
            carsCapacity = INITIAL_CAPACITY;
        } else {
            carsCapacity *= 2;
        }
        cars = realloc(cars, carsCapacity * sizeof(Car));
    }

    // Adicione o carro ao array
    cars[carsCount] = *car;
    carsCount++;
}

bool searchClientByCPF(const char *cpf) {
    FILE *clientsFile = fopen("clients.txt", "r");
    if (clientsFile == NULL) {
        printf("Erro ao abrir o arquivo de clientes.\n");
        return false;
    }

    char line[256];
    bool found = false;

    while (fgets(line, sizeof(line), clientsFile)) {
        if (strstr(line, cpf)) {
            found = true;
            printf("======Cliente encontrado======\n");
            printf("%s", line); // Exibe a linha com o CPF e o nome

            // Agora, vamos procurar e exibir os carros associados a este cliente no arquivo "carros.txt"
            FILE *carsFile = fopen("carros.txt", "r");
            if (carsFile == NULL) {
                printf("Erro ao abrir o arquivo de carros.\n");
                fclose(clientsFile);
                return true;
            }

            char carLine[256];
            bool carsFound = false;

            printf("======Carros associados======\n");
            bool inCarData = false;

            while (fgets(carLine, sizeof(carLine), carsFile)) {
                if (inCarData) {
                    if (strstr(carLine, "=")) {
                        inCarData = false;
                    } else {
                        printf("%s", carLine); 
                    }
                } else if (strstr(carLine, cpf)) {
                    carsFound = true;
                    inCarData = true;
                }
            }

            fclose(carsFile);

            if (!carsFound) {
                printf("Nenhum carro associado a este CPF encontrado.\n");
            }

            fclose(clientsFile);
            return true;
        }
    }

    fclose(clientsFile);

    if (!found) {
        printf("Cliente com CPF %s não encontrado.\n", cpf);
    }

    return found;
}
void deleteCar(const char *cpf, const char *tag) {
    // Busque o carro pelo número da placa no arquivo "carros.txt"
    FILE *carsFile = fopen("carros.txt", "r");
    if (carsFile == NULL) {
        printf("Erro ao abrir o arquivo de carros.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Erro ao criar o arquivo temporário.\n");
        fclose(carsFile);
        return;
    }

    char carLine[256];
    bool carDeleted = false;
    bool deleteThisCar = false;

    while (fgets(carLine, sizeof(carLine), carsFile)) {
        if (strstr(carLine, cpf)) {
            // Encontrou uma linha com o CPF do cliente
            while (fgets(carLine, sizeof(carLine), carsFile)) {
                if (strstr(carLine, "=")) {
                    // Se encontrar uma linha contendo "=", significa que é o início de um novo carro
                    // Verifique se o carro corresponde à placa a ser excluída
                    if (!deleteThisCar) {
                        fputs(carLine, tempFile);  // Escreva o início do novo carro no arquivo temporário
                    }
                    deleteThisCar = false;  // Reinicialize a flag para o próximo carro
                } else if (strstr(carLine, tag)) {
                    // Verifique se esta linha contém a placa do carro a ser excluído
                    carDeleted = true;
                    deleteThisCar = true;  // Marque o carro para exclusão
                } else if (!deleteThisCar) {
                    fputs(carLine, tempFile);  // Escreva a linha do carro no arquivo temporário
                }
            }
        } else {
            // Se não for o CPF do cliente atual, escreva no arquivo temporário
            fputs(carLine, tempFile);
        }
    }

    fclose(carsFile);
    fclose(tempFile);

    if (carDeleted) {
        // Renomeie o arquivo temporário para "carros.txt" para substituir o original
        remove("carros.txt");
        rename("temp.txt", "carros.txt");
        printf("Carro com placa %s foi excluído com sucesso.\n", tag);
    } else {
        printf("Carro com placa %s não encontrado para o cliente com CPF %s.\n", tag, cpf);
    }
}

void deleteAllCars(const char *cpf) {
    // Abra o arquivo de carros para leitura
    FILE *carsFile = fopen("carros.txt", "r");
    if (carsFile == NULL) {
        printf("Erro ao abrir o arquivo de carros.\n");
        return;
    }

    // Crie um arquivo temporário para salvar os carros restantes
    FILE *tempCarsFile = fopen("temp_cars.txt", "w");
    if (tempCarsFile == NULL) {
        printf("Erro ao criar o arquivo temporário de carros.\n");
        fclose(carsFile);
        return;
    }

    char carLine[256];
    bool carsDeleted = false;

    while (fgets(carLine, sizeof(carLine), carsFile)) {
        if (!strstr(carLine, cpf)) {
            // Se não encontrar o CPF do cliente no carro, escreva a linha no arquivo temporário de carros
            fputs(carLine, tempCarsFile);
        } else {
            carsDeleted = true;
        }
    }

    fclose(carsFile);
    fclose(tempCarsFile);

    if (carsDeleted) {
        // Exclua o arquivo original de carros
        remove("carros.txt");

        // Renomeie o arquivo temporário para substituir o original
        if (rename("temp_cars.txt", "carros.txt") != 0) {
            printf("Erro ao renomear o arquivo temporário de carros.\n");
        }
    }
}


void deleteClient(const char *cpf) {
    // Abra o arquivo de clientes para leitura
    FILE *clientsFile = fopen("clients.txt", "r");
    if (clientsFile == NULL) {
        printf("Erro ao abrir o arquivo de clientes.\n");
        return;
    }

    // Crie um arquivo temporário para salvar os clientes restantes
    FILE *tempClientsFile = fopen("temp_clients.txt", "w");
    if (tempClientsFile == NULL) {
        printf("Erro ao criar o arquivo temporário.\n");
        fclose(clientsFile);
        return;
    }

    char clientLine[256];
    bool clientDeleted = false;

    while (fgets(clientLine, sizeof(clientLine), clientsFile)) {
        if (!strstr(clientLine, cpf)) {
            // Se não encontrar o CPF do cliente no cliente, escreva a linha no arquivo temporário de clientes
            fputs(clientLine, tempClientsFile);
        } else {
            clientDeleted = true;
        }
    }

    fclose(clientsFile);
    fclose(tempClientsFile);

    if (clientDeleted) {
        // Exclua o arquivo original de clientes
        remove("clients.txt");

        // Renomeie o arquivo temporário para substituir o original
        if (rename("temp_clients.txt", "clients.txt") != 0) {
            printf("Erro ao renomear o arquivo temporário de clientes.\n");
        }

        // Chame a função deleteAllCars para excluir todos os carros associados a este cliente
        deleteAllCars(cpf);

        printf("Cliente com CPF %s foi excluído com sucesso, juntamente com seus carros.\n", cpf);
    } else {
        printf("Cliente com CPF %s não encontrado.\n", cpf);
    }
}

void displayMainMenu() {
    printf("\n--- MENU ---\n");
    printf("1. Adicionar cliente\n");
    printf("2. Vincular carro a cliente\n");
    printf("3. Pesquisar cliente por CPF\n");
    printf("4. EDeletar carro do cliente\n");
    printf("5. Deletar cliente\n");
    printf("6. Sair\n");
    printf("Escolha uma opcao: ");
}



int main() {
    Person person; //Defini person do tipo Person
    Car car; //Defini car do tipo Car
    int option = 0;
    char ownerCPF[12]; // Mova a declaração para fora do switch
    bool clientExists = false; //Controle das opções

    do {
        displayMainMenu();
        scanf ("%d", &option);

        switch (option){
            case 1:
                printf("Opção 1 escolhida: adicionar cliente\n");
                    printf("=== Dados da Pessoa ===\n");
                    receivePersonData(&person); // Atribui os dados do person.c a variavel person
                    addPerson(&person); 
                    savePersonToFile(&person);
                    clearPersonVars(&person);
                    break;
            case 2:
                printf("Opção 2 escolhida: vincular carro a cliente\n");
                printf("CPF do proprietário: ");
                scanf("%s", ownerCPF);

                // Verifique se o cliente com o CPF especificado existe
                clientExists = searchClientByCPF(ownerCPF);

                if (!clientExists) {
                    printf("Cliente com CPF %s não encontrado. Cadastre o cliente primeiro.\n", ownerCPF);
                } else {
                    printf("=== Dados do Carro ===\n");
                    strcpy(car.owner, ownerCPF);
                    receiveCarData(&car);
                    addCar(&car);
                    saveCarToFile(&car);
                    clearCarVars(&car);
                }
                break;
                    
            case 3:
                    printf("Opção 3 escolhida: pesquisar cliente por CPF\n");
                    char searchCPF[12];
                    printf("Digite o CPF do cliente: ");//
                    scanf("%s", searchCPF);
                    searchClientByCPF(searchCPF);
                     
                    break;        
            case 4:
                printf("Opção 4 escolhida: excluir carro do cliente\n");
                printf("CPF do proprietário: ");
                scanf("%s", ownerCPF);

                // Verifique se o cliente com o CPF especificado existe
                clientExists = searchClientByCPF(ownerCPF);

                if (!clientExists) {
                    printf("Cliente com CPF %s não encontrado. Cadastre o cliente primeiro.\n", ownerCPF);
                } else {
                    // Exibir os carros do cliente antes de excluir
                    printf("Carros do cliente com CPF %s:\n", ownerCPF);
                    //displayClientCars(ownerCPF);
                    char carTag[100];
                    printf("Placa do carro a ser excluído: ");
                    scanf("%s", carTag);
                    deleteCar(ownerCPF, carTag);
                }
                break;

            case 5:
                printf("Opção 5 escolhida: deletar cliente\n");
                char deleteCPF[12];
                printf("Digite o CPF do cliente a ser excluído: ");
                scanf("%s", deleteCPF);
                deleteClient(deleteCPF);
                break;

            case 6:
                    printf("Opção 6 escolhida: sair\n");
                    free(people);
                    free(cars);
                    exit(0); // Sai do programa com o código 0 (sucesso)
                    break;

            
            default:
                 
                break;           
        }
   
    } while (option != 6);


    
    //Limpa a memoria
    free(people);
    free(cars);
    return 0;

}


