#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct joueur{
	char prenom[10];
	char nom[10];
	short age;
	short niveau;
}Joueur;

typedef struct equipe{
	char nom[10];
	Joueur joueur1;
	Joueur joueur2;
}Equipe;

void AddPlayer(Joueur *j){
	printf("Entrer le prenom : ");
	scanf("%s",j->prenom);
	printf("Entrer le nom : ");
	scanf("%s",j->nom);
	printf("Entrer l'age : ");
	scanf("%d",&j->age);
	do{
		printf("Entrer le niveau : ");
		scanf("%d",&j->niveau);
	}while(j->niveau<0 || j->niveau>10);
	
}

void AddTeam(Equipe *e){
	printf("Entrer le nom : ");
	scanf("%s",e->nom);
	printf("joueur 1 : \n");
	AddPlayer(&e->joueur1);
	printf("joueur 2 : \n");
	AddPlayer(&e->joueur2);
}

void afficher_joueur(Joueur j){
	printf("\tprenom : %s\n",j.prenom);
	printf("\tnom : %s\n",j.nom);
	printf("\tage : %d\n",j.age);
	printf("\tniveau : %d\n",j.niveau);
}

void afficher_equipe(Equipe e){
	printf("nom : %s\n",e.nom);
	printf("joueur 1 :\n");
	afficher_joueur(e.joueur1);
	printf("joueur 2 :\n");
	afficher_joueur(e.joueur2);
}

void match(Equipe *e1, Equipe *e2){
	short level1 = 0, level2 = 0;
	level1 = e1->joueur1.niveau + e1->joueur2.niveau;
	level2 = e2->joueur1.niveau + e2->joueur2.niveau;
	printf("Level 1 - Level 2 : Score --> %d - %d : (%d) ",level1, level2, level1-level2);
}

int main(){
	int n, i;
    printf("Veuillez entrer le nombre d\'equipes a ajouter: \n");
	scanf("%d",&n);
	
	Equipe *equipes = calloc(n,sizeof(Equipe));
	
	for(i=0;i<n;i++){
		printf("L\'equipe %d :\n",i+1);
		AddTeam(equipes+i);
	}
	
	for(i=0;i<n;i++){
		printf("L\'equipe %d :\n",i+1);
		afficher_equipe(equipes[i]);
	}
	match(equipes,equipes+1);
	
	
	free(equipes);
}




