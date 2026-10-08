#pragma once
#include <iostream>
#include <vector>
#include "tehnician.h"
#include "cerere.h"
#include "receptioner.h"  
#include "supervizor.h"  
using namespace std;

class Service {
private:

    static Service* instantaUnica; // UN singur service posibil(singleton)
    Service(); //PRIVAT!!!!!!!!!!

    vector<Tehnician*> tehnicieni;
    vector<Receptioner*> receptioneri; 
    vector<Supervizor*> supervizori;   
    vector<Cerere*> cereri;
    //trb sa le uneasca

public:

    static Service* getInstanta(); //doar asa dam acces
    ~Service(); 


    void angajeazaTehnician(Tehnician* t);
    void primesteCerere(Cerere* c);
    void angajeazaReceptioner(Receptioner* r); 
    void angajeazaSupervizor(Supervizor* s);   


    bool poateFunctiona() const; 
    void afiseazaTotiAngajatii() const;
    Receptioner* getReceptionerDisponibil();

    void asigneazaTaskuri();        
    void simuleazaTrecereaTimpului(int minute); 
    
    void afisareStatusComplet() const;
};