'''
Type Conversion or Casting Data Example
Author : Ariq Marwan Permana - 2024

'''

import os #importing os library for os.system function
from datetime import datetime # importing datetime to get the current year

os.system('cls' if os.name == 'nt' else 'clear')  # to clear the screen based on OS
x = input("Siapa nama lengkap anda? : ")
y = input("Berapakah tahun lahir anda? : ")
print(type(y)) #To show you every input function on default set yielded string data type
print(type(x)) #Even though you input int value, it's set to string output
y = int(y) #This function to convert the x variable data type to integer data type
sekarang = datetime.now()
tahun = sekarang.year
tahun = int(tahun)
tahun_lahir = tahun - y #To calculate user birth year
print(f"umur anda sekarang adalah : {tahun_lahir} ")
