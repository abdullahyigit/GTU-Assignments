#ifndef BOOK_H
#define BOOK_H
#include "entry.h"

class Book : public Entry{

	public:

		Book(){	
			Year = 0;
			Type = "book";
		}	
		
		void set_fields(string line);		
		void print_fields();
		string returning_type();
		string get_fields();		
		int get_year();		
		string get_title();							
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
		string Tags;
		string Author;
		int Year;
};

#endif
