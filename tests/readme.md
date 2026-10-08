# Proiect FixItNow - Date de Testare

Acest folder contine fisierele de intrare (CSV) utilizate pentru a testa functionalitatea si robustetea aplicatiei de service "FixItNow".

## 1. Fisierul `angajati.csv`
Acest fisier contine lista personalului service-ului. Aplicatia incarca acesti angajati la pornire.

**Scenarii Testate:**

* **Angajati Valizi:** Contine echipa minima necesara pentru rulare (3 Tehnicieni, 1 Receptioner, 1 Supervizor), cu CNP-uri valide si date corecte.
* **Validare CNP:** Testeaza algoritmul de validare a CNP-ului (verificarea cifrei de control, lungimea de 13 caractere, continut exclusiv numeric).
* **Format Invalid:** Linii care contin erori de sintaxa sau date lipsa sunt detectate si raportate in consola fara a opri executia programului (Eroare "Silent Skip" sau "Exception Catch").

## 2. Fisierul `cereri.csv`
Acest fisier simuleaza clientii care vin la service cu aparate defecte.

**Scenarii Testate:**

* **Cereri Valide:** Include o varietate de electrocasnice (Frigider, MasinaSpalat, Televizor) cu specificatii corecte.
* **Tipuri Necunoscute:** Testeaza reactia sistemului la aparate pe care service-ul nu le repara (ex: "CuptorMicrounde"), generand mesaje de eroare specifice.
* **Validare Tipuri de Date:** Testeaza robustetea citirii (ex: introducerea unui text "DOUAMII" in campul de pret sau "Mica" in campul capacitate), demonstrand gestionarea exceptiilor (`try-catch` pe `stod`/`stoi`).
* **Factory Pattern:** Verifica daca `ElectrocasnicFactory` instantiaza corect obiectele sau returneaza `nullptr` in caz de erori.

## Rulare
La pornirea aplicatiei `./proiect`, aceste fisiere sunt citite automat. Orice linie invalida va genera un mesaj de eroare in consola cu prefixul `[EROARE IMPORT]`, demonstrand capacitatea aplicatiei de a filtra datele corupte.