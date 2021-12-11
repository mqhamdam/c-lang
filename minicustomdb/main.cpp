#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include <Windows.h>


using namespace std;

 // # Go to X , Y console
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
// # Get current X COORD
int wherex()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(
		GetStdHandle(STD_OUTPUT_HANDLE),
		&csbi
	))
		return -1;
	return csbi.dwCursorPosition.X;
}
// # Get current Y COORD
int wherey()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(
		GetStdHandle(STD_OUTPUT_HANDLE),
		&csbi
	))
		return -1;
	return csbi.dwCursorPosition.Y;
}

// # Init Student Struct model
typedef struct StudentModel
{
	int ban;
	int num;
	char name[15];
	int sub1;  // °ú¸ñ1
	int sub2;
	int sub3;
	long sum;
	int brank; // ¹Ý¼øÀ§
	long rank;   // ÀüÃ¼¼øÀ§
} StudentModel;

// # Exit function to terminate program
int _exitProgram() {
	cout << "\n\nExit after\n>> ";
	for (int i = 5; i > 0; i--) {
		Sleep(1000);
		cout << i << "\t";
	}
	 exit(0);
}

 int _getSize() {
	fstream motd("students.dat", std::ios::binary | std::ios::in | std::ios::ate);
	fstream::pos_type size;
	if (motd) {
		size = motd.tellg();

	}
	else {

	}

	motd.close();
	return size / 48; // 48(bytes) is size of 1 struct.
}

// # Swap function for bubble sort
void swap(StudentModel* xp, StudentModel* yp)
{
	StudentModel temp = *xp;
	*xp = *yp;
	*yp = temp;
}

// # bubble Sort By default sorts by students sum of subjects
void bubbleSort(StudentModel arr[], int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++)

		for (j = 0; j < n - i - 1; j++)
			if (arr[j].sum < arr[j + 1].sum)
				swap(&arr[j], &arr[j + 1]);
}


// # Update Rank (runs everyTime if change occures on the documents
void updateRank() {
	
	  
	const int count = _getSize();
	
	 
	ifstream fin("students.dat", ios::in | ios::binary);
	ofstream fout("tmp.dat", ios::out | ios::binary);
	
	StudentModel* st = new StudentModel[count];
	for (int i = 0; i < count; i++) {

	fin.read((char*)&st[i], 48);
	}
	
	//update rank
	bubbleSort(st, count);
	
	//write to file
	for (int i = 0; i < count; i++) {
		st[i].rank = i + 1;
	fout.write((char*)&st[i], 48);

	}

	fin.close();
	fout.close();

	remove("students.dat");
	rename("tmp.dat", "students.dat");
	delete[] st;
}

// # Build banner for main pages
void _buildBanner(string title ) {
	for (int i = 0; i < 30; i++) {
		cout << "*";
	}
	cout << endl;
	cout << " ->\t" << title <<endl;
	for (int i = 0; i < 30; i++) {
		cout << "*";
	}
	cout << endl;
}

// # Function for inserting data
void _pushData(StudentModel st) {
	ofstream fout;
	
	st.sum = st.sub1 + st.sub2 + st.sub2;
	fout.open("students.dat", ios::app | ios::binary);
	
	
	fout.write((char*)&st, sizeof(st));

	fout.close();
	updateRank();
	cout << "Data Saved Successfully!\n";
}

// # Build Insert Data Page 
int _buildInsertPage() {
	int _status = 1;
	StudentModel st;
	int i,j;
	while (_status != -1) {
		system("CLS");
	_buildBanner("Insert Data");
		cout << "Type 1 to add data, type 2 to go back to main page and type 0 to exit program"<<endl;
		cin >> _status;
		switch (_status) {
		case 1 :
		do {
			system("CLS");
		cout << "Please Enter the following Data to insert it to the Database. (Name, Student Number,StudentGroup, Subjects(3))\n";
		cout << "Student Number >> ";
		cin >> st.num;
		cout << "Name >>";
		cin >> st.name;
		cout << "StudentGroup >> ";
		cin >> st.ban;
		cout << "Points for Subject 1 >> ";
		cin >> st.sub1;
		cout << "Points for Subject 2 >> ";
		cin >> st.sub2;
		cout << "Points for Subject 3 >> ";
		cin >> st.sub3;
		cout << "\n\n";
		cout << "Please type 1 to push data to the database, type 2 to discard changes \n";
		cin >> i;
		if (i == 1) {
			_pushData(st);
		}
		else if(i==2) {
			cout << "Changes discarded\n";
		} 
		cout << "Type 1 to insert new Data, Type 2 to go back";
		cin >> j;
		} while (j!=2);
			break;
		case 2:
			_status = -1;
			break;
		case 0:
			_exitProgram();
			break;

		}
	}
	return -1;
}

// # Print Struct data
void _printStruct(StudentModel st[], int size) {
	cout << "StName\t\tStID\t\tGroup\tSub1\tSub2\tSub3\tSum\tRank\n\n";
	for (int i = 0; i < size; i++) {
		cout << st[i].name << "    "<< '\t';
	cout << st[i].num << "    " << '\t';
	cout << st[i].ban << '\t';
	cout << st[i].sub1 << '\t';
	cout << st[i].sub2 << '\t';
	cout << st[i].sub3 << '\t';
	cout << st[i].sum << '\t';
	cout << st[i].rank << '\n';
	}
	cout << "\n\n";
}

// # Check if student exist on Database
bool _isExist(int id,bool printData = false) {
	int count = _getSize();
	ifstream fin("students.dat",ios::binary|ios::in);
	StudentModel* st = new StudentModel[count];

	for (int i = 0; i < count; i++) {
		fin.read((char*)&st[i], 48);
	}

	bool found = false;
	for (int i = 0; i < count; i++) {
		if (st[i].num == id) {
			found =true;
			cout << "FOUND\n>> "  << endl;
			if (printData) {
				//cout << "Name\tStudentID\tGroup\tSub1\tSub2\tSub3\tSum\tRank\n";
				cout << "Name\tStID\tGroup\tSub1\tSub2\tSub3\tSum\tRank\n";

				cout << st[i].name << '\t';
				cout << st[i].num << '\t';
				cout << st[i].ban << '\t';
				cout << st[i].sub1 << '\t';
				cout << st[i].sub2 << '\t';
				cout << st[i].sub3 << '\t';
				cout << st[i].sum << '\t';
				cout << st[i].rank << '\n';
			}
			break;
		}
	}
	
	delete[]st;

	fin.close();
	return found;
}


// # Function to delete Data from the DB by given ID
void _deleteData(int id) {
	int count = _getSize();

	ifstream fin("students.dat", ios::binary | ios::in);
	ofstream fout("tmp.dat", ios::binary | ios::out);

	StudentModel* st = new StudentModel[count];
	StudentModel* st2 = new StudentModel[count-1];
	for (int i = 0; i < count; i++) {

		fin.read((char*)&st[i], 48);
	}
	
	// if st size is 7, st2 size is 6  
	for (int i = 0; i < count - 1; i++) {
		if (st[i].num != id) {
			st2[i] = st[i];
		}
		else {
			st2[i] = st[count - 1];
		}
	}

	
	for (int i = 0; i < count-1; i++) {
		fout.write((char*)&st2[i], 48);

	}
	
	fin.close();
	fout.close();
	remove("students.dat");
	rename("tmp.dat", "students.dat");
	updateRank();
	delete[]st;
	delete[]st2;
}

// # Build Update Data Page
int _buildUpdatePage() {
	int _status = 1;
	StudentModel st;
	int searchId;
	int i, j;
	while (_status != -1) {
		system("CLS");
		_buildBanner("Update Data");
		cout << "Type 1 to search, type 2 to go back and type 0 to exit program" << endl;
		cin >> _status;
		switch (_status) {
		case 1:
			do {
				system("CLS");
				cout << "Please enter Student ID searching for\n>> ";
				cin >> searchId;
				if (_isExist(searchId,true)) {
					cout << "Enter following data do update data\n";
					cout << "Student Number >> ";
					cin >> st.num;
					cout << "Name >>";
					cin >> st.name;
					cout << "StudentGroup >> ";
					cin >> st.ban;
					cout << "Points for Subject 1 >> ";
					cin >> st.sub1;
					cout << "Points for Subject 2 >> ";
					cin >> st.sub2;
					cout << "Points for Subject 3 >> ";
					cin >> st.sub3;
					cout << "\n\n";
					cout << "* -> Please enter 1 to confirm update or 2 to discard changes\n";
					cin >> i;
					if (i == 1) {
					_deleteData(searchId);
					_pushData(st);
					}
					else if(i == 2){
						cout << "Changes discarded\n";
					}
				}
				else {
					cout << "Could not find student data by given id" << endl;
				}
					cout << "Please enter 1 to update other Student data or 2 to go back\n";
					cin >> j;
				
			} while (j != 2);
			break; 
		case 2:
			_status = -1;
			break;
		case 0:
			_exitProgram();
			break;
		}
	}
	return -1;
}
 // # Function for search by <ID> option
int _searchById() {
	int searchId;
	int _status = 1;
	
	
	do {
		system("CLS");
		cout << "Enter Id of Student\n>> ";
		cin >> searchId;
		if (_isExist(searchId,true)) {
		}
		else {
			cout << "\nCould not find student by given ID" << endl;
		}
		cout << "Type 1 to search again, type 2 to go back to main menu, type 0 to exit program.\n >> ";
		cin >> _status;
		if (_status == 0) _exitProgram();
	} while (_status != 2);
	return -1;
}

// # Returns All Data from DB
int _searchByAll() {
	int count;
	int _status = 1;
	
	do {
		system("CLS");
			count = _getSize();
			if (count != 0) {
			cout << "FOUND DATA >> " << count << endl;
			ifstream fin("students.dat",ios::binary|ios::in);
			StudentModel* st = new StudentModel[count];
			for (int i = 0; i < count; i++) {

				fin.read((char*)&st[i], 48);
			}
			
			//cout << "StudentName\tStudentID\tGroup\tSub1\tSub2\tSub3\tSum\tRank\n";
			_printStruct(st, count);
			
			fin.close();
			}
			else {
				cout << "No Data found :(\n";
			}
		cout << "Type 1 to search again, type 2 to go back to main menu, type 0 to exit program.\n >> ";
		cin >> _status;
		if (_status == 0) _exitProgram();
	} while (_status != 2);
	return -1;
}

// # Build Search Data Page
int _buildSearchPage() {
	int _status = 1;

	
	int i, j;
	while (_status != -1) {
		system("CLS");
		_buildBanner("Search Student Data");
		cout << "Type 1 to search, type 2 to go back and type 0 to exit program" << endl;
		cin >> _status;
		switch (_status) {
		case 1:
			do {
				system("CLS");
				cout << "Search by\n(1) ID\n(2) All\n>> * Type 4 to go back\n>> ";
				cin >> i;
				switch (i) {
				case 1: 
					_searchById();
					break;
				
				case 2:
					_searchByAll();
					break;
				}
				
			} while (i != 4);
			break;
		case 2:
			_status = -1;
			break;
		case 0:
			_exitProgram();
			break;
		}
	}
	return -1;
}

// # Build Delete Data Page
int _buildDeletePage() {
	int _status = 1;
	
	int searchStr;
	int i = 2, j;
	while (_status != -1) {
		system("CLS");
		_buildBanner("Delete Data Page");
		cout << "Type 1 to search to delete, type 2 to go back and type 0 to exit program" << endl;
		cin >> _status;
		switch (_status) {
		case 1:
			do {
				system("CLS");
				cout << "Type student ID\n>> ";
				cin >> searchStr;
				if (_isExist(searchStr, true)) {
					cout << "Type 1 to delete given student data, type 2 to search again,type 3 to go back, type 0 to exit program\n>> ";
					cin >> j;
					if (j == 1) {
						_deleteData(searchStr);
						cout << "\nData deleted Successfully! \n";
					}
					else if(j == 3){
						i = 4;

					}
					
					else if (j == 0) {
						_exitProgram();
					} 
				}
				else {
					cout << "Could not find Data by given ID\n";
				}
				cout << "Type 2 to search again, type 3 to go back, type 0 to exit program\n>>";
				cin >> j;
				if (j == 3) {
					i = 4;

				}
				else if (j == 0) {
					_exitProgram();
				}

			} while (i != 4);
			break;
		case 2:
			_status = -1;
			break;
		case 0:
			_exitProgram();
			break;
		}
	}
	return -1;
}

// # Build Main Menu
int _buildMenu() {
	int _status = 0;
	string errMsg = "";

	do {
		system("CLS");
	_buildBanner("Main Menu");
	cout << "\t[1] ÀÚ·áÀÔ·Â" << endl;
	cout << "\t[2] ÀÚ·á¼öÁ¤" << endl;
	cout << "\t[3] ÀÚ·á°Ë»ö" << endl;
	cout << "\t[4] ÀÚ·á»èÁ¦" << endl << endl;
	cout << "\t[0] ÀÛ¾÷Á¾·á" << endl << endl<<endl;
		cout << "ÀÔ·ÂÇÑ ÀÛ¾÷ - [";
		int x = wherex();
		int y = wherey();
		cout << " ]\n\n" << errMsg;
		gotoxy(x, y);
		cin >> _status;
		switch (_status) {
		case 1:
			system("CLS");
			errMsg = "";
			_buildInsertPage();
			break;
		case 2:
			system("CLS");
			errMsg = "";
			_buildUpdatePage();
			break;
		case 3:
			system("CLS");
			errMsg = "";
			_buildSearchPage();
			break;
		case 4:
			system("CLS");
			errMsg = "";
			_buildDeletePage();
		case -1:
			system("CLS");
			errMsg = "";
			break;
		case 0:
			_exitProgram();
			break;
		default:
			errMsg = "input is incorrect.";
			break;
		}
	} while (_status);
		return _status;
}



// # Entry Program
int main(void) {
	
	
	int _programStatus  = 1;
	
	
	while (_programStatus) {
	_programStatus =_buildMenu();
}
	
	return 0;
}
