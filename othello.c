/**
*
@file othello.c
*
@brief Funções auxiliares
*
* 
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "pcolor.h"
#include "othello.h"

/**
* @brief Gets the input to choose either singleplayer or multiplayer
* @param void
* @return Op char. 1 for singleplayer, 2 for multiplayer
*/
char Option(void)
{	
	char op=0;
	while(op!='1' && op!='2')
	{
		printf("\nType '1' to singleplayer or '2' to multiplayer\nOption:");
		op=getchar();
		getchar();
		fflush(stdin);
	}
	return	op;	
}

/**
* @brief InitGame
* @param Pointer to game char array (*jg)
* @return void
*/
void InitGame( othello *jg){ // todas as céluas a VAZIO exceto as 4 centrais
	
	//Inicializar todas as células com vazio ' '
	for(int l=0;l<8;l++)
	{
		for(int c=0;c<8;c++)
		{
			jg -> T[l][c] = VAZIO;
		}
	}

	//Inicializar células do jogador 1 com 'O'
	jg -> T[3][3] = JOGADOR1;
	jg -> T[4][4] = JOGADOR1;
	
	//Inicializar células do jogador 2 com 'X'
	jg -> T[3][4] = JOGADOR2;
	jg -> T[4][3] = JOGADOR2;
}

/**
* @brief Prints game board
* @param Pointer to game char array (*jg)
* @return void
*/
void PrintGameBoard(othello *jg)
{
	int l, c;
	printf("\n\n");
	printf("     a   b   c   d   e   f   g   h\n");
	for(l=0;l<8;l++)
	{
		printf("   +-------------------------------+\n");
		printf(" %d ",l+1);
		for(c=0;c<8;c++)
		{
			printf("|");
			if(jg->T[l][c]==JOGADOR1){textcolor(RESET,BLUE,WHITE);}
			if(jg->T[l][c]==JOGADOR2){textcolor(RESET,RED,WHITE);}
			printf(" %c ",jg -> T[l][c]);
			ResetTextColors();
		}
		printf("| %d \n",l+1);
	}
	printf("   +-------------------------------+\n");
	printf("     a   b   c   d   e   f   g   h\n");
}


/**
* @brief Saves game board
* @param Pointer to game char array (*jg) and pointer to filename
* @return 1 if succesful ; 0 if unsuccesful
*/
int SaveGame(othello *jg, char *filename)
{	
	FILE *fp=fopen(filename,"w");
	if(fp == NULL) return 0;
	for(int l=0;l<8;l++)
	{
		for(int c=0;c<7;c++)
		{
			fprintf(fp,"%c,",jg -> T[l][c]);
		}
		fprintf(fp,"%c\n",jg -> T[l][7]);
	}
		
	fclose(fp);
	return 1;
}


/**
* @brief Loads game board
* @param Pointer to game char array (*jg) and pointer to filename
* @return 1 if succesful ; 0 if unsuccesful
*/
int LoadGame(othello *jg, char *filename)
{
	FILE *fp=fopen(filename,"rb");
	if(fp == NULL) return 0;
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	fseek(fp, 0, SEEK_SET);  //same as rewind(f);
	char *str = malloc(size + 1);
	fread(str, size, 1, fp);
	fclose(fp);

	char *token;
	int c=0;
	token=strtok(str,",\n");
	while(token!=NULL)
	{
		jg -> T[0][c]= * token;
		token=strtok(NULL,",\n");
		c++;//next column
	}

	free(str);
	return 1;	
}


/**
* @brief Reads keyboard and computes player move
* @param void
* @return player move from 11 to 88; 11 to quit; 10 to load game; 9 to save game
*/

int GetPlayerMove(othello *jg)
{
	char c_cor, l, aux;
	int c=0;
	do{
		printf("Next move coordinates or command: ");
		scanf(" %c",&c_cor);
		scanf("%c",&l);
		if(isalpha(l)){
			aux=l;
			l=c_cor;
			c_cor=aux;
		}
		if(c_cor=='q' || c_cor=='Q'){
			exit(0);
		}
		if(c_cor=='s' || c_cor =='S'){
			int save_game=SaveGame(jg,"othello.txt");
			printf("\nSaving game...\n");
			if(save_game) printf("Game saved!\n");
			else printf("Game not saved.\n");
			c=90;
			break;
		}
		if(c_cor=='l' || c_cor =='L'){
			int load_game=LoadGame(jg,"othello.txt");
			printf("\nLoading game...\n");
			if(load_game){printf("Game loaded!\n");PrintGameBoard( jg );}
			else{printf("Game not found.\nExiting\n");break;}
			c=91;
			break;
		}
		if(atoi(&l)<1 || atoi(&l)>8){
			c_cor='0';
		}
		if(c_cor!='l' || c_cor!='L' || c_cor!='s' ||  c_cor!='S'){
			switch(c_cor){
				case'a':
				case'A':
					c=1;break;
				case'b':
				case'B':
					c=2;break;
				case'c':
				case'C':
					c=3;break;
				case'd':
				case'D':
					c=4;break;
				case'e':
				case'E':
					c=5;break;
				case'f':
				case'F':
					c=6;break;
				case'g':
				case'G':
					c=7;break;
				case'h':
				case'H':
					c=8;break;
				default:
					printf("Invalid Option. Try again! \n");
			}
		}
	}while(c==0);
	if(c==90 || c==91){return 9999;}
	else{return c*10+atoi(&l);}
}

/**
* @brief Checks if the given move is possible
* @param Pointer to board array, Desired move, player 
* @return Int 1 if move is possible, Int 0 if move is not possible
*/
int CheckMove( othello *jg , int move , int player )
{
	for(int l=0;l<8;l++)
	{
		for(int c=0;c<8;c++)
		{
			if(jg -> T[l][c] == player)
			{
				int check_right=CheckRight(jg,l,c,player);
				if(check_right==move){ReversePieces(jg,move,player);return 1;}

				int check_left=CheckLeft(jg,l,c,player);
				if(check_left==move){ReversePieces(jg,move,player);return 1;}

				int check_up=CheckUp(jg,l,c,player);
				if(check_up==move){ReversePieces(jg,move,player);return 1;}

				int check_down=CheckDown(jg,l,c,player);
				if(check_down==move){ReversePieces(jg,move,player);return 1;}
			
				int check_upright=CheckUpRight(jg,l,c,player);
				if(check_upright==move){ReversePieces(jg,move,player);return 1;}

				int check_upleft=CheckUpLeft(jg,l,c,player);
				if(check_upleft==move){ReversePieces(jg,move,player);return 1;}

				int check_downright=CheckDownRight(jg,l,c,player);
				if(check_downright==move){ReversePieces(jg,move,player);return 1;}
				
				int check_downleft=CheckDownLeft(jg,l,c,player);
				if(check_downleft==move){ReversePieces(jg,move,player);return 1;}
			}	
		}					
	}
	return 0;
}


/**
* @brief Checks the right direction of a given cell
* @param Pointer to board array, int line, int collumn, player
* @return Possible move coordinates if there's any else returns 0
*/
int CheckRight (othello *jg , int l , int c , int player)
{
	int opponent=0;
	if(player==JOGADOR1){opponent=JOGADOR2;}
	if(player==JOGADOR2){opponent=JOGADOR1;}
	if(jg -> T[l][c+1] == opponent)
	{
		do{c++;}while(jg -> T[l][c] == opponent && c<7);
		//if(jg-> T[l][c] == player){return 1;}
		if(jg-> T[l][c] == VAZIO){return (c+1)*10+l+1;}
	}
	return 0;
}

/**
* @brief Checks the left direction of a given cell
* @param Pointer to board array, int line, int collumn, player
* @return Possible move coordinates if there's any else returns 0
*/
int CheckLeft (othello *jg , int l , int c , int player)
{
	int opponent=0;
	if(player==JOGADOR1){opponent=JOGADOR2;}
	if(player==JOGADOR2){opponent=JOGADOR1;}
	if(jg -> T[l][c-1] == opponent)
	{
		do{c--;}while(jg -> T[l][c] == opponent && c>0);
		//if(jg-> T[l][c] == player){return 1;}
		if(jg-> T[l][c] == VAZIO){return (c+1)*10+l+1;}
	}
	return 0;
}

/**
* @brief Checks the up direction of a given cell
* @param Pointer to board array, int line, int collumn, player
* @return Possible move coordinates if there's any else returns 0
*/
int CheckUp (othello *jg , int l , int c , int player)
{
	int opponent=0;
	if(player==JOGADOR1){opponent=JOGADOR2;}
	if(player==JOGADOR2){opponent=JOGADOR1;}
	if(jg -> T[l-1][c] == opponent)
	{
		do{l--;}while(jg -> T[l][c] == opponent && l>0);
		//if(jg-> T[l][c] == player){return 1;}
		if(jg-> T[l][c] == VAZIO){return (c+1)*10+l+1;}
	}
	return 0;
}

/**
* @brief Checks the down direction of a given cell
* @param Pointer to board array, int line, int collumn, player
* @return Possible move coordinates if there's any else returns 0
*/
int CheckDown (othello *jg , int l , int c , int player)
{
	int opponent=0;
	if(player==JOGADOR1){opponent=JOGADOR2;}
	if(player==JOGADOR2){opponent=JOGADOR1;}
	if(jg -> T[l+1][c] == opponent)
	{
		do{l++;}while(jg -> T[l][c] == opponent && l<7);
		//if(jg-> T[l][c] == player){return 1;}
		if(jg-> T[l][c] == VAZIO){return (c+1)*10+l+1;}
	}
	return 0;
}

/**
* @brief Checks the upright direction of a given cell
* @param Pointer to board array, int line, int collumn, player
* @return Possible move coordinates if there's any else returns 0
*/
int CheckUpRight (othello *jg , int l , int c , int player)
{
	int opponent=0;
	if(player==JOGADOR1){opponent=JOGADOR2;}
	if(player==JOGADOR2){opponent=JOGADOR1;}
	if(jg -> T[l-1][c+1] == opponent)
	{
		do{l--;c++;}while(jg -> T[l][c] == opponent && l>0 && c<7);
		//if(jg-> T[l][c] == player){return 1;
		if(jg-> T[l][c] == VAZIO){printf("\n%d %d",l,c);return (c+1)*10+l+1;}
	}
	return 0;
}

/**
* @brief Checks the upleft direction of a given cell
* @param Pointer to board array, int line, int collumn, player
* @return Possible move coordinates if there's any else returns 0
*/
int CheckUpLeft (othello *jg , int l , int c , int player)
{
	int opponent=0;
	if(player==JOGADOR1){opponent=JOGADOR2;}
	if(player==JOGADOR2){opponent=JOGADOR1;}
	if(jg -> T[l-1][c-1] == opponent)
	{
		do{l--;c--;}while(jg -> T[l][c] == opponent && l>0 && c>0);
		//if(jg-> T[l][c] == player){return 1;}
		if(jg-> T[l][c] == VAZIO){return (c+1)*10+l+1;}
	}
	return 0;
}

/**
* @brief Checks the downright direction of a given cell
* @param Pointer to board array, int line, int collumn, player
* @return Possible move coordinates if there's any else returns 0
*/
int CheckDownRight (othello *jg , int l , int c , int player)
{
	int opponent=0;
	if(player==JOGADOR1){opponent=JOGADOR2;}
	if(player==JOGADOR2){opponent=JOGADOR1;}
	if(jg -> T[l+1][c+1] == opponent)
	{
		do{l++;c++;}while(jg -> T[l][c] == opponent && l<7 && c<7);
		//if(jg-> T[l][c] == player){return 1;}
		if(jg-> T[l][c] == VAZIO){return (c+1)*10+l+1;}
	}
	return 0;
}

/**
* @brief Checks the downleft direction of a given cell
* @param Pointer to board array, int line, int collumn, player
* @return Possible move coordinates if there's any else returns 0
*/
int CheckDownLeft (othello *jg , int l , int c , int player)
{
	int opponent=0;
	if(player==JOGADOR1){opponent=JOGADOR2;}
	if(player==JOGADOR2){opponent=JOGADOR1;}
	if(jg -> T[l+1][c-1] == opponent)
	{
		do{l++;c--;}while(jg -> T[l][c] == opponent && l<7 && c>0);
		//if(jg-> T[l][c] == player){return 1;}
		if(jg-> T[l][c] == VAZIO){return (c+1)*10+l+1;}
	}
	return 0;
}

/**
* @brief Reverses the pieces after a play
* @param Pointer to board array, int move (cell the user chose to play), player
* @return void
*/
void ReversePieces(othello *jg , int move , int player)
{
	int l=move%10-1;
	int c=move/10-1;
	int cc=10, ll=10;
	int flag=0;

	jg -> T[l][c]=player;
	//right
	for(cc=c+1 ; cc<8 ; cc++){
		if(jg -> T[l][cc] == player){flag=1;break;}
		if(jg -> T[l][cc] == VAZIO) break;
	}
	if(flag){
		for(int n=c+1 ; n<cc ; n++){
			jg -> T[l][n]=player;		
		}
	}
	flag=0;

	//left
	for(cc=c-1 ; cc>-1 ; cc--){
		if(jg -> T[l][cc] == player){flag=1;break;}
		if(jg -> T[l][cc] == VAZIO) break;
	}
	if(flag){
		for(int n=c-1 ; n>cc ; n--){
			jg -> T[l][n]=player;		
		}
	}
	flag=0;

	//up
	for(ll=l+1 ; ll<8 ; ll++){
		if(jg -> T[ll][c] == player){flag=1;break;}
		if(jg -> T[ll][c] == VAZIO) break;
	}
	if(flag){
		for(int n=l+1 ; n<ll ; n++){
			jg -> T[n][c]=player;		
		}
	}
	flag=0;

	//down
	for(ll=l-1 ; ll>-1 ; ll--){
		if(jg -> T[ll][c] == player){flag=1;break;}
		if(jg -> T[ll][c] == VAZIO) break;
	}
	if(flag){
		for(int n=l-1 ; n>ll ; n--){
			jg -> T[n][c]=player;		
		}
	}
	flag=0;
	
	//upright
	for(ll=l-1 ; ll>-1 ; ll--){
		if(c-(ll-l)>8) break;
		if(jg -> T[ll][c-(ll-l)] == player){flag=1;break;}
		if(jg -> T[ll][c-(ll-l)] == VAZIO) break;
	}
	if(flag){
		for(int n=l-1 ; n>ll ; n--){
			jg -> T[n][c-(n-l)]=player;		
		}
	}
	flag=0;

	//downright
	for(ll=l+1 ; ll<8 ; ll++){
		if(c+(ll-l)>8) break;
		if(jg -> T[ll][c+(ll-l)] == player){flag=1;break;}
		if(jg -> T[ll][c+(ll-l)] == VAZIO) break;
	}
	if(flag){
		for(int n=l+1 ; n<ll ; n++){
			jg -> T[n][c+(n-l)]=player;		
		}
	}
	flag=0;

	//upleft
	for(ll=l-1 ; ll>-1 ; ll--){
		if(c+(ll-l)<0) break;
		if(jg -> T[ll][c+(ll-l)] == player){flag=1;break;}
		if(jg -> T[ll][c+(ll-l)] == VAZIO) break;
	}
	if(flag){
		for(int n=l-1 ; n>ll ; n--){
			jg -> T[n][c+(n-l)]=player;		
		}
	}
	flag=0;

	//downleft
	for(ll=l+1 ; ll<8 ; ll++){
		if(c-(ll-l)<0) break;
		if(jg -> T[ll][c-(ll-l)] == player){flag=1;break;}
		if(jg -> T[ll][c-(ll-l)] == VAZIO) break;
	}
	if(flag){
		for(int n=l+1 ; n<ll ; n++){
			jg -> T[n][c-(n-l)]=player;		
		}
	}
	flag=0;

}

/**
* @brief Checks if there are any possible moves for a given player
* @param Pointer to board array, player
* @return 1 if there are no possible moves, 0 if there is at least one possible move
*/
int WinGame(othello *jg,int player)
{
	int flag=0, l, c;
	for( l=0;l<8;l++)
	{
		for( c=0;c<8;c++)
		{
			if(jg->T[l][c]==player){
				if(CheckRight(jg,l,c,player)){flag=1;break;}
				if(CheckLeft(jg,l,c,player)){flag=1;break;}
				if(CheckUp(jg,l,c,player)){flag=1;break;}
				if(CheckDown(jg,l,c,player)){flag=1;break;}
				if(CheckUpLeft(jg,l,c,player)){flag=1;break;}
				if(CheckUpRight(jg,l,c,player)){flag=1;break;}
				if(CheckDownLeft(jg,l,c,player)){flag=1;break;}
				if(CheckDownRight(jg,l,c,player)){flag=1;break;}
			}
		}
		if(flag) break;
	}

	if(!flag){
		return 1;
	}
	return 0;
}


/**
* @brief Generates a move for the CPU
* @param Pointer to game board
* @return Move to be played
*/
int GenerateMove(othello *jg)
{
	int moves[100]={0};
	int moves_count=0;

	for(int l=0;l<8;l++)
	{
		for(int c=0;c<8;c++)
		{
			if(jg -> T[l][c] == JOGADOR2)
			{
				int check_right=CheckRight(jg,l,c,JOGADOR2);
				if(check_right>10 && check_right<89){
					moves[moves_count]=check_right;
					moves_count++;
				}		
				int check_left=CheckLeft(jg,l,c,JOGADOR2);
				if(check_left>10 && check_left<89){
					moves[moves_count]=check_left;
					moves_count++;
				}
				int check_up=CheckUp(jg,l,c,JOGADOR2);
				if(check_up>10 && check_up<89){
					moves[moves_count]=check_up;
					moves_count++;
				}
				int check_down=CheckDown(jg,l,c,JOGADOR2);
				if(check_down>10 && check_down<89){
					moves[moves_count]=check_down;
					moves_count++;
				}		
				int check_upright=CheckUpRight(jg,l,c,JOGADOR2);
				if(check_upright>10 && check_upright<89){
					moves[moves_count]=check_upright;
					moves_count++;
				}
				int check_upleft=CheckUpLeft(jg,l,c,JOGADOR2);
				if(check_upleft>10 && check_upleft<89){
					moves[moves_count]=check_upleft;
					moves_count++;
				}				
				int check_downright=CheckDownRight(jg,l,c,JOGADOR2);
				if(check_downright>10 && check_downright<89){
					moves[moves_count]=check_downright;
					moves_count++;
				}				
				int check_downleft=CheckDownLeft(jg,l,c,JOGADOR2);
				if(check_downleft>10 && check_downleft<89){
					moves[moves_count]=check_downleft;
					moves_count++;
				}
			}
		}
	}
	int i=0;
	while(moves[i]!=0)
	{
		i++;
	}
	i--;
	srand(time(NULL));
	if(i>0){i=rand()%i;}
	return moves[i];	
}

