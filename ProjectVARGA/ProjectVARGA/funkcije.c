#define _CRT_SECURE_NO_WARNINGS
#include "header.h"

Parfem* parfemi = NULL;
size_t brojParfema = 0;
size_t kapacitetParfema = 0;

void prikaziIzbornik(void) {
    printf("\n--- Skladiste Parfumerije Douglas ---\n");
    printf("1.        Dodaj parfem\n");
    printf("2.       Prikazi parfeme\n");
    printf("3.       Azuriraj parfem\n");
    printf("4.       Obrisi parfem\n");
    printf("5.     Sortiraj parfeme\n");
    printf("6.     Pretrazi parfeme\n");
    printf("7.    Upravljanje datotekama\n");
    printf("8.          Izlaz\n");
    printf("Unesite opciju: ");
}

void prikaziPodizbornikSort(void) {
    printf("\n--- Sortiranje ---\n");
    printf("1. Sortiraj po nazivu\n");
    printf("2. Sortiraj po cijeni\n");
    printf("3. Sortiraj po statusu\n");
    printf("4. Nazad\n");
    printf("Unesite opciju: ");
}

void prikaziPodizbornikPretraga(void) {
    printf("\n--- Pretraga ---\n");
    printf("1. Pretrazi po nazivu\n");
    printf("2. Pretrazi po sifri\n");
    printf("3. Nazad\n");
    printf("Unesite opciju: ");
}

void prikaziPodizbornikDatoteke(void) {
    printf("\n--- Upravljanje datotekama ---\n");
    printf("1. Obrisi datoteku\n");
    printf("2. Preimenuj datoteku\n");
    printf("3. Kopiraj datoteku\n");
    printf("4. Nazad\n");
    printf("Unesite opciju: ");
}

static void povecajKapacitet(void) {
    size_t noviKapacitet = (kapacitetParfema == 0) ? 2 : kapacitetParfema * 2;
    Parfem* privremeno = realloc(parfemi, noviKapacitet * sizeof(Parfem));
    if (!privremeno) {
        perror("Greska pri alokaciji memorije");
        exit(EXIT_FAILURE);
    }
    parfemi = privremeno;
    kapacitetParfema = noviKapacitet;
}

void dodajParfem(void) {
    if (brojParfema == kapacitetParfema) {
        povecajKapacitet();
    }

    Parfem novi;
    printf("Unesite sifru parfema: ");
    if (scanf("%d", &novi.sifra) != 1) {
        printf("Neispravan unos.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    printf("Unesite naziv parfema: ");
    if (!fgets(novi.naziv, sizeof(novi.naziv), stdin)) {
        printf("Greska pri unosu naziva.\n");
        return;
    }
    novi.naziv[strcspn(novi.naziv, "\n")] = 0;  // ukloni novi red

    printf("Unesite kolicinu: ");
    if (scanf("%d", &novi.kolicina) != 1) {
        printf("Neispravan unos.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    printf("Unesite cijenu: ");
    if (scanf("%f", &novi.cijena) != 1) {
        printf("Neispravan unos.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    novi.status = STATUS_AKTIVAN;

    parfemi[brojParfema++] = novi;
    printf("Parfem uspjesno dodan.\n");

    spremiUDatoteku();
}

void prikaziParfeme(void) {
    if (brojParfema == 0) {
        printf("Nema parfema za prikaz.\n");
        return;
    }
    printf("\n--- Popis parfema ---\n");
    for (size_t i = 0; i < brojParfema; i++) {
        Parfem* p = &parfemi[i];
        if (!isActive(p->status)) continue;
        printf("Sifra: %d, Naziv: %s, Kolicina: %d, Cijena: %.2f EUR, Status: %s\n",
            p->sifra, p->naziv, p->kolicina, p->cijena,
            (p->status == STATUS_AKTIVAN) ? "Aktivan" : "Obrisan");
    }
}

Parfem* traziParfemPoSifri(int sifra) {
    for (size_t i = 0; i < brojParfema; i++) {
        if (parfemi[i].sifra == sifra && isActive(parfemi[i].status)) {
            return &parfemi[i];
        }
    }
    return NULL;
}

void azurirajParfem(void) {
    printf("Unesite sifru parfema za azuriranje: ");
    int sifra;
    if (scanf("%d", &sifra) != 1) {
        printf("Neispravan unos.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    Parfem* p = traziParfemPoSifri(sifra);
    if (!p) {
        printf("Parfem sa zadanim sifrom nije pronaden.\n");
        return;
    }

    printf("Unesite novi naziv (trenutni: %s): ", p->naziv);
    if (!fgets(p->naziv, sizeof(p->naziv), stdin)) {
        printf("Greska pri unosu.\n");
        return;
    }
    p->naziv[strcspn(p->naziv, "\n")] = 0;

    printf("Unesite novu kolicinu (trenutna: %d): ", p->kolicina);
    if (scanf("%d", &p->kolicina) != 1) {
        printf("Neispravan unos.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    printf("Unesite novu cijenu (trenutna: %.2f): ", p->cijena);
    if (scanf("%f", &p->cijena) != 1) {
        printf("Neispravan unos.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    spremiUDatoteku();
    printf("Parfem uspjesno azuriran.\n");
}

void obrisiParfem(void) {
    printf("Unesite sifru parfema za brisanje: ");
    int sifra;
    if (scanf("%d", &sifra) != 1) {
        printf("Neispravan unos.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    Parfem* p = traziParfemPoSifri(sifra);
    if (!p) {
        printf("Parfem sa zadanim sifrom nije pronaden.\n");
        return;
    }
    p->status = STATUS_OBRISAN;

    spremiUDatoteku();
    printf("Parfem uspjesno obrisan.\n");
}

void sortirajParfeme(int (*cmp)(const void*, const void*)) {
    if (brojParfema <= 1) return;
    quicksortParfeme(0, (int)brojParfema - 1, cmp);
    printf("Sortiranje zavrseno.\n");
}

void quicksortParfeme(int left, int right, int (*cmp)(const void*, const void*)) {
    if (left < right) {
        int pi = particija(left, right, cmp);
        quicksortParfeme(left, pi - 1, cmp);
        quicksortParfeme(pi + 1, right, cmp);
    }
}

int particija(int left, int right, int (*cmp)(const void*, const void*)) {
    Parfem pivot = parfemi[right];
    int i = left - 1;
    for (int j = left; j < right; j++) {
        if (cmp(&parfemi[j], &pivot) < 0) {
            i++;
            Parfem temp = parfemi[i];
            parfemi[i] = parfemi[j];
            parfemi[j] = temp;
        }
    }
    Parfem temp = parfemi[i + 1];
    parfemi[i + 1] = parfemi[right];
    parfemi[right] = temp;
    return i + 1;
}

Parfem* pretraziParfem(int (*cmp)(const void*, const void*), const void* key) {
    if (brojParfema == 0) return NULL;

    // Moramo imati sortirani niz da bsearch radi ispravno!
    // Za pretragu po nazivu i sifri, sortirajmo po istom kriteriju
    // Ovdje pretpostavljamo da je niz vec sortiran po kriteriju cmp
    Parfem* rez = (Parfem*)bsearch(key, parfemi, brojParfema, sizeof(Parfem), cmp);
    if (rez && isActive(rez->status))
        return rez;
    return NULL;
}

int usporediNaziv(const void* a, const void* b) {
    const Parfem* pa = (const Parfem*)a;
    const Parfem* pb = (const Parfem*)b;
    return strcmp(pa->naziv, pb->naziv);
}

int usporediCijena(const void* a, const void* b) {
    const Parfem* pa = (const Parfem*)a;
    const Parfem* pb = (const Parfem*)b;
    if (pa->cijena < pb->cijena) return -1;
    else if (pa->cijena > pb->cijena) return 1;
    else return 0;
}

int usporediStatus(const void* a, const void* b) {
    const Parfem* pa = (const Parfem*)a;
    const Parfem* pb = (const Parfem*)b;
    return (int)pa->status - (int)pb->status;
}

int pretraziPoNazivu(const void* key, const void* element) {
    const char* nazivKey = (const char*)key;
    const Parfem* p = (const Parfem*)element;
    return strcmp(nazivKey, p->naziv);
}

int pretraziPoSifri(const void* key, const void* element) {
    int sifraKey = *(const int*)key;
    const Parfem* p = (const Parfem*)element;
    return sifraKey - p->sifra;
}

void ucitajIzDatoteke(void) {
    FILE* f = fopen(DATOTEKA, "rb");
    if (!f) {
        if (errno == ENOENT) { // datoteka ne postoji, nije greska
            return;
        }
        perror("Greska pri otvaranju datoteke");
        exit(EXIT_FAILURE);
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    if (size == 0) { // prazna datoteka
        fclose(f);
        return;
    }

    brojParfema = size / sizeof(Parfem);
    kapacitetParfema = brojParfema > 0 ? brojParfema : 2;

    parfemi = malloc(kapacitetParfema * sizeof(Parfem));
    if (!parfemi) {
        perror("Greska pri alokaciji memorije");
        fclose(f);
        exit(EXIT_FAILURE);
    }

    size_t procitano = fread(parfemi, sizeof(Parfem), brojParfema, f);
    if (procitano != brojParfema) {
        perror("Greska pri citanju datoteke");
        fclose(f);
        oslobodiMemoriju();
        exit(EXIT_FAILURE);
    }

    fclose(f);
}

void spremiUDatoteku(void) {
    FILE* f = fopen(DATOTEKA, "wb");
    if (!f) {
        perror("Greska pri otvaranju datoteke za pisanje");
        return;
    }

    size_t zapisano = fwrite(parfemi, sizeof(Parfem), brojParfema, f);
    if (zapisano != brojParfema) {
        perror("Greska pri pisanju u datoteku");
    }

    fclose(f);
}

void oslobodiMemoriju(void) {
    if (parfemi != NULL) {
        free(parfemi);
        parfemi = NULL;
    }
    brojParfema = 0;
    kapacitetParfema = 0;
}

int obrisiDatoteku(const char* imeDatoteke) {
    if (remove(imeDatoteke) == 0) {
        printf("Datoteka '%s' uspjesno obrisana.\n", imeDatoteke);
        return 0;
    }
    else {
        perror("Greska pri brisanju datoteke");
        return -1;
    }
}

int preimenujDatoteku(const char* staroIme, const char* novoIme) {
    if (rename(staroIme, novoIme) == 0) {
        printf("Datoteka preimenovana iz '%s' u '%s'.\n", staroIme, novoIme);
        return 0;
    }
    else {
        perror("Greska pri preimenovanju datoteke");
        return -1;
    }
}

int kopirajDatoteku(const char* izvor, const char* destinacija) {
    FILE* fIzvor = fopen(izvor, "rb");
    if (!fIzvor) {
        perror("Greska pri otvaranju izvornog fajla");
        return -1;
    }

    FILE* fDest = fopen(destinacija, "wb");
    if (!fDest) {
        perror("Greska pri otvaranju destinacijskog fajla");
        fclose(fIzvor);
        return -1;
    }

    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), fIzvor)) > 0) {
        if (fwrite(buffer, 1, bytes, fDest) != bytes) {
            perror("Greska pri pisanju u destinacijski fajl");
            fclose(fIzvor);
            fclose(fDest);
            return -1;
        }
    }

    fclose(fIzvor);
    fclose(fDest);
    printf("Datoteka uspjesno kopirana.\n");
    return 0;
}
