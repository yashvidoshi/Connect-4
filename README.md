# 🔴🟡 Connect 4 – Web Game using Flask + C++

A modern, fully working **Connect 4** game with:

- 🧠 Game logic written entirely in **C++**
- 🌐 Frontend built using **HTML & CSS**
- ⚙️ Flask (Python) connects frontend ↔ backend
- ✅ No JavaScript required!

Players take turns dropping colored discs into a 7-column, 6-row board. The first to form a horizontal, vertical, or diagonal line of **four** of their discs wins!

---

## 🎮 Features

- 👥 **2 Player Mode** (Player X vs Player O)
- 🔄 Alternating turns with live board updates
- 🧠 **C++-based backend logic** checks for win after every move
- ✅ Winner is detected and displayed
- 🧼 Play Again button to reset the board
- 📦 Minimal & organized project layout
- 🎨 Fully styled UI (clean, modern, and visually balanced)

---

---

## 🚀 How to Run Locally

1. Clone the repo

```bash
    git clone https://github.com/yashvidoshi/Connect-4.git
    cd Connect-4
```
2. Install Flask. Make sure you have Python 3 installed, then:
   ```
   pip install flask
    ```
3. Run the game
    ```
    python3 app.py
    ```
4. The game will run on this link in your browser:
   ```
   http://localhost:5000
   ```
   


## 🧠 How It Works

- 🗂️ **Board state** is stored in `backend/game_state.txt`
- 🌐 **Flask** handles routing and receives column input from the user
- ✏️ Player move is **written** to the backend file (`game_state.txt`)
- ⚙️ `connect4.cpp` is **compiled and executed** to:
  - 🔽 Drop the disc
  - 🧱 Update the board
  - 🏆 Check if someone won
- 📖 Flask **reads** the updated files and dynamically updates the frontend

## Built by Yashvi Doshi

