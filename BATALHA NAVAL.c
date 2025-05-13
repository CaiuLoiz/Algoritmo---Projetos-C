#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define LIN 5
#define COL 5
#define TIRO 2
#define LBAR 3

void pausa(void);
int casoganho(void);

int Tabuleiro(int tab[LIN][COL]) //Inicializa o tabuleiro
{
	int lin, col;
	
	system("cls");
	
		for(lin=0; lin<LIN; lin++)
			for(col=0; col<COL; col++)
				tab[lin][col] = -1;
				
}

int AtualTab(int campo[][COL])	//Atualiza o tabuleiro
{
	int lin, col, l, c;
	
	printf("\n\t  ");
	for(c = 0; c < COL; c++)
		printf("    %d", c+1);
	printf("\n\t    ");
	for(c = 0; c < COL; c++)
		printf("_____");
	printf("\n\n");
	
	for(lin=0; lin<LIN; lin++)
		{
			printf("\t%d  |  ", lin+1);
			for(col=0; col<COL; col++)
			{
				if(campo[lin][col] == -1)
					printf("~    ");
				else if(campo[lin][col] == 0)
						printf("*    ");
				else printf("X    ");
			}
			printf("\n\t   |\n\n");
		}
}

int tiro(int atira[TIRO])	//Esolher linha e coluna
{
	printf("Informe duas posicoes entre 1 e 5:\n");
	do
	{
		printf("Prim: ");
		scanf("%d", &atira[0]);
		printf("Segu: ");
		scanf("%d", &atira[1]);
		if(atira[0] < 1 || atira[0] > 5 || atira[1] < 1 || atira[1] > 5)
			printf("\nInforme um valor valido!!\n");
	}while	(atira[0] < 1 || atira[0] > 5 || atira[1] < 1 || atira[1] > 5);
	
	atira[0] -= 1;
	atira[1] -= 1;
	//O usuurio digitar: de 1 a 5, isto eh para que nao acesse valores 
	//indevidos nas memarias com posicoes erradas na matriz
}

int LocaNavio(int bar[][TIRO])	//Escolhe a posicao dos navios aleatorio
{
	int i, lin, LinT, col;
	
	printf("\nSerao 3 navios no jogo\n");
	
	srand(time(NULL));
	for(lin = 0; lin < LBAR; lin++)
	{
		bar[lin][0] = rand()%5;	//Primeira Coluna
		bar[lin][1] = rand()%5;	//Segunda Coluna
		
		if(lin > 0)	//Garante que nao sejam geradas coordenadas repetidas pelo computador
			for(LinT = 0; LinT < lin; LinT++)
			{
				if(bar[LinT][0] == bar[lin][0]) bar[lin][0] = rand()%5;
				if(bar[LinT][1] == bar[lin][1]) bar[lin][1] = rand()%5;
			}	
	}
	
	for(i=0; i<LBAR; i++)
	{
		printf("%d   ", bar[i][0]);
		printf("%d", bar[i][1]);
		printf("\n");
	}
}

int Acerto(int shot[TIRO], int ship[][TIRO], int QTAC) //Compara os valores que o usuario deu com os da maquina
{
	int i;
	
	system("cls");
	for(i=0; i < LBAR; i++)
		if(shot[0] == ship[i][0] && shot[1] == ship[i][1])
		{
			printf("\n\n\t\tACERTOU %d NAVIOS\n\n\n", QTAC+1);
			return 1;
		}
			
	printf("\n\t\tERROU\n\n");
	return 0; // caso erre retorne valor 0
}

void dicas(int shot[TIRO], int barco[][TIRO])
{
	int i, qtLin=0, qtCol=0;
	
	for(i = 0; i < LBAR; i++)
	{
		//Se o numero informado para linha ou coluna foi igual ao valor sorteado do barco
		//Entao soma 1, que vai contar a quantidade que tem nessa posiao
		//Ou seja, se eu acertei uma coluna e errei uma linha, ele retorna quantos valores hao nesta posicao
		if(barco[i][0]==shot[0]) qtLin++;
		if(barco[i][1]==shot[1]) qtCol++;
	}
	
	printf("\tDICA: Ha %d barco na coluna %d\n\n", qtCol, shot[1]+1);
}

void inicio(void)
{
	int i;
	printf("\n\n\t\t\tBEM VINDO AO JOGO\n\n");
	for(i=0; i <= 25; i++) printf("-");
	printf("BATALHA NAVAL");
	for(i=0; i <= 25; i++) printf("-");
	printf("\n\n");
}

void regra(void)
{
	printf("\t\t\tRegras do jogo\n");
	printf("\n\tVoce deve escolher duas posicoes do 'mar' e atacar");
	printf("\n\t Se acertar o barco 'X' poderao atirar novamente");
	printf("\n\n\t\tSera passado sua vez:\n");
	printf("\n\t  Se acertou a agua, nao ha navio no local");
	printf("\n\tSe atirar 2X no local que nao acertou o navio");
	
	printf("\n\n");
}

int jogada(int campo[][COL], int barco[][TIRO], int atira[TIRO], int *QtAcer,int *QtAcr, int N_Ten)
{
	static int vez = 0;	//Variavel estatica para controlar quando um jogador acertar 2x
	
	do
	{
		if(*QtAcr == 2 && vez == 0) //Caso um jogador acerte 2 barcos
		{
			if(casoganho()) return ++*QtAcer;
			vez++;
		}
		printf("    \nN Tentativas: %d vez - %d\n",  N_Ten, vez);
		AtualTab(campo);
		
		do	//Garante que nao informe dois valores ja jogados
		{
			tiro(atira);
			if(campo[atira[0]][atira[1]] != -1)
				printf("\nUm tiro ja foi dado neste local.\n");
		}while	(campo[atira[0]][atira[1]] == 1);		
		//printf("\nVetor na funcao: %d %d\n", atira[0], atira[1]);
		pausa();
		
		if(Acerto(atira, barco, *QtAcer))
		{
			campo[atira[0]][atira[1]] = 1;
			*QtAcer+=1;
		}
		else
			campo[atira[0]][atira[1]] = 0;
	}while(campo[atira[0]][atira[1]] == 1 && (*QtAcer + *QtAcr) < 3);
}

void maquina(int campo[][COL], int barco[][TIRO], int atirarM[], int *qtAc, int QtA1, int Ten)
{
	int i, cont=0;
	
	do
	{
		printf("    \nN Tentativas: %d\n", Ten);
		AtualTab(campo);
		
		do
		{
			srand(time(NULL));
			for(i = 0; i < TIRO; i++)
				atirarM[i] = rand()%5;
			
			if(campo[atirarM[0]][atirarM[1]] == 1) printf("%d ", ++cont);
		}while(campo[atirarM[0]][atirarM[1]] == 1 || campo[atirarM[0]][atirarM[1]] == 0);
		printf("Repeticoes %d\n", cont);
		printf("\nValores informados\n%d\n%d\n", atirarM[0]+1, atirarM[1]+1);		
		pausa();
		
		if(Acerto(atirarM, barco, *qtAc))
		{
			campo[atirarM[0]][atirarM[1]] = 1;
			*qtAc+=1;
		}
		else
			campo[atirarM[0]][atirarM[1]] = 0;
	}while(campo[atirarM[0]][atirarM[1]] == 1 && (*qtAc + QtA1) < 3);
}

void MsgFim(int QtAcer, int x)
{
	printf("\n\n\t\t* * * * * * PARABENS! * * * * * * *\n\n");
	printf("\n\t\t\tJOGADOR %d GANHOU", x);
	if(x == 3)	printf("\n\t\t\t--- MAQUINA ---\n");
	printf("\n\n\t\tVOCE CONSEGUIU ACERTAR %d BARCOS.\n\n", QtAcer);
}

void pausa(void)
{
	//char deci;
	printf("Pressione enter para continuar");
	//fflush(stdin);
	getch();
}

int casoganho(void)
{
	int binario;
	
	printf("\nDeseja parar? (0 or 1) 2 barcos foram acertados:    ");
	scanf("%d", &binario);
	
	return binario;
}

main()
{
	setlocale(LC_ALL, "portuguese");
	int mat[5][5], atirarJ1[2], atirarJ2[2], navio[3][2];
	int qtAcJ1=0, qtAcJ2=0, inicia, QtJog, repe1=0, repe2=0;
	char desi='S';
	
	inicio();	//Mostra mensagem
	
	printf("Deseja Iniciar? 0 or 1");
	printf("          -            ");
	scanf("%d", &inicia);
	printf("\n\n");
	
	if(inicia!=0)
	{
		printf("Deseja saber a regra do jogo? 0 or 1     -\t");
		scanf("%d", &inicia);
		printf("\n\n");
		if(inicia!=0) regra();	//Mostra regras
		
		do
		{
			printf("Quantos Jogadores ter�o a partida?\n 1 - 2 - 3(M�q)\t- ");
			scanf("%d", &QtJog);
		}while(QtJog < 1 || QtJog > 3);
		
		Tabuleiro(mat);		//Inicializa o tabuleiro com -1
		LocaNavio(navio);	//Inicializa as posi��es com n�meros randomicos
	
		while((qtAcJ1 + qtAcJ2) < 3)
		{
			printf("\nJOGADOR 1:\n");
			repe1++;
			jogada(mat, navio, atirarJ1, &qtAcJ1, &qtAcJ2, repe1);			
			
			if(mat[atirarJ1[0]][atirarJ1[1]]==0) dicas(atirarJ1, navio);
			//printf("\nQt Acerto na main Jog1: %d\n", qtAcJ1);		
				
			if(QtJog == 2 && (qtAcJ1 + qtAcJ2) < 3)
			{
				printf("\nJOGADOR 2:\n");
				repe2++;
				
				jogada(mat, navio, atirarJ2, &qtAcJ2, &qtAcJ1, repe2);
				
				if(mat[atirarJ2[0]][atirarJ2[1]]==0) dicas(atirarJ2, navio);
			}
			
			if(QtJog == 3 && (qtAcJ1 + qtAcJ2) < 3)
			{
				printf("\nM�QUINA: ");
				repe2++;
				
				maquina(mat, navio, atirarJ2, &qtAcJ2, qtAcJ1, repe2);
				
				//printf("\nQt Acerto na main Maq: %d\n", qtAcJ2);
				if(mat[atirarJ2[0]][atirarJ2[1]] == 0) dicas(atirarJ2, navio);
			}
		}
	}
	
	//FINAL	
	system("cls");
	printf("Em %d jogadas\n\n", repe1+repe2);
	
	if(qtAcJ1 > qtAcJ2) MsgFim(qtAcJ1, 1);
	else if(qtAcJ1 < qtAcJ2 && QtJog==3) MsgFim(qtAcJ2, 3);
	else if(qtAcJ1 < qtAcJ2) MsgFim(qtAcJ2, 2);
	else printf("Saiu da partida. Execute novamente se quiser jogar.\n");
	
/*	printf("Deseja informa��es adicionais sobre o jogo?  ");
	scanf(" %c", &desi);
	
	if(desi == 'S')
	{
		printf("\n\nEspa�o em mem�ria utilizado por main em bytes:\n");
		printf("Tabela Principal....... %d\n", sizeof(mat[5][5]));
		printf("Tabela Navio........... %d\n", sizeof(navio[3][2]));
		printf("Vetor Atirar........... %d\n", sizeof(atirarJ1[2]));
		printf("Vetor AtirarJ2......... %d\n", sizeof(atirarJ2[2]));
		printf("Linha........ %d\n", sizeof(l));
		printf("Coluna....... %d\n", sizeof(c));
		printf("QtAcJ1....... %d\n", sizeof(qtAcJ1));
		printf("QtAcJ2....... %d\n", sizeof(qtAcJ2));
		printf("Inicia....... %d\n", sizeof(inicia));
		printf("QtJog........ %d\n", sizeof(QtJog));
		printf("Repe1........ %d\n", sizeof(repe1));
		printf("Repe2........ %d\n", sizeof(repe2));
		printf("Desi......... %d\n", sizeof(desi));
	}
	*/
	system("pause");
}
