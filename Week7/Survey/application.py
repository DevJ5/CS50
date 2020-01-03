import cs50
import csv

from flask import Flask, jsonify, redirect, render_template, request

# Configure application
app = Flask(__name__)

# Reload templates when they are changed
app.config["TEMPLATES_AUTO_RELOAD"] = True


@app.after_request
def after_request(response):
    """Disable caching"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET"])
def get_index():
    return redirect("/form")


@app.route("/form", methods=["GET"])
def get_form():
    return render_template("form.html")


@app.route("/form", methods=["POST"])
def post_form():
    name = request.form.get("name")
    department = request.form.get("department")
    gender = request.form.get("gender")

    with open("survey.csv", "a", newline="") as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow([name, department, gender])

    return redirect("sheet")


@app.route("/sheet", methods=["GET"])
def get_sheet():
    with open("survey.csv", newline="") as csvfile:
        reader = csv.DictReader(csvfile, ["name", "department", "gender"])
        data = []
        for row in reader:
            print(f"Row: === {row}")
            data.append(row)

    return render_template("sheet.html", len=len(data), data=data)


@app.route("/employees", methods=["GET"])
def get_data():
    with open("survey.csv", newline="") as csvfile:
        reader = csv.DictReader(csvfile, ["name", "department", "gender"])
        data = []
        for row in reader:
            print(f"Row: === {row}")
            data.append(row)

    return jsonify(data)
