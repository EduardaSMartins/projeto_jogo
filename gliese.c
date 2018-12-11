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

void loadField(FILE *file, char field[], int n) {
    char line[500];
    // fgets: copy n-1 characters. A terminating null character is
    // automatically appended after the characters copied to str.
    fgets(line, 500, file);

    // strncpy: No null-character is implicitly appended at the end of
    // destination if source is longer than num. Thus, in this case,
    // destination shall not be considered a null terminated C string (reading it as such would overflow).

    // campo deve receber até o tamanho maximo
    int maxRead = strlen(line)-1; // exclui o caractere \n
    if (n-1 < maxRead) maxRead = n-1; // exclui o espaćo para o \0
    strncpy(field, line, maxRead);
    field[maxRead] = '\0'; // encerra a string, por garantia

    #ifdef DEBUG
    printf("line:  %s", line);
    printf("field: %s\n\n", field);
    #endif // DEBUG
}

Command loadCommand(FILE* file){
    Command comm;
    loadField(file, comm.id, TEXT_SHORT);
    loadField(file, comm.type, TEXT_SHORT);
    loadField(file, comm.name, TEXT_SHORT);
    loadField(file, comm.result, TEXT_LONG);
    loadField(file, comm.outcome, TEXT_SHORT);
    loadField(file, comm.requirements, TEXT_LONG);
    loadField(file, comm.missingItems, TEXT_LONG);
    return comm;
}

Scene loadScene(FILE* file) {
    Scene scn;
    loadField(file, scn.id, TEXT_SHORT);
    loadField(file, scn.title, TEXT_SHORT);
    loadField(file, scn.description, TEXT_LONG);
    scn.commandsSize = 0;
    return scn;
}

void loadGameData(char fileName[]) {
    FILE *file;
    char line[50];

    printf("LOAD GAME DATA: reading data file...\n");
    file = fopen(fileName, "r");
    if (file == NULL) {
        printf("LOAD GAME DATA: error oppening file\n");
        return;
    }
    game.scenesSize = 0;
    Scene scn;

    while (fgets(line, sizeof(line), file)) {
        //printf("%s", line);
        if (strlen(line) > 0) {
            if (strstr(line, "CENA") != NULL) {
                scn = loadScene(file);
            } else
            if (strstr(line, "COMANDO") != NULL){
                Command comm = loadCommand(file);
                scn.commands[scn.commandsSize] = comm;
                scn.commandsSize++;
            } else
            if (strstr(line, "END") != NULL){
                // terminou a cena -> colocar no array e seguir para a proxima
                game.scenes[game.scenesSize] = scn;
                game.scenesSize++;
            }
        }
    }
    fclose(file);
    printf("LOAD GAME DATA: file read\n");
}

// Minhas funções
////////////////////////////////////////////////////////////////
int buscarCena(Command comm){
    int buscar_cena;
    for(int i = 0; i < game.scenesSize; i++){
        if (strcmp(comm.outcome, game.scenes[i].id) == 0) {
            return i;
        }
    }
    return -1;
}

int trataAcao(Command comm) {
    int temItens = 1;
    if (strcmp(comm.requirements, "NONE") != 0){
        // Aqui acho que seria um for comparando os itens necessários com os itens
        // que o personagem tem. Não sei onde vc está guardando isso.
        // Da pra usar um for com strcmp para comparar o ID do item
        printf("EDUARDA - TRATAR NECESSIDADE DE ITENS");
        temItens = -1; // caso não tenha os item, setar em -1

    }
    if (comm.result && temItens >= 0){
        printf(" %s \n", comm.result);
        return buscarCena(comm);
    } else if (temItens < 0 ){
        printf(" %s \n", comm.missingItems);
        return -1;
    }
}


int trataItem(Command comm) {
    // Não sei / não entendi mt bem como funcionariam os itens.
    // Se vc só printa o resultado.. se tem que tirar o item do inventário. dependendo do item..
    // To meio em dúvida. Mas faça seus ifs lecais aqui, e dps busque e retorne a cena (:
    if (comm.result){
        printf(" %s \n", comm.result);
        return buscarCena(comm);
    }
}

void printScene(int s) {
    // printf("[[PRINT GAME DATA]]\n\n");
    int op;
    int nova_cena = -1;

    Scene scene = game.scenes[s];
    printf("[SCENE]\n");
    printf(" %s\n %s\n\n", scene.title, scene.description ); // imprime a cena
    printf("  [COMMANDS]\n");
    for (int j = 0; j < scene.commandsSize; j++) { // laço para imprimir os comandos da cena
        Command comm = scene.commands[j];
        printf("%d: %s - [%s]\n", j+1, comm.type, comm.name);
    }

    while (op <= 0 || op > scene.commandsSize) { // laço para pegar um comando válido
        printf("\n --> ");
        scanf("%d", &op);
        if (op <= 0 || op > scene.commandsSize){
            printf("Por favor, escolha um comando válido!\n");
        }
    }

    Command choose = scene.commands[op-1]; // comando escolhido
    if(strcmp(choose.type, "ACTION") == 0) {
        nova_cena = trataAcao(choose); // caso seja ação, trata ação
    } else if(strcmp(choose.type, "ITEM") == 0) {
        nova_cena = trataItem(choose); // caso seja item, trata item
    }

    if (strcmp(choose.outcome,"exit") == 0){
        exit(0);
    } else if(nova_cena >= 0) {
        printScene(nova_cena); // ir para nova cena
    } else {
        printf("\n\n");
        // Não sei mt bem o que fazer aqui kkk.
        // Aqui é caso o tratamento da ação ou item não de certo.
        // Talvez chamar a função printando a mesma cena seja o ideal, não sei.
        // ou usar um goto pro for que printa os comandos kkkk
        printScene(s);
    }
}


// main
///////////////////////////////////////////////////////////////

int main() {
    char fileName[] = "gliese.txt";
    loadGameData(fileName);
    printScene(0);
    return 0;
}
