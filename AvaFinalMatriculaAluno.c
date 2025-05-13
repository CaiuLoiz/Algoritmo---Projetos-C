#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

#define NM 30
#define NOTA 3
#define TRUE 0
#define FALSE 1

int QTALUNOS;
int cont = 0;	//Esta variável controla a inserção, exclusão	-	Quantos registros foram feitos
				//servindo também para saber qual foi a última posição de cada operação efetuada
typedef struct
{
	int matricula;
	char nome[NM];
	float nota[NOTA], media;
}alunos;

int cadastro(alunos cad[]);
int consulta(alunos ccad[]);
int altera(alunos acad[]);
int exclui(alunos ecad[]);
void calcnotas(alunos ncad[], int posi, int num);
void consAluno(alunos cacad[]);
void decisao(alunos apcad[], int opc);
void consultaAp(alunos registro[], int j);

main()
{
	setlocale(LC_ALL, "portuguese");
	
	printf("Informe quantos cadastros você deseja fazer - ");
	scanf("%d", &QTALUNOS);
	//Ao inserir os dados na struct não precisa inserí-los de uma vez, mesmo que fique lixo na memória
	int opc, i;
	char opcao;
	alunos registro[QTALUNOS];
	
	FILE *arqv;
	
	arqv = fopen("Alunos.txt", "ab");
					//Este arquivo foi aberto aqui pois a mudança na struct pode ocorrer em 3 funções então não há muita repetição
		if(arqv == NULL)
		{
			printf("Erro ao abrir o arquivo.\nDeseja continuar? S\\N");
			
			opcao = getch();
			opcao = toupper(opcao);
			if(opcao == 'N') exit(EXIT_FAILURE);
			else printf("Todos os seus dados não serão salvos.\n\n");
		}
		
	do
	{
		printf("Você pode fazer até %d cadastros.\n", QTALUNOS - cont);
		printf("Menu de opções:\n");
		printf("\t1 - Cadastrar alunos e notas\n\t2 - Alterar alunos e notas\n\t3 - Excluir alunos e notas\n\t4 - Listar alunos e médias\n");
		printf("\t5 - Listar alunos aprovados\n\t6 - Listar alunos reprovados\n\t7 - Encerrar o programa\n\n");
		
		printf("Escolha uma das opções:\t");
		scanf("%d", &opc);
		
		printf("\n\n");
		switch(opc)
		{
			case 1:	cadastro(registro);	break;
			
			case 2:	altera(registro);	break;
			
			case 3:	exclui(registro);	break;
			
			case 4:	consAluno(registro);	break;
			
			case 5:	decisao(registro, TRUE);	break;
			
			case 6:	decisao(registro, FALSE);	break;
			
			default: printf("Saída do programa!\n"); break;
		}
		
		puts("Pressione qualquer tecla para continuar...");
		getchar();
		getchar();
		
		if(opc > 0 && opc < 4) fwrite(registro, sizeof(alunos), cont, arqv);
		
		system("cls");
		printf("\n\n");
	}while(opc > 0 && opc < 7);
	
	fclose(arqv);
	
	system("pause");
}

int cadastro(alunos cad[])
{
	int i, j, bit;
	int tam;
	char opc;
	
	while(cont < QTALUNOS)
	{
		printf("Informe a matrícula do aluno %d:\t", cont+1);
		do
		{
			bit = 0;
			scanf("%d", &cad[cont].matricula);
				
				if(cont > 0)
				for(j = 0; j < cont; j++)
					if(cad[cont].matricula == cad[j].matricula)
					{
						printf("Valor já cadastrado.\n");
						printf("Digite outro:\t");
						bit = 1;
					}
		}while(bit == 1);
		
		getchar();
		printf("Digite o nome do aluno:\t");
		fgets(cad[cont].nome, NM-1, stdin);
			tam = strlen(cad[cont].nome);
			cad[cont].nome[tam-1] = '\0';
		
		printf("Digite as notas:\n");
		calcnotas(cad, cont, 4);
		
		cont++;	//Já que é uma variável global, a cada inserção o novo valor será registrado em uma nova posição
		
		printf("Deseja sair esta operação? S/N\n");
		opc = getch();
		opc = toupper(opc);
			if(opc == 'S' || cont == QTALUNOS) return FALSE;
	}
	
}

int consulta(alunos ccad[])	//Função criada para diminuir o tamanho do código, pois duas funções precisam fazer uma consulta
{
	int mat, j, bit;
	
	printf("Informe o número de matrícula do aluno:\t");
	scanf("%d", &mat);
	
	for(j=0; j < QTALUNOS; j++)
		if(mat != ccad[j].matricula)
			bit = 1;
		else return j;
	
	if(bit == 1)
	{
		printf("Valor não encontrado.\nTente novamente a operação.\n");
		return -1;
	}
}

void calcnotas(alunos ncad[], int posi, int num)
{
	int i=0, sum;
	
	if(num == 4)
	{
		while(i < NOTA)
		{
			printf("\t\t%d:   ", i+1);
			scanf("%f", &ncad[posi].nota[i]);
			
			if(ncad[posi].nota[i] < 0 || ncad[posi].nota[i] > 10)
				continue;
			i++;
		}
	}
	else
	{
		printf("Corrija a nota %d: ", num);
		do
		{
			if(num == 3) scanf("%f", &ncad[posi].nota[2]);
			else if(num == 2) scanf("%f", &ncad[posi].nota[1]);
			else scanf("%f", &ncad[posi].nota[0]);
			
			puts("\n");
			
			if(ncad[posi].nota[num-1] < 0 || ncad[posi].nota[num-1] > 10)
				printf("Valor não permitido.\nPor favor digite um válido:  ");
			else printf("Alteração bem sucedida.\n");
			
		}while(ncad[posi].nota[num-1] < 0 || ncad[posi].nota[num-1] > 10);
	}
	
	for(i=0; i < NOTA; i++)
		sum += ncad[posi].nota[i];
	
	ncad[posi].media = sum / NOTA;
	
	printf("\nSua média é %.2f\n", ncad[posi].media);
}

int altera(alunos acad[])
{
	int i, pos, opc;
	
	pos = consulta(acad);
	
	if(pos == -1) return FALSE;
	
	printf("Qual nota você deseja alterar? (1 - 2 - 3 - 4 todas)\n");
	scanf("%d", &opc);
	
	if(opc < 1 || opc > 4)
	{
		printf("Inválido. Refaça a operação\n");
		return FALSE;
	}
	
	calcnotas(acad, pos, opc);
}

int exclui(alunos ecad[])
{
	int i, pos;
	char opc;
	
	pos = consulta(ecad);
	if(pos == -1) return FALSE;
	
	printf("Deseja mesmo fazer esta exclusão? S\\N\n");
	opc = getch();
		opc = toupper(opc);
	if(opc == 'N') return FALSE;
	
	ecad[pos] = ecad[cont-1];	//O valor da última posição que foi inserido um registro será copiado para a que se quer deletar
	cont--;		//Garante que em uma consulta não chegue até o último valor que ficaria repetido
				//E também que seja "liberado" o espaço para nova inserção
	printf("Exclusão bem sucedida.\n");
}

void consAluno(alunos cacad[])
{
	FILE *arquivo;
	int j, i;
	
	arquivo = fopen("Alunos.txt", "rb");
	
	if(arquivo == NULL)
		printf("Erro ao abrir o arquivo.\n");
	
	while(fread(cacad, sizeof(alunos), 1, arquivo))
	{
		printf("Matrícula: %d\n", cacad[j].matricula);
		printf("Aluno: %s\n", cacad[j].nome);
		
		printf("Notas:\n");
		for(i=0; i < NOTA; i++)
			printf("\t\t%d:  %.2f\n", i+1, cacad[j].nota[i]);
				
		printf("Média: %.2f\n", cacad[j].media);
		puts("\n\n");
	}
	
	fclose(arquivo);
}

void decisao(alunos apcad[], int opc)
{
	int i;
	
	for(i=0; i <= cont-1; i++)
	{
		if(apcad[i].media >= 7 && opc == TRUE)
			consultaAp(apcad, i);
		if(apcad[i].media < 7 && opc == FALSE)
			consultaAp(apcad, i);
	}
}

void consultaAp(alunos registro[], int j)
{
	int i;
	
	printf("Matrícula: %d\n", registro[j].matricula);
	printf("Aluno: %s\n", registro[j].nome);
	
	printf("Notas:\n");
	for(i=0; i < NOTA; i++)
		printf("\t\t%d:  %.2f\n", i+1, registro[j].nota[i]);
			
	printf("Média: %.2f\n", registro[j].media);
	puts("\n\n");
}
