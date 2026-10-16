# 🛠️ FixItNow - Electronics Service Management System

Terminal-based C++17 application that simulates the backend of an electronics repair shop. Built as a university project for the Object-Oriented Programming course (UPB), developed in autumn 2025 and documented in January 2026 (see `documentatie.pdf` and `en_documntation.pdf`).

## 🧠 Architecture

- **Singleton `Service`:** the single instance (`Service::getInstanta()`) owns the vectors of technicians, receptionists, supervisors and repair requests. Everything is released through destructors when the program exits (`Service` deletes its requests, and each request deletes its appliance).
- **Factory for appliances:** `ElectrocasnicFactory` provides static creation methods (`creareFrigider`, `creareMasinaSpalat`, `creareTelevizor`) that return `Electrocasnic*`. The appliance type is chosen from the CSV data in `main.cpp`.
- **Polymorphism for employees:** the abstract class `Angajat` (pure virtual `calculeazaSalariu()` and `afisare()`, virtual destructor) is inherited by `Tehnician`, `Receptioner` and `Supervizor`. Salary = base salary + seniority and transport bonuses; technicians also get 2% of the value of the repairs they complete, and supervisors a management bonus.

## ⚙️ Features

- **Task assignment:** each pending request goes to the available technician with the least accumulated work time.
- **Time simulation:** advances time by a number of minutes and counts down active repairs; when a repair ends the technician becomes available and receives the bonus.
- **Request model:** estimated duration (seconds) = max(1, 2026 − appliance year) × complexity; repair price = catalog price × duration.
- **CSV import:** employees and requests are loaded from `angajati.csv` and `cereri.csv`. Malformed lines (for example text where a number is expected) are reported with `[EROARE IMPORT]` and skipped; the rest of the file is still loaded. Lines with too few fields are skipped silently.
- **Validation:** Romanian ID numbers (CNP) are checked for length, digits only and the control digit; names must have 3-30 characters. The main menu and the employees menu clear bad console input with `cin.clear()` and `cin.ignore()`.

## 🚀 Build and run

```bash
git clone https://github.com/rbrt77/FixItNow.git
cd FixItNow
g++ -std=c++17 *.cpp -o fixitnow
./fixitnow
```

The service menu is available only if the loaded data contains at least 3 technicians, 1 receptionist and 1 supervisor.

## 📄 Data files

- Employees: `TIP,NUME,PRENUME,CNP,ZI,LUNA,AN,ORAS,COMPETENTE` (competencies as `Frigider-Arctic|TV-Samsung`)
- Requests: `TIP_APP,MARCA,MODEL,AN,PRET,SPECIFIC,COMPLEXITATE`

The `tests/` folder contains input files with valid data and intentionally malformed lines (invalid CNP, text in numeric fields, unknown appliance type); see `tests/readme.md` and copy them over the root CSV files to try them.

## ⚠️ Limitations

- Console application without persistence.
- Technician competencies are stored but not used when assigning requests.
- The reference year (2026) is hard-coded in the seniority bonus and in the request duration.
- The PDFs describe the submitted design; where they differ from the code (for example factory creation "from a string", assignment by "fewest active tasks", or sorted salary reports), the code and this README are authoritative.

## 🕘 Repository history

This project was developed between autumn 2025 and January 2026 and was first uploaded to GitHub in October 2026. The commits were created at upload time to follow the order in which the project was built (base classes, derived entities and factory, service logic, entry point, documentation); their dates are the upload date, not the development dates.