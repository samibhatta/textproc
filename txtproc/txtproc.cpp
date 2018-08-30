/* -----------------------------------------------------------------------------

FILE:              Source11.cpp

DESCRIPTION:        This is a command line driven text processing program .
The valid command line for the program
1.txtproc inputfile.txt [/C /H /L /O /R]
2.txtproc
3.txtproc /?

COMPILER:          visual studio 2013

MODIFICATION HISTORY:

Author                   Date                Version
---------------          ----------          --------------
Samikchhya Bhatta        2015-03-08          Version Number 11

----------------------------------------------------------------------------- */
# include <iostream> //for input output
#include <fstream>//for file operation
#include <new> // dynamic memory allocation
#include <string> // for strings
#include <cstring> // for strcmp
#include<cctype> // for to check isalpha,isupper and more

using namespace std;

#define SHOW_DEBUG_OUTPUT 0 
#define SHOW_LOCATION_OUTPUT 0

void help_option();
unsigned long read_input_file(char * filename);
void c_option(char* argv[], char test1);
void h_option(char* argv[]);
void cmd_arg(int argc, char* argv[]);
void l_option(char* argv[]);
string o_option(char* argv[]);
unsigned long rep_input_file(char * filename);
void r_option(char* argv[],string filename);

int main(int argc, char* argv[])//argc is the counter and argv=value
{

	char * test_enter = argv[0]; // assign pointer to the first argument-- executable file

	if (test_enter[7] == NULL && argv[1] == NULL)//checks if the user pressed enter key
	{
		help_option();
	}
	else
	{
		
		//cout << argc;// This function will check the cmd line arguments
		cmd_arg(argc, argv);
		
		// This function reads the input file into memory
		read_input_file(argv[1]);
	}
	return 0;
}
/* -----------------------------------------------------------------------------
FUNCTION:         cmd_arg(int argc, char*argv[])
DESCRIPTION:       checks if the first character of  argv[1] is / or not
and second character of argv[1] is one of the required characters or not.
RETURNS:           does not return anything
----------------------------------------------------------------------------- */

void cmd_arg(int argc, char* argv[])
{
#if SHOW_LOCATION_OUTPUT
	std::cout << "In handle_cmd_line_arguments()" << std::endl;
#endif
	// This loop looks at each cmd line paramter, one at a time
	string o_option_filename= string();
	for (int i = 2; i < argc; i++)
	{
		bool valid_cmd_line_arg = false;
		char * argument = argv[i]; // Copy the pointer from the array element
		if (argument[0] != '/')
		{
			// Describe the error
			std::cout << "The first character of \""
				<< argument << "\" is not the slash character (/)."
				<< std::endl;
			// Call the help function
			exit(1); // Exit the program
		}
		switch (argument[1])
		{
		case 'h':
		case 'H':
		
			h_option(argv);
			valid_cmd_line_arg = true;
			break;
		case 'c':
		case 'C':
			c_option(argv, argument[2]);
			valid_cmd_line_arg = true;
			break;

		case 'l':
		case 'L':
		
			l_option(argv);
			valid_cmd_line_arg = true;
			break;
		case 'o':
		case 'O':
			o_option_filename=o_option(argv);
			valid_cmd_line_arg = true;
			break;
		case 'r':
		case 'R':
			r_option(argv,o_option_filename);

			valid_cmd_line_arg = true;
			break;
		default:
			break;
		};

		if (valid_cmd_line_arg == false)
		{

			std::cout << "/" << argument[1]
				<< " is not a recognized option."
				<< std::endl;
			exit(2); // Exit the program
		}
	}

}
/* -----------------------------------------------------------------------------
FUNCTION:           read_input_file(char * filename)
DESCRIPTION:        checks if the file opens or not
if file opens--performs operation
if file doe not open--1. checks converts '/?' to string and checks for it to display help option.
if file does not open--2. display error message
RETURNS:           count
----------------------------------------------------------------------------- */

unsigned long read_input_file(char * filename)
{
#if SHOW_LOCATION_OUTPUT
	std::cout << "In read_input_file()" << std::endl;
#endif
	std::fstream fs; // fs is the file object

	fs.open(filename, std::fstream::in);
	char st[] = "/?";// make help option character array
	int help = 0;
	if (strcmp(st, filename) == 0)// strcmp compares two string string st with the filename
	{
		help = 1;
		help_option();
	}
	else
	{
		if (!fs)
		{
			// Explain the error
			std::cout << "Failed to open the input file." << std::endl;
			exit(3); // Exit the program
		}

		char c;
		unsigned long count = 0;
		while (fs.get(c))          // loop getting single characters
			count++;
#if SHOW_DEBUG_OUTPUT
		std::cout << "The byte  count for the input file is: " << count << std::endl;
#endif

		// Allocate space for the file
		char * mydata = new char[count]; // The input file will be stored here
		fs.close();
		
		fs.open(filename, std::fstream::in); // read only file
		if (!fs)
		{
			cout << "Failed to open the input file." << std::endl;
			exit(3); // Exit the program
		}
		for (unsigned int i = 0; i < count; i++)
		{
			fs.get(c); // Get a byte from the file
			mydata[i] = c; // Store the byte in our buffer (char array)
		}
		return count;
	}
}
/* -----------------------------------------------------------------------------
FUNCTION:           helpoption()
DESCRIPTION:        opens the help menu if the funtion is called
----------------------------------------------------------------------------- */
void help_option()
{
	ifstream helpfile;
	string letters;

	helpfile.open("help.txt", ios::in);// data will be read from file

	if (helpfile)
	{
		getline(helpfile, letters);
		while (helpfile)
		{
			cout << letters << endl;
			getline(helpfile, letters);
		}
	}
	else
	{
		cout << "Error!! opening file!!" << endl;

	}
	helpfile.close();

}
/* -----------------------------------------------------------------------------
FUNCTION:           c_option()
DESCRIPTION:        opens the input file and checks for the character after '/c' argument and adds total
and writes it to report.txt
----------------------------------------------------------------------------- */
void c_option(char* argv[], char test1)
{
	fstream inputfile;
	char ch;

	inputfile.open(argv[1], std::fstream::in);
	if (inputfile)
	{
		inputfile.get(ch);// get character from a file
	}
	int count = 0;
	while (inputfile)//test if textproc inputfile.txt /c(and any character entered after c)
	{
		//cout << ch;
		if (ch == test1)
			count++;//add total
		inputfile.get(ch);


	}
	ofstream reportfile;

	reportfile.open("report1.txt", ios::out);
	reportfile << "The total count of character ";
	reportfile << test1;// write result to report.txt
	reportfile << " in inputfile.txt is : ";
	reportfile << count;
	reportfile << endl;
	inputfile.close();
	reportfile.close();
}
/* -----------------------------------------------------------------------------
FUNCTION:           h_option()
DESCRIPTION:        read the file and creates histogram bar for the character..maximum star=80
----------------------------------------------------------------------------- */
void h_option(char* argv[])
{
	int TOTAL_STAR = 80;//maximum no. of stars a histogram bar can have
	//	int total_count;
	fstream inputfile;
	char ch;

	int count_lc_aplha = 0;
	int count_uc_aplha = 0;
	int count_number = 0;
	int count_punct = 0;
	int count_whitespace = 0;
	int count_other_c = 0;

	inputfile.open(argv[1], std::fstream::in);

	if (inputfile)
	{
		inputfile.get(ch);
	}
	int count = 0;
	while (inputfile)//test if textproc inputfile.txt /c(and any character entered after c)
	{
		if (islower(ch)){// check for lowercase alphabet
			count_lc_aplha++;

		}
		else if (isupper(ch)){ //check for uppercase alphabet
			count_uc_aplha++;
		}
		else if (isdigit(ch)){ // check for numbers
			count_number++;
		}
		else if (isspace(ch)){ // check for space
			count_whitespace++;
		}
		else if (ispunct(ch)){ // check for punctutions
			count_punct++;
		}
		else
			count_other_c++;
		inputfile.get(ch);


	}
	cout << endl;
	cout << "HISTOGRAM" << endl;
	cout << "Lowercase character:\t";

	for (int i = 0; i< count_lc_aplha && i <= TOTAL_STAR; i++)
	{
		cout << "*";
	}
	cout << endl;
	cout << "Upper case character:\t";

	for (int i = 0; i<count_uc_aplha && i<TOTAL_STAR; i++)
	{
		cout << "*";
	}
	cout << endl;
	cout << "Number character:\t";

	for (int i = 0; i<count_number && i<TOTAL_STAR; i++)
	{
		cout << "*";
	}
	cout << endl;
	cout << "Whitespace character:\t";

	for (int i = 0; i<count_whitespace && i<TOTAL_STAR; i++){
		cout << "*";
	}
	cout << endl;
	cout << "Punctuation character:\t";
	for (int i = 0; i<count_punct && i<TOTAL_STAR; i++)
	{
		cout << "*";
	}
	cout << endl;
	cout << "Other character:\t";

	for (int i = 0; i<count_other_c && i<TOTAL_STAR; i++){
		cout << "*";
	}
	cout << endl;
	inputfile.close();
	cout << endl;
}
/* -----------------------------------------------------------------------------
FUNCTION:           l_option()
DESCRIPTION:        combines the character typed by the user to string and checks for the word in the inputfile.txt
writes the total count of the appearance of the word into report1.txt
----------------------------------------------------------------------------- */

void l_option(char* argv[])
{
	ifstream inputfile;
	ofstream reportfile;
	string ch, string_combo = string();


	char * str = argv[2];//assign pointer 
	size_t length = strlen(argv[2]);//size_t 
	//char * mydata = new char[length];
	reportfile.open("report.txt");//write the result to report.txt
	for (int i = 2; i < (int)length; i++)
	{
		string_combo += str[i];
	}
	//string_combo = string() + str[2] + str[3] + str[4] + str[5] + str[6];//combine characters typed by user to single string

	inputfile.open(argv[1], std::fstream::in);

	if (inputfile)
	{
		getline(inputfile, ch);//first line 
	}
	int count = 0;
	int word_counter = 0;
	while (inputfile)// test for characters after /l argument
	{
		int temp_counter = 0;

		int i = 0;

		while (ch[i] != NULL)
		{
			if (ch[i] == string_combo[temp_counter])
			{

				if (temp_counter + 1 == (int)length - 2)//typecasting
				{
					word_counter++;

					temp_counter = 0;

				}
				else
				{
					temp_counter++;
				}
			}
			else{

				temp_counter = 0;

			}
			i++;
		}

		//if (string_combo == ch)
		//count++;

		getline(inputfile, ch);

	}


	reportfile << "The total count of word ";
	reportfile << string_combo;
	reportfile << " ' in inputfile.txt is : ";
	reportfile << word_counter;
	reportfile << endl;


	inputfile.close();
	reportfile.close();
}
/* -----------------------------------------------------------------------------
FUNCTION:           0_option()
DESCRIPTION:        creates a file after /o
----------------------------------------------------------------------------- */
string o_option(char* argv[])
{
	ofstream reportfile;
	ifstream inputfile;
	string ch, string_combo = string();


	char * str = argv[2];//assign pointer 
	size_t length = strlen(argv[2]);//size_t 
	//char * mydata = new char[length];
	//write the result to report.txt
	for (int i = 2; i < (int)length; i++)
	{
		string_combo += str[i];
	}

	reportfile.open(string_combo);
	inputfile.open("inputfile.txt");
	getline(inputfile, ch);
	while (inputfile){
		reportfile << ch;
		getline(inputfile, ch);
	}
	reportfile.close();
	inputfile.close();
	return string_combo;
}

void r_option(char* argv[],string filename)
{
	ofstream reportfile;
	ifstream inputfile;
	string ch, string_combo = string();
	cout << filename;

	char * str = argv[2];//assign pointer 
	size_t length = strlen(argv[2]);//size_t 
	//char * mydata = new char[length];
	//write the result to report.txt
	for (int i = 2; i < (int)length; i++)
	{
		string_combo += str[i];
	}

	reportfile.open(string_combo);
	inputfile.open("inputfile.txt");
	getline(inputfile, ch);
	while (inputfile){
		reportfile << ch;
		getline(inputfile, ch);
	}
	reportfile.close();
	inputfile.close();
}