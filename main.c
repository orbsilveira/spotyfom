#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "stack.h"
#include "LSE.h"
#include "musica.h"

int main() {
    
	int op = 0;
	
	do {
			printf("\n\n========== MENU SPOTYFOM ==========\n");
			printf(" [0] Sair;\n");
			printf(" [1] Carregar banco de dados (musicas.txt);\n");
			printf(" [2] ;\n");
			printf(" [3] ;\n");
			printf(" [4] ;\n");
			printf(" [5] ;\n");
			printf(" [6] ;\n");
			printf(" [7] ;\n");
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
						break;
					case 4:
						break;
					case 5:
						break;
					case 6:
						break;
					case 7:
						break;
				}
			
			}
	} while (op != 0);
    return 0;
}