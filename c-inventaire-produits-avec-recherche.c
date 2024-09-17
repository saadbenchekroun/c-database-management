#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

typedef struct produit{
	char Design[21];
	int qte;
	float prix;
}Produit;

typedef struct s_element {
	Produit prod ;
	struct s_element *suivant;
}element;

typedef struct stock_l{
	int nbr_prod;
	element * debut;
}Stock;

void Creer_Stock(Stock *stock){
	stock->nbr_prod=0;
	stock->debut = NULL;
}

void Saisir_Produit(Produit *p) {
	printf("\t Saisir la designation du produit : \n");
	scanf("%s", p->Design);
	printf("\t Saisir la qunatite du produit : \n");
	scanf("%d", &p->qte);
	printf("\t Saisir le prix du produit : :\n");
	scanf ("%f", &p->prix);
}

element* creer_element(Produit produit){
	element *e;
	e = (element *) malloc(sizeof(element));
	if(e != NULL){
		e->prod = produit;
		e->suivant = NULL;
	}
	return e;
}

element* acceder_element(Stock s, int position){
	element *resultat = s.debut;//temp
	int p;
	p=0;
	while(p<position && resultat!=NULL){
		resultat = resultat->suivant;
		p++;
	}
	return resultat;
}

bool inserer_element(Stock *s, element *e, int p){ 
	element *temp = s->debut, *avant, *apres;
	bool erreur = false;
	if(p==0){ // si on insère en position 0, on doit modifier l
		e->suivant = temp;
		s->debut = e;
		(s->nbr_prod)++;//Changement
	} // sinon, on doit modifier le champ 'suivant' de l'élément précédent
	else{ 
		temp = acceder_element(*s,p-1); // on se place au bon endroit
		if(temp==NULL)	// on insère l'élément
			erreur = true;
		else{ 
			avant = temp;
			apres = temp->suivant;
			e->suivant = apres;
			avant->suivant = e;
			(s->nbr_prod)++;
		}
}
return erreur;
}

int rechercher_produit(Stock s, char *desg){ 
	int i = 0;
	int pos = -1;
	element *temp = s.debut;
	while(pos==-1 && temp!=NULL){
		if(strcmp(temp->prod.Design,desg)>0)
			pos = i;
		else{
			temp = temp->suivant;
			i++;
		}
	}
return pos;
}

bool inserer_produit(Stock *s, Produit *prod){ 
	element *temp = s->debut, *avant, *apres;
	element *e = creer_element(*prod);
	bool erreur = false;
	int p;
	if(s->nbr_prod==0){
		e->suivant = temp;
		s->debut = e;
		(s->nbr_prod)++;
	}else{
		p = rechercher_produit(*s,e->prod.Design);
		if(p==0){ // si on insère en position 0, on doit modifier l
			e->suivant = temp;
			s->debut = e;
			(s->nbr_prod)++;
		}
		else if(p==-1){
			temp = acceder_element(*s,(s->nbr_prod)-1);
			if(temp==NULL)	// on insère l'élément
				erreur = true;
			else{
				e->suivant = NULL;
				temp->suivant = e;
				(s->nbr_prod)++;
			}
		}
		else{ 
			temp = acceder_element(*s,p-1); // on se place au bon endroit
			if(temp==NULL)	// on insère l'élément
				erreur = true;
			else{ 
				avant = temp;
				apres = temp->suivant;
				e->suivant = apres;
				avant->suivant = e;
				(s->nbr_prod)++;
			}
	}
}
return erreur;
}

void Afficher_Produit(Produit p) {
	printf("%s\t\t%d\t%.2f \n", p.Design,p.qte,p.prix);	
}

void Afficher_Stock(Stock s){
	printf("Nombre de produits : %d \n", s.nbr_prod);
	printf("Liste des produits: \n");
	printf("************************************************\n");
	printf("Designation\tQuantite\tPrix \n");
	
	element *temp = s.debut;
	while(temp != NULL){
		Afficher_Produit(temp->prod);
		temp = temp->suivant;
	}
}

void produit_pl_cher(Stock s){
	element *temp = s.debut;
	float max = 0.0;
	element *cher;
	while(temp != NULL){
		if(temp->prod.prix>max){
			max = temp->prod.prix;
			cher = temp;
		}
		temp = temp->suivant;
	}
	Afficher_Produit(temp->prod);
}



/******************************************************************/



int main() {

int i,n;
bool res_ins = false;
Stock *stock = (Stock*) malloc(sizeof(Stock));
Creer_Stock(stock);

printf("Entrer le nombre de produits \n");
scanf("%d",&n);
for(i=0;i<n;i++){
	Produit *prod = (Produit*) malloc(sizeof(Produit));
	Saisir_Produit(prod);
	element * elem = creer_element(*prod);
	res_ins = inserer_produit(stock,prod);
	if(!res_ins)
  		printf("Insertion avec succes \n");
  	else
  		printf("Erreur d\'insertion \n");
}

Afficher_Stock(*stock);
produit_pl_cher(*stock);



return 0;
  
}



