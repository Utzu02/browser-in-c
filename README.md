# Browser Tabs Simulator

---

## 📌 Descriere

Acest proiect implementează un **simulator de browser web** care gestionează tab-uri, istoric de navigare și funcționalități de bază asociate acestora.

Aplicația funcționează pe bază de comenzi citite dintr-un fișier (`tema1.in`) și scrie rezultatele în `tema1.out`.

---

## ✅ Funcționalități implementate

- 🔄 **Inițializare browser** cu o pagină implicită (`https://acs.pub.ro/`)
- ➕ **Adăugare tab-uri noi** (`NEW_TAB`)
- ❌ **Închidere tab** (`CLOSE`)
- 🔁 **Navigare între tab-uri** (`NEXT`, `PREV`)
- 🔍 **Selectare tab după ID** (`OPEN id`)
- 🌐 **Navigare către pagini noi** (`PAGE id`)
- ↩️ **BACKWARD** – istoric înapoi
- ↪️ **FORWARD** – istoric înainte
- 📜 **PRINT_HISTORY id** – afișează istoricul tabului specificat
- 🖨️ **PRINT** – afișează toate ID-urile tab-urilor și descrierea paginii curente

---

## 🧠 Structuri de date utilizate

- **Listă dublu înlănțuită circulară cu santinelă** pentru tab-uri
- **Stive (LIFO)** pentru navigarea `BACKWARD` și `FORWARD`
- **Vector dinamic de pagini (`page[]`)** care se extinde pe măsură ce se citesc din fișier

---

## 🗃️ Fișiere

- `tema1.c` – sursa principală
- `tema1.in` – input-ul de comenzi și pagini
- `tema1.out` – output-ul rezultat
- `README.md` – acest fișier

---

## 🧪 Exemple de comenzi în `tema1.in`

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
