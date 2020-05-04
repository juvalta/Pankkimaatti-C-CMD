#include <stdio.h>
#include <stdlib.h>

    typedef struct {

        char tilinnimi[50]; //= {"12345.tili"};//= {"%d.tili", tilinumero};
        int salasana;
        int saldo;

    }Asiakas;

    Asiakas a;

int tervetuloa();
int nostaRahaa();
int talletaRahaa();
int lataaMenu();
int syotaTiedot();
int lataaSaldoa();
int tallennaKamat(Asiakas a);
int lueKokonaisluku(void);
void lueRoskat(void);
void lueMerkkijono( char merkkijono[], int pituus );

    int balance;		//pankkitilillä oleva rahamäärä
    int otto;		//nostettava/talletettava rahasumma
    int suurinottomoney = 1000;	//suurin määrä rahaa, jota voi nostaa. Pätee myös puhelinnumeron saldon nostamiseen!
    int numero;		//nostettavan rahasumman valitsemiseen käytetty numero
    int menunumero;	//päävalikon navigoimiseen käytettävä numero
    int tilinumero;     //tilinumero, kuten 12345
    int password;		//syötetty pankkikortin PIN-koodi
    char tulostusmetodi;	//käytetään kuitille vai näytölle tulostamisessa

    int jakojaannos;
    int kakkosjakojaannos;
    int kakskyt;
    int viiskyt;
    double returnvalue;

    /*
    *   MAIN
    *
    *   Siirtää asiakkaan sisäänkirjautumisesta alkuvalikkoon
    *   Hoitaa siis skriptin alussa siirtymisen oikeisiin paikkoihin
    *
    *
    */




int main(void)
{
        tervetuloa();
        lataaMenu();

    return 0;
}


    /*
    *
    *   LATAAMENU
    *
    *   Antaa asiakkaan navigoida käyttöliittymää alkuvalikosta
    *   Palautuu aina tänne
    *
    *
    */



int lataaMenu () {

    while (1){

        printf("Paavalikko\n\n1. Nosta rahaa\n2. Talleta rahaa\n3. Lataa saldoa puhelimellesi\n4. Tilinakyma\n5. Lopeta ohjelma\n>>> ");

        menunumero = lueKokonaisluku();

        while (menunumero<0 || menunumero>5) {
            printf("Syottamasi luku ei kelpaa!\n\nSyota uusi luku >  ");
            menunumero = lueKokonaisluku();
        }



        switch (menunumero) {
        case 1:
            printf("\n");
            nostaRahaa();
            break;
        case 2:
            talletaRahaa();
            break;
        case 3:
            lataaSaldoa();
            break;
        case 4:
            printf("Tilillasi %d on %d euroa rahaa\n", tilinumero, balance);
            printf("Voit nostaa tanaan %d euron verran rahaa\n\n", suurinottomoney);
            break;
        case 5:
            tallennaKamat(a);
            printf("\n\n\n\n<=<=<=<=<=<=<=<=<=<= Kiitos, kun asioit Pankkimaatissa! =>=>=>=>=>=>=>=>=>=>\n\n\n\n");
            return (0);

        }
    }
}

    /*
    *
    *   TERVETULOA
    *
    *   Antaa kayttajan kirjautua sisään tai tehdä uuden käyttäjän.
    *   Tallentaa uuden käyttäjätilin tiedostona samaan tallennuskansioon skriptin kanssa.
    *
    */

int tervetuloa() {

    int valinta;
    printf("Tervetuloa. Paina numeroa 1 kirjautuaksesi sisaan tai numeroa 2 tehdaksesi kayttajan.\n>>> ");
    valinta = lueKokonaisluku();

    while (valinta < 1 || valinta > 2) {
        printf("Syotit vaaran numeron.\n>>> ");
        valinta = lueKokonaisluku();
    }

    switch(valinta) {

    case 1:
        syotaTiedot();
        return(0);
        break;
    case 2:
        break;
    }
    char saldomaara[100000];    //säilöö saldon kansioon
    int salasana;

    printf("Syota tulevan tilisi nimi\n");
    tilinumero = lueKokonaisluku();
    printf("Tilisi nimi on %d\n", tilinumero);
    sprintf(a.tilinnimi, "%d.tili", tilinumero);
    printf("Syota salasanasi\n");
    a.salasana = lueKokonaisluku();
    printf("Syota tilillasi oleva rahasumma\n");
    a.saldo = lueKokonaisluku();
    balance = a.saldo;


    sprintf(a.tilinnimi, "%d.tili", tilinumero);

    FILE * filepointer;
    sprintf(saldomaara,"%d", a.saldo);

    printf("Tilillasi %s on %d euron verran rahaa. Salasanasi on %d\n", a.tilinnimi, a.saldo, a.salasana);

    filepointer = fopen(a.tilinnimi, "w+");

    fprintf(filepointer, "%d", a.salasana);

    fputs("\n", filepointer);
    fputs(saldomaara, filepointer);
    fclose(filepointer);

    return(0);


}

    /*
    *
    *   SYOTATIEDOT
    *
    *   Antaa asiakkaan avata tilinsä tiedoston ja kysyy tiedostossa olevaa salasanaa, on siis sisäänkirjautuminen
    *
    */


int syotaTiedot (){

    int tila = 0;   //määrittelee onko tiedosto auki
    int salasana;
    int oikeasaldo;
    int oikeasalasana;
    FILE * filepointer;

    printf("Anna tilisi numero\n>>> ");

    while (tila != 1) {

        tilinumero = lueKokonaisluku();
        printf("Etsitaan tilia %d...\n", tilinumero);
        sprintf(a.tilinnimi, "%d.tili", tilinumero);
        filepointer = fopen(a.tilinnimi, "r");

        if (filepointer == NULL) {
            printf("Kyseista tilia ei loydetty. Kirjoitiko oikean nimen ja onko tili olemassa?\n\nKokeile uudestaan>>> ");
        }
        else {
            tila = 1;
        }

    }


    fscanf(filepointer, "%d %d", &oikeasalasana, &oikeasaldo);

    fclose(filepointer);

    printf("Syota PIN-koodi tilille %d\n>>> ", tilinumero);

    while(salasana != oikeasalasana) {

        salasana = lueKokonaisluku();
        if (salasana != oikeasalasana) {
            printf("Vaara salasana. Kokeile uudestaan.\n>>> ");

        }


    }

    a.saldo = oikeasaldo;
    a.salasana = oikeasalasana;
    balance = a.saldo;
    printf("\n");
    printf("Tervetuloa Pankkimaattiin!\n");
    printf("Tilisi saldo talla hetkella on %d\n\n", a.saldo);

    printf("\n");

}

    /*
    *
    *   NOSTARAHAA
    *
    *   Antaa asiakkaan nostaa rahaa tililtänsä, maksimissaan 1000 euroa per "päivä" eli per ohjelmanajokerran
    *   Antaa setelit joko 20:n euron seteleinä tai 50:n euron seteleinä
    *
    */


int nostaRahaa() {

    viiskyt = 0;
    kakskyt = 0;

    printf("1. Nosta 20 euroa\n2. 40 euroa\n3. 50 euroa\n 4. 60 euroa\n5. 70 euroa\n6. 80 euroa\n7. 90 euroa\n8. 100 euroa\n9. Syota summa tuhannen alapuolella, joka on kymmenella jaollinen\n10. Lopeta asiointi\n>>> ");
    numero = lueKokonaisluku();

    while (numero<1 || numero>10){
        printf("Syotit vaaran luvun. Kokeile uudestaan.");
        numero = lueKokonaisluku();
    }

    switch(numero) {
    case 1:
        otto = 20;
        printf("\n");
        break;
    case 2:
        otto = 40;
        printf("\n");
        break;
    case 3:
        otto = 50;
        printf("\n");
        break;
    case 4:
        otto = 60;
        printf("\n");
        break;
    case 5:
        otto = 70;
        printf("\n");
        break;
    case 6:
        otto = 80;
        printf("\n");
        break;
    case 7:
        otto = 90;
        printf("\n");
        break;
    case 8:
        otto = 100;
        printf("\n");
        break;

    case 9:

        printf("Syota haluamasi 10:lla jaettava summa\n> ");
        otto = lueKokonaisluku();
        double money = otto;

        double ottoamount = money / 10;
        int maara = ottoamount;

        while (maara != ottoamount) {          //tarkistaa, onko luku 10:llä jaollinen
            printf("Syotit luvun, joka ei ole 10:lla jaollinen. Kokeile uudestaan.\n>>> ");
            otto = lueKokonaisluku();
            money = otto;
            ottoamount = money / 10;
            maara = ottoamount;
        }



        if (ottoamount > 1 && ottoamount <= 100) {
            printf("Summa ok.\n");
        }

        else {
            printf("Syottamasi summa ei kelpaa\n\n");
            return(0);
        }

        break;

    case 10:
        printf("Rahannosto peruttu.\n");
        return (0);

    }

    jakojaannos = otto;

    do {
        if (jakojaannos >= 50) {
            jakojaannos = jakojaannos - 50;
            viiskyt++;
        }
    }while (jakojaannos < otto && jakojaannos >= 50);



    while (jakojaannos > 0) {

        if (jakojaannos <= 10) {
            jakojaannos = jakojaannos + 50;
            viiskyt = viiskyt - 1;
        }

        while (jakojaannos >= 20) {

            jakojaannos = jakojaannos -20;
            kakskyt++;

        }



    }





    if (suurinottomoney <= 0 || otto > 1000) {
        printf("Et voi nostaa enempää tanaan kuin %d euroa", suurinottomoney);
        return(0);

    }

    if (otto > balance) {
        printf("Tilillasi ei ole tarpeeksi rahaa....\n\n");
        return(0);
    }


    balance = balance - otto;
    suurinottomoney = suurinottomoney - otto;
    tallennaKamat(a);
    printf("Nostit %d euroa rahaa tililtasi!\n", otto);
    printf("Annetaan %d 50 euron seteliä ja %d 20 euron seteliä\n", viiskyt, kakskyt);
    printf("Tilillasi on %d euroa rahaa jaljella.\n", balance);
    printf("Voit nostaa tanaan viela %d euron verran rahaa euroissa\n\n\n\n<=<=<=<=<=<=<=<=<=<= Kiitos, kun nostit rahaa! =>=>=>=>=>=>=>=>=>=>\n\n\n\n", suurinottomoney);
}

    /*
    *
    *   TALLETARAHAA
    *
    *   Antaa käyttäjän tallettaa rahaa tililleensä
    *
    *
    */



int talletaRahaa() {

    int valinta;
    printf("1. Talleta rahaa\n2. Poistu alkuvalikkoon\n");
    valinta = lueKokonaisluku();

    while (valinta < 1 && valinta > 2) {
        valinta = lueKokonaisluku();
    }

    if (valinta == 1) {

            printf("Syota talletettava rahasumma (suurimmissaan 1000 euroa.\n>>> ");
            otto = lueKokonaisluku();

            while (otto > 1000 || otto < 0) {
                printf("Et syottanyt rahasummaa oikein (1-1000e). Kokeile uudestaan\n>>> ");
                otto = lueKokonaisluku();
            }
            balance = balance + otto;
            printf("Talletit %d euroa tilillesi.\n\n", otto);
            tallennaKamat(a);

    }
    else {
        printf("Talletus peruttiin. Palataan paavalikkoon.\n\n");
    }
}

    /*
    *   LATAASALDOA
    *
    *   Lataa asiakkaan puhelimelle saldoa.
    *   HUOM! Ladattavan saldon määrä vähentää 1000 euron päivittäistä käyttörajaa ladatun saldon verran!
    *
    */

int lataaSaldoa(){
    char operaattori[26];
    int saldo;
    int puhnumero;
    int valinta;


    printf("Syota operaattorisi nimi. (Voit perua maksun ennen maksamista). \n");
    lueMerkkijono(operaattori, 27);

    printf("Syota puhelimesi numero\n");
    puhnumero = lueKokonaisluku();

    printf("Syota ladattava saldo kokonaislukuna\n");
    saldo = lueKokonaisluku();

    printf("Paina numeroa 1 vahvistaaksesi maksun, tai paina numeroa 2 peruaksesi maksun. \n");
    valinta = lueKokonaisluku();

    while (valinta < 1 || valinta > 2){
        printf("Et syottanyt oikeata lukua.\n");
        valinta = lueKokonaisluku();
    }

    switch (valinta) {

    case 1:
        if (balance > saldo && saldo < suurinottomoney){

            printf("Latasit %d euron verran saldoa numeroon %d. %s kiittaa!\n", saldo, puhnumero, operaattori);
            balance = balance - saldo;
            suurinottomoney = suurinottomoney - saldo;
            tallennaKamat(a);
            return (0);
        }


        else {
            printf("Rahasi tililla eivat riita....\n\n");
            return(0);
        }

    case 2:

        printf("Maksutapahtuma peruttu.\n");
        return (0);

    }

    printf("Palataan paavalikkoon\n\n");

}

    /*
    *TALLENNAKAMAT
    *
    *   Tallentaa tilin tiedot tiedostoon
    *   Suoritetaan rahatapahtumien yhteydessä sekä poistuttaessa
    *
    */

int tallennaKamat(Asiakas a) {  //tyhjentää tiedoston kirjoitusmoodia varten, tallentaa päivittyneen saldon ja salasanan tiedostoon

    a.saldo = balance;
    char saldomaara[100000];    //tällä säilötään saldo kansioon

    FILE * filepointer;
    sprintf(saldomaara,"%d", a.saldo);

    filepointer = fopen(a.tilinnimi, "w");

    fprintf(filepointer, "%d", a.salasana);

    fputs("\n", filepointer);
    fputs(saldomaara, filepointer);
    fclose(filepointer);

}

    /*
    *   LUEKOKONAISLUKU
    *
    *   Lukee näppäimistöltä kokonaisluvun.
    *
    *
    */

int lueKokonaisluku(void){

   int luku;
   char mki;
   int status;

   while((status = scanf("%d%c", &luku, &mki))==0  || (2 == status && mki != '\n') ){
      lueRoskat();
      printf("Et syottanyt kokonaislukua > ");
   }

   return luku;
}

    /*
    *   LUEROSKAT
    *
    *   Lukee jäljelle jääneet roskat, ettei inputtiin tule vääriä merkkejä sattumalta
    *
    */

void lueRoskat(void){

   while( fgetc(stdin) != '\n');

}

    /*
    *   LUEMERKKIJONO
    *
    *   Lukee näppäimistölle kirjoitetun "stringin"
    *
    *
    */



void lueMerkkijono( char merkkijono[], int pituus ){

   fgets( merkkijono, pituus, stdin );

   if( merkkijono[ strlen(merkkijono) -1 ] == '\n')
      merkkijono[ strlen(merkkijono) -1 ] = '\0';
   else
      lueRoskat();

}
