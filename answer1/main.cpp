#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <fstream>
#include <cmath>
#include <algorithm>

using namespace std;

int arraySize;

int newWord(string b[], string a, int  score);

int main()
{
	int n, score = 0;
	int a1 = NULL;

	string a;
	string b[] = { "Mexico","Sixpep","Vamsi","Hello","Accept","Abode","Active","Time","Start","Finish" };  //Array that stores the words;

	int high_score;

	arraySize = sizeof(b)/sizeof(b[0]);           //Finding number of words present in array 'b';
	//cout << arraySize;

	ofstream file;
	ifstream obj;

	obj.open("hs.txt");                    //open the file in reading mode;
	obj >> a1;
	if (a1 == NULL) { high_score = 0; }              //   check if the file is empty.
	high_score = a1;                               //  if yes,then high_score = 0;
	obj.close();


	cout << "Test your typing speed :" << endl;
lable1:

	cout << " 1. New Word 2. Score 3. High Score 4. Save & Quit" << endl;       // Taking user input to decide the action to be done;
	cout << "Players input: ";

	cin >> n;

	if (std::cin.fail())     // To handle exception if user enters alphabets instead of integers                                                                             // To clear cin and ignore the input if an
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	switch (n)                     // To perform the appropriate action asked by the user;
		{

		case 1:
			score = newWord(b, a, score);            // Display's the word to be typed and calculate
			break;                                   // time taken to type and the score of the user;
     	case 2:
			cout << score << endl<<endl;            // Display the present score of the user;
			break;
		case 3:
			if (score > high_score) { high_score = score; }    //Display the highest score;
			cout << high_score << endl<<endl;
			break;
		case 4:
			file.open("hs.txt");              // Saving the data to the file and exiting the program;
			if (score > high_score) { file << score; }
			else { file << high_score; }
			file.close();
			cout << "Saving score and exiting the application."<<endl<<endl;
			return 0;
		default:
			cout << "Enter valid input" << endl<<endl;

		}
	goto lable1;

	return 0;
}



int newWord(string b[], string a, int  score)
{
	time_t start, finish;
	srand(time(0));                                                                                             // To produce a random number
	int y = rand() % arraySize;                                                                                 // To get the index of the word to be typed;
	cout << "Your new word is \" " << b[y] << " \" type now :" << endl;
	time(&start);                                                                                               // Present time i.e. time before typing started;
	cin >> a;
	time(&finish);                                                                                              // Time after typing is completed;
	int x = ceil(difftime(finish, start));                                                                      // Time taken to type in ceiling form;
	if (b[y] == a)
	{
		cout << "Time taken to type " << b[y] << " is " << x << " seconds." << endl;
		switch (x)                                                                                              // To assign the score appropriate for the
		{                                                                                                       // time taken to type the word;
		case 0:
		case 1:
		case 2:
			score += 2;
			cout << "You scored 2 points and your total score is " << score << endl<<endl;
			break;
        case 3:
            score += 1;
            cout << "You scored 1 points and your total score is " << score << endl<<endl;
            break;
		default:

			cout << "You scored 0 points and your total score is " << score << endl<<endl;
		}


	}
	else                                                                                                         // To give negative score for typing wrong word;
	{
		cout << "Incorrect, you loose 1 point"<<endl;
		score -= 1;
		cout << "Total score is :" << score<<endl<<endl;
	}
	return score;
}

