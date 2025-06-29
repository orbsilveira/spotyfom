#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "stack.h"
#include "LSE.h"
#include "musica.h"
#include "spotyfom.h"

int main() {
    FILE *arquivo;
	struct musica *musica = NULL;
	struct nodo *novonodo = NULL;
	struct nodo_queue *nodoQueue = NULL;
	struct desc_lista_encadeada *acervo = NULL;
	struct desc_queue *fila = NULL;
    char linha[1024]; // Buffer para ler cada linha do arquivo
    int quantidade_musicas;
	int op = 0;
	
	do {	
		////////////////////////////////////////////////////////////////////////////////////////////////
		if (acervo == NULL) {
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
		////////////////////////////////////////////////////////////////////////////////////////////////			
		printf("\n\n========== MENU SPOTYFOM ==========\n");
		printf(" [0] Sair;\n");
		printf(" [1] Execucao;\n");
		printf(" [2] Playlist;\n");
		printf(" [3] Busca;\n");
		printf(" [4] Impressao;\n");
		printf(" [5] Relatorio;\n");
		printf(" [6] Verificar tamanho do acervo;\n");
		printf(" [7] Free no acervo;\n");
		printf("=======================================\n");
		
		printf(" Selecao: ");
		scanf("%d", &op);
		setbuf(stdin, NULL);
		
		if (op < 0 || op > 7) {
			printf("\nOpcao Invalida!\n");
		}
		else {
			switch (op)
			{
			case 1:
				break;
			case 2:
				char selecao;
				printf("Criar playlist aleatoria [r] ou personalizada [p]? ");
				scanf(" %c", &selecao);

				switch (selecao) {
				case 'r':
					int aleatorio = (int)random() % 5001;
					struct nodo *nodoAux;
					fila = CriaDescQueue(fila);
					nodoAux = get(acervo, aleatorio);
					nodoQueue = CriaNodoQueue(nodoAux->info);
					enqueue(fila, nodoQueue);
					break;
				case 'p':
					
					break;
				}

				break;
			case 3:
				struct musica *minhaMusica = NULL;
				minhaMusica = busca(acervo);
				printf("\n Titulo: %s", minhaMusica->titulo);
				printf("\n Artista: %s", minhaMusica->artista);
				printf("\n Letra: %s", minhaMusica->letra);
				printf("\n Codigo: %d", minhaMusica->codigo);
				printf("\n Execucoes: %d", minhaMusica->execucoes);
				break;
			case 4:
				int num;
				printf("\nImprimir acervo [1]\nImprimir fila [2]\nImprimir pilha [3]\nSelecao: ");
				scanf("%d", &num);
				switch (num)
				{
				case 1:
					imprime(acervo);
					break;
				case 2:
					ShowQueue(fila);
					break;
				case 3:
					
					break;
				}
				
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