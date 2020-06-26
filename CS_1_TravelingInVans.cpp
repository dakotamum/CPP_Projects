// Dakota Mumford
// Ski Trip Cost Report Assignment

#include <iostream>
#include <iomanip>
using namespace std;

// main function calculates values and outputs a cost report for
// a company sending their employees on a ski trip with vans
int main()
{
	// initial values
	int numEmployees = 115;
	int passengersPerVan = 14;
	double pricePerPassenger = 12.50;
	double salesTaxRate = 0.0675;

	// computed values
	int vansNeeded = numEmployees / passengersPerVan;
	int seatsUnused = numEmployees % vansNeeded;
	double fareCost = pricePerPassenger * numEmployees;
	double salesTax = salesTaxRate * fareCost;
	double totalCost = fareCost + salesTax;

	// output report
	cout << "Cost of Travel for Company Ski Trip\n";
	cout << "=======================================\n";
	cout << setw(30) << left << "Number of Passengers" << numEmployees << endl;
	cout << setw(30) << left << "Number of Unoccupied Seats" <<seatsUnused << endl;
	cout << setprecision(2) << fixed << setw(30) << left << "Cost of fare" << "$" << fareCost << endl;
	cout << setprecision(2) << fixed << setw(30) << left << "Sales Tax" << "$" << salesTax << endl;
	cout << setprecision(2) << fixed << setw(30) << left << "Total Cost" << "$" << totalCost << endl;

	return 0;
}
