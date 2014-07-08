#include<stdio.h>

Tesoura corta papel
    Papel cobre pedra
    Pedra esmaga Lagarto
    Lagarto envenena Spock
    Spock dobra tesoura
    Tesoura decapita lagarto
    Lagarto come papel
    Papel desqualifica Spock
    Spock vaporiza pedra
    Pedra esmaga tesoura

#define PEDRA 0
#define PAPEL 1
#define TESOURA 2
#define LAGARTO 3
#define SPOCK 4



int define_vencedor(int jogador1, int jogador2)
{
	switch: jogador1
		case 0:
			if ( jogador2 == 3 || jogador2 == 2)
				printf("Pedra venceu!");
		return jogador1;
	
		case 1:
			if ( jogador2 == 0 || jogador2 == 4)
				printf("Papel venceu!");
		return jogador1;

		case 2:
			if ( jogador2 == 1 || jogador2 == 3)
				printf("Tesoura venceu!");
		return jogador1;

		case 3:
			if ( jogador2 == 4 || jogador2 == 1)
				printf("Lagarto venceu!");
		return jogador1;	

		case 4:
			if ( jogador2 == 0 || jogador2 == 2)
				printf("Spock venceu!");
		return jogador1;
		
		default:
			return jogador2;
}



