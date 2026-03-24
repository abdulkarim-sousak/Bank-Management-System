# 🏦 Bank Management System (C++)

A robust and efficient **Command Line Interface (CLI)** application built in C++ to manage bank client records. This project demonstrates core programming concepts such as **File Handling**, **Dynamic Data Structures (Vectors)**, **Structs**, and **String Manipulation**.

---

## 🚀 Features

The system provides a complete **CRUD** (Create, Read, Update, Delete) functionality for managing bank clients:

* **[1] Show Client List:** Displays all registered clients in a formatted table with details like Account Number, PIN, Name, and Balance.
* **[2] Add New Client:** Allows adding new clients with unique account numbers. It includes a built-in validation to prevent duplicate IDs.
* **[3] Delete Client:** Safely removes a client from the system after confirmation.
* **[4] Update Client Info:** Allows modifying existing client details (PIN, Name, Phone, and Balance).
* **[5] Find Client:** Quickly search for and display a specific client’s details using their account number.
* **[6] Data Persistence:** All data is saved in a structured text file (`Clients.txt`), ensuring data is preserved after closing the program.

---

## 🛠️ Technical Implementation

* **Data Storage:** Uses a flat-file database using `#//#` as a custom separator for data parsing.
* **Memory Management:** Utilizes `std::vector` to handle records dynamically during runtime.
* **Formatting:** Uses `<iomanip>` to ensure the console output is aligned and professional.
* **Input Validation:** Checks for existing account numbers before adding new records to maintain data integrity.

---

## 📁 File Structure

* `main.cpp`: The core source code containing the logic and UI.
* `Clients.txt`: The database file where client records are stored in the following format:
    > `AccountNumber#//#PinCode#//#Name#//#Phone#//#Balance`

---

## 💻 How to Run

1.  **Prerequisites:** Ensure you have a C++ compiler installed (e.g., GCC, Clang, or MSVC).
2.  **Compile the code:**
    ```bash
    g++ -o BankSystem main.cpp
    ```
3.  **Run the application:**
    ```bash
    ./BankSystem
    ```

---

## 📖 Usage Instructions

1.  Upon launching, you will be presented with the **Main Menu**.
2.  Enter a choice from **[1] to [6]** to navigate through the system.
3.  When adding/updating, follow the prompts carefully.
4.  To ensure all changes are saved and the program closes correctly, always use option **[6] Exit**.

---

## 📝 Planned Improvements
* [ ] Implementation of a **Transactions Menu** (Deposit/Withdraw).
* [ ] User Authentication (Admin Login).
* [ ] Encryption for PIN codes.

---
**Developed with ❤️ in C++**