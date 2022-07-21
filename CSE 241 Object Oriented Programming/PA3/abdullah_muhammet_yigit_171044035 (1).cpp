#include<iostream>
#include<cstdlib>
#include<fstream>
#include<cstring>
#include<vector>

using namespace std;

class ppmImage{
	public:
		void read_ppmImage(const string file_name, ppmImage &object);
		void write_ppmImage(const string file_name, ppmImage &object);
		void set_dimensions(int row, int column);
		void vector_pushback(int number);
		void changing_pixel(ppmImage &object, int value, int index);
		int calculating_size(ppmImage &object);	
		int warning_check(ppmImage &object);
		int returning_row() {return image_row;}
		int returning_column() {return image_column;}
		friend ppmImage operator + (ppmImage const &img1, ppmImage const &img2);
		friend ppmImage operator - (ppmImage const &img1, ppmImage const &img2);
		friend ostream& operator << (ostream& term, ppmImage const &object);
		int& operator () (int row, int column, int color);			
		
		ppmImage(const string file_name)
		{
			std::ofstream outfile(file_name);
		} 
		ppmImage(int row, int column)
		{	
			if(column < 1 || row < 1) exit(1);
			
			int size = (row*column*3) + (row*column - 1);
			for(int i = 0; i < size; i++)
			{
				if((i+1) % 4 == 0 && i != 0) pixel.push_back(-1);
				else pixel.push_back(255);
			}	
		}
		ppmImage(){		
			
		}

	private:
		int image_row;
		int image_column;
		vector <int> pixel;
};


int ppmImage::warning_check(ppmImage &object){

	if(object.pixel[0] < 0 && object.pixel[0] > 255) return 0;
	else return 1;

}

int ppmImage::calculating_size(ppmImage &object){ /* calculates the object's array size and returns it */

	int size = (object.image_row*object.image_column*3) + (object.image_row*object.image_column - 1);
	
	return size;
}

void ppmImage::changing_pixel(ppmImage &object, int value, int index){ /* changes given index with given value */

	object.pixel[index] = value;

}


void ppmImage::set_dimensions(int row, int column){ /* sets given values to private datas */
	image_row = row;
	image_column = column;
}	

void ppmImage::vector_pushback(int number){ /* enters a value to vector */
	pixel.push_back(number);
}	


int write_image(const string file_name, ppmImage &object){ /* stand alone write func */

	ofstream write_file(file_name);
	object.write_ppmImage(file_name,object);

}


void ppmImage::write_ppmImage(const string file_name, ppmImage &object){ /* member write func */

	int size = (object.image_row*object.image_column*3) + (object.image_row*object.image_column - 1);
	
	std::ofstream outfile(file_name);
	outfile << "P3" << endl;
	outfile << object.image_row << " " << object.image_column << endl;
	outfile << "255" << endl;
	
	int i = -1;
	int row_count = 0;
	int column_count = 0;
	
	while(i++ < size -1){
	
		if(pixel[i] != -1){
			if(pixel[i] >= 100) outfile << pixel[i] << " ";
			else if(pixel[i] >= 10 && pixel[i] <= 99) outfile << pixel[i] << "  ";
			else outfile << pixel[i] << "   ";
			column_count++;
		}
	
		else{
			if((column_count) % 3 == 0 && column_count != object.image_column * 3) outfile << "    ";
			else{
				outfile << endl;
				column_count = 0;	
			}
		}
	
	}

	outfile.close();

}


int read_image(const string file_name, ppmImage &object){ /* stand alone read func */

	ifstream read_file(file_name);
	object.read_ppmImage(file_name,object);
	
	if(object.warning_check(object) == 1) return 1;
	else return 0;

}



void ppmImage::read_ppmImage(const string file_name, ppmImage &object){ /* member read func */

	ifstream read_file(file_name);
	char c,temp;
	int x=0,y=0; /* row and column values */
	int count=0, count2 = 1, count3 = 0; /* first count is number of row of the file, second count is determines is the character space or number if it is 1 character is number and if it is 0 character is space of \n, third count is number of channel of the pixel it cant be bigger than 3 */
	int number = 0;
	int size;
	vector <int> temp3;

	while(read_file.get(c)){
	
		if(c != '\n' && c != ' '){
		
			if(temp == 'P'){ /* checks P^ format */
				if(c != '3') exit(1);
				else temp = 'x';		
			}
			if(c == 'P') temp = c;
		
			if(temp == 'x' && count == 1){ /* sets given dimensions on private members */
				if(x == 0) x = c - 48;
				else y = c - 48;
				
				if(x != 0 && y != 0){
					object.set_dimensions(x,y);
					size = (x*y*3) + (x*y - 1);
					temp = 'y';
				}
			}
				
			if(count >= 3){ /* pixel values comes after 3. row */
			
				if(count2 != 0){
					if(number == 0)number += c - 48; /* if number is 0 adds the character's value */
					else{
						number *= 10; /* if number is not 0 and count2 is not 0 also, multiplies current value with 10 and adds the current character's value*/
						number += c - 48;
					}
				}
				else{ /* if count is 0, it means character is space or \n, so adds number to vector and sets the values */
					temp3.push_back(number);
					count3++;
					if(count3 == 3){
						temp3.push_back(-1);
						count3 = 0;
					}
					number = 0;
					number += c - 48;
					count2 = 1;

				}
			
			}
			
		}
		
		else{
			if(c == '\n'){
				count++;
				if(count > 3){
					temp3.push_back(number);
					number = 0;
					temp3.push_back(-1);
					count3 = 0;
					count2 = 1;
				}				
			}
			if(count >= 3 && c == ' '){
				count2 = 0;
			}
			
		}
	
	}
	temp3.push_back(number);
	
	int i;
	for(i = 0; i < size; i++)
		object.vector_pushback(temp3[i]);	
	
}


int swap_channelss(ppmImage &object, int swap_choice){

	int size = object.calculating_size(object);
	int red, green, blue;
	int m=0,n=0; /* m is row value and n is column value */

	if(swap_choice == 1){
	
		for(int i = 0; i < size; i++){
			if(i%4 == 0){ /* first channel of a pixel */
				red = object(m,n,1); /* stores red wit operator */
				green = object(m,n,2); /* stores green wit operator */
				object.changing_pixel(object,green,i); /* changes red channel with green */
				object.changing_pixel(object,red,i+1); /* changes green channel with red */
				n++;
				if(n == 4){
					n = 0;
					m++;
				}	
			}
		}
	}	

	if(swap_choice == 2){
	
		for(int i = 0; i < size; i++){
			if(i%4 == 0){
				red = object(m,n,1); /* stores red wit operator */
				blue = object(m,n,3); /* stores blue wit operator */
				object.changing_pixel(object,blue,i); /* changes red channel with blue */
				object.changing_pixel(object,red,i+2); /* changes blue channel with red */
				n++;
				if(n == 4){
					n = 0;
					m++;
				}	
			}
		}
	}
	
	if(swap_choice == 3){
	
		for(int i = 0; i < size; i++){
			if(i%4 == 0){
				green = object(m,n,2); /* stores green wit operator */
				blue = object(m,n,3); /* stores blue wit operator */
				object.changing_pixel(object,blue,i+1); /* changes green channel with blue */
				object.changing_pixel(object,green,i+2); /* changes blue channel with green */
				n++;
				if(n == 4){
					n = 0;
					m++;
				}	
			}
		}
	}
	

	return 1;
}


ppmImage single_colorr(ppmImage &object, int color_choice){

	int size = object.calculating_size(object);
	int i,m=0,n=0; /* m is row value and n is column value */
	
	ppmImage new_object;
	new_object.set_dimensions(object.returning_row(),object.returning_column());
	
	if(color_choice == 1){
		for(int i = 0; i < size; i++){
			if(i%4 == 0){ /* if it is 0 it means this is red channel of pixel */
				if(n == object.returning_column()){ /* if n is equal to object's column, resets it and increases row value */
					new_object.vector_pushback(object(m,n++,1)); 
					n = 0;
					m++;
				}
				else new_object.vector_pushback(object(m,n++,1)); /* adds red channels of object with operator into new object's vector */
			
			}
			
			else if(i%4 == 1) new_object.vector_pushback(0); /* puts 0 to blue and green channels */
			else if(i%4 == 2) new_object.vector_pushback(0);
			else new_object.vector_pushback(-1); /* puts -1 between every pixel */
		
		}
	}

	if(color_choice == 2){
		for(int i = 0; i < size; i++){
			if(i%4 == 1){ /* if it is 1 it means this is green channel of pixel */
				if(n == object.returning_column()){ /* if n is equal to object's column, resets it and increases row value */
					new_object.vector_pushback(object(m,n++,2));
					n = 0;
					m++;
				}
				else new_object.vector_pushback(object(m,n++,2)); /* adds green channels of object with operator into new object's vector */
			
			}
			
			else if(i%4 == 0) new_object.vector_pushback(0); /* puts 0 to blue and red channels */
			else if(i%4 == 2) new_object.vector_pushback(0);
			else new_object.vector_pushback(-1); /* puts -1 between every pixel */
		
		}
	}
	
	if(color_choice == 3){ 
		for(int i = 0; i < size; i++){
			if(i%4 == 2){ /* if it is 2 it means this is blue channel of pixel */
				if(n == object.returning_column()){ /* if n is equal to object's column, resets it and increases row value */
					new_object.vector_pushback(object(m,n++,3));
					n = 0;
					m++;
				}
				else new_object.vector_pushback(object(m,n++,3)); /* adds blue channels of object with operator into new object's vector */
			
			}
			
			else if(i%4 == 1) new_object.vector_pushback(0); /* puts 0 to green and red channels */
			else if(i%4 == 0) new_object.vector_pushback(0);
			else new_object.vector_pushback(-1);/* puts -1 between every pixel */
		
		}
	}		

	return new_object;
}


ppmImage operator + (ppmImage const &img1, ppmImage const &img2){

	ppmImage new_img;

	if(img1.image_row == img2.image_row && img1.image_column == img2.image_column){
		
		new_img.set_dimensions(img1.image_row,img1.image_column);		
		int size = (img1.image_row*img1.image_column*3) + (img1.image_row*img1.image_column - 1), i;
		
		for(i = 0; i < size; i++){
			
			if(i%4 != 3){
		
				if(img1.pixel[i] + img2.pixel[i] > 255) new_img.vector_pushback(255);/* pixel value cant be bigger than 255, so if it is bigger than 255 sets is to 255*/
				else new_img.vector_pushback(img1.pixel[i] + img2.pixel[i]);
			}
			else
				new_img.vector_pushback(-1); /* puts -1 between every pixel */		
		}

		return new_img;	
	}
	
	return new_img;
}


ppmImage operator - (ppmImage const &img1, ppmImage const &img2){

	ppmImage new_img;

	if(img1.image_row == img2.image_row && img1.image_column == img2.image_column){
		
		new_img.set_dimensions(img1.image_row,img1.image_column);		
		int size = (img1.image_row*img1.image_column*3) + (img1.image_row*img1.image_column - 1), i;
		
		for(i = 0; i < size; i++){
			
			if(i%4 != 3){
		
				if(img1.pixel[i] - img2.pixel[i] < 0) new_img.vector_pushback(0); /* pixel value cant be smaller than 0, so if it is smaller than 0 sets is to 0*/
				else new_img.vector_pushback(img1.pixel[i] - img2.pixel[i]);
			}
			else
				new_img.vector_pushback(-1); * puts -1 between every pixel */		
		}

		return new_img;	
	}
	
	return new_img;
}


ostream& operator << (ostream& term, ppmImage const &object){

	term << "P3" << endl;
	term << object.image_row << " " << object.image_column << endl;
	term << "255" << endl;
	
	int size = (object.image_row*object.image_column*3) + (object.image_row*object.image_column - 1);
	int i = -1;
	int row_count = 0;
	int column_count = 0;

	for(i = 0; i < size; i++){

		if(object.pixel[i] != -1){
			if(object.pixel[i] >= 100) term << object.pixel[i] << " ";
			else if(object.pixel[i] >= 10 && object.pixel[i] <= 99) term << object.pixel[i] << "  ";
			else term << object.pixel[i] << "   ";
			column_count++;
		}
	
		else{
			if((column_count) % 3 == 0 && column_count != object.image_column * 3) term << "    ";
			else{
				term << endl;
				column_count = 0;	
			}
		}

	}
	
	term << endl;
	
	return term;

}


int& ppmImage::operator()(int row, int column, int color){

	if(row >= 0 && row < 4 && column >= 0 && column < 4 && color > 0 && color < 4){ /* checks the values */
	
		int index = (row*16) + (column*4) - 1 + color; /* every row begins from multiple of 16 and every column begins from multiple of 4 because there are -1 values between every pixel in pixel vector */

		return this->pixel[index];
	}
	
	else{
		cout << "Wrong input..." << endl;
		return this->pixel[3]; /* if values are wrong, then returns object.pixel[3] which is equal to -1 */
	}

}


int test_addition(const string file_name_1, const string file_name_2, const string file_name_3){ 

	ppmImage img1, img2, img3;
	int x;
	
	read_image(file_name_1,img1);
	read_image(file_name_2,img2);
	
	img3 = img1 + img2;
	
	ofstream write_file(file_name_3);
	x = write_image(file_name_3,img3);
	write_file.close();
	
	return 1;

}


int test_substraction(const string file_name_1, const string file_name_2, const string file_name_3){

	ppmImage img1, img2, img3;
	int x;
	
	read_image(file_name_1,img1);
	read_image(file_name_2,img2);
	
	img3 = img1 - img2;
	
	ofstream write_file(file_name_3);
	x = write_image(file_name_3,img3);
	write_file.close();
	
	return 1;

}


int test_print(const string filename_image1){

	ppmImage img;
	int x;
	
	x = read_image(filename_image1,img);
	
	cout << img;
	
	return 1;

}


int main(int argc, char** argv){

	char ppm_file_name1[20], ppm_file_name2[20], ppm_file_name3[20], control_string[20];
	control_string[0] = '\0';
	strcpy(ppm_file_name1,argv[2]);
	strcpy(ppm_file_name2,argv[3]);
	strcpy(ppm_file_name3,argv[4]);
	int choice = argv[1][0] - 48;
	int x;
	
	ppmImage img;
	
	if(choice == 1){
		x = test_addition(ppm_file_name1,ppm_file_name2,ppm_file_name3);
	}
	
	else if(choice == 2){
		x = test_substraction(ppm_file_name1,ppm_file_name2,ppm_file_name3);
	}	
	
	else if(choice == 3){
		x = read_image(ppm_file_name1,img);
		ofstream write_file1("ppm_file_name2.ppm");
		x = swap_channelss(img,2);
		x = write_image("ppm_file_name2.ppm",img);
		write_file1.close();
	}
	
	else if(choice == 4){
		x = read_image(ppm_file_name1,img);
		ofstream write_file2("ppm_file_name2.ppm");
		x = swap_channelss(img,3);
		x = write_image("ppm_file_name2.ppm",img);
		write_file2.close();
	}
	
	else if(choice == 5){
		x = read_image(ppm_file_name1,img);
		ofstream write_file3("ppm_file_name2.ppm");
		ppmImage only_red;
		only_red = single_colorr(img,1);
		x = write_image("ppm_file_name2.ppm",only_red);
		write_file3.close();
	}
	
	else if(choice == 6){
		x = read_image(ppm_file_name1,img);
		ofstream write_file4("ppm_file_name2.ppm");
		ppmImage only_green;
		only_green = single_colorr(img,2);
		x = write_image("ppm_file_name2.ppm",only_green);
		write_file4.close();
	}
	else if(choice == 7){
		x = read_image(ppm_file_name1,img);
		ofstream write_file5("ppm_file_name2.ppm");
		ppmImage only_blue;
		only_blue = single_colorr(img,3);
		x = write_image("ppm_file_name2.ppm",only_blue);
		write_file5.close();
	}				
	
	return 0;
}
