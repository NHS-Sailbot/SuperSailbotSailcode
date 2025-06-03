import sys
import os

for path in sys.path:
    if path.endswith("builder"):
        builder_path = path
        break

if not builder_path:
    print("Could not find builder path in sys.path, waiting for PlatformIO to fix this...")
else:
    pio_path = os.path.join(builder_path, "tools", "pioupload.py")
    
if not os.path.exists(pio_path):
    print("pioupload.py not found! Is PlatformIO installed? Path checked:", pio_path)
    exit(-1)
else:
    with open(pio_path, "r") as file:
        content = file.read()
    content = content.replace(" 5 ", " 25 ")
    with open(pio_path, "w") as file:
        file.write(content)
    print("pioupload.py has been fixed!")