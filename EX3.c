#include<stdio.h>
#include<stdlib.h>

void saisie(int n, int *Tab){
	int i;
	printf("Entrer les %d elements du tableau : \n",n);
	for(i=0;i<n;i++){
		printf("Tab[%d]= ",i);
		scanf("%d",Tab+i);
	}	
}

void afficher(int n, int *Tab){
	int i;
	printf("\n Les elements du tableau Tab sont \n");
	
	for(i=0;i<n;i++){
		printf("--> %d ", *(Tab+i));
		printf("\n");
	}
}

/****** Déclaration des Fonctions Minimum du Tableau *******/

void minimum(int n, int *Tab){
	int min, i;
	min = *Tab;
	for(i=1;i<n;i++){
		if(Tab[i]<min)
			min = Tab[i];
	}
	printf("le minimum du Tableau Tab est %d : \n", min);
	//return min;
}

/****** Déclaration des Fonctions Maximum du Tableau *******/

void maximum(int n, int *Tab){
	int max, i;
	max = *Tab;
	for(i=1;i<n;i++){
		if(Tab[i]>max)
			max = Tab[i];
	}
	printf("le maximum du Tableau Tab est %d : \n", max);
	//return max;
}

/****** Déclaration des Fonctions Maximum du Tableau *******/

void moyenne(int n, int *Tab){
	float moy;
	int i, somme = 0;
	//somme = *Tab;
	for(i=0;i<n;i++){
		somme += Tab[i];
	}
	moy = (float)somme/n;
	printf("la moyenne du Tableau Tab est %.2f : \n", moy);
	//return max;
}
void Trier(int n, int *T){
	int tmp;
	int *ptr1, *ptr2;
	for(ptr1=T;ptr1<T+n;ptr1++){
		for(ptr2=ptr1+1;ptr2<T+n;ptr2++){
			if(*ptr1>*ptr2){
				tmp = *ptr1;
				*ptr1 = *ptr2;
				*ptr2 = tmp;
			}
		}
	}
	printf("Les elements du Tableau après le Tri \n");
	afficher(n,T);
}

void reexecuter_N(int n, int a, int *Tab){
	int i;
	Tab = realloc(Tab,n*sizeof(int));
	printf("Entrer les %d autres elements du tableau : \n",a);
	for(i=n-a;i<n;i++){
		printf("Tab[%d]= ",i);
		scanf("%d",Tab+i);
	}
	afficher(n,Tab);
	maximum(n,Tab);
	minimum(n,Tab);
	moyenne(n,Tab);
	Trier(n,Tab);
}


int main(){
	char reponse;
	int n, a, i;
	printf("Veuillez entrer le nombre d\'elements a saisir: \n");
	scanf("%d",&n);
	
	int *Tab = calloc(n,sizeof(int));
	saisie(n,Tab);
	afficher(n,Tab);
	maximum(n,Tab);
	minimum(n,Tab);
	moyenne(n,Tab);
	Trier(n,Tab);
	printf("est-ce que vous voulez effectuer une autre operation ?");
	getchar();//fflush(stdin);
	scanf("%c",&reponse);
	while(reponse!='N'){
		printf("Veuillez entrer le nombre d\'elements a saisir: \n");
		scanf("%d",&a);
		n = n + a;
		for(i=0;i<n-a;i++){
			printf("--> %d ", *(Tab+i));
			printf("\n");
		}
		reexecuter_N(n,a,Tab);
		printf("est-ce que vous voulez effectuer une autre operation ?");
		getchar();//fflush(stdin);
		scanf("%c",&reponse);
	}
	return 0;
	
}
