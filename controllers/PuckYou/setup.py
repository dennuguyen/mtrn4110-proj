'''
It is up to the user to ensure cython and any required packages are installed.
'''

from Cython.Build import cythonize
import os

# Generate .h and .cpp files from all .pyx files in scripts folder.
cythonize("scripts/*.pyx")

# Move the generated files into their respective folders.
files = os.listdir("scripts/")
for f in files:
    if ".cpp" in f:
        os.replace("scripts/" + f, "src/" + f)
    elif ".h" in f:
        os.replace("scripts/" + f, "include/" + f)