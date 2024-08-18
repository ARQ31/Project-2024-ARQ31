'''
Author  : Ariq Marwan Permana
Topic   :"For" Examples - Python Programming Languages 2024

'''


import os

os.system("cls")
print("PERULANGAN TIPE 1 (For) ")
planets = ['Mercury', 'Venus', 'Earth', 'Mars', 'Jupiter', 'Saturn', 'Uranus', 'Neptune']
for planet in planets:
    print(planet, end=' ') # print all on same line

print("\n")
print("PERULANGAN TIPE 2 (For) ")
for planet in planets:
    print(planet)

print("\n")
print("PERULANGAN TIPE 3 (For) ")
for i in range(1,6):
    print(f"Aku cinta kamu {i}")

print("\n")
print("PERULANGAN TIPE 3 - 2 (For) ")
for i in range (1,6):
    print(f"I love you {i}, ", end = ' ')

print("\n")
print("PERULANGAN TIPE 4 (While) ")
i = 0
while i < 5:
    print("I'm still falling in love with you each day, darling. . . .")
    i += 1

print ("\n")
print ("LIST COMPREHENSIONS")
pangkat = [n**2 for n in range(10)]
print(pangkat)

print ("\n")
print ('Pangkat tanpa "LIST COMPREHENSIONS"')
pangkat = []
for n in range (10):
    pangkat.append(n**2)
print(pangkat)

print("\n")
print("Adding if condition to list comprehensions")
planet1 = [planet for planet in planets if len(planet) < 6]
print (planet1)

print("\n")
print("Adding if condition to list comprehensions (2)")
planet1 = [planet.upper() + '!!' for planet in planets if len(planet) < 6]
print (planet1)

print("\n")
planet2 = [x.upper() for x in planets]
print (planet2)

print("\n")
nums = [5, -1, -2, 0, 3, 7, 14]
#Type 1 list comprehensions to measuring total negatives number
print("Type 1 : " + str([num for num in nums if num < 0]))
#Type 2 list comprehensions to measuring total negatives number
print("Type 2 : " + str(sum([num < 0 for num in nums])))

# For with function type 1
'''Finding whether the given list is greater than the comp variable's'''
nums1 = [-1, 0, 5, 7, 14]
comp = 2
def lucky(nums, comp):
    print("\n")
    temp = []
    for num in nums:
        temp.append(num > comp)
    return print(temp)

lucky (nums1, comp)

# For with function type 2 
'''(Finding whether the given list of numbers is lucky,
A lucky list contains at least one number divisible by 7.'''

def lucky2(numb):
    print("\n")
    return any([num % 7 == 0 for num in numb])

print(lucky2(nums1))

# For with function type 3
'''Finding whether the given meals served twice in a row'''
meals = ["Mie Ayam", "Ayam Goreng", "Nasi Goreng", "Spaghetti", "Spaghetti", "Fettucini", "Nasi Lemak", "Nasi Lemak", "Nasi Lemak", "Nasi Lemak"]
def find_meals(n):
    print("\n")
    print("jumlah data pada list meals adalah : " + str(len(meals)))
    for x in range(len(n) + 1):
        if n[x] == n[x + 1]:
            return print("Makanan yang disajikan dua kali berturut - turut adalah : " + str(n[x]))

find_meals(meals)

def find_meals(n, consecutive_count):
    print("\n")
    temp = []
    for i in range(len(n) - consecutive_count + 1):
        is_consecutive = True
        for j in range(consecutive_count - 1):
            if n[i + j] != n[i + j + 1]:
                is_consecutive = False
                break
        if is_consecutive: #alternative (more verbose) : if is_consecutive == True:
            return print(f"Makanan yang disajikan {consecutive_count} kali berturut-turut adalah: {n[i]}")


find_meals(meals, 2)
find_meals(meals, 4)
