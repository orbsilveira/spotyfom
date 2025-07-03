#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "stack.h"
#include "LSE.h"
#include "musica.h"
#include "spotyfom.h"

/*====================================================================*/

int parseMusica(char *linha_do_arquivo, struct musica *musica_destino) {
    if (linha_do_arquivo == NULL || musica_destino == NULL) {
        return -1; // Parâmetros inválidos
    }

    // Cria uma cópia da linha
    char *linha_copia = strdup(linha_do_arquivo);

    // Remove o caractere de nova linha
    linha_copia[strcspn(linha_copia, "\n")] = '\0';

    char *token;

    // ordem dos campos no arquivo é: artista;codigo;titulo;letra;execucoes

    // 1. Artista
    token = strtok(linha_copia, ";");
	strncpy(musica_destino->artista, token, sizeof(musica_destino->artista) - 1);
    musica_destino->artista[sizeof(musica_destino->artista) - 1] = '\0';

    // 2. Código
    token = strtok(NULL, ";");
    musica_destino->codigo = atoi(token);

    // 3. Título
    token = strtok(NULL, ";");
    strncpy(musica_destino->titulo, token, sizeof(musica_destino->titulo) - 1);
    musica_destino->titulo[sizeof(musica_destino->titulo) - 1] = '\0';

    // 4. Letra
    token = strtok(NULL, ";");
    strncpy(musica_destino->letra, token, sizeof(musica_destino->letra) - 1);
    musica_destino->letra[sizeof(musica_destino->letra) - 1] = '\0';
	
	// Execuções
	musica_destino->execucoes = 0;

    free(linha_copia);

    return 0;
}

struct musica *busca(struct desc_lista_encadeada *descritor) {
	char selec;
	printf("Busca por:\n [c] Codigo\n [t] Titulo\n [a] Artista\n \tSelecao: ");
	scanf(" %c", &selec);

	switch (selec) {
		case 'c':
			return codigo(descritor);
			break;
		case 't':
			return titulo(descritor);
			break;
		case 'a':
			return artista(descritor);
			break;
	}
}

struct musica *codigo(struct desc_lista_encadeada *descritor) {
	int codigo;
	struct nodo *aux = descritor->lista;
	printf("\nBusca por codigo.\n");
	printf("Digitar codigo da musica: ");
	scanf("%d", &codigo);

	while (aux != NULL) {
		if (codigo == aux->info->codigo)
		{
			return aux->info;
		}
		aux = aux->prox;
	}
}

struct musica *titulo(struct desc_lista_encadeada *descritor) {
	struct nodo *aux = descritor->lista;
	char titulo[256];
	int c;
	printf("\nBusca por titulo.\n");
	printf("Digitar titulo da musica: ");
    while ((c = getchar()) != '\n' && c != EOF);
	fgets(titulo, sizeof(titulo), stdin);
	titulo[strcspn(titulo, "\n")] = 0; // remove o '\n' do final

	while (aux != NULL)
	{
		if (strcasecmp(titulo, aux->info->titulo) == 0)
		{
			return aux->info;
		}
		aux = aux->prox;
	}
}

struct musica *artista(struct desc_lista_encadeada *descritor) {
	struct nodo *aux = descritor->lista;
	char artista[256];
	int quantidade = 0;
	printf("\nBusca por artista.\n");
	printf("Digitar artista: ");
	scanf("%s", artista);

	while (aux != NULL) {
		if (strcasecmp(artista, aux->info->artista) == 0)
		{
			quantidade++;	
			printf("\n Titulo: %s", aux->info->titulo);
			printf("\n Artista: %s", aux->info->artista);
			printf("\n Letra: %s", aux->info->letra);
			printf("\n Codigo: %d", aux->info->codigo);
			printf("\n Execucoes: %d\n", aux->info->execucoes);
		}
		aux = aux->prox;
	}
			
	if (quantidade > 1) {
		aux = descritor->lista;
		char selec;
		printf("\n%d Musicas encontradas, buscar por codigo ou titulo.", quantidade);
		printf("\nBusca por:\n [c] Codigo\n [t] Titulo\n \tSelecao: ");
		scanf(" %c", &selec);

		switch (selec) {
			case 'c':
				return codigo(descritor);
				break;
			case 't':
				return titulo(descritor);
				break;
		}
	}
	else
	{
		return aux->info;
	}
}

// salvar acervo
void salvarAcervo(struct desc_lista_encadeada *descritor) {
    FILE *arquivo = fopen("acervo.txt", "w");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo para escrita");
        return;
    }

    // Escrever a quantidade na primeira linha
    fprintf(arquivo, "%d\n", descritor->tamanho);

	struct nodo *aux = descritor->lista;
    while (aux != NULL) {
        fprintf(arquivo, "%s;%s;%s;%d;%d\n",
                aux->info->titulo,
                aux->info->artista,
                aux->info->letra,
                aux->info->codigo,
                aux->info->execucoes);
        aux = aux->prox;
    }

    fclose(arquivo);
}