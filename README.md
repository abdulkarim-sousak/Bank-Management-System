# 🏦 Bank Management System (C++)

A robust and efficient **Command Line Interface (CLI)** application built in C++ to manage bank client records. This project demonstrates core programming concepts such as **File Handling**, **Dynamic Data Structures (Vectors)**, **Structs**, and **String Manipulation**.

---

## Features

### Client Management
- **Show Client List**: Display all clients stored in the system with formatted output.
- **Add New Client**: Add new clients with validation to prevent duplicate account numbers.
- **Delete Client**: Mark clients for deletion and update the file storage.
- **Update Client Info**: Modify client details such as PIN, name, phone, and balance.
- **Find Client**: Search for a client by account number and display their details.

### Transactions
- **Deposit**: Add funds to a client’s account.
- **Withdraw**: Deduct funds from a client’s account with balance validation.
- **Total Balance**: Display the balance of all clients and calculate the total across the system.

 
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

## 📖 Usage Instructions

1.  Upon launching, you will be presented with the **Main Menu**.
2.  Enter a choice from **[1] to [6]** to navigate through the system.
3.  When adding/updating, follow the prompts carefully.
4.  To ensure all changes are saved and the program closes correctly, always use option **[6] Exit**.

---

**Developed with ❤️ in C++**