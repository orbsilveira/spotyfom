#include "musica.h"

/*====================================================================*/

int parse_linha_para_musica(char *linha_do_arquivo, struct musica *musica_destino);
struct musica *busca(struct desc_lista_encadeada *descritor);
struct musica *codigo(struct desc_lista_encadeada *descritor);
struct musica *titulo(struct desc_lista_encadeada *descritor);
struct musica *artista(struct desc_lista_encadeada *descritor);
void salvarAcervo(struct desc_lista_encadeada *descritor);