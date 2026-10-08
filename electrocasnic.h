#pragma once
#include <iostream>
#include <string>
#include "auxiliar.h" 
using namespace std;


class Electrocasnic {
protected:

    TipElectrocasnic tip;
    string marca;
    string model;
    int anFabricatie;
    double pretCatalog;


public:
   
    Electrocasnic(TipElectrocasnic t, string m, string mod, int an, double pret);
    
    virtual ~Electrocasnic() = default;
    virtual void afisare(ostream& os) const = 0;
    virtual string getDetaliiSpecifice() const = 0;

    TipElectrocasnic getTip() const;
    string getMarca() const;
    string getModel() const;
    int getAn() const;
    double getPret() const;
};