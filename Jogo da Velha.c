#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

#define LIN 3
#define COL 3
#define POSI 2

void pausa(void);
/*
int diagonais(int);
int linha(int);
int coluna(int);
*/

void inicializa(int tab[][COL])
{
	int l, c;
	
	for(l=0; l < LIN; l++)
		for(c=0; c < COL; c++)
			tab[l][c] = 0;
}

void tabuleiro(int jogo[][COL], int vez)		//Exibe o tabuleiro
{
	int l, c, tra;
	
	printf("\nJogada - %d", vez);
	printf("\n\n\t");
	
	for(tra = 0; tra < COL; tra++)
		printf(" %d \t", tra+1);
		printf("\n\t_______________________\n\n");
	
	for(l=0; l < LIN; l++)
	{
		printf("%d   |  \t", l+1);
		for(c=0; c < COL; c++)
			{
				if(jogo[l][c] == 0) printf("   \t");
				if(jogo[l][c] == -1) printf(" X \t");
				if(jogo[l][c] == 1) printf(" O \t");
			}
			printf("\n    |\n    |\n");
	}
	
	printf("\n\n");	
}

int Jogada(int posi[], int tab[][COL])
{
	/*int l, c;
	printf("\n");
	for(l=0; l < LIN; l++)
	{
		for(c=0; c < COL; c++)
			printf("   %d  ", tab[l][c]);
		printf("\n");
	}
	printf("\n"); */
	
	do
	{
		printf("Escolha duas posições:\n");		
		scanf("%d%d", &posi[0], &posi[1]);
		
		if(posi[0] < 1 || posi[0] > 3 || posi[1] < 1 || posi[1] > 3) printf("Valor não aceitável.\n");
	}while(posi[0] < 1 || posi[0] > 3 || posi[1] < 1 || posi[1] > 3);
	
	posi[0] -= 1;
	posi[1] -= 1;
}

int testeAcerto(int matriz[][COL])
{
	if(diagonais(matriz)) return 1;
	if(linha(matriz)) return 1;
	if(coluna(matriz)) return 1;
	
	return 0;
}

int diagonais(int tabela[][COL])
{
	int l, c, soma=0;
	
	printf("\nNas diagonais.\n");
	for(l=0; l < LIN+1; l++)
		for(c=0; c < COL+1; c++)
			if(l == c)	//Diagonal Principal
			{
				soma += tabela[l][c];
				if(soma == 3 || soma == -3)
				{
					//posifim(tabela[l][c]);
					return 1;
				}
			}
	
	soma = 0;
	for(l=0; l < LIN; l++)
		for(c=0; c < COL; c++)	
			if((l+c) == POSI)	//Diagonal Secundária
			{                           
				soma += tabela[l][c];
				if(soma == 3 || soma == -3) return 1;
			}
		
	return 0;
}

int linha(int tabela[][COL])
{
	int l, c, soma=0;
	printf("\nNas linhas.\n");
/*	
	if(soma += tabela[l][c] == 3) printf("Jogador 1 venceu l=c\n");
	if(soma += tabela[l][c] == -3) printf("Jogador 2 venceu l=c\n");
*/
	for(l=0; l < LIN; l++)
	{
		soma = 0; //quando fizer a nova iteração ele zera a variável
		
		for(c=0; c < COL; c++)
			soma += tabela[l][c];
		
		if(soma == 3 || soma == -3)
		{
			printf("%d\n", soma);
			return 1;
		}
	}
	return 0;
}

int coluna(int tabela[][COL])
{
	int l, c, soma=0;
	
	printf("\nNas colunas.\n");
	for(c=0; c < COL; c++)
	{
		soma = 0; //quando fizer a nova iteração ele zera a variável para não haver outros números
		for(l=0; l < LIN; l++)
			soma += tabela[l][c];
			
		if(soma == 3 || soma == -3) 
		{
			printf("%d\n", soma);
			return 1;
		}
	}
	return 0;
}

void ganhador(int player, int play)
{
	printf("Parabéns! Vitória do Jogador %d na %dª jogada.\n", player, play);
}
void posifim(int tab[][COL])
{
	int l, c, tra;
	
	for(tra = 0; tra < COL; tra++)
		printf(" %d \t", tra+1);
		printf("\n\t_______________________\n\n");
	
	for(l=0; l < LIN; l++)
	{
		printf("%d   |  \t", l+1);
		for(c=0; c < COL; c++)
			{
				if(tab[l][c] == 0) printf("   \t");
				if(tab[l][c] == -1) printf(" X \t");
				if(tab[l][c] == 1) printf(" O \t");
			}
			printf("\n    |\n    |\n");
	}
	
	printf("\n\n");	
}

void pausa(void)
{
	//int decide;
	printf("\nPressione enter para continuar...");
	//fflush(stdin);
	getche();
	system("cls");
	printf("\n");
}

main()
{
	setlocale(LC_ALL, "portuguese");
	int mat[3][3], inicio, valor, qtJog=0;
	int jog1[POSI], jog2[POSI], v1 = -1, v2 = 1;
	
	printf("Deseja iniciar o jogo? 0 or 1");
	printf("             -                ");
	scanf("%d", &inicio);
	
	if(inicio == 1)
	{
		inicializa(mat); //Inicializa a matriz com 0
		
		do
		{
			qtJog++;
			pausa();
			tabuleiro(mat, qtJog);	//atualiza a matriz
			
			printf("Jogador 1: X\n");
			do{
				Jogada(jog1, mat);
			}while(mat[jog1[0]][jog1[1]] != 0);
			
			mat[jog1[0]][jog1[1]] = v1;
			
			valor = testeAcerto(mat);
			if(valor == 1) break;
			
			qtJog++;
			pausa();
			tabuleiro(mat, qtJog);	//atualiza a matriz
			
			printf("Jogador 2: O\n");				
			do{
				Jogada(jog2, mat);
			}while(mat[jog2[0]][jog2[1]] != 0);	 
			
			mat[jog2[0]][jog2[1]] = v2;
			
			valor = testeAcerto(mat);
			if(valor == 1) break;
			
		}while(valor != 1);	
	}
	
	if(qtJog % 2 != 0) ganhador(1, qtJog);
	else ganhador(2, qtJog);
	tabuleiro(mat, qtJog); //Mostra a última posição do tabuleiro
	
	system("pause");
}
