#include <stdio.h>
#include <stdlib.h>
#include "LSE.h"

struct nodo *CriaNodoLSE(struct musica *novaMusica){//cria novos nodos para a lista mas não inseri
	struct nodo *novoElemento = (struct nodo *)malloc(sizeof(struct nodo));
	novoElemento->info = novaMusica;
	novoElemento->prox =  NULL;
	return novoElemento;
}

struct desc_lista_encadeada *CriaDescritorLSE(void){//cria descritores de listas
	struct desc_lista_encadeada *novoDescLista = (struct desc_lista_encadeada *)malloc(sizeof(struct desc_lista_encadeada));
	novoDescLista->tamanho = 0;
	novoDescLista->lista = NULL;
	return novoDescLista;
}

struct nodo* removeLista(struct desc_lista_encadeada *minhaLista, int posicao){
	if((minhaLista->tamanho ==0)||(posicao > minhaLista->tamanho)){ //posicao nao existe na lista não remove nada
		printf("posicao não existe OU LISTA VAZIA!\n");
		return NULL;
	}
	else{
		if(posicao==0){ //delecao no inicio da lista atualiza apenas o ponteiro da lista do descritor de lista
			struct nodo *aux = minhaLista->lista;
			minhaLista->lista = minhaLista->lista->prox;
			minhaLista->tamanho--;
			return aux; 
		}
		else{ //delecao no meio ou no fim da lista
			int listaPos=0;
			struct nodo *anterior;
			struct nodo *aux = minhaLista->lista;
			while(aux != NULL){
				anterior = aux;
				aux = aux->prox;
				listaPos++;
				if(listaPos == posicao){
					anterior->prox = aux->prox;
					minhaLista->tamanho--;
					return aux;
				}
			}	
		}
	}
}


void insere(struct desc_lista_encadeada *minhaLista, struct nodo *novo_elemento, int posicao){
	if((minhaLista->lista == NULL)||(posicao ==0)){//insercao no inicio da lista
		novo_elemento->prox = minhaLista->lista;
		minhaLista->lista = novo_elemento;
		minhaLista->tamanho++;
	}
	else{ //caso de insercao no meio ou no fim da lista
		struct nodo *aux = minhaLista->lista;
		int listaPos = 0;
		if(minhaLista->tamanho < posicao){//posicao invalida na lista -> insere no final
			while(aux->prox != NULL){
				aux = aux->prox; 
			}
			aux->prox = novo_elemento;
			minhaLista->tamanho++;
			return;
		}else{//posicao valida na lista insere na posicao
			struct nodo *anterior;
			while(aux != NULL){
				anterior = aux;
				aux = aux->prox; 
				listaPos++;
				if(listaPos == posicao){
					novo_elemento->prox	= aux;
					anterior->prox = novo_elemento;
					minhaLista->tamanho++;
					return;
				}
			}
		}
	}
}


int tamanho(struct desc_lista_encadeada *minhaLista){
	return minhaLista->tamanho;
}


void libera(struct desc_lista_encadeada *minhaLista){
	struct nodo *aux = minhaLista->lista;
	struct nodo *corrente;
	while(aux != NULL){//percorre a lista de nodos liberando o nodos armazenado em corrente
		corrente = aux;
		aux = aux->prox;
		free(corrente->info);
		free(corrente);
	}
	free(aux); //libera o último nodo restante da lista
	minhaLista->lista =NULL; //transforma o ponteiro pra lista NULL no descritor
	minhaLista->tamanho=0; //atualiza o tamanho da lista no descritor
}


void imprime(struct desc_lista_encadeada *minhaLista){
	struct nodo *aux = minhaLista->lista;
	while(aux != NULL){
		printf("Titulo: [%s]\n", aux->info->titulo);
		printf("Autor: [%s]\n", aux->info->artista);
		printf("Letra: [%s]\n", aux->info->letra);
		printf("Codigo: [%d]\n", aux->info->codigo);
		printf("Execucoes: [%d]\n", aux->info->execucoes);
		
		aux = aux->prox;
		printf("\n");
	}
	printf("\n");
}

struct nodo* get(struct desc_lista_encadeada *minhaLista, int posicao){
	struct nodo *aux = minhaLista->lista;
	int posicaoAux = 0;
	while (aux != NULL)
	{
		if (posicao == posicaoAux)
		{
			return aux;
		}
		
		posicaoAux ++;
		aux = aux->prox;
	}
	
}

void set(struct desc_lista_encadeada *minhaLista, int valor, int posicao){}
