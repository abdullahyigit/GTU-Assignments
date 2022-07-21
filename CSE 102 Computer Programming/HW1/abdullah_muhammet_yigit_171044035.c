#include<stdio.h>

#define macro 3

int main(){

	float sum_of_x = 0, sum_of_y = 0, input_x, input_y,class1_x_avg,class2_x_avg,class1_y_avg,class2_y_avg,midpoint_of_x,midpoint_of_y,equation_x = 1,equation_y = 1,equation_number,incline_of_normal,incline_of_equation,normal_x = 1,normal_y = -1,normal_number,result,temp = 0,result_class1_avg;
	int i,quit_count = 0;

	/*
		it counts the sum of entered values. First, when for loop comes to 9 counts the class1's averages and resets sum variables, when loop comes to 19 counts the class2's average this time. 

	*/

	for(i=0;i<macro;i++){
		
		scanf("%f %f",&input_x,&input_y);

		sum_of_x += input_x;
		sum_of_y += input_y;

		if(i==((macro/2) - 1)){

			class1_x_avg = sum_of_x / 2;
			class1_y_avg = sum_of_y / 2;
			sum_of_x = 0;
			sum_of_y = 0;

		}
			
		if(i==(macro - 1)){

			class2_x_avg = sum_of_x / 2;
			class2_y_avg = sum_of_y / 2;

		}

	}

	/*
		this part uses the formula (y - y1) / (y1 - y2) = (x - x1) / (x1 - x2) to find the equation like ax + by + c = 0. a = equation_x, b = equation_y, c = equation_number.
	*/
		
	equation_number = ((class2_y_avg - class1_y_avg) * (-class2_x_avg)) - ((class2_x_avg - class1_x_avg) * (-class2_y_avg));
	equation_x *= (class2_y_avg - class1_y_avg);
	equation_y *= (class2_x_avg - class1_x_avg);
	equation_y = (-equation_y);

	/*
		after found the equation, calculates the midpoint of averages class1 and class2 and incline of the equation.
	*/

	midpoint_of_x = (class1_x_avg + class2_x_avg) / 2;
	midpoint_of_y = (class1_y_avg + class2_y_avg) / 2;

	incline_of_equation = (class1_y_avg - class2_y_avg) / (class1_x_avg - class2_x_avg);

	/*
		this part uses the formula "y - y1 = m (x - x1)" to find the normal of equation. 
		for the if statement = if midpoint of x '0' it means incline of normal(m) is infinity, so if we pass the m value to the opposite site like a divider it will make the opposite site '0' and the
normal of equation will be "x=x1".
		for the else if statement = if midpoint of y '0' it means incline of normal(m) is '0', so the normal of equation will be "y=y1"
		for the else statement = this statement uses the formula "m1 * m2 = -1" to find icline of normal, after than puts yhe m into the formula "y - y1 = m (x - x1)"
	*/

	if(midpoint_of_x == 0 && midpoint_of_y != 0){ 
						
		normal_x = 1;
		normal_y = 0;
		normal_number = midpoint_of_x;

	}

	else if(midpoint_of_y == 0 && midpoint_of_x != 0){ 

		normal_x = 0;
		normal_y = 1;
		normal_number = midpoint_of_y;

	}

	else{

		incline_of_normal = (-1) / incline_of_equation;
		normal_x *= incline_of_normal;
		normal_number = ((-midpoint_of_x) * incline_of_normal) + midpoint_of_y;

	}

	/*
		finally gets inputs from the user. there are 3 statement (incline of normal, result of normal with input and result of normal with avegare of class1) so there should be 8 if else statement
to check the class of input.
	*/
	

	while(quit_count != 1){

		if(scanf("%f%f",&input_x,&input_y) == 0) quit_count = 1;

		if(quit_count == 0){
		
			i++;

			result = (input_x * normal_x) + (input_y * normal_y) + normal_number;
			result_class1_avg = (class1_x_avg * normal_x) + (class1_y_avg * normal_y) + normal_number;

			if(normal_x >= 0 && result < 0 && result_class1_avg < 0) printf("class1\n");
			else if(normal_x >= 0 && result < 0 && result_class1_avg > 0) printf("class2\n");
			else if(normal_x >= 0 && result > 0 && result_class1_avg > 0) printf("class1\n");
			else if(normal_x >= 0 && result > 0 && result_class1_avg < 0) printf("class2\n");
			else if(normal_x <= 0 && result < 0 && result_class1_avg < 0) printf("class1\n");
			else if(normal_x <= 0 && result < 0 && result_class1_avg > 0) printf("class2\n");
			else if(normal_x <= 0 && result > 0 && result_class1_avg > 0) printf("class1\n");
			else if(normal_x <= 0 && result > 0 && result_class1_avg < 0) printf("class2\n");

			i++;

		}
	
	}

	return 0;
}
