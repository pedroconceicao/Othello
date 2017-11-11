/**
*
@file myf.h
*
@brief Breve Descrição
*
* Descrição mais detalhada do ficheiro que até poderiam incluir links para imagens
etc.
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

#define VAZIO ' '
#define JOGADOR1 'O'
#define JOGADOR2 'X'
typedef char celula;
typedef struct {
        celula T[8][8];  // Array bidimensional [8][8] com o estado das células
        int vez;         // inteiro que designa quem é a vez do próximo a jogar (1-jogador1, 2-jogador2)
        int terminado;   // inteiro que indica se o jogo está terminado (1 se sim , 0 se não )
        } othello;

#include "prototypes.h"
