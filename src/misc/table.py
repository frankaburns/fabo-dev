import sys

# other imports...
import string
import pandas as pd

def parseDoc(doc_url):
    try:
        # Attempt to read HTML tables from the published URL
        tables = pd.read_html(doc_url)

        # Assuming the table you want is the first one found
        df = pd.DataFrame(tables[0])
        num_rows = len(df)

        # find the matrix bounds
        num_x = 0
        num_y = 0
        for row in range(num_rows):
            if row > 0:
                r = df.iloc[row]
                if int(r[0]) > num_x:
                    num_x = int(r[0])
                if int(r[2]) > num_y:
                    num_y = int(r[2])
        num_x += 1
        num_y += 1

        # build the matrix
        code = [[" " for _ in range(num_x)] for _ in range(num_y)]
        for row in range(num_rows):
            if row > 0:
                r = df.iloc[row]
                code[int(r[2])][int(r[0])] = r[1]

        # form and print the image
        for line in range(num_y-1, -1, -1):
            line_string = ""
            for row in range(num_x):
                line_string += code[line][row]
            print(line_string.upper())
    except Exception as e:
        print(f"Could not read table directly from URL: {e}")
        print("Consider using the Google Docs API for more robust table extraction.")
    return

if __name__ == "__main__":
    if len(sys.argv) > 1:
        doc = sys.argv[1]
    else:
        doc = "https://docs.google.com/document/d/e/2PACX-1vQGUck9HIFCyezsrBSnmENk5ieJuYwpt7YHYEzeNJkIb9OSDdx-ov2nRNReKQyey-cwJOoEKUhLmN9z/pub"

    parseDoc(doc)
