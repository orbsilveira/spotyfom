#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "stack.h"
#include "LSE.h"
#include "musica.h"

int parse_linha_para_musica(char *linha_do_arquivo, struct musica *musica_destino);

int main() {
    FILE *arquivo;
	struct musica *musica = NULL;
	struct nodo *novonodo = NULL;
	struct desc_lista_encadeada *acervo = NULL;
    char linha[1024]; // Buffer para ler cada linha do arquivo
    int quantidade_musicas;
	int op = 0;
	
	do {	
			if (acervo == NULL)
			{
				acervo = CriaDescritorLSE();
				char name[20];
				printf("              ######### Carregar banco de dados #########\n");
				printf("Digitar nome do arquivo com extensao (arquivo.txt) ou digitar 's' para sair: ");
				scanf("%s", name);

				if (strcmp(name, "s") == 0)
				{
					return 1;
				}

				arquivo = fopen(name, "r");
    			if (arquivo == NULL) {
    				perror("Erro ao abrir o arquivo");
    				return 1;
    			}

    			if (fgets(linha, sizeof(linha), arquivo) != NULL) {
        			quantidade_musicas = atoi(linha);
        			printf("Quantidade total de músicas informada no arquivo: %d\n", quantidade_musicas);
    			} else {
        			fprintf(stderr, "Erro ao ler a quantidade de músicas do arquivo.\n");
        			fclose(arquivo);
    				return 1;
    			}

				int musicas_lidas = 0;
				int posicao = 0;
				while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        			struct musica nova_musica; // Cria uma struct temporária para preencher

        			if (parse_linha_para_musica(linha, &nova_musica) == 0) {
						struct musica *m = malloc(sizeof(struct musica));
						*m = nova_musica;
						novonodo = CriaNodoLSE(m);
						insere(acervo, novonodo, posicao);
            			//printf("Música processada: %s - %s\n", nova_musica.titulo, nova_musica.artista);
            			musicas_lidas++;
						posicao ++;
        			} else {
            			fprintf(stderr, "Skipping malformed line: %s\n", linha);
        			}
    			}
				printf("\nTotal de músicas lidas e processadas: %d\n", musicas_lidas);
			}
			
			printf("\n\n========== MENU SPOTYFOM ==========\n");
			printf(" [0] Sair;\n");
			printf(" [1] Execucao;\n");
			printf(" [2] Selecionar Playlist;\n");
			printf(" [3] Busca;\n");
			printf(" [4] Impressao;\n");
			printf(" [5] Relatorio;\n");
			printf(" [6] Verificar tamanho do acervo;\n");
			printf(" [7] Free no acervo;\n");
			printf("===========================================\n");
		
			printf(" Selecao: ");
			scanf("%d", &op);
			setbuf(stdin, NULL);
		
			if (op < 0 || op > 7) {
				printf("\nOpcao Invalida!\n");
			}
			else
			{
				switch (op)
				{
					case 1:
						break;
					case 2:
						break;
					case 3:
						char selec;
						printf("Busca por:\n [c] Codigo\n [t] Titulo\n [a] Artista\n Selecao: ");
						scanf(" %c", &selec);

						switch (selec)
						{
						case 'c':
							printf("\nBusca por codigo.\n");
							break;
						case 't':
							printf("\nBusca por titulo.\n");
							break;
						case 'a':
							printf("\nBusca por artista.\n");
							break;
						}

						break;
					case 4:
						break;
					case 5:
						break;
					case 6:
						printf("\n Tamanho do acervo: %d", tamanho(acervo));
						break;
					case 7:
						libera(acervo);
						break;
				}
			
			}
	} while (op != 0);
    return 0;
}

//funções extras
int parse_linha_para_musica(char *linha_do_arquivo, struct musica *musica_destino) {
    if (linha_do_arquivo == NULL || musica_destino == NULL) {
        return -1; // Parâmetros inválidos
    }

    // Cria uma cópia da linha, pois strtok modifica a string original
    char *linha_copia = strdup(linha_do_arquivo);
    if (linha_copia == NULL) {
        perror("Erro ao alocar memória para cópia da linha");
        return -1;
    }

    // Remove o caractere de nova linha, se houver
    linha_copia[strcspn(linha_copia, "\n")] = '\0';

    char *token;

    // A ordem dos campos no arquivo é: codigo;execucoes;titulo;letra;artista

    // 1. Código (int)
    token = strtok(linha_copia, ";");
    if (token == NULL) {
        fprintf(stderr, "Erro de parsing: Código não encontrado.\n");
        free(linha_copia);
        return -1;
    }
    musica_destino->codigo = atoi(token);

    // 2. Execuções (int)
    token = strtok(NULL, ";");
    if (token == NULL) {
        fprintf(stderr, "Erro de parsing: Execuções não encontradas.\n");
        free(linha_copia);
        return -1;
    }
    musica_destino->execucoes = atoi(token);

    // 3. Título (string)
    token = strtok(NULL, ";");
    if (token == NULL) {
        fprintf(stderr, "Erro de parsing: Título não encontrado.\n");
        free(linha_copia);
        return -1;
    }
    // strncpy é mais seguro para evitar estouro de buffer
    strncpy(musica_destino->titulo, token, sizeof(musica_destino->titulo) - 1);
    musica_destino->titulo[sizeof(musica_destino->titulo) - 1] = '\0'; // Garante null-termination

    // 4. Letra (string)
    token = strtok(NULL, ";");
    if (token == NULL) {
        fprintf(stderr, "Erro de parsing: Letra não encontrada.\n");
        free(linha_copia);
        return -1;
    }
    strncpy(musica_destino->letra, token, sizeof(musica_destino->letra) - 1);
    musica_destino->letra[sizeof(musica_destino->letra) - 1] = '\0';

    // 5. Artista (string)
    token = strtok(NULL, ";");
    if (token == NULL) {
        fprintf(stderr, "Erro de parsing: Artista não encontrado.\n");
        free(linha_copia);
        return -1;
    }
    strncpy(musica_destino->artista, token, sizeof(musica_destino->artista) - 1);
    musica_destino->artista[sizeof(musica_destino->artista) - 1] = '\0';

    // Libera a memória alocada para a cópia da linha
    free(linha_copia);

    return 0; // Sucesso
}