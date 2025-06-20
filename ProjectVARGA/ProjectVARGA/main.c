#define _CRT_SECURE_NO_WARNINGS
#include "header.h"

int main(void) {
    ucitajIzDatoteke();

    int opcija;
    do {
        prikaziIzbornik();
        if (scanf("%d", &opcija) != 1) {
            printf("Neispravan unos.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (opcija) {
        case OPCIJA_DODAJ:
            dodajParfem();
            break;
        case OPCIJA_PREGLED:
            prikaziParfeme();
            break;
        case OPCIJA_AZURIRAJ:
            azurirajParfem();
            break;
        case OPCIJA_OBRISI:
            obrisiParfem();
            break;
        case OPCIJA_SORTIRAJ:
        {
            int sortOpcija;
            do {
                prikaziPodizbornikSort();
                if (scanf("%d", &sortOpcija) != 1) {
                    printf("Neispravan unos.\n");
                    while (getchar() != '\n');
                    continue;
                }
                while (getchar() != '\n');

                switch (sortOpcija) {
                case SORT_NAZIV:
                    sortirajParfeme(usporediNaziv);
                    break;
                case SORT_CIJENA:
                    sortirajParfeme(usporediCijena);
                    break;
                case SORT_STATUS:
                    sortirajParfeme(usporediStatus);
                    break;
                case SORT_NAZAD:
                    break;
                default:
                    printf("Nepostojeca opcija.\n");
                }
            } while (sortOpcija != SORT_NAZAD);
        }
        break;
        case OPCIJA_PRETRAZI:
        {
            int pretragaOpcija;
            do {
                prikaziPodizbornikPretraga();
                if (scanf("%d", &pretragaOpcija) != 1) {
                    printf("Neispravan unos.\n");
                    while (getchar() != '\n');
                    continue;
                }
                while (getchar() != '\n');

                switch (pretragaOpcija) {
                case PRETRAGA_NAZIV:
                {
                    char nazivKey[50];
                    printf("Unesite naziv za pretragu: ");
                    if (!fgets(nazivKey, sizeof(nazivKey), stdin)) {
                        printf("Greska pri unosu.\n");
                        break;
                    }
                    nazivKey[strcspn(nazivKey, "\n")] = 0;
                    sortirajParfeme(usporediNaziv);
                    Parfem* pronadjen = pretraziParfem(pretraziPoNazivu, nazivKey);
                    if (pronadjen) {
                        printf("Pronaden parfem: Sifra: %d, Naziv: %s, Kolicina: %d, Cijena: %.2f\n",
                            pronadjen->sifra, pronadjen->naziv, pronadjen->kolicina, pronadjen->cijena);
                    }
                    else {
                        printf("Parfem nije pronaden.\n");
                    }
                }
                break;
                case PRETRAGA_SIFRA:
                {
                    int sifraKey;
                    printf("Unesite sifru za pretragu: ");
                    if (scanf("%d", &sifraKey) != 1) {
                        printf("Neispravan unos.\n");
                        while (getchar() != '\n');
                        break;
                    }
                    while (getchar() != '\n');
                    sortirajParfeme(usporediSifru);
                    Parfem* pronadjen = pretraziParfem(pretraziPoSifri, &sifraKey);
                    if (pronadjen) {
                        printf("Pronaden parfem: Sifra: %d, Naziv: %s, Kolicina: %d, Cijena: %.2f\n",
                            pronadjen->sifra, pronadjen->naziv, pronadjen->kolicina, pronadjen->cijena);
                    }
                    else {
                        printf("Parfem nije pronaden.\n");
                    }
                }
                break;
                case PRETRAGA_NAZAD:
                    break;
                default:
                    printf("Nepostojeca opcija.\n");
                }
            } while (pretragaOpcija != PRETRAGA_NAZAD);
        }
        break;
        case OPCIJA_UPRAVLJANJE_DATOTEKAMA:
        {
            int datOpcija;
            do {
                prikaziPodizbornikDatoteke();
                if (scanf("%d", &datOpcija) != 1) {
                    printf("Neispravan unos.\n");
                    while (getchar() != '\n');
                    continue;
                }
                while (getchar() != '\n');

                char imeDat[100];
                char novoImeDat[100];
                switch (datOpcija) {
                case DAT_BRISI:
                    printf("Unesite ime datoteke za brisanje: ");
                    if (!fgets(imeDat, sizeof(imeDat), stdin)) {
                        printf("Greska pri unosu.\n");
                        break;
                    }
                    imeDat[strcspn(imeDat, "\n")] = 0;
                    obrisiDatoteku(imeDat);
                    break;
                case DAT_PREIMENUJ:
                    printf("Unesite staro ime datoteke: ");
                    if (!fgets(imeDat, sizeof(imeDat), stdin)) {
                        printf("Greska pri unosu.\n");
                        break;
                    }
                    imeDat[strcspn(imeDat, "\n")] = 0;
                    printf("Unesite novo ime datoteke: ");
                    if (!fgets(novoImeDat, sizeof(novoImeDat), stdin)) {
                        printf("Greska pri unosu.\n");
                        break;
                    }
                    novoImeDat[strcspn(novoImeDat, "\n")] = 0;
                    preimenujDatoteku(imeDat, novoImeDat);
                    break;
                case DAT_KOPIRAJ:
                {
                    char izvor[100], destinacija[100];
                    printf("Unesite ime izvornog fajla: ");
                    if (!fgets(izvor, sizeof(izvor), stdin)) {
                        printf("Greska pri unosu.\n");
                        break;
                    }
                    izvor[strcspn(izvor, "\n")] = 0;
                    printf("Unesite ime destinacijskog fajla: ");
                    if (!fgets(destinacija, sizeof(destinacija), stdin)) {
                        printf("Greska pri unosu.\n");
                        break;
                    }
                    destinacija[strcspn(destinacija, "\n")] = 0;
                    kopirajDatoteku(izvor, destinacija);
                }
                break;
                case DAT_NAZAD:
                    break;
                default:
                    printf("Nepostojeca opcija.\n");
                }
            } while (datOpcija != DAT_NAZAD);
        }
        break;
        case OPCIJA_IZLAZ:
            printf("Izlaz iz programa.\n");
            break;
        default:
            printf("Nepostojeca opcija.\n");
        }

    } while (opcija != OPCIJA_IZLAZ);

    oslobodiMemoriju();
    return 0;
}

int usporediSifru(const void* a, const void* b) {
    const int* key = (const int*)a;
    const Parfem* p = (const Parfem*)b;
    return *key - p->sifra;
}
