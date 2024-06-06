#include <stdio.h>
#include <string.h>

void inverser(char *debut, char *fin) {
  char temp;
  if (debut < fin) {
    temp = *debut;
    *debut = *fin;
    *fin = temp;
    inverser(debut + 1, fin - 1);
  }
}

int main(){
	char mot[50];
	char c;
	printf("Veuillez saisir le mot:\n");
	gets(mot);

	inverser(mot, mot + strlen(mot) - 1);
	printf("%s\n", mot);
	return 0;
}
