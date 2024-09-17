#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
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

typedef struct s_element {
	Etudiant etud ;
	struct s_element *suivant;
}element;

typedef struct fil_s{
	char nom_fil[20];
	int nb_etud;
	element * debut;
	struct fil_s * next;
}Filiere;

typedef struct{
	char Dept[50];
	int nbr_fil;
	Filiere *first;
}liste_filiere;

void Creer_Filiere(Filiere *Fil){
	printf("Nom de la filiere: \n");
	scanf("%s",Fil->nom_fil);
	Fil->nb_etud=0;
	Fil->debut = NULL;
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

element* creer_element(Etudiant etudiant){
	element *e;
	e = (element *) malloc(sizeof(element));
	if(e != NULL){
		e->etud = etudiant;
		e->suivant = NULL;
	}
	return e;
}

element* acceder_element(Filiere l, int position){
	element *resultat = l.debut;//temp
	int p;
	p=0;
	while(p<position && resultat!=NULL){
		resultat = resultat->suivant;
		p++;
	}
	return resultat;
}

bool inserer_element(Filiere *l, element *e, int p){ 
	element *temp = l->debut, *avant, *apres;
	bool erreur = false;
	if(p==0){ // si on insère en position 0, on doit modifier l
		e->suivant = temp;
		l->debut = e;
		(l->nb_etud)++;//Changement
	} // sinon, on doit modifier le champ 'suivant' de l'élément précédent
	else{ 
		temp = acceder_element(*l,p-1); // on se place au bon endroit
		if(temp==NULL)	// on insère l'élément
			erreur = true;
		else{ 
			avant = temp;
			apres = temp->suivant;
			e->suivant = apres;
			avant->suivant = e;
			(l->nb_etud)++;
		}
}
return erreur;
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

void Afficher_filiere(Filiere f){
	printf("Filiere : %s \n", f.nom_fil);
	printf("Nombre des etudiants : %d \n", f.nb_etud);
	printf("Liste des etudiants: \n");
	printf("************************************************\n");
	printf("Matricule\tNom\tPrenom\tDate_Naissance\tMoyenne Generale \n");
	
	element *temp = f.debut;
	while(temp != NULL){
		Afficher_Etudiant(temp->etud);
		temp = temp->suivant;
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
	printf("La Liste des etudiants admis est : \n");
	printf("********************************************\n");
	printf("Matricule\tNom\tPrenom\tDate Naissance\tMoyenne Generale \n");
	element *temp = Fil->debut;
	while(temp != NULL){
		if(moyenne_par_etudiant(temp->etud)>=12)
			Afficher_Etudiant(temp->etud);
		temp = temp->suivant;
	}			
}

void Rechercher_par_matricule(Filiere *Fil, int matricule){
	bool trouve = false;
	element *temp = Fil->debut;
	while(temp != NULL){
		if(temp->etud.matricule==matricule){
			printf("Matricule\tNom\tPrenom\tDate Naissance\tMoyenne Generale \n");
			Afficher_Etudiant(temp->etud);
			trouve = true;
			break;
		}else{
			temp = temp->suivant;
		}	
	}
	if(!trouve)
		printf("Ce matricule ne figure pas dans la liste des etudiants \n");
}

void Rechercher_par_nom(Filiere *Fil, char *name){
	bool trouve = false;
	element *temp = Fil->debut;
	while(temp != NULL && !trouve){
		if(strcmp(temp->etud.nom,name)==0){
			printf("Matricule\tNom\tPrenom\tDate Naissance\tMoyenne Generale \n");
			Afficher_Etudiant(temp->etud);
			trouve = true;
			break;
		}else{
			temp = temp->suivant;
		}	
	}
	if(!trouve)
		printf("Ce nom ne figure pas dans la liste des etudiants \n");
}

void Trier_Filiere_per_moy(Filiere *Fil){
	element *elem_i = Fil->debut;
	while(elem_i != NULL){
		element *elem_j = elem_i->suivant;
		while(elem_j != NULL){
			if(moyenne_par_etudiant(elem_i->etud)<moyenne_par_etudiant(elem_j->etud)){
				Etudiant tmp = elem_j->etud;
				elem_j->etud = elem_i->etud;
				elem_i->etud = tmp;
			}
			elem_j = elem_j->suivant;		
		}
		elem_i = elem_i->suivant;	
	}
}

void Afficher_Majors(Filiere *Fil){
	Trier_Filiere_per_moy(Fil);
	int cmp = 0;
	element *temp = Fil->debut;
	printf("\n La liste des Majors de la filiere %s est : \n",Fil->nom_fil);
	printf("Matricule\tNom\tPrenom\tDate Naissance\tMoyenne Generale \n");
	while(temp != NULL && cmp<3){
		Afficher_Etudiant(temp->etud);
		cmp++;
		temp = temp->suivant;	
	}
}

void Trier_Tableau_per_name(Filiere *Fil){
	element *elem_i = Fil->debut;
	while(elem_i != NULL){
		element *elem_j = elem_i->suivant;
		while(elem_j != NULL){
			if(strcmp(elem_i->etud.nom,elem_j->etud.nom)==0){
				if(moyenne_par_etudiant(elem_i->etud)<moyenne_par_etudiant(elem_j->etud)){
					Etudiant tmp = elem_j->etud;
					elem_j->etud = elem_i->etud;
					elem_i->etud = tmp;
				}
			}else if(strcmp(elem_i->etud.nom,elem_j->etud.nom)>0){
				Etudiant tmp = elem_j->etud;
				elem_j->etud = elem_i->etud;
				elem_i->etud = tmp;
			}
		elem_j = elem_j->suivant;
		}
		elem_i = elem_i->suivant;
	}
	
}

void Afficher_Etu_par_nom(Filiere *Fil){
	Trier_Tableau_per_name(Fil);
	element *temp = Fil->debut;
	printf("\n La liste des etudiants tries \n");
	printf("Matricule\tNom\tPrenom\tDate Naissance\tMoyenne Generale \n");
	while(temp != NULL){
		Afficher_Etudiant(temp->etud);
		temp = temp->suivant;	
	}
}

bool supprimer_element(Filiere *l, int p){ 
	element *temp = l->debut, *e, *avant, *apres;
	bool erreur = false;
	if(p==0) {// si on supprime en position 0, on doit modifier l
		e = temp;
		if(e == NULL)
			erreur = true;
		else
			l->debut = e->suivant;
	}
	else {// sinon, on doit modifier le champ 'suivant' de l'élément précédent
		temp = acceder_element(*l,p-1); // on se place au bon endroit
		// on supprime l'élément de la liste
		if(temp==NULL)	
			erreur = true;
		else {
			avant = temp;
			e = temp->suivant;
			if(e == NULL) 
				erreur = true;
			else{
				apres = e->suivant;
				avant->suivant = apres;
			}
		}
	}
// on désalloue l'élément
if(!erreur)
	free(e);
// on termine la fonction
return erreur;
}

void supprimer_doublons(Filiere *l){
	element *temp=l->debut,*temp2;
	element *avant,*apres;
	while (temp!=NULL){
		avant = temp;
		temp2 = avant->suivant;
		while (temp2!=NULL){
			apres = temp2->suivant;
			if(temp->etud.matricule == temp2->etud.matricule){
				avant->suivant = apres;
				free(temp2);
			}
			else
				avant = temp2;
			temp2 = apres;
		}
	temp = temp->suivant;
	}
}

int copier_liste(Filiere l1, Filiere *l2){
	element *temp=l1.debut,*e;
	int erreur=0;
	int i=0;
	while(temp!=NULL && erreur!=-1){
		if((e=creer_element(temp->etud))==NULL)
			erreur = -1;
		else{
			temp = temp->suivant;
			inserer_element(l2, e, i);
			i++;
		}
	}		
return erreur;
}

void inverser(Filiere *l){
	element *temp = l->debut;
	int i;
	int n = longueur_liste(*l);
	element *first = acceder_element(*l,0);
	element *last = acceder_element(*l,n-1);
	for(i=n-1;i>0;i--){
		element *e = acceder_element(*l,i);
		e->suivant = acceder_element(*l,i-1);	
	}
	first->suivant = NULL;
	l->debut = last;
	Afficher_filiere(*l);	
}


int longueur_liste(Filiere l){
	element *temp = l.debut;
	int resultat = 0;
	while(temp != NULL){ 
		resultat++;
		temp = temp->suivant;
	}
return resultat;
}

/******************************************************************/

void Creer_Liste_Filiere(liste_filiere *liste){
	printf("Nom du Departement: \n");
	gets(liste->Dept);
	liste->nbr_fil = 0;
	liste->first = NULL;
}

int rechercher_filiere(liste_filiere l, char *nomFil){ 
	int i = 0;
	int pos = -1;
	Filiere *temp = l.first;
	while(pos==-1 && temp!=NULL){
		if(strcmp(temp->nom_fil,nomFil)>0)
			pos = i;
		else{
			temp = temp->next;
			i++;
		}
	}
return pos;
}

Filiere* acceder_filiere(liste_filiere l, int position){
	Filiere *resultat = l.first;//temp
	int p;
	p=0;
	while(p<position && resultat!=NULL){
		resultat = resultat->next;
		p++;
	}
	return resultat;
}

bool inserer_filiere(liste_filiere *l, Filiere *f){ 
	Filiere *temp = l->first, *avant, *apres;
	bool erreur = false;
	int p;
	if(l->nbr_fil==0){
		f->next = temp;
		l->first = f;
		(l->nbr_fil)++;
	}else{
		p = rechercher_filiere(*l,f->nom_fil);
		if(p==0){ // si on insère en position 0, on doit modifier l
			f->next = temp;
			l->first = f;
			(l->nbr_fil)++;
		}
		else if(p==-1){
			temp = acceder_filiere(*l,(l->nbr_fil)-1);
			if(temp==NULL)	// on insère l'élément
				erreur = true;
			else{
				f->next = NULL;
				temp->next = f;
				(l->nbr_fil)++;
			}
		}
		else{ 
			temp = acceder_filiere(*l,p-1); // on se place au bon endroit
			if(temp==NULL)	// on insère l'élément
				erreur = true;
			else{ 
				avant = temp;
				apres = temp->next;
				f->next = apres;
				avant->next = f;
				(l->nbr_fil)++;
			}
	}
}
return erreur;
}

void Trier_Liste_Filieres(liste_filiere *liste_filieres){
	Filiere *fil_i = liste_filieres->first;
	while(fil_i != NULL){
		Filiere *fil_j = fil_i->next;
		while(fil_j != NULL){
			if(fil_i->nb_etud<fil_j->nb_etud){
				Filiere tmp = fil_j;
				fil_j = fil_i;
				fil_i->tmp;
			}
			fil_j = fil_j->suivant;		
		}
		fil_i = fil_i->suivant;	
	}
}

int main() {

int val,i,n;
/*bool res_ins = false;
Filiere *fil = (Filiere*) malloc(sizeof(Filiere));
Creer_Filiere(fil);

printf("nbr d\'elements \n");
scanf("%d",&n);
for(i=0;i<n;i++){
	Etudiant *etud = (Etudiant*) malloc(sizeof(Etudiant));
	Saisir_Etudiant(etud);
	element * elem = creer_element(*etud);
	res_ins = inserer_element(fil,elem,0);
	if(!res_ins)
  		printf("Insertion avec succes \n");
  	else
  		printf("Erreur d\'insertion \n");
}*/

//Afficher_filiere(*fil);
//Etudiants_Admis(fil);
//Rechercher_par_matricule(fil,1234);
//Rechercher_par_nom(fil,"NOM1");
//Rechercher_par_nom(fil,"NOM2");

//Trier_Filiere_per_moy(fil);
//Afficher_filiere(*fil);
//Afficher_Majors(fil);


liste_filiere *liste_filieres = (liste_filiere*) malloc(sizeof(liste_filiere));
Creer_Liste_Filiere(liste_filieres);

printf("nbr de filieres \n");
scanf("%d",&n);
for(i=0;i<n;i++){
	bool res_ins = false;
	Filiere *fil = (Filiere*) malloc(sizeof(Filiere));
	Creer_Filiere(fil);
	inserer_filiere(liste_filieres,fil);
	
}

Filiere *tmp = liste_filieres->first;
while(tmp != NULL){
	printf("%s--->\n",tmp->nom_fil);
	printf("NBR_ETD : %d",tmp->nb_etud);
	tmp = tmp->next;
}	

return 0;
  
}



