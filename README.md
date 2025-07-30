# Eid ul-Adha Qurbani & Charity Manager 🐄🐐🐪

A Windows-based C console application to manage Qurbani (animal sacrifice) data and distribute meat portions fairly during Eid ul-Adha.

## 📌 Features

- 🏠 Input Qurbani animal data per family (ox, goat, camel)
- 🍖 Calculate total meat and divide it into 3 parts (poor, own, relatives)
- 📦 Save/load family data to/from file
- 📊 Estimate how many poor families were helped
- 🔍 Search for a specific family's contribution
- 📈 Display meat contribution bar graph
- 🚫 Identify families who gave nothing
- 🥇 Sort families by total meat contribution

---

## ⚙️ Requirements

- Windows OS (uses `windows.h` for color and sound)
- GCC Compiler (e.g., Code::Blocks, MinGW, etc.)

---

## 🧪 How to Compile

```bash
gcc qurbani_manager.c -o qurbani.exe

