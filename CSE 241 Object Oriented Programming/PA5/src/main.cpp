#include "book.h"
#include "music.h"
#include "movie.h"

template<typename T>
void writing_output(vector<T>& object){

	ofstream output_file("output.txt"); 
	
	string temp = object[0].returning_type();

	output_file << "Catalog Read: " << temp  << endl;
	
	int sizeofObject = object.size() - 1; /*total entry*/
	int UniqueCount = sizeofObject; /*unique entry which will decrease when an object is not unique*/

	for(int i = 0; i < sizeofObject; i++){ /*founds missing field and duplicate entry and markes that object has those errors*/
	
		if(i == 0){ /*for first object*/
			if(!object[i].missing_field_check()){
				output_file << "Exception : missing field" << endl;
				object[i].set_isUnique(0);
				output_file << object[i].get_fields() << endl;
				UniqueCount--;				
				}
			else
				object[i].set_isUnique(1);	
		}
		
		else{	
		
			T temp_object = object[i];	/*fills a temp object array as the same of real object array and compares it with real object array to find duplicate entry*/
			for(int k = 0; k < i; k++){
				if(object[k].get_title() == temp_object.get_title()){
					output_file << "Exception : duplicate entry" << endl;
					temp_object.set_isUnique(0);
					output_file << object[i].get_fields() << endl;
					UniqueCount--;	
					break;
				}
				else
					temp_object.set_isUnique(1);		
		
			}
			
			object[i] = temp_object;
			
			if(!object[i].missing_field_check() && object[i].get_isUnique()){
				output_file << "Exception : missing field" << endl;
				object[i].set_isUnique(0);
				output_file << object[i].get_fields() << endl;
				UniqueCount--;				
			}
			
			
		}

	}
	
	output_file << UniqueCount << " unique entries" << endl;

	ifstream command_file("commands.txt");
	
	string line;
	
	char command[20], field[10], word[100];
	int temp1=-1,temp2=-1,command_count=0,line_count=0;
	
	while(getline(command_file,line)){

		for(int i = 0; i < line.length(); i++){ /*this for gets a command line and splits it into 3 char array (command, field and word which will be searched or sorted)*/
		
			if(command_count == 0 && line[i] != ' ') command[i] = line[i];
			
			if(line[i] == '"'){ /*determines the " character's indexes */
				command[i-1] = '\0';
				
				command_count++;
				if(temp1 != -1) temp2 = i ;
				else temp1 = i;
			}
			
			if(temp2 != -1){
				
				if(command[1] == 'e'){ /*copies the word between determined indexes*/
					
					if(line_count == 0)
						{line.copy(word,temp2-temp1-1,temp1+1); word[temp2-temp1-1] = '\0';}	
					else if(line_count == 1)
						{line.copy(field,temp2-temp1-1,temp1+1); field[temp2-temp1-1] = '\0';}
						
				}
				
				else if(command[1] == 'o'){
					line.copy(field,temp2-temp1-1,temp1+1);
					field[temp2-temp1-1] = '\0';
				}
				
				temp1 = -1;
				temp2 = -1;
				line_count++;
				
				
				
			}

		}
		
		int word_is_found = -1;/**/
		int search_repeat_count = 0; /*if there are more than one searched object, it prevents the repeating of command line */
				
		if(command[1] == 'e'){
		
			int res = object[0].search_fields(field); /*checks that if the object has given filed*/
		
			if(res == 0){
				output_file << "Exception: command is wrong" << endl;
				output_file << line << endl;
			}
			
			else{
			
				for(int j = 0; j < sizeofObject; j++){
				
					if(object[j].get_isUnique() != 0){
							
						int res1 = object[j].searching_word(word,field); /*searches the given word into given field*/
							
						if(res1 != 0){
							word_is_found = 1;
							if(search_repeat_count == 0)output_file << line << endl;
							search_repeat_count++;
							output_file << object[j].get_fields() << endl;
						}
					}
				
				
				}
				
				if(word_is_found == -1)
						output_file << "There is no entry" << endl;
				else
					word_is_found = -1;			
			
			}
		
		}
		
		else if(command[1] == 'o'){
		
			int res = object[0].search_fields(field); /*checks that if the object has given filed*/
		
			if(res == 0){
				output_file << "Exception: command is wrong" << endl;
				output_file << line << endl;
			}
			
			else{
			
				if(!strcmp(field,"year")){
				
					output_file << line << endl;
				
					vector<int> all_years; /*gets the years of all objects and sorts it in this vector*/
					all_years.resize(sizeofObject);
					for(int x = 0; x < sizeofObject; x++)
						if(object[x].get_isUnique())
							all_years[x] = object[x].get_year();
					
					sort(all_years.begin(),all_years.end());
					
					for(int x = 0; x < sizeofObject; x++){ /*then prints the matched object's info's with year*/
						for(int y = 0; y < sizeofObject; y++){
							if(all_years[x] == object[y].get_year())
								if(object[y].get_isUnique())
									output_file << object[y].get_fields() << endl;	
						}
					}	
				}
				
				else{
				
					output_file << line << endl;
				
					vector<string> all_titles; 
					all_titles.resize(sizeofObject);
					for(int x = 0; x < sizeofObject; x++)
						if(object[x].get_isUnique())
							all_titles[x] = object[x].get_a_field(field); /*gets the sent fields of all objects and sorts it in this vector*/
					
					sort(all_titles.begin(),all_titles.end());
					
					for(int x = 0; x < sizeofObject; x++){ /*then prints the matched object's info's with sent field*/
						for(int y = 0; y < sizeofObject; y++){
							if(all_titles[x] == object[y].get_a_field(field))
								if(object[y].get_isUnique())
									output_file << object[y].get_fields() << endl;	
						}
					}	
				}					
			
			}			

		}

		/*resets some counts*/

		command_count = 0;
		line_count = 0;
		temp1 = -1;
		temp2 = -1;
		field[0] = '\0';
		word[0] = '\0';
		command[0] = '\0';

	}
	
	output_file.close();

}

template<typename T>
void reading_data_file(vector<T>& object){

	int object_count = 1, line_count = 0;
	string line;
	
	ifstream data_file("data.txt");

	while(getline(data_file,line)){ /*gets line and sent it to object's function to split and keep it into that object*/
	
		if(line_count != 0){

			object[object_count-1].set_fields(line);
			
			vector<T> temp_object; /*creates aa vector object with current size of real object,fills is with real object, increases real object's size*/
			temp_object.resize(object_count);
			temp_object = object;
			object.resize(object_count+1);
			for(int k = 0; k < object_count;k++) object[k] = temp_object[k];/*gets objects from temp object by one by*/
			
			object_count++;	
							
			
		}
		line_count++;
	}
	
	data_file.close();
	
}


int main(){

	string line;


	vector<Book> books;
	books.resize(1);
	
	vector<Music> musics;
	musics.resize(1);	
	
	vector<Movie> movies;
	movies.resize(1);
	
	
	ifstream data_file("data.txt");/*reads first line and sends matched object*/
	getline(data_file,line);
	data_file.close();
	
	if(line == "book"){	
		reading_data_file(books);
		writing_output(books);	
	}
			
	else if(line == "music"){	
		reading_data_file(musics);
		writing_output(musics);	
	}

	else if(line == "movie"){	
		reading_data_file(movies);
		writing_output(movies);	
	}		
	
	


	return 0;
}
