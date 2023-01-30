/*************************************************************************/ 
/* CT60A2500 C-ohjelmoinnin perusteet  
 * Tekijä: Juhani Manninen
 * Päivämäärä: 1.3.2022
/*************************************************************************/ 
/* Tehtävä HTPerustaso, tiedoston nimi HT.c */ 

// Ohjelmalla pystyy lukemaan ja analysoimaan sähködata tekstitiedostoja sekä kirjoittamaan tietoja analyysin pohjalta
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HTPerusKirjasto.h"

int main()
{
    DATA *ptrAlku = NULL;
    DATA *ptrUusi = NULL;
    DATA *ptr = NULL;
    TULOS *ptrTulos = NULL;

    int valinta;
    while(1)
    {
        valinta = valikko();
        if(valinta == 1)
        {
            ptrAlku = NULL;
            ptrAlku = lueTiedosto(ptrAlku, ptrUusi, ptr);
        }
        else if(valinta == 2)
        {
            if(ptrAlku != NULL)
            {
                if(ptrTulos != NULL)
                {
                    ptrTulos = NULL;
                }
                ptrTulos = analysoiTiedot(ptrAlku, ptr, ptrTulos);
            }
            else
            {
                printf("Ei analysoitavaa, lue tiedosto ennen analyysiä.\n");
            }
        }
        else if(valinta == 3)
        {
            if(ptrTulos != NULL)
            {
                kirjoitaTulokset(ptrTulos);
            }
            else
            {
                printf("Ei kirjoitettavia tietoja, analysoi tiedot ennen tallennusta.\n");
            }
        }
        else if(valinta == 0)
        {
            vapautaMuisti(ptrAlku, ptrTulos);
            printf("\nKiitos ohjelman käytöstä.\n");
            return 0;
        }
        else
        {
            printf("Tuntematon valinta, yritä uudestaan.\n");
        }
        printf("\n");
    }
}
/* eof */