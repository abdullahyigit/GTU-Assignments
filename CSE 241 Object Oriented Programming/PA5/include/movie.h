#ifndef MOVIE_H
#define MOVIE_H
#include "entry.h"

class Movie : public Entry{

	public:
	
		Movie(){	
			Year = 0;
			Type = "movie";
		}
			
		void set_fields(string line);		
		string returning_type();		
		string get_title();				
		int get_year();		
		string get_fields();		
		string get_a_field(string field);				
		int get_isUnique();		
		int search_fields(string field);													
		void set_isUnique(int number);		
		int searching_word(string word, string field);	
		int missing_field_check();		

	private:
		string Type;
		int isUnique;
		string Title;
		string Genre;
		string Director;
		string Starring;
		int Year;
};

#endif
