# 🏦 Bank Management System (C++)

A robust **Command Line Interface (CLI)** application built in C++ for managing bank clients **and system users**. The system features role‑based access control, secure authentication, and full CRUD operations for both clients and users.

---

## Features

### 🔐 Authentication & Authorization
- **Login System** – Users must authenticate with a username and password.
- **Permission Model** – Granular permissions (bitmask) control access to:
  - List Clients
  - Add New Client
  - Delete Client
  - Update Client
  - Find Client
  - Transactions
  - Manage Users
- **Admin Account** – Pre‑configured `Admin` user with full permissions (cannot be deleted).

### 👥 Client Management
- **Show Client List**: Display all clients stored in the system with formatted output.
- **Add New Client**: Add new clients with validation to prevent duplicate account numbers.
- **Delete Client**: Mark clients for deletion and update the file storage.
- **Update Client Info**: Modify client details such as PIN, name, phone, and balance.
- **Find Client**: Search for a client by account number and display their details.

### 💰 Transactions
- **Deposit**: Add funds to a client’s account.
- **Withdraw**: Deduct funds from a client’s account with balance validation.
- **Total Balance**: Display the balance of all clients and calculate the total across the system.

### 👤 User Management (for administrators)
- **List Users** – Show all system users.
- **Add User** – Create new users with custom permissions (or full access).
- **Delete User** – Remove a user (except the `Admin` user).
- **Update User** – Change password and permissions.
- **Find User** – Search by username.

---

## 🛠️ Technical Implementation

- **Data Storage** – Flat files (`Clients.txt`, `Users.txt`) using `#//#` as a custom delimiter.
- **Memory Management** – `std::vector` to hold records dynamically.
- **String Parsing** – Custom `SplitString()` function to parse lines into structs.
- **Formatting** – `<iomanip>` for clean, aligned console output.
- **Validation** – Prevents duplicate account numbers / usernames and checks withdrawal limits.
- **Persistence** – All changes are immediately written back to the respective files.
- **Permissions** – Bitmask system (1,2,4,8,16,32,64) to combine privileges; `-1` grants full access.

---

## 📁 File Structure

| File          | Format                                                                 |
|---------------|------------------------------------------------------------------------|
| `main.cpp`    | Complete source code with all logic and UI screens.                    |
| `Clients.txt` | `AccountNumber#//#PinCode#//#Name#//#Phone#//#Balance`                 |
| `Users.txt`   | `UserName#//#Password#//#Permission` (permission is a bitmask integer) |

---

## 📖 Usage Instructions

1. **Compile** the program (any C++17 compiler).
2. **Run** the executable.
3. **Login** with your credentials (default `Admin` / `1234` or any user you create).
4. Use the **Main Menu** to navigate:
---

**Developed with ❤️ in C++**


