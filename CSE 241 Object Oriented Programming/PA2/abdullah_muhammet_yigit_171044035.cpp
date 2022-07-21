#include<iostream>
#include<cstdlib>
#include<fstream>
#include<cstring>
#include<vector>

using namespace std;

class ppmImage{
	public:
		int read_ppmImage(const string file_name, ppmImage &object);
		int write_ppmImage(const string file_name, ppmImage &object);
		int swap_channels(ppmImage &object, int swap_choice);
		ppmImage single_color(ppmImage &object, int color_choice);
		void set_dimensions(int row, int column);
		void vector_pushback(int number);	
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


void ppmImage::set_dimensions(int row, int column){ /* sets given values to private datas */
	image_row = row;
	image_column = column;
}	

void ppmImage::vector_pushback(int number){ /* enters a value to vector */
	pixel.push_back(number);
}	


int ppmImage::write_ppmImage(const string file_name, ppmImage &object){

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
	
	return 1;

}


int ppmImage::read_ppmImage(const string file_name, ppmImage &object){

	ifstream read_file(file_name);
	char c,temp;
	int x=0,y=0;
	int count=0, count2 = 1, count3 = 0;
	int number = 0;
	int size;
	vector <int> temp3;

	while(read_file.get(c)){
	
		if(c != '\n' && c != ' '){
		
			if(temp == 'P'){
				if(c != '3') return 0;
				else temp = 'x';		
			}
			if(c == 'P') temp = c;
		
			if(temp == 'x' && count == 1){
				if(x == 0) x = c - 48;
				else y = c - 48;
				
				if(x != 0 && y != 0){
					object.set_dimensions(x,y);
					size = (x*y*3) + (x*y - 1);
					temp = 'y';
				}
			}
				
			if(count >= 3){
			
				if(count2 != 0){
					if(number == 0)number += c - 48;
					else{
						number *= 10;
						number += c - 48;
					}
				}
				else{
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
				}				
			}
			if(count >= 3 && c == ' '){
				count2 = 0;
			}
			
		}
	
	}
	
	int i;
	for(i = 0; i < size; i++) object.vector_pushback(temp3[i]);

	return 1;
}


int ppmImage::swap_channels(ppmImage &object, int swap_choice){

	int size = (object.image_row*object.image_column*3) + (object.image_row*object.image_column - 1);
	int temp;
	

	if(swap_choice == 1){
	
		for(int i = 0; i < size; i++){
			if(i%4 == 0){
				temp = object.pixel[i];
				object.pixel[i] = object.pixel[i+1];
				object.pixel[i+1] = temp;	
			}
		}
	}
	
	else if(swap_choice == 2){
	
		for(int i = 0; i < size; i++){
			if(i%4 == 0){
				temp = object.pixel[i];
				object.pixel[i] = object.pixel[i+2];
				object.pixel[i+2] = temp;	
			}
		}
	}
	
	else if(swap_choice == 3){
	
		for(int i = 0; i < size; i++){
			if(i%4 == 1){
				temp = object.pixel[i];
				object.pixel[i] = object.pixel[i+1];
				object.pixel[i+1] = temp;	
			}
		}
	}
	
	else return 0;

	return 1;

}


ppmImage ppmImage::single_color(ppmImage &object, int color_choice){

	ppmImage new_object(image_row,image_column);
	new_object.set_dimensions(object.image_row,object.image_column);
	
	int size = (object.image_row*object.image_column*3) + (object.image_row*object.image_column - 1);
	
	if(color_choice == 1){
		for(int i = 0; i < size; i++){
			if(i%4 == 0) new_object.pixel[i] = object.pixel[i];
			else if(i%4 == 1) new_object.pixel[i] = 0;
			else if(i%4 == 2) new_object.pixel[i] = 0;
		
		}
	}
	
	if(color_choice == 2){
		for(int i = 0; i < size; i++){
			if(i%4 == 1) new_object.pixel[i] = object.pixel[i];
			else if(i%4 == 0) new_object.pixel[i] = 0;
			else if(i%4 == 2) new_object.pixel[i] = 0;
		
		}
	}	
	
	if(color_choice == 3){
		for(int i = 0; i < size; i++){
			if(i%4 == 2) new_object.pixel[i] = object.pixel[i];
			else if(i%4 == 1) new_object.pixel[i] = 0;
			else if(i%4 == 0) new_object.pixel[i] = 0;
		
		}
	}
	
	return new_object;
}



int main(int argc, char** argv){

	char file_name[20];
	strcpy(file_name,argv[2]);
	int choice = argv[1][0] - 48;
	int x;
	
	ppmImage img;

	if(choice == 1){
		x = img.read_ppmImage(file_name,img);
		ofstream write_file("o1.ppm");
		x = img.write_ppmImage("o1.ppm",img);
		write_file.close();
	}
	else if(choice == 2){
		x = img.read_ppmImage(file_name,img);
		ofstream write_file2("o2.ppm");
		x = img.swap_channels(img,1);
		x = img.write_ppmImage("o2.ppm",img);
		write_file2.close();
	}			
	else if(choice == 3){
		x = img.read_ppmImage(file_name,img);
		ofstream write_file3("o3.ppm");
		x = img.swap_channels(img,2);
		x = img.write_ppmImage("o3.ppm",img);
		write_file3.close();
	}	
	else if(choice == 4){
		x = img.read_ppmImage(file_name,img);
		ofstream write_file4("o4.ppm");
		x = img.swap_channels(img,3);
		x = img.write_ppmImage("o4.ppm",img);
		write_file4.close();
	}	
	else if(choice == 5){
		x = img.read_ppmImage(file_name,img);
		ofstream write_file5("o5.ppm");
		ppmImage only_red;
		only_red = img.single_color(img,1);
		x = only_red.write_ppmImage("o5.ppm",only_red);
		write_file5.close();
	}
	else if(choice == 6){
		x = img.read_ppmImage(file_name,img);
		ofstream write_file6("o6.ppm");
		ppmImage only_green;
		only_green = img.single_color(img,2);
		x = only_green.write_ppmImage("o6.ppm",only_green);
		write_file6.close();
	}
	else if(choice == 7){
		x = img.read_ppmImage(file_name,img);
		ofstream write_file7("o7.ppm");
		ppmImage only_blue;
		only_blue = img.single_color(img,3);
		x = only_blue.write_ppmImage("o7.ppm",only_blue);
		write_file7.close();
	}	
	
	
	return 0;
}
