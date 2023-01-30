/*************************************************************************/ 
/* CT60A2500 C-ohjelmoinnin perusteet  
 * Tekijä: Juhani Manninen
 * Opiskelijanumero: 0560873
 * Päivämäärä: 1.3.2022
 * Palauttamalla tämän työn arvioitavaksi vakuutan, että  
 * 1) Olen itse kirjoittanut kaiken tässä tiedostossa olevan koodin 
 * 2) En ole antanut tätä koodia kenenkään muun käyttöön 
 *  
 * Kurssin oppimateriaalien lisäksi työhön ovat vaikuttaneet seuraavat  
 * lähteet ja henkilöt, ja se näkyy koodissa seuraavissa kohdissa: 
 * -
 */ 
/*************************************************************************/ 
/* Tehtävä HTPerustaso, tiedoston nimi HTPerusKirjasto.h */ 

#ifndef HTPERUSKIRJASTO_H
#define HTPERUSKIRJASTO_H
#define LEN 200

typedef struct data
{
    char aikaleima[LEN];
    int viikko;
    int kulutus;
    int aurinkovoima;
    int tuulivoima;
    int vesivoima;
    int ydinvoima;
    int yhteistuotanto;
    int erillinenLampo;
    struct data *ptrSeuraava;
} DATA;

typedef struct tulos
{
    char aikaleimaSuurin[LEN];
    char aikaleimaPienin[LEN];
    double kuukausiTuotanto[12];
    double kokonaisKulutus;
    double keskimaara;
    double suurinKulutus;
    int pieninKulutus;
    int mittaustulostenMaara;
} TULOS;

void kysyTiedostonNimi(char* tulostus, char* tiedostoNimi);
void vapautaMuisti(DATA* ptrAlku, TULOS* ptrTulos);
void kirjoitaTulokset(TULOS* ptrTulos);
TULOS* analysoiTiedot(DATA* ptrAlku, DATA* ptr, TULOS* ptrTulos);
DATA* lueTiedosto(DATA* ptrAlku, DATA* ptrUusi, DATA* ptr);
int valikko();

#endif
/* eof */