//Ariba Ahmed : 20934753

#include <iostream>
#include <string>
#include <fstream> // files library
#include <iomanip> // manipulator for fixed point numbers
using namespace std;

//declare constant variables
const int lineWidth = 20;
const int optionZero = 0;
const int optionOne = 1;
const int optionTwo = 2;
const int optionThree = 3;
const int optionMin = 0;
const int menuOptionMax = 4;
const int toppingsOptionMax = 6;
const int burgerOptionMax = 3;
const int initialPrice = 0;
const double smallBurgerPrice = 3.00;
const double mediumBurgerPrice = 5.50;
const double largeBurgerPrice = 7.25;
const int burgerArrayLen = 4;
const int toppingsArrayLen = 7;
const string burgerSizeArray[burgerArrayLen] = { " ", "Small", "Medium", "Large" };
const string toppingsArray[toppingsArrayLen] = { " ", "Cheese", "Salad", "Bacon", "Ketchup", "Mayo", "Extra burger" };
const double burgerSizePrice[burgerArrayLen] = { 0, 3.00, 5.50, 7.25 };
const double toppingsPrice[toppingsArrayLen] = { 0, 0.80, 0.50, 1.00, 0.30, 0.30, 1.50 };
const int decimalFilling = 2;


void DrawLine() // function to draw lines for menu and title
{
	for (int i = 0; i < lineWidth; i++)
	{
		cout << "--";
	}
}

void ToppingsMenu() // function for toppings menu and prices
{
	DrawLine(); // use draw-line function within this function for efficiency
	cout << endl << "1. Cheese [0.80 credits]" << endl <<
		"2. Salad [0.50 credits]" << endl <<
		"3. Bacon [1.00 credits]" << endl <<
		"4. Ketchup [0.30 credits]" << endl <<
		"5. Mayo [0.30 credits]" << endl <<
		"6. Extra burger [1.50 credits]" << endl <<
		"0. Return to Main Menu" << endl;
	DrawLine();
}

double CalculatePrice(double initialMoney, double price) // used to increment price
{
	double currentBalance = initialMoney + price; // total price is now the previous price plus additional toppings/burger size
	return currentBalance;
}

double NumInputValidation() // input validation for numbers
{
	double inputValue;

	cout << "Input is invalid. Please try again." << endl; // displays error message to user
	cin.clear(); // clears the cin
	cin.ignore(80, '\n');
	cin >> inputValue; // allows user input again

	return inputValue;
}

string StringInputValidation() // input validation for strings
{
	string yesNo;

	cout << "Input is invalid. Please try again." << endl;
	cin.clear();
	cin.ignore(80, '\n');
	cin >> yesNo;

	return yesNo;
}

double AddCredits(double credits) // add credits at the start
{
	double addCredits;
	cout << "Please enter the amount you want to add" << endl;
	cin >> addCredits; // allows user to input credits

	// check if input is a negative number or the wrong data type is used
	while (cin.fail() || addCredits < 0)
	{
		addCredits = NumInputValidation();
	}
	return credits += addCredits; // return credits (0) plus the added credits

}


double AvailableBalance(double burgerPrice, double credits) // displays burger price and current balance
{
	DrawLine();
	cout << endl << "Available balance: " << fixed << setprecision(decimalFilling) << credits << " credits" << endl << // credits are passed through to store its value
		"Burger Price: " << burgerPrice << " credits" << endl; // burger price is passed through to store its value
	DrawLine();

	return credits; // credits are returned to get output
}

double AddBurgerSize(double credits) // choose burger size and then add it to the total cost
{
	int chooseBurgerSize;
	cin >> chooseBurgerSize; // user can choose burger size
	double burgerPrice;
	string burgerSize;
	string name;

	cout << "Please enter your name: " << endl;
	cin >> name;

	// input validation to check if data type is incorrect or if the input is less than 0 or more than 3
	while (cin.fail() || chooseBurgerSize < optionMin || chooseBurgerSize > burgerOptionMax)
	{
		chooseBurgerSize = NumInputValidation(); // calling input validation function
	}

	for (int i = 1; i < burgerArrayLen; i++) // loops through the different burger sizes using an array
	{
		if (chooseBurgerSize == i) // if burger size = 1,2 or 3...
		{

			burgerSize = burgerSizeArray[i];
			burgerPrice = CalculatePrice(initialPrice, burgerSizePrice[i]); // increment price based on each burger size
			// display message to show what burger is selected and the price of it 
			cout << "Thank you " << name << ", you have selected a " << burgerSize << " burger. Your current price is : " << fixed << setprecision(decimalFilling) << burgerPrice << " credits" << endl;

			// video used: https://www.youtube.com/watch?v=EaHFhms_Shw
			fstream ordersFile; // use fstream variable to create variable
			ordersFile.open("recentOrders.txt", ios::app); // open file, pass text file and append mode through parameters to write into file
			if (ordersFile.is_open()) // check if file is open using 
			{
				{
					ordersFile << endl << name << "'s order: " << endl << endl << "Burger size: " << burgerSize << endl;
				}

				ordersFile.close(); // close file
			}

			return burgerPrice;

		}
	}


	return chooseBurgerSize;
}

double ExtraBurger(double credits) // order extra burger 
{
	string yesNo;
	cout << endl << "Would you like to order another burger? Please input 'Y' for yes and 'N' for no" << endl;
	cin >> yesNo; // allow user to add another burger or end the transaction

	// input validation to check if data type is wrong or if the input is not Y or N
	while (cin.fail() || yesNo != "Y" && yesNo != "N" && yesNo != "y" && yesNo != "n")
	{
		yesNo = StringInputValidation();
	}

	system("cls");

	if (yesNo == "Y") // if yes then return to menu
	{
		return credits;
	}

	else if (yesNo == "N") // if no then end the transaction and display goodbye message
	{
		cout << endl << "Thank you, goodbye!" << endl;
		system("pause");
		return credits; // return to menu
	}

}


double Checkout(double burgerPrice, double credits) // end order and check credits
{
	string yesNo;
	double extraCredits; // extra credits that user will add
	double requiredCredits; // required credits needed to complete transaction

	while (credits >= burgerPrice) // check if there are enough credits 
	{
		credits = AvailableBalance(burgerPrice, credits);
		credits -= burgerPrice; // deduct the burger price from the total credits to make the user pay
		cout << endl << "Your transaction was successful :)" // displayy success message
			<< endl << "Your new balance = " << fixed << setprecision(decimalFilling) << credits << " credits" << endl; // display new balance
		DrawLine();
		yesNo = ExtraBurger(credits); // call the extra burger function
		return credits;
	}

	while (credits < burgerPrice) //use this while loop if there are insufficient credits and don't break until there's enough credits
	{
		requiredCredits = burgerPrice - credits; // calculate required credits by deductingn current credits from burger price
		credits = AvailableBalance(burgerPrice, credits);

		// display insufficient funds message and allow user to add more
		cout << endl << "You have insufficient credits available.You require " << fixed << setprecision(decimalFilling) << requiredCredits << " more credits" << endl <<
			"Would you like to add more credits? Please input 'Y' for yes and 'N' for no" << endl;
		cin >> yesNo;

		while (cin.fail() || yesNo != "Y" && yesNo != "N" && yesNo != "y" && yesNo != "n")
		{
			yesNo = StringInputValidation();
		}

		if (yesNo == "Y" || yesNo == "y")
		{
			cout << "Please enter how many credits you would like to add to your balance" << endl;
			cin >> extraCredits; // allow user to add credits

			while (cin.fail() || extraCredits < initialPrice)
			{
				extraCredits = NumInputValidation();
			}

			credits += extraCredits; // credits are incremented by user input
			cout << "Your new balance = " << credits << " credits" << endl; // display new balance

			if (extraCredits >= requiredCredits) // check if credits are still enough after adding more
			{
				cout << "Would you like to continue processing your order?" << endl; // continue transaction
				cin >> yesNo;

				while (cin.fail() || yesNo != "Y" && yesNo != "N" && yesNo != "y" && yesNo != "n")
				{
					yesNo = StringInputValidation();
				}

				system("cls");

				if (yesNo == "Y" || yesNo == "y")
				{
					credits = AvailableBalance(burgerPrice, credits);
					credits -= burgerPrice; // deduct burger price from total credits
					DrawLine();
					cout << endl << "Your transaction was successful :)"
						<< endl << "Your new balance = " << fixed << setprecision(decimalFilling) << credits << " credits" << endl; // display new balance
					DrawLine();
					yesNo = ExtraBurger(credits); // call extra burger function
					return credits;
				}

				else if (yesNo == "N" || yesNo == "n") // otherwise clear terminal and return to menu
				{
					system("cls");
					return credits;
				}
			}
		}

		else if (yesNo == "N" || yesNo == "n")
		{
			system("cls");
			return credits;
		}
	}

}

double AddToppings(double burgerPrice, double credits) // add toppings and incrememnt price for each one
{
	cout << endl << "ORDER BURGER - Select Toppings" << endl << "Please choose from the following toppings:" << endl;
	ToppingsMenu(); // call toppings menu function to display toppings and prices
	cout << endl << "Please enter a number" << endl;

	int toppingsOption;
	cin >> toppingsOption; // allow user to choose a topping
	double priceTotal;
	string yesNo;
	fstream ordersFile;

	// input validation to check if data type is incorrect or if the input is less than 0 or more than 6
	while (cin.fail() || toppingsOption < optionMin || toppingsOption > toppingsOptionMax)
	{
		toppingsOption = NumInputValidation();
	}

	for (int i = 1; i < toppingsArrayLen; i++) // loop through each topping using an array
	{
		if (toppingsOption == i)
		{
			priceTotal = CalculatePrice(burgerPrice, toppingsPrice[i]); // calculate total price using the burger size price + the price of selected topping
			cout << endl;
			// display message to show which topping is added + the price
			cout << "You have added " << toppingsArray[toppingsOption] << " to your burger. Your current price is: " << fixed << setprecision(decimalFilling) << priceTotal << " credits. " << endl <<
				// allow user to add more toppings
				"Would you like to add additional toppings? Please input 'Y' for yes and 'N' for no" << endl;
			cin >> yesNo;
			system("cls");
			ToppingsMenu();

			while (cin.fail() || yesNo != "Y" && yesNo != "N" && yesNo != "y" && yesNo != "n")
			{
				yesNo = StringInputValidation();
			}
		}

		else if (toppingsOption == optionZero) // return to menu if user chooses 0
		{
			system("cls");
			return credits;
		}
	}

	ordersFile.open("recentOrders.txt", ios::app); // append mode
	if (ordersFile.is_open())
	{
		ordersFile << "Toppings: " << toppingsArray[toppingsOption]; // write chosen toppings into file
		ordersFile.close();
	}

	while (yesNo == "Y" || yesNo == "y") // use a while loop to allow user to add as many toppings as they want
	{
		system("cls");
		ToppingsMenu();
		cout << endl << "Please enter a number" << endl;
		cin >> toppingsOption;

		while (cin.fail() || toppingsOption < optionMin || toppingsOption > toppingsOptionMax) // input validation
		{
			toppingsOption = NumInputValidation();
		}

		if (toppingsOption == optionZero)
		{
			system("cls");
			return credits;
		}

		priceTotal = CalculatePrice(priceTotal, toppingsPrice[toppingsOption]); // increment price
		cout << "You have added " << toppingsArray[toppingsOption] << " to your burger. Your current price is: " << fixed << setprecision(decimalFilling) << priceTotal << " credits. " << endl <<
			"Would you like additional toppings? Please input 'Y' for Yes and 'N' for No " << endl;
		cin >> yesNo;

		while (cin.fail() || yesNo != "Y" && yesNo != "N" && yesNo != "y" && yesNo != "n")
		{
			yesNo = StringInputValidation();
		}

		ordersFile.open("recentOrders.txt", ios::app); // append mode
		if (ordersFile.is_open())
		{
			ordersFile << ", " << toppingsArray[toppingsOption]; // write chosen toppings into file
			ordersFile.close();
		}
	}

	if (yesNo == "N" || yesNo == "n") // end order
	{
		system("cls");
		credits = Checkout(priceTotal, credits); // call finish order function and pass through the total price and the credits
	}


	ordersFile.open("recentOrders.txt", ios::app);
	if (ordersFile.is_open() && burgerPrice >= credits)
	{
		ordersFile << fixed << setprecision(decimalFilling);
		ordersFile << endl << "Price: " << fixed << setprecision(decimalFilling) << priceTotal << endl << endl; // write burger price into file
		ordersFile.close();
	}

	return credits;
}


int main()
{
	bool choosingOption = true;
	int menuOption;
	double credits = initialPrice; // declare variable to set the credits to 0

	while (choosingOption) // use a while loop to allow user to choose more than once
	{
		DrawLine();
		cout << endl << "UCLan BURGER" << endl;
		DrawLine();
		cout << endl << "MAIN MENU" << endl <<
			"[current credits = " << fixed << setprecision(decimalFilling) << credits << " ]" << endl;
		DrawLine();
		cout << endl << "1. Add Credits" << endl <<
			"2. Order Burger" << endl <<
			"3. Recent Orders" << endl <<
			"0. Exit" << endl;
		DrawLine();

		cout << endl << "Please enter a number" << endl;
		cin >> menuOption; // user chooses an option

		// input validation to check if data type is incorrect or if the input is less than 0 or more than 2
		while (cin.fail() || menuOption < optionMin || menuOption > menuOptionMax)
		{
			menuOption = NumInputValidation();
		}

		if (menuOption == optionOne)
		{
			credits = AddCredits(credits); // if user chooses 1 then call the add credits function to store its value 
			system("cls");
		}

		else if (menuOption == optionTwo) // if user chooses 2, go to the burger size menu
		{
			system("cls");

			cout << endl << "ORDER BURGER - Select Size" << endl << "Please choose from the following options:" << endl;

			DrawLine(); cout << endl <<
				"1. Small [3.00 credits]" << endl <<
				"2. Medium [5.50 credits]" << endl <<
				"3. Large [7.25 credits]" << endl <<
				"0. Return to Main Menu" << endl;
			DrawLine();

			cout << endl << "Please enter a number" << endl;

			double burgerSize = AddBurgerSize(credits); // display credits based on burger price

			system("pause");
			system("cls");

			if (burgerSize != optionZero)
			{
				credits = AddToppings(burgerSize, credits); // if the user doesn't return to menu, go to toppings menu
			}
		}

		else if (menuOption == optionThree)
		{
			system("cls");
			DrawLine();
			cout << endl;
			cout << "RECENT ORDERS" << endl;
			DrawLine();
			cout << endl;

			fstream ordersFile;
			ordersFile.open("recentOrders.txt", ios::in);
			if (ordersFile.is_open())
			{
				string recentOrdersText;
				while (getline(ordersFile, recentOrdersText))
				{
					cout << recentOrdersText << endl;
				}
				ordersFile.close();
			}
			system("pause");
			system("cls");
		}

		else if (menuOption == optionZero)
		{
			return 0; // exit
		}

	}
}