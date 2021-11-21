#include<fstream>
#include<iostream>
#include<iomanip>
#include<string>
//#include<cstring>
//#include<cstdlib>
#include<regex>
using namespace std;

namespace NameRecord
{
	struct node
	{
		char name[100];
		char mobile_no[20];
		char email_id[100];
		node *next;
		node *pre;
	};

    node *head_ptr;
    node *tail_ptr;
    node *current_ptr;
    char pause;

    class Record
    {
        public:
                void userChoice(int choice);
                void insertRecord();
                void insertNode(node *new_ptr);
                void insertNodeHead(node *new_ptr);
                void insertNodeEnd(node *new_ptr);
                void showList();
                void searchByName();
                void saveFile();
                void loadFile();
                void deleteRecord();
                void deleteNodeHead();
                void deleteNodeEnd();
                void deleteNodeMiddle();
                int verifyDelete();
                void deleteNode();
                void deleteList();
                void modifyRecord();
                void backupReset();
                void restoreData();
    };
}

using namespace NameRecord;

bool validateName(char name[100])
{
    string toCheck = name;

    for (int i = 0; i < toCheck.length(); i++)
    {
        if (!isalpha(toCheck[i]) && !isspace(toCheck[i]))
        return false;

    }
    return true;
}

bool validateMobileNumber(char toCheck[20])
{
    int count = 1;

    for (int i = 0; count <= 10 ; i++)
    {
        if (isdigit(toCheck[i]) == false)
        return false;

        count++;
    }
    return true;
}

bool validateEmailId(char toCheck[100]) {

    const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
   // bool correct = false;
    string data = toCheck;

   // try to match the string with the regular expression
    if(regex_match(data, pattern))
        return true;
    else
        return false;

   // return correct;
}

int main()
{
	Record myrecord;

	cout << "\n\n\n\n\t\t\t======================================================\n\n" ;
    cout << "\t\t\t\t     Welcome to use the phone book \n\n" ;
    cout << "\t\t\t======================================================" << endl ;
	cout<< " \n\n " ;
    cout<< "\t\t\t Display Menu( Press Enter ) : " ;

	cin.get(pause);
	system("cls");

	int choice;

	head_ptr=NULL;
	tail_ptr=NULL;

	myrecord.loadFile();

	do
	{
        cout << "\n\n\t\t===============\n" ;
        cout << "\t\t     Menu \n" ;
        cout << "\t\t===============" << endl ;

        cout << "\n\t\t 1. Add Record" << endl ;
        cout << "\t\t 2. Show All Records" << endl ;
        cout << "\t\t 3. Search Records By Name" << endl ;
        cout << "\t\t 4. Delete Record" << endl ;
        cout << "\t\t 5. Modify Record" << endl ;
        cout << "\t\t 6. Backup and Reset" << endl ;
        cout << "\t\t 7. Restore Data" << endl ;
        cout << "\t\t 8. Quit The Program" << endl ;
        cout << "\n\t\t Enter your choice : ";
        cin >> choice;
        myrecord.userChoice(choice);

	}while(choice != 8);

	return 0;
}

void Record::userChoice(int choice)
{
	switch(choice)
	{
		case 1:
			insertRecord();
			saveFile();
			break;
		case 2:
			showList();
			break;
		case 3:
			searchByName();
			break;
		case 4:
			deleteRecord();
			saveFile();
			break;
		case 5:
			modifyRecord();
			saveFile();
			break;
        case 6:
			backupReset();
			break;
		case 7:
		    restoreData();
		    break;
        case 8:
		    break;
		default:
		    cin.get(pause);
            cout<<"\n\t\t Invalid choice..! Press Any Key..";
            cin.ignore(1,pause);
            system("cls");
			break;
	}
}

void Record::insertRecord()
{
	node *new_ptr;
	new_ptr=new node;

	system("cls");

	cout << "\n\n\t\t=======================================================================\n" ;
	cout << "\t\t\t\t\t -: Adding New Record :- " ;
 	cout << "\n\t\t=======================================================================\n\n" ;

	if(new_ptr!=NULL)
	{
	    cin.ignore(1,pause);
        cout << "\n\t\tEnter your Full Name : " ;
        cin.getline(new_ptr->name, 100);

        while(1)
        {
            if(!validateName(new_ptr->name))
            {
                cout << "\n\t\t\tName must contain alphabets only... " ;
                cout << "\n\t\tEnter your Full Name : " ;
                cin.getline(new_ptr->name, 100);
            }
            else
            break;
        }
        //cout << new_ptr->name ;

        cout << "\n\t\tEnter Mobile Number(10 digit) : " ;
        cin.getline(new_ptr->mobile_no, 20);
        while(1)
        {
            if(!validateMobileNumber(new_ptr->mobile_no))
            {
                cout << "\n\t\t\tMobile number must contains numbers only and it should consist 10 digits..." ;
                cout << "\n\t\tEnter Mobile Number(10 digit) : " ;
                cin.getline(new_ptr->mobile_no, 20);
            }
            else
            break;
        }
        //cout << new_ptr->mobile_no ;

        cout << "\n\t\tEnter Email Address : " ;
        cin.getline(new_ptr->email_id, 100);
        while(1)
        {
            if(!validateEmailId(new_ptr->email_id))
            {
                cout << "\n\t\t\tPlease enter valid email address... " ;
                cout << "\n\t\tEnter Email Address : " ;
                cin.getline(new_ptr->email_id, 100);
            }
            else
            break;
        }
        //cout << new_ptr->email_id ;

		insertNode(new_ptr);

		cout<<"\n\n\t\tRecord Successfully Inserted.. \n";
        cout<<"\n\n\t\tPlease press enter to continue : ";
        cin.ignore(1,pause);
        system("cls");
	}
	else
    {
        cout << "\n Warning: Failed to apply for storage space, cannot create new node...\n" ;
        cout<<"\n\n\t Please press enter to continue : ";
        cin.ignore(1,pause);
        system("cls");
    }
}
void Record::insertNode(node *new_ptr)
{
	//cout << new_ptr->name << new_ptr->mobile_no << new_ptr->email_id;

	node *temp_ptr;

    //The doubly linked list is empty
	if(head_ptr == NULL)
	{
		insertNodeHead(new_ptr);

		return;
	}
    else {

        insertNodeEnd(new_ptr);

        return;
    }
}
void Record::insertNodeHead(node *new_ptr)
{
	new_ptr->next=new_ptr;
    new_ptr->pre=new_ptr;

    head_ptr=new_ptr;
    tail_ptr=new_ptr;
}
void Record::insertNodeEnd(node *new_ptr)
{
	new_ptr->next = head_ptr;
    new_ptr->pre = tail_ptr;

	tail_ptr->next = new_ptr;
	tail_ptr = new_ptr;
}

void Record::showList()
{
	system("cls");

	int i = 0;
	current_ptr = head_ptr;

	cout << "\n\n\t=======================================================================\n" ;
	cout << "\t\t\t\t -: Phone Book :- " ;
 	cout << "\n\t=======================================================================\n" ;

	if(current_ptr == NULL)
        cout<<"\n\n\t Phone Book is empty..! \n";
	else {
        cout<< "\n\n\t==================================================================================================" << endl ;
        cout<< "\t Sr.No |              Name              |   Phone Number   |       Email Address  " << endl ;
        cout<< "\t===============================================================================================" << endl << endl ;
        //cout<<" Name "<<setw(40)<<" Phone Number "<<setw(30)<<" Email Address "<<setw(40)<<endl ;

        do
        {
            i++;
            cout << "\t" << setw(5) << i << setw(35) << current_ptr->name << setw(15) << current_ptr->mobile_no << setw(40) << current_ptr->email_id <<endl;
            //cout<< <<setw(10)<<<<setw(10)<<<<setw(120)<<endl;
            current_ptr = current_ptr->next;

        }while(current_ptr != head_ptr);
	}

	cin.get(pause);

    cout<<"\n\n\t Please press enter to continue : ";
	cin.ignore(1,pause);
	system("cls");
}

void Record::searchByName()
{
	system("cls");
	int nflag=0;

	cout << "\n\n\t=======================================================================\n" ;
	cout << "\t\t\t\t -: Searching A Record :- " ;
 	cout << "\n\t=======================================================================\n" ;

	char search_string[100];
	current_ptr = head_ptr;

	if(current_ptr==NULL)
        cout<<"\n\tPhone Book is empty";
	else
	{
		cin.ignore(20,'\n');
        cout << "\n\n\tEnter the Full Name of the Person you want to search : " ;
		cin.getline(search_string, 100);

		do
		{
			if(strcmp(current_ptr->name, search_string) == 0)
			{
                cout<<"\n\tFound record..\n\n";

                nflag=1;

                cout<< "\t                 Name                |    Phone Number    |       Email Address  " << endl ;
                cout<< "\t==================================================================================================" << endl ;
                cout << "\t " << setw(35) << current_ptr->name << setw(15) << current_ptr->mobile_no << setw(40) << current_ptr->email_id <<endl;

                break;
            }

			current_ptr = current_ptr->next;

		}while(current_ptr != head_ptr);

		if(nflag == 0)
        {
            cout << "\n\n\tNo record Found..!\n";
        }
	}

    cout<<"\n\n\tPlease press enter to continue : ";
	cin.ignore(1,pause);
	system("cls");
}

void Record::saveFile()
{
	ofstream outfile;

	outfile.open("Data.txt",ios::out);

	if(outfile)
	{
		current_ptr = head_ptr;

		if(current_ptr != NULL)
		{
			do{
                /*cout << current_ptr->name << current_ptr->mobile_no << current_ptr->email_id;
                cout<< " Press enter to continue \n" ;
                cin.get(pause);
                system("cls");*/

				outfile<<current_ptr->name<<endl;
				outfile<<current_ptr->mobile_no<<endl;
				outfile<<current_ptr->email_id<<endl;

				current_ptr = current_ptr->next;

			}while(current_ptr != head_ptr);
		}
		outfile.close();
	}
	else
        cout<<"\n\t\t Error opening file..\n";
}

void Record::loadFile()
{
	node *new_ptr;

	ifstream infile;
	infile.open("Data.txt");

	int end_lop = 0;

	if(infile)
	{
		do{
			new_ptr = new node;

            infile.get(new_ptr->name,100);
            infile.ignore(100,'\n');

             if((strcmp(new_ptr->name, "") != 0))
            {
                infile.get(new_ptr->mobile_no,20);
                infile.ignore(20,'\n');

                infile.get(new_ptr->email_id,100);
                infile.ignore(100,'\n');

                insertNode(new_ptr);
            }
            else
            {
                delete new_ptr;
                end_lop = 1;
            }

            /*cout << new_ptr->name << new_ptr->mobile_no << new_ptr->email_id << endl;
            cout<< " Press enter to continue \n" ;
            cin.get(pause);
            system("cls");*/

		}while(end_lop == 0 && !infile.eof());

		infile.close();
	}
	else
	 cout<<"\n\t\t No data file is available, the record table is empty..\n";
}

void Record::deleteRecord()
{
    system("cls");
    char search_string[100];
    int nflag=0;

    node *previous_ptr;
    previous_ptr=NULL;

    current_ptr = head_ptr;

    cout << "\n\n\t=======================================================================\n" ;
    cout << "\t\t\t\t -: Deleting A Record :- " ;
    cout << "\n\t=======================================================================\n" ;

    if(current_ptr==NULL)
    {
        cout<<"\n\tNo records to delete.. ";
        return;
    }
    cin.ignore(20,'\n');

    cout<<"\n\tEnter the Full Name of the person you want to delete : ";
    cin.getline(search_string, 100);

    do
    {
        if(strcmp(current_ptr->name, search_string) == 0) {

            nflag=1;

            cout<<"\n\tFound record.. \n\n";
            cout<< "\t                 Name                |    Phone Number    |       Email Address  " << endl ;
            cout<< "\t==================================================================================================" << endl ;
            cout << "\t " << setw(35) << current_ptr->name << setw(15) << current_ptr->mobile_no << setw(40) << current_ptr->email_id <<endl;

            break;
        }

        current_ptr = current_ptr->next;

    }while(current_ptr != head_ptr);

    if(nflag==0)
        cout<<"\n\tNo matching records were found or deleted\n";
    else {
        if(verifyDelete())
        {
            deleteNode();
            cout<<"\n\n\tRecord Successfully deleted.. \n";
        }
        else
        {
            cout << "\n\tThe records of " << search_string <<" were not deleted..\n";
            current_ptr=current_ptr->next;
        }
    }

    cout<<"\n\n\tPlease press enter to continue : ";
    cin.ignore(1,pause);
    system("cls");
}
int Record::verifyDelete()
{
    char yesno;
    cout<<"\n\tConfirm? (y/n) : ";
	cin>>yesno;

	cin.ignore(20,'\n');
	if((yesno=='Y')||(yesno=='y'))
        return(1);
	else
        return(0);
}
void Record::deleteNode()
{
    if(current_ptr == head_ptr)
        deleteNodeHead();
    else
        if(current_ptr->next == head_ptr)
            deleteNodeEnd();
        else
            deleteNodeMiddle();
}
void Record::deleteNodeHead()
{
    if(head_ptr->next != head_ptr)
	{
		head_ptr = current_ptr->next;
		tail_ptr->next = head_ptr;
		head_ptr->pre = tail_ptr;

		delete current_ptr;
		current_ptr = head_ptr;
	}
	else
	{
		head_ptr = NULL;
		tail_ptr = NULL;

		delete current_ptr;
	}
}
void Record::deleteNodeMiddle()
{
    node *previous_ptr = current_ptr->pre;

	previous_ptr->next = current_ptr->next;
	current_ptr->next->pre = previous_ptr;

	delete current_ptr;
	current_ptr=previous_ptr;
}
void Record::deleteNodeEnd()
{
    node *previous_ptr = current_ptr->pre;
	delete current_ptr;

	previous_ptr->next=head_ptr;
	head_ptr->pre = previous_ptr;

	tail_ptr = previous_ptr;
	current_ptr = tail_ptr;
}

void Record::modifyRecord()
{
    system("cls");
	char search_string[100];
	int nflag=0;
	current_ptr=head_ptr;

	cout << "\n\n\t=======================================================================\n" ;
    cout << "\t\t\t\t -: Updating A Record :- " ;
    cout << "\n\t=======================================================================\n" ;

	if(current_ptr==NULL)
    {
        cout<<"\n\tNo records to modify.. ";
        return;
    }
	cin.get(pause);
    cout<<"\n\tEnter the Full Name of the person you want to update : ";
    cin.getline(search_string, 100);

	do
    {
        if(strcmp(current_ptr->name, search_string) == 0) {

            nflag=1;

            cout<<"\n\tFound record.. \n\n";
            cout<< "\t                 Name                |    Phone Number    |       Email Address  " << endl ;
            cout<< "\t==================================================================================================" << endl ;
            cout << "\t " << setw(35) << current_ptr->name << setw(15) << current_ptr->mobile_no << setw(40) << current_ptr->email_id <<endl;

            cout<< "\n\n\tPlease enter Name to be updated in record : ";
			cin.getline(current_ptr->name, 100);
			cout<< "\tPlease enter Mobile number for updated record : ";
			cin >> current_ptr->mobile_no;
			cin.get(pause);
			cout<< "\tPlease enter Email address for updated record  : ";
			cin >> current_ptr->email_id;

			cin.get(pause);
			cout<<"\n\tUpdated record.. \n\n";
            cout<< "\t                 Name                |    Phone Number    |       Email Address  " << endl ;
            cout<< "\t==================================================================================================" << endl ;
            cout << "\t " << setw(35) << current_ptr->name << setw(15) << current_ptr->mobile_no << setw(40) << current_ptr->email_id <<endl;

            break;
        }

        current_ptr = current_ptr->next;

    }while(current_ptr != head_ptr);

	if(nflag == 0)
	{
        cout<<"\n\tNo matching record found";
	}

	cout<<"\n\n\tPlease press enter to continue : ";
    cin.ignore(1,pause);
	system("cls");
}

 void Record::backupReset() {
    string line;
    bool f1 = false, f2 = false;

    ifstream in_file;
    ofstream out_file;

    in_file.open("Data.txt");
    out_file.open("Backup.txt", ios::app|ios::out);

    system("cls");

    cout << "\n\n\t=======================================================================\n" ;
    cout << "\t\t\t\t -: Data Backup :- " ;
    cout << "\n\t=======================================================================\n" ;

    if(in_file && out_file){

        while(getline(in_file, line)){
            out_file << line << "\n";
        }
        f1 = true;
    }
    else {
       cout << "\n\tCannot read File..";
    }

    in_file.close();
    out_file.close();

    ofstream file;
    file.open("Data.txt", ios::out);

    if(file){
        file << "" ;
        f2 = true;
    }
    else {
       cout << "\n\tCannot read File..";
    }

    if(f1 == true && f2 == true) {
        cout << "\n\tData Backup & Reset Successfully Done..! ";
        loadFile();
    }
    else
        cout << "\n\tError while doing data backup.. ";

    file.close();

    cin.get(pause);
    cout<<"\n\n\tPlease press enter to continue : ";
    cin.ignore(1,pause);
	system("cls");
 }
 void Record::restoreData() {
    string line;

    ifstream in_file;
    ofstream out_file;

    in_file.open("Backup.txt");
    out_file.open("Data.txt", ios::app|ios::out);

    system("cls");

    cout << "\n\n\t=======================================================================\n" ;
    cout << "\t\t\t\t -: Restoring Backup Data :- " ;
    cout << "\n\t=======================================================================\n" ;

    if(in_file && out_file){

        while(getline(in_file, line)){
            out_file << line << "\n";
        }
        cout << "\n\tRestored Backup Data Successfully..! ";
        loadFile();
    }
    else {
       cout << "\n\tCannot read File..";
    }

    in_file.close();
    out_file.close();

    cin.get(pause);
    cout<<"\n\n\tPlease press enter to continue : ";
    cin.ignore(1,pause);
	system("cls");
 }

 /*
Samarth Misal
0987654321
misalsamarth@gmail.com
Snehal Kapadnis
1144772299
snehalkapadnis@gmail.com
Karan Kadam
0987654321
karankadam@gmail.com
Sanskruti Kakade
0987654321
saanskrutikakade@gmail.com
Neha Manoj Gandhmal
1234567890
nehagandhmal123@gmail.com*/
