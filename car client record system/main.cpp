#include<iostream>
#include<fstream>
#include<iomanip>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
#define SIZE  10
const int BREAK = 32767;

using namespace std;

//FUNCTION PROTOTYPES
void mainMenu();
void load();
void logo();
void displayInvalid();
void chevroletClient();

//INLINE FUNCTIONS
inline void cls() {
	system("cls");
}

inline void space(int tab) {
	for (int i = 0; i < tab; i++)
		cout << "\t";
}

inline void line(int lines) {
	for (int i = 0; i < lines; i++)
		cout << endl;
}

inline void character(char c, int n) {
	for (int i = 0; i < n; i++) {
		Sleep(100);
		cout << c << " ";
	}
	cout << endl;
}

//FRIEND FUNCTION DEFINITION
void displayValues(const char* features[SIZE], int nums, int chosenfeatures[SIZE]) {
	int i = 0;

	//RECORDS STORAGE FILE
	ofstream records;
	records.open("clientRecords.txt", ios::out | ios::app);
	if (!records) {
		line(6);	space(9); 	Sleep(300);
		cout << "ERROR: Data could not be stored.";
		Sleep(1000);
		exit(1);
	}
	while (chosenfeatures[i] != BREAK) {
		line(1);  space(8);	 Sleep(200);
		records << setw(21) << right << char(4) << "  " << features[chosenfeatures[i] - 1] << endl;
		cout << char(4) << "  " << features[chosenfeatures[i++] - 1];
	}

	records.close();
}


//FILE FUNCTIONS
void engineInfo(const char Scode[4], const char Ecode[4]) {

	ifstream inf;
	inf.open("engineDetails.txt", ios::in);
	if (!inf) {
		logo();
		line(6);	space(9); 	Sleep(300);
		cout << "~ EMPTY ARCHIVES ~";
	}

	const int N = 80;
	char line[N];
	inf.getline(line, N);
	while (inf) {
		if (!strcmp(line, Scode)) {
			while (inf) {
				inf.getline(line, N);
				if (!strcmp(line, Ecode))
					break;
				Sleep(200);	    space(6);
				cout << line << endl;
			}
		}
		inf.getline(line, N);
	}

	inf.close();
}

void chosenEngine(char engineNum, const char Scode[4]) {

	ifstream inf;
	inf.open("engineDisplay.txt", ios::in);

	//RECORDS STORAGE FILE
	ofstream records;
	records.open("clientRecords.txt", ios::out | ios::app);
	if (!records) {
		line(6);	space(9); 	Sleep(300);
		cout << "ERROR: Data could not be stored.";
		Sleep(1000);
		exit(1);
	}

	char opt;
	const int N = 80;
	char fline[N];
	inf.getline(fline, N);
	while (inf) {
		if (!strcmp(fline, Scode)) {
			while (inf) {
				inf >> opt;
				if (opt == engineNum) {
					inf.seekg(2, ios::cur);
					for (int i = 0; i < 4; i++) {
						line(1);	Sleep(300);		space(6);
						inf.getline(fline, N, '\n');
						cout << setw(33) << left << fline;
						records << endl << setw(33) << left << fline;
						inf.getline(fline, N, '\n');
						cout << setw(33) << right << fline;
						records << setw(33) << right << fline;
					}
					break;
				}
				else {
					inf.seekg(2, ios::cur);
					for (int i = 0; i < 8; i++)
						inf.getline(fline, N);
				}
			}
			break;
		}
		inf.getline(fline, N);
	}

	inf.close();
	records.close();
}

char engineChoice(char engine, int choices) {
	while (engine == '0') {
		try {
			Sleep(300);  line(2);   space(6);
			cout << ">>>\t";
			cin >> engine;
			char nums = '0' + choices;
			if (engine < '1' || engine > nums || cin.fail())
				throw engine;
			return engine;
		}
		catch (...) {
			engine = '0';
			displayInvalid();
		}
	}
}


class Admin {
public:
	void login();
	void adminMenu();
	void clientRecords();
};
void Admin::login() {
	string admininput;
	char password[20];
	char c;

	ifstream fin;
	fin.open("password.txt");
	if (!fin) {
		line(6);	space(9); 	Sleep(300);
		cout << "ERROR: FILE MISSING !!";
		exit(1);
	}
	fin.getline(password, 20);
	fin.close();

	do {
		cls();
		line(15);		space(9);		Sleep(500);
		cout << "P  A  S  S  W  O  R  D";
		line(4);		space(10);		Sleep(200);
		while ((c = _getch()) != '\r')
		{
			if (c == '\b')																			//If the 'Backspace' key is pressed
			{
				if (admininput.size() != 0)															//If the password string contains data, erase last character
				{
					cout << "\b \b";
					admininput.erase(admininput.size() - 1, 1);
				}
				continue;
			}
			else {
				admininput += c;
				cout << "*";
			}
		}
		if (password != admininput) {
			line(3);		space(9);		Sleep(200);
			cout << "    Password Inavlid." << endl;
			admininput = "";
			Sleep(700);
		}
	} while (password != admininput);

	cls();
	line(17);		space(9);		Sleep(500);
	cout << "P A S S W O R D   M A T C H E D";
	Sleep(1000);
	load();
	adminMenu();
}
void Admin::adminMenu() {
	int x;
	cls();
	line(15);		space(7);		Sleep(500);
	cout << ">>>>>> \t  W E L C O M E   A D M I N\t<<<<<<";
	line(4);		space(8);		Sleep(200);
	cout << "1.  Chevrolet Client Records" << endl;
	space(8);		Sleep(200);
	cout << "2.  Log Out" << endl;

	while (1) {
		line(3);		space(8);		Sleep(300);
		cout << ">>>\t";
		cin >> x;
		try {
			if (x < 1 || x > 2 || isalpha(x))
				throw x;

			switch (x) {
			case 1:
				load();
				clientRecords();
				break;
			case 2:
				load();
				mainMenu();
				break;
			default:
				break;
			}
		}
		catch (...) {
			displayInvalid();
		}
	}
}
void Admin::clientRecords() {
	char str[100];
	cls();
	logo();
	line(3);

	ifstream records;
	records.open("clientRecords.txt", ios::in);
	if (!records) {
		line(6);	space(9); 	Sleep(300);
		cout << "~ EMPTY ARCHIVES ~";
	}
	else {
		while (!records.eof()) {
			Sleep(100);	space(6);
			records.getline(str, 100);
			cout << str << endl;
		}
		records.close();
	}

	line(6);	space(9);
	cout << "     admin menu";
	line(3);	space(9);
	cout << ">>>\t";
	_getch();
	load();
	adminMenu();
}

class Customer {
	char name[30];
	char contactNumber[11];
	char email[30];

protected:
	char registrationNum[15];
	char VIN[25];
	static int clientID;

public:
	static int getClientID();
	void read();
	void display();
};
int Customer::clientID = 4005000;
int Customer::getClientID() {

	fstream fID;
	fID.open("ChevroletClientIDs.txt", ios::in);

	if (fID.fail()) {
		fID.open("ChevroletClientIDs.txt", ios::out);
		fID << clientID << endl;
		fID.close();
		return clientID;
	}
	fID.close();
	fID.open("ChevroletClientIDs.txt", ios::app);
	fID.seekp(0, ios::end);
	int len = fID.tellp();
	clientID = 4005000  + (len / 9);
	fID << clientID << endl;
	fID.close();
	return clientID;
}
void Customer::read() {
	line(3);	space(7);	character(249, 23);	 line(1);  space(7);
	cout << "C L I E N T   P E R S O N A L   D E T A I L S";
	line(2);  space(7);	character(249, 23);		line(6);		space(6);
	cin.ignore();
	cout << setw(30) << "NAME:  ";
	std::cin.getline(name, 30);
	Sleep(500);	line(1); space(6);
	cout << setw(30) << "CONTACT NUMBER:  ";
	std::cin.getline(contactNumber, 11);
	Sleep(500);  line(1);	space(6);
	cout << setw(30) << "EMAIL:  ";
	std::cin.getline(email, 30);
	Sleep(500);	line(1); space(6);
	cout << setw(30) << "VEHICLE REGISTRATION NO.:  ";
	std::cin.getline(registrationNum, 17);
	Sleep(500);	 line(1);   space(6);
	cout << setw(30) << "VEHICLE IDENTIFICATION NO.:  ";
	std::cin.getline(VIN, 25);
	cls();
}
void Customer::display() {

	//RECORDS STORAGE FILE
	ofstream records;
	records.open("clientRecords.txt", ios::out | ios::app);
	if (!records) {
		line(6);	space(9); 	Sleep(300);
		cout << "ERROR: Data could not be stored.";
		Sleep(1000);
		exit(1);
	}

	line(3);		space(9);
	cout << "PERSONAL     INFO" << endl;
	records << endl << endl << "PERSONAL INFO" << endl;
	line(3);		space(6);
	cout << setw(33) << left << "NAME:  " << setw(33) << right << name << endl;
	records << setw(33) << left << "NAME:  " << setw(33) << right << name << endl;
	Sleep(300);		space(6);
	cout << setw(33) << left << "CONTACT NUMBER:  " << setw(33) << right << contactNumber << endl;
	records << setw(33) << left << "CONTACT NUMBER:  " << setw(33) << right << contactNumber << endl;
	Sleep(500);		space(6);
	cout << setw(33) << left << "EMAIL:  " << setw(33) << right << email << endl;
	records << setw(33) << left << "EMAIL:  " << setw(33) << right << email << endl;
	Sleep(300);		space(6);
	cout << setw(33) << left << "VEHICLE REGISTRATION NO.:  " << setw(33) << right << registrationNum << endl;
	records << setw(33) << left << "VEHICLE REGISTRATION NO.:  " << setw(33) << right << registrationNum << endl;
	Sleep(300);		space(6);
	cout << setw(33) << left << "VEHICLE IDENTIFICATION NO.:  " << setw(33) << right << VIN << endl;
	records << setw(33) << left << "VEHICLE IDENTIFICATION NO.:  " << setw(33) << right << VIN << endl;

	records << endl << endl << endl << setfill(char(249)) << right << setw(66) << char(249) << endl << endl;

	line(3);	space(9);  Sleep(300);
	cout << "C H E V R O L E T" << endl;
	line(2); space(10);
	cout << char(4);	line(2);	space(8);
	cout << "    F I N D   N E W   R O A D S" << endl;

	records.close();

	line(6);	space(9);
	cout << "     main menu";
	line(3);	space(9);
	cout << ">>>\t";
	_getch();
	load();
	mainMenu();
}

class Billing
{
	int finalCost;
	int baseCost;
	int additionalCost;

public:
	Billing() {
		baseCost = 0;
		finalCost = 0;
		additionalCost = 0;
	}
	void read(int base) {
		baseCost = base;
		finalCost = base;
	}

	void operator+=(int cost) {
		this->additionalCost += cost;
		this->finalCost += cost;
	}

	void display();
};
void Billing::display() {

	//RECORDS STORAGE FILE
	static ofstream records;
	records.open("clientRecords.txt", ios::out | ios::app);
	if (!records) {
		line(6);	space(9); 	Sleep(300);
		cout << "ERROR: Data could not be stored.";
		Sleep(1000);
		exit(1);
	}

	line(4);		space(10);		character(4, 1);	 line(1);   space(9);
	cout << "  P A Y M E N T   ";
	records << endl << endl << "PAYMENT";
	line(3);	Sleep(300);		space(6);
	cout << setw(33) << left << "STANDARD VEHICLE PRICE:" << setw(31) << right << baseCost << "/-";
	records << endl << setw(33) << left << "STANDARD VEHICLE PRICE:" << setw(31) << right << baseCost << "/-";
	line(1);	Sleep(300);		space(6);
	cout << setw(33) << left << "TOTAL ACCESSORY PRICE:" << setw(31) << right << additionalCost << "/-";
	records << endl << setw(33) << left << "TOTAL ACCESSORY PRICE:" << setw(31) << right << additionalCost << "/-";
	line(1);	Sleep(300);		space(6);
	cout << setw(33) << left << "NET VEHICLE PRICE:" << setw(31) << right << finalCost << "/-";
	records << endl << setw(33) << left << "NET VEHICLE PRICE:" << setw(31) << right << finalCost << "/-";
	line(2);	space(6);	cout << char(4);	Sleep(100);		cout << setw(65) << char(4);

	records.close();
}

class AutomobileFeatures : protected Billing, protected Customer
{
	const char* interiorColors[SIZE];
	const char* exteriorColors[SIZE];
	const char* upholsteryTypes[SIZE];
	int exteriorColor;
	int interiorColor;
	int upholsteryType;

public:
	AutomobileFeatures() :
		interiorColors{ "Jet Black" , "Dark Atmosphere", "Medium Ash Gray", "Almond Butter", "Linen Beige", "Mocha", "Ivory" },
		exteriorColors{ "Caviar Black","Summit White", "Switch Blade Silver", "Sand Drift Grey", "Super Red", "Shadow Metallic" ,"Mineral Gray Metallic", "Dark Ash Metallic", "Mosaic Black Metallic" },
		upholsteryTypes{ "Premium cloth", "Perforated leather" }
	{
		exteriorColor = 0;
		interiorColor = 0;
		upholsteryType = 0;
	}
	void read();
	int readValue(const char* [], int);
	void display();
};
void AutomobileFeatures::read() {
	line(6);		space(7);		Sleep(500);
	cout << "C L A S S I C   C H E V R O L E T   E X T E R I O R   C O L O R S";
	line(4);
	exteriorColor = readValue(exteriorColors, 9);
	cls();
	line(6);		space(7);		Sleep(500);
	cout << "C L A S S I C   C H E V R O L E T   I N T E R I O R   C O L O R S";
	line(4);
	interiorColor = readValue(interiorColors, 7);
	cls();
	line(6);		space(8);		Sleep(500);
	cout << "I N T E R I O R   U P H O L S T E R Y   T Y P E S";
	line(4);
	upholsteryType = readValue(upholsteryTypes, 2);
}
int AutomobileFeatures::readValue(const char* choices[SIZE], int r) {
	int choice;
	for (int i = 0; i < r; i++) {
		Sleep(200);			space(9);
		cout << i + 1 << ".  " << choices[i] << endl;
	}

	while (1) {
		Sleep(500);			line(3);			space(8);
		cout << ">>>\t";
		cin >> choice;

		try {
			if (choice < 1 || choice > r)
				throw choice;
			return choice;
		}
		catch (...) {
			displayInvalid();
		}
	}
}
void AutomobileFeatures::display() {

	//RECORDS STORAGE FILE
	ofstream records;
	records.open("clientRecords.txt", ios::out | ios::app);
	if (!records) {
		line(6);	space(9); 	Sleep(300);
		cout << "ERROR: Data could not be stored.";
		Sleep(1000);
		exit(1);
	}

	line(1);	Sleep(300);		space(6);
	cout << setw(33) << left << "EXTERIOR COLOUR:" << setw(33) << right << exteriorColors[exteriorColor - 1];
	records << endl << setw(33) << left << "EXTERIOR COLOUR:" << setw(33) << right << exteriorColors[exteriorColor - 1] << endl;
	line(1);	Sleep(300);		space(6);
	cout << setw(33) << left << "INTERIOR COLOUR:" << setw(33) << right << interiorColors[interiorColor - 1];
	records << setw(33) << left << "INTERIOR COLOUR:" << setw(33) << right << interiorColors[interiorColor - 1] << endl;
	line(1);	Sleep(300);		space(6);
	cout << setw(33) << left << "UPHOLSTERY:" << setw(33) << right << upholsteryTypes[upholsteryType - 1] << endl;
	records << setw(33) << left << "UPHOLSTERY:" << setw(33) << right << upholsteryTypes[upholsteryType - 1] << endl << endl;

	records.close();
}

class Sedan : protected AutomobileFeatures
{
	const char* sedanModels[SIZE];
	const char* engineMalibu[SIZE];
	const char* engineCruze[SIZE];
	const char* exteriorFeatures[SIZE];
	const char* interiorFeatures[SIZE];
	const char* electronicFeatures[SIZE];
	int sedanCost[SIZE];
	int myExteriorFeatures[SIZE];
	int myInteriorFeatures[SIZE];
	int myElectronicFeatures[SIZE];
	int exFeatureCost[SIZE];
	int intFeatureCost[SIZE];
	int elecFeatureCost[SIZE];
	int model;
protected:
	char engine;
public:
	Sedan() : AutomobileFeatures(), sedanModels{ "Malibu", "Cruze" },
		engineMalibu{ "1.5L turbo four-cylinder", "2.0L turbo four-cylinder" },
		engineCruze{ "1.5L turbocharged four-cylinder", "1.6L turbo four-cylinder" },
		exteriorFeatures{ "Front and Rear Splash Guards", "Wheel Locks", "Front license plate bracket", "5-Split-Spoke Wheels", "Chrome Door Handles", "Rearview Mirror Covers", "Chevy Emblem in Black", "Leading edge Grille" },
		interiorFeatures{ "Premium carpeted floor mats","All-weather floor mats", "Front and rear all-weather floor liners", "Cargo mat", "Rear view Auto - dimming Mirror", "Heated Steering Wheel", "Leather Wrapped Shift Knob", "Rear Window Sunshades" },
		electronicFeatures{ "Bose nine-speaker audio system", "1-Meter Lightning Cable", "Universal Tablet Holder", "XGC4 Power Adapter" , "Premium Thinkware F200 Dashcam" },
		sedanCost{ 1670000, 1465000 },
		exFeatureCost{ 14500, 5500, 3000, 25000, 11250, 8400, 4400, 21500 },
		intFeatureCost{ 16400, 12300, 7500, 7200, 8000, 12000 , 4300, 6000 },
		elecFeatureCost{ 32000,  5240, 10300, 4100,  29500 },
		myExteriorFeatures{ 0 },
		myInteriorFeatures{ 0 },
		myElectronicFeatures{ 0 }
	{
		model = 0;
		engine = '0';
	}
	void read();
	void readValue(const char* [], int, int[], int[]);
	void display();
	friend void displayValues(const char* [], int, int[]);
};
void Sedan::read() {
	line(6);		space(8);		Sleep(500);
	cout << "C H E V R O L E T  S E D A N  M O D E L S" << endl;
	line(3);
	model = AutomobileFeatures::readValue(sedanModels, 2);
	Billing::read(sedanCost[(model - 1)]);

	cls();
	line(6);			space(8);			Sleep(500);
	switch (model) {
	case 1:
	{
		cout << "M A L I B U   E N G I N E S";
		line(4);
		engineInfo("ms", "me");
		line(3);		space(8);
		engine = engineChoice(engine, 2);
		break;
	}
	case 2:
	{
		cout << "C R U Z E   E N G I N E S";
		line(4);
		engineInfo("cs", "ce");
		line(3);		space(8);
		engine = engineChoice(engine, 1);
		break;
	}
	default: break;
	}

	cls();
	AutomobileFeatures::read();

	cls();
	line(6);		space(6);		Sleep(500);
	cout << "C L A S S I C   C H E V Y   S E D A N   E X T E R I O R   F E A T U R E S";
	line(4);
	readValue(exteriorFeatures, 8, myExteriorFeatures, exFeatureCost);
	cls();
	line(6);		space(6);		Sleep(500);
	cout << "C L A S S I C   C H E V Y   S E D A N   I N T E R I O R   F E A T U R E S";
	line(4);
	readValue(interiorFeatures, 8, myInteriorFeatures, intFeatureCost);
	cls();
	line(6);		space(6);		Sleep(500);
	cout << "C L A S S I C  C H E V Y  S E D A N  E L E C T R O N I C  F E A T U R E S";
	line(4);
	readValue(electronicFeatures, 5, myElectronicFeatures, elecFeatureCost);

	cls();
	Customer::read();
}
void Sedan::readValue(const char* features[SIZE], int r, int chosenfeatures[SIZE], int prices[]) {
	int j = 0, choice;
	for (int i = 0; i < r; i++) {
		Sleep(200);		space(6);
		cout << setw(2) << right << i + 1 << "  " << setw(44) << left << features[i] << setw(24) << right << prices[i] << "/-" << endl;
	}
	line(4);   space(6);
	cout << "Press 0 after selection." << endl;
	while (1) {
		Sleep(300);  line(2);   space(6);
		cout << ">>>\t";
		cin >> choice;
		try {
			if (choice < 0 || choice > r || cin.fail())
				throw choice;
			if (choice == 0) {
				chosenfeatures[j] = BREAK;
				return;
			}
			*this += prices[choice - 1];
			chosenfeatures[j++] = choice;
		}
		catch (...) {
			displayInvalid();
		}
	}
}
void Sedan::display() {

	//RECORDS STORAGE FILE
	ofstream records;
	records.open("clientRecords.txt", ios::out | ios::app);

	logo();
	if (!records) {
		line(6);	space(9); 	Sleep(300);
		cout << "ERROR: Data could not be stored.";
		Sleep(1000);
		exit(1);
	}

	records << endl << "CLIENT ID: #" << Customer::getClientID() << endl;

	line(3);	Sleep(300);		space(9);
	cout << "Chevrolet " << sedanModels[model - 1] << endl;
	records << endl << setw(33) << right << "Chevrolet " << sedanModels[model - 1] << endl;
	line(1);
	if (model == 1)
		chosenEngine(engine, "ms");
	else
		chosenEngine(engine, "cs");

	AutomobileFeatures::display();

	line(3);	Sleep(300);		space(9);
	cout << "EXTERIOR FEATURES";
	records << "EXTERIOR FEATURES" << endl;
	line(1);
	displayValues(exteriorFeatures, 9, myExteriorFeatures);
	line(3);	Sleep(300);		space(9);
	cout << "INTERIOR FEATURES";
	records << endl << "INTERIOR FEATURES" << endl;
	line(1);
	displayValues(interiorFeatures, 7, myInteriorFeatures);
	line(3);	Sleep(300);		space(9);
	cout << "ELECTRONIC FEATURES";
	records << endl << "ELECTRONIC FEATURES" << endl;
	line(1);
	displayValues(electronicFeatures, 5, myElectronicFeatures);
	records.close();

	Billing::display();
	Customer::display();
}

class SUV : protected AutomobileFeatures
{
	const char* suvModels[SIZE];
	const char* engineEquinox[SIZE];
	const char* engineSuburban[SIZE];
	const char* exteriorFeatures[SIZE];
	const char* interiorFeatures[SIZE];
	const char* electronicFeatures[SIZE];
	int suvCost[SIZE];
	int myExteriorFeatures[SIZE];
	int myInteriorFeatures[SIZE];
	int myElectronicFeatures[SIZE];
	int exFeatureCost[SIZE];
	int intFeatureCost[SIZE];
	int elecFeatureCost[SIZE];
	int model;
	char engine;
public:
	SUV() : AutomobileFeatures(), suvModels{ "Equinox", "Suburban" },
		engineEquinox{ "1.5L turbo four-cylinder", "2.0L turbo four-cylinder" },
		engineSuburban{ "1.5L turbocharged four-cylinder", "1.6L turbo four-cylinder" },
		exteriorFeatures{ "Illuminated Black bowtie emblem" , "Molded Black assist steps" , "Rear bumper protector", "2 - Bike T2 Classic Bicycle Carrier", "Deflectors in Chrome" , "Fender Flares" , "Roof Bicycle Carrier", "Black roof rack cross rails", "Black nameplates" },
		interiorFeatures{ "Collapsible cargo area organizer" , "Retractable cargo shade" , "Vertical cargo net" , "Premium all - weather floor mats",  "All - weather floor liners" , "All - weather cargo mat" , "Front window shade" },
		electronicFeatures{ "X-Connect 10-foot Extension Cable", "XGC4 Power Adapter", "B150 Boost Plus Battery Jump Starter", "Premium Thinkware F800 Dashcam", "Universal Tablet Holder with Integrated Power" },
		suvCost{ 2000000, 4000000 },
		exFeatureCost{ 16200, 45500, 10450 ,44100, 13300, 32900, 14900, 37600, 13900 },
		intFeatureCost{ 11600, 19900, 5600, 14900, 11000, 17500,  9900 },
		elecFeatureCost{ 1500, 3300, 2400, 29900, 11300 },
		myExteriorFeatures{ 0 },
		myInteriorFeatures{ 0 },
		myElectronicFeatures{ 0 }
	{
		model = 0;
		engine = '0';
	}
	void read();
	void readValue(const char* [], int, int[], int[]);
	void display();
	friend void displayValues(const char* [], int, int[]);
};
void SUV::read() {
	line(6);		space(8);		Sleep(500);
	cout << "C H E V R O L E T  S U V  M O D E L S" << endl;
	line(3);
	model = AutomobileFeatures::readValue(suvModels, 2);
	Billing::read(suvCost[(model - 1)]);

	cls();
	line(6);			space(8);			Sleep(500);
	switch (model) {
	case 1:
	{
		cout << "E Q U I N O X   E N G I N E S";
		line(4);
		engineInfo("es", "ee");
		line(3);		space(8);
		engine = engineChoice(engine, 1);
		break;
	}
	case 2:
	{
		cout << "S U B U R B A N   E N G I N E S";
		line(4);
		engineInfo("sus", "sue");
		line(3);		space(8);
		engine = engineChoice(engine, 3);
		break;
	}
	default: break;
	}

	cls();
	AutomobileFeatures::read();

	cls();
	line(6);		space(6);		Sleep(500);
	cout << "C L A S S I C   C H E V Y   S U V   E X T E R I O R   F E A T U R E S";
	line(4);
	readValue(exteriorFeatures, 9, myExteriorFeatures, exFeatureCost);
	cls();
	line(6);		space(6);		Sleep(500);
	cout << "C L A S S I C   C H E V Y   S U V   I N T E R I O R   F E A T U R E S";
	line(4);
	readValue(interiorFeatures, 7, myInteriorFeatures, intFeatureCost);
	cls();
	line(6);		space(6);		Sleep(500);
	cout << "C L A S S I C  C H E V Y  S U V  E L E C T R O N I C  F E A T U R E S";
	line(4);
	readValue(electronicFeatures, 5, myElectronicFeatures, elecFeatureCost);

	cls();
	Customer::read();
}
void SUV::readValue(const char* features[SIZE], int r, int chosenfeatures[SIZE], int prices[]) {
	int choice;
	int i, j = 0;
	for (i = 0; i < r; i++) {
		Sleep(200);		space(6);
		cout << setw(2) << right << i + 1 << "  " << setw(50) << left << features[i] << setw(14) << right << prices[i] << "/-" << endl;
	}
	line(4);   space(6);
	cout << "Press 0 after selection." << endl;
	while (1) {
		Sleep(300);  line(2);   space(6);
		cout << ">>>\t";
		cin >> choice;
		try {
			if (choice < 0 || choice > r || cin.fail())
				throw choice;
			if (choice == 0) {
				chosenfeatures[j] = BREAK;
				return;
			}
			*this += prices[choice - 1];
			chosenfeatures[j++] = choice;
		}
		catch (...) {
			displayInvalid();
		}
	}
}
void SUV::display() {

	//RECORDS STORAGE FILE
	ofstream records;
	records.open("clientRecords.txt", ios::out | ios::app);

	logo();
	if (!records) {
		line(6);	space(9); 	Sleep(300);
		cout << "ERROR: Data could not be stored.";
		Sleep(1000);
		exit(1);
	}

	records << endl << "CLIENT ID: #" << Customer::getClientID() << endl;

	line(3);	Sleep(300);		space(9);
	cout << "Chevrolet " << suvModels[model - 1] << endl;
	records << endl << setw(33) << right << "Chevrolet " << suvModels[model - 1] << endl;
	line(1);

	if (model == 1)
		chosenEngine(engine, "es");
	else
		chosenEngine(engine, "sus");


	AutomobileFeatures::display();

	line(3);	Sleep(300);		space(9);
	cout << "EXTERIOR FEATURES";
	records << "EXTERIOR FEATURES" << endl;
	line(1);
	displayValues(exteriorFeatures, 9, myExteriorFeatures);
	line(3);	Sleep(300);		space(9);
	cout << "INTERIOR FEATURES";
	records << endl << "INTERIOR FEATURES" << endl;
	line(1);
	displayValues(interiorFeatures, 7, myInteriorFeatures);
	line(3);	Sleep(300);		space(9);
	cout << "ELECTRONIC FEATURES";
	records << endl << "ELECTRONIC FEATURES" << endl;
	line(1);
	displayValues(electronicFeatures, 5, myElectronicFeatures);
	records.close();

	Billing::display();
	Customer::display();
}

class Truck : protected AutomobileFeatures
{
	const char* truckModels[SIZE];
	const char* engineColorado[SIZE];
	const char* engineSilverado[SIZE];
	const char* exteriorFeatures[SIZE];
	const char* interiorFeatures[SIZE];
	const char* electronicFeatures[SIZE];
	int truckCost[SIZE];
	int myExteriorFeatures[SIZE];
	int myInteriorFeatures[SIZE];
	int myElectronicFeatures[SIZE];
	int exFeatureCost[SIZE];
	int intFeatureCost[SIZE];
	int elecFeatureCost[SIZE];
	int model;
	char engine;
public:
	Truck() : AutomobileFeatures(), truckModels{ "Colorado", "Silverado" },
		engineColorado{ "1.5L turbo four-cylinder", "2.0L turbo four-cylinder" },
		engineSilverado{ "1.5L turbocharged four-cylinder", "1.6L turbo four-cylinder" },
		exteriorFeatures{ "Off - Road Black assist steps" , "Off - Road lighting" , "Rear wheelhouse liners" , "Cargo tie - downs" , "Cargo box LED lighting", "Illuminated Black bowtie emblem", "Rubber bed mat", "Bedliner with Storage Compartments", "Chrome Door Handle", "Roof Carriers" },
		interiorFeatures{ "Cupholder Illumination", "All - weather floor liners", "All - weather floor mats", "Sunshade Package", "Up-level rear seat with storage package", "Front and Rear floor liner" },
		electronicFeatures{ "Bose premium audio system", "Premium Thinkware F200 Dashcam", "Personal Device Electronic Cable", "XGC4 Power Adapter" },
		truckCost{ 2020000, 2200000 },
		exFeatureCost{ 55500, 34600, 14400, 9400, 11700, 13400, 10800, 31800, 10900, 36700 },
		intFeatureCost{ 24500, 14400, 12790, 9300, 25000, 17300 },
		elecFeatureCost{ 32000, 29500, 2500, 4100 },
		myExteriorFeatures{ 0 },
		myInteriorFeatures{ 0 },
		myElectronicFeatures{ 0 }
	{
		model = 0;
		engine = '0';
	}
	void read();
	void readValue(const char* [], int, int[], int[]);
	void display();
	friend void displayValues(const char* [], int, int[]);
};
void Truck::read() {
	line(6);		space(8);		Sleep(500);
	cout << "C H E V R O L E T  T R U C K  M O D E L S" << endl;
	line(3);
	model = AutomobileFeatures::readValue(truckModels, 2);
	Billing::read(truckCost[(model - 1)]);

	cls();
	line(6);			space(8);			Sleep(500);
	switch (model) {
	case 1:
	{
		cout << "C O L O R A D O   E N G I N E S";
		line(4);
		engineInfo("cos", "coe");
		line(3);		space(8);
		engine = engineChoice(engine, 2);
		break;
	}
	case 2:
	{
		cout << "S I L V E R A D O   E N G I N E S";
		line(4);
		engineInfo("ss", "se");
		line(3);		space(8);
		engine = engineChoice(engine, 3);
		break;
	}
	default: break;
	}

	cls();
	AutomobileFeatures::read();

	cls();
	line(6);		space(6);		Sleep(500);
	cout << "C L A S S I C   C H E V Y   T R U C K   E X T E R I O R   F E A T U R E S";
	line(4);
	readValue(exteriorFeatures, 10, myExteriorFeatures, exFeatureCost);
	cls();
	line(6);		space(6);		Sleep(500);
	cout << "C L A S S I C   C H E V Y   T R U C K   I N T E R I O R   F E A T U R E S";
	line(4);
	readValue(interiorFeatures, 6, myInteriorFeatures, intFeatureCost);
	cls();
	line(6);		space(6);		Sleep(500);
	cout << "C L A S S I C  C H E V Y  T R U C K  E L E C T R O N I C  F E A T U R E S";
	line(4);
	readValue(electronicFeatures, 4, myElectronicFeatures, elecFeatureCost);

	cls();
	Customer::read();
}
void Truck::readValue(const char* features[SIZE], int r, int chosenfeatures[SIZE], int prices[]) {
	int choice, j = 0;
	for (int i = 0; i < r; i++) {
		Sleep(200);		space(6);
		cout << setw(2) << right << i + 1 << "  " << setw(44) << left << features[i] << setw(24) << right << prices[i] << "/-" << endl;
	}
	line(4);   space(6);
	cout << "Press 0 after selection.";
	while (1) {
		Sleep(300);  line(2);   space(6);
		cout << ">>>\t";
		cin >> choice;
		try {
			if (choice < 0 || choice > r || cin.fail())
				throw choice;
			if (choice == 0) {
				chosenfeatures[j] = BREAK;
				return;
			}
			*this += prices[choice - 1];
			chosenfeatures[j++] = choice;
		}
		catch (...) {
			displayInvalid();
		}
	}
}
void Truck::display() {

	//RECORDS STORAGE FILE
	ofstream records;
	records.open("clientRecords.txt", ios::out | ios::app);

	logo();

	if (!records) {
		line(6);	space(9); 	Sleep(300);
		cout << "ERROR: Data could not be stored.";
		Sleep(1000);
		exit(1);
	}

	records << endl << "CLIENT ID: #" << Customer::getClientID() << endl;

	line(3);	Sleep(300);		space(9);
	cout << "Chevrolet " << truckModels[model - 1] << endl;
	records << endl << setw(33) << right << "Chevrolet " << truckModels[model - 1] << endl;
	line(1);
	if (model == 1)
		chosenEngine(engine, "cos");
	else
		chosenEngine(engine, "ss");

	AutomobileFeatures::display();

	line(3);	Sleep(300);		space(9);
	cout << "EXTERIOR FEATURES";
	records << "EXTERIOR FEATURES" << endl;
	line(1);
	displayValues(exteriorFeatures, 9, myExteriorFeatures);
	line(3);	Sleep(300);		space(9);
	cout << "INTERIOR FEATURES";
	records << endl << "INTERIOR FEATURES" << endl;
	line(1);
	displayValues(interiorFeatures, 7, myInteriorFeatures);
	line(3);	Sleep(300);		space(9);
	cout << "ELECTRONIC FEATURES";
	records << endl << "ELECTRONIC FEATURES" << endl;
	line(1);
	displayValues(electronicFeatures, 5, myElectronicFeatures);
	records.close();

	Billing::display();
	Customer::display();
}

int main() {

	mainMenu();

	_getch();
	return 0;
}

//FUNCTION DEFINITION
void mainMenu() {
	int entry;
	cls();
	line(6);	space(6);	character('\\', 29);	space(7); 	Sleep(300);
	cout << "C H E V R O L E T  A U T O M O B I L E S" << endl;
	space(6);	character('\\', 29);	line(3);	space(9);
	cout << "1. Client" << endl;
	space(9);
	cout << "2. Admin" << endl;
	space(9);
	cout << "3. Exit" << endl;

	while (1) {
		Sleep(500);   line(3);	space(8);
		cout << ">>>\t";
		cin >> entry;
		switch (entry) {
		case 1:
			load();
			chevroletClient();
			break;
		case 2:
			Admin manager;
			manager.login();
			break;
		case 3:
			cls();
			line(15);	space(7);	Sleep(500);
			cout << " T H A N K    Y O U   F O R   S T O P P I N G   B Y !";
			logo();
			line(20);
			exit(0);
		default:
			displayInvalid();
			break;
		}
	}
}

void load() {
	cls();
	line(30);		space(9);		Sleep(500);
	cout << " L O A D I N G ";
	Sleep(1000);
	character('.', 7);
	Sleep(100);
}

void logo() {
	line(6);	space(9); 	Sleep(300);
	cout << "C H E V R O L E T";
	line(2); space(10);
	cout << char(4);
	line(2); space(9);
	cout << "EST. " << setw(13) << "1911";
}

void displayInvalid() {
	cin.clear();
	cin.ignore(50, '\n');
	line(3);		space(9);	Sleep(500);
	cout << "INVALID CHOICE!";
}

void chevroletClient() {
	int automobile;
	cls();
	line(6);	space(6);	character('\\', 29);	space(7); 	Sleep(300);
	cout << "C H E V R O L E T  A U T O M O B I L E S" << endl;
	space(6);	character('\\', 29);	line(3);	space(9);
	cout << "1. Sedan" << endl;
	space(9);
	cout << "2. SUV" << endl;
	space(9);
	cout << "3. Truck" << endl;

	while (1) {
		Sleep(500);			line(3);			space(8);
		cout << ">>>\t";
		cin >> automobile;
		switch (automobile) {
		case 1:
		{
			Sedan client;
			cls();
			client.read();
			client.display();
			break;
		}
		case 2:
		{
			SUV client;
			cls();
			client.read();
			client.display();
			break;
		}
		case 3:
		{
			Truck client;
			cls();
			client.read();
			client.display();
			break;
		}
		default:
			displayInvalid();
			break;
		}
	}
}