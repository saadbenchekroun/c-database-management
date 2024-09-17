#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct date{
	int jour;
	int mois;
	int annee;
}Date;

typedef struct etudiant{
	int matricule;
	char nom[21], prenom[21];
	Date date_naissance;
	float notes[3];
}Etudiant;

typedef struct tab_Filiere{
	char nom_fil[20] ; // nom filière
	int nb_etud; // nombre d'étudiants
	Etudiant etudiants[100]; // tableau d'étudiants
}Filiere;

void Ajouter_Filiere(Filiere *Fil){
	printf("Nom de la filiere: \n");
	gets(Fil->nom_fil);
	Fil->nb_etud=0;
}

void Saisir_Etudiant(Etudiant *e) {
	int i;
	printf("\t Donner le matricule de l\'etudiant : ");
	scanf("%d", &e->matricule);
	printf("\t Donner le nom de l\'etudiant : ");
	scanf("%s", e->nom); // gets(e->nom);
	printf("\t Donner prenom de l\'etudiant : ");
	scanf("%s", e->prenom); // gets(e->prenom);
	printf("\t Donner date naissance de l\'etudiant :\n");
	printf ("\t Donner le jour : ");
	scanf ("%d", &e->date_naissance.jour);
	printf("\t Donner le mois : ");
	scanf("%d", &e->date_naissance.mois);
	printf("\t Donner l'annee : ");
	scanf("%d", &e->date_naissance.annee);
	for(i=0; i<3;i++){
		printf("Donner Note[%d]:",i);
		scanf("%f", &e->notes[i]);
	}	
}

void Afficher_Etudiant(Etudiant e) {
	int i;
	int somme = 0;
	float moy = 0.0;
	for(i=0; i<3;i++)
		somme+=e.notes[i];
	moy = (float)somme/3;
	printf("%d\t\t%s\t%s\t%d/%d/%d\t%.2f \n", e.matricule,e.nom,e.prenom,e.date_naissance.jour, 
	e.date_naissance.mois, e.date_naissance.annee,moy);
		
}

void Ajouter_Etudiant(Filiere *Fil){
	if(Fil->nb_etud==100){
		printf("Desole, le tableau des etudiants est plein");
		system("pause");
	}
	else{
		printf("Entrer les information de l\'etudiant (%d) \n",(Fil->nb_etud)+1);
		Saisir_Etudiant(&Fil->etudiants[Fil->nb_etud]);
		(Fil->nb_etud)++;
	}	
}

void Afficher_Filiere(Filiere *Fil) {
	int i;
	printf("Filiere : %s \n", Fil->nom_fil);
	printf("Nombre des etudiants : %d \n", Fil->nb_etud);
	printf("Liste des etudiants: \n");
	printf("************************************************\n");
	printf("Matricule\tNom\tPrenom\tDate_Naissance\tMoyenne Generale \n");
	for(i=0;i<Fil->nb_etud;i++){
		Afficher_Etudiant(Fil->etudiants[i]);
	}
			
}

float moyenne_par_etudiant(Etudiant e){
	int i;
	int somme = 0;
	float moy = 0.0;
	for(i=0;i<3;i++)
		somme+=e.notes[i];
	moy= (float)somme/3;
	return moy;
}

void Etudiants_Admis(Filiere *Fil) {
	int i;
	
	printf("La Liste des etudiants admis est : \n");
	printf("********************************************\n");
	printf("Matricule\tNom\tPrenom\tDate Naissance\tMoyenne Generale \n");
	for(i=0;i<Fil->nb_etud;i++){
		if(moyenne_par_etudiant(Fil->etudiants[i])>=12)
			Afficher_Etudiant(Fil->etudiants[i]);
	}			
}

void Rechercher_par_matricule(Filiere *Fil, int matricule){
	int i;
	for(i=0;i<Fil->nb_etud;i++){
		if(Fil->etudiants[i].matricule==matricule){
			printf("Matricule\tNom\tPrenom\tDate Naissance\tMoyenne Generale \n");
			Afficher_Etudiant(Fil->etudiants[i]);
		}
			
	}
}

void Rechercher_par_nom(Filiere *Fil, char *name){
	int i;
	for(i=0;i<Fil->nb_etud;i++){
		if(strcmp(Fil->etudiants[i].nom,name)==0){
			printf("Matricule\tNom\tPrenom\tDate Naissance\tMoyenne Generale \n");
			Afficher_Etudiant(Fil->etudiants[i]);
		}else{
			printf("Ce nom ne figure pas dans la liste des etudiants \n");
		}
			
	}
}

void Trier_Tableau(Etudiant *Tab, int n){
	int i,j;
	Etudiant tmp;
	for(i=0;i<n;i++){
		for(j=i+1;j<n;j++){
			if(moyenne_par_etudiant(Tab[i])<moyenne_par_etudiant(Tab[j])){
				tmp = Tab[j];
				Tab[j]=Tab[i];
				Tab[i]=tmp;	
			}
		}
	}
}

void Trier_Tableau_per_name(Etudiant *Tab, int n){
	int i,j;
	Etudiant tmp;
	for(i=0;i<n;i++){
		for(j=i+1;j<n;j++){
			if(strcmp(Tab[i].nom,Tab[j].nom)==0){
				if(moyenne_par_etudiant(Tab[i])<moyenne_par_etudiant(Tab[j])){
					tmp = Tab[j];
					Tab[j]=Tab[i];
					Tab[i]=tmp;	
				}
			}else if(strcmp(Tab[i].nom,Tab[j].nom)>0){
					tmp = Tab[j];
					Tab[j]=Tab[i];
					Tab[i]=tmp;	
			}			
		}
	}
}

void Afficher_Majors(Filiere *Fil){
	Trier_Tableau(Fil->etudiants,Fil->nb_etud);
	int i;
	printf("\n La liste des Majors de la filiere %s est : \n",Fil->nom_fil);
	printf("Matricule\tNom\tPrenom\tDate Naissance\tMoyenne Generale \n");
	for(i=0;i<3;i++){
		Afficher_Etudiant(Fil->etudiants[i]);	
	}
}

void Afficher_Etu_par_nom(Filiere *Fil){
	Trier_Tableau_per_name(Fil->etudiants,Fil->nb_etud);
	int i;
	printf("\n La liste des etudiants tries \n");
	printf("Matricule\tNom\tPrenom\tDate Naissance\tMoyenne Generale \n");
	for(i=0;i<Fil->nb_etud;i++){
		Afficher_Etudiant(Fil->etudiants[i]);	
	}
}

int main() {
	int i;int mat;
	char nom_etd[20];
	Filiere *Fil = (Filiere*) malloc(sizeof(Filiere));
	printf("Veuillez entrer les informations de la filiere: \n");
	printf("*************************************************\n");
	
	/**********Ajouter Filiere*********************/
	Ajouter_Filiere(Fil);
	
	/**********  Ajouter des Etudiants à la Filiere ******************/
	for(i=0;i<5;i++){
		Ajouter_Etudiant(Fil);
	}
	
	/**********  Afficher les details de la Filiere ******************/
	//Afficher_Filiere(Fil);
	
	/**********  Afficher la liste des Etudiants Admis ******************/
	//Etudiants_Admis(Fil);
	
	/*****************Recherche*****************************/
	//printf("Veuillez saisir le matricule de l\'etudiant : \n");
	//scanf("%d",&mat);
	//Rechercher_par_matricule(Fil,mat);
	//printf("Veuillez saisir le nom de l\'etudiant : \n");
	//scanf("%s",nom_etd);
	//Rechercher_par_nom(Fil,nom_etd);
	
	/***************Majors************************************/
	//Afficher_Majors(Fil);
	
	/***************Trier Les Etudiants par Noms************************************/
	//Afficher_Etu_par_nom(Fil);
	
	free(Fil);
    return 0;
}

