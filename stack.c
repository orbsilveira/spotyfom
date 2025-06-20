#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

/*====================================================================*/

//cria descritor da pilha
struct desc_stack *CriaDescStack(struct desc_stack *pilha) {
	pilha = (struct desc_stack*) malloc(sizeof(struct desc_stack));
	if (pilha == NULL)
	{
		printf("Memoria nao alocada!");
	}
	pilha->topo = NULL;
	pilha->tamanho = 0;
	printf("\nDescritor da pilha criado!");
	return pilha;
	}

//cria novo nodo
struct nodo_stack *CriaNodoStack(struct musica *novaMusica) {
	struct nodo_stack *novoNodo = (struct nodo_stack*) malloc(sizeof(struct nodo_stack));
	if (novoNodo == NULL)
	{
		printf("Memoria nao alocada!");
	}
	novoNodo->prox = NULL;
	novoNodo->info = novaMusica;
	printf("\nNodo criado!");
	return novoNodo;
}

//criar nova musica
struct musica *CriaElementoStack(void) {
	struct musica *novaMusica = (struct musica *) malloc(sizeof(struct musica));
	if (novaMusica == NULL)
	{
		printf("Memoria nao alocada!");
	}
	printf("\nTitulo da musica: ");
	fgets(novaMusica->titulo, sizeof(novaMusica->titulo), stdin);
	novaMusica->titulo[strcspn(novaMusica->titulo, "\n")] = 0;
	
	printf("Nome do artista: ");
	fgets(novaMusica->artista, sizeof(novaMusica->artista), stdin);
	novaMusica->artista[strcspn(novaMusica->artista, "\n")] = 0;
	
	printf("Letra da musica: ");
	fgets(novaMusica->letra, sizeof(novaMusica->letra), stdin);
	novaMusica->letra[strcspn(novaMusica->letra, "\n")] = 0;
	
	printf("Codigo da musica: ");
	scanf("%d", &novaMusica->codigo);
	getchar();

	novaMusica->execucoes = 0;
	printf("\nMusica criada!");
	return novaMusica;
}

//push
void push(struct desc_stack *descritor, struct nodo_stack *nodo) {
		if (descritor->topo == NULL)
		{
			descritor->topo = nodo;
			descritor->tamanho ++;
		}
		else
		{
			nodo->prox = descritor->topo;
			descritor->topo = nodo;
			descritor->tamanho ++;
		}
		printf("\nMusica empilhada!");
	}

//pop
struct nodo_stack *pop(struct desc_stack *descritor) {
		if (descritor->topo == NULL)
		{
			printf(" Pilha Vazia!");
			return NULL;
		}
		else
		{
			struct nodo_stack *aux = descritor->topo;
			descritor->topo = descritor->topo->prox;
			descritor->tamanho --;
			return aux;
		}
	}

//imprime musica
void ImprimeMusicaStack(struct desc_stack *descritor, int posicao) {
		int posicaoAux = 0;
		if (posicao >= descritor->tamanho)
		{
			printf(" Posicao fora da pilha!");
		}
		else
		{
			struct nodo_stack *aux = descritor->topo;
			while (aux != NULL)
			{
				if (posicaoAux == posicao)
				{
					printf("\n====================================\n");
					printf("\nTitulo: %s\n", aux->info->titulo);
					printf("Artista: %s\n", aux->info->artista);
					printf("Letra: %s\n", aux->info->letra);
					printf("Codigo: %d\n", aux->info->codigo);
					printf("Execucoes: %d\n", aux->info->execucoes);
					printf("\n====================================\n");
					break;
				}
				aux = aux->prox;
				posicaoAux++;
			}
		}
	}

//imprime pilha de musicas
void imprimePilha(struct desc_stack *descritor) {
		for (int i = 0; i <= descritor->tamanho; i++)
		{
			ImprimeMusicaStack(descritor, i);
		}
	}

//retorno de pilha vazia
int EmptyStack(struct desc_stack *pilha) {
	if(pilha->topo == NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//retorno quantidade de itens na pilha
int length(struct desc_stack *pilha) {
	return pilha->tamanho;
}

//retorna primeiro item da pilha
struct nodo_stack* top(struct desc_stack *pilha) {
	if (pilha->topo == NULL)
	{
		printf(" Pilha Vazia!");
		return NULL;
	}
	else
	{
		return pilha->topo;
	}
}

//libera memoria
void freeStack(struct desc_stack *pilha) {
		if (pilha->topo != NULL)
		{
			struct nodo_stack *aux = pilha->topo;
			struct nodo_stack *corrente;
			while (aux->prox != NULL)
			{
				corrente = aux;
				aux = aux->prox;
				free(corrente->info);
				free(corrente);
			}
			free(aux);
			pilha->topo = NULL;
			pilha->tamanho = 0;
		}
		free(pilha);
	}
