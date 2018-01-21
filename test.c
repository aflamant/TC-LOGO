#include <stdio.h>
#include <stdlib.h>

#include "fonctions_logo.h"
#include "logo_type.h"

int main(int argc, char const *argv[]) {

   //test d'ajout d'une instruction
   PROG testProg = NULL;
   testProg = ajouterInstruction(testProg, creerInstruction(FORWARD, 100, NULL));

   //test de création de boucles imbriquées
   PROG rep1 = NULL;
   rep1 = ajouterInstruction(rep1, creerInstruction(LEFT, 90, NULL));
   rep1 = ajouterInstruction(rep1, creerInstruction(FORWARD, 50, NULL));

   PROG rep2 = NULL;
   rep2 = ajouterInstruction(rep2, creerInstruction(FORWARD,100, NULL));
   rep2 = ajouterInstruction(rep2, creerInstruction(RIGHT, 90, NULL));

   rep1 = ajouterInstruction(rep1, creerInstruction(REPEAT, 2, rep2));

   testProg = ajouterInstruction(testProg, creerInstruction(REPEAT, 4, rep1));
   testProg = ajouterInstruction(testProg, creerInstruction(FORWARD, 100, NULL));

   afficher(testProg,0);

   supprimerProgramme(testProg);

   return 0;
}
