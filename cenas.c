
//cena 1
	if(op == 1){
		char nomeCena = "CENA1"
		for(int i = 0; i < game.scenesSize; i++){
        	buscar_cena = strcmp(nomeCena, scene.id);
        	if(buscar_cena == 0){
        		printScene(int s);
        	}
        }
    }
		//continua o jogo
	}else if(op == 2){
		printf("Até a próxima missão Gliese\n");
	}