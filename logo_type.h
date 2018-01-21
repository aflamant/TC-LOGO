/**
* \file     logo_type.h
* \author   Antoine Flamant
* \date     13 janvier 2018
* \brief    Définit les structures et les types nécéssaires au TP.
*/

#ifndef _LOGO_TYPE
#define _LOGO_TYPE

#define FORWARD 1
#define RIGHT 2
#define LEFT 3
#define MOVE 4
#define REPEAT 0
#define SAVE 5
#define RECALL 6
#define CIRCLE 7

typedef struct inst {
   struct inst* suivant;
   int param;
   int type;
   struct inst* prog;
} INST;

typedef struct fleche {
   double x;
   double y;
   double angle;
} FLECHE;

typedef INST* PROG;

#endif
