#pragma once
#include <string>
#include "electrocasnic.h"
#include "frigider.h"
#include "masinaspalat.h"
#include "televizor.h"
using namespace std;

class ElectrocasnicFactory {
public:


    // 1.frigider
    static Electrocasnic* creareFrigider(string marca, string model, int an, double pret, bool areCongelator) {
        return new Frigider(marca, model, an, pret, areCongelator);
    }

    // 2.masina spalat
    static Electrocasnic* creareMasinaSpalat(string marca, string model, int an, double pret, double capacitate) {
        return new MasinaSpalat(marca, model, an, pret, capacitate);
    }

    // 3.televizor
    static Electrocasnic* creareTelevizor(string marca, string model, int an, double pret, double diagonala) {
        return new Televizor(marca, model, an, pret, diagonala);
    }
};