/*************************************************************************/ 
/* CT60A2500 C-ohjelmoinnin perusteet  
 * Tekijä: Juhani Manninen
 * Päivämäärä: 1.3.2022
 */ 
/*************************************************************************/ 
/* Tehtävä HTPerustaso, tiedoston nimi HTPerusKirjasto.c */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HTPerusKirjasto.h"
#define LEN 200

void kysyTiedostonNimi(char* tulostus, char* tiedostoNimi)
{
    printf("%s", tulostus);
    scanf("%s", tiedostoNimi);
    return;
}

void vapautaMuisti(DATA* ptrAlku, TULOS* ptrTulos)
{
    DATA* ptr = ptrAlku;
    while (ptr != NULL) 
    {
        ptrAlku = ptr->ptrSeuraava;
        free(ptr);
        ptr = ptrAlku;
    }
    free(ptrTulos);
    return;
}

// Kirjoittaa ja tulostaa tulokset
void kirjoitaTulokset(TULOS* ptrTulos)
{  
    FILE *tiedosto;
    int i = 0;
    char tiedostoNimi[LEN];
    kysyTiedostonNimi("Anna kirjoitettavan tiedoston nimi: ", tiedostoNimi);

    if((tiedosto = fopen(tiedostoNimi, "w")) == NULL) 
    {
        printf("Tilastotiedot %d mittaustuloksesta:\n", ptrTulos->mittaustulostenMaara);
        printf("Kulutus oli yhteensä %.0f kWh, ja keskimäärin %.1f kWh.\n", ptrTulos->kokonaisKulutus, ptrTulos->keskimaara);
        printf("Suurin kulutus, %.0f kWh, tapahtui %s.\n", ptrTulos->suurinKulutus, ptrTulos->aikaleimaSuurin);
        printf("Pienin kulutus, %d kWh, tapahtui %s.\n", ptrTulos->pieninKulutus, ptrTulos->aikaleimaPienin);
        printf("\n");
        printf("Pvm;Tuotanto (GWh)\n");

        for(i = 0; i < 12; ++i)
        {
            printf("Kk %d;%.2f\n", i + 1, ptrTulos->kuukausiTuotanto[i]);
        }

        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    printf("Tilastotiedot %d mittaustuloksesta:\n", ptrTulos->mittaustulostenMaara);
    printf("Kulutus oli yhteensä %.0f kWh, ja keskimäärin %.1f kWh.\n", ptrTulos->kokonaisKulutus, ptrTulos->keskimaara);
    printf("Suurin kulutus, %.0f kWh, tapahtui %s.\n", ptrTulos->suurinKulutus, ptrTulos->aikaleimaSuurin);
    printf("Pienin kulutus, %d kWh, tapahtui %s.\n", ptrTulos->pieninKulutus, ptrTulos->aikaleimaPienin);
    printf("\n");
    printf("Pvm;Tuotanto (GWh)\n");

    for(i = 0; i < 12; ++i)
    {
        printf("Kk %d;%.2f\n", i + 1, ptrTulos->kuukausiTuotanto[i]);
    }

    fprintf(tiedosto, "Tilastotiedot %d mittaustuloksesta:\n", ptrTulos->mittaustulostenMaara);
    fprintf(tiedosto, "Kulutus oli yhteensä %.0f kWh, ja keskimäärin %.1f kWh.\n", ptrTulos->kokonaisKulutus, ptrTulos->keskimaara);
    fprintf(tiedosto, "Suurin kulutus, %.0f kWh, tapahtui %s.\n", ptrTulos->suurinKulutus, ptrTulos->aikaleimaSuurin);
    fprintf(tiedosto, "Pienin kulutus, %d kWh, tapahtui %s.\n", ptrTulos->pieninKulutus, ptrTulos->aikaleimaPienin);
    fprintf(tiedosto, "\n");
    fprintf(tiedosto, "Pvm;Tuotanto (GWh)\n");

    for(i = 0; i < 12; ++i)
    {
        fprintf(tiedosto, "Kk %d;%.2f\n", i + 1, ptrTulos->kuukausiTuotanto[i]);
    }

    printf("Tiedosto '%s' kirjoitettu.\n", tiedostoNimi);
    fclose(tiedosto);
    return;
}

// Laskee kokonaiskulutuksen, etsii suurimman ja pienimmän kulutuksen sekä niiden aikaleimat ja laskee kuukausittaiset tuotot
TULOS* analysoiTiedot(DATA* ptrAlku, DATA* ptr, TULOS* ptrTulos)
{
    int i = 0;
    double kuukausiTuotto;
    double kokonaisKulutus = 0;
    int pieninKulutus = ptrAlku->kulutus;
    int suurinKulutus = ptrAlku->kulutus;
    char aikaleimaSuurin[LEN];
    char aikaleimaPienin[LEN];
    strcpy(aikaleimaSuurin, ptrAlku->aikaleima);
    strcpy(aikaleimaPienin, ptrAlku->aikaleima);

    if ((ptrTulos = (TULOS*)malloc(sizeof(TULOS))) == NULL)
    {
        perror("Muistin varaus epäonnistui");
        exit(0);
    }

    ptr = ptrAlku;
    while (ptr != NULL) 
    {
        // Kokonaiskulutus
        kokonaisKulutus += ptr->kulutus;
        
        // Pienin ja suurin kulutus sekä niiden ajat
        if(ptr->kulutus < pieninKulutus)
        {
            pieninKulutus = ptr->kulutus;
            strcpy(aikaleimaPienin, ptr->aikaleima);
        }

        if(ptr->kulutus > suurinKulutus)
        {
            suurinKulutus = ptr->kulutus;
            strcpy(aikaleimaSuurin, ptr->aikaleima);
        }

        // Kuukausi tuotanto

        char aikaleima[LEN];
        strcpy(aikaleima, ptr->aikaleima);
        memcpy(aikaleima, &aikaleima[3], 2);
        aikaleima[2] = '\0';
        int kuukausi = atoi(aikaleima);

        kuukausiTuotto = ptr->aurinkovoima + ptr->tuulivoima + ptr->vesivoima + ptr->ydinvoima + ptr->yhteistuotanto + ptr->erillinenLampo;
        kuukausiTuotto = kuukausiTuotto * 0.000001; // kWh -> gWh
        ptrTulos ->kuukausiTuotanto[kuukausi - 1] += kuukausiTuotto;

        ptr = ptr->ptrSeuraava;
        i++;
    }

    // Tallennetaan data tulos tietueeseen
    strcpy(ptrTulos->aikaleimaSuurin, aikaleimaSuurin);
    strcpy(ptrTulos->aikaleimaPienin, aikaleimaPienin);
    ptrTulos->pieninKulutus = pieninKulutus;
    ptrTulos->suurinKulutus = suurinKulutus;
    ptrTulos->kokonaisKulutus = kokonaisKulutus;
    ptrTulos->mittaustulostenMaara = i;
    ptrTulos->keskimaara = kokonaisKulutus / i;

    printf("Analysoitu %d mittaustulosta.\n", i);
    printf("Kokonaiskulutus oli yhteensä %.0f kWh.\n", ptrTulos->kokonaisKulutus);
    printf("Kuukausittaiset tuotannot analysoitu.\n");
    
    return ptrTulos;
}

// Lukee tiedostosta sähkön tuotantoon ja kulutukseen liittyviä arvoja ja tallentaa ne data tietueeseen
DATA* lueTiedosto(DATA* ptrAlku, DATA* ptrUusi, DATA* ptr)
{
    char tiedostoNimi[LEN];
    kysyTiedostonNimi("Anna luettavan tiedoston nimi: ", tiedostoNimi);

    FILE *tiedosto;
    if((tiedosto = fopen(tiedostoNimi, "r")) == NULL) 
    {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    // Lukee dataa rivi kerrallaan ja jakaa sen puolipisteiden mukaan eri tietueen arvoihin
    char rivi[LEN];
    char *aikaleima, *viikko, *kulutus, *aurinkovoima, *tuulivoima, *vesivoima, *ydinvoima, *yhteistuotanto, *erillinenLampo;


    fgets(rivi, LEN, tiedosto); // Skippaa tiedoston otsikon
    while(fgets(rivi, LEN, tiedosto) != NULL)
    {
        if ((ptrUusi = (DATA*)malloc(sizeof(DATA))) == NULL)
        {
            perror("Muistin varaus epäonnistui");
            exit(0);
        }

        aikaleima = strtok(rivi, ";");
        viikko = strtok(NULL, ";");
        kulutus = strtok(NULL, ";");
        aurinkovoima = strtok(NULL, ";");
        tuulivoima = strtok(NULL, ";");
        vesivoima = strtok(NULL, ";");
        ydinvoima = strtok(NULL, ";");
        yhteistuotanto = strtok(NULL, ";");
        erillinenLampo = strtok(NULL, ";");

        // Tallennetaan tiedot tietueeseen
        strcpy(ptrUusi->aikaleima, aikaleima);
        ptrUusi->viikko = atoi(viikko);
        ptrUusi->kulutus = atoi(kulutus);
        ptrUusi->aurinkovoima = atoi(aurinkovoima);
        ptrUusi->tuulivoima = atoi(tuulivoima);
        ptrUusi->vesivoima = atoi(vesivoima);
        ptrUusi->ydinvoima = atoi(ydinvoima);
        ptrUusi->yhteistuotanto = atoi(yhteistuotanto);
        ptrUusi->erillinenLampo = atoi(erillinenLampo);
        ptrUusi->ptrSeuraava = NULL;

        if (ptrAlku == NULL) 
        {
            ptrAlku = ptrUusi;
        } 
        else 
        {
            ptr = ptrAlku;
            while(ptr ->ptrSeuraava != NULL)
            {
                ptr = ptr->ptrSeuraava;
            }
            ptr->ptrSeuraava = ptrUusi;
        }
    }
    
    printf("Tiedosto '%s' luettu.\n", tiedostoNimi);
    fclose(tiedosto);
    return ptrAlku;
}

int valikko()
{
    int valinta;
    printf("Valitse haluamasi toiminto:\n");
    printf("1) Lue tiedosto\n");
    printf("2) Analysoi tiedot\n");
    printf("3) Kirjoita tulokset\n");
    printf("0) Lopeta\n");
    printf("Anna valintasi: ");
    scanf("%d", &valinta);
    return valinta;
}
/* eof */