#include "musica.h"

/*====================================================================*/

struct nodo_stack{
	struct nodo_stack *prox;
	struct musica *info;
};

struct desc_stack{
	struct nodo_stack *topo;
	int tamanho;
};

/*====================================================================*/

struct desc_stack *CriaDescStack(struct desc_stack *pilha);
struct nodo_stack *CriaNodoStack(struct musica *novaMusica);
struct musica *CriaElementoStack(void);
void push(struct desc_stack *descritor, struct nodo_stack *nodo);
struct nodo_stack *pop(struct desc_stack *descritor);
void ImprimeMusicaStack(struct desc_stack *descritor, int posicao);
void ImprimeStack(struct desc_stack *descritor);
int EmptyStack(struct desc_stack *pilha);
int LengthStack(struct desc_stack *pilha);
struct nodo_stack* top(struct desc_stack *pilha);
void freeStack(struct desc_stack *pilha);