from cs50 import SQL
db = SQL("sqlite:///finance.db")

rows = db.execute("SELECT * FROM log")
print(rows)               

new_rows = []
for i in range(len(rows)):
    if rows[i]["symbol"] not in [item["symbol"] for item in new_rows]:
        new_rows.append(rows[i])
        print("NO DUBLICATE")
    else:
        for row in new_rows:
            if row["symbol"] == rows[i]["symbol"]:
                row["shares"] += rows[i]["shares"]
        
print(new_rows)
