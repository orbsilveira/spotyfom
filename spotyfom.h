#include "musica.h"

/*====================================================================*/

int parserNovoAcervo(char *linha_do_arquivo, struct musica *musica_destino);
int parserBackup(char *linha_do_arquivo, struct musica *musica_destino);
struct musica *busca(struct desc_lista_encadeada *descritor);
struct musica *codigo(struct desc_lista_encadeada *descritor);
struct musica *titulo(struct desc_lista_encadeada *descritor);
struct musica *artista(struct desc_lista_encadeada *descritor);
void salvarAcervo(struct desc_lista_encadeada *descritor);
struct desc_lista_encadeada *carregaAcervo(struct desc_lista_encadeada *acervo);
void execucao(struct desc_queue *fila, struct desc_stack *pilha);