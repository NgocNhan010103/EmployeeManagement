#include <iostream>
#include <string>
#include <string.h>
#include <iomanip>
#include <fstream>
#include <ctime>

using namespace std;

struct DATE
{
    int d, m ,y;
};

struct STAFF
{
    string ID;
    string fullname;
    string possition; //chuc vu
    DATE birthday;
    double coefficientssalary; //he so luong
    double basicsalary; //luong co ban
    double actualsalary ; //Luong thuc nhan = he so luon x luong co ban
};

struct NODE
{
	STAFF data;
	NODE *NEXT;
};

struct LIST
{
	NODE *HEAD;
	NODE *TAIL;
};

NODE *CREATENODE(STAFF s)
{
	NODE *p = new NODE;
	if (p == NULL)
		return NULL;
	p->data = s;
	p->NEXT = NULL;
	return p;
};

void CREATELIST(LIST &l)
{
	l.HEAD = NULL;
	l.TAIL = NULL;
};

void ADDLASTLIST(LIST &l, NODE *p)
{
	if (l.HEAD == NULL)
		l.HEAD = l.TAIL = p;
	else
	{
		l.TAIL->NEXT = p;
		l.TAIL = p;
	}
};

void STANDARDNAME(string &fullname)
{
	while (fullname[0] == ' ')
		fullname.erase(0, 1); //xoa ki tư trong dau tien trong chuoi
	while (fullname[fullname.length() - 1] == ' ')
		fullname.pop_back(); //xoa khoang trong o cuoi
	int i = 0;
	while (i < fullname.length() - 1)
	{
		if (fullname[i] == ' '&&fullname[i + 1] == ' ')
		{
			fullname.erase(i, 1);
			i--;
		}
		i++;
	}
	int l = fullname.length();
	strlwr((char*)fullname.c_str());
	fullname[0] = fullname[0] - 32;
	for (int i = 0; i < l-1;i++)
	if (fullname[i]==' '&& fullname[i+1]!=' ')
		fullname[i+1] = fullname[i+1] - 32;
};

int LEN(LIST l)
{
	int i = 0;
	NODE* p = l.HEAD;
	while (p != NULL)
	{
		i++;
		p = p->NEXT;
	}
	return i;
};

void INPUTONESTAFF(LIST &l, STAFF &s)
{
	cin.ignore();
    cout << "Enter ID: "; 
    getline(cin, s.ID);

    // Kiểm tra xem ID đã tồn tại trong danh sách hay chưa
    NODE *p = l.HEAD;
    while (p != NULL)
    {
        if (p->data.ID == s.ID)
        {
            cout << "ID already exists. Please enter a different ID: ";
            getline(cin, s.ID);
            p = l.HEAD;
        }
        else
        {
            p = p->NEXT;
        }
    }

    cout << "Enter the fullname: ";
    getline(cin, s.fullname);
    STANDARDNAME(s.fullname);

    cout << "Enter Day: "; 
    cin >> s.birthday.d;
    cout << "Enter Month: "; 
    cin >> s.birthday.m;
    cout << "Enter Year: "; 
    cin >> s.birthday.y;
    cin.ignore();

    cout << "Enter Possition: "; 
    getline(cin,s.possition);

    do
    {
        cout << "Enter Coefficientssalary: "; cin >> s.coefficientssalary;
        if (s.coefficientssalary < 0)
            cout << "Retype Coefficientssalary: " << endl;

    } while (s.coefficientssalary < 0);

    do
    {
        cout << "Enter Basicsalary: "; cin >> s.basicsalary;
        if (s.basicsalary < 0)
            cout << "Retype Basicsalary: " << endl;

    } while (s.basicsalary < 0);

    cin.ignore();
    s.actualsalary = s.coefficientssalary * s.basicsalary;
};


void INPUTLIST(LIST &l)
{
	STAFF s;
	INPUTONESTAFF(l, s);
	NODE* p = CREATENODE(s);
	ADDLASTLIST(l, p);
};

void OUTPUTONESTAFF(STAFF s)
{
	cout << fixed;
	cout << setprecision(2);
	cout << setw(10) << left << s.ID << setw(30) << left << s.fullname << right << setfill('0') << setw(2) << s.birthday.d <<"/"
	<< right << setfill('0') << setw(2) << s.birthday.m <<"/"<< setfill(' ') << left << setw(14) << s.birthday.y << setfill(' ') << setw(20) << left 
	<< s.possition << setfill(' ') << setw(30) << left << s.coefficientssalary << setfill(' ') << setw(20) << left << s.basicsalary 
	<< setfill(' ') << setw(20) << left << s.actualsalary << endl;
};

void OUTPUTLIST(LIST l)
{
	if (LEN(l) == 0)
	{
		cout << "List empty" << endl;
		return;
	}
	cout << setw(10) << left << "ID" << setw(30) << left << "NAME" << setw(20) << left << "BIRTHDAY" << setw(20) << left << "POSSITION" 
	<< setw(30) << left << "COEFFICIENTSSALARY" << setw(20) << left << "BASICSALARY($)" << setw(20) << left << "ACTUALSALARY($)" << endl;
	for (NODE *p = l.HEAD; p != NULL; p = p->NEXT)
		OUTPUTONESTAFF(p->data);
};

string GETNAME(string fullname)
{
	int l = fullname.length();
	int i;
	for (i = l - 1; i >= 0; i--)
	if (fullname[i] == ' ')
	{
		break;
	return fullname.substr(i);
	}
};

string GETID(string ID)
{
    int l = ID.length();
    for (int i = l - 1; i >= 0; i--)
    {
    if (ID[i] == 'T' || ID[i] == '0')
        break;
    return ID.substr(i);
    }
}

void SWAP(STAFF &x, STAFF &y)
{
	STAFF t = x;
	x = y;
	y = t;
};



NODE *SEARCHBYCRETERIA(LIST l,string field, string value)
{
	cout << "Enter the criteria to search: ";
	cin >> field;
	cout << "Enter the infomation to search: ";
	cin >> value;
    int i = 0;
    bool found = false;
    for (NODE *p = l.HEAD; p != NULL; p = p->NEXT) 
	{
        i++;
		if (field == "ID" && value == p->data.ID) {
			found = true;
		} else if (field == "NAME" && value == GETNAME(p->data.fullname)) {
            found = true;
        } else if (field == "POSSITION" && value == p->data.possition) {
            found = true;
        } else if (field == "BIRTHDAY" && value == to_string(p->data.birthday.d) + "/" + to_string(p->data.birthday.m) + "/" + to_string(p->data.birthday.y)) {
            found = true;
        } else if (field == "COEFFICIENTSSALARY" && stod(value) == p->data.coefficientssalary) {
            found = true;
        } else if (field == "BASICSALARY" && stod(value) == p->data.basicsalary) {
			found = true;
		} else if (field == "ACTUALSALARY" && stod(value) == p->data.actualsalary) {
			found = true;
		}
        if (found)
			return p;
		return NULL;
	}
};

void POSSITIONORDER(string possition)
{
    "Staff" < "Magager";
    "Manager" < "Secretary";
    "Secretary" < "VicePresident";
    "VicePresident" < "GeneralManager";
    "GeneralManager" < "ChairPerson";
};

void SORTFORCRITERIA(LIST l)
{
	string field;
	cout << "Enter the criteria to sort: ";
	cin >> field;
	for (NODE* Q = l.HEAD; Q->NEXT != NULL; Q = Q->NEXT)
    { 
        for (NODE* p = Q->NEXT; p != NULL; p = p->NEXT)
        {
			bool found = false;
			if (field == "ID" && strcmp((char*)GETID(Q->data.ID).c_str(), (char*)GETID(p->data.ID).c_str()) > 0) {
				found = true;
			} else if (field == "NAME" && strcmp((char*)GETNAME(Q->data.fullname).c_str(), (char*)GETNAME(p->data.fullname).c_str()) > 0) {
				found = true;
			} else if (field == "BIRTHDAY" && Q->data.birthday.y > p->data.birthday.y || (Q->data.birthday.y == p->data.birthday.y 
            	     && Q->data.birthday.m > p->data.birthday.m) || (Q->data.birthday.y == p->data.birthday.y 
            	     && Q->data.birthday.m == p->data.birthday.m && Q->data.birthday.d > p->data.birthday.d)) {
				found = true;
			} else if (field == "POSSITION" && strcmp((char*)Q->data.possition.c_str(), (char*)p->data.possition.c_str()) > 0) {
				found = true;
			} else if (field == "COEFFICIENTSSALARY" && Q->data.coefficientssalary > p->data.coefficientssalary) {
				found = true;
			} else if (field == "BASICSALARY" && Q->data.basicsalary > p->data.basicsalary) {
				found = true;
			} else if (field == "ACTUALSALARY" && Q->data.actualsalary > p->data.actualsalary) {
				found = true;
			}
			if (found)
				SWAP(Q->data, p->data);
		}
	}	
};

void INSERTFORCRITERIA(LIST &l)
{
	STAFF s;
	string field;
	cout << "Enter the criteria to insert: ";
	cin >> field;
    INPUTONESTAFF(l, s);
	NODE *q = l.HEAD;
	NODE *p = CREATENODE(s);
    if (p == NULL)
        return;
	bool found = false;
	if (field == "ID" && (l.HEAD == NULL || GETID(p->data.ID) <= GETNAME(l.HEAD->data.ID))) {
		found = true;
	} else while (field == "ID" && (q->NEXT != NULL && GETID(q->NEXT->data.ID) < GETID(s.ID)))  
    		q = q->NEXT;
	if (field == "NAME" && (l.HEAD == NULL || GETNAME(p->data.fullname) <= GETNAME(l.HEAD->data.fullname))) {
		found = true;
	} else while (field == "NAME" && (q->NEXT != NULL && GETNAME(q->NEXT->data.fullname) < GETNAME(s.fullname))) 
			q = q->NEXT;
	if (field == "BIRTHDAY" && (l.HEAD == NULL || (p->data.birthday.y < l.HEAD->data.birthday.y || (p->data.birthday.y == l.HEAD->data.birthday.y 
           					   && p->data.birthday.m < l.HEAD->data.birthday.m) || (p->data.birthday.y == l.HEAD->data.birthday.y 
                       	 	   && p->data.birthday.m == l.HEAD->data.birthday.m && p->data.birthday.d < l.HEAD->data.birthday.d)))) {
		found = true;
	} else while (field == "BIRTHDAY" && (q->NEXT != NULL && (s.birthday.y > q->NEXT->data.birthday.y || (s.birthday.y == q->NEXT->data.birthday.y 
           					       && s.birthday.m > q->NEXT->data.birthday.m) || (s.birthday.y == q->NEXT->data.birthday.y 
                                   && s.birthday.m == q->NEXT->data.birthday.m && s.birthday.d > q->NEXT->data.birthday.d))))
			q = q->NEXT;
	if (field == "POSSITION" && (l.HEAD == NULL || p->data.possition <= l.HEAD->data.possition)) {
		found = true;
	} else while (field == "POSSITION" && (q->NEXT != NULL && q->NEXT->data.possition < s.possition)) 
			q = q->NEXT;
	if (field == "COEFFICIENTSSALARY" && (l.HEAD == NULL || p->data.coefficientssalary <= l.HEAD->data.coefficientssalary)) {
		found = true;
	} else while (field == "COEFFICIENTSSALARY" && (q->NEXT != NULL && q->NEXT->data.coefficientssalary < s.coefficientssalary)) 
			q = q->NEXT;
	if (field == "BASICSALARY" && (l.HEAD == NULL || p->data.basicsalary <= l.HEAD->data.basicsalary)) {
		found = true;
	} else while (field == "BASICSALARY" && (q->NEXT != NULL && q->NEXT->data.basicsalary < s.basicsalary)) 
			q = q->NEXT;
	if (field == "ACTUALSALARY" && (l.HEAD == NULL || p->data.actualsalary <= l.HEAD->data.actualsalary)) {
		found = true;
	} else while (field == "ACTUALSALARY" && (q->NEXT != NULL && q->NEXT->data.actualsalary < s.actualsalary)) 
			q = q->NEXT;
	if (found) {
		p->NEXT = l.HEAD;
        l.HEAD = p;
	} else {
		p->NEXT = q->NEXT;
        q->NEXT = p;
	}
};

void DELETEFORCRITERIA(LIST& l)
{
	string field;
	string value;
    NODE* q = SEARCHBYCRETERIA(l,field,value);
    if (q == NULL)
    {
        cout << "Value does not exist";
        return;
    }
    else
    {
        int pos = 1;
        NODE* p = l.HEAD;
        NODE* k;
        while (p->data.ID != q->data.ID)
        {
            pos++;
            p = p->NEXT;
        }
        if (pos == 1)
        {
            k = l.HEAD;
            l.HEAD = l.HEAD->NEXT;
            delete k;
        }
        else
        {
            if (pos == LEN(l))
            {
                int i = 1;
                p = l.HEAD;
                while (i != pos - 1)
                {
                    i++;
                    p = p->NEXT;
                }

                k = q;
                p->NEXT = NULL;
                delete k;

            }
            else
            {
                int i = 1;
                p = l.HEAD;
                while (i != pos - 1)
                {
                    p = p->NEXT;
                    i++;
                }

                k = q;
                p->NEXT = k->NEXT;
                delete k;
            }

        }
    }
};

void SEARCHFORCRITERIA(LIST l) 
{
	string field;
	string value;
	cout << "Enter the criteria to search: ";
	cin >> field;
	cout << "Enter the infomation to search: ";
	cin >> value;
    int i = 0;
    bool found = false;
    for (NODE *p = l.HEAD; p != NULL; p = p->NEXT) 
	{
        i++;
		if (field == "ID" && value == p->data.ID) {
			found = true;
		} else if (field == "NAME" && value == GETNAME(p->data.fullname)) {
            found = true;
        } else if (field == "POSSITION" && value == p->data.possition) {
            found = true;
        } else if (field == "BIRTHDAY" && value == to_string(p->data.birthday.d) + "/" + to_string(p->data.birthday.m) + "/" + to_string(p->data.birthday.y)) {
            found = true;
        } else if (field == "COEFFICIENTSSALARY" && stod(value) == p->data.coefficientssalary) {
            found = true;
        } else if (field == "BASICSALARY" && stod(value) == p->data.basicsalary) {
			found = true;
		} else if (field == "ACTUALSALARY" && stod(value) == p->data.actualsalary) {
			found = true;
		}
        if (found) {
            cout << "Infomation Staff: " << endl;
            cout << setw(10) << left << "ID" << setw(30) << left << "NAME" << setw(20) << left << "BIRTHDAY" << setw(20) << left << "POSSITION"
                << setw(30) << left << "COEFFICIENTSSALARY" << setw(20) << left << "BASICSALARY($)" << setw(20) << left << "ACTUALSALARY($)" << endl;
            cout << fixed << setprecision(2);
            cout << setw(10) << left << p->data.ID << setw(30) << left << p->data.fullname << right << setfill('0') << setw(2) << p->data.birthday.d << "/"
                << right << setfill('0') << setw(2) << p->data.birthday.m << "/" << setfill(' ') << left << setw(14) << p->data.birthday.y << setfill(' ') << setw(20) << left
                << p->data.possition << setfill(' ') << setw(30) << left << p->data.coefficientssalary << setfill(' ') << setw(20) << left << p->data.basicsalary
                << setfill(' ') << setw(20) << left << p->data.actualsalary << endl;
            cout << "Staff Possition: " << i << endl;
            found = false;
        }
    }
	if (found = false)
	cout << "Staff does not exist ! " << endl;
};

void READONESTAFF(fstream &f,STAFF &s)
{
	char (ch);
	getline(f, s.ID, ',');
    getline(f, s.fullname, ',');
    f >> s.birthday.d;
    f.ignore(1);
    f >> s.birthday.m;
    f.ignore(1);
    f >> s.birthday.y;
    f.ignore(1);
    getline(f, s.possition, ',');
    f >> s.coefficientssalary;
    f.ignore(1);
    f >> s.basicsalary;
	
	f.get(ch);
     s.actualsalary = s.coefficientssalary * s.basicsalary;

}

void READLISTSTAFF(fstream &f, LIST &l)
{
	STAFF s;
	f.open("C:/Giai Thuat/BAITAPNHOM/FILETXT/LISTSTAFF.txt", ios::in);
	if (!f.is_open()) //kiem tra file duoc mo hay chua 
      cout<<"Could not open file!"<< endl;
    else
	{
		 while (f.peek() != EOF)// Kiểm tra xem đã đọc đến cuối file hay chưa
    	{	
        	READONESTAFF(f, s);
            NODE *p = CREATENODE(s);
            ADDLASTLIST(l, p);
    	}
		f.clear();
	}
	f.close();
};

void WRITEONESTAFFTOFILE(fstream &f, STAFF s)
{
	f << setw(10) << left << s.ID << setw(30) << left << s.fullname << right << setfill('0') << setw(2) << s.birthday.d <<"/"
	<< right << setfill('0') << setw(2) << s.birthday.m <<"/"<< setfill(' ') << left << setw(14) << s.birthday.y << setfill(' ') << setw(20) << left 
	<< s.possition << setfill(' ') << setw(30) << left << s.coefficientssalary << setfill(' ') << setw(20) << left << s.basicsalary 
	<< setfill(' ') << setw(20) << left << s.actualsalary << endl;
};

void WRITELISTTOFILE(fstream &f, LIST l)
{
	f.open("Staff1.txt", ios::out);
	f << setw(10) << left << "ID" << setw(30) << left << "NAME" << setw(20) << left << "BIRTHDAY" << setw(20) << left << "POSSITION" 
	<< setw(30) << left << "COEFFICIENTSSALARY" << setw(20) << left << "BASICSALARY($)" << setw(20) << left << "ACTUALSALARY($)" << endl;
	for (NODE *k = l.HEAD; k != NULL; k = k->NEXT)
		WRITEONESTAFFTOFILE(f, k->data);
	f.close();
};

void MENU()
{
	fstream f;
	LIST l;
	STAFF s;
	CREATELIST(l);
	int option;
	do
	{
		system("cls");
		cout << "1.Input || " << "2.Output || " << "3.READ FILE || " 
		<< "4.SORT || " << "5.INSERT || " << "6.DELETE || "<< "7.SEARCH || " << "8.WRITE || " << endl;
		cout << "Please option: "; 
		cin >> option; 
		cin.ignore();
		if (option == 1)  INPUTLIST(l);
		if (option == 2)  OUTPUTLIST(l);
		if (option == 3)  READLISTSTAFF(f,l);
		if (option == 4)  SORTFORCRITERIA(l);
		if (option == 5)  INSERTFORCRITERIA(l);
		if (option == 6)  DELETEFORCRITERIA(l);
		if (option == 7)  SEARCHFORCRITERIA(l);
		if (option == 8)  WRITELISTTOFILE(f,l);
		system("pause");
	} while (option > 0 && option <= 8);
};

int main()
{
	LIST l;
	CREATELIST(l);
	MENU();
	return 0;
}