/**
*
@file main.c
*
@brief TPC da Aula 7 - Etapa 1
*
* Othello Game - TPC7 - Etapa 1
*
*
@author Pedro,
pedro.s.conceicao@ua.pt
*
*
@internal
*
Created 31-Out-2017
*
Company University of Aveiro
*
Copyright Copyright (c) 2017, Pedro
*
*
=====================================================================================
*/
 
#define _MAIN_C_		
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "pcolor.h"
#include "othello.h"

int main(int argc, char *argv[])
{   
	
	othello jg1;
    othello *jg = & jg1; //ponteiro "jg" para "jg1"
    int m;
	
	InitGame( jg );
	PrintGameBoard(jg);

    do   // loop for game
    {	
		//###### PLAYER 1 #######
		textcolor(RESET,BLUE,WHITE);
		printf("\n##########  Player 1 Turn '0' ##########\n");
		ResetTextColors();
		do  // loop until valid user play
       	{		
			m=GetPlayerMove(jg);
       	} while( ! CheckMove( jg , m , JOGADOR1));
        PrintGameBoard( jg );
        if ( WinGame(jg,JOGADOR2) ) break;   // break if Player 1 won
		if ( WinGame(jg,JOGADOR1)) break;	// break if Player 2 won
		textcolor(RESET,RED,WHITE);
		printf("\n##########  Player 2 Turn 'X'  ##########\n            I'm thinking...\n");
		ResetTextColors();
		//###### PLAYER 2/COMPUTER #######
        do  // loop until valid computer play
        {
			m=GenerateMove(jg);sleep(2);
			//m=GetPlayerMove(jg);
        } while( ! CheckMove( jg , m , JOGADOR2));
        PrintGameBoard( jg );
		if ( WinGame(jg,JOGADOR1)) break;   // break if Player 1 won
		if ( WinGame(jg,JOGADOR2)) break;  // break if Player 2 won
	} while(1);   // break loop if anyone wins
	printf("################## END ##################\n\n");
    return 0;

}


