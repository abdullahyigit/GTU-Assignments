#include<iostream>
#include<cstdlib>

using namespace std;

class Point
{
	public:
		double first();
		double second();
		void move(double first, double second);
		void rotate();
		void set(double first, double second);

	private:
		double x;
		double y;
};

double Point::first()
{
	return x;
}

double Point::second()
{
	return y;
}

void Point::set(double first, double second)
{
	x = first;
	y = second;
}

void Point::move(double first, double second)
{
	x += first;
	y += second;
}

void Point::rotate()
{
	int temp = x;
	if(y != 0) x = -y;
	else x = 0;
	y = temp;
}

int main()
{

	

	Point A,B,C;

	A.set(-1,-1);
	cout << "Point is set to   " << A.first() << "," << A.second() << endl;
	
	A.rotate();	
	cout << "Point is rotated  " << A.first() << "," << A.second() << endl;
	
	A.rotate();
	cout << "Point is rotated  " << A.first() << "," << A.second() << endl;
	
	A.move(1,-1);
	cout << "Point is moved   " <<  A.first() << "," << A.second() << endl;

	A.rotate();
	cout << "Point is rotated  " << A.first() << "," << A.second() << endl;
	

	
	return 0;
}
