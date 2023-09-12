# detran_simple_project
Este código é um programa em C que permite gerenciar uma lista de clientes e seus carros associados. Ele possui as seguintes funcionalidades:

Adicionar Cliente (Opção 1): Permite adicionar informações de um cliente, incluindo CPF e nome, e salvar esses dados em um arquivo chamado "clients.txt". Também armazena as informações do cliente em um array dinâmico.

Vincular Carro a Cliente (Opção 2): Permite vincular informações de um carro a um cliente existente usando seu CPF como identificação. As informações do carro, como placa, modelo e cor, são adicionadas ao arquivo "carros.txt" e armazenadas em um array dinâmico.

Pesquisar Cliente por CPF (Opção 3): Permite pesquisar um cliente pelo seu CPF e exibir seus dados, incluindo os carros associados a ele, a partir dos arquivos "clients.txt" e "carros.txt".

Excluir Carro do Cliente (Opção 4): Permite excluir um carro associado a um cliente específico. O programa solicita o CPF do proprietário e a placa do carro a ser excluído. Os dados do carro são removidos do arquivo "carros.txt".

Deletar Cliente (Opção 5): Permite excluir um cliente e todos os carros associados a ele. O programa solicita o CPF do cliente a ser excluído. Os dados do cliente são removidos do arquivo "clients.txt", e os carros associados a ele também são excluídos do arquivo "carros.txt".

Sair do Programa (Opção 6): Encerra o programa e libera a memória alocada para os arrays dinâmicos.

O código organiza os dados dos clientes e carros em estruturas de dados (structs) e utiliza arquivos para armazenar essas informações persistentemente. Além disso, implementa funções auxiliares para validar CPFs, receber dados de pessoas e carros, e salvar informações em arquivos.

Esse programa pode ser usado para criar e gerenciar um cadastro de clientes e seus veículos, com a capacidade de adicionar, consultar e remover registros. É uma aplicação básica de gerenciamento de dados em C.
