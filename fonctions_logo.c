#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "fonctions_logo.h"
#include "logo_type.h"

#define STROKECOLOR "red"


void afficher(INST* pinst, int tab, PROG root) {


   if (pinst != NULL) { //condition d'arrêt, NULL si on est au bout du programme

      int i;
      for (i = 0; i<tab; i++) { //OPTIONNEL POUR UN AFFICHAGE INDENTÉ
         printf("    ");
      }

      switch (pinst->type) {

         case REPEAT :  printf("REPEAT %d [\n", pinst->param);
                        afficher(pinst->prog, tab + 1, root); //appel récursif du programme associé

                        for (i = 0; i<tab; i++) { //OPTIONNEL POUR UN AFFICHAGE INDENTÉ
                           printf("    ");
                        }

                        printf("]\n");
                        break;

         case FORWARD : printf("FORWARD %d\n", pinst->param);
                        break;

         case LEFT :    printf("LEFT %d\n", pinst->param);
                        break;

         case RIGHT :   printf("RIGHT %d\n", pinst->param);
                        break;

         case MOVE :    printf("MOVE %d\n", pinst->param);
                        break;

         case SAVE :    printf("SAVE %d [\n", pinst->param);
                        afficher(pinst->prog, tab + 1, root);

                        for (i = 0; i<tab; i++) { //OPTIONNEL POUR UN AFFICHAGE INDENTÉ
                           printf("    ");
                        }

                        printf("]\n");
                        break;

         case RECALL :  printf("RECALL %d\n", pinst->param);
                        break;

         case CIRCLE :  printf("CIRCLE %d\n", pinst->param);
                        break;


         default :      printf("Erreur de syntaxe\n");
                        exit(0);
      }
      afficher(pinst->suivant, tab, root); //appel recursif de l'instruction suivante du programme
   }
}

INST* creerInstruction(int type, int param, PROG prog) {

   INST* pinst = (INST*) malloc(sizeof(INST));

   pinst->type = type;
   pinst->param = param;
   pinst->prog = prog;
   pinst->suivant = NULL;

   return pinst;
}

INST* ajouterInstruction(PROG prog, INST* pinst) {
   pinst->suivant = prog; //ATTENTION ca veut dire que les règles de grammaires doivent
   return pinst;          //prendre en compte que programme := instruction programme
}

int strToInt(char* input) { //deux anagrammes auront le même ID. à prendre en compte, cependant, je considère ce problème négligeable

   int s = 0, i;

	for (i = 0; input[i] != '\0'; i++) {
		s += input[i];
	}

	return s;
}

PROG lookup( PROG root, int id) {
	PROG tmp = root;

	if (tmp == NULL) {
		fprintf(stderr, "Can't find requested memory\n");
		exit(1);
	}

	while (tmp->type != SAVE || tmp->param != id) {
		tmp = tmp->suivant;
		if (tmp == NULL) { //signifie que l'on est arrivé à la fin du programme sans trouver de match
			fprintf(stderr, "Can't find requested memory\n");
			exit(1);
		}
	}
	return tmp->prog;
}

void supprimerProgramme(PROG prog) {
   if (prog->suivant != NULL) {
      supprimerProgramme(prog->suivant);
   }
   if (prog->type == REPEAT || prog->type == SAVE) {
      supprimerProgramme(prog->prog);
   }
   free (prog);
}

FLECHE* initFleche(int x, int y, int angle) {
   FLECHE* fleche = (FLECHE*) malloc(sizeof(FLECHE));
   fleche->x = x;
   fleche->y = y;
   fleche->angle = angle;
   return fleche;
}

void instructionsSVG(PROG prog, FLECHE* pfleche, FILE* stream,PROG root) {
   if (prog != NULL) {
      float newX, newY;
      int i;
      switch (prog->type) { // on écrit le SVG correspondant aux différents types d'instructions

         case FORWARD : fprintf(stream, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke = \"%s\" />\n", pfleche->x, pfleche->y, newX = pfleche->x + prog->param * cos(pfleche->angle), newY = pfleche->y + prog->param * sin(pfleche->angle), STROKECOLOR );
                        pfleche->x = newX;
                        pfleche->y = newY;
                        break;

         case CIRCLE :  fprintf(stream, "<circle cx=\"%lf\" cy=\"%lf\" r=\"%d\" fill=\"none\" stroke=\"%s\"/>\n", pfleche->x, pfleche->y, prog->param, STROKECOLOR);
                        break;

         case LEFT : pfleche->angle = (pfleche->angle - prog->param * M_PI / 180.0f);
                     break;

         case RIGHT : pfleche->angle = (pfleche->angle + prog->param * M_PI / 180.0f  );
                     break;

         case REPEAT :  i = 0;
                        while (i<prog->param) {
                           instructionsSVG(prog->prog, pfleche, stream,root);
                           i++;
                        }
                        break;

         case MOVE :	   pfleche->x += prog->param * cos(pfleche->angle);
			               pfleche->y += prog->param * sin(pfleche->angle);
                        break;

         case SAVE :    break; // on ne souhaite rien écrire dans le fichier SVG dans le cas d'une mise en mémoire d'un sous-programme

         case RECALL : instructionsSVG(lookup(root, prog->param), pfleche, stream, root) ; //ici on imprime le sous programme en mémoire correspondant.
                        break;

      }

      instructionsSVG(prog->suivant, pfleche, stream, root); //appel récursif de l'instruction suivante
   }
}

void ecrireSVG(PROG prog, FLECHE* pfleche, FILE* stream, char* title, char* desc, int width, int height) {

   //écriture du header
   fprintf(stream, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
   fprintf(stream, "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"%d\" height=\"%d\">\n", width, height);
   fprintf(stream, "<title>%s</title>\n", title );
   fprintf(stream, "<desc>%s</desc>\n", desc );

   //écriture du dessin en tant que tel
   instructionsSVG(prog,pfleche,stream,prog);

   //fermeture de la balise SVG
   fprintf(stream, "</svg>\n");
}
