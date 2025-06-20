#include "musica.h"

/*====================================================================*/

struct nodo_queue {
	struct nodo_queue *prox;
	struct musica *info;
};

struct desc_queue {
	struct nodo_queue *head;
	struct nodo_queue *tail;
	int tamanho;
};

/*====================================================================*/

struct desc_queue *CriaDescQueue(struct desc_queue *descritor);
struct nodo_queue *CriaNodoQueue(struct musica *novaMusica);
struct musica *CriaElementoQueue(void);
void enqueue(struct desc_queue *descritor, struct nodo_queue *nodo);
struct nodo_queue *dequeue(struct desc_queue *descritor);
void DELETE(struct desc_queue *descritor);
int EmptyQueue(struct desc_queue *queue);
int LenghtQueue(struct desc_queue *queue);
void ImprimeMusicaQueue(struct desc_queue *descritor, int posicao);
void ShowQueue(struct desc_queue *descritor);