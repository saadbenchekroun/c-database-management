#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct s_element {
	int valeur ;
	struct s_element *suivant;
}element;

typedef struct {
	element *debut;
}liste;

void Creer_Liste(liste *l){
	l->debut = NULL;
}

element* creer_element(int valeur){
	element *e;
	e = (element *) malloc(sizeof(element));
	if(e != NULL){
		e->valeur = valeur;
		e->suivant = NULL;
	}
	return e;
}

element* acceder_element(liste l, int position){
	element *resultat = l.debut;//temp
	int p;
	p=0;
	while(p<position && resultat!=NULL){
		resultat = resultat->suivant;
		p++;
	}
	return resultat;
}

bool inserer_element(liste *l, element *e, int p){ 
	element *temp = l->debut, *avant, *apres;
	bool erreur = false;
	if(p==0){ // si on insère en position 0, on doit modifier l
		e->suivant = temp;
		l->debut = e;
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
		}
}

return erreur;
}

bool supprimer_element(liste *l, int p){ 
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

void affiche_liste(liste l){
	element *temp = l.debut;
	printf("{");
	while(temp != NULL){
		printf(" %d", temp->valeur);
		temp = temp->suivant;
	}
	printf(" }\n");
}

int longueur_liste(liste l){
	element *temp = l.debut;
	int resultat = 0;
	while(temp != NULL){ 
		resultat++;
		temp = temp->suivant;
	}
return resultat;
}

int recherche_valeur(liste l, int v){ 
	int i = 0;
	int pos = -1;
	element *temp = l.debut;
	while(pos==-1 && temp!=NULL){
		if(temp->valeur == v)
			pos = i;
		else{
			temp = temp->suivant;
			i++;
		}
	}
return pos;
}

void supprimer_doublons(liste l){
	element *temp=l.debut,*temp2;
	element *avant,*apres;
	while (temp!=NULL){
		avant = temp;
		temp2 = avant->suivant;
		while (temp2!=NULL){
			apres = temp2->suivant;
			if(temp->valeur == temp2->valeur){
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

void afficher_liste_recursif(liste l){
	element *temp = l.debut;
	liste l_bis;
	if(temp != NULL){
		printf("%d ",temp->valeur);
		l_bis.debut = temp->suivant;
		afficher_liste_recursif(l_bis);
	}
}

int copier_liste(liste l1, liste *l2){
	element *temp=l1.debut,*e;
	int erreur=0;
	int i=0;
	while(temp!=NULL && erreur!=-1){
		if((e=creer_element(temp->valeur))==NULL)
			erreur = -1;
		else{
			temp = temp->suivant;
			inserer_element(l2, e, i);
			i++;
		}
	}		
return erreur;
}

void inverser(liste *l){
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
	affiche_liste(*l);	
}

int main() {

int val,i,n;
bool res_ins = false;
liste *l = (liste*) malloc(sizeof(liste));
Creer_Liste(l);
printf("nbr d\'elements \n");
scanf("%d",&n);
for(i=0;i<n;i++){
	printf("Veuillez inserer la valeur de l\'element \n");
	scanf("%d",&val);
	element* e = creer_element(val);
	res_ins = inserer_element(l,e,0);
	if(!res_ins)
  		printf("Insertion avec succes \n");
  	else
  		printf("Erreur d\'insertion \n");
}

affiche_liste(*l);
inverser(l);
return 0;
  
}



