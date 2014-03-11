#ifndef BUFFER_H
#define BUFFER_H

#include <iostream>
#include <vector>

#include <unistd.h>
//#include <stdlib.h>
#include <ncurses.h>

#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

class Buffer
{
	public:
		string start; // startovací sekvence
		int sposition; // startovaci pozice
		int linenum; // aktualni linka od spusteni terminalu.	
		int lpointer; // ukazatel na aktualni pozici v cele historii
		int xpointer; // ukazatel na aktualni pozici v danem radku.
		int ypointer; // ukazatel na aktualni lajnu v aktivnim okne.
		int hpointer; // ukazatel na aktualni pozici v historii.
		int rows, cols; // maximalni hodnoty terminalu.
        string current, temp; // aktualni radek 
		string wline; // kompletni radka, pro ulozeni do historie.
		vector<string> history; // historie prikazu
		vector<string> lines; // historie celeho terminalu
		
		void addChar(char c);
		void changeCurrent(string newCurrent);
		void changeStart(string input);
		void scrollUp();
		void scrollDown();
		void writeLine(string input);
		void writeStart();
		void write(string input);
		void nextLine();
		string getCommand();
		
		Buffer();
        virtual ~Buffer();
	protected:

    private:
};

#endif // BUFFER_H
