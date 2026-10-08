#pragma once
#include <iostream>
#include <string>
#include <ctime>            //speciala timp
#include "electrocasnic.h"
#include "auxiliar.h"

using namespace std;

class Cerere {
private:
    static int generatorId; // pt toate

    const int idCerere;
    Electrocasnic* aparat; 
    
    string timestamp;      // in text
    int complexitate;      // 1-5
    

    int durataEstimata;    // secunde
    double pretReparatie;  // ron
    
    StatusCerere status;
    int idTehnicianAsignat; // DACA NU E NIMENI E -1 !!!!!!!!!!!!

    string genereazaTimestamp(); //face data/ora string

public:
  
    Cerere(Electrocasnic* ap, int complexitate);
    ~Cerere();

    int getId() const;
    Electrocasnic* getAparat() const;
    string getTimestamp() const;
    int getDurataEstimata() const;
    double getPret() const;
    StatusCerere getStatus() const;
    int getIdTehnician() const;

    void setStatus(StatusCerere s);
    void setTehnician(int idTehnician);
    
    void scadeDurata(int secunde); 

    void afisare(ostream& os) const;
};