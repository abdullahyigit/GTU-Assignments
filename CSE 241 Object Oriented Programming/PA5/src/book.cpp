#include "book.h"

void Book::set_fields(string line){ /*gets line and splits is into fileds*/

	int temp1=-1,temp2=-1;
	char author[50],tags[100],title[100],year[50];
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
				{line.copy(author,temp2-temp1-1,temp1+1); author[temp2-temp1-1] = '\0';}
			else if(line_count == 2)
				{line.copy(year,temp2-temp1-1,temp1+1); year[temp2-temp1-1] = '\0';}
			else
				{line.copy(tags,temp2-temp1-1,temp1+1); tags[temp2-temp1-1] = '\0';}
									
			temp1 = -1;
			temp2 = -1;
			line_count++;
		}									
	}

	
	Year = atoi(year);
	Title = title;
	Tags = tags;
	Author = author;
}

string Book::returning_type(){
	return Type;
}
		
string Book::get_title(){
	return Title;
}		
		
int Book::get_year(){
	return Year;
}

string Book::get_fields(){ /*returns a string which includes a line that will be print into output.txt*/

	string full_fields;

	if(Year != 0)
		full_fields = '"' + Title + '"' + ' ' + '"' + Author + '"' + ' ' + '"' + to_string(Year) + '"' + ' ' + '"' + Tags + '"';
	else
	 	full_fields = '"' + Title + '"' + ' ' + '"' + Author + '"' + ' ' + '"' + '"' + ' ' + '"' + Tags + '"';
	 	
	return full_fields;
}
		
string Book::get_a_field(string field){ /*returns given field*/
		
	if(field == "title")
		return Title;
	else if(field == "author")
		return Author;				
	else if(field == "tags")
		return Tags;
				
	return "none";	
		
}		
		
int Book::get_isUnique(){
	return isUnique;
}


int Book::search_fields(string field){ /* checks given fields with object's field */
	if(field == "title" || field == "author" || field == "year" || field == "tags")
		return 1;
	else
		return 0;
}					
								
void Book::set_isUnique(int number){
	isUnique = number;	
}
		
int Book::searching_word(string word, string field){ /*search a word with given fields*/
		
	int foundCount = -1;
		
	if(field == "title")
		foundCount = Title.find(word);
	else if(field == "author")
		foundCount = Author.find(word);				
	else if(field == "year"){
		if(Year == stoi(word)) foundCount = 1;
	}	
	else if(field == "tags")
		foundCount = Tags.find(word);
		
	if(foundCount == -1)
		return 0;
				
	else
		return 1;
					
}	

int Book::missing_field_check(){ /*checks missing fields*/
		
	if(Title.empty() || Tags.empty() || Author.empty() || Year == 0)
		return 0;
	else
		return 1;
}
