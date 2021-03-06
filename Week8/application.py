import os

# from cs50 import SQL
import sqlite3
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
# Session(app)
app.secret_key = 'the random string'


# Configure CS50 Library to use SQLite database
# db = SQL("sqlite:///finance.db")
conn = sqlite3.connect('finance.db', check_same_thread=False)
cur = conn.cursor()

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

# Routes:
@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    return apology("TODO")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == 'POST':
        # Check if the number of shares is valid
        try:
            numberOfShares = int(request.form.get("shares"))
            if numberOfShares < 0:
                raise ValueError
        except ValueError:
            return apology("Thats not a valid number of shares.")

        # Check if the symbol is valid
        symbol = request.form.get("symbol").strip()
        quote = lookup(symbol)
        if symbol == "" or quote == None:
            return apology("Enter a valid stock symbol.")

        # Calculate total price
        totalPrice = quote.get('price') * numberOfShares

        # Check for sufficient funds
        userId = session["user_id"]
        row = cur.execute("SELECT cash FROM users WHERE users.id =?", (userId,)).fetchone()
        cash = row[0]
        cashLeft = cash - totalPrice
        if cashLeft < 0:
            return apology("Insufficient funds.")

        # Insert purchase into database
        cur.execute("INSERT INTO purchases (name, price, amount, user_id, symbol) values(?, ?, ?, ?, ?)",
            (quote['name'], quote['price'], numberOfShares, userId, quote['symbol']))
        cur.execute("UPDATE users SET cash =? WHERE users.id =?", (cashLeft, userId,))
        conn.commit()
        return render_template('quote.html')
    else:
        return render_template('buy.html')


@app.route("/check", methods=["GET"])
def check():
    """Return true if username available, else false, in JSON format"""
    return jsonify("TODO")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        # Ensure username was submitted
        if not username:
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not password:
            return apology("must provide password", 403)

        # Query database for username
        rows = cur.execute("SELECT * FROM users WHERE username =?", (username,)).fetchall()
        print(rows)
        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0][2], password):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0][0]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    else:
        symbol = request.form['symbol']
        quote = lookup(symbol)
        print(quote)
        print(type(quote))
        return render_template("quoted.html", quote=quote)

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form['username']
        password = request.form['password']
        confirmation = request.form['confirmation']

        # Get username from database
        rows = cur.execute(f"select * from users where users.username =?", (username,))
        # Check if username doesnt exist yet and password input is correct
        if rows.fetchone() == None and password == confirmation:
            hashedPassword = generate_password_hash(password, method='pbkdf2:sha256', salt_length=8)
            # Create new user in the database
            cur.execute("INSERT INTO users (username, hash) VALUES (?, ?)", (username, hashedPassword))
            conn.commit()

        return redirect("/login")
    else:
        return render_template("signup.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
