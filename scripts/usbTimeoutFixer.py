import os
home_dir = os.path.expanduser("~")
platformio_dir = os.path.join(home_dir, ".platformio")
tools_dir = os.path.join(platformio_dir, "penv", "Lib", "site-packages", "platformio", "builder", "tools")
pioupload = os.path.join(tools_dir, "pioupload.py")

# replace " 5 " with " 25 "

with open(pioupload, "r") as file:
    content = file.read()
    content = content.replace(" 5 ", " 25 ")
with open(pioupload, "w") as file:
    file.write(content)