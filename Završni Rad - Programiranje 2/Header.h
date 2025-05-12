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


