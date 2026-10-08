#include "angajat.h"
#include <stdexcept> // pt invalid


// init global!!!!!
int Angajat::numarTotalAngajati = 0;
int Angajat::generatorId = 0;


// constr CU VERIFICARI!!
Angajat::Angajat(string n, string p, string c, Data da, string oras) : idAngajat(generatorId++), nume(n), prenume(p), cnp(c), dataAngajare(da), orasDomiciliu(oras)
{
    numarTotalAngajati++;

    // valid nume
    if (nume.length() < 3 || nume.length() > 30)  /*lungime de <string>*/  {
        numarTotalAngajati--;
        throw runtime_error("Nume invalid (trebuie intre 3 si 30 caractere)");
    }

    // valid prenume
    if (prenume.length() < 3 || prenume.length() > 30)  /*lungime de <string>*/  {
        numarTotalAngajati--;
        throw runtime_error("Prenume invalid (trebuie intre 3 si 30 caractere)");
    }

    // valid CNP

    //1) lugime string
    if (cnp.length() != 13) 
    {
        numarTotalAngajati--;
        throw runtime_error("CNP invalid (lungime incorecta, trebuie 13)");
    }

    //2) tip de elemente(doar cifre)
    for (int i = 0; i < 13; i++) 
    {
        if (cnp[i] < '0' || cnp[i] > '9') {
            numarTotalAngajati--;
            throw runtime_error("CNP invalid (contine caractere non-numerice)");
        }
    }


    //3) coditie validare suma/rest finala

    int constanta[12] = {2, 7, 9, 1, 4, 6, 3, 5, 8, 2, 7, 9}; //data exact deja - constanta "279146358279"
    long suma = 0;

    // suma prod primele 12
    for (int i = 0; i < 12; i++) {
        int cifraCNP = cnp[i] - '0'; // converteste automat in int(==scad in ascii 48)
        suma += cifraCNP * constanta[i];
    }

    // rest /11
    int rest = suma % 11;
    
    // cifra control C
    int cifraControlCalculata;
    if (rest == 10) {
        cifraControlCalculata = 1;
    } else {
        cifraControlCalculata = rest;
    }

    // cifra control reala C
    int cifraControlReala = cnp[12] - '0';

    // C reala si C calculata
    if (cifraControlCalculata != cifraControlReala) {
        numarTotalAngajati--;
        throw runtime_error("CNP invalid (cifra de control incorecta)");
    }

}




Angajat::~Angajat() {
    numarTotalAngajati--; 
}


int Angajat::getNumarAngajati() {
    return numarTotalAngajati;
}


double Angajat::getSalariuComun() const {
    
    double salariu = SALARIU_BAZA_FIX; // init 4000
    int aniVechime = 2026 - dataAngajare.an;
    
    //bonus vechime
    if (aniVechime > 0) {
        int seturiAni = aniVechime / ANI_FIDELITATE;   //cate 3 e un set
        salariu += (SALARIU_BAZA_FIX * BONUS_FIDELITATE_PROCENT * seturiAni);
    }

    //bonus transport
    if (orasDomiciliu != "Bucuresti" && orasDomiciliu != "BUCURESTI" && orasDomiciliu != "bucuresti") {
        salariu += PRIMA_TRANSPORT; // +400 RON
    }

    return salariu;
}


int Angajat::getId() const { 
    return idAngajat; 
}

string Angajat::getNumeComplet() const { 
    return nume + " " + prenume; 
}

string Angajat::getCnp() const { 
    return cnp; 
}

string Angajat::getOras() const { 
    return orasDomiciliu; 
}

Data Angajat::getDataAngajare() const {
    return dataAngajare;
}