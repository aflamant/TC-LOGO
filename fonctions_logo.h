/**
* \file     fonctions_logo.h
* \author   Antoine Flamant
* \date     13 janvier 2018
* \brief    Définit les fonctions utilisées par le programme.
*/

#ifndef _FONCTIONS_LOGO
#define _FONCTIONS_LOGO

#include "logo_type.h"

/**
* \brief    Affiche la structure du programme passé en paramètre dans la sortie standard.
* \param    prog     Le programme à afficher.
* \param    tab      Le niveau d'indentation souhaité (utilisé dans les appels récursifs afin d'indenter le programme).
* \param    root     La racine du programme (utilisé dans les appels récursifs pour pouvoir parcourir le programme depuis le début).
*/
void afficher(PROG prog,int tab,PROG root);

/**
* \brief    Crée un noeud pour y stocker une instruction.
* \param    type     Le type de l'instruction (entiers définis dans logo_type.h).
* \param    param    Le paramètre de l'instruction.
* \param    prog     L'éventuel programme de l'instruction, dans le cas de REPEAT ou SAVE.
* \return   Le pointeur vers l'instruction créée.
*/
INST* creerInstruction(int type, int param, PROG prog);

/**
* \brief    Ajoute une instruction à la suite d'un programme.
* \param    prog     Le programme à la suite duquel on ajoute l'instruction.
* \param    pinst    Un pointeur vers l'instruction à ajouter.
* \return   Le programme mis à jour.
*/
INST* ajouterInstruction(PROG prog, INST* pinst);

/**
* \brief    Libère la mémoire allouée à un programme.
* \param    prog     Le programme à supprimer.
*/
void supprimerProgramme(PROG prog);

/**
* \brief    Change un paramètre string en int utilisable comme paramètre d'une instruction.
* \brief    input    La chaîne de caractère à changer.
* \return   L'entier correspondant.
*/
int strToInt(char* input) ;

/**
* \brief    Cherche dans le programme un sous-programme enregistré auparavant.
* \param    root     La racine du programme dans lequel on cherche le sous-programme.
* \param    id       L'identifiant du sous-programme recherché.
* \return   Le programme correspondant s'il existe.
*/
PROG lookup( PROG root, int id);

/**
* \brief    Écrit un fichier svg depuis un programme TC-LOGO passé en paramètre.
* \param    prog     Le programme à écrire.
* \param    pfleche  Un pointeur vers la flêche à utiliser pour la position dans le dessin.
* \param    stream   Le flux de sortie dans lequel écrire le svg.
* \param    root     La racine du programme (utilisé dans les appels récursifs).
*/
void instructionsSVG(PROG prog, FLECHE* pfleche, FILE* stream, PROG root);

/**
* \brief    Fait appel à la fonction instructionsSVG en ajoutant les balises nécessaires au début et à la fin du fichier.
* \param    prog     Le programme à écrire.
* \param    pfleche  Un pointeur vers la flêche à utiliser pour la position dans le dessin.
* \param    stream   Le flux de sortie dans lequel écrire le svg.
* \param    title    Le titre du dessin svg.
* \param    desc     La description du dessin svg.
* \param    width    La largeur de la fenêtre de dessin.
* \param    height   La hauteur de la fenêtre de dessin.
*/
void ecrireSVG(PROG prog, FLECHE* pfleche, FILE* stream, char* title, char* desc, int width, int height);

/**
* \brief    Déclare un fleche de dessin et initialise ses coordonnées.
* \param    x        La coordonnée horizontale à laquelle initialiser la flêche.
* \param    y        La coordonnée verticale à laquelle initialiser la flêche.
* \param    angle    L'angle auquel initialiser la flêche.
*/
FLECHE* initFleche(int x, int y, int angle);

#endif
