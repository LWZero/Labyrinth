/*
 * auteurs/mails    : Do Samuel et Valentin Messias
 * groupe de TD     : Groupe E	
 * groupe de TP     : Groupe Prepa
 * date de création : 2014-01-11
 * description      : Sujet de projet n°20 : Représentation d'un labyrinthe.

Note Importante.
Pour pouvoir se repérer sur la carte, on utilise les conventions suivantes.

8 code le nord,
6 l'est, 
4 l'ouest,
2 le sud.

OU

8 pour le haut, 
6 pour la droite,
4 pour la gauche, 
2 pour le bas 

Selon la variable, cela représente l'orientation ou le sens du mouvement.


Pour la carte, la valeur 0 est le mur, et 1 la case vide.
		5 est le joueur, 7 est la sortie.
		9 code tout autre objet, et n'est pas utilisé pour autre chose que les '\n'.

 */



#include <MLV/MLV_all.h>
#include <stdio.h>
#include <stdlib.h>
#define T_MAX 128

/* Structure de position, donne les coordonnées x et y d'un objet.
Elle permettra de donner un couple de coordonnées à un objet, comme le joueur ou la sortie.
*/


typedef struct{
	int x;
	int y;
}Position;


//Cette fonction vérifie que la carte n'est pas vide, elle renvoie une valeur en fonction du test.
int Verif_fichier( FILE* fich)
{
	if(fich==NULL)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/*
Cette fonction prend en argument l'adresse d'un fichier, contenant la carte, le tableau Carte, et la longueur et hauteur de celle-ci. 
Elle récupère la carte du fichier et la transforme en tableau
*/
void LireTab(FILE* fich, int Carte[][T_MAX],int longueur,int hauteur)
{
	int i,j;
	char temp;
		
	for(i=0;i<hauteur;i=i+1)
	{
		for(j=0;j<longueur;j=j+1)
		{
			/*Stock le caractère dans un tampon et remplit la case en fonction du caractère
			selon les conventions écrites en début de programme
			*/
			fscanf(fich,"%c",&temp);
			switch(temp){
				case '*':
					Carte[i][j]=0;
					break;
 				case '.':
					Carte[i][j]=1;
					break;
				case '@':
					Carte[i][j]=5;
					break;
				case 'X':
					Carte[i][j]=7;
					break;
				default:
					Carte[i][j]=9;
					break;
			}
		}
	}
}


/*
Cette fonction récupère la position du joueur
Il teste la carte et entre les coordonnées de la case contenant le code du joueur, le 5
*/		
void Recup_Pos_Joueur( Position *PJoueur,int Carte[][T_MAX] ,int longueur , int hauteur )
{
	int i,j;
	for(i=0;i<hauteur;i=i+1)
	{
		for(j=0;j<longueur;j=j+1)
		{
			if( Carte[i][j]==5)
			{
				PJoueur->x=j;
				PJoueur->y=i;
			}	
		}
	}
}

/* 
Cette fonction récupère la position de la sortie
Exactement comme au dessus, mais cherche le code 7 de la sortie
*/
void Recup_Pos_Sortie( Position *PSortie,int Carte[][T_MAX], int longueur , int hauteur )
{
	
	int i,j;
	for(i=0;i<hauteur;i=i+1)
	{
		for(j=0;j<longueur;j=j+1)
		{
			if( Carte[i][j]==7)
			{
				PSortie->x = j;
				PSortie->y = i;
			}	
		}
	}
}		


/*
Cette fonction prend en argument les coordonnées x et y du clic de la souris.
Elle teste les différentes zones pour savoir si le joueur a cliqué sur une touche.
Elle renvoie une valeur en fonction de la zone
Si le joueur a cliqué sur une zone qui n'est pas une touche, elle renvoie -1
*/
int zone_clic( int x,int y)
{
	// Zone du  Bouton de sauvegarde
	if( y>=605 && y<= 655 && x >= 100 && x<= 300)
	{
		return 1;
	}


	if( y>=580 && y <= 630)
	{	
		// Bouton pour Tourner vers la gauche
		if( x>=400 && x<=500)
		{
			return 7;
		}
		//Bouton pour le Pas en avant
		else if( x>500 && x<=600)
		{
			return 8;
		}
		//Bouton pour  Tourner vers la droite 
		else if( x>600 && x<=700)
		{
			return 9;
		}
	}
	if( y>630 && y<=680)
	{
		//Bouton pour le Pas vers la gauche
		if( x>=400 && x<=500)
		{
			return 4;
		}
		//Bouton pour le Pas en arrière 
		else if( x>500 && x<=600)
		{
			return 5;
		}
		//Bouton pour le Pas vers la droite
		else if( x>600 && x<=700)
		{	
			return 6;
		}
	}
	// si aucun test n'est bon, il va renvoyer -1
	return -1;

}

/*
Cette fonction permet d'afficher l'interface de l'utilisateur
Elle crée la fenêtre, donne le fond blanc pour la vue
et crée des lignes qui dessinent les différentes zones.
On actualise à la fin de cette fonction.
Cela sera le cas pour les autres fonctions Affiche_ suivantes.
*/
void Affiche_cadre()
{
	// Ouvre une Fenêtre de 1280*720
	MLV_create_window( "labyrinthe", "Laby", 1280, 720 );
  	// Donne le fond blanc pour les vues.
	MLV_draw_filled_rectangle(0 ,0 ,960 ,540 ,MLV_COLOR_WHITE);
  
	// Donne le fond blanc pour les touches du joueur
	MLV_draw_filled_rectangle( 400, 580, 300, 100, MLV_COLOR_WHITE);

	//Trace la ligne du milieu pour délimiter les boutons du haut et du bas
  	MLV_draw_line(400, 630, 700, 630, MLV_COLOR_BLACK);
	//Trace les colonnes pour délimiter les 3 boutons d'une même rangée.
  	MLV_draw_line(500, 580, 500, 680, MLV_COLOR_BLACK);
 	MLV_draw_line(600, 580, 600, 680, MLV_COLOR_BLACK);
	
	//Donne le fond blanc pour le bouton de sauvegarde.
	MLV_draw_filled_rectangle( 100, 605, 200, 50, MLV_COLOR_WHITE );

	//Donne le cadre rouge de la carte
	MLV_draw_rectangle( 970, 10, 370,530, MLV_COLOR_RED);	
	
	MLV_actualise_window();
}

/*
Cette fonction affiche les flèches de l'utilisateur et le bouton sauvegarde
*/
void Affiche_Boutons()
{
 
	//
	// quart de tour à gauche
	//
	int coordonnee_x[3] = { 439 , 466 , 450 };
	int coordonnee_y[3] = { 612 ,  609, 595 };
	MLV_draw_bezier_curve( coordonnee_x, coordonnee_y, 3, MLV_COLOR_BLACK );
	MLV_draw_line( 450, 595, 457, 595, MLV_COLOR_BLACK);
	MLV_draw_line( 450, 595, 450, 602, MLV_COLOR_BLACK);

	//
	// quart de tour à droite
	//
	int coordonnee_xx[3] = { 666 , 639 , 655 };
	int coordonnee_yy[3] = { 612 ,  609, 595 };
	MLV_draw_bezier_curve( coordonnee_xx, coordonnee_yy, 3, MLV_COLOR_BLACK );
	MLV_draw_line( 655, 595, 648, 595, MLV_COLOR_BLACK);
	MLV_draw_line( 655, 595, 655, 602,MLV_COLOR_BLACK);

	//
	// avancer d'une case
	//
	MLV_draw_line( 550, 590, 550, 620, MLV_COLOR_BLACK);
	MLV_draw_line( 550, 590, 543, 597, MLV_COLOR_BLACK);
	MLV_draw_line( 550, 590, 557, 597, MLV_COLOR_BLACK);



	//
	// pas en arrière
	//
	MLV_draw_line( 550, 640, 550, 670,MLV_COLOR_BLACK);
	MLV_draw_line( 550, 670, 543, 663, MLV_COLOR_BLACK);
	MLV_draw_line( 550, 670, 557, 663,MLV_COLOR_BLACK);

	//
	// pas sur le côté à gauche
	//
	MLV_draw_line( 430, 655, 470, 655, MLV_COLOR_BLACK);
	MLV_draw_line( 430, 655, 437, 648, MLV_COLOR_BLACK);
	MLV_draw_line( 430, 655, 437, 662,MLV_COLOR_BLACK);

	//
	// pas sur le côté à droite
	//
	MLV_draw_line( 630, 655, 670, 655, MLV_COLOR_BLACK);
	MLV_draw_line( 670, 655, 663, 648,MLV_COLOR_BLACK);
	MLV_draw_line( 670, 655, 663, 662, MLV_COLOR_BLACK);


	// Bouton sauvegarder

	MLV_draw_text(
			145, 622, 
			"SAUVEGARDER",
			MLV_COLOR_RED
		);
		
	MLV_actualise_window();

}



// Affiche une boussole pour donner l'orientation du joueur
void Afficher_boussole( int orientation )
{
	
	MLV_draw_filled_circle( 1120 , 630 , 70 , MLV_COLOR_WHITE );
	
	switch (orientation){
		case 8:
			MLV_draw_line( 1105, 630, 1135, 630, MLV_COLOR_BLACK);
			MLV_draw_line( 1105, 630, 1120, 560, MLV_COLOR_BLACK);
			MLV_draw_line( 1135, 630, 1120, 560, MLV_COLOR_BLACK); 
			break;
		case 6:
			MLV_draw_line( 1120, 615, 1120, 645, MLV_COLOR_BLACK);
			MLV_draw_line( 1120, 615, 1190, 630, MLV_COLOR_BLACK);
			MLV_draw_line( 1120, 645, 1190, 630, MLV_COLOR_BLACK); 
			break;
		case 4:
			MLV_draw_line( 1120, 615, 1120, 645, MLV_COLOR_BLACK);
			MLV_draw_line( 1120, 615, 1050, 630, MLV_COLOR_BLACK);
			MLV_draw_line( 1120, 645, 1050, 630, MLV_COLOR_BLACK);
			break;
		case 2:
			MLV_draw_line( 1105, 630, 1135, 630, MLV_COLOR_BLACK);
			MLV_draw_line( 1105, 630, 1120, 700, MLV_COLOR_BLACK);
			MLV_draw_line( 1135, 630, 1120, 700, MLV_COLOR_BLACK);
			break;
		default:
			break;

	}
	
		
		
	MLV_actualise_window();
}


/* 
Les fonctions suivantes dessinent les différents blocs pour les vues.
Elles effacent les lignes derrières elles, et tracent les lignes correspondantes.
On n'actualise pas ici, car l'actualisation se fera dans la fonction Affichage_blocs, après voir tout dessiné
*/


// Permet de vider la vue du labyrinthe pour le redessiner
void Vider_Vue()
{
	MLV_draw_filled_rectangle(0 ,0 ,959 ,539 ,MLV_COLOR_WHITE);
}

// Affiche le mur à trois cases en face, 
void Afficher_mur_fond_2()
{
	Vider_Vue();
	MLV_draw_line(0,200,960 ,200, MLV_COLOR_BLACK);
	MLV_draw_line(0,346,960 ,346, MLV_COLOR_BLACK);
	MLV_draw_line(340,200,340 ,346, MLV_COLOR_BLACK);
	MLV_draw_line(620,200,620 ,346, MLV_COLOR_BLACK);


	
}
// Affiche le mur à deux cases en face et une case à gauche
void Afficher_diag_2_gauche()
{
	
	MLV_draw_filled_rectangle(0 ,0 ,340 ,539 ,MLV_COLOR_WHITE);
	MLV_draw_line(0,162 , 288,162,MLV_COLOR_BLACK);
  	MLV_draw_line(0,378 , 288,378, MLV_COLOR_BLACK);
        MLV_draw_line(288,162, 340,200, MLV_COLOR_BLACK);

	MLV_draw_line(288,378,340 ,346, MLV_COLOR_BLACK);
	MLV_draw_line(340,200,340 ,346, MLV_COLOR_BLACK);

        MLV_draw_line(288,162, 288,378, MLV_COLOR_BLACK);
}


// Affiche le mur à trois cases en face et une case à droite.
void Afficher_diag_2_droite()
{

	MLV_draw_filled_rectangle(619 ,0 ,340 ,539 ,MLV_COLOR_WHITE);
	MLV_draw_line(672,162, 960,162, MLV_COLOR_BLACK);
	MLV_draw_line(672,378,960,378, MLV_COLOR_BLACK);
	
	MLV_draw_line(672,162 , 620,200,MLV_COLOR_BLACK);
  	MLV_draw_line(672,378 , 620,346, MLV_COLOR_BLACK);
      
	MLV_draw_line(620,200,620 ,346, MLV_COLOR_BLACK);

	
	MLV_draw_line(672,162,672 ,378, MLV_COLOR_BLACK);
	
}

// Affiche le mur à deux cases en face. 
void Afficher_mur_fond()
{	MLV_draw_filled_rectangle(287, 162, 386, 216, MLV_COLOR_WHITE);
	    MLV_draw_rectangle(288, 162, 384, 216, MLV_COLOR_BLACK);
	   
}

// Affiche le bloc diagonal droit 
void Afficher_diag_droite()
{
	MLV_draw_filled_rectangle(671,0 ,288 ,539 ,MLV_COLOR_WHITE);
	
	MLV_draw_line(885,42 , 960,42, MLV_COLOR_BLACK);
	MLV_draw_line(885,499 , 960,499, MLV_COLOR_BLACK);
	MLV_draw_line(672, 162, 672, 378,MLV_COLOR_BLACK);
	MLV_draw_line(885, 42, 672, 162, MLV_COLOR_BLACK);
	MLV_draw_line(885, 499, 672, 378, MLV_COLOR_BLACK);
	MLV_draw_line(885, 42, 885, 499, MLV_COLOR_BLACK);

}
// Affiche le bloc diagonal gauche 
void Afficher_diag_gauche()
{
	MLV_draw_filled_rectangle(0,0 ,288 ,539 ,MLV_COLOR_WHITE);

	   MLV_draw_line(0,42 , 75,42, MLV_COLOR_BLACK);
           MLV_draw_line(0,499 , 75,499, MLV_COLOR_BLACK);
           MLV_draw_line(288, 162, 288, 378, MLV_COLOR_BLACK);
           MLV_draw_line(75, 42, 288, 162, MLV_COLOR_BLACK);
           MLV_draw_line(75, 499, 288, 378, MLV_COLOR_BLACK);
           MLV_draw_line(75,42 , 75,499, MLV_COLOR_BLACK);


}
// Affiche le mur en face
void Afficher_mur_face()
{
	    MLV_draw_filled_rectangle(75,42 ,811 ,457 ,MLV_COLOR_WHITE);
	    MLV_draw_rectangle(75,42 ,810 ,457 ,MLV_COLOR_BLACK);

}
// Affiche le mur à droite 
void Afficher_bloc_a_droite()
{
	 MLV_draw_filled_rectangle(884,0, 75 , 539,MLV_COLOR_WHITE);
	 MLV_draw_line(960, 0, 885, 42, MLV_COLOR_BLACK);
  	 MLV_draw_line(960, 540, 885, 499, MLV_COLOR_BLACK);
 	 MLV_draw_line(885, 42, 885, 499, MLV_COLOR_BLACK);
}

// Affiche le mur à gauche 
void Afficher_bloc_a_gauche()
{
	MLV_draw_filled_rectangle(0,0, 75 , 539,MLV_COLOR_WHITE);
	MLV_draw_line(0, 0, 75, 42, MLV_COLOR_BLACK);
  	MLV_draw_line(0, 540, 75, 499, MLV_COLOR_BLACK);
  	MLV_draw_line(75,42 , 75,499, MLV_COLOR_BLACK);


}
// Affiche le S signifiant la sortie
void Afficher_sortie()
{
	
	MLV_draw_line(405, 195, 555, 195, MLV_COLOR_BLACK);
	MLV_draw_line(405, 265, 555, 265, MLV_COLOR_BLACK);
	MLV_draw_line(405, 335, 555, 335, MLV_COLOR_BLACK);
	MLV_draw_line(405, 195, 405, 265, MLV_COLOR_BLACK);
	MLV_draw_line(555, 265, 555, 335, MLV_COLOR_BLACK);
}


/* En argument est passé le sens du mouvement,
8 pour le haut 
6 pour la droite
4 pour la gauche 
2 pour le bas 
On vérifie s'il y a un espace vide ou la sortie grâce aux coordonnées du joueur.
Renvoie ensuite si le mouvement est possible ou non/
*/


int Verif_Obstacle(int Carte[][T_MAX],Position Pjoueur,int sens)
{
	int mov_possible;
	mov_possible=0;

	switch (sens){
		case 8:
			if( Carte[Pjoueur.y - 1][ (Pjoueur.x)] == 1 || Carte[Pjoueur.y - 1][ (Pjoueur.x)] == 7 )
 			{
				mov_possible = 1;
			}
			break;
		case 4:
			if( Carte[ (Pjoueur.y) ][Pjoueur.x -1 ] == 1 || Carte[ (Pjoueur.y) ][Pjoueur.x -1 ] == 7)
			{
				mov_possible = 1;
			}
			break;
		case 2:
			if( Carte[Pjoueur.y + 1][ (Pjoueur.x )] == 1 || Carte[ (Pjoueur.y + 1) ][Pjoueur.x ] == 7)
			{
				mov_possible = 1;
			}
			break;
		case 6:
			if( Carte[ (Pjoueur.y ) ][ (Pjoueur.x + 1)] == 1 || Carte[ (Pjoueur.y) ][Pjoueur.x + 1 ] == 7)
			{
				mov_possible = 1;
			}
			break;
		default:
			break;

	}
	return mov_possible;
}

// Change l'orientation du joueur de 90° vers la gauche et renvoie la nouvelle orientation
int Tourner_gauche( int orientation )
{
	switch (orientation){
		case 8:
			orientation=4; 
			break;
		case 4:
			orientation=2; 
			break;
		case 2:
			orientation=6; 
			break;
		case 6:
			orientation=8; 
			break;
		default:
			break;

	}
	return orientation;

}

// Change l'orientation du joueur de 90° vers la droite et renvoie la nouvelle orientation
int Tourner_droite( int orientation )
{
	switch (orientation){
		case 2:
			orientation=4; 
			break;
		case 6:
			orientation=2; 
			break;
		case 8:
			orientation=6; 
			break;
		case 4:
			orientation=8; 
			break;
		default:
			break;

	}
	return orientation;

}


/*  POUR TOUTES LES TOUCHES 
	
	L'action est différente selon l'orientation
	La case d'arrivée prend la valeur 5, codant le joueur
	La case de départ reprend la valeur 1, qui est à nouveau vide.
	De même pour la carte utilisée pour l'affichage	
	Ensuite, on change les coordonnées de position du joueur .
	( Juste une , car le mouvement est dans une seule direction)
	

*/


// Code l'action du bouton Arrière
void Bouton_arriere (int Carte[][T_MAX], int Carte_Affich[][T_MAX],Position  *Pjoueur,int orientation)
{	
	
	
		switch (orientation){
		case 2:
			if( Verif_Obstacle(Carte, *Pjoueur,8) == 1) 
			{
				Carte[Pjoueur->y - 1 ][Pjoueur->x ] =5;
				Carte[Pjoueur->y][Pjoueur->x] = 1; 
				Carte_Affich[Pjoueur->y - 1 ][Pjoueur->x ] =5;
				Carte_Affich[Pjoueur->y][Pjoueur->x] = 1; 
		
				Pjoueur->y = Pjoueur->y - 1;
			}
			break;
		case 4 :
			if( Verif_Obstacle(Carte, *Pjoueur,6) == 1) 
			{			
				Carte[Pjoueur->y][Pjoueur->x + 1] =5;
				Carte[Pjoueur->y ][Pjoueur->x] = 1; 
				Carte_Affich[Pjoueur->y][Pjoueur->x + 1] =5;
				Carte_Affich[Pjoueur->y ][Pjoueur->x] = 1; 
				Pjoueur->x = Pjoueur->x + 1; 
			}			
			break;
		case 6 :
			if( Verif_Obstacle(Carte, *Pjoueur,4) == 1) 
			{
				Carte[Pjoueur->y][Pjoueur->x - 1] =5;
				Carte[Pjoueur->y][Pjoueur->x] = 1; 
				Carte_Affich[Pjoueur->y][Pjoueur->x - 1] =5;
				Carte_Affich[Pjoueur->y][Pjoueur->x] = 1; 
				Pjoueur->x = Pjoueur->x - 1; 
			}			
			break;
		case 8 :
			if( Verif_Obstacle(Carte, *Pjoueur,2) == 1) 
			{
				Carte[Pjoueur->y + 1][Pjoueur->x] =5;
				Carte[Pjoueur->y ][Pjoueur->x] = 1; 
				Carte_Affich[Pjoueur->y + 1][Pjoueur->x] =5;
				Carte_Affich[Pjoueur->y ][Pjoueur->x] = 1; 
				Pjoueur->y = Pjoueur->y + 1;
			}
			break;
		
		default:
			break;

	}
	
	
}

// code l'action du bouton avant
void Bouton_avant (int Carte[][T_MAX], int Carte_Affich[][T_MAX],Position  *Pjoueur,int orientation)
{	
	
	
		switch (orientation){
		case 8:
			if( Verif_Obstacle(Carte, *Pjoueur,8) == 1) 
			{
				Carte[Pjoueur->y - 1 ][Pjoueur->x ] =5;
				Carte[Pjoueur->y][Pjoueur->x] = 1; 
				Carte_Affich[Pjoueur->y - 1 ][Pjoueur->x ] =5;
				Carte_Affich[Pjoueur->y][Pjoueur->x] = 1; 
				Pjoueur->y = Pjoueur->y - 1;
			}
			break;
		case 6:
			if( Verif_Obstacle(Carte, *Pjoueur,6) == 1) 
			{			
				Carte[Pjoueur->y][Pjoueur->x + 1] =5;
				Carte[Pjoueur->y ][Pjoueur->x] = 1; 	
				Carte_Affich[Pjoueur->y][Pjoueur->x + 1] =5;
				Carte_Affich[Pjoueur->y ][Pjoueur->x] = 1; 
				Pjoueur->x = Pjoueur->x + 1; 
			}			
			break;
		case 4 :
			if( Verif_Obstacle(Carte, *Pjoueur,4) == 1) 
			{
				Carte[Pjoueur->y][Pjoueur->x - 1] =5;
				Carte[Pjoueur->y][Pjoueur->x ] = 1; 
				Carte_Affich[Pjoueur->y][Pjoueur->x - 1] =5;
				Carte_Affich[Pjoueur->y][Pjoueur->x ] = 1; 
				Pjoueur->x = Pjoueur->x - 1; 
			}			
			break;
		case 2 :
			if( Verif_Obstacle(Carte, *Pjoueur,2) == 1) 
			{
				Carte[Pjoueur->y + 1][Pjoueur->x] =5;
				Carte[Pjoueur->y ][Pjoueur->x] = 1;
				Carte_Affich[Pjoueur->y + 1][Pjoueur->x] =5;
				Carte_Affich[Pjoueur->y ][Pjoueur->x] = 1;  
				Pjoueur->y = Pjoueur->y + 1;
			}
			break;
		
		default:
			break;

	}
	
	
}

// code l'action du bouton gauche
void Bouton_gauche (int Carte[][T_MAX], int Carte_Affich[][T_MAX],Position  *Pjoueur,int orientation)
{	
	
	
		switch (orientation){
		case 6:
			if( Verif_Obstacle(Carte, *Pjoueur,8) == 1) 
			{
				Carte[Pjoueur->y - 1 ][Pjoueur->x ] =5;
				Carte[Pjoueur->y][Pjoueur->x] = 1; 
				Carte_Affich[Pjoueur->y - 1 ][Pjoueur->x ] =5;
				Carte_Affich[Pjoueur->y][Pjoueur->x] = 1; 
				Pjoueur->y = Pjoueur->y - 1;
			}
			break;
		case 2 :
			if( Verif_Obstacle(Carte, *Pjoueur,6) == 1) 
			{			
				Carte[Pjoueur->y][Pjoueur->x + 1] =5;
				Carte[Pjoueur->y ][Pjoueur->x] = 1; 
				Carte_Affich[Pjoueur->y][Pjoueur->x + 1] =5;
				Carte_Affich[Pjoueur->y ][Pjoueur->x] = 1; 
				Pjoueur->x = Pjoueur->x + 1; 
			}			
			break;
		case 8 :
			if( Verif_Obstacle(Carte, *Pjoueur,4) == 1) 
			{
				Carte[Pjoueur->y][Pjoueur->x - 1] =5;
				Carte[Pjoueur->y][Pjoueur->x ] = 1; 
				Carte_Affich[Pjoueur->y][Pjoueur->x - 1] =5;
				Carte_Affich[Pjoueur->y][Pjoueur->x ] = 1; 
				Pjoueur->x = Pjoueur->x - 1; 
			}			
			break;
		case 4 :
			if( Verif_Obstacle(Carte, *Pjoueur,2) == 1) 
			{
				Carte[Pjoueur->y + 1][Pjoueur->x] =5;
				Carte[Pjoueur->y ][Pjoueur->x] = 1; 
				Carte_Affich[Pjoueur->y + 1][Pjoueur->x] =5;
				Carte_Affich[Pjoueur->y ][Pjoueur->x] = 1; 
				Pjoueur->y = Pjoueur->y + 1;
			}
			break;
		
		default:
			break;

	}
	
	
}

// code l'action du bouton droit
void Bouton_droite (int Carte[][T_MAX], int Carte_Affich[][T_MAX], Position  *Pjoueur,int orientation)
{	
	
	
		switch (orientation){
		case 4:
			if( Verif_Obstacle(Carte, *Pjoueur,8) == 1) 
			{
				Carte[Pjoueur->y - 1 ][Pjoueur->x ] =5;
				Carte[Pjoueur->y][Pjoueur->x] = 1; 
				Carte_Affich[Pjoueur->y - 1 ][Pjoueur->x ] =5;
				Carte_Affich[Pjoueur->y][Pjoueur->x] = 1; 
				Pjoueur->y = Pjoueur->y - 1;
			}
			break;
		case 8 :
			if( Verif_Obstacle(Carte, *Pjoueur,6) == 1) 
			{			
				Carte[Pjoueur->y][Pjoueur->x + 1] =5;
				Carte[Pjoueur->y ][Pjoueur->x] = 1; 
				Carte_Affich[Pjoueur->y][Pjoueur->x + 1] =5;
				Carte_Affich[Pjoueur->y ][Pjoueur->x] = 1; 
				Pjoueur->x = Pjoueur->x + 1; 
			}			
			break;
		case 2 :
			if( Verif_Obstacle(Carte, *Pjoueur,4) == 1) 
			{
				Carte[Pjoueur->y][Pjoueur->x - 1] =5;
				Carte[Pjoueur->y][Pjoueur->x ] = 1; 
				Carte_Affich[Pjoueur->y][Pjoueur->x - 1] =5;
				Carte_Affich[Pjoueur->y][Pjoueur->x ] = 1; 
				Pjoueur->x = Pjoueur->x - 1; 
			}			
			break;
		case 6 :
			if( Verif_Obstacle(Carte, *Pjoueur,2) == 1) 
			{
				Carte[Pjoueur->y + 1][Pjoueur->x] =5;
				Carte[Pjoueur->y ][Pjoueur->x] = 1; 
				Carte_Affich[Pjoueur->y + 1][Pjoueur->x] =5;
				Carte_Affich[Pjoueur->y ][Pjoueur->x] = 1; 
				Pjoueur->y = Pjoueur->y + 1;
			}
			break;
		
		default:
			break;

	}
	
	
}

/* Affichage blocs
En argument, on rentre les cases qui entourent le joueur. Cela est obtenue avec la fonction vue, codée plus bas.
Il affiche d'abord le mur le plus loin.
Ensuite, chaque test vrai efface ce qu'il y a derrière lui et affiche son mur.
En effet, s'il y a un mur devant, il n'y a pas besoin d'afficher le mur derrière.
Ainsi, on obtient seulement les murs en vue directe par l'utilisateur. 

*/
void Affichage_blocs (int en_face,int en_face_plus,int a_droite,int a_gauche,int diag_gauche,int diag_droite,int en_face_plus_2, int diag_2_gauche, int diag_2_droite)
{
// Dans le cas où il n'y a aucun mur aux alentours, afin de ne pas avoir juste du blanc , on affiche un mur au loin
        MLV_draw_line(0,240,340 ,240, MLV_COLOR_BLACK);
	MLV_draw_line(0,346,340 ,346, MLV_COLOR_BLACK);	
	MLV_draw_line(620,240,960 ,240, MLV_COLOR_BLACK);
	MLV_draw_line(620,346,960 ,346, MLV_COLOR_BLACK);
	
	MLV_draw_line(340,240,340 ,346, MLV_COLOR_BLACK);
	MLV_draw_line(620,240,620 ,346, MLV_COLOR_BLACK);	

	if(en_face_plus_2==0 )
	{
		Afficher_mur_fond_2();
	}
	if(diag_2_gauche==0)
	{
		Afficher_diag_2_gauche();
	}
	if(diag_2_droite==0)
	{
		Afficher_diag_2_droite();
	}
	if(en_face_plus==0 || en_face_plus==7)
	{
		Afficher_mur_fond();
	}
	if(diag_gauche == 0)
	{
		Afficher_diag_gauche();
	}
	if(diag_droite ==0)
	{
		Afficher_diag_droite();
	}
	if(en_face==0)
	{
		Afficher_mur_face();
	}
	if( a_droite ==0)
	{
		Afficher_bloc_a_droite();
	}
	if( a_gauche ==0)
	{
		Afficher_bloc_a_gauche();
	}

	// S'il y a la sortie en face, on affiche le mur puis la sortie
	if(en_face==7 )
	{
		Afficher_mur_face();
		Afficher_sortie();
	}
	
	if(en_face_plus==7 )
	{
		Afficher_mur_fond();
		Afficher_sortie();
	}
	
	MLV_actualise_window();
}


/*	Fonction vue

La fonction vue prend en argument l'orientation de l'utilisateur
Elle cherche et affecte les différentes cases autour de l'utilisateur.
Cela permet après pour les vues , de ne plus se soucier de l'orientation
mais seulement de ce que l'utilisateur voit.

On affecte donc aux 9 variables les différentes cases alentours,
Et ensuite, on affiche les blocs  grâce à l'appel de la fonction Affichage_blocs

	C
       CCC
       CCC
       CXC

Chaque C est une case à tester  


*/
void Vue ( int Carte[][T_MAX],Position  *Pjoueur,int orientation )
{
	int en_face,a_droite,a_gauche,diag_gauche,diag_droite,en_face_plus;
	int diag_2_gauche,en_face_plus_2,diag_2_droite;
	
	Vider_Vue();
	switch (orientation){
		case 2:
			en_face = Carte[Pjoueur->y + 1 ][Pjoueur->x ];
			en_face_plus = Carte[Pjoueur->y + 2 ][Pjoueur->x ];		
			a_droite = Carte[Pjoueur->y ][Pjoueur->x - 1 ];
			a_gauche = Carte[Pjoueur->y  ][Pjoueur->x + 1];
			diag_gauche = Carte[Pjoueur->y + 1 ][Pjoueur->x + 1 ];
			diag_droite =Carte[Pjoueur->y + 1 ][Pjoueur->x - 1 ];
			en_face_plus_2 = Carte[Pjoueur->y + 3 ][Pjoueur->x ];		
			diag_2_gauche = Carte[Pjoueur->y + 2 ][Pjoueur->x + 1 ];		
			diag_2_droite = Carte[Pjoueur->y + 2 ][Pjoueur->x - 1 ];		
			
			Affichage_blocs(en_face,en_face_plus,a_droite,a_gauche,diag_gauche,diag_droite,en_face_plus_2, diag_2_gauche,diag_2_droite);
			break;


		case 4 :
			en_face = Carte[Pjoueur->y  ][Pjoueur->x -1 ];
			en_face_plus = Carte[Pjoueur->y  ][Pjoueur->x -2 ];		
			a_droite = Carte[Pjoueur->y -1][Pjoueur->x  ];
			a_gauche = Carte[Pjoueur->y +1 ][Pjoueur->x ];
			diag_gauche = Carte[Pjoueur->y + 1 ][Pjoueur->x -1 ];
			diag_droite =Carte[Pjoueur->y - 1 ][Pjoueur->x - 1 ];
			en_face_plus_2 = Carte[Pjoueur->y  ][Pjoueur->x - 3 ];		
			diag_2_gauche = Carte[Pjoueur->y + 1 ][Pjoueur->x - 2 ];		
			diag_2_droite = Carte[Pjoueur->y - 1  ][Pjoueur->x - 2 ];		
	
			Affichage_blocs(en_face,en_face_plus,a_droite,a_gauche,diag_gauche,diag_droite,en_face_plus_2, diag_2_gauche,diag_2_droite);			
			break;

		case 6 :
			en_face = Carte[Pjoueur->y ][Pjoueur->x +1 ];
			en_face_plus = Carte[Pjoueur->y ][Pjoueur->x +2 ];		
			a_droite = Carte[Pjoueur->y +1][Pjoueur->x ];
			a_gauche = Carte[Pjoueur->y - 1 ][Pjoueur->x ];
			diag_gauche = Carte[Pjoueur->y - 1 ][Pjoueur->x +1 ];
			diag_droite =Carte[Pjoueur->y + 1 ][Pjoueur->x +1 ];
			en_face_plus_2 = Carte[Pjoueur->y ][Pjoueur->x +3 ];		
			diag_2_gauche = Carte[Pjoueur->y - 1 ][Pjoueur->x + 2 ];		
			diag_2_droite = Carte[Pjoueur->y + 1 ][Pjoueur->x + 2 ];		

			Affichage_blocs(en_face,en_face_plus,a_droite,a_gauche,diag_gauche,diag_droite,en_face_plus_2, diag_2_gauche,diag_2_droite);
			break;

		case 8 :
			
			en_face = Carte[Pjoueur->y - 1 ][Pjoueur->x ];
			en_face_plus = Carte[Pjoueur->y - 2 ][Pjoueur->x ];		
			a_droite = Carte[Pjoueur->y ][ Pjoueur->x + 1 ];
			a_gauche = Carte[Pjoueur->y ][Pjoueur->x - 1];
			diag_gauche = Carte[Pjoueur->y - 1 ][Pjoueur->x -1 ];
			diag_droite =Carte[Pjoueur->y - 1 ][Pjoueur->x +1 ];	
			en_face_plus_2 = Carte[Pjoueur->y - 3 ][Pjoueur->x ];		
			diag_2_gauche = Carte[Pjoueur->y - 2 ][Pjoueur->x - 1 ];		
			diag_2_droite = Carte[Pjoueur->y - 2 ][Pjoueur->x + 1 ];		

		
			Affichage_blocs(en_face,en_face_plus,a_droite,a_gauche,diag_gauche,diag_droite,en_face_plus_2, diag_2_gauche,diag_2_droite);
			break;
		
		default:
			break;

	}
}

/*
Sauvegarde la progression du joueur sur la carte.
N'affecte pas l'affichage de la carte, mais le fichier contenant la carte

Comme LireTab, mais remplit le fichier en fonction de la valeur dans la carte.
*/
void Save_Carte ( FILE* fich,int Carte[][T_MAX], int longueur, int hauteur)
{
	int i,j;
	for(i=0;i<hauteur;i=i+1)
	{
		for(j=0;j<longueur;j=j+1)
		{
			switch(Carte[i][j])
			{
				case  0:
					fputc('*',fich);
					break;
 				case  1:
					fputc('.',fich);
					break;
				case  5:
					fputc('@',fich);
					break;
				case  7:
					fputc('X',fich);
					break;
				default:
					fputc('\n',fich);
					break;
			}
		}
	} 
	
}
/*
La fonction Afficher_Carte prend en argument le tableau Carte et ses tailles.
Son principe est le suivant:
Il y a un curseur à la position 970,10.
On teste la valeur du tableau correspondant à la case.
Si la valeur est 1, c'est une case vide , ou le joueur s'est déjà déplacé, on affiche alors un rectangle blanc.
Si c'est la valeur 5, c'est la case du joueur, on l'affiche en bleu.
Sinon, on ne fait rien et elle sera en noire car le fond est noir.
On incremente alors le curseur x de 10 et on teste.
Au changement de ligne, on réinitialise le compteur x, mais on augmente le y de 10.
On continue jusqu'à atteindre la fin de la carte.

On actualise la fenêtre à la fin comme toutes les affichages.
*/
void Afficher_Carte( int Carte_a_Afficher[][T_MAX], int longueur, int hauteur)
{
	
	int i , j ;
	// Variable de la case à afficher
	Position Curseur;
	Curseur.x = 970;
	Curseur.y = 10;
	
	for ( i=0; i<hauteur; i=i+1)
	{
		// on réinitialise la variable pour partir de la gauche
		Curseur.x = 970;
		
		for( j=0;j<longueur;j=j+1)
		{
			switch ( Carte_a_Afficher[i][j] ) 
			{
				case 1:
					MLV_draw_filled_rectangle( Curseur.x, Curseur.y, 10,10, MLV_COLOR_WHITE);		
					break;

				case 5:
					MLV_draw_filled_rectangle( Curseur.x, Curseur.y, 10,10, MLV_COLOR_BLUE);	
					break;
	
				default :
					break;
			}
		Curseur.x = Curseur.x + 10;

		}

	Curseur.y = Curseur.y + 10;
	}
	MLV_actualise_window();	
}

/*
A la fin du programme, afin de pouvoir rejouer avec une carte vierge, on la réinitialise.
La case de départ prend la valeur 5 , et les autres prennent la valeur  0.
Ensuite, avec la sauvegarde, on aura la carte de départ pour l'affichage.
*/
void Reinitial_Carte_Afficher( int Carte_Affich[][T_MAX],Position Depart ,int longueur, int hauteur)
{
	int i,j;
	for(i=0;i<hauteur;i=i+1)
	{
		for(j=0;j<longueur;j=j+1)
		{
			if( i == Depart.y && j == Depart.x)
			{
				Carte_Affich[i][j] = 5;			
			}
			// On garde les cases codées avec 9, pour garder les sauts de lignes à la sauvegarde
			else if(   !(Carte_Affich[i][j] == 9) )
			{
				Carte_Affich[i][j] = 0;			
			}
		}
	}
}

int main(int argc, char *argv[]){
	int Carte[T_MAX][T_MAX];
	int Carte_Afficher[T_MAX][T_MAX];
	int Verif,VerifA,orientation,zone,x,y;
	int longueur,hauteur;
	Position PJoueur;
	Position PSortie;
	Position Depart;
	FILE* fichier_carte= NULL;
	FILE* fichier_carteA= NULL;
	// Longueur et hauteur de la carte fixées au préalable.
	longueur = 31;
	hauteur = 52;
	// Les coordonnées de la case de départ sont aussi fixées
	Depart.x = 15;
	Depart.y = 45;
	
	// On définit les coordonnées de la sortie sur -1.-1, car s'ils ne sont pas définies, le compilateur avertit qu'il risque d'y avoir une erreur.
	PSortie.x=-1;
	PSortie.y=-1;
	// L'orientation est initialisée arbitrairement vers le nord
	orientation=8;
	
	
	// Ouvre les deux fichiers afin de tester leur présence.
	
	fichier_carte=fopen("Carte","r");
	Verif=Verif_fichier(fichier_carte);

	
	fichier_carteA=fopen("CarteA","r");
	VerifA=Verif_fichier(fichier_carteA);

	
	if(Verif ==1 && VerifA == 1)
	{
		fclose(fichier_carteA);
		// Permet d'initialiser et de jouer la musique
		MLV_init_audio( );
		MLV_Music* music = MLV_load_music( "bgm.mp3" );
		MLV_play_music( music, 1.0, -1 );

		// Affecte la carte à un tableau, puis ferme le fichier
		LireTab(fichier_carte,Carte,longueur,hauteur);
		fclose(fichier_carte);
		
		printf("\n");

		// On affecte de même la carte à afficher dans un tableau, puis  on referme la carte.
		fichier_carte=fopen("CarteA","r");
		LireTab(fichier_carte,Carte_Afficher,longueur,hauteur);
		fclose(fichier_carte);

		//Récupère les positions du joueur et de la sortie, nécessaire pour les tests suivants.				
		Recup_Pos_Joueur( &PJoueur,Carte,longueur,hauteur);
		Recup_Pos_Sortie( &PSortie,Carte,longueur,hauteur);
		
		
		Affiche_cadre();
		Affiche_Boutons();

		while(  (PJoueur.x != PSortie.x ) || (PJoueur.y != PSortie.y )   )
		{

			// Affiche la Vue,la boussole,et la carte
			Vue(Carte, &PJoueur,orientation);
			Afficher_boussole(orientation);
			Afficher_Carte( Carte_Afficher,longueur,hauteur);

			// On attend le clic pour déterminer la zone et on appelle les fonctions liées aux boutons.
	 		MLV_wait_mouse(&x,&y);
			zone=zone_clic(x,y);
			switch(zone){
				// On affecte la valeur de la fonction à l'orientation pour que la valeur de celle-ci change. 
				case 7 :
					orientation=Tourner_gauche(orientation);
					break;
				case 8 :
					Bouton_avant(Carte,Carte_Afficher, &PJoueur,orientation);
					break;
				// On affecte la valeur de la fonction à l'orientation pour que la valeur de celle-ci change
				case 9:
					orientation=Tourner_droite(orientation);
					break;
				case 4 :
					Bouton_gauche(Carte,Carte_Afficher, &PJoueur,orientation);
					break;
				case 5 :
					Bouton_arriere(Carte,Carte_Afficher, &PJoueur,orientation);
					break;
				case 6 :
					Bouton_droite(Carte,Carte_Afficher, &PJoueur,orientation);
					break;

				// Bouton de sauvegarde				
				case 1:	
					// On ouvre le fichier, sauvegarde la première carte, et on ferme le  fichier
					fichier_carte=fopen("Carte","r+");
					Save_Carte( fichier_carte,Carte,longueur,hauteur);					
					fclose(fichier_carte);
	
					// De même pour le second
					fichier_carte=fopen("CarteA","r+");
					Save_Carte(fichier_carte,Carte_Afficher,longueur,hauteur);					
					fclose(fichier_carte);
				
					// On affiche une boîte de dialogue de confirmation de la sauvegarde.
					MLV_draw_adapted_text_box( 370,240, "Les données ont été sauvegardées", 9, MLV_COLOR_BLACK, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_TEXT_CENTER);
					
					MLV_actualise_window();
					MLV_wait_seconds(1);
					break;

				default:
					break;
		 	}
			
		}
		
		// Arrivé à la fin, on affiche une boîte de dialogue affichant la fin du jeu
		MLV_draw_adapted_text_box( 370,240, "Vous êtes sorti du labyrinthe\nMerci de cliquer pour sortir", 9, MLV_COLOR_BLACK, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_TEXT_CENTER);
		MLV_actualise_window();	
		MLV_wait_mouse(&x,&y);
		
		// On réinitialise ensuite les cartes

		// Réinitialise le fichier  Carte
		fichier_carte=fopen("Carte","r+");
		// Le joueur étant arrivé à la fin, sa position est celle de la sortie en temps normal.
		Carte[ PJoueur.y][PJoueur.x] = 7;
		Carte[ Depart.y] [Depart.x] = 5;
		Save_Carte( fichier_carte,Carte,longueur,hauteur);							
		fclose(fichier_carte);
 
		// Réinitialie le fichier CarteA
		fichier_carte=fopen("CarteA","r+");
		Reinitial_Carte_Afficher( Carte_Afficher,Depart,longueur,hauteur);
					Save_Carte( fichier_carte,Carte_Afficher,longueur,hauteur);					
		fclose(fichier_carte);

		// On referme la fenêtre et le périphérique audio.
		MLV_free_window();
		MLV_stop_music();
		MLV_free_music( music );
		MLV_free_audio();

	}	
	else
 	{
		printf("Il y a une erreur\nIl n'y a pas de carte à charger\n");			
	}


	return 0;
}
