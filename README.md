# 💰 Transaction Processor in C++

This project demonstrates a robust **command-processing system** in C++ that reads transaction instructions from a file, validates them, and updates a virtual balance accordingly. It also showcases **custom exception handling** for invalid commands and insufficient funds.

---

## 📁 Files

- `main.cpp` – Entry point of the program.
- `implementation.cpp` – Contains the implementation of all class methods.
- `header.hpp` – Header file with class declarations.
- `file.txt` – Sample input file containing commands like `DEPOSIT` and `WITHDRAW`.

---

## 📌 Command Format

Each line in `file.txt` should be formatted as:

Where:
- `COMMAND` can be `DEPOSIT` or `WITHDRAW`.
- `AMOUNT` is a positive integer (e.g., `100`, `200`).

---

## ⚠️ Exception Handling

Two types of custom exceptions are used:

- **InvalidCommandException** – Thrown for unknown or malformed commands.
- **InsufficientFundsException** – Thrown when attempting to withdraw more than the current balance.

---

💡 Features
	•	Uses std::ifstream with exception flags.
	•	Parses input line-by-line using std::stringstream.
	•	Supports nested exception throwing with std::throw_with_nested.
	•	Handles both syntax and semantic errors cleanly.

⸻

📌 Notes
	•	The file is automatically closed using RAII (TransactionFileHandler destructor).
	•	Errors are printed with the line number for easy debugging.


## 🔧 Compilation

Compile using:

```bash
g++ -std=c++17 main.cpp implementation.cpp -o processor

./processor
