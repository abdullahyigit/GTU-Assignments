#include "music.h"

void Music::set_fields(string line){/*gets line and splits is into fileds*/

	int temp1=-1,temp2=-1;
	char artists[50],genre[100],title[100],year[50];
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
				{line.copy(artists,temp2-temp1-1,temp1+1); artists[temp2-temp1-1] = '\0';}
			else if(line_count == 2)
				{line.copy(year,temp2-temp1-1,temp1+1); year[temp2-temp1-1] = '\0';}
			else
				{line.copy(genre,temp2-temp1-1,temp1+1); genre[temp2-temp1-1] = '\0';}
									
			temp1 = -1;
			temp2 = -1;
			line_count++;
		}									
	}

	Year = atoi(year);
	Title = title;
	Genre = genre;
	Artists = artists;
}

string Music::returning_type(){
	return Type;
}
		
string Music::get_title(){
	return Title;
}		
		
int Music::get_year(){
	return Year;
}
	
string Music::get_fields(){ /*returns a string which includes a line that will be print into output.txt*/

	string full_fields;

	if(Year != 0)		
		full_fields = '"' + Title + '"' + ' ' + '"' + Artists + '"' + ' ' + '"' + to_string(Year) + '"' + ' ' + '"' + Genre + '"';
	else
		full_fields = '"' + Title + '"' + ' ' + '"' + Artists + '"' + ' ' + '"' + '"' + ' ' + '"' + Genre + '"';
			
	return full_fields;
}
		
string Music::get_a_field(string field){ /*returns given field*/
		
	if(field == "title")
		return Title;
	else if(field == "artists")
		return Artists;				
	else if(field == "genre")
		return Genre;
				
	return "none";	
		
}		
		
int Music::get_isUnique(){
	return isUnique;
}


int Music::search_fields(string field){ /* checks given fields with object's field */
	if(field == "title" || field == "artists" || field == "year" || field == "genre")
		return 1;
	else
		return 0;
}					
								
void Music::set_isUnique(int number){
	isUnique = number;	
}
		
int Music::searching_word(string word, string field){ /*search a word with given fields*/
		
	int foundCount = -1;
		
	if(field == "title")
		foundCount = Title.find(word);
	else if(field == "artists")
		foundCount = Artists.find(word);				
	else if(field == "year"){
		if(Year == stoi(word)) foundCount = 1;
	}	
	else if(field == "genre")
		foundCount = Genre.find(word);
		
	if(foundCount == -1)
		return 0;
				
	else
		return 1;
					
}	

int Music::missing_field_check(){ /*checks missing fields*/
		
	if(Title.empty() || Genre.empty() || Artists.empty() || Year == 0)
		return 0;
	else
		return 1;
}
