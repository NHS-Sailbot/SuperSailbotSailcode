import os

stringToRemove = """template<typename _Rep, typename _Period>
      constexpr
      enable_if_t<numeric_limits<_Rep>::is_signed, duration<_Rep, _Period>>
      abs(duration<_Rep, _Period> __d)
      {
	if (__d >= __d.zero())
	  return __d;
	return -__d;
      }"""

file_path = os.path.join(os.path.expanduser("~"), ".platformio", "packages", "toolchain-gccarmnoneeabi", "arm-none-eabi", "include", "c++", "7.2.1", "chrono")

if not os.path.exists(file_path):
    print("File not found")
    exit()

with open(file_path, "r") as file:
    content = file.read()

content = content.replace(stringToRemove, "")

with open(file_path, "w") as file:
    file.write(content)