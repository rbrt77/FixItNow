# 🛠️ FixItNow - Electronics Service Management System

This is a terminal-based C++17 application I built to simulate the backend operations of an electronics repair shop. My main goal with this project was to implement core Object-Oriented Programming principles and practical design patterns in a realistic, data-driven scenario.

## 🧠 Technical Architecture & Decisions

Instead of writing everything in a procedural way, I structured the app modularly, separating the business logic from the data entities.

* **The Singleton Controller:** The `Service` class acts as the single source of truth for the application. It holds the dynamically managed vectors of employees and repair requests. I used the Singleton pattern here to ensure there's only one state of the service running at any time, preventing data duplication and conflicts across the app.
* **Factory Method for Appliances:** I wanted to avoid huge `switch` or `if-else` chains when creating appliances. The `ElectrocasnicFactory` takes a string (e.g., "Frigider") and returns the correct derived object, decoupling the instantiation logic from the main flow.
* **Polymorphism in HR:** The base abstract class `Angajat` is inherited by `Tehnician`, `Receptioner`, and `Supervizor`. Each derived class overrides the virtual `calculeazaSalariu()` method to handle its own specific coefficients and financial bonuses.

## ⚙️ Key Features

* **Smart Load Balancing:** When assigning tasks, the system doesn't just pick a random technician. It scans the pending requests and assigns the job to the technician with the lowest active workload to ensure fair distribution.
* **Time Simulation (Tick System):** I added a feature to advance time by a specific number of minutes. This dynamically decrements the remaining repair times. When a repair hits 0, the technician's status automatically updates to available, and their financial bonus is processed.
* **Fault-Tolerant CSV Parsing:** The system loads initial data from `angajati.csv` and `cereri.csv`. I implemented strict `try-catch` blocks so if a CSV line is malformed (e.g., text where a number should be), the app catches the `stod failed` error, logs it, and continues loading the rest of the data instead of crashing.
* **Strict Data Validation:** Includes a custom algorithm to validate Romanian ID numbers (CNP), checking length, non-numeric characters, and the control digit. It also uses `cin.clear()` and `cin.ignore()` to prevent infinite loops on bad keyboard inputs.

## 🚀 How to Build and Run

You will need a C++17 compatible compiler (like `g++`).

```bash
git clone [https://github.com/rbrt77/FixItNow.git](https://github.com/rbrt77/FixItNow.git)
cd FixItNow
g++ *.cpp -o fixitnow
./fixitnow




Note: To access the main service operations menu, the loaded CSV data must contain a minimum viable team (at least 3 technicians, 1 receptionist, and 1 supervisor).

Author's Note regarding repository history:
This project was originally developed and finalized between October 2025 and January 2026. Due to losing access to my original GitHub account, I have re-uploaded the project here. I carefully recreated the original atomic commits and file structure to accurately reflect the true development timeline and the architectural steps taken during that period.