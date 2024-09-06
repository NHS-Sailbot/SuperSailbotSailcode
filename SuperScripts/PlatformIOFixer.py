# Python sucks, BUT since it's a json file, and I want it to run everywhere, and I don't want a whole c# project, it's alright I guess, maybe

import json
import os

file_path = os.path.join(os.path.expanduser("~"), ".platformio", "platforms", "ststm32", "boards", "giga_r1_m7.json")

if not os.path.exists(file_path):
    print(f"File not found: {file_path}")
    input("Press Enter to exit...")
    exit(1)

with open(file_path, "r") as file: data = json.load(file)
data["build"]["hwids"] = [ ["0x2341", "0x0366"] ]
with open(file_path, "w") as file: json.dump(data, file, indent=4)

print("Modification completed successfully.")
input("Press Enter to exit...")
