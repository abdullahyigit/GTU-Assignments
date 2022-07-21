#include<iostream>
#include<cstdlib>

using namespace std;

class Fraction
{
	public:
		void setNumerator(int n);
		void setDenominator(int d);
		void output();
		double getDouble();
		
	private:
		int numerator;
		int denominator;
		int gcd();
};

void Fraction::setNumerator(int n)
{
	numerator = n;
}

void Fraction::setDenominator(int d)
{
	denominator = d;
}

double Fraction::getDouble()
{
	return (static_cast<double>(numerator)/denominator);

}

void Fraction::output()
{
	int greatest = gcd();

	cout << numerator/greatest << " / " << denominator/greatest << endl;
}

int Fraction::gcd()
{
	int max, greatest;
	
	if(numerator >= denominator) max = denominator;
	else max = numerator;

	for(int i = 1; i <= max; i++)
	{
		if((numerator % i) == 0 && (denominator % i) == 0) greatest = i;
	}
	
	return greatest;
}

int main()
{
	int num1 = 50;
	int num2 = 50;

	Fraction f1;

	f1.setNumerator(num1);
	f1.setDenominator(num2);
	cout << "num = " << num1 << endl;
	cout << "denom = " << num2 << endl;
	cout << "num/denom = " << f1.getDouble() << endl;
	f1.output();
	
}
