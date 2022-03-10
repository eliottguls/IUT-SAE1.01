/**
    \brief Jeu du Yams

    \author Eliott GUILLOSSOU H2

    \date 21/11/2021

    Le Yams se joue avec 5 dés et se finit une fois toutes les cases de la feuille de marque
    remplies (il y a 13 combinaisons à réaliser). Les joueurs jouent à tour de rôle et chaque
    joueur dispose de 3 lancers à chaque coup. Le joueur a le choix de reprendre tous ou
    une partie des dés à chaque lancer, selon son gré, pour tenter d’obtenir la combinaison
    voulue. À chaque tour, le joueur doit obligatoirement inscrire son score dans une des
    ca ses de la feuille de marque que ce soit par les points qu’il a obtenus ou par un 0. Il
    peut en effet arriver lors d’un tour que le résultat ne convienne pas au joueur et qu’il se
    dise qu’il pourrait faire un plus grand score sur un autre tour. Il peut alors choisir de
    barrer une autre case à la place. Bien entendu, il ne pourra plus faire cette combinaison
    par la suite. Les cases vides sont définies par la présence de 61 dans celle-ci
    Le gagnant d’une partie de Yams est le joueur qui comptabilise le plus de points à la fin
    des 13 coups. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

/** \def Definition de la longueur pour les 2 tableaux de la feuille de marque*/
#define MAX_TAB_SCORES 14

/** \def Definition de la longueur maximale pour les noms des joueurs */
#define MAX_CAR_NOM 13

/** \def Nombre de dés qui seront stockés dans un tableau */
#define NB_DES 5

/** \def score du full */
#define FULL_HOUSE 25

/**
 * @def score du yams
 * 
 */
#define YAMS 50

/**
 * @def score de la grande suite
 * 
 */
#define GRANDE_SUITE 40

/**
 * @def score de la petite suite
 * 
 */
#define PETITE_SUITE 30

/**
 * \def NB_TOUR
 * 
 * \brief constante pour le nombre de tour + 1
 */
const int NB_TOUR = 26;

/**
 * \def NB_TOUR_JOUEUR
 * 
 * \brief constante pour le nombre de lancers que dispose chaque joueur + 1
 * 
 */
const int NB_LANCER_JOUEUR = 4;


/**
 * @def score à atteindre pour avoir droit au bonus
 * 
 */
const int BONUS_LIM = 62;


/**
 * @def score du bonus
 * 
 */
const int BONUS_POINTS = 35;

/**
 * @def definition de tableaux pour les dés et la feuille de marque

 * 
 */
int scores_1st_part[MAX_TAB_SCORES];
/**  Contenu de chaque éléments et son indice :
    tot_1_j1, tot_1_j2 || scores_1st_part[0,1]
    tot_2_j1, tot_2_j2 || scores_1st_part[2,3]
    tot_3_j1, tot_3_j2 || scores_1st_part[4,5]
    tot_4_j1, tot_4_j2 || scores_1st_part[6,7]
    tot_5_j1, tot_5_j2 || scores_1st_part[8,9]
    tot_6_j1, tot_6_j2 || scores_1st_part[10,11]
    bonus_j1, bonus_j2 || scores_1st_part[12,13]
*/

  
/**
 * @def  définition de tableaux pour les dés et la feuille de marque

 * 
 */
int scores_2nd_part[MAX_TAB_SCORES];
/** Contenu de chaque éléments et son indice :
    brelan_j1, brelan_j2             || scores_2nd_part[0,1]
    carre_j1, carre_j2               || scores_2nd_part[2,3]
    full_house_j1, full_house_j2     || scores_2nd_part[4,5]
    petite_suite_j1, petite_suite_j2 || scores_2nd_part[6,7]
    grande_suite_j1, grande_suite_j2 || scores_2nd_part[8,9]
    yams_j1, yams_j2                 || scores_2nd_part[10,11]
    chance_j1, chance_j2             || scores_2nd_part[12,13]
*/

/**
 * @def definition du tableau de dés
 * 
 */
int des[NB_DES];

/**
 * @def variables pour param de lancerDes
 * 
 */
int lance_verif, valid_lancer;


/**
 * @def Définition des tailles de j1, et j2 pour feuille de marque 
 * 
 */
char j1[MAX_CAR_NOM], j2[MAX_CAR_NOM];


/**
 * @def def des variables pour feuille de marque
 * 
 */
int tot_sup_j1, tot_sup_j2,
    tot_inf_j1, tot_inf_j2,
    tot_score_j1, tot_score_j2;


/**
 * @def def des variables besoins pour compter tour et donc savoir à quel joueur affecter les valeurs 
 * 
 */
int tour, tour_jeu;


/**
 *  \brief Fonction qui permet d'afficher une feuille de marque où toutes les cases sont vides
 *
 *  \param ind_max correspond a la longueur des tableaux "scores_1st_part" et "scores_2nd_part"
 *
 *  \return Remplis les tableaux cités de -1
*/
void remplirTab(int ind_max){
    int i;
    for (i=0;i<ind_max;i++){// ind_max pour parcourir les tableau en jusqu'au dernier éléments
        scores_1st_part[i]=-1;
        scores_2nd_part[i]=-1;
    }
}




/**
 * \brief Fonction qui vérifie que le joueur lance bien les dés
 * 
 * \param Variable que l'on a demandé au joueur de remplir
 * 
 * \return Tant que le joueur ne dis pas qu'il veut lancer lse dés on lui redemande de lancer les dés
 */
void propLancer(int lance_verif){ 
  while (lance_verif!=0){ // tant qu'il ne veut pas lancer ses dés on lui redemande de les lancer
    printf("|0 : oui           |                       |\n");
    printf("|");
    scanf("%1d", &lance_verif);

  }
}


/**
 * \brief  Affiche la feuille de marque
 * 
 * \param j1,j2 :  
 *        tot_ sup_j1, tot_sup_j2 : 
 *        tot_inf_j1, tot_inf_j2 : 
 *        tot_score_j1, tot_score_j2 : 
 *        scores_1st_part, scores_2nd_part : 
 */

 /**
  * @brief Permet en un appel de procédures d'afficher notre feuille de marque évolutives
  * 
  * @param j1 : affiche nom du joueur personalisé
  * @param j2 : affiche nom du joueur personalisé
  * @param tot_sup_j1 : variable qui nous servirons pour calculer le score total
  * @param tot_sup_j2 : variable qui nous servirons pour calculer le score total
  * @param tot_inf_j1 : variable qui nous servirons pour calculer le score total
  * @param tot_inf_j2 : variable qui nous servirons pour calculer le score total
  * @param tot_score_j1 : variable pour stocker score totaux
  * @param tot_score_j2 : variable pour stocker score totaux
  * @param scores_1st_part : tableau pour pouvoir afficher les valeurs qui changeront au fur et mesure de la partie
  * @param scores_2nd_part : tableau pour pouvoir afficher les valeurs qui changeront au fur et mesure de la partie
  */
void afficheTableau(char *j1, char *j2, int tot_sup_j1, int tot_sup_j2, int tot_inf_j1, int tot_inf_j2, int tot_score_j1, int tot_score_j2, int scores_1st_part[], int scores_2nd_part[]){

    printf("Feuille de marque :\n");
    printf("                  +-------+\n");
    printf("+-----------------| J1| J2|     J1 : %s  J2 : %s  \n", j1, j2);
    printf("|        1        |%3d|%3d|\n", scores_1st_part[0], scores_1st_part[1]);
    printf("|        2        |%3d|%3d|\n", scores_1st_part[2], scores_2nd_part[3]);
    printf("|        3        |%3d|%3d|\n", scores_1st_part[4], scores_1st_part[5]);
    printf("|        4        |%3d|%3d|\n", scores_1st_part[6], scores_1st_part[7]);
    printf("|        5        |%3d|%3d|\n", scores_1st_part[8], scores_1st_part[9]);
    printf("|        6        |%3d|%3d|\n", scores_1st_part[10], scores_1st_part[11]);
    printf("|Bonus si sup  62 |%3d|%3d|\n", scores_1st_part[12], scores_1st_part[13]);
    printf("|Tot Superieur    |%3d|%3d|\n", tot_sup_j1, tot_sup_j2);
    printf("+-----------------+-------+     0  signifie que la case est occupé(remplie) et vaut 0 points \n");
    printf("+-----------------+-------+     -1 signifie que la case est vide\n");
    printf("|Brelan           |%3d|%3d|\n", scores_2nd_part[0], scores_2nd_part[1]);
    printf("|Carre            |%3d|%3d|\n", scores_2nd_part[2], scores_2nd_part[3]);
    printf("|Full House       |%3d|%3d|\n", scores_2nd_part[4], scores_2nd_part[5]);
    printf("|Petite Suite     |%3d|%3d|\n", scores_2nd_part[6], scores_2nd_part[7]);
    printf("|Grande Suite     |%3d|%3d|\n", scores_2nd_part[8], scores_2nd_part[9]);
    printf("|Yams             |%3d|%3d|\n", scores_2nd_part[10], scores_2nd_part[11]);
    printf("|Chance           |%3d|%3d|\n", scores_2nd_part[12], scores_2nd_part[13]);
    printf("|Tot inferieur    |%3d|%3d|\n", tot_inf_j1, tot_inf_j2);
    printf("+-------------------------+\n");
    printf("|Total            |%3d|%3d|\n", tot_score_j1, tot_score_j2);
    printf("+-------------------------+\n");


}

/**
 * @brief Demande prénoms
 * 
 * @param j1 : joueur 1
 * @param j2 : joueur 2
 *
 * Demande de saisir prénoms des deux joueurs pour, ensuite, commencer la partie
 */
void demandePrenom(char *j1, char *j2){
  printf("Pour commencer la partie inscrivez vos prénoms\n");
  printf("J1 :");
  scanf("%s", j1);
  printf("J2 :");
  scanf("%s", j2);
}




/**
 * \brief Fonction qui affiche les dés(de manière plus visuel) en fonction des chiffres généres par la fonction "lancerDes"
 * 
 * @param des : tableau comprenant les chiffres générés 
 */
void afficheDes(int des[]){
  int i;
  for (i=0;i<NB_DES;i++){ // boucle pour vérifier que le dés générer sont valide pour la suite
    if (des[i]<=0 && des[i]>6){
      printf("erreur type dés");
    }
  }

  for (i=0;i<NB_DES;i++){ // "NB_DES"  pour parcourir 5 toutes les valeurs générés, que l'on a utlisé pour définir des[]
    if (des[i]==1){
      printf("\n");
      printf("+-------------+\n");
      printf("|             |\n");
      printf("|             |\n");
      printf("|      O      |     Indice %d\n",i);
      printf("|             |\n");
      printf("|             |\n");
      printf("+-------------+\n");
    }
    else if (des[i]==2){
      printf("\n");
      printf("+-------------+\n");
      printf("|           O |\n");
      printf("|             |\n");
      printf("|             |     Indice %d\n",i);
      printf("|             |\n");
      printf("| O           |\n");
      printf("+-------------+\n");
    }
    else if (des[i]==3){
      printf("\n");
      printf("+-------------+\n");
      printf("|           O |\n");
      printf("|             |\n");
      printf("|      O      |     Indice %d\n", i);
      printf("|             |\n");
      printf("| O           |\n");
      printf("+-------------+\n");  

    }
    else if (des[i]==4){
      printf("\n");
      printf("+-------------+\n");
      printf("| O         O |\n");
      printf("|             |\n");
      printf("|             |     Indice %d\n",i);
      printf("|             |\n");
      printf("| O         O |\n");
      printf("+-------------+\n");
    }
    else if (des[i]==5){
      printf("\n");
      printf("+-------------+\n");
      printf("| O         O |\n");
      printf("|             |\n");
      printf("|      O      |     Indice %d\n",i);
      printf("|             |\n");
      printf("| O         O |\n");
      printf("+-------------+\n");
    }
    else{
      printf("\n");
      printf("+-------------+\n");
      printf("| O         O |\n");
      printf("|             |\n");
      printf("| O         O |     Indice %d\n",i);
      printf("|             |\n");
      printf("| O         O |\n");
      printf("+-------------+\n");
    }
  }
  printf("\n");
}










/**
 * @brief demande au joueur quel dés il garde(en retenant l'indice du dés)
 * 
 * @param des : tableau de dés
 */
void choix_score(int des[]){
  char choix_case[13];
  int i;
  int iok=0;//besoin dans le petite_suite
  int cpt_6_j1=0,cpt_6_j2=0 ,cpt_5_j1=0, cpt_5_j2=0, cpt_4_j1=0, cpt_4_j2=0, cpt_3_j1=0,  cpt_3_j2=0,  cpt_2_j1=0, cpt_2_j2=0, cpt_1_j1=0, cpt_1_j2=0; // def des variables pour affectation de scores dans la feuille de marque

  printf("| Choisissez quel case vous souhaitez remplir :");
  scanf("%s", choix_case);
  while ( strcmp(choix_case,"1")!=0 &&  strcmp(choix_case,"2")!=0 && strcmp(choix_case,"3")!=0 && strcmp(choix_case,"4")!=0 && strcmp(choix_case,"5")!=0 && strcmp(choix_case,"6")!=0 && strcmp(choix_case,"Brelan")!=0 &&  strcmp(choix_case,"Carre")!=0 && strcmp(choix_case,"Full_House")!=0 && strcmp(choix_case,"Petite_Suite")!=0 && strcmp(choix_case,"Grande_Suite")!=0 && strcmp(choix_case,"Yams")!=0 && strcmp(choix_case,"Chance")!=0){
    printf("Respectez l'orthographe de la feuille de marque s'il vous plaît en remplacant les espaces par des '_'\n");
    scanf("%s", choix_case);
  }

/**************************************************************************
************************* TOTAL DE 1 **************************************
**************************************************************************/
  if (strcmp(choix_case,"1")==0 && (scores_1st_part[0]== -1 ||scores_1st_part[1]==-1)){ // vérif que si il saisit 1 et que soit la case 2 de j1 est vide soit celle de j2 
    for (i=0;i<NB_DES;i++){ //on parcourt le tableau des[]
      if (des[i]==1){ // on vérifie que des[i]=1
        if (tour_jeu%2==0){//verif pour affecter la val au bon joueur(ici j1)(ici j1)
          if (cpt_1_j1==0){ // si c'est la première fois que l'on ajoute
            scores_1st_part[0]=scores_1st_part[0]+2; // +2 pour compenser le -1
          }
          else{
            scores_1st_part[0]=scores_1st_part[0]+1; // +1 car on a déjà compenser le 1 à la premiere occurence
          }
          cpt_1_j1++; // on incrémente pour que ce ne soit que la première fois que l'on ajoute +2
        }
        else{
          if (cpt_1_j2==0){ // ici j2
            scores_1st_part[1]=scores_1st_part[1]+2; // +2 pour compenser le -1
          }
          else{
            scores_1st_part[1]=scores_1st_part[1]+1; // +1 car on a déjà compenser le -1 à la premiere occurence
          }
          cpt_1_j2++; // on incrémente pour que ce ne soit que la première fois que l'on ajoute +2
        }
      }
    }
    if (cpt_1_j1==0){// si il n'y a aucun 1 dans les dés mais qu'il choisit quand même cette combinaison on affiche 0 dans la feuille de marque de J1
      scores_1st_part[0]=0;
    }
    else if (cpt_1_j2==0){//si il n'y a aucun 1 dans les dés mais qu'il choisit quand même cette combinaison on affiche 0 dans la feuille de marque de J1
      scores_1st_part[1]=0;
    }
  }
  else if(scores_1st_part[0]!=-1 || scores_1st_part[1]!=-1){
    printf("Case déja remplie ou combinaison impossible avec vos dés donc remplissage par un 0\n");
    if ((scores_1st_part[0]>=0) || (scores_1st_part[1]>=0)){
      printf(" dans ce cas : Case déja remplie");
      scanf("%s", choix_case);
      choix_score(des);
    }
  }
/**************************************************************************
************************* TOTAL DE 2 **************************************
**************************************************************************/
  else if (strcmp(choix_case,"2")==0 && (scores_1st_part[2]== -1 ||scores_1st_part[3]==-1)){ // vérif que si il saisit 2 et que soit la case 2 de j1 est vide soit celle de j2 
    for (i=0;i<NB_DES;i++){ //on parcourt le tableau des[]
      if (des[i]==2){ // on vérifie que des[i]=2
        if (tour_jeu%2==0){//verif pour affecter la val au bon joueur(ici j1)(ici j1)
          if (cpt_2_j1==0){
            scores_1st_part[6]=scores_1st_part[2]+3; // +6 pour compenser le -1
          }
          else{
            scores_1st_part[6]=scores_1st_part[2]+2; // +5 car on a déjà compenser le 1 à la premiere occurence
          }
          cpt_2_j1++;
        }
        else{
          if (cpt_2_j2==0){
            scores_1st_part[2]=scores_1st_part[3]+6; // +6 pour compenser le -1
          }
          else{
            scores_1st_part[3]=scores_1st_part[3]+5; // +5 car on a déjà compenser le -1 à la premiere occurence
          }
          cpt_2_j2++;
        }
      }
    }
    if (cpt_2_j1==0){// si il n'y a aucun 6 dans les dés mais qu'il choisit quand même cette combinaison on affiche 0 dans la feuille de marque de J1
      scores_1st_part[2]=0;
    }
    else if (cpt_2_j2==0){//si il n'y a aucun 6 dans les dés mais qu'il choisit quand même cette combinaison on affiche 0 dans la feuille de marque de J1
      scores_1st_part[3]=0;
    }
  }
  else if(scores_1st_part[2]!=-1 || scores_1st_part[3]!=-1){ // si c'est différent de -1
    if ((scores_1st_part[2]>=0) || (scores_1st_part[3]>=0)){
      printf(" dans ce cas : Case déja remplie");
      scanf("%s", choix_case);
      choix_score(des);
    }
  }
/**************************************************************************
************************* TOTAL DE 3 **************************************
**************************************************************************/ 
  else if (strcmp(choix_case,"3")==0 && (scores_1st_part[4]== -1 ||scores_1st_part[5]==-1)){ // vérif que si il saisit 2 et que soit la case 2 de j1 est vide soit celle de j2 
    for (i=0;i<NB_DES;i++){ //on parcourt le tableau des[]
      if (des[i]==3){ // on vérifie que des[i]=3
        if (tour_jeu%2==0){//verif pour affecter la val au bon joueur(ici j1)(ici j1)
          if (cpt_3_j1==0){
            scores_1st_part[4]=scores_1st_part[4]+4; // +4 pour compenser le -1
          }
          else{
            scores_1st_part[4]=scores_1st_part[4]+3; // +3 car on a déjà compenser le 1 à la premiere occurence
          }
          cpt_3_j1++;
        }
        else{
          if (cpt_3_j2==0){
            scores_1st_part[5]=scores_1st_part[5]+4; // +4 pour compenser le -1
          }
          else{
            scores_1st_part[5]=scores_1st_part[5]+3; // +3 car on a déjà compenser le -1 à la premiere occurence
          }
          cpt_3_j2++;
        }
      }
    }
    if (cpt_3_j1==0){// si il n'y a aucun 6 dans les dés mais qu'il choisit quand même cette combinaison on affiche 0 dans la feuille de marque de J1
      scores_1st_part[4]=0;
    }
    else if (cpt_3_j2==0){//si il n'y a aucun 6 dans les dés mais qu'il choisit quand même cette combinaison on affiche 0 dans la feuille de marque de J1
      scores_1st_part[5]=0;
    }
  }
  else if(scores_1st_part[4]!=-1 || scores_1st_part[5]!=-1){
    if ((scores_1st_part[4]>=0) || (scores_1st_part[5]>=0)){
      printf(" dans ce cas : Case déja remplie");
      scanf("%s", choix_case);
      choix_score(des);
    }
  }
/**************************************************************************
************************* TOTAL DE 4 **************************************
**************************************************************************/  
else if (strcmp(choix_case,"4")==0 && (scores_1st_part[6]== -1 ||scores_1st_part[7]==-1)){ // vérif que si il saisit 2 et que soit la case 2 de j1 est vide soit celle de j2 
    for (i=0;i<NB_DES;i++){ //on parcourt le tableau des[]
      if (des[i]==4){  // on vérifie que des[i]=4
        if (tour_jeu%2==0){//verif pour affecter la val au bon joueur(ici j1)(ici j1)
          if (cpt_4_j1==0){
            scores_1st_part[6]=scores_1st_part[6]+5; // +5 pour compenser le -1
          }
          else{
            scores_1st_part[6]=scores_1st_part[6]+4; // +4 car on a déjà compenser le 1 à la premiere occurence
          }
          cpt_4_j1++;
        }
        else{
          if (cpt_4_j2==0){
            scores_1st_part[7]=scores_1st_part[7]+5; // +5 pour compenser le -1
          }
          else{
            scores_1st_part[7]=scores_1st_part[7]+4; // +4 car on a déjà compenser le -1 à la premiere occurence
          }
          cpt_4_j2++;
        }
      }
    }
    if (cpt_4_j1==0){// si il n'y a aucun 6 dans les dés mais qu'il choisit quand même cette combinaison on affiche 0 dans la feuille de marque de J1
      scores_1st_part[6]=0;
    }
    else if (cpt_4_j2==0){//si il n'y a aucun 6 dans les dés mais qu'il choisit quand même cette combinaison on affiche 0 dans la feuille de marque de J1
      scores_1st_part[7]=0;
    }
    
  }
  

  else if(scores_1st_part[6]!=-1 || scores_1st_part[7]!=-1){
    if ((scores_1st_part[6]>=0) || (scores_1st_part[7]>=0)){
      printf(" dans ce cas : Case déja remplie");
      scanf("%s", choix_case);
      choix_score(des);
    }
  }
/**************************************************************************
************************* TOTAL DE 5 **************************************
**************************************************************************/
  else if (strcmp(choix_case,"5")==0 && (scores_1st_part[9]== -1 ||scores_1st_part[10]==-1)){ // vérif que si il saisit 2 et que soit la case 2 de j1 est vide soit celle de j2 
    for (i=0;i<NB_DES;i++){ //on parcourt le tableau des[]
      if (des[i]==5){ // on vérifie que des[i]=5
        if (tour_jeu%2==0){//verif pour affecter la val au bon joueur(ici j1)(ici j1)
          if (cpt_5_j1==0){
            scores_1st_part[8]=scores_1st_part[8]+6; // +6 pour compenser le -1
          }
          else{
            scores_1st_part[8]=scores_1st_part[8]+5; // +5 car on a déjà compenser le 1 à la premiere occurence
          }
          cpt_5_j1++;
        }
        else{
          if (cpt_5_j2==0){
            scores_1st_part[9]=scores_1st_part[9]+6; // +6 pour compenser le -1
          }
          else{
            scores_1st_part[9]=scores_1st_part[9]+5; // +5 car on a déjà compenser le -1 à la premiere occurence
          }
          cpt_5_j2++;
        }
      }
    }
    if (cpt_5_j1==0 && tour_jeu%2==0){// si il n'y a aucun 6 dans les dés mais qu'il choisit quand même cette combinaison on affiche 0 dans la feuille de marque de J1
      scores_1st_part[8]=0;
    }
    else if (cpt_5_j2==0 && tour_jeu%2==1){//si il n'y a aucun 6 dans les dés mais qu'il choisit quand même cette combinaison on affiche 0 dans la feuille de marque de J1
      scores_1st_part[9]=0;
    }

  }
  else if(scores_1st_part[8]!=-1 || scores_1st_part[9]!=-1){
    if ((scores_1st_part[8]>=0) || ((scores_1st_part[9]>=0))){
      printf(" dans ce cas : Case déja remplie");
      scanf("%s", choix_case);
      choix_score(des);
    }
  }

/******************************************************************
************************* TOTAL DE 6 ******************************
*******************************************************************/
  else if (strcmp(choix_case,"6")==0 && (scores_1st_part[10]== -1 ||scores_1st_part[11]==-1)){ // vérif que si il saisit 2 et que soit la case 2 de j1 est vide soit celle de j2 
    for (i=0;i<NB_DES;i++){ //on parcourt le tableau des[]
      if (des[i]==6){ // on vérifie que des[i]=6
        if (tour_jeu%2==0){ //verif pour affecter la val au bon joueur(ici j1)(ici j1)
            if (cpt_6_j1==0){ // comparer pour mettre notre cellule à 0 que au premier passage
                scores_1st_part[10]=scores_1st_part[10]+7; // +7 pour le premier ajout pou compenser le -1 
            }
            else{
                scores_1st_part[10]=scores_1st_part[10]+6;
            }
            cpt_6_j1++;
        }
        else{
            if (cpt_6_j2==0){ // comparer pour mettre notre cellule à 0 que au premier passage
                scores_1st_part[11]=scores_1st_part[11]+7; // mise à zero pour ensutie ajouter les valeurs des dés
            }
            else{
                scores_1st_part[11]=scores_1st_part[11]+6;
            }
            cpt_6_j2++;
        }
      }
    }
    if (cpt_6_j1==0 && tour_jeu%2==0){// si il n'y a aucun 6 dans les dés mais qu'il choisit quand même cette combinaison on affiche 0 dans la feuille de marque de J1
      scores_1st_part[10]=0;
    }
    else if (cpt_6_j2==0 && tour_jeu%2==1){//si il n'y a aucun 6 dans les dés mais qu'il choisit quand même cette combinaison on affiche 0 dans la feuille de marque de J2
      scores_1st_part[11]=0;
    }
  }
  else if(scores_1st_part[10]!=-1 || scores_1st_part[11]!=-1){
    if (scores_1st_part[10]>=0 || scores_1st_part[11]>=0){
      printf(" dans ce cas : Case déja remplie \n");
      printf("Veuillez saisir une autre case");
      choix_score(des);
    }
  }

/*******************************************************************
***************************** BRELAN *******************************
*******************************************************************/
  else if (strcmp(choix_case,"Brelan")==0 && (scores_2nd_part[0]!= -1 ||scores_2nd_part[1]!=-1)){ // vérif que si il saisit 2 et que soit la case 2 de j1 est vide soit celle de j2 
    if (((des[0])==(des[1])==(des[2])) || ((des[1])==(des[2])==(des[3])) || ((des[2])==(des[3])==(des[4]))){
      if (tour_jeu%2==0){//verif pour affecter la val au bon joueur(ici j1)(ici j1)
      scores_2nd_part[0]=des[0]+des[1]+des[2]+des[3]+des[4];
      }
      else{
        scores_2nd_part[1]=des[0]+des[1]+des[2]+des[3]+des[4];
      }
    }
    else if (tour_jeu%2==0){
      scores_2nd_part[0]=0;// mettre 0 si la combinaison ne marche pas et que la case est vide(cf premier else if de la combinaison)
    }
    else{
      scores_2nd_part[1]=0;// mettre 0 si la combinaison ne marche pas et que la case est vide
    }
  }
  else if(scores_2nd_part[0]!=-1 || scores_2nd_part[1]!=-1){
    if (scores_2nd_part[0]>=0 || scores_2nd_part[1]>=0){ // si deja un score dedans on redemande une autre case en appellant choix_score(recursif)
      printf("Case déja remplie, veuillez saisir une autre case\n");
      choix_score(des);
    }
    else if (tour_jeu%2==0 && scores_2nd_part[0]!=0){
      scores_2nd_part[0]=0;
    }
    else if(tour_jeu%2==1 && scores_2nd_part[1]!=0){
      scores_2nd_part[1]=0;
    }
  }

/******************************************************************
************************** CARRE **********************************
*******************************************************************/
  else if (strcmp(choix_case,"Carre")==0 && (scores_2nd_part[2]!= -1 ||scores_2nd_part[3]!=-1)){ // vérif que si il saisit 2 et que soit la case 2 de j1 est vide soit celle de j2 
    if (((des[0])==(des[1])==(des[2])==(des[3])) || ((des[1])==(des[2])==(des[3])==(des[4]))){
      if (tour_jeu%2==0){//verif pour affecter la val au bon joueur(ici j1)
        scores_2nd_part[2]=des[0]+des[1]+des[2]+des[3]+des[4];
      }
      else{
        scores_2nd_part[3]=des[0]+des[1]+des[2]+des[3]+des[4];
      }
    }
    else if (tour_jeu%2==0){
      scores_2nd_part[2]=0;// mettre 0 si la combinaison ne marche pas et que la case est vide(cf premier else if de la combinaison)
    }
    else{
      scores_2nd_part[3]=0;// mettre 0 si la combinaison ne marche pas et que la case est vide
    }
  }
  else if(scores_2nd_part[2]!=-1 || scores_2nd_part[3]!=-1){
    printf("Case déja remplie ou combinaison impossible avec vos dés donc remplissage par un 0\n");
    if (scores_2nd_part[2]>=0 || scores_2nd_part[3]>=0){ // si deja un score dedans on redemande une autre case en appellant choix_score(recursif)
      printf("Case déja remplie, veuillez saisir une autre case\n");
      choix_score(des);
    }
    else if (tour_jeu%2==0 && scores_2nd_part[2]!=0){
      scores_2nd_part[2]=0;
    }
    else if(tour_jeu%2==1 && scores_2nd_part[3]!=0){
      scores_2nd_part[3]=0;
    }
  }

/************************************************************************
************************* FULL HOUSE ************************************
************************************************************************/
  else if (strcmp(choix_case,"Full_House")==0 && (scores_2nd_part[4]!= -1 ||scores_2nd_part[5]!=-1)){ // vérif que si il saisit 2 et que soit la case 2 de j1 est vide soit celle de j2 
    if ((((des[0])==(des[1])==(des[2])) && ((des[3])==(des[4]))) || ((des[0])==(des[1]) && ((des[2])==(des[3])==(des[4])))){
      if (tour_jeu%2==0){//verif pour affecter la val au bon joueur(ici j1)
      scores_2nd_part[4]=FULL_HOUSE;
      }
      else{
        scores_2nd_part[5]=FULL_HOUSE;
      }
    }
    else if (tour_jeu%2==0){
      scores_2nd_part[5]=0;// mettre 0 si la combinaison ne marche pas et que la case est vide
    }
    else{
      scores_2nd_part[6]=0;// mettre 0 si la combinaison ne marche pas et que la case est vide
    }
  }
  else if(scores_2nd_part[4]!=-1 || scores_2nd_part[5]!=-1){
    if (scores_2nd_part[4]>=0 || scores_2nd_part[5]>=0){ // si deja un score dedans on redemande une autre case en appellant choix_score(recursif)
      printf("Case déja remplie, veuillez saisir une autre case\n");
      choix_score(des);
    }
  }
  else if (tour_jeu%2==0 && scores_2nd_part[4]!=0){
    scores_2nd_part[4]=0;
  }
  else if(tour_jeu%2==1 && scores_2nd_part[5]!=0){
    scores_2nd_part[5]=0;
  }
  


/**************************************************************************
************************* PETITE SUITE ************************************
**************************************************************************/
  else if (strcmp(choix_case,"Petite_Suite")==0 && (scores_2nd_part[6]== -1 ||scores_2nd_part[7]==-1)){ // vérif que si il saisit 2 et que soit la case 2 de j1 est vide soit celle de j2 
    for (i=0;i<NB_DES;i++){ //on parcourt le tableau des[]
      if (des[i]==(des[i+1] + 1)){
        iok++;
      }
    }

    if (iok==4){
      if (tour_jeu%2==0){//verif pour affecter la val au bon joueur(ici j1)
      scores_2nd_part[6]=PETITE_SUITE;
      }
      else{
        scores_2nd_part[7]=PETITE_SUITE;
      }
    }
    else if (tour_jeu%2==0){
      scores_2nd_part[6]=0;// mettre 0 si la combinaison ne marche pas et que la case est vide
    }
    else{
      scores_2nd_part[7]=0;// mettre 0 si la combinaison ne marche pas et que la case est vide
    }
  }

  else if(scores_2nd_part[6]!=-1 || scores_2nd_part[7]!=-1){
    if (scores_2nd_part[6]>=0 || scores_2nd_part[7]>=0){ // si deja un score dedans on redemande une autre case en appellant choix_score(recursif)
      printf("Case déja remplie, veuillez saisir une autre case\n");
      choix_score(des);
    }
  }

  else if (tour_jeu%2==0 && scores_2nd_part[6]!=0){
    scores_2nd_part[6]=0;
  }

  else if(tour_jeu%2==1 && scores_2nd_part[7]!=0){
    scores_2nd_part[7]=0;
  }

/**************************************************************************
************************* GRANDE SUITE ************************************
**************************************************************************/
  else if (strcmp(choix_case,"Grande_Suite")==0 && (scores_2nd_part[8]== -1 ||scores_2nd_part[9]==-1)){ // vérif que si il saisit 2 et que soit la case 2 de j1 est vide soit celle de j2 
    if ((des[0])==(des[1]-1)==(des[2]-2)==(des[3]-3)==(des[4]-4)){
      if (tour_jeu%2==0){//verif pour affecter la val au bon joueur(ici j1)
        scores_2nd_part[8]=GRANDE_SUITE;
      }
      else{
        scores_2nd_part[9]=GRANDE_SUITE;
      }
    }
  else if (tour_jeu%2==0){
    scores_2nd_part[8]=0;// mettre 0 si la combinaison ne marche pas et que la case est vide
    }
  else{
    scores_2nd_part[9]=0;// mettre 0 si la combinaison ne marche pas et que la case est vide
    }
  }
  else if(scores_2nd_part[8]!=-1 || scores_2nd_part[9]!=-1){
    if (scores_2nd_part[8]>=0 || scores_2nd_part[9]>=0){ // si deja un score dedans on redemande une autre case en appellant choix_score(recursif)
      printf("Case déja remplie, veuillez saisir une autre case\n");
      choix_score(des);
    }
  }
  else if (tour_jeu%2==0 && scores_2nd_part[8]!=0){
    scores_2nd_part[8]=0;
  }
  else if(tour_jeu%2==1 && scores_2nd_part[9]!=0){
    scores_2nd_part[9]=0;
  }

/**************************************************************************
************************* YAMS ********************************************
**************************************************************************/
  else if (strcmp(choix_case,"Yams")==0 && (scores_2nd_part[10]== -1 ||scores_2nd_part[11]==-1)){ // vérif que si il saisit 2 et que soit la case 2 de j1 est vide soit celle de j2 
    if ((des[0])==(des[1])==(des[2])==(des[3])==(des[4])){
      if (tour_jeu%2==0){//verif pour affecter la val au bon joueur(ici j1)
      scores_2nd_part[10]=YAMS;
      }
      else{
        scores_2nd_part[11]=YAMS;
      }
    }
    else if (tour_jeu%2==0){ 
      scores_2nd_part[10]=0;// mettre 0 si la combinaison ne marche pas et que la case est vide
    }
    else{
      scores_2nd_part[11]=0; // mettre 0 si la combinaison ne marche pas et que la case est vide
    }
  }
  else if(scores_2nd_part[10]!=-1 || scores_2nd_part[11]!=-1){
    if (scores_2nd_part[10]>=0 || scores_2nd_part[11]>=0){ // si deja un score dedans on redemande une autre case en appellant choix_score(recursif)
      printf("Case déja remplie, veuillez saisir une autre case\n");
      choix_score(des);
    }
  }
  else if (tour_jeu%2==0 && scores_2nd_part[10]!=0){
    scores_2nd_part[10]=0;
  }
  else if(tour_jeu%2==1 && scores_2nd_part[11]!=0){
    scores_2nd_part[11]=0;
  }
  
/**************************************************************************
************************* CHANCE ******************************************
**************************************************************************/
  else if (strcmp(choix_case,"Chance")==0 && (scores_2nd_part[12]== -1 ||scores_2nd_part[13]==-1)){ // vérif que si il saisit 2 et que soit la case 2 de j1 est vide soit celle de j2 

    if ((des[0])==(des[1])==(des[2])==(des[3])==(des[4])){

      if (tour_jeu%2==0){//verif pour affecter la val au bon joueur(ici j1)
      scores_2nd_part[12]=des[0]+des[1]+des[2]+des[3]+des[4];
      }

      else{
        scores_2nd_part[13]=des[0]+des[1]+des[2]+des[3]+des[4];
      }
    }

    else if (tour_jeu%2==0){ 
      scores_2nd_part[12]=0;// mettre 0 si la combinaison ne marche pas et que la case est vide
    }

    else{
      scores_2nd_part[13]=0; // mettre 0 si la combinaison ne marche pas et que la case est vide
    }
  }


  else if(scores_2nd_part[12]!=-1 || scores_2nd_part[13]!=-1){ // si deja remplie
    
    if (scores_2nd_part[12]>=0 || scores_2nd_part[13]>=0){ // si deja un score dedans on redemande une autre case en appellant choix_score(recursif)
      printf("Case déja remplie, veuillez saisir une autre case\n");
      choix_score(des);
    }
  }

  else if (tour_jeu%2==0 && scores_2nd_part[12]==-1){ // si la case est vide on peut remplir par 0
    scores_2nd_part[12]=0;
  }

  else if(tour_jeu%2==1 && scores_2nd_part[13]==-1){// si la case est vide on peut remplir par 0
    scores_2nd_part[13]=0;
  }
}



/**
 * @brief Change un dés et l'insère dans le tableau des[] directement après
 * 
 * @param ind_des_retenu contient l'indice afficher à droite des dés qu'il veut changer
 */
void lancerUnDes(int ind_des_retenu){
  int un_de;
  srand(time(NULL));

  un_de = rand() %6 +1;

  des[ind_des_retenu]=un_de;  
}


/*****************
* FONTCIONS TRIS *
*****************/
/**
*   @brief Renvoie l'indice du plus grand élément du tableau
*
*   @param tab : tableau dans lequel on effectue la recherche
*   @param taille : taille du tableau
*
*   @return int l'indice du plus grand élément
**/
int max(int tab[], int taille){
    // on considère que le plus grand élément est le premier
    int i=0, indice_max=0;
    
    while(i < taille)
    {
        if(tab[i] > tab[indice_max])
            indice_max = i;
        i++;
    }
    return indice_max;
}


/**
*   @brief Échange deux éléments d'un tableau
*
*   @param  tab[] : tableau dans lequel on effectue l'échange
*   @param  x : indice du premier élément
*   @param  y : indice du second élément
*
**/
void echanger(int tab[], int x, int y){
    int tmp;
    
    tmp = tab[x];
    tab[x] = tab[y];
    tab[y] = tmp;
}

/**
*   @brief Trie le tableau donné selon l'algorithme de tri par sélection et l'affiche
*
*   @param  tab[] : tableau à trier
*   @param  taille : taille du tableau
*
**/
void tri_selection(int tab[], int taille){
    int indice_max;
    
    /* 
    A chaque tour de boucle, on va déplacer le plus grand élément
    vers la fin du tableau, on diminue donc à chaque fois sa taille
    car le dernier élément est obligatoirement correctement
    placé (et n'a donc plus besoin d'être parcouru/déplacé)
    */

    for(taille=5; taille > 1 ; taille--) // tant qu'il reste des éléments non triés
    {
        indice_max = max(tab, taille);
    
        echanger(tab, taille-1, indice_max); // on échange le dernier élément avec le plus grand
    }
}






/**
 * @brief Demande au joueur quel dés il veut retenir et les change directement en appelant lancerUnDes
 * 
 */
void choix_des(){
  int ind_des_retenu, cpt=1;
  printf("Choisissez vos dés à conserver :");
  printf("tapez -1 pour arretter la saisie d'indice(s) \n");
  printf("Retenue de  :");
  scanf("%d", &ind_des_retenu);

  while(ind_des_retenu<6 && ind_des_retenu!=-1 && cpt<5){
    lancerUnDes(ind_des_retenu);
    scanf("%d", &ind_des_retenu);
    cpt++;
  }
  tri_selection(des,5);
  afficheDes(des);

}






/**
 * @brief Appel de procédures différentes selon valid_lancer, tant qu'il n'est pas valide il redemande valid_lancer
 * 
 * @param valid_lancer contient le choix du joueur
 */
void lancer_oui_non(int valid_lancer){
   while(valid_lancer != 0 && valid_lancer !=1){ // on vérifie qu'il saisit la bonne valeur 
    valid_lancer=0; // remise à zero pour pouvoir comparer dans le lancerJeu avec valid_lancer!=1 dans le if du main dans for de tour_joueur
    printf("|                       |Validez votre lancer ? |\n");
    printf("|Tapez 1 pour valider   | Tapez 0  pour relancer\n");
    printf("|");
    scanf("%d", &valid_lancer);
  }
  if (valid_lancer==1){// Vrai(il ne veut pas relancer de dés)
    choix_score(des); // choisi quelle case il veut remplir
    }
  else{
    choix_des(); // sinon il choisit quel dés il veut changer
  }
}






/*********************
* GENERATION DES DES *
*********************/
/**
 *  @brief Fonction qui génère 5 chiffres entre 1 et 6 
 *  
 *  @return génère ces chiffres et les stockes dans le tableau "des"
 */
void lancerDes(){
    int cpt;

    srand(time(NULL)); //initialisation du générateur

    for (cpt=0; cpt<NB_DES; cpt++){
            des[cpt] = rand() %6 + 1; //génération de valeurs entre 1 et 6 inclus
    }
    tri_selection(des, 5); // tri du tableau de dés
}




/**
 * @brief Calcul des totaux au fur et à mesure
 * 
 * @param scores_1st_part tableau de la 1re partie (tot sup)
 * @param scores_2nd_part tableau de la 2nd partie (tot inf)
 */
void calculTotaux(int scores_1st_part[], int scores_2nd_part[]){
  tot_score_j1 = 0; 
  tot_score_j2 = 0;


  for (int i=0;i<MAX_TAB_SCORES;i++){
    if ((scores_2nd_part[i]!=-1 || scores_1st_part[i]!=-1) && i%2==0){ // on calcule pour J1(que les cases de gauche)
      tot_sup_j1 = tot_sup_j1 + scores_1st_part[i];
      tot_inf_j1 = tot_inf_j1 + scores_2nd_part[i];
      
    }
    else if((scores_2nd_part[i]!=-1 || scores_1st_part[i]!=-1) && i%2==1){
      tot_sup_j2 = tot_sup_j2 + scores_1st_part[i];
      tot_inf_j2 = tot_inf_j2 + scores_1st_part[i];
    }
  }
  if (tot_sup_j1>BONUS_LIM){ // 62 pts
    scores_1st_part[12]=BONUS_POINTS; // 35 pts
  }
  else if(tot_sup_j2>BONUS_LIM){ // 62 pts
    scores_1st_part[13]=BONUS_POINTS; // 35 pts
  }
  tot_score_j1 = tot_sup_j1 + tot_inf_j1;
  tot_score_j2 = tot_sup_j2 + tot_inf_j2;

  
}

/*******************
* LANCEMENT DU JEU *
*******************/
/**
 * @brief Met en place le jeu avec le nb de tours obligatoire
 * 
 */
void lancerJeu(){
  int tour_joueur; // compte le nombre de tour que le joueur dispose par tour
  int nb_lancer_restants ; // compte le nombre de lancers restants au joueur
  for (tour_jeu=0;tour_jeu<=NB_TOUR;tour_jeu++){ // boucle pour l'entièreté du jeu (26tour_jeu qui est définit en variable globale)
    tour_joueur = 0;
    valid_lancer = 0;
    nb_lancer_restants =2; // au premier affichage de cette varaible il aura deja fait son lancer de base
    while (tour_joueur < 4 && valid_lancer == 0){ // tant qu'il n'pas joué 3 fois où qu'il veuille saisir son score
        printf("\n");
        printf("\n");  
        printf("+-----------------------------------------------+\n");   
        printf("|-----------------------------------------------|\n");
        if (tour_jeu%2==0){ // on vérifie quel nom de joueur afficher
          printf("|Lancer dés de %13s|                       |\n", j1);
        }
        else{
          printf("|Lancer dés de %13s|                       |\n", j2);
        }
        printf("|0 : oui                |                       |\n");
        printf("|");
        scanf("%1d", &lance_verif);
        propLancer(lance_verif);
        printf("|                       |                       |\n");
        printf("|Résultat lancer :      |                       |\n");
        printf("\n");
        lancerDes();
        afficheDes(des);
        printf("|                       |Validez votre lancer ? |\n");
        printf("|                       |  %1d lancers restants   |\n", nb_lancer_restants);
        printf("|Tapez 1 pour valider   | Tapez 0  pour relancer\n");
        printf("|");
        scanf("%d", &valid_lancer);
        lancer_oui_non(valid_lancer);
        nb_lancer_restants--;
        while (valid_lancer == 0 && nb_lancer_restants>0){ // insérer une var globale qui incrémente dans choix des puis ici
          printf("|                       |Validez votre lancer ? |\n");
          printf("|                       |  %1d lancers restants   |\n", nb_lancer_restants);
          printf("|Tapez 1 pour valider   | Tapez 0  pour relancer\n");
          printf("|");
          scanf("%d", &valid_lancer);
          lancer_oui_non(valid_lancer);
          tri_selection(des,5);
          nb_lancer_restants--;
          tour_joueur++;
        }
        if (nb_lancer_restants==0){
          choix_score(des);
        }

        printf("\n");
        printf("\n");
        calculTotaux(scores_1st_part,  scores_2nd_part);
        afficheTableau( j1,  j2,  tot_sup_j1,  tot_sup_j2,  tot_inf_j1,  tot_inf_j2,   tot_score_j1,  tot_score_j2,  scores_1st_part,  scores_2nd_part);
      }
      
      
  }
  // system("clear");
}

/**
 * @brief Permet d'afficher le gagnant
 * 
 * @param tot_score_j1 : score de j1
 * @param tot_score_j2 : score de j2
 */
void afficheGagnant(int tot_score_j1, int tot_score_j2){
  if (tot_score_j1 > tot_score_j2){
    printf("%13s a gagné !!!!", j1);
  }
  else if (tot_score_j2 > tot_score_j1){
    printf("%13s a gagné !!!", j2);
  }
  else{
    printf("Ex Aequo");
  }
}




/**********************
* PROGRAMME PRINCIPAL *
**********************/
int main(){
  /*********************************
  * PROCEDURE POUR DEMARRER LE JEU *
  *********************************/
  remplirTab(MAX_TAB_SCORES);

  // initialisation des vatiables à 0
  tot_sup_j1 = 0, tot_sup_j2 = 0,
  tot_inf_j1 = 0, tot_inf_j2 = 0,
  tot_score_j1 = 0, tot_score_j2 = 0;

  // demande les prénoms des joeurs
  demandePrenom(j1, j2);

  afficheTableau(j1, j2, tot_sup_j1, tot_sup_j2, tot_inf_j1, tot_inf_j2, tot_score_j1, tot_score_j2, scores_1st_part, scores_2nd_part);

/*******************
* LANCEMENT DU JEU *
*******************/
  lancerJeu();

  afficheGagnant(tot_score_j1, tot_score_j2);
  return EXIT_SUCCESS;
}    
  


