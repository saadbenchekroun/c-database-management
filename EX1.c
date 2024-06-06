#include <stdio.h>

int puissance_Iter(int base, int exposant) {
	int i, resultat = 1;
  	for (i= 0; i < exposant; i++){
    	resultat *= base;
  	}
  	return resultat;
}

int puissance_Rec(int base, int exposant) {
  	if (exposant==0){
    return 1;
  	}
  	return base * puissance_Rec(base, exposant - 1);
}

int main() {
  int base, exposant;
  printf("Entrez la base: ");
  scanf("%d", &base);
  printf("Entrez l'exposant: ");
  scanf("%d", &exposant);
  printf("Iteratif : %d^%d = %d\n", base, exposant, puissance_Iter(base, exposant));
  printf("Recursive : %d^%d = %d\n", base, exposant, puissance_Rec(base, exposant));
  //printf("%.lf^%d = %.lf\n", base, exposant, puissance_Rec(base, exposant));
  return 0;
}



