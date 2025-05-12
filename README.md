//* HEADER
#define _CRT_SECURE_NO_WARNINGS

#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAKS_NAZIV 50
#define DATOTEKA "skladiste_douglas.dat"

// ENUMI
typedef enum {
    OPCIJA_DODAJ = 1,
    OPCIJA_PREGLED,
    OPCIJA_AZURIRAJ,
    OPCIJA_OBRISI,
    OPCIJA_SORTIRAJ,
    OPCIJA_PRETRAZI,
    OPCIJA_IZLAZ
} IzbornikOpcija;

typedef enum {
    STATUS_AKTIVAN = 1,
    STATUS_OBRISAN = 0
} StatusParfem;

// STRUKTURA
typedef struct {
    int sifra;
    char naziv[MAKS_NAZIV];
    int kolicina;
    float cijena;
    StatusParfem status;
} Parfem;

// GLOBALNE PROMJENJIVE
extern Parfem* parfemi;
extern size_t brojParfema;

// DEKLARACIJE FUNKCIJA
void prikaziIzbornik();
void dodajParfem();
void prikaziParfeme();
void azurirajParfem();
void obrisiParfem();
void sortirajParfeme();
void pretraziParfem();
void ucitajIzDatoteke();
void spremiUDatoteku();
void oslobodiMemoriju();

int usporediNaziv(const void*, const void*);
int usporediSifre(const void*, const void*);
Parfem* traziParfemPoSifri(int sifra);

#endif






//FUNKCIJE 

#define _CRT_SECURE_NO_WARNINGS

#include "header.h"

Parfem* parfemi = NULL;
size_t brojParfema = 0;

void prikaziIzbornik() {
   
    printf("\n=========================================\n");
    printf("||      IZBORNIK PARFEMERIJE DOUGLAS   ||\n");
    printf("=========================================\n");
    printf("|| 1. Dodaj novi parfem                ||\n");
    printf("|| 2. Prikazi sve parfeme              ||\n");
    printf("|| 3. Azuriraj postojeci parfem        ||\n");
    printf("|| 4. Obriši parfem                    ||\n");
    printf("|| 5. Sortiraj parfeme                 ||\n");
    printf("|| 6. Pretraži parfem po nazivu        ||\n");
    printf("|| 7. Izlaz iz aplikacije              ||\n");
    printf("=========================================\n");
    printf("Unesite svoj odabir: ");
}

void dodajParfem() {
    parfemi = realloc(parfemi, (brojParfema + 1) * sizeof(Parfem));
    if (!parfemi) {
        perror("Greska kod alokacije memorije");
        return;
    }

    printf("Unesi šifru parfema: ");
    scanf("%d", &parfemi[brojParfema].sifra);
    printf("Unesi naziv parfema: ");
    scanf(" %[^\n]", parfemi[brojParfema].naziv);
    printf("Unesi količinu: ");
    scanf("%d", &parfemi[brojParfema].kolicina);
    printf("Unesi cijenu: ");
    scanf("%f", &parfemi[brojParfema].cijena);

    parfemi[brojParfema].status = STATUS_AKTIVAN;
    brojParfema++;

    spremiUDatoteku();
}

void prikaziParfeme() {
    for (size_t i = 0; i < brojParfema; i++) {
        if (parfemi[i].status == STATUS_AKTIVAN) {
            printf("\nSifra: %d\nNaziv: %s\nKolicina: %d\nCijena: %.2f EUR\n",
                parfemi[i].sifra, parfemi[i].naziv, parfemi[i].kolicina, parfemi[i].cijena);
        }
    }
}

void azurirajParfem() {
    int sifra;
    printf("Unesi šifru parfema za ažuriranje: ");
    scanf("%d", &sifra);

    Parfem* p = traziParfemPoSifri(sifra);
    if (p && p->status == STATUS_AKTIVAN) {
        printf("Unesi novi naziv: ");
        scanf(" %[^\n]", p->naziv);
        printf("Unesi novu količinu: ");
        scanf("%d", &p->kolicina);
        printf("Unesi novu cijenu: ");
        scanf("%f", &p->cijena);
        spremiUDatoteku();
    }
    else {
        printf("Parfem nije pronađen.\n");
    }
}

void obrisiParfem() {
    int sifra;
    printf("Unesi šifru parfema za brisanje: ");
    scanf("%d", &sifra);

    Parfem* p = traziParfemPoSifri(sifra);
    if (p && p->status == STATUS_AKTIVAN) {
        p->status = STATUS_OBRISAN;
        spremiUDatoteku();
    }
    else {
        printf("Parfem nije pronađen.\n");
    }
}

void sortirajParfeme() {
    qsort(parfemi, brojParfema, sizeof(Parfem), usporediNaziv);
    printf("Sortirano po nazivu.\n");
}

void pretraziParfem() {
    int sifra;
    printf("Unesi šifru parfema za pretragu: ");
    scanf("%d", &sifra);

    Parfem* p = traziParfemPoSifri(sifra);
    if (p && p->status == STATUS_AKTIVAN) {
        printf("Naziv: %s, Količina: %d, Cijena: %.2f\n", p->naziv, p->kolicina, p->cijena);
    }
    else {
        printf("Parfem nije pronađen.\n");
    }
}

void ucitajIzDatoteke() {
    FILE* dat = fopen(DATOTEKA, "rb");
    if (!dat) return;

    fread(&brojParfema, sizeof(size_t), 1, dat);
    parfemi = malloc(brojParfema * sizeof(Parfem));
    fread(parfemi, sizeof(Parfem), brojParfema, dat);
    fclose(dat);
}


}
