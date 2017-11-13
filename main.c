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
	//Singleplayer or Multiplayer
	int option=Option()-'0';

	othello jg1;
    othello *jg = & jg1; //pointer "jg" to "jg1" struct
    int m, score1=0, score2=0, win=0;
	
	InitGame( jg );
	PrintGameBoard(jg);

    do   // loop for game
    {	
		//###### PLAYER 1 #######
		textcolor(RESET,BLUE,WHITE);
		printf("\n##########  Player 1 Turn '0' ##########\n");
		ResetTextColors();
		printf("\n### COMMANDS : q/Q - quit ; s/S - Save ; l/L - Load ###\n\n");
		do  // loop until valid user play
       	{	if ( WinGame(jg,JOGADOR2)){win =1;break;} 			  //Skip play if no movements possible
			m=GetPlayerMove(jg);                    //Player 1 plays
       	} while( ! CheckMove( jg , m , JOGADOR1));
        PrintGameBoard( jg );
        if ( WinGame(jg,JOGADOR2) && WinGame(jg,JOGADOR1)) break;   // Game Over is either player can't play


		//if ( WinGame(jg,JOGADOR1)) break;	// break if Player 2 won
		textcolor(RESET,RED,WHITE);
		printf("\n##########  Player 2 Turn 'X'  ##########\n");
		if(option==1) printf("            I'm thinking...\n");
		ResetTextColors();
		if(option==2) printf("\n### COMMANDS : q/Q - quit ; s/S - Save ; l/L - Load ###\n\n");
		//###### PLAYER 2/COMPUTER #######
        do  // loop until valid computer play
        {
			if (WinGame(jg,JOGADOR2)){win =1;break;} 			  //Skip play if no movements possible
			if(option==1){m=GenerateMove(jg);sleep(2);}   //sleep simulates pc thinking. optional
			if(option==2) m=GetPlayerMove(jg);            // Player 2 plays
        } while( ! CheckMove( jg , m , JOGADOR2));
        PrintGameBoard( jg );
		if ( WinGame(jg,JOGADOR1) && WinGame(jg,JOGADOR2)) break;   // Game Over is either player can't play
		//if ( WinGame(jg,JOGADOR2)) break;  // break if Player 2 won
	} while(!win);   // break loop if anyone wins

	for(int l=0; l<8; l++){
		for(int c=0; c<8; c++){
				if(jg -> T[l][c]==JOGADOR1) score1++;
				if(jg -> T[l][c]==JOGADOR2) score2++;
			}
		}
	if(score1>score2) printf("\n\nPlayer 1 wins! Player 1 %d - %d Player 2\n\n", score1,score2);
	else if(score1<score2) printf("\n\nPlayer 2 wins! Player 2 %d - %d Player 1\n\n", score2,score1);
	else printf("\n\nDraw! Player 1 %d - %d Player 2\n\n",score1,score2);
	printf("################## END ##################\n\n");
    return 0;

}


