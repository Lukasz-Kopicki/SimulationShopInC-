#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;


class Produkt{
private:
    string nazwa;
    double cena;
public:

    Produkt(string nazwa, double cena){
        this->nazwa = nazwa;
        this->cena = cena;
    }

    void ustawNazwa(string nazwa){
        this->nazwa = nazwa;
    }
    void ustawCena(double cena){
        this->cena = cena;
    }

    string pobierzNazwa(){
        return nazwa;
    }
    double pobierzCena(){
        return cena;
    }

    void wyswietl(){
        cout << nazwa << " " << cena << " zl" << endl;
    }

};

class Produkty{
protected:
    Produkt* produkty[];
    string sciezka;
    int iloscProduktow;

public:
    Produkty(){
        iloscProduktow = 0;
    }
//    ~Produkty(){
//        for(int i=0; i<iloscProduktow; i++){
//            delete produkty[i]>pobierzCena();
//        }
//    }

    int pobierzIloscProduktow(){
        return iloscProduktow;
    }

    void wyswietl(){
        cout << "Lista produktow: ";
        if (iloscProduktow==0){
            cout << "(lista pusta)";
        }
        cout <<endl;

        for(int i=0; i<iloscProduktow; i++){
            cout << i+1 << ". ";
            produkty[i]->wyswietl();
        }
        cout << "Wartosc calkowita: " << sumujWartosc() <<endl;
    }

    void sortuj(){
        Produkt* pom;
        int j;
        for(int i=1; i<iloscProduktow; i++){
             pom = produkty[i];
             j = i-1;
             while(j>=0 && produkty[j]->pobierzCena() > pom->pobierzCena()){
                produkty[j+1] = produkty[j];
                --j;
             }
             produkty[j+1] = pom;
        }
    }

    void odczytajZPliku()
    {
        fstream plik;
        string token;
        double cenaProduktu;
        string nazwaProduktu;

        plik.open(sciezka, ios::in);
        if (plik.good())
        {
            while (!plik.eof())
            {
                //getline(plik, linia);
                plik >> token;  //numer produktu (ignorujemy)
                plik >> nazwaProduktu;
                plik >> cenaProduktu;

                Produkt* produkt = new Produkt(nazwaProduktu, cenaProduktu);
                produkty[iloscProduktow] = produkt;
                iloscProduktow++;

            }
            plik.close();
        }
    }

    double sumujWartosc(){
        double S = 0;
        for(int i=0; i<iloscProduktow; i++){
            S += produkty[i]->pobierzCena();
        }
        return S;
    }

};

class Kategoria: public Produkty{
public:

    Produkt* pobierzProduktZKategorii(int numerProduktu){
        return produkty[numerProduktu-1];
    }

    void virtual wyswietlKategorie(){
        wyswietl();
    }

};

class KategoriaOdziez: public Kategoria{
private:
    //string rozmiar;

public:
    void virtual wyswietlKategorie(){
        system("cls");
        cout << "SKLEP -> MENU GLOWNE -> KATEGORIE -> Kategoria odziez" <<endl;
        wyswietl();
    }

    KategoriaOdziez(){
        sciezka = "kategoriaOdziez.txt";
    }
};

class KategoriaMeble: public Kategoria{
    void virtual wyswietlKategorie(){
        system("cls");
        cout << "SKLEP -> MENU GLOWNE -> KATEGORIE -> Kategoria meble" <<endl;
        wyswietl();
    }

public:
    KategoriaMeble(){
        sciezka = "kategoriaMeble.txt";
    }

};

class KategoriaSport: public Kategoria{
    void virtual wyswietlKategorie(){
        system("cls");
        cout << "SKLEP -> MENU GLOWNE -> KATEGORIE -> Kategoria sport " <<endl;
        wyswietl();
    }

public:
    KategoriaSport(){
        sciezka = "kategoriaSport.txt";
    }

};


class Koszyk: public Produkty{
    string sciezka2;

public:
    Koszyk(){
        sciezka2 = "koszyk.txt";
        iloscProduktow = 0;
    }

    void dodajProdukt(Produkt *p){
        produkty[iloscProduktow] = p;
        iloscProduktow++;
    }

    void zapiszDoPliku(){
        fstream plik;
        plik.open(sciezka2, ios::out);
        if (plik.good())
        {
            for(int i=0; i<iloscProduktow; i++){
                plik << i+1 << ". " ;
                plik << produkty[i]->pobierzNazwa() << " ";
                plik << produkty[i]->pobierzCena() << endl;
            }
            plik.close();
        }
    }

    void oproznijKoszyk(){
        for(int i=0; i<iloscProduktow; i++){
            delete produkty[i];
        }
        iloscProduktow =0;
        zapiszDoPliku();

    }
};

class Sklep{
private:
    Koszyk* koszyk;

public:

    Sklep(){
        koszyk = new Koszyk();
    }
    ~Sklep(){
        delete koszyk;
    }

    void wyswietlMenuGlowne()
    {
        system("cls");
        cout << "SKLEP -> MENU GLOWNE" <<endl;
        cout << "Wybierz numer" << endl;
        cout << "1. Kategorie" << endl;
        cout << "2. Koszyk" << endl;
        cout << "3. Wyjscie" << endl;

        int wybor;
        cin >> wybor;
        switch (wybor)
        {
        case 1:
            wyswietlKategorie();
            break;
        case 2:
            wyswietlKoszyk();
            getchar();
            wyswietlMenuGlowne();
            break;

        case 3:
            break;

        default:
            break;
        }
    }

    void wyswietlKoszyk(){
        system("cls");
        cout << "SKLEP -> MENU GLOWNE -> KOSZYK" <<endl;
        koszyk->wyswietl();
        cout << "Wybierz opcje:" << endl;
        cout << "1. Wyczysc koszyk" << endl;
        cout << "2. Zapisz koszyk" << endl;
        cout << "3. Powrot do menu glownego" << endl;

        int wybor;
        cin >> wybor;
        switch (wybor)
        {
        case 1:
            koszyk->oproznijKoszyk();
            wyswietlMenuGlowne();
            break;
        case 2:
            koszyk->zapiszDoPliku();
            break;
        case 3:
            wyswietlMenuGlowne();
            break;
        default:
            wyswietlKoszyk();
        }
    }

    void wyswietlKategorie()
    {
        Kategoria * kategoria;

        system("cls");
        cout << "SKLEP -> MENU GLOWNE -> KATEGORIE" <<endl;
        cout << "Wybierz kategorie" << endl;
        cout << "1. Odziez" << endl;
        cout << "2. Meble" << endl;
        cout << "3. Sprzet sportowy" << endl;
        cout << "4. Wyjdz" << endl;
        int wybor;
        cin >> wybor;
        switch (wybor)
        {
        case 1:
            kategoria = new KategoriaOdziez();
            break;
        case 2:
            kategoria = new KategoriaMeble();
            break;

        case 3:
            kategoria = new KategoriaSport();
            break;
        case 4:
            wyswietlMenuGlowne();
        }

        kategoria->odczytajZPliku();
        kategoria->sortuj();
        kategoria->wyswietlKategorie();

        cout << "Ktory produkt chcesz wybrac? " <<endl;


        int numerProduktu;
        cin >> numerProduktu;
        if (numerProduktu>=1 and numerProduktu <= kategoria->pobierzIloscProduktow()){
            Produkt *p = kategoria->pobierzProduktZKategorii(numerProduktu);
            koszyk->dodajProdukt(p);
        }
        else{
            cout << "Nieprawidlowy numer produktu. Powrot do Menu glownego";
            getchar();
        }

        delete kategoria;
//        //system("cls");
//        cout << "Stan Twojego koszyka:" <<endl;
//        koszyk.wyswietl();
        wyswietlMenuGlowne();

    }


};



int main()
{


    Sklep sklep;
    sklep.wyswietlMenuGlowne();

    return 0;
}
