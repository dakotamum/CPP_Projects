// *** NOTE: This code was provided as part of the assignment ***

// a frivilous class of generic bugs
class Bug
{
public:
	Bug();
	Bug(int legs, int mass, int odomoter);

	int getLegs() { return m_legs; }
	int getMass() { return m_mass; }
	int getOdometer() { return m_odometer; }

	void print();
	void eat(int bites);
	void walk(int steps);
	void poop();

private:
	int m_legs;
	int m_mass;
	int m_odometer;
};
