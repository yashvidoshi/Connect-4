import os
from flask import Flask, render_template, request
import subprocess

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def index():
    # Load current player from file or set to X
    if not os.path.exists("backend/turn.txt"):
        with open("backend/turn.txt", "w") as f:
            f.write("X")
    with open("backend/turn.txt", "r") as f:
        player = f.read().strip()

    if request.method == 'POST':
        col = int(request.form['column'])

        # Write move to game_state.txt
        with open("backend/game_state.txt", "r") as f:
            lines = f.readlines()

        with open("backend/game_state.txt", "w") as f:
            for line in lines[:6]:
                f.write(line)
            f.write(f"{col} {player}\n")

        # Run game logic
        subprocess.run(["g++", "backend/connect4.cpp", "-o", "backend/game"])
        subprocess.run(["./backend/game"])

        # Flip turn if no winner
        if not os.path.exists("backend/winner.txt"):
            next_player = "O" if player == "X" else "X"
            with open("backend/turn.txt", "w") as f:
                f.write(next_player)

    # Read updated board
    with open("backend/game_state.txt", "r") as f:
        board = [list(line.strip()) for line in f.readlines()[:6]]

    # Check for winner
    winner = None
    if os.path.exists("backend/winner.txt"):
        with open("backend/winner.txt", "r") as f:
            winner = f.read().strip()

    return render_template("index.html", board=board, current_player=player, winner=winner)

@app.route('/reset')
def reset():
    # Clear board
    with open("backend/game_state.txt", "w") as f:
        for _ in range(6):
            f.write(".......\n")

    # Reset turn
    with open("backend/turn.txt", "w") as f:
        f.write("X")

    # Remove winner
    if os.path.exists("backend/winner.txt"):
        os.remove("backend/winner.txt")

    # Return to fresh board
    board = [['.'] * 7 for _ in range(6)]
    return render_template("index.html", board=board, current_player='X', winner=None)

if __name__ == "__main__":
    # Init board and turn if not present
    if not os.path.exists("backend/game_state.txt"):
        with open("backend/game_state.txt", "w") as f:
            for _ in range(6):
                f.write(".......\n")

    if not os.path.exists("backend/turn.txt"):
        with open("backend/turn.txt", "w") as f:
            f.write("X")

    # Clear previous winner
    if os.path.exists("backend/winner.txt"):
        os.remove("backend/winner.txt")

    app.run(debug=True)
