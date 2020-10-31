#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // para poder usar o sleep no ubuntu
#include <locale.h> // define o idioma

// define os valores constantes de cada componente no mapa
#define robo 10 // pra colocar o rob�
#define estacao 20 // pra colocar a esta��o
#define sujeira 30 // pra colocar sujeira
#define parede 40 // pra colocar parede
#define limpo 50 // pra ele limpar
#define caminho 60 // pra o rob� voltar

struct robot{
	int linhaR;
	int colunaR;
	int linhaAtual;
	int colunaAtual;
};

void limpar(){
	system("cls");
}

// fun��o que imprime e atualiza as condi��es do mapa
void mapa(int map[8][8], int linhaS, int colunaS){
	limpar();
	
	printf("\n");

	for(int i = 0; i < 8; i++){
		for(int j = 0; j <= 8; j++){
			// verifica as cordenadas
			if(j == 8){
				printf("|");
			} else if(map[i][j] == robo){
				printf("| @ ", map[i][j]);
			} else if(map[i][j] == estacao || map[i][j] == robo){
				printf("| E ",map[i][j]);
			} else if(map[i][j] == sujeira && map[i][j] != robo){
				printf("|***",map[i][j]);
			} else if(map[i][j] == limpo || map[i][j] == caminho){
				printf("|   ",map[i][j]);
			} else if(linhaS == -1 && colunaS == -1 && map[i][j] != robo && map[i][j] != sujeira && map[i][j] != limpo && map[i][j] != caminho){
				map[i][j] == parede;
				printf("|---", map[i][j]);
			}else {
				printf("|   ", map[i][j]);
			}
		}
		printf("\n");
	}
	
	printf("\n");
}

void jogo(int map[8][8], int linhaS, int colunaS){
	int res, contSujeira = 0, contPassos = 0, maxPassos;
	
	struct robot r;
	

 	mapa(map, linhaS, colunaS);

	printf("Digite a linha do robo: ");
	scanf("%d", & r.linhaR);
	printf("Digite a coluna do robo: ");
	scanf("%d", & r.colunaR);
	
	r.linhaAtual = r.linhaR; // recebe as cordenadas do robo
	r.colunaAtual = r.colunaR; // recebe as cordenadas do robo
	map[r.linhaR][r.colunaR] = estacao; // recebe as cordenadas do robo
	map[r.linhaAtual][r.colunaAtual] = robo;


	mapa(map, linhaS, colunaS);
	
	do{
		mapa(map, linhaS, colunaS);
		printf("Quantidade de sujeiras: %i \n", contSujeira);
		
		printf("Digite a linha da sujeira: ");
		scanf("%d", & linhaS);
		printf("Digite a coluna da sujeira: ");
		scanf("%d", & colunaS);

		if(linhaS == r.linhaR && colunaS == r.colunaR){
			printf("\nAlerta: Voc� n�o pode colocar sujeira no lugar do rob�.");
			sleep(2);
		} else if(linhaS == -1 && colunaS == -1){
			break;
		}else {
			map[linhaS][colunaS] = sujeira; // recebe as cordenadas do robo
			contSujeira++;
			maxPassos++;
		}
	}while(linhaS != -1 && colunaS != -1);

	do{
		mapa(map, linhaS, colunaS);
		printf("Quantidade de sujeiras: %i \n", contSujeira);
		printf("Quantidade de passos: %i \n", contPassos);
		printf("Quantidade maxima de passos: %i \n", maxPassos*2);
		usleep(500000);
		
		while(contSujeira >= 0){
			// norte sul leste oeste
			if(map[r.linhaAtual-1][r.colunaAtual] == sujeira && map[r.linhaAtual-1][r.colunaAtual] != parede){
				map[r.linhaAtual][r.colunaAtual] = limpo;
				map[r.linhaAtual][r.colunaAtual] = caminho;
				map[r.linhaAtual-1][r.colunaAtual] = robo;
				r.linhaAtual--;
				contSujeira--;
				contPassos++;
				break;
			} else if(map[r.linhaAtual+1][r.colunaAtual] == sujeira && map[r.linhaAtual+1][r.colunaAtual] != parede){
				map[r.linhaAtual][r.colunaAtual] = limpo;
				map[r.linhaAtual][r.colunaAtual] = caminho;
				map[r.linhaAtual+1][r.colunaAtual] = robo;
				r.linhaAtual++;
				contSujeira--;
				contPassos++;
		break;
			} else if(map[r.linhaAtual][r.colunaAtual-1] == sujeira && map[r.linhaAtual][r.colunaAtual-1] != parede){
				map[r.linhaAtual][r.colunaAtual] = limpo;
				map[r.linhaAtual][r.colunaAtual] = caminho;
				map[r.linhaAtual][r.colunaAtual-1] = robo;
				r.colunaAtual--;
				contSujeira--;
				contPassos++;
		break;
			} else if(map[r.linhaAtual][r.colunaAtual+1] == sujeira && map[r.linhaAtual][r.colunaAtual+1] != parede){
				map[r.linhaAtual][r.colunaAtual] = limpo;
				map[r.linhaAtual][r.colunaAtual] = caminho;
				map[r.linhaAtual][r.colunaAtual+1] = robo;
				r.colunaAtual++;
				contSujeira--;
				contPassos++;
		break;
			}
			// comeca a voltar
			else {
				if(map[r.linhaAtual+1][r.colunaAtual] == caminho && map[r.linhaAtual+1][r.colunaAtual] != parede){
				map[r.linhaAtual][r.colunaAtual] = limpo;
				map[r.linhaAtual+1][r.colunaAtual] = robo;
				r.linhaAtual++;
				contPassos++;
		break;
			} else if(map[r.linhaAtual-1][r.colunaAtual] == caminho && map[r.linhaAtual-1][r.colunaAtual] != parede){
				map[r.linhaAtual][r.colunaAtual] = limpo;
				map[r.linhaAtual-1][r.colunaAtual] = robo;
				r.linhaAtual--;
				contPassos++;
		break;
			} else if(map[r.linhaAtual][r.colunaAtual+1] == caminho && map[r.linhaAtual][r.colunaAtual+1] != parede){
				map[r.linhaAtual][r.colunaAtual] = limpo;
				map[r.linhaAtual][r.colunaAtual+1] = robo;
				r.colunaAtual++;
				contPassos++;
		break;
			} else if(map[r.linhaAtual][r.colunaAtual-1] == caminho && map[r.linhaAtual][r.colunaAtual-1] != parede){
				map[r.linhaAtual][r.colunaAtual] = limpo;
				map[r.linhaAtual][r.colunaAtual-1] = robo;
				r.colunaAtual--;
				contPassos++;
		break;
			} else{
				printf("\nlimpeza concluida.\n");
		 		sleep(2);
				return;
			}
		}
		
	}
	}	while(contSujeira >= 0 && contPassos <= 2 * maxPassos);
}

int main(){
	setlocale(LC_ALL, "Portuguese"); // define o idioma do programa
	int map[8][8],linhaS, colunaS; // chama a refer�ncia
	jogo(map, linhaS, colunaS);
	return 0;
}
