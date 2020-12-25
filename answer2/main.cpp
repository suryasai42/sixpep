#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <algorithm>


using namespace std;

// Store the student information in an array
string values[4];
void add();
string idRand();
void update();
void delete1(string n);
void view();

// Creating structure student which contains student id, name, age and city;
struct student
{
	string id, name, city;
	int age;
};

int main()
{
	int n;
	string m;

	cout << "Student Management System" << endl;
lable1:
	cout << endl << "1. Add 2. Update 3. Delete 4. View 5. Save & Quit" << endl;                   // To take user input to perform appropriate action;
	cout << "Player input is :";
	cin >> n;
	if (std::cin.fail()) // To handle exception if user enters alpahabets instead of integers
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	switch (n)     // To perform the task asked by the user;
	{
	case 1:
		add();     // Adds the data of a student to the file;
		break;
	case 2:
		update();  // Updates the existing student records in the file;
		break;
	case 3:
		cout << "Enter the Id to delete :";
		cin >> m;
		delete1(m);   // Deletes a students record by taking the Id as reference;
		break;
	case 4:
		view();   // To view the data in the file using query;
		break;
	case 5:
	  // Data is saved in file after each operation. Need not explixitly save it before termination.
		return 0;
		break;
	default:
		cout << "Invalid input, Give a valid input" << endl;
		break;
	}

	goto lable1;

	return 0;
}
bool checkIfIDExists(string id)
{
	student s;
	ifstream getdata("student.txt");
	while (getdata >> s.id >> s.name >> s.age >> s.city)               // get the record from the file;
	{
		if (id == s.id)                    // if generated random id is equal the id of the record
		{
			return true;
		}

	}
	return false;
}
void add()
{
	string line, f1;
	student s;
	cout << endl << "Add new student details [name,age,city] separated by a comma, ex: vamsi,22,kakinada" << endl;
	cin >> line;                                    // To get the details from the user in the form of string;
	stringstream ss(line);

	getline(ss, s.name, ',');       // To store the data in the string in different variables;
	getline(ss, f1, ',');
	getline(ss, s.city, ',');
	if (s.name.empty() || f1.empty() || s.city.empty())          // To check if the input format is correct;
	{
		cout << "Incorrect format, try again" << endl;
		return;
	}
	s.age = stoi(f1);            // Converting the age to integer type;

	s.id = idRand();                  // To create a random 6 lettered alpha numeric number;

	while (checkIfIDExists(s.id))
	{
		s.id = idRand();
	}
	ofstream newstd("student.txt", ios::app);                          // To open(or create) a file student.txt;
	newstd << s.id << ' ' << s.name << ' ' << s.age << ' ' << s.city << endl;              // writes the data into the file;
	newstd.close();

	cout << "Added successfully with a new Id " << s.id << endl;
}


string idRand()                // To create a random 6 lettered alpha numeric number;
{
	int a1, a2, a3, a4;
	string b1, b2, b3, b4, b5, b6;
	srand(time(0));                       // To generate a random number;
	a1 = rand() % 26 + 97;
	b1 = char(a1);

	stringstream a;
	// srand(time(0));
	a2 = (rand() % 900) + 100;
	a << a2;
	b2 = a.str();

	// srand(time(0));
	a3 = rand() % 26 + 97;
	b3 = char(a3);

	stringstream m;
	//  srand(time(0));
	a4 = rand() % 10;
	m << a4;
	b4 = m.str();

	b5 = b1 + b2 + b3 + b4;                                                                // Concatenating the strings together to form ihe id;
	return b5;

}

// Update() updates the existing student record
// Required Inputs :
// Student ID : Record of the student which matches the user given Id will be updated.
// If no student record is found with the Id specified by user, no records will be updates
// Name, age, City : The values provided by the user are updated.
void update()
{
	student s;
	string line, nname, nf1, ncity, nid;
	int nage, k = 0;
	cout << "To update the details input in format [id,name,age,city] separated by comma: " << endl;
	cin >> line;

	stringstream ss(line);

	getline(ss, nid, ',');                     // Assigning the newly obtained data to variables;
	getline(ss, nname, ',');
	getline(ss, nf1, ',');
	getline(ss, ncity, ',');
	if (nf1.empty())               // if nfi is empty then there is no change in age, so, nage is empty;
	{
		goto lable2;
	}

	nage = stoi(nf1);

lable2:

	ifstream getdata("student.txt");




	while (getdata >> s.id >> s.name >> s.age >> s.city)
	{
		if (nid == s.id)                              // Comparing user input id and student id from the file
		{                                             // If the id match and new details are not empty
			k++;                                      // then replace old data with new data;
			if (!nname.empty()) { s.name = nname; }
			if (!nf1.empty()) { s.age = nage; }
			if (!ncity.empty()) { s.city = ncity; }

		    ofstream newstd("newfile.txt", ios::app);                                      // opening newfile.txt file in write mode;
			newstd << s.id << ' ' << s.name << ' ' << s.age << ' ' << s.city << endl;      // Adding data to the file;
			newstd.close();

		}
		if (s.id != nid)              // If id do not match then add the old data to the newfile.txt without any change;
		{

            ofstream givedata("newfile.txt", ios::app);
			givedata << s.id << ' ' << s.name << ' ' << s.age << ' ' << s.city << endl;
			givedata.close();
		}

	}
	getdata.close();
	if(k == 0)
	{
		cout << "Given Id do not exist. Try again." << endl;          // k==0; that means the given id don't match with any existing id;
	}
	else
		cout << "Data updated" << endl;
	remove("student.txt");                      // Removing student.txt file;
	rename("newfile.txt", "student.txt");                   // Renaming newfile.txt to student.txt

	getdata.close();

}

// Delete the existing record;
// Functional Argument : n - Id of the record that is to be deleted.
void delete1(string n)
{
	student s;
	ifstream getdata("student.txt");                                                     // Open the student.txt file in read mode;
	bool recordFound = false;
	while (getdata >> s.id >> s.name >> s.age >> s.city)                                 // get the record from the file;
	{
		if (n != s.id)                                                                   // if given input id is equal the id of the record
		{                                                                                // then do not copy it to newfile.txt;
			ofstream givedata("newfile.txt", ios::app);
			givedata << s.id << ' ' << s.name << ' ' << s.age << ' ' << s.city << endl;
			givedata.close();
		}
		else
			recordFound = true;
	}
	getdata.close();


	remove("student.txt");                               // Remove student.txt file;
	rename("newfile.txt", "student.txt");            // Rename newfile.txt to student.txt
	if (recordFound)
	{
		cout << "Successfully deleted the student record with Id : " << n << endl;
	}
	else
	{
		cout << "No student record found with id : " << n << " . Please check the Id" << endl;
	}
}

// Compares the strings by ignoring casesensitve
int checkEqual(string str1, string str2)
{
	transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
	transform(str2.begin(), str2.end(), str2.begin(), ::tolower);
	return str1.compare(str2);
}

// Check if the string str1 starts with string str2
bool findString(string str1, string str2)
{
	transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
	transform(str2.begin(), str2.end(), str2.begin(), ::tolower);
	return (str1.rfind(str2, 0) == 0);
}

// Compute evaluates the query specified by user
bool compute(string Condition)
{
	int value = 0;
	int argumentIndex = -1;
	// Identify the column(id/name/age/city) specified by user in query
	if (findString(Condition ,"Id"))
		argumentIndex = 0;
	else if (findString(Condition, "name"))
		argumentIndex = 1;
	else if (findString(Condition, "age"))
		argumentIndex = 2;
	else if (findString(Condition, "city"))
		argumentIndex = 3;
	else
	{
		// Throw an exception if user input is invalid
		cout << "User specified column is not valid. Please check the query" << endl;
		exception ex;
		throw (ex);
	}

	// Identify the operator in the condition and evaluate accordingly
	// Evaluates = operator
	int pos = Condition.find('=');
	if (pos > 0)
	{
		string value = Condition.substr(pos + 1);
		if (checkEqual(values[argumentIndex], value) == 0)
			return true;
		return false;
	}
	// Evaluates < operator
	pos = Condition.find('<');
	if (pos > 0)
	{
		if (checkEqual(values[argumentIndex], Condition.substr(pos + 1)) < 0)
			return true;
		return false;
	}
	// Evaluates > operator
	pos = Condition.find('>');
	if (pos > 0)
	{
		string value = Condition.substr(pos + 1);
		if (checkEqual(values[argumentIndex], value) > 0)
			return true;
		return false;
	}
	return false;

}

// Validates the user specified condition on each student record
// Technique used : Divide and Merge
// Split the condtion to simpler conditions recursively by splitting at || and &&.
// Evaluate each simpler condition and merge the result accordingly
bool Evaluate(string userInput)
{

	int index = userInput.find("||");
	if (index > 0)
	{
		// Split the condition to sub conditions if || is found and merge the result recursively
		return(Evaluate(userInput.substr(0, index)) || Evaluate(userInput.substr(index + 2)));
	}
	else
	{
		// if || is not found, Split the condition to sub conditions if && is found
		int index = userInput.find("&&");
		if (index > 0)
		{
			// Merge the result
			return(Evaluate(userInput.substr(0, index)) && Evaluate(userInput.substr(index + 2)));
		}
		else
		{
			// Evaluate simpler condition
			return compute(userInput);
		}
	}
	return false;
}



void view()
{
	cout << "To view single enrty, enter Id ex:a123b6. " << endl;
	cout << "To query, combine with operators >,<.=,&&" << endl;
	cout << "Ex: age>20 , age>20&&city=hyderabad" << endl;
	cout << "(Note : Do not give space in between the query.)" << endl;

	string line;

	cin >> line;

	int count = 0;

	ifstream getdata("student.txt");
	try {
		// Fetch each record from student.txt file
		while (getdata >> values[0] >> values[1] >> values[2] >> values[3])
		{
			// For each student record evaluate to check if the record satisfies the query.
			if (Evaluate(line))
			{
				count++;
				if (count == 1)
					cout << endl;
				cout << values[0] << " " << values[1] << " " << values[2] << " " << values[3] << endl;
			}

		}
	}
	catch(exception ex)
	{
		count = 1; // Caught exception due to invalid input from user.
	}
	getdata.close();
	if (count == 0)
		cout << "No record satisfied the user conditions" << endl; // Notify user that no records are retrieved

}

