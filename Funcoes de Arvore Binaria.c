/*
UnB/FGA - Estrutura de Dados e Algoritmos
Codigo que recebe valores inteiros positivos a serem inseridos em uma arvore
Este exibe a profundidade da arvore, a apresentacao dos valores dos nos,
O numero de termos (nos) da arvore e a soma dos valore dos nos

Compilador utilizado: gcc -g -o 2testArvore -W -Wall -pedantic -ansi -I. 2testArvore.c -lm
*/

#include <stdio.h>
#include <stdlib.h>
#define INCREMENTO_ALTURA 1
#define INCREMENTO_NUMERO_TERMO 1
#define CONDICAO_DE_PARADA 999
#define SET_VALOR_RAIZ 0

/*Estrutura dos termos(nos)*/
typedef struct noArvore
{
	unsigned int valor;
	struct noArvore *noDireitoDoPai;
	struct noArvore *noEsquerdoDoPai;
}noArvore;

noArvore *setNovoNo(noArvore *novoNo, const unsigned int novoValorParaInserir)
{
	novoNo = malloc(sizeof(noArvore));
	novoNo->valor = novoValorParaInserir;
	novoNo->noDireitoDoPai = NULL;
	novoNo->noEsquerdoDoPai = NULL;

	return novoNo;
}

/*
Insere um novo no na arvore, de maneira recursiva, percorrendo a arvore a procura do no
que deve ser inserido, ate passa a referencia do pai que tera o novo no inserido
*/
void insereNovoNo(noArvore *busca, const unsigned int novoValorParaInserir)
{
	noArvore *novoNo = NULL;
	int novoValorDiferenteCondicaoParada = (novoValorParaInserir != CONDICAO_DE_PARADA);
	int novoValorDiferenteValorSetado = (busca->valor != SET_VALOR_RAIZ);
	int novoValorMaiorValorPresenteNo = (novoValorParaInserir > busca->valor);
	int novoValorMenorValorPresenteNo = (novoValorParaInserir < busca->valor);
	int noDireitaBuscaIgualNULL = (busca->noDireitoDoPai == NULL);
	int noEsquerdaBuscaIgualNULL = (busca->noEsquerdoDoPai == NULL);

	if(novoValorDiferenteCondicaoParada)
	{
		if(novoValorDiferenteValorSetado){
			if(novoValorMaiorValorPresenteNo)
			{
				if(noDireitaBuscaIgualNULL)
				{
					novoNo = setNovoNo(novoNo, novoValorParaInserir);
				
					busca->noDireitoDoPai = novoNo;
				}else
				{
					insereNovoNo(busca->noDireitoDoPai, novoValorParaInserir);
				}
			}
			else if(novoValorMenorValorPresenteNo)
			{
				if(noEsquerdaBuscaIgualNULL)
				{
			
					busca->noEsquerdoDoPai = novoNo;
				}else
				{
					insereNovoNo(busca->noEsquerdoDoPai, novoValorParaInserir);
				}
			}
		}
		else
		{
			busca->valor = novoValorParaInserir;
		}
	}
	else
	{
		/*Nada para fazer, pois a arvore nao deve inserir o valor de condicao de parada*/
	}
}

/*Percorre a arvore recursivamente a fim de obter sua profundidade*/
int profundidadeTotalDaArvore(const noArvore* busca)
{
	int profundidadeDaArvore = 0;
	int alturaDaArvorePelaEsquerda = 0;
	int alturaDaArvorePelaDireita = 0;
	
	if(busca)
	{
		alturaDaArvorePelaEsquerda = profundidadeTotalDaArvore(busca->noEsquerdoDoPai);
		alturaDaArvorePelaDireita = profundidadeTotalDaArvore(busca->noDireitoDoPai);
		
		if(alturaDaArvorePelaEsquerda > alturaDaArvorePelaDireita)
		{
			profundidadeDaArvore = alturaDaArvorePelaEsquerda + INCREMENTO_ALTURA;		
		}
		else
		{
			profundidadeDaArvore = alturaDaArvorePelaDireita + INCREMENTO_ALTURA;
		}
	}
	else
	{
		profundidadeDaArvore = 0;
	}
	
	return profundidadeDaArvore;
}


/*Percorre a arvore recursivamente exibindo os valores inteiros em ordem*/
void imprimeValoresArvore(const noArvore *busca)
{
	if(busca)
	{
		imprimeValoresArvore(busca->noEsquerdoDoPai);
		printf("%d ", busca->valor);
		imprimeValoresArvore(busca->noDireitoDoPai);
	}
}

/*Percorre a arvore revursivamente retornando o numero de nos da arvore*/
int numeroTermosArvore(noArvore *busca)
{
	int numeroTermos = 0;

	if(busca)
	{
		numeroTermos = numeroTermosArvore(busca->noDireitoDoPai) 
		+ numeroTermosArvore(busca->noEsquerdoDoPai) + INCREMENTO_NUMERO_TERMO;
	}else
	{
		numeroTermos = 0;
	}

	return numeroTermos;
}

/*Percorre a arvore recursivamente retornando a soma dos valores dos nos*/
int calculaSomaDosTermos(const noArvore *busca)
{
	int somaTermosArvore = 0;

	if(busca)
	{
		somaTermosArvore = calculaSomaDosTermos(busca->noDireitoDoPai) 
		+ calculaSomaDosTermos(busca->noEsquerdoDoPai) + busca->valor;
	}
	else
	{
		somaTermosArvore = 0;
	}

	return somaTermosArvore;
}

/*Inicializa raiz da arvore*/
noArvore *setRaiz(noArvore *raizDaArvore)
{
	raizDaArvore = setNovoNo(raizDaArvore, SET_VALOR_RAIZ);

	return raizDaArvore;
}

/*Insere valores na arvore*/
noArvore *recebeValores(noArvore *raizDaArvore)
{
	int novoValorParaInserir = 0;

	printf("Entre com os valores da arvore por vez\n");
	printf("Para encerrar a insercao de valores, insira o valor 999\n");
	scanf("%d", &novoValorParaInserir);
	insereNovoNo(raizDaArvore, novoValorParaInserir);
	
	while(novoValorParaInserir != CONDICAO_DE_PARADA)
	{
		scanf(" %d", &novoValorParaInserir);
		insereNovoNo(raizDaArvore, novoValorParaInserir);	
	}

	return raizDaArvore;
}

/*Imprime resultados sobre a arvore*/
void imprimeResultados(noArvore *raizDaArvore)
{
	int alturaTotalDaArvore = 0;
	int numeroDeNos = 0;
	int somaDosNos = 0;

	printf("\n\n");
	printf("Termos da arvore: \t");
	imprimeValoresArvore(raizDaArvore);
	printf("\n");
	
	numeroDeNos = numeroTermosArvore(raizDaArvore);
	printf("Numero de nos: \t\t%d\n", numeroDeNos);
	
	somaDosNos = calculaSomaDosTermos(raizDaArvore);
	printf("Soma dos nos: \t\t%d\n", somaDosNos);
	
	alturaTotalDaArvore = profundidadeTotalDaArvore(raizDaArvore);
	printf("Altura da arvore: \t%d\n", alturaTotalDaArvore);
}

int main(void)
{
	noArvore *raizDaArvore = NULL;
	
	raizDaArvore = setRaiz(raizDaArvore);
	
	raizDaArvore = recebeValores(raizDaArvore);
	
	imprimeResultados(raizDaArvore);
		
	return 0;
}
