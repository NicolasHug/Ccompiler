// Initialise un tableau
void initTab (int * tab, int taille) {
  int i;
  int val = 0;
  for (i = 0; i < taille; i++) {
      *(tab + i) = i + 1;
  }
}

/* 
 * Renvoie la somme des éléments d'un tableau
 */
int somme (int * tab, int taille, int indice) {
  int nouvelIndice = indice + 1;
  if (indice == taille) {
    return 0;
  } else {
    return tab[indice] + somme(tab, taille, nouvelIndice);
  }
}

int main () {
  int taille = 10;
  int tab[10];
  int indiceDepart = 0;

  initTab(tab,taille);
  printf(somme(tab,taille,indiceDepart));
  return 0;
}
