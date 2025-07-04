#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "queue.h"
#include "stack.h"
#include "LSE.h"
#include "musica.h"
#include "spotyfom.h"

int main() {
	srandom(time(NULL));
	struct musica *musica = NULL;
	struct nodo_queue *nodoQueue = NULL;
	struct nodo_stack *nodoStack = NULL;
	struct desc_lista_encadeada *acervo = NULL;
	struct desc_queue *fila = NULL;
	struct desc_stack *pilha = NULL;
	int op = 0;
	
	do {	
		////////////////////////////////////////////////////////////////////////////////////////////////
		acervo = carregaAcervo(acervo);
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
		printf("==================================\n");
		
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
				execucao(fila, pilha);
				break;
			case 2:
				char selecao;
				printf("Criar playlist aleatoria [r] ou personalizada [p]? ");
				scanf(" %c", &selecao);

				switch (selecao) {
				case 'r':
					int aleatorio, q;
					struct nodo *nodoAux;
					printf("Quantidade de musicas: ");
					scanf("%d", &q);
					if (fila == NULL)
					{
						fila = CriaDescQueue(fila);
					}
					for (int i = 0; i < q; i++)
					{
						aleatorio = (int)random() % 5001;
						nodoAux = get(acervo, aleatorio);
						nodoQueue = CriaNodoQueue(nodoAux->info);
						enqueue(fila, nodoQueue);
					}
					break;
				case 'p':
					int stop = 0;
					struct musica *auxmusica;
					do
					{
						if (pilha == NULL)
						{
							pilha = CriaDescStack(pilha);
						}
						auxmusica = busca(acervo);
						nodoStack = CriaNodoStack(auxmusica);
						push(pilha, nodoStack);

						printf("\nAdicionar nova musica ([0]SIM [1]NAO): ");
						scanf("%d", &stop);
					} while (stop != 1);
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
					ImprimeStack(pilha);
					break;
				}
				break;
			case 5:
				int num2;
				printf("\nSalvar acervo [1]\nSalvar fila [2]\nSalvar pilha [3]\nSelecao: ");
				scanf("%d", &num2);
				switch (num2)
				{
				case 1:
					salvarAcervo(acervo);
					break;
				case 2:
					
					break;
				case 3:
					
					break;
				}
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