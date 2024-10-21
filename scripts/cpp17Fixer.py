# If one of you python wizards can make this better, please do so! I could not get exit() to work without killing the build process.

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

Import("env")
file_path = os.path.join(env.PioPlatform().get_package_dir("toolchain-gccarmnoneeabi"), "arm-none-eabi", "include", "c++", "7.2.1", "chrono")
patchIndicator = file_path + ".patched"

if os.path.exists(patchIndicator):
    print("Chrono has already been fixed!")

if not os.path.exists(file_path):
    print("Chrono file not found! Is gcc-arm-none-eabi even installed?")

if os.path.exists(file_path) and not os.path.exists(patchIndicator):
    with open(file_path, "r") as file:
        content = file.read()

    content = content.replace(stringToRemove, "")

    with open(file_path, "w") as file:
        file.write(content)

    with open(patchIndicator, "w") as file:
        file.write("")

    print("Chrono has been fixed!")