#include "service.h"

Service* Service::instantaUnica = nullptr;

Service* Service::getInstanta() {
    if (instantaUnica == nullptr) {
        instantaUnica = new Service();
    }
    return instantaUnica;
}

Service::Service() {}

Service::~Service() {

    for (size_t i = 0; i < tehnicieni.size(); i++) delete tehnicieni[i];
    tehnicieni.clear();


    for (size_t i = 0; i < receptioneri.size(); i++) delete receptioneri[i];
    receptioneri.clear();


    for (size_t i = 0; i < supervizori.size(); i++) delete supervizori[i];
    supervizori.clear();


    for (size_t i = 0; i < cereri.size(); i++) delete cereri[i];
    cereri.clear();

    cout << "Service-ul s-a inchis si a eliberat memoria." << endl;
}

void Service::angajeazaTehnician(Tehnician* t) {
    tehnicieni.push_back(t);
}

void Service::angajeazaReceptioner(Receptioner* r) {
    receptioneri.push_back(r);
}

void Service::angajeazaSupervizor(Supervizor* s) {
    supervizori.push_back(s);
}


void Service::primesteCerere(Cerere* c) {
    cereri.push_back(c);
    
    if (!receptioneri.empty()) {
        receptioneri[0]->adaugaCerere(c->getId());
    }
}


bool Service::poateFunctiona() const {
    if (tehnicieni.size() < 3) 
        return false;
    if (receptioneri.size() < 1) 
        return false;
    if (supervizori.size() < 1) 
        return false;
    return true;
}

Receptioner* Service::getReceptionerDisponibil() {
    if (receptioneri.empty()) 
        return nullptr;
    return receptioneri[0];
}

void Service::afiseazaTotiAngajatii() const {
    cout << "\n=== LISTA COMPLETA ANGAJATI ===" << endl;
    for (size_t i = 0; i < supervizori.size(); i++) supervizori[i]->afisare(cout);
    for (size_t i = 0; i < receptioneri.size(); i++) receptioneri[i]->afisare(cout);
    for (size_t i = 0; i < tehnicieni.size(); i++) tehnicieni[i]->afisare(cout);
    cout << "===============================\n" << endl;
}


void Service::asigneazaTaskuri() {
    for (size_t i = 0; i < cereri.size(); i++) {
        
        if (cereri[i]->getStatus() == StatusCerere::InAsteptare) {
        
            Tehnician* celMaiLiberTehnician = nullptr;
            long minMunca = 2000000000; // pt min initial

            for (size_t j = 0; j < tehnicieni.size(); j++) {
                if (tehnicieni[j]->eDisponibil()) {
                    if (tehnicieni[j]->getDurataMunca() < minMunca) 
                    {
                        minMunca = tehnicieni[j]->getDurataMunca();
                        celMaiLiberTehnician = tehnicieni[j];
                    }
                }
            }

            if (celMaiLiberTehnician != nullptr) {
                
                cereri[i]->setTehnician(celMaiLiberTehnician->getId());
                cereri[i]->setStatus(StatusCerere::Asignata);

                celMaiLiberTehnician->asigneazaCerere(cereri[i]->getId(), cereri[i]->getDurataEstimata());

                cout << ">> [ALOCARE] Cererea " << cereri[i]->getId() 
                     << " -> " << celMaiLiberTehnician->getNumeComplet() 
                     << " (Istoric total: " << celMaiLiberTehnician->getDurataMunca() << " sec)" << endl;
            }
        }
    }
}


void Service::simuleazaTrecereaTimpului(int minute) {
    int secundeSimulate = minute * 60; 

    cout << "--- Trec " << minute << " minute (" << secundeSimulate << " sec) ---" << endl;


    for (size_t j = 0; j < tehnicieni.size(); j++) {
        if (!tehnicieni[j]->eDisponibil()) {
            int idCerere = tehnicieni[j]->getIdCerereCurenta();

            Cerere* cerereActuala = nullptr;
            for (size_t i = 0; i < cereri.size(); i++) {
                if (cereri[i]->getId() == idCerere) {
                    cerereActuala = cereri[i];
                    break;
                }
            }

            if (cerereActuala != nullptr) {

                cerereActuala->scadeDurata(secundeSimulate);
                if (cerereActuala->getDurataEstimata() <= 0) {
                    cerereActuala->setStatus(StatusCerere::Finalizata);
                    tehnicieni[j]->adaugaReparatieLaSalariu(cerereActuala->getPret());

                    while(!tehnicieni[j]->eDisponibil()) {
                         tehnicieni[j]->executaTic(); 
                    }

                    cout << "!! [FINALIZAT] Cererea " << cerereActuala->getId() 
                         << " terminata de " << tehnicieni[j]->getNumeComplet() 
                         << ". Bonus adaugat!" << endl;
                }
            }
        }
    }
}

void Service::afisareStatusComplet() const {
    // Aici folosim functia noua ca sa vedem TOTI angajatii
    afiseazaTotiAngajatii();

    cout << "\nCERERI:" << endl;
    for (size_t i = 0; i < cereri.size(); i++) {
        cereri[i]->afisare(cout); 
        cout << "-----------------" << endl;
    }
}