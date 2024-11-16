# Simple Ransomware Example 🚨

This repository provides a simple **educational example** of how ransomware functionality works. **It is strictly for educational purposes, research, and learning about cybersecurity.** 

## ⚠️ Disclaimer

This project is intended for **legal and ethical use only.**  
Using this code to harm, exploit, or disrupt others is **illegal** and punishable by law. By using or referencing this code, you agree to comply with all applicable laws and take full responsibility for your actions. The author assumes **no responsibility** for any misuse of this code.

---

## 📝 Overview

Ransomware is malicious software that encrypts or locks files and demands a ransom to restore access. This repository demonstrates a **non-encrypting** example of ransomware behavior by recursively "locking" files in a directory using a file rename operation (adding a `.locked` extension). 

### Key Features:
- Recursively processes all files in a directory and subdirectories.
- Adds a `.locked` extension to files to simulate "locking."
- Skips directories and special entries like `.` and `..`.

---

## 💻 Code Explanation

### Functions:
1. **`lock_file(const wchar_t* filename)`**  
   Attempts to rename a given file by appending the `.locked` extension. Reports errors if the file cannot be renamed.

2. **`lock_directory(const wchar_t* dir_name)`**  
   Recursively traverses a directory. Processes all files and subdirectories, calling `lock_file` for files and `lock_directory` for subdirectories.

3. **`main()`**  
   Prompts the user to input the directory to "lock" and calls `lock_directory` to process all files.

---

## 🛠️ How to Use

### Prerequisites:
- Windows OS (due to Windows API dependencies like `MoveFileW`).
- A C compiler (e.g., GCC with MinGW).

### Steps:
1. Clone this repository:
   ```bash
   git clone https://github.com/yourusername/simple-ransomware-example.git
   cd simple-ransomware-example
