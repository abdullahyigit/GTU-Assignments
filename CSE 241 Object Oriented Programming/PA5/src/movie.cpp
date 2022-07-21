#include "movie.h"

void Movie::set_fields(string line){/*gets line and splits is into fileds*/	

	int temp1=-1,temp2=-1;
	char director[50],genre[100],title[100],year[50],starring[50];
	int line_count = 0;

	for(int i = 0; i < line.length(); i++){
			
		if(line[i] == '"'){
			if(temp1 != -1) temp2 = i ;
			else temp1 = i;
		}
							
		if(temp2 != -1){
			if(line_count == 0)
				{line.copy(title,temp2-temp1-1,temp1+1); title[temp2-temp1-1] = '\0';}			
			else if(line_count == 1)
				{line.copy(director,temp2-temp1-1,temp1+1); director[temp2-temp1-1] = '\0';}
			else if(line_count == 2)
				{line.copy(year,temp2-temp1-1,temp1+1); year[temp2-temp1-1] = '\0';}
			else if (line_count == 3)
				{line.copy(genre,temp2-temp1-1,temp1+1); genre[temp2-temp1-1] = '\0';}
			else
				{line.copy(starring,temp2-temp1-1,temp1+1); starring[temp2-temp1-1] = '\0';}	
									
			temp1 = -1;
			temp2 = -1;
			line_count++;
		}									
	}

	Year = atoi(year);
	Title = title;
	Genre = genre;
	Director = director;
	Starring = starring;
}

string Movie::returning_type(){
	return Type;
}
		
string Movie::get_title(){
	return Title;
}		
		
int Movie::get_year(){
	return Year;
}
		
string Movie::get_fields(){ /*returns a string which includes a line that will be print into output.txt*/

	string full_fields;

	if(Year != 0)		
		full_fields = '"' + Title + '"' + ' ' + '"' + Director + '"' + ' ' + '"' + to_string(Year) + '"' + ' ' + '"' + Genre + '"' + ' ' + '"' + Starring + '"';
	else
		full_fields = '"' + Title + '"' + ' ' + '"' + Director + '"' + ' ' + '"' + '"' + ' ' + '"' + Genre + '"' + ' ' + '"' + Starring + '"';
		
	return full_fields;
}
		
string Movie::get_a_field(string field){ /*returns given field*/
		
	if(field == "title")
		return Title;
	else if(field == "director")
		return Director;				
	else if(field == "genre")
		return Genre;
	else if(field == "starring")
		return Starring;		
				
	return "none";	
		
}		
		
int Movie::get_isUnique(){
	return isUnique;
}


int Movie::search_fields(string field){ /* checks given fields with object's field */
	if(field == "title" || field == "director" || field == "year" || field == "genre" || field == "starring")
		return 1;
	else
		return 0;
}					
								
void Movie::set_isUnique(int number){
	isUnique = number;	
}
		
int Movie::searching_word(string word, string field){ /*search a word with given fields*/
		
	int foundCount = -1;
		
	if(field == "title")
		foundCount = Title.find(word);
	else if(field == "director")
		foundCount = Director.find(word);				
	else if(field == "year"){
		if(Year == stoi(word)) foundCount = 1;
	}	
	else if(field == "genre")
		foundCount = Genre.find(word);
	else if(field == "starring")
		foundCount = Starring.find(word);
				
	if(foundCount == -1)
		return 0;
				
	else
		return 1;
					
}	

int Movie::missing_field_check(){ /*checks missing fields*/
		
	if(Title.empty() || Genre.empty() || Director.empty() || Year == 0 || Starring.empty())
		return 0;
	else
		return 1;
}
