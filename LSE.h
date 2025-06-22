#include "musica.h"

struct nodo{
	struct musica *info;
	struct nodo *prox;
};

struct desc_lista_encadeada{
	int tamanho;
	struct nodo *lista;
};

struct nodo* CriaNodoLSE(struct musica *novaMusica);
struct desc_lista_encadeada *CriaDescritorLSE(void);
struct nodo* removeLista(struct desc_lista_encadeada *minhaLista, int posicao);
void insere(struct desc_lista_encadeada *minhaLista, struct nodo *novo_elemento, int posicao);
int tamanho(struct desc_lista_encadeada *minhaLista);
void libera(struct desc_lista_encadeada *minhaLista);
void imprime(struct desc_lista_encadeada *minhaLista);
struct nodo* get(struct desc_lista_encadeada *minhaLista, int posicao);
void set(struct desc_lista_encadeada *minhaLista, int valor, int posicao);
