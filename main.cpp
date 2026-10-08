#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <limits> // Pentru numeric_limits

#include "service.h"
#include "receptioner.h"
#include "supervizor.h"
#include "tehnician.h"
#include "electrocasnic_factory.h" 
#include "auxiliar.h"

using namespace std;

// citire, separare csv


vector<string> separaText(const string& textSursa, char delimitator) {
    vector<string> rezultate;
    string bucata;
    istringstream fluxDate(textSursa); //ca sa mearga cu getline
    
    while (getline(fluxDate, bucata, delimitator)) {
        rezultate.push_back(bucata);
    }
    return rezultate;
}

void incarcaAngajatiDinFisier(string numeFisier) {
    Service* s = Service::getInstanta();
    ifstream file(numeFisier);

    if (!file.is_open()) {
        cout << "[INFO] Fisierul " << numeFisier << " nu exista. Se porneste cu baza de date goala." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue; 

        try {
            // TIP,NUME,PRENUME,CNP,ZI,LUNA,AN,ORAS,COMPETENTE
            vector<string> date = separaText(line, ',');
            if (date.size() < 8) continue; 

            string tip = date[0];
            string nume = date[1];
            string prenume = date[2];
            string cnp = date[3];
            int z = stoi(date[4]);
            int l = stoi(date[5]);
            int a = stoi(date[6]);
            string oras = date[7];

            if (tip == "Tehnician") {
                Tehnician* t = new Tehnician(nume, prenume, cnp, {z, l, a}, oras);
                // competente(Frigider-Arctic|TV-Samsung)
                if (date.size() > 8) {
                    string competenteRaw = date[8];
                    vector<string> compList = separaText(competenteRaw, '|');
                    for (const auto& c : compList) {
                        vector<string> pair = separaText(c, '-');
                        if (pair.size() == 2) {
                            t->adaugaCompetenta(pair[0], pair[1]);
                        }
                    }
                }
                s->angajeazaTehnician(t);
            }

            else if (tip == "Receptioner") {
                Receptioner* r = new Receptioner(nume, prenume, cnp, {z, l, a}, oras);
                s->angajeazaReceptioner(r); 
            }

            else if (tip == "Supervizor") {
                Supervizor* sup = new Supervizor(nume, prenume, cnp, {z, l, a}, oras);
                s->angajeazaSupervizor(sup); 
            }
        }
        catch (exception& e) {
            cout << "[EROARE IMPORT] Linia: " << line << " -> " << e.what() << endl;
        }
    }
    file.close();
}

void incarcaCereriDinFisier(string numeFisier) {
    Service* s = Service::getInstanta();
    ifstream file(numeFisier);

    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        try {
            // TIP_APP,MARCA,MODEL,AN,PRET,SPECIFIC,COMPLEXITATE
            vector<string> date = separaText(line, ',');
            if (date.size() < 7) continue;

            string tipApp = date[0];
            string marca = date[1];
            string model = date[2];
            int an = stoi(date[3]);
            double pret = stod(date[4]);
            
            Electrocasnic* el = nullptr;

            
            if (tipApp == "Frigider") {
                bool areCongelator = (stoi(date[5]) == 1);
                el = ElectrocasnicFactory::creareFrigider(marca, model, an, pret, areCongelator);
            }
            else if (tipApp == "MasinaSpalat") {
                double capacitate = stod(date[5]);
                el = ElectrocasnicFactory::creareMasinaSpalat(marca, model, an, pret, capacitate);
            }
            else if (tipApp == "Televizor") {
                double diagonala = stod(date[5]);
                el = ElectrocasnicFactory::creareTelevizor(marca, model, an, pret, diagonala);
            }
            else {
                
                cout << "[EROARE IMPORT CERERE] " << line << " -> Tip aparat necunoscut: " << tipApp << endl;
                continue;
            }

            if (el != nullptr) {
                int complexitate = stoi(date[6]);
                Cerere* c = new Cerere(el, complexitate);
                s->primesteCerere(c);
            }

        } catch (exception& e) {
             cout << "[EROARE IMPORT CERERE] " << line << " -> " << e.what() << endl;
        }
    }
    file.close();
}


void meniuGestiuneAngajati() {
    Service* s = Service::getInstanta();
    int opt = -1;
    while (opt != 0) {
        cout << "\n--- SUBMENIU: GESTIUNE ANGAJATI ---" << endl;
        cout << "1. Angajare Tehnician" << endl;
        cout << "2. Angajare Receptioner" << endl;
        cout << "3. Angajare Supervizor" << endl;
        cout << "4. Afisare Lista Completa Angajati" << endl;
        cout << "0. Inapoi la meniul principal" << endl;
        cout << "Optiune: ";
        
        if (!(cin >> opt)) {
            cout << "Input invalid!" << endl;
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //goleste si ignora bufferul cu date gresite \n
            continue;
        }

        // globale in fct
        string n, p, cnp, oras;
        int z, l, a;

        switch (opt) {
            case 1: { // TEHNICIAN
                try {
                    cout << ">> Date Tehnician: Nume Prenume CNP Zi Luna An Oras: ";
                    cin >> n >> p >> cnp >> z >> l >> a >> oras;
                    
                    Tehnician* t = new Tehnician(n, p, cnp, {z, l, a}, oras);
                    
                    cout << "Adaugi competenta? (1-Da, 0-Nu): ";
                    int dec; cin >> dec;
                    if (dec == 1) {
                        string tip, marca;
                        cout << "Tip (ex: Frigider) Marca (ex: Arctic): "; 
                        cin >> tip >> marca;
                        t->adaugaCompetenta(tip, marca);
                    }
                    s->angajeazaTehnician(t);
                    cout << "[OK] Tehnician adaugat." << endl;
                } catch (exception& e) { cout << "Eroare: " << e.what() << endl; }
                break;
            }

            case 2: { // RECEPTIONER
                try {
                    cout << ">> Date Receptioner: Nume Prenume CNP Zi Luna An Oras: ";
                    cin >> n >> p >> cnp >> z >> l >> a >> oras;
                    
                    Receptioner* r = new Receptioner(n, p, cnp, {z, l, a}, oras);
                    s->angajeazaReceptioner(r);
                    cout << "[OK] Receptioner adaugat." << endl;
                } catch (exception& e) { cout << "Eroare: " << e.what() << endl; }
                break;
            }

            case 3: { // SUPERVIZOR
                try {
                    cout << ">> Date Supervizor: Nume Prenume CNP Zi Luna An Oras: ";
                    cin >> n >> p >> cnp >> z >> l >> a >> oras;
                    
                    Supervizor* sup = new Supervizor(n, p, cnp, {z, l, a}, oras);
                    s->angajeazaSupervizor(sup);
                    cout << "[OK] Supervizor adaugat." << endl;
                } catch (exception& e) { cout << "Eroare: " << e.what() << endl; }
                break;
            }

            case 4:
                s->afiseazaTotiAngajatii();
                break;

            case 0: break;
            default: cout << "Optiune invalida." << endl;
        }
    }
}

void meniuGestiuneCereri() {
    Service* s = Service::getInstanta();
    int opt = -1;
    while (opt != 0) {
        cout << "\n--- SUBMENIU: PROCESARE CERERI ---" << endl;
        cout << "1. Inregistrare Cerere Noua" << endl;
        cout << "2. Alocare Automata Task-uri" << endl;
        cout << "3. Simulare Trecere Timp" << endl;
        cout << "0. Inapoi" << endl;
        cout << "Optiune: ";
        cin >> opt;

        switch (opt) {
            case 1: {
                cout << "\n>> Tip aparat (1-Frigider, 2-MasinaSpalat, 3-TV): ";
                int tip; cin >> tip;
                
                string marca, model;
                int an;
                double pret;
                
                cout << "Marca: "; cin >> marca;
                cout << "Model: "; cin >> model;
                cout << "An fabricatie: "; cin >> an;
                cout << "Pret catalog: "; cin >> pret;
                
                Electrocasnic* el = nullptr;

                if (tip == 1) {
                    bool cong; 
                    cout << "Are congelator? (1-Da, 0-Nu): "; cin >> cong;
                    el = ElectrocasnicFactory::creareFrigider(marca, model, an, pret, cong);
                }
                else if (tip == 2) {
                    double cap; 
                    cout << "Capacitate (kg): "; cin >> cap;
                    el = ElectrocasnicFactory::creareMasinaSpalat(marca, model, an, pret, cap);
                }
                else if (tip == 3) {
                    double diag; 
                    cout << "Diagonala (cm): "; cin >> diag;
                    el = ElectrocasnicFactory::creareTelevizor(marca, model, an, pret, diag);
                }

                if (el != nullptr) {
                    int complexitate;
                    cout << "Grad complexitate (1-5): "; cin >> complexitate;
                    if(complexitate < 1 || complexitate > 5) 
                        complexitate = 1;

                    Cerere* c = new Cerere(el, complexitate);
                    s->primesteCerere(c);
                    cout << "[SUCCES] Cererea a fost inregistrata si pusa in asteptare." << endl;
                } else {
                    cout << "[EROARE] Tip electrocasnic invalid!" << endl;
                }
                break;
            }

            case 2:
                cout << ">> Se ruleaza algoritmul de asignare..." << endl;
                s->asigneazaTaskuri();
                break;

            case 3:
                int minute;
                cout << ">> Cate minute vrei sa simulezi?: ";
                cin >> minute;
                if (minute > 0)
                    s->simuleazaTrecereaTimpului(minute);
                else
                    cout << "[EROARE] Timpul trebuie sa fie pozitiv." << endl;
                break;

            case 0: 
                break;

            default: cout << "Optiune invalida." << endl;
        }
    }
}

void meniuRaportare() {
    Service* s = Service::getInstanta();
    int opt = -1;
    while (opt != 0) {
        cout << "\n--- SUBMENIU: RAPOARTE ---" << endl;
        cout << "1. Raport Complet (Angajati + Stare Cereri)" << endl;
        cout << "0. Inapoi" << endl;
        cout << "Optiune: ";
        cin >> opt;

        switch(opt) {
            case 1:
                s->afisareStatusComplet();
                break;
            case 0: break;
            default: cout << "Optiune invalida." << endl;
        }
    }
}





int main() {
    Service* service = Service::getInstanta();

    cout << "============================================" << endl;
    cout << "   BUN VENIT LA SERVICE-UL 'FixItNow' " << endl;
    cout << "============================================" << endl;

   
    incarcaAngajatiDinFisier("angajati.csv");
    incarcaCereriDinFisier("cereri.csv");
    
    cout << "[SISTEM] Datele initiale au fost incarcate." << endl;

    int optiune = -1;
    while (optiune != 0) {
  
        cout << "\n### MENIU PRINCIPAL ###" << endl;
        cout << "1. Gestiune Angajati" << endl;
        cout << "2. Procesare Cereri (Service)" << endl;
        cout << "3. Raportare" << endl;
        cout << "0. Iesire din aplicatie" << endl;
        cout << "Alege o actiune: ";
        
   
        if (!(cin >> optiune)) {
            cout << "Input invalid! Introduceti o cifra." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignora si scoate, trece dupa
            continue;
        }

        switch (optiune) {
            case 1:
                meniuGestiuneAngajati();
                break;
            
            case 2:
                if (!service->poateFunctiona()) {
                    cout << "\n[EROARE CRITICA] Service-ul nu poate functiona!" << endl;
                    cout << "Necesita MINIM: 3 Tehnicieni, 1 Receptioner, 1 Supervizor." << endl;
                    cout << "Foloseste meniul 'Gestiune Angajati' pentru a completa echipa sau verifica fisierul 'angajati.txt'." << endl;
                } 
                else 
                    meniuGestiuneCereri();
                break;
            

            case 3:
                meniuRaportare();
                break;
            

            case 0:
                cout << "La revedere! Se elibereaza memoria..." << endl;
                break;
            
            default:
                cout << "Optiune inexistenta. Incearca din nou." << endl;
        }
    }

    delete service; 
    
    
    return 0;
}