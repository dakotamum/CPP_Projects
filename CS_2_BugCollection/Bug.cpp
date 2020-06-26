// *** NOTE: This code was provided as part of the assignment ***
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include "bug.hpp"

using namespace std;

Bug::Bug()
{
	m_legs = rand() % 10;
	m_mass = rand() % 10;
	m_odometer = 0;
}

Bug::Bug(int legs, int mass, int odometer) {
	m_legs = legs, m_mass = mass, m_odometer = odometer;
}

//simple print function
void Bug::print()
{
	cout << "legs: " << m_legs;
	cout << " mass: " << m_mass;
	cout << " odo: " << m_odometer;
	cout << endl;
}

void Bug::eat(int bites)
{
	//a bug is what it eats
	m_mass += bites;
	//if a bug's mass exceeds 10, it
	//uses 5 units to grow a new leg
	if (m_mass > 10)
	{
		m_mass = 5;
		m_legs++;
	}

}

void Bug::walk(int steps)
{
	//bugs with no legs nowhere
	if (m_legs == 0)
	{
		return;
	}

	m_odometer += steps;
	//if a bug stop walking with a 0 on
	//the last digit of the odometer,
	//it sacrifices a leg
	if (m_odometer % 10 == 0)
	{
		m_legs--;
	}
}

void Bug::poop()
{
	//try the new bug diet!
	m_mass -= rand() % min(m_mass, 5);

	//if a bug trys to poop itself into 
	//oblivion, it loses a leg instead
	if (m_mass < 3)
	{
		if (m_legs > 0)
		{
			m_legs--;
		}
		m_mass = 3;
	}
}
