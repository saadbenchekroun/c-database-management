#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct produit{
	char Design[20];
	int quantite;
	float prix;
}Produit;

void saisie(int n, Produit *stock){
	int i;
	printf("Entrer les %d produits : \n",n);
	for(i=0;i<n;i++){
		printf("Donner la designation du produit n %d: \n",i+1);
		scanf("%s",stock[i].Design);
		printf("Donner la quantite du produit n %d: \n",i+1);
		scanf("%d",&stock[i].quantite);
		printf("Donner le prix du produit n %d: \n",i+1);
		scanf("%f",&stock[i].prix);
	}	
}

void afficher(int n, Produit *stock){
	int i;
	printf("La liste des produits est : \n");
	printf("Desgnation\tQuantite\tPrix: \n");
	for(i=0;i<n;i++){
		printf("%s\t\t%d\t\t%.2f \n",stock[i].Design,stock[i].quantite,stock[i].prix);
	}
}

void produit_pc(int n, Produit *stock){
	Produit pc;
	int i;
	pc = stock[0];
	for(i=1;i<n;i++){
		if(stock[i].prix>pc.prix)
			pc = stock[i];
	}
	printf("Le produit le plus cher de notre stock est : (%s) \n", pc.Design);
}

void Trier_par_des(int n, Produit *stock){
	Produit tmp;
	Produit *ptr1, *ptr2;
	for(ptr1=stock;ptr1<stock+n;ptr1++){
		for(ptr2=ptr1+1;ptr2<stock+n;ptr2++){
			if(strcmp(ptr1->Design,ptr2->Design)>0){
				tmp = *ptr1;
				*ptr1 = *ptr2;
				*ptr2 = tmp;
			}
		}
	}
	
	printf("\n Les produits du stock apres Tri \n");
	afficher(n,stock);
}

void reexecuter_N(int n, int a, Produit *stock){
	int i;
	stock = realloc(stock,n*sizeof(int));
	printf("Entrer les %d produits existants du stock : \n",a);
	for(i=n-a;i<n;i++){
		printf("Donner la designation du produit n %d: \n",i+1);
		scanf("%s",stock[i].Design);
		printf("Donner la quantite du produit n %d: \n",i+1);
		scanf("%d",&stock[i].quantite);
		printf("Donner le prix du produit n %d: \n",i+1);
		scanf("%f",&stock[i].prix);
	}
	afficher(n,stock);
	produit_pc(n,stock);
	Trier_par_des(n,stock);
}

int main() {
	int n,a,i;
	char reponse;
	printf("Veuillez entrer le nombre de produit a ajouter dans le stock: \n");
	scanf("%d",&n);
	Produit *stock = (Produit*) malloc(n*sizeof(Produit));
	
	saisie(n,stock);
	afficher(n,stock);
	produit_pc(n,stock);
	Trier_par_des(n,stock);
	
	printf("est-ce que vous voulez effectuer une autre operation ?");
	getchar();//fflush(stdin);
	scanf("%c",&reponse);
	while(reponse!='N'){
		printf("Veuillez entrer le nombre de produit a ajouter: \n");
		scanf("%d",&a);
		n = n + a;
		for(i=0;i<n-a;i++){
			printf("--> %s ",stock[i].Design);
			printf("\n");
		}
		reexecuter_N(n,a,stock);
		printf("est-ce que vous voulez effectuer une autre operation ?");
		getchar();//fflush(stdin);
		scanf("%c",&reponse);
	}
	
    return 0;
}

