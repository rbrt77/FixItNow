
#include "cerere.h"
#include <string>


int Cerere::generatorId = 1;

Cerere::Cerere(Electrocasnic* ap, int gradComplexitate) : idCerere(generatorId++), aparat(ap), complexitate(gradComplexitate)
{
    this->timestamp = genereazaTimestamp();
    
    this->status = StatusCerere::InAsteptare; 
    this->idTehnicianAsignat = -1; 

    int vechime = 2026 - aparat->getAn(); 
    if (vechime < 1) vechime = 1; 

    this->durataEstimata = vechime * this->complexitate;
    this->pretReparatie = aparat->getPret() * this->durataEstimata;
}

Cerere::~Cerere() {
    if (aparat != nullptr) {
        delete aparat;
    }
}

string Cerere::genereazaTimestamp() {
    time_t now = time(0); //cate sec au trecut din 1970 pana acum
    tm* ltm = localtime(&now); //sparge in an/zi/... (tm - are tm_year, ..., tm_sec)
 
    string data = to_string(ltm->tm_mday) + "/"   //1-31
                + to_string(1 + ltm->tm_mon) + "/"  // lunile de la 0 la 11
                + to_string(1900 + ltm->tm_year) + " " //incepe cu 1900 ca an 0
                + to_string(ltm->tm_hour) + ":" 
                + to_string(ltm->tm_min) + ":" 
                + to_string(ltm->tm_sec);
    
    return data;
}


int Cerere::getId() const { 
    return idCerere; 
}

Electrocasnic* Cerere::getAparat() const {
     return aparat; 
}

string Cerere::getTimestamp() const { 
    return timestamp;
 }
int Cerere::getDurataEstimata() const { 
    return durataEstimata; 
}

double Cerere::getPret() const { 
    return pretReparatie; 
}

StatusCerere Cerere::getStatus() const { 
    return status; 
}

int Cerere::getIdTehnician() const { 
    return idTehnicianAsignat; 
}


void Cerere::setStatus(StatusCerere s) {
    this->status = s;
}

void Cerere::setTehnician(int id) {
    this->idTehnicianAsignat = id;
    this->status = StatusCerere::Asignata; 
}

void Cerere::scadeDurata(int secunde) {
    if (durataEstimata > 0) {
        durataEstimata -= secunde;
    }
}


void Cerere::afisare(ostream& os) const {
    os << "Cerere #" << idCerere << " | " << timestamp << endl;
    
    if (aparat != nullptr) {
        os << "Aparat: " << aparat->getMarca() << " " << aparat->getModel() 
           << " (Pret reparatie: " << pretReparatie << " RON)" << endl;
    }

    os << "Durata ramasa: " << durataEstimata << " sec | Complexitate: " << complexitate << endl;
    
    os << "Status: ";
 
    switch (status) {
        case StatusCerere::InAsteptare: os << "IN ASTEPTARE"; break;
        case StatusCerere::Asignata:    os << "ASIGNATA (Tehnician " << idTehnicianAsignat << ")"; break;
        case StatusCerere::Finalizata:  os << "FINALIZATA"; break;
        case StatusCerere::Imposibila:  os << "IMPOSIBILA"; break;
    }
    os << endl;
}