#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

/*====================================================================*/

//cria descritor
struct desc_queue *CriaDescQueue(struct desc_queue *descritor) {
		descritor = (struct desc_queue *) malloc(sizeof(struct desc_queue));
		if (descritor == NULL)
		{
			printf("Erro de alocacao!");
			return NULL;
		}
		else
		{
			descritor->head = NULL;
			descritor->tail = NULL;
			descritor->tamanho = 0;
			printf("\nDescritor da fila criado!");
			return descritor;
		}
	}

//criar nova musica
struct musica *CriaElementoQueue(void) {
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

//cria nodo
struct nodo_queue *CriaNodoQueue(struct musica *novaMusica) {
		struct nodo_queue *novoNodo = (struct nodo_queue*) malloc(sizeof(struct nodo_queue));
		if (novoNodo == NULL)
		{
			printf("Memoria nao alocada!");
			return NULL;
		}
		else
		{
			novoNodo->prox = NULL;
			novoNodo->info = novaMusica;
			printf("\nNodo criado!");
			return novoNodo;
		}
	}

//esvazia a fila
void DELETE(struct desc_queue *descritor) {
		if ((descritor == NULL) || descritor->head == NULL)
		{
			printf("\nDescritor não alocado ou fila vazia!");
		}
		else
		{
			struct nodo_queue *aux = descritor->head;
			struct nodo_queue *corrente;
			while (aux->prox != NULL)
			{
				corrente = aux;
				aux = aux->prox;
				free(corrente->info);
				free(corrente);
			}
			free(aux);
			descritor->head = NULL;
			descritor->tail = NULL;
			descritor->tamanho = 0;
		}
		free(descritor);
	}

//enqueue
void enqueue(struct desc_queue *descritor, struct nodo_queue *nodo) {
		if (descritor->head == NULL)
		{
			descritor->head = nodo;
			descritor->tail = nodo;
			descritor->tamanho ++;
		}
		else
		{
			descritor->tail->prox = nodo;
			descritor->tail = nodo;
			descritor->tamanho ++;
		}
		printf("\nMusica na fila!");
	}

//dequeue
struct nodo_queue *dequeue(struct desc_queue *descritor) {
		if ((descritor->head == NULL) || (descritor == NULL))
		{
			printf(" Fila vazia ou nao foi criada!");
			return NULL;
		}
		else
		{
			struct nodo_queue *aux = descritor->head;
			descritor->head = descritor->head->prox;
			descritor->tamanho --;
			return aux;
		}
	}

//retorno de fila vazia
int EmptyQueue(struct desc_queue *queue) {
		if(queue->head == NULL)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

//retorna tamanho da fila
int LenghtQueue(struct desc_queue *queue) {
		if (queue == NULL)
		{
			printf("\nFila nao criada!\n");
			return 0;
		}
		else
		{
			return queue->tamanho;
		}
		
	}

//imprime musica
void ImprimeMusicaQueue(struct desc_queue *descritor, int posicao) {
		int posicaoAux = 0;
		if (posicao > descritor->tamanho)
		{
			printf(" Posicao fora da fila!");
		}
		else
		{
			struct nodo_queue *aux = descritor->head;
			while (aux != NULL)
			{
				if (posicaoAux == posicao)
				{
					printf("\n**************************************");
					printf("\nTitulo: %s\n", aux->info->titulo);
					printf("Artista: %s\n", aux->info->artista);
					printf("Letra: %s\n", aux->info->letra);
					printf("Codigo: %d\n", aux->info->codigo);
					printf("Execucoes: %d\n", aux->info->execucoes);
					break;
				}
				aux = aux->prox;
				posicaoAux++;
			}
		}
	}

//imprime fila de musicas
void ShowQueue(struct desc_queue *descritor) {
		if (descritor == NULL)
		{
			printf("\nFila não criada!");
		}
		else
		{
			for (int i = 0; i <= descritor->tamanho; i++)
			{
				ImprimeMusicaQueue(descritor, i);
			}
		}
	}

/*====================================================================*/