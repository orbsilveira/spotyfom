#ifndef MUSICA_H
#define MUSICA_H

struct musica {
	char titulo[256];
	char artista[256];
	char letra[256];
	int codigo;
	int execucoes;
};

#endif // MUSICA_H