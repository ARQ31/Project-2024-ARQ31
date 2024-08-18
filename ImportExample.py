'''
Author  : Ariq Marwan Permana
Topic   : "Importing Library" in Python Programming Language 2024

'''

# Working with external libraries
import math
print("Math libraries has {} type".format(type(math)))
print("Pi number is : {:.3}".format(math.pi))
print("Logarithm with basis 2 from 32 is : {}".format(math.log(32, 2)))
# alternative use of import libraries : "import math as mt"
# Example : 
import math as mt 
print("\n")
print("Example libraries import usage of math as mt : {:.3}".format(mt.pi)) # More concise usage of importing libraries

# Example 2 :
print("\n")
from math import *  # Refer to all variables in math module
print("Pi number : {:.3} and Log 32 with basis 2 is : {}".format(pi, log(32,2))) # We don't need math.pi again instead just use pi, log, etc)
# Be careful sometimes two or more modules has 2 same functions so this methods is not recommended

# Example 3 :
print("\n")
import numpy
print("numpy libraries has {} type".format(type(numpy)))
print("It contains such as : ", dir(numpy.random)[:-15])

# Roll 10 dices :
print("\n")
rolls = numpy.random.randint(low = 1, high = 6, size = 10)
print(rolls)
print("is the data inside rolls variable greater than 3 : {}".format(rolls <= 3))
print("Average data from 10 rolls : {}".format(rolls.mean()))
print("Turn the array to a list : {}".format(rolls.tolist()))
print("What is this thing? : ")
print(type(rolls))
print("\n")
print("What can it do with it? : ")
print(dir(rolls))
print("\n")

# Three important tools for understanding strange objects
# type() What is this thing?
# dir() -  What can it do with it?
# help() -  tell me more

# Operator Overloading
x = rolls + 10
print("Plus each data in rolls variable with \"10\" value : {}".format(x))

# Create a 2-dimensional array
print("\n")
xlist = [[1,2,3],[2,4,6]]
x = numpy.asarray(xlist)
print("xlist = {}\nx =\n{}".format(xlist, x))
print("\n")
a = int(input("Column? : "))
b = int(input("Row?    : "))
print("Data in Colomn {} and Row {} : {}".format(a, b, x[a-1][b-1]))

