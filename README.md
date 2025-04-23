# Browser Tabs Simulator

---

## 📌 Description

This project implements a **web browser simulator** that manages multiple tabs, navigation history, and essential browser operations.

The application reads commands from an input file (`tema1.in`) and writes the results to `tema1.out`.

---

## ✅ Features

- 🔄 **Browser initialization** with a default homepage (`https://acs.pub.ro/`)
- ➕ **Open new tabs** (`NEW_TAB`)
- ❌ **Close tabs** (`CLOSE`)
- 🔁 **Navigate between tabs** (`NEXT`, `PREV`)
- 🔍 **Select a tab by ID** (`OPEN id`)
- 🌐 **Open a new page in the current tab** (`PAGE id`)
- ↩️ **BACKWARD** – go back in history
- ↪️ **FORWARD** – go forward in history
- 📜 **PRINT_HISTORY id** – display the full history of a specific tab
- 🖨️ **PRINT** – print all tab IDs and the current page description

---

## 🧠 Data Structures Used

- **Doubly linked circular list with a sentinel node** for managing tabs
- **Stacks (LIFO)** for `BACKWARD` and `FORWARD` history navigation
- **Dynamic array of pages (`page[]`)** expanded as input is read

---

## 🗃️ Files

- `main.c` – main source file
- `tema1.in` – input with pages and commands
- `tema1.out` – output results
- `README.md` – this file

---

## 🧪 Sample Commands from `tema1.in`

```txt
3
1 https://google.com/
Google
2 https://github.com/
GitHub
3 https://stackoverflow.com/
Stack Overflow
15
NEW_TAB
PAGE 2
BACKWARD
FORWARD
PRINT
CLOSE
PRINT_HISTORY 0
```
---

## ⚠️ Notes
The project handles invalid operations by printing 403 Forbidden.

Proper memory management is implemented using free_all() to prevent memory leaks.

The code is clean, modular, and logically organized by feature.

## 🔚 Conclusion
This browser tabs simulator demonstrates effective use of doubly linked lists and stacks to manage tab navigation and history — similar to real-world browser behavior.
