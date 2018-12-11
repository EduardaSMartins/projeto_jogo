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

Command printScene(int s) {
    int op;
    char cena;
    Scene scene = game.scenes[s];
    printf("[SCENE]\n");
    printf(" %s\n %s\n %s\n\n",scene.id, scene.title, scene.description);
    printf("  [COMMANDS]\n");
    for (int j = 0; j < scene.commandsSize; j++) {
        Command comm = scene.commands[j];
        printf("%d: %s - [%s]\n", j+1, comm.type, comm.name);
    }

    while (op <= 0 || op > scene.commandsSize) {
        printf("\n --> ");
        scanf("%d", &op);
        if (op <= 0 || op > scene.commandsSize){
            printf("Comando inválido!\n");
        }
    }
   if(scene.commandsSize == 1)
    return scene.commands[op];
}


// main
///////////////////////////////////////////////////////////////

int main() {
    char fileName[] = "gliese.txt";
    loadGameData(fileName);
    printScene(0);
    return 0;
}
