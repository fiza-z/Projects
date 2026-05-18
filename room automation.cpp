#include<iostream>
#include<string>
using namespace std;

class Device {

private:
	string name;
	bool isOn;
	int brightness;

public:

	//constructors

	Device() {
		name = "Unknown";
		isOn = false;
		brightness = 50;
	}
	Device(string n , bool on , int brig) {
		name = n;
		isOn = on;
		brightness = brig;
	}

	//destructor

	~Device() {
		cout << "Device [" << name << "] is being removed."<<endl;
	}

	//setters and getters

	void setName(string n) {
		name = n;
	}
	string getName()const {
		return name;
	}
	void setBrightness(int b) {
		if (b >= 0 || b <= 100) {
			brightness = b;
		}
		else {
			cout << "Invalid"<<endl;
		}
	}
	int getBrightness() const {
		return brightness;
	}
	void turnOn() {
		isOn = true;
	}
	void turnOff() {
		isOn = false;
		}
	bool getStatus() {
			return isOn;
	}

	//display func

	void showInfo() const {
		cout << "Name: " << name << endl;
		cout << "Status: " << (isOn ? "ON" : "OFF") << endl;
		cout << "Brightness: "<< brightness << endl;
	}
};

class Room {

private:
	string roomName;
	Device devices[5];   //array of device obj
	int count;    //no of decives currently in room

public:

	//constructor
	Room(string name) {
		roomName = name;
		count = 0;
	}

	//destructor
	~Room() {
		cout << "Room [" << roomName << "] manager cosed"<<endl;
	}

	//functions
	void addDevice(Device d) {
		if (count < 5) {
			devices[count] = d;
			count++;
			cout << "Device Added." << endl;
		}
		else {
			cout << "No space in the room." << endl;
		}
	}
	void showAllDevices() const {
		if (count == 0) {
			cout << "No devices inside the room." << endl;
		}
		else
		{
			for (int i = 0; i < count; i++) {
				cout << "Device " << i + 1 << endl;
				devices[i].showInfo();
			}
		}
	}
	int findDevice(string name) {
		for (int i = 0; i < count; i++) {
			if (devices[i].getName() == name) {
				return i;
			}
			else {
				return -1;
			}
		}
	}
	void toggleDevice(string name) {
		for (int i = 0; i < count; i++) {
			if (devices[i].getName() == name) {
				if (devices[i].getStatus()) {
					devices[i].turnOff();
					cout << "Device [" << name << "] is turned off."<<endl;
				}

				else {
					devices[i].turnOn();
					cout << "Device [" << name << "] is turned on."<<endl;
				}
			}
		}
	}
	void setDeviceBrightness(string name, int brightness) {
		for (int i = 0; i < count; i++) {
			if (devices[i].getName() == name) {
					devices[i].setBrightness(brightness);
					cout << "Device " << name << "'s brightness is changed to " << brightness << ".";
				
			}
			else {
				cout << "Device not found.";
			}
		}
	}
};




int main() {
	string n;
	cout << "Enter room name: ";
	cin.ignore();
	getline(cin, n);
	Room r1(n);

	int choice;
	do {
		cout << "==== Smart Room Manager ==== \n 1. Add a Device \n 2. Show All Devices \n 3. Turn Device ON/OFF \n 4. Change Brightness \n 5. Exit" <<endl;
		cout << "Enter Choice: ";
		cin >> choice;
		if (cin.fail()) {
			cin.clear();                  // clear error
			cin.ignore(1000, '\n');       // discard wrong input
			cout << "Invalid input! Enter a number.\n";
			continue;                     // restart loop
		}
		if (choice >= 1 && choice <= 5) {
			switch (choice) {
			case 1: {
				string dName;
				int devbr;
				bool is;
				cout << "Enter device name: ";
				cin.ignore();
				getline(cin, dName);
				cout << "Enter device brightness: ";
				cin >> devbr;
				cout << "Is the device ON or OFF? (1 for ON, 0 for OFF): ";
				cin >> is;
				Device d(dName, is, devbr);
				r1.addDevice(d);
				break;
			}
			case 2: {
				r1.showAllDevices();
				break;
			}
			case 3: {
				string dName;
				cout << "Enter device name to turn ON/OFF: ";
				cin.ignore();
				getline(cin, dName);
				r1.toggleDevice(dName);
				break;
			}
			case 4: {
				string dName;
				int devbr;
				cout << "Enter device name to change brightness: ";
				cin.ignore();
				getline(cin, dName);
				cout << "Enter device brightness: ";
				cin >> devbr;
				r1.setDeviceBrightness(dName, devbr);
				break;
			}
			case 5: {
				cout << "Exiting Smart Room Manager.";
				break;
			}
			}
		}
		else {
			cout << "Invalid choice.";
		}
	} 
	while (choice != 5);
}