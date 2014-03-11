#include "include/Buffer.h"
//TODO:: docela fuska, mozna by se mohlo znovu prespat
//TODO:: konecne autocompletetion :)))

Buffer::Buffer()
{
	// prepnuti bash terminualu.
	//WINDOW* window = initscr();
	
	initscr();
	
	getmaxyx(stdscr, rows, cols);	
	scrollok(stdscr, TRUE);
	printw("%i", rows);
	//idlok(window, TRUE);
	raw(); // zapnuti raw mode
	crmode(); // prepnuti terminalu
	
	keypad(stdscr, TRUE); // iniciliazace charakteru po stiksnutí

	noecho(); // vypnuti vypisovano charakteru
	
	// WELCOME
	//printw("%s", "## Welcome in Rapidshare Manager \n");
	//printw("%s", "rs#~/ ");
	
	linenum = 0;
	ypointer = 0;
	xpointer = 0;
	hpointer = 0;
	lpointer = 0;
	
	writeLine("## Welcome in Rapidshare Manager");
	start = "rs#~/ ";
	writeStart();
	
	sposition = 6;
	
}
/**
 * Pouze vypsání základních znaků.
 */ 
void Buffer::writeStart()
{
	write(start);
}
void Buffer::changeStart(string input)
{
	start = input;
	sposition = input.size();
}
/**
 * Funkce zmeni aktualni retezec za jiny a posune pointer.
 */
void Buffer::changeCurrent(string newCurrent)
{
	current = newCurrent;
	move(ypointer, sposition); // posuneme na zacatek
	clrtoeol(); // smazeme
	xpointer = sposition;
	write(current);
	move(ypointer, xpointer); // posuneme pointer
}
/**
 * Vypis jednoho radku do bufferu a zvetseni poctu line.
 */ 
void Buffer::writeLine(string input)
{	
	//printw("%s \n", input.c_str());
	mvprintw(ypointer, 0, "%s", input.c_str());
	wline = input;
	// posuneme pointer
	nextLine();
}
/**
 * Zvýsení pointeru o jedno. 
 */
void Buffer::nextLine()
{
	if(ypointer >= rows - 1)
	{
		// provedeme scroll up
		wscrl(stdscr, 1);
	}else{
		ypointer++;
	}
	//mvprintw(1, 45, "Debug:: %s", wline.c_str());
	lines.push_back(wline);
	linenum++;
	//write("ypointer: " + lexical_cast<string>(ypointer));
	// vynulujeme x pointer
	xpointer = 0;
	
}
/**
 * Vypis na soucasny radek, bez posunu.
 */ 
void Buffer::write(string input)
{		
	mvprintw(ypointer, xpointer, "%s", input.c_str());
	xpointer += input.size();
	
	/*for(int i = 0; i < input.size(); i++)
	{
		addch(input[i]);
	} */
}
/**
 * Scroll stranky o jeden radek up.
 */ 
void Buffer::scrollUp()
{
	//write(lexical_cast<string>(rows) + lexical_cast<string>(linenum));
	if(rows - 1 < linenum)
	{
		wscrl(stdscr, -1);
		int position;
		position = lines.size() - rows - lpointer; // spocteni soucasne pozice v linkach
		//mvprintw(1, 65, "Debug:: %i", position);		
		mvprintw(0, 0, "%s", lines[position].c_str());
		linenum--;
		lpointer++;
		
	}
	
}
/**
 * Scroll stranky o jeden radek down
 */ 
void Buffer::scrollDown()
{
	if(linenum < lines.size() - 1) // posledni radek neni jeste ulozen.
	{
		//mvprintw(1, 65, "Debug:: %i", linenum);	
		wscrl(stdscr, 1);
		
		mvprintw(rows - 1, 0, "%s", lines[linenum + 1].c_str());
		linenum++;
		lpointer--;
		
	}else{
		
		if(linenum == lines.size() - 1) // pokud jsem na posledni lince
		{
			wscrl(stdscr, 1);
			// pokusime se vypsat aktualni radek
			mvprintw(rows - 1, 0, "%s", (start + current).c_str());
			linenum++;	
			lpointer--;				
		}
	}
	
}
string Buffer::getCommand()
{
	current = "";
	temp.clear();
	xpointer = sposition;
	hpointer = 0;
	
	int key;
	key = getch();
	
	// live kontrola klaves
	while(key != 10) {
		switch(key){
			case KEY_END: 
				move(linenum, sposition + current.length()); 
			break;
			case KEY_RIGHT:
				// zkontrolujeme rozsah
				if((xpointer - sposition) < current.length())
				{
					xpointer++;
					move(ypointer, xpointer); 
				}
				
				break;
			case KEY_LEFT: 
				if(xpointer > sposition)
				{
					xpointer--;
					move(ypointer, xpointer); 
				}
			break;
			case KEY_UP:
				
				if(history.size() != 0 && hpointer == 0)
					temp = current; //ulozime si soucasne
				// pokud mame nejakou historii
				if(history.size() != 0 && hpointer != history.size())
				{	
					changeCurrent(history[history.size() - hpointer - 1]);
					hpointer++;
				}
				break;
			// PAGE-UP
			case 339: 
				scrollUp();
				break;
			// PAGE DOWN
			case 338: 
				scrollDown();
				break;	
			// TAB
			case 9:
				// tady bude autocomplete
				break;
			case KEY_BACKSPACE: 
				// pokud mame co mazat
				if(xpointer != sposition)
				{
					current.erase(xpointer - sposition - 1, 1); // smazani znaku
					xpointer--;			
					
					move(ypointer, sposition); // posuneme na zacatek
					clrtoeol(); // smazeme
					
					printw("%s", current.c_str()); // vypisime
					
					move(ypointer, xpointer); // posuneme pointer
				}

				break;
			case KEY_DOWN: 
				// pokud mame nejakou historii
				
				if(hpointer - 1 > 0)
				{			
					hpointer--;		
					changeCurrent(history[history.size() - hpointer]);

				}else{
					if(!temp.empty())
						changeCurrent(temp);				
				}
				break;
			default: 
				
				current.insert(xpointer - sposition,lexical_cast<string>((char)key));
				
				//printw("Unmatched - %d", key);
				//charnum++;
				//mvaddch(linenum, charnum, getch());
				move(ypointer, sposition);
				// posuneme na zacatek
				mvprintw(ypointer, sposition, "%s", current.c_str());		
				xpointer++;
				// posuneme kurzor
				move(ypointer, xpointer);
				//mvprintw(linenum, charnum, "%c", getch());
			break;
			}
			
			key = getch();
		}
		wline = start + current;
		nextLine();
		if(current.length())
			history.push_back(current); // ulozime do historie
		
		return current;
		
}

Buffer::~Buffer()
{

}