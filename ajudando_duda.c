int buscarCena(Command comm){
    int buscar_cena;
    for(int i = 0; i < game.scenesSize){
        buscar_cena = strcmp(comm.outcome, scene.id);
        
    }
    // Aqui vc tem que fazer um for comparando comm.outcome com o ID das cenas. use strcmp.
    // Retorne o indice da cena encontrada ( quando encontrar, retorne o i do for, na iteração atual)
    printf("%s \n", comm.outcome);
    printf("IMPLEMENTAR BUSCA DE CENA!");
    return 0;
}

int trataAcao(Command comm) {
    int temItens = 1;
    if (comm.requirements){
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
    printf(" %s\n %s\n\n", scene.title, scene.description); // imprime a cena
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

    choose = scene.commands[op]; // comando escolhido

    if(strcmp(choose.type, "ACTION")) {
        nova_cena = trataAcao(choose); // caso seja ação, trata ação
    } else if(strcmp(choose.type, "ITEM") {
        nova_cena = trataItem(choose); // caso seja item, trata item
    }

    if(nova_cena >= 0) {
        printScene(nova_cena); // ir para nova cena
    } else {
        printf("\n\n");
        // Não sei mt bem o que fazer aqui kkk.
        // Aqui é caso o tratamento da ação ou item não de certo.
        // Talvez chamar a função printando a mesma cena seja o ideal, não sei.
        // ou usar um goto pro for que printa os comandos kkkk
    }
}


/*Esquece, ou não
Command printScene(int s) {
    // printf("[[PRINT GAME DATA]]\n\n");
    int op;

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
            printf("Por favor, escolha um comando válido!\n");
        }
    }
    if(scene.commandsSize == 1)
    return scene.commands[op];
}
*/


//NUM USO
/*void printGameData() {
    printf("[[PRINT GAME DATA]]\n\n");
    for (int i = 0; i < game.scenesSize; i++) {
        Scene scene = game.scenes[i];
        printf("[SCENE]\n");
        printf(" %s\n %s\n %s\n\n",scene.id, scene.title, scene.description);
        for (int j = 0; j < scene.commandsSize; j++) {
            Command comm = scene.commands[j];
            printf("  [COMMAND]\n");
            printf("  %s\n    %s\n    %s\n    %s\n    %s\n    %s\n    %s\n\n",
                    comm.id, comm.type, comm.name,
                    comm.result, comm.outcome,
                    comm.requirements, comm.missingItems);
        }
    }


void printScene(int s) {
    int op;
    int nova_cena = -1;
        Scene scene = game.scenes[s];
    printf("[SCENE]\n");
    printf(" %s\n %s\n\n", scene.title, scene.description); // imprime a cena
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

    choose = scene.commands[op]; // comando escolhido

    if(strcmp(choose.type, "ACTION")) {
        nova_cena = trataAcao(choose); // caso seja ação, trata ação
    } else if(strcmp(choose.type, "ITEM") {
        nova_cena = trataItem(choose); // caso seja item, trata item
    }

    if(nova_cena >= 0) {
        printScene(nova_cena); // ir para nova cena
    } else {
        printf("\n\n");
        // aso o tratamento da ação ou item não de certo.
        // Talvez chamar a função printando a mesma cena seja o ideal, não sei.
        // ou usar um goto pro for que printa os comandos kkkk
    }
}


}*/
