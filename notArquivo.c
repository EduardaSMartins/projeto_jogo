#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// CONTROLES GERAIS
/////////////////////////////////////////////////////////////////////////

//#define DEBUG

#define TEXT_SHORT 500
#define TEXT_LONG  1000

#define MAX_COMMANDS 15
#define MAX_SCENES   10
#define MAX_ITEMS    50

// ESTRUTURAS NECESSARIAS
/////////////////////////////////////////////////////////////////////////

typedef struct command {
    // ID do comando (unico)
    // Se ITEM, contem o ID do item
    char id[TEXT_SHORT];
    // ACTION / ITEM
    char type[TEXT_SHORT];
    // Contem o texto do comando
    // ex: Verficar porta, abrir baú, disparar contra o vulto
    char name[TEXT_SHORT];
    // Texto de resultado positivo ao usar o comando
    // ex: Abriu o baú e pegou a lanterna
    char result[TEXT_LONG];
    // Se ACTION, contem o ID da cena alvo ou NONE
    // Se ITEM, contem o nome do item
    char outcome[TEXT_SHORT];
    // Nomes dos ITENS necessarios, separados por vírgula (ou NONE)
    char requirements[TEXT_LONG];
    // Caso comando necessite de itens, mas não os tem, mostrar este texto
    // ex: Está muito escuro para seguir por este caminho
    // (neste caso, precisa de uma lanterna ou similar)
    char missingItems[TEXT_LONG];
} Command;

typedef struct scene {
    // ID da cena (unico)
    char id[TEXT_SHORT];
    // Titulo da cena/local. Ex: Corredor principal
    char title[TEXT_SHORT];
    // Descricao longa da cena
    char description[TEXT_LONG];

    // Lista de comandos da Cena
    int commandsSize;
    Command commands[MAX_COMMANDS];
} Scene;

typedef struct item {
    // ID deve ser unico.
    // Ex: municao1, municao2, pedra1, lanterna1, lanterna2,...
    char id[TEXT_SHORT];
    // Nome pode repetir e ser mais generico
    // Ex: municao, pedra, lanterna
    char name[TEXT_SHORT];
    // Indica se item jah foi usado (YES/NO)
    // Jogo deve exibir no inventario somente itens validos (nao usados)
    char used[TEXT_SHORT];
} Item;

typedef struct game {
    // Cena atual
    int currentScene;

    // Lista de cenas do jogo
    int scenesSize;
    Scene scenes[MAX_SCENES];

    // Registra todos so itens ja obtidos pelo jogador (log).
    // Itens válidos tem item.used == "NO". Itens já usados tem item.used == "YES"
    // Se um item estiver no inventario, seu comando nao pode ser exibido na cena.
    int itemsSize;
    Item items[MAX_ITEMS];
} Game;

// OPERACOES
/////////////////////////////////////////////////////////////////////////

Game game;  


void firstScene(){
    printf("[CENA]\n");
    printf("Esperar ou explorar?\n");
    printf("Você está em sua nave e como indicado, sua missão é explorar o planeta, isso deverá ser feito para que sua vida seja mantida, caso contrário, seus dias estão contados. \n");
}

void begin(){
    int op;
    printf("[CENA]\n");
    printf("A Chegada\n");
    printf("Você é um astronauta que partiu em uma missão com mais 5 astronautas, mas ao decorrer da viagem houveram algumas complicações e seus companheiros não resistiram e restou apenas você.\n"); 
    printf("Ao aterrissar com sucesso na superfície do planeta Gliese 667 Cc sua nave não está em boas condições de uso e deverá ser abandonada\n"); 
    printf("Mas para isso você deve arranjar abrigo e alimento. Vamos lá?\n");
    printf("1 - [Iniciar MIssão]\n");
    printf("2 - [Sair da Missão]\n");
    scanf("%d", &op);
    if(op == 1){
        printf("    [COMANDO]\n");
        printf("Seja bem vindo ao planeta Gliese 667 Cc! Vamos la!!!\n\n");
            firstScene();
    }else if(op == 2){
        printf("    [COMANDO]\n");
        printf("Até a próxima missão Gliese...\n");
    }else{
        printf("Selecione um comando válido\n");
    }
}


void main(){
    begin();
}