#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 5

typedef struct {
    char nome;
    int id;
} Peca;

typedef struct {
    Peca fila[TAM];
    int frente;
    int tras;
    int cont;
} Fila;

// Inicializa a fila
void inicializarFila(Fila* f) {
    f->frente = 0;
    f->tras = 0;
    f->cont = 0;
}

// Enfileirar (inserir peça)
void enfileirar(Fila* f, Peca p) {
    if (f->cont == TAM) {
        printf("Fila cheia! Não é possível inserir.\n");
        return;
    }
    f->fila[f->tras] = p;
    f->tras = (f->tras + 1) % TAM;
    f->cont++;
}

// Dequeue (jogar peça)
Peca jogar(Fila* f) {
    Peca vazia = {'X', -1};
    if (f->cont == 0) {
        printf("Fila vazia! Nenhuma peça para jogar.\n");
        return vazia;
    }
    Peca p = f->fila[f->frente];
    f->frente = (f->frente + 1) % TAM;
    f->cont--;
    return p;
}

// Mostrar fila
void mostrarFila(Fila* f) {
    if (f->cont == 0) {
        printf("Fila vazia.\n");
        return;
    }
    printf("Fila atual: ");
    for (int i = 0; i < f->cont; i++) {
        int idx = (f->frente + i) % TAM;
        printf("[%c-%d] ", f->fila[idx].nome, f->fila[idx].id);
    }
    printf("\n");
}

// Gerar peça aleatória
char nomes[] = {'I', 'O', 'T', 'L'};

Peca gerarPeca(int id) {
    Peca p;
    p.nome = nomes[rand() % 4];
    p.id = id;
    return p;
}

int main() {
    Fila fila;
    inicializarFila(&fila);
    srand(time(NULL));

    // Inicializa com 5 peças
    for (int i = 1; i <= TAM; i++) {
        enfileirar(&fila, gerarPeca(i));
    }

    int proximoID = TAM + 1;
    int opcao;
    do {
        printf("\n--- Menu ---\n");
        printf("1. Visualizar fila\n");
        printf("2. Jogar peça da frente\n");
        printf("3. Inserir nova peça\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                mostrarFila(&fila);
                break;
            case 2: {
                Peca p = jogar(&fila);
                if (p.id != -1) printf("Você jogou a peça [%c-%d]\n", p.nome, p.id);
                break;
            }
            case 3: {
                Peca p = gerarPeca(proximoID++);
                enfileirar(&fila, p);
                printf("Nova peça [%c-%d] adicionada.\n", p.nome, p.id);
                break;
            }
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}
