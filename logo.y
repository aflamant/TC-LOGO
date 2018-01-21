/*--------------------------------------------------------
                  DEFINITIONS
--------------------------------------------------------*/
%{
#include <stdio.h>
#include <stdlib.h>
#include "logo_type.h"
#include "fonctions_logo.h"

int yywrap(){
  return 1;
}

int yyerror()
{
  printf("\n erreur !\n");
  exit(1);
}

PROG p1 = NULL;

%}


// symbole terminaux
%token   ENTIER TK_FORWARD TK_MOVE TK_SAVE TK_RECALL TK_LEFT TK_RIGHT TK_REPEAT TK_BEGIN TK_END NAME TK_CIRCLE

//type de yylval
%union {
    INST* prog;
    int val;
    char* strval;
};

//type des  symboles
%type  <val> ENTIER
%type <prog> programme instruction
%type <strval> NAME

%%
/*--------------------------------------------------------
                  GRAMMAIRE ANNOTEE
--------------------------------------------------------*/
update: programme {
   p1=$1;
}

instruction: TK_FORWARD ENTIER {
$$=creerInstruction(FORWARD,$2, NULL);}
| TK_MOVE ENTIER {
$$=creerInstruction(MOVE,$2,NULL);}
| TK_REPEAT ENTIER TK_BEGIN programme TK_END{
$$=creerInstruction(REPEAT,$2, $4);}
| TK_RIGHT ENTIER{
$$=creerInstruction(RIGHT,$2, NULL);}
| TK_LEFT ENTIER{
$$=creerInstruction(LEFT,$2, NULL);}
| TK_SAVE NAME TK_BEGIN programme TK_END {
$$=creerInstruction(SAVE, strToInt($2) , $4);
free($2);}
| NAME {
$$=creerInstruction(RECALL,strToInt($1),NULL);
free($1);}
| TK_CIRCLE ENTIER {
$$=creerInstruction(CIRCLE,$2,NULL);}

programme: instruction programme {
   $$ = ajouterInstruction($2,$1);}
| instruction {
   $$ = $1;}


%%

/*--------------------------------------------------------
                  FONCTIONS MAIN
--------------------------------------------------------*/
main() {
   //lecture de l'entrée standard
   yyparse();

   //affichage intermédiaire dans le terminal
   afficher(p1,0,p1);

   //déclaration et initialisation de la flêche de dessin
   FLECHE* pfleche = initFleche(100,100,0);

   //ouverture du fichier de sortie
   FILE* f;
   if ((f = fopen("output","w+")) ==  NULL) {
      fprintf(stderr, "Impossible d'ouvrir le fichier en écriture\n");
      exit(1);
   }

   //ecriture du SVG
   ecrireSVG(p1,pfleche,f,"Exemple LOGO", "Du LOGO.",500,500);
   system("eog output &");

   //libération de la mémoire
   fclose(f);
   supprimerProgramme(p1);
   free(pfleche);
}
