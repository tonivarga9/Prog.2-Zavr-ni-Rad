#define _CRT_SECURE_NO_WARNINGS

#include "header.h"

int main() {
    int izbor;
    ucitajIzDatoteke();

    do {
        prikaziIzbornik();
        scanf("%d", &izbor);

        switch (izbor) {
        case OPCIJA_DODAJ: dodajParfem(); break;
        case OPCIJA_PREGLED: prikaziParfeme(); break;
        case OPCIJA_AZURIRAJ: azurirajParfem(); break;
        case OPCIJA_OBRISI: obrisiParfem(); break;
        case OPCIJA_SORTIRAJ: sortirajParfeme(); break;
        case OPCIJA_PRETRAZI: pretraziParfem(); break;
        case OPCIJA_IZLAZ: oslobodiMemoriju(); break;
        default: printf("Nepoznata opcija.\n"); break;
        }

    } while (izbor != OPCIJA_IZLAZ);

    return 0;
}
