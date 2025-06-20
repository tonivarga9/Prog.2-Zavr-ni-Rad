#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef enum {
    STATUS_AKTIVAN,
    STATUS_OBRISAN
} Status;

typedef struct {
    int sifra;
    char naziv[50];
    int kolicina;
    float cijena;
    Status status;
} Parfem;

#define DATOTEKA "parfemi.dat"

// Izbornik opcije
typedef enum {
    OPCIJA_DODAJ = 1,
    OPCIJA_PREGLED,
    OPCIJA_AZURIRAJ,
    OPCIJA_OBRISI,
    OPCIJA_SORTIRAJ,
    OPCIJA_PRETRAZI,
    OPCIJA_UPRAVLJANJE_DATOTEKAMA,
    OPCIJA_IZLAZ
} Opcija;

typedef enum {
    SORT_NAZIV = 1,
    SORT_CIJENA,
    SORT_STATUS,
    SORT_NAZAD
} SortOpcija;

typedef enum {
    PRETRAGA_NAZIV = 1,
    PRETRAGA_SIFRA,
    PRETRAGA_NAZAD
} PretragaOpcija;

typedef enum {
    DAT_BRISI = 1,
    DAT_PREIMENUJ,
    DAT_KOPIRAJ,
    DAT_NAZAD
} DatotekaOpcija;

extern Parfem* parfemi;
extern size_t brojParfema;
extern size_t kapacitetParfema;

static inline int isActive(Status status) {
    return status == STATUS_AKTIVAN;
}

void prikaziIzbornik(void);
void prikaziPodizbornikSort(void);
void prikaziPodizbornikPretraga(void);
void prikaziPodizbornikDatoteke(void);

void dodajParfem(void);
void prikaziParfeme(void);
void azurirajParfem(void);
void obrisiParfem(void);

void sortirajParfeme(int (*cmp)(const void*, const void*));
void quicksortParfeme(int left, int right, int (*cmp)(const void*, const void*));
int particija(int left, int right, int (*cmp)(const void*, const void*));

Parfem* pretraziParfem(int (*cmp)(const void*, const void*), const void* key);

int usporediNaziv(const void* a, const void* b);
int usporediCijena(const void* a, const void* b);
int usporediStatus(const void* a, const void* b);

int pretraziPoNazivu(const void* key, const void* element);
int pretraziPoSifri(const void* key, const void* element);
int usporediSifru(const void* a, const void* b);

void ucitajIzDatoteke(void);
void spremiUDatoteku(void);
void oslobodiMemoriju(void);

int obrisiDatoteku(const char* imeDatoteke);
int preimenujDatoteku(const char* staroIme, const char* novoIme);
int kopirajDatoteku(const char* izvor, const char* destinacija);

#endif
