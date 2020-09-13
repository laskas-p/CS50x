import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session, url_for
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
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

@app.route("/")
@login_required
def index():
    # select * from shares and cash from users
    myshares = db.execute("SELECT * FROM shares WHERE userid = :upid", upid = session['user_id'])
    mycash = db.execute("SELECT cash FROM users WHERE id = :upid", upid = session['user_id'])
    usercash=mycash[0]['cash']
    sumshares = 0
    # calculate the sum of totals from shares
    for i in myshares:
        sumshares = sumshares + i['total']

    # calculate the total for users' cash
    totalcash = sumshares + usercash
    # render index.html. note the import for usd function to be used as a function in the html file
    return render_template("index.html", usd=usd, myshares=myshares, usercash=usd(usercash), totalcash=usd(totalcash))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
     # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # retrieve the data of symbol field sent to lookup function
        qtb = lookup(request.form.get("symbol"))
        numb = request.form.get("shares")
        ucash = db.execute("SELECT cash FROM users WHERE id = :uid", uid = session["user_id"])
        # if symbol field was empty or not correct according to lookup
        if qtb == None:
            return apology("No share found for this symbol")
        else:
            # if the shares field is empty
            if numb == '':
                return apology("Please input a number of Shares")
            # else if the shares field is not a positive integer
            elif int(numb) % 1 != 0 or int(numb) < 1:
                return apology("Number of Shares need to be a Positive Integer")
            # else if the user don't have enough cash
            elif int(numb) * float(qtb["price"]) > float(ucash[0]['cash']):
                return apology("You don't have enough cash")
            else:
                prshare = db.execute("SELECT * FROM shares WHERE symbol = :prsymb AND userid = :upid", prsymb = qtb["symbol"], upid = session['user_id'])
                total = int(numb)*qtb["price"]

                # else if the user has the symbol already
                if len(prshare) == 1:
                    db.execute("UPDATE shares SET shares = shares + :bought, total = total + :uptotal WHERE userid = :upid AND symbol = :upsymbol", upid = session["user_id"],
                    bought = numb, upsymbol = qtb["symbol"], uptotal = total)
                    db.execute("UPDATE users SET cash = cash - :intotal WHERE id = :upid", upid = session["user_id"], intotal = total)

                    # insert transaction in history table
                    db.execute("INSERT INTO history (trans, symbol, shares, price, userid) VALUES (:htran, :hsym, :hsha, :hpri, :huid)", htran="Buy",
                    hsym = qtb["symbol"], hsha = int(numb), hpri = qtb["price"], huid = session["user_id"])

                    # flash message
                    flash("You successfully bought " + numb + " shares of " + qtb["symbol"] + ", "+ qtb["name"] + " at the price of " + usd(qtb["price"]))
                    return redirect("/")

                # insert in database if user don't have the symbol
                else:
                    db.execute("INSERT INTO shares (symbol, name, shares, price, userid, total) VALUES (:bsym, :bnam, :bsha, :bpri, :buid, :btot)", bsym = qtb["symbol"],
                    bnam = qtb["name"], bsha = int(numb), bpri = qtb["price"], buid = session["user_id"], btot = total)
                    db.execute("UPDATE users SET cash = cash - :intotal WHERE id = :upid", upid = session["user_id"], intotal = total)

                    # insert transaction in history table
                    db.execute("INSERT INTO history (trans, symbol, shares, price, userid) VALUES (:htran, :hsym, :hsha, :hpri, :huid)", htran="Buy",
                    hsym = qtb["symbol"], hsha = int(numb), hpri = qtb["price"], huid = session["user_id"])

                    # flash message
                    flash("You successfully bought " + numb + " shares of " + qtb["symbol"] + ", "+ qtb["name"] + " at the price of " + usd(qtb["price"]))
                    return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    # select * from shares and cash from users
    myshares = db.execute("SELECT * FROM history WHERE userid = :upid", upid = session['user_id'])

    # render index.html. note the import for usd function to be used as a function in the html file
    return render_template("history.html", usd=usd, myshares=myshares)


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

        # set session variable
        flash(request.form.get("username") + ", Welcome")

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
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        qt = lookup(request.form.get("symbol"))

        if qt == None:
            return apology("No share found for this symbol")
        else:
            return render_template("quoted.html", qtn = qt)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")



@app.route("/register", methods=["GET", "POST"])
def register():
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        reg_usn = request.form.get("username")
        reg_hash = generate_password_hash(request.form.get("password"))
         # Query database for username

        reg_rows = db.execute("SELECT * FROM users WHERE username = :usn", usn = reg_usn)

        # Check for existing username
        if len(reg_rows) == 1:
            return apology("Username exists already", 303)
        else:
            db.execute("INSERT INTO users (username, hash) VALUES (:usn, :hsh)", usn = reg_usn, hsh = reg_hash)
            # Redirect user to home page
            return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        sellnumb = request.form.get("shares")
        sellsymb = request.form.get("symbol")
        checksymb = db.execute("SELECT shares FROM shares WHERE userid = :slid and symbol = :slsymb", slid = session['user_id'], slsymb = sellsymb)
        if sellsymb == None or checksymb[0]['shares'] == 0:
            return apology("No shares are selected or you don't have shares to sell")
        elif int(sellnumb) % 1 != 0 or int(sellnumb) < 1:
                return apology("Number of Shares need to be a Positive Integer")
        elif checksymb[0]['shares'] < int(sellnumb):
                return apology("You don't have that much shares to sell")
        else:
            qt = lookup(request.form.get("symbol"))
            selltotal = int(sellnumb) * qt['price']

            # update tabe users for cash income
            db.execute("UPDATE users SET cash = cash + :sltotal WHERE id = :upid", upid = session["user_id"], sltotal = selltotal)

            # update table shares for shares and total change
            db.execute("UPDATE shares SET shares = shares - :slshares, total = total - price*:slshares WHERE userid = :upid AND symbol = :slsymbol ", upid = session["user_id"],
            slshares = int(sellnumb), slsymbol = sellsymb)

            # insert the transaction in history table
            db.execute("INSERT INTO history (trans, symbol, shares, price, userid) VALUES (:htran, :hsym, :hsha, :hpri, :huid)", htran="Sell",
            hsym = qt["symbol"], hsha = int(sellnumb), hpri = qt["price"], huid = session["user_id"])

            # check if there's no more shares left for the current symbol to delete the table row
            checkforzero= db.execute("SELECT shares FROM shares WHERE userid = :slid and symbol = :slsymb", slid = session['user_id'], slsymb = sellsymb)
            if checkforzero[0]['shares'] == 0:
                db.execute("DELETE FROM shares WHERE userid = :slid and symbol = :slsymb", slid = session['user_id'], slsymb = sellsymb)

            # flash message
            flash("You successfully sold " + sellnumb + " shares of " + sellsymb + ", " + qt['name'] + ", at the price of " + usd(qt['price']))
            return redirect("/")


    # User reached route via GET (as by clicking a link or via redirect)
    else:
        myshares = db.execute("SELECT symbol FROM shares WHERE userid = :upid", upid = session['user_id'])
        return render_template("sell.html", myshares=myshares)

@app.route("/pwdchange", methods=["GET", "POST"])
def pwdchange():
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # generate hash for the new password
        pwd_hash = generate_password_hash(request.form.get("password"))

        # Query database for user
        pwd_rows = db.execute("SELECT hash FROM users WHERE id = :usid", usid = session['user_id'])

        # Check if current password and the given one match
        if check_password_hash(pwd_rows[0]["hash"], request.form.get("cpassword")):
            # update users table with the new password
            db.execute("UPDATE users SET hash = :pwdhash WHERE id = :upid", pwdhash = pwd_hash, upid = session["user_id"])
            # flash message
            flash("Your password changed successfully")
            return redirect("/")
        else:
            # Redirect user to home page
            return apology("The password you entered doesn't match the one on our database")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("pwdchange.html")


@app.route("/addcash", methods=["GET", "POST"])
def addcash():
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # generate hash for the new password
        add_cash = request.form.get("cash")


        # update users table with the new password
        db.execute("UPDATE users SET cash = cash + :cash WHERE id = :upid", cash = add_cash, upid = session["user_id"])

        # flash message
        flash("Cash were added successfully")
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("addcash.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
