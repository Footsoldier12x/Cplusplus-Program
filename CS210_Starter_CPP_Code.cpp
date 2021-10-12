/*
	Name: Juan Pablo Izquierdo

	Date: 11 October 2021

	Description:
	Corner Grocer App

	Performs 4 tasks depending on user input

	1- Produce a list of all items purchased in a given day along with the number of times each item was purchased.
	2- Produce a number representing how many times a specific item was purchased in a given day.
	3- Produce a text-based histogram listing all items purchased in a given day, along with a representation of the number of times each item was purchased.
	4- Exit program

*/

#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("CS210_Starter_PY_Code");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"CS210_Starter_PY_Code");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"CS210_Starter_PY_Code");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

// Print input menu prompting user for input
string MainMenuPrompt() {
	string userInputString;		//Stores user input selection

	try {
		// Prints prompt for user input
		cout << setfill('=') << setw(100) << "" << endl;
		cout << "What would you like to do?" << endl;

		cout << setfill('-') << setw(100) << "" << endl;
		cout << "1: Produce a list of all items purchased in a given day along with the number of times each item was purchased." << endl <<endl;
		cout << "2: Produce a number representing how many times a specific item was purchased in a given day." << endl << endl;
		cout << "3: Produce a text-based histogram listing all items purchased in a given day, ";
		cout << "along with a representation of the number of times each item was purchased." << endl << endl;
		cout << "4: Exit program" << endl;
		cout << setfill('=') << setw(100) << "" << endl << endl;

		cout << "Enter your selection as a number 1, 2, 3, or 4:" << endl;

		cin >> userInputString;				// Stores user input selection
		cout << endl;

		// Checks if input is valid
		if ((userInputString.size() > 1) || (userInputString < "1" || userInputString > "4")) {
			throw runtime_error("Invalid entry.");
		}
	}
	catch (runtime_error& excpt) {			// Prompts user for input again if input is invalid
		cout << excpt.what() << endl;
		cout << "Please try again." << endl << endl;
	}
	return userInputString;
}

// Prompt user input to print an individual item and the quantity sold
void PrintItemNameQuantity() {
	string userInputItem = " ";		// Stores the value of the specific item to be checked
	int itemQuantity = 0;			// Stores the quantity of the specific item to be checked

	cout << "Enter the name of a specific item you want to check:" << endl;

	cin >> userInputItem;
	itemQuantity = callIntFunc("ItemDailySales", userInputItem);					// Calls Python function and sends item name to be checked
	cout << endl;

	if (itemQuantity > 1) {
		cout << setfill('*') << setw(20) << "" << endl;								// Top of banner
		cout << "Item sales today:" << endl;	

		cout << userInputItem << " " << itemQuantity << endl;						// Prints specific item and quantity

		cout << setfill('*') << setw(20) << "" << endl << endl << endl;				// Bottom of banner
	}
	else {
		cout << "Invalid item entry." << endl << endl;								// Error message if invalid item is entered
	}
}

// Print a thank you message when exiting program
void ExitProgramMessage() {
	cout << setfill('*') << setw(45) << "" << endl;							// Top of banner
	cout << "Exiting program." << endl;
	cout << "Thank you for testing the Corner Grocer App!" << endl;
	cout << setfill('*') << setw(45) << "" << endl << endl;					// Bottom of banner
}

// Prints welcome message
void WelcomeMessage() {
	cout << setfill('*') << setw(34) << "" << endl;							// Top of banner
	cout << "Welcome to the Corner Grocer App!" << endl;
	cout << setfill('*') << setw(34) << "" << endl << endl << endl;			// Bottom of banner
}

// Reads file and displays a histogram with its data
void PrintHistogram() {
	ifstream inputFile;			// Input file reference
	string inputItemName;		// Stores item name string coming from the input file reference
	int inputItemQuantity;		// Stores item quantity int coming from the input file reference 

	inputFile.open("frequency.dat");										// Opens file for reading and creates reference object
	
	if (!inputFile.is_open()) {												// If file does not open, exit function with an error
		cout << "Could not open file frequency.dat" << endl;
		return;
	}
	else {																	// Else, read file and store its contents
		cout << setfill('*') << setw(30) << "" << endl;						// Top of banner
		cout << " Histogram of all Items sold" << endl << endl;
		
		inputFile >> inputItemName;											// Read item name
		inputFile >> inputItemQuantity;										// Read item quantity

		while (!inputFile.fail()) {											// If it is not the end of the file, read the file

			cout << setfill(' ') << setw(12) << inputItemName << " ";

			for (int i = 0; i < inputItemQuantity; ++i) {					// Loop prints histogram symbols
				cout << "$";
			}
			cout << endl;

			inputFile >> inputItemName;										// Read item name for next loop
			inputFile >> inputItemQuantity;									// Read item quantity for next loop
		}
	}
	inputFile.close();

	cout << setfill('*') << setw(30) << "" << endl << endl << endl;			// Bottom of banner
}


int main() {
	string menuSelection = " ";				// Stores selection made by user

	WelcomeMessage();						// Prints welcome message

	menuSelection = MainMenuPrompt();

	// Call the correct function according to user input
	while (menuSelection != "4") {								// Exit program if user input is 4

		if (menuSelection == "1") {								// Print list of all items sold if user input is 1
			CallProcedure("PrintListAllItemsSold");
		}
		else if (menuSelection == "2") {						// Print specific item is user input is 2
			PrintItemNameQuantity();
		}
		else if (menuSelection == "3") {						// Print histogram if user input is 3
			CallProcedure("WriteQuantityItemsSoldFile");
			PrintHistogram();
		}
		menuSelection = MainMenuPrompt();						// Update user input for next loop
	}
	ExitProgramMessage();										// Print exit program message

	return 0;

}