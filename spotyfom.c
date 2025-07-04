#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "stack.h"
#include "LSE.h"
#include "musica.h"
#include "spotyfom.h"

/*====================================================================*/

int parserNovoAcervo(char *linha_do_arquivo, struct musica *musica_destino) {
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

int parserBackup(char *linha_do_arquivo, struct musica *musica_destino) {
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
	
	// 5. Execuções
	token = strtok(NULL, ";");
	musica_destino->execucoes = atoi(token);

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
        fprintf(arquivo, "%s;%d;%s;%s;%d;\n",
              	aux->info->artista,
				aux->info->codigo,
				aux->info->titulo,
                aux->info->letra,
                aux->info->execucoes);
        aux = aux->prox;
    }

    fclose(arquivo);
}

struct desc_lista_encadeada *carregaAcervo(struct desc_lista_encadeada *acervo) {
	if (acervo == NULL) {
		struct nodo *novonodo = NULL;
		char linha[256];
    	int quantidade_musicas, op;
		char name[20];
		FILE *arquivo;

		acervo = CriaDescritorLSE();

		printf("              ######### Carregar banco de dados #########\n");
		printf("[1] Carregar novo acervo\n[2] Carregar backup\n>>> Selecao: ");
		scanf("%d", &op);
		printf("Digitar nome do arquivo com extensao (arquivo.txt): ");
		setbuf(stdin, NULL);
		scanf("%s", name);

		arquivo = fopen(name, "r");

    	if (fgets(linha, sizeof(linha), arquivo) != NULL) {
			quantidade_musicas = atoi(linha);
    		printf("Quantidade total de músicas informada no arquivo: %d\n", quantidade_musicas);
		} else {
    		printf("Erro!");
    		fclose(arquivo);
		}

		int musicas_lidas = 0;
		int posicao = 0;

		switch (op)
		{
			case 1:
				while (fgets(linha, sizeof(linha), arquivo) != NULL) {
					struct musica nova_musica;
					if (parserNovoAcervo(linha, &nova_musica) == 0) {
						struct musica *m = malloc(sizeof(struct musica));
						*m = nova_musica;
						novonodo = CriaNodoLSE(m);
						insere(acervo, novonodo, posicao);
        				musicas_lidas++;
						posicao ++;
       				} else {
           				printf("Erro no parser!");
    				}
   				}
				printf("\nTotal de músicas lidas: %d\n", musicas_lidas);
				break;
			case 2:
				while (fgets(linha, sizeof(linha), arquivo) != NULL) {
					struct musica nova_musica;
					if (parserBackup(linha, &nova_musica) == 0) {
						struct musica *m = malloc(sizeof(struct musica));
						*m = nova_musica;
						novonodo = CriaNodoLSE(m);
						insere(acervo, novonodo, posicao);
        				musicas_lidas++;
						posicao ++;
       				} else {
           				printf("Erro no parser!");
    				}
   				}
				printf("\nTotal de músicas lidas: %d\n", musicas_lidas);
				break;
		}
		
	}
	return acervo;
}

void execucao(struct desc_queue *fila, struct desc_stack *pilha) {
	int op;
	printf("[1] Playlist Aleatoria\n[2] Playlist Pessoal\n>>> Selecao: ");
	scanf("%d", &op);
	switch (op)
	{
	case 1:
		struct nodo_queue *auxqueue = fila->head;
		while (auxqueue != NULL)
		{
			auxqueue->info->execucoes ++;
			dequeue(fila);
			auxqueue = auxqueue->prox;
		}
		break;
	
	case 2:
		struct nodo_stack *auxstack = pilha->topo;
		while (auxstack != NULL)
		{
			auxstack->info->execucoes ++;
			pop(pilha);
			auxstack = auxstack->prox;
		}
		break;
	}
}