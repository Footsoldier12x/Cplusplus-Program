""" 
	Name: Juan Pablo Izquierdo

	Date: 11 October 2021

	Description:
	Corner Grocer App

	Supports the main C++ program to perform 4 tasks depending on user input

	1- Produce a list of all items purchased in a given day along with the number of times each item was purchased.
	2- Produce a number representing how many times a specific item was purchased in a given day.
	3- Produce a text-based histogram listing all items purchased in a given day, along with a representation of the number of times each item was purchased.
	4- Exit program

"""


import re
import string

quantityItemsSold = {}  # Stores a dictionary of the items sold

# Read and stores the total list of items sold in a dictionary
fileReader = open("CS210_Project_Three_Input_File.txt")
listAllItems = fileReader.read().splitlines()

# Adds new items to dictionary and increases quantity by 1 if item is already in the dictionary
for item in listAllItems:
    if item not in quantityItemsSold.keys():
        quantityItemsSold[item] = 1
    else:
        quantityItemsSold[item] = quantityItemsSold[item] + 1
        
fileReader.close()              # Closes file

# Prints a list of all items sold and their quantities. 
def PrintListAllItemsSold():
    print("***************************************")
    print("List of total items sold\n")

    # Prints "Item quantity" for every key:value in dictionary
    for item, quantity in quantityItemsSold.items(): 
        print("{} {}".format(item, quantity))

    print("***************************************\n")

# Prints an item and the times it was sold
def ItemDailySales(itemName):
    itemName = itemName.capitalize()                          # Capitalize item name
    if itemName in quantityItemsSold.keys():                  # if item name in sold items list, return its quantity
        return quantityItemsSold[itemName]
    else:
        return 0;                                             # return 0 if item is not found

# Creates a new file with total items sold
def WriteQuantityItemsSoldFile():
    fileWriter = open('frequency.dat', 'w')                   # Opening new file

    for item, quantity in quantityItemsSold.items():
        fileWriter.write("{} {}\n".format(item, quantity))    # Write string

    fileWriter.close()                                        # Closes file

    print("New frequency.dat file created.")
    print()