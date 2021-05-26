import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime
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
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    rows = db.execute("SELECT * FROM log WHERE person_id = :user_id", user_id = session["user_id"])
    return render_template("index.html", rows = rows, cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id = session["user_id"])[0]["cash"])



@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    else:
        if not (request.form.get("symbol") and request.form.get("shares")):
            return render_template("buy.html", message = "No enough data")
        if lookup(request.form.get("symbol")) == None:
            return render_template("buy.html", message = f"The quote ({request.form.get('symbol')}) does not exist")
        quote_price = lookup(request.form.get("symbol"))["price"]
        num = request.form.get("shares")
        # print(f"{type(quote_price)}, num is {type(num)}")
        total_price = quote_price * int(num)
        session["user_cash"] = db.execute("SELECT cash FROM users WHERE id = :id",id = session["user_id"])
        if session["user_cash"][0]["cash"] < total_price:
            return render_template("buy.html", message = f"you don't have enough stock for {total_price}$, your stock is only {session['user_cash'][0]['cash']}$")
        else:
            session["user_cash"][0]["cash"] = session["user_cash"][0]["cash"] - total_price
            db.execute("UPDATE users SET cash = :cash WHERE id = :id", cash = session["user_cash"][0]["cash"], id = session["user_id"])
            db.execute("INSERT INTO log (person_id, symbol, shares, trans, incname, incprice) VALUES (:person_id ,:symbol ,:shares ,:trans, :incname, :incprice)", person_id = session["user_id"], symbol = request.form.get("symbol"), shares = num, trans = datetime.now().strftime("%Y-%m-%d %H:%M:%S"), incname = lookup(request.form.get("symbol"))["name"], incprice = lookup(request.form.get("symbol"))["price"])
            return redirect("/")



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

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

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
    if request.method == "GET":
        return render_template("quote.html")
    else:
        quote_data = lookup(request.form.get("quote"))
        if quote_data == None:
            return render_template("quote.html", message = f"The quote ({request.form.get('quote')}) does not exist")
        return render_template("quote.html", message = f"{quote_data['name']}\'s share ({quote_data['symbol']}) costs {quote_data['price']}$")

    """Get stock quote."""
    return apology("TODO")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")
    else:
        if not request.form.get("username"):
            return apology("must provide username", 403)
        elif not request.form.get("password"):
            return apology("must provide password", 403)
        elif request.form.get("password") != request.form.get("passwordagain"):
            return render_template("register.html", message = "The passwords does not match!")
        db.execute("INSERT INTO users (username, hash) VALUES (:userreg, :hashreg)",userreg=request.form.get("username"), hashreg = generate_password_hash(request.form.get("password")))
    return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    rows = db.execute("SELECT symbol FROM log WHERE person_id = :user_id", user_id = session["user_id"])
    if request.method == "GET":
        return render_template("sell.html", rows = rows)
    # else:




def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
