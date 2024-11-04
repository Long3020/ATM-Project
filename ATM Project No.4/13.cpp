#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

const int ID_SIZE = 10;

const int PASSWORD_SIZE = 6;

const int ACCOUNTBALANCE_ARRAY_SIZE = 9;

int getInput1(string userInput) {
	while (userInput[0] < 49 || userInput[0] > 51 || userInput.length() > 1) {
		cout << "Wrong option! Please choose again: ";
		getline(cin, userInput);
	}
	return int(userInput[0]) - 48;
}

int getInput2(string userInput) {
	while (userInput[0] < 49 || userInput[0] > 53 || userInput.length() > 1) {
		if (userInput == "back" || userInput == "BACK" || userInput == "Back") return -1;
		cout << "Wrong option! Please choose again: ";
		getline(cin, userInput);
	}
	return int(userInput[0]) - 48;
}

bool validPassword(string password) {
	if (password.length() > PASSWORD_SIZE || password.length() < PASSWORD_SIZE) {
		return false;
	}
	int countPass = 0;
	for (int i = 0; i < PASSWORD_SIZE; i++) {
		if (password[i] < 48 || password[i] > 57) {
			countPass++;
		}
	}
	if (countPass != 0) return false;
	else return true;

}

bool validInfo(string password, string accountBalance, vector<string> friendlyAcc, int friendNumb) {
	if (password.length() > PASSWORD_SIZE || password.length() < PASSWORD_SIZE) {
		return false;
	}
	int countPass = 0;
	for (int i = 0; i < PASSWORD_SIZE; i++) {
		if (password[i] < 48 || password[i] > 57) {
			countPass++;
		}
	}
	if (countPass != 0) return false;

	if (accountBalance.length() > ACCOUNTBALANCE_ARRAY_SIZE) {
		return false;
	}
	int countAccBalance = 0;
	for (int i = 0; i < accountBalance.length(); i++) {
		if (accountBalance[i] < 48 || accountBalance[i] > 57) {
			countAccBalance++;
		}
	}
	if (countAccBalance != 0) return false;

	for (int i = 0; i < friendNumb; i++) {
		if (friendlyAcc[i].length() > ID_SIZE || friendlyAcc[i].length() < ID_SIZE) {
			return false;
		}
	}
	int countFriendAcc = 0;
	for (int i = 0; i < friendNumb; i++) {
		for (int j = 0; j < ID_SIZE; j++) {
			if (friendlyAcc[i][j] < 48 || (friendlyAcc[i][j] > 57 && friendlyAcc[i][j] < 65) || friendlyAcc[i][j] > 90) {
				countFriendAcc++;
			}
		}
	}
	if (countFriendAcc != 0) return false;
	else return true;

}

void read(string id, string& password, string& accountBalance, vector<string>& friendlyAcc, int& friendNumb) {
	string txt = ".txt";
	string fileName = id + txt;
	string friendlyAccName;
	ifstream readFile(fileName);
	readFile >> password >> accountBalance;
	while (readFile >> friendlyAccName) {
		friendlyAcc.push_back(friendlyAccName);
		friendNumb++;
	}
	readFile.close();
	bool valid = validInfo(password, accountBalance, friendlyAcc, friendNumb);
	if (valid == false) {
		cout << "Error in the main file! Please contact your developer to fix this.";
		exit(0);
	}

	for (int i = 0; i < friendNumb; i++) {
		string errorFileName = friendlyAcc[i] + txt;
		ifstream readErrorFile(errorFileName);
		if (!readErrorFile) {
			cout << "Your friend's account ID does not exist! Please contact your developer to fix this." << endl;
			readErrorFile.close();
			exit(0);
		}
		else readErrorFile.close();
	}
}

void update(string id, string& password, int& accountBalance, vector<string>& friendlyAcc, int& friendNumb) {
	string txt = ".txt";
	string fileName = id + txt;
	ofstream updateFile(fileName);
	updateFile << password << "\t" << accountBalance << endl;
	for (int i = 0; i < friendNumb; i++) {
		updateFile << friendlyAcc[i] << endl;
	}
	updateFile.close();
}

int stringToInt(string money) {
	int accountAmount = 0;
	for (int i = 0; i < money.length(); i++) {
		accountAmount += (int(money[i]) - 48) * pow(10, money.length() - i - 1);
	}
	return accountAmount;
}

string createID() {
	srand(time(0));
	while (true) {
		char id[10];
		for (int i = 0; i < 10; i++) {
			int random = rand();
			if (random % 2 == 0) id[i] = rand() % 10 + 48;
			else id[i] = rand() % 26 + 65;
		}
		string idName(id, 10);
		string txt = ".txt";
		string fileName = idName + txt;
		ifstream readFile(fileName);
		if (!readFile) {
			readFile.close();
			return idName;
		}
	}
}

string createPassword() {
	cout << "Enter your password (a positive 6 digits number): ";
	string password;
	getline(cin, password);
	while (true) {
		if (password == "back" || password == "BACK" || password == "Back") return password;;
		int count = 0;
		if (password.length() == PASSWORD_SIZE) {
			for (int i = 0; i < PASSWORD_SIZE; i++) {
				if (password[i] < 48 || password[i] > 57) {
					count++;
				}
			}
			if (count != 0) {
				cout << "Invalid password! Please enter again: ";
				getline(cin, password);
			}
			else break;
		}
		else {
			cout << "Invalid password! Please enter again: ";
			getline(cin, password);
		}
	}
	return password;
}

void createNewAccount() {
	string idName = createID();
	cout << "Your ID is: " << idName << endl;
	string password = createPassword();
	if (password == "back" || password == "BACK" || password == "Back") return;
	string txt = ".txt";
	string fileName = idName + txt;
	int initialBalance = 0;
	ofstream newAcc(fileName);
	newAcc << password << "\t" << initialBalance << endl;
	newAcc.close();
	cout << "Create account successfully!" << endl;
}

string checkID(string id) {
	string txt = ".txt";
	while (true) {
		string fileName = id + txt;
		ifstream readFile(fileName);
		if (!(readFile)) {
			if (id == "back" || id == "BACK" || id == "Back") return id;
			cout << "ID not found! Please try again: ";
			getline(cin, id);
		}
		else {
			readFile.close();
			break;
		}
	}
	return id;
}

string checkPassWord(string id, string password) {
	string txt = ".txt";
	string fileName = id + txt;
	string correctPassWord;
	ifstream readFile(fileName);
	readFile >> correctPassWord;
	readFile.close();
	bool validPass = validPassword(correctPassWord);
	if (validPass == false) {
		cout << "Error in the main file! Please contact your developer to fix this.";
		exit(0);
	}
	while (true) {
		if (correctPassWord != password) {
			if (password == "back" || password == "BACK" || password == "Back") return password;
			cout << "Your password is incorrect! Please try again: ";
			getline(cin, password);
		}
		else break;
	}
	return password;
}

string login() {
	cout << "What is your ID: ";
	string id;
	getline(cin, id);
	id = checkID(id);
	if (id == "back" || id == "BACK" || id == "Back") return id;
	cout << "What is your password: ";
	string password;
	getline(cin, password);
	password = checkPassWord(id, password);
	if (password == "back" || password == "BACK" || password == "Back") return password;
	return id;
}

void accountInfo(string id) {
	string password, accountBalance;
	vector<string> friendlyAcc;
	int friendNumb = 0;
	read(id, password, accountBalance, friendlyAcc, friendNumb);
	cout << "Account ID: " << id << "\nAccount Balance: " << accountBalance << endl;
	if (friendNumb == 0) cout << "You have no friendly account." << endl;
	else {
		cout << "Friendly account list:" << endl;
		for (int i = 0; i < friendNumb; i++) {
			cout << friendlyAcc[i] << endl;
		}
	}
}

int getWithdrawMoney(string withdrawMoney) {
	int count;
	while (true) {
		count = 0;
		for (int i = 0; i < withdrawMoney.length(); i++) {
			if (withdrawMoney[i] < 48 || withdrawMoney[i] > 57 || withdrawMoney.length() > ACCOUNTBALANCE_ARRAY_SIZE) {
				count++;
			}
		}
		if (count != 0) {
			if (withdrawMoney == "back" || withdrawMoney == "BACK" || withdrawMoney == "Back") return -1;
			cout << "Invalid amount of money! Please try again: ";
			getline(cin, withdrawMoney);
		}
		else break;
	}
	int withdrawAmount = stringToInt(withdrawMoney);
	return withdrawAmount;
}

void withdraw(string id, int userOption) {
	string password, accountBalance;
	vector<string> friendlyAcc;
	int friendNumb = 0;
	read(id, password, accountBalance, friendlyAcc, friendNumb);
	int accountAmount = stringToInt(accountBalance);
	if (userOption == 1) {
		if (accountAmount - 10 < 0) cout << "Not enough money!" << endl;
		else {
			accountAmount -= 10;
			cout << "Withdraw successfully!" << endl;
		}
	}
	else if (userOption == 2) {
		if (accountAmount - 20 < 0) cout << "Not enough money!" << endl;
		else {
			accountAmount -= 20;
			cout << "Withdraw successfully!" << endl;
		}
	}
	else if (userOption == 3) {
		if (accountAmount - 50 < 0) cout << "Not enough money!" << endl;
		else {
			accountAmount -= 50;
			cout << "Withdraw successfully!" << endl;
		}
	}
	else if (userOption == 4) {
		if (accountAmount - 100 < 0) cout << "Not enough money!" << endl;
		else {
			accountAmount -= 100;
			cout << "Withdraw successfully!" << endl;
		}
	}
	else {
		cout << "How much money do you want to withdraw? ";
		string withdrawMoney;
		getline(cin, withdrawMoney);
		int withdrawAmount = getWithdrawMoney(withdrawMoney);
		if (withdrawAmount == -1) return;
		if (accountAmount - withdrawAmount < 0) cout << "Not enough money!" << endl;
		else {
			accountAmount -= withdrawAmount;
			cout << "Withdraw successfully!" << endl;
		}
	}
	update(id, password, accountAmount, friendlyAcc, friendNumb);
}

int getDepositMoney(string depositMoney, string id) {
	string password, accountBalance;
	vector<string> friendlyAcc;
	int friendNumb = 0;
	read(id, password, accountBalance, friendlyAcc, friendNumb);
	int accountAmount = stringToInt(accountBalance);
	int count;
	while (true) {
		count = 0;
		for (int i = 0; i < depositMoney.length(); i++) {
			if (depositMoney[i] < 48 || depositMoney[i] > 57 || depositMoney.length() > ACCOUNTBALANCE_ARRAY_SIZE) count++;
		}
		if (count != 0) {
			if (depositMoney == "back" || depositMoney == "BACK" || depositMoney == "Back") return -1;
			cout << "Invalid amount of money! Please try again: ";
			getline(cin, depositMoney);
		}
		else break;
	}
	int depositAmount = stringToInt(depositMoney);
	if (depositAmount + accountAmount >= pow(10, 9)) {
		cout << "You can't have more than 99999999(money) in your account!" << endl;;
		return -1;
	}
	return depositAmount;
}

void deposit(string id) {
	cout << "How much money do you want to deposit: ";
	string depositMoney;
	getline(cin, depositMoney);
	int depositAmount = getDepositMoney(depositMoney, id);
	if (depositAmount == -1) return;
	else {
		string password, accountBalance;
		vector<string> friendlyAcc;
		int friendNumb = 0;
		read(id, password, accountBalance, friendlyAcc, friendNumb);
		int accountAmount = stringToInt(accountBalance);
		accountAmount += depositAmount;
		update(id, password, accountAmount, friendlyAcc, friendNumb);
		cout << "Deposit successfully!" << endl;
	}
}

int transferOption(string userOption, int friendNumb) {
	while (true) {
		int count = 0;
		for (int i = 0; i < userOption.length(); i++) {
			if (userOption[i] < 48 || userOption[i] > 57 || userOption.length() > 1 || (userOption.length() == 1 && userOption[0] == 48)) count++;
		}
		if (count != 0) {
			if (userOption == "back" || userOption == "BACK" || userOption == "Back") return -1;
			cout << "Invalid number! Please try again: ";
			getline(cin, userOption);
		}
		else {
			while (true) {
				int validUserOption = stringToInt(userOption);
				if (validUserOption > friendNumb + 1) {
					if (userOption == "back" || userOption == "BACK" || userOption == "Back") return -1;
					cout << "Invalid number! Please try again: ";
					getline(cin, userOption);
				}
				else return validUserOption;
			}

		}
	}
}

bool getTransferMoney(string transferMoney, string id, string transferID) {
	while (true) {
		if (transferMoney == "back" || transferMoney == "BACK" || transferMoney == "Back") return false;
		int count = 0;
		for (int i = 0; i < transferMoney.length(); i++) {
			if (transferMoney[i] < 48 || transferMoney[i] > 57 || transferMoney.length() > ACCOUNTBALANCE_ARRAY_SIZE) count++;
		}
		if (count != 0) {
			cout << "Invalid number! Please try again: ";
			getline(cin, transferMoney);
		}
		else break;
	}
	int transferAmount = stringToInt(transferMoney);
	string password, accountBalance;
	vector<string> friendlyAcc;
	int friendNumb = 0;
	read(id, password, accountBalance, friendlyAcc, friendNumb);
	int accountAmount = stringToInt(accountBalance);
	if (transferAmount > accountAmount) {
		cout << "Not enough money!" << endl;
		return false;
	}
	else {
		string transferPassword, transferAccountBalance;
		vector<string> transferFriendlyAcc;
		int transferFriendNumb;
		read(transferID, transferPassword, transferAccountBalance, transferFriendlyAcc, transferFriendNumb);
		int transferAccountAmount = stringToInt(transferAccountBalance);
		if (transferAmount + transferAccountAmount >= pow(10, 9)) {
			cout << "Too much money for the transfer account!" << endl;
			return false;
		}
		else {
			transferAccountAmount += transferAmount;
			accountAmount -= transferAmount;
			update(id, password, accountAmount, friendlyAcc, friendNumb);
			update(transferID, transferPassword, transferAccountAmount, transferFriendlyAcc, transferFriendNumb);
			return true;
		}
	}
}

void transferOtherAcc(string id, string password, int accountAmount, vector<string> friendlyAcc, int friendNumb) {
	cout << "Enter the ID of the transfer account: ";
	string transferID;
	getline(cin, transferID);
	transferID = checkID(transferID);
	if (transferID == "back" || transferID == "BACK" || transferID == "Back") return;
	while (transferID == id) {
		cout << "This is your ID! Please enter the transfer ID: ";
		getline(cin, transferID);
		transferID = checkID(transferID);
		if (transferID == "back" || transferID == "BACK" || transferID == "Back") return;
	}
	string transferPassword, transferAccountBalance;
	vector<string> transferFriendlyAcc;
	int transferCount = 0;
	read(transferID, transferPassword, transferAccountBalance, transferFriendlyAcc, transferCount);
	cout << "Do you want to save this account to your friendly list? (Y/y for yes and N/n for no) ";
	string saveOrNot;
	getline(cin, saveOrNot);
	while (true) {
		if (saveOrNot == "Y" || saveOrNot == "y") {
			friendlyAcc.push_back(transferID);
			friendNumb++;
			break;
		}
		else if (saveOrNot == "N" || saveOrNot == "n") break;
		else if (saveOrNot == "back" || saveOrNot == "BACK" || saveOrNot == "Back") return;
		else {
			cout << "Invalid option! Please try again: ";
			getline(cin, saveOrNot);
		}
	}
	update(id, password, accountAmount, friendlyAcc, friendNumb);
	cout << "How much amount of money do you want to transfer: ";
	string transferMoney;
	getline(cin, transferMoney);
	bool transferSuccess = getTransferMoney(transferMoney, id, transferID);
	if (transferSuccess == false) return;
	else cout << "Transfer successfully!" << endl;
}

void transfer(string id) {
	string password, accountBalance;
	vector<string> friendlyAcc;
	int friendNumb = 0;
	read(id, password, accountBalance, friendlyAcc, friendNumb);
	int accountAmount = stringToInt(accountBalance);
	if (friendNumb != 0) {
		cout << "Here is the list of your friendly account: " << endl;
		for (int i = 0; i < friendNumb + 1; i++) {
			if (i == friendNumb) cout << friendNumb + 1 << ". Other\nYour option: ";
			else cout << i + 1 << ". " << friendlyAcc[i] << endl;
		}
		string userOption;
		getline(cin, userOption);
		int transferAccOption = transferOption(userOption, friendNumb);
		if (transferAccOption == friendNumb + 1) {
			transferOtherAcc(id, password, accountAmount, friendlyAcc, friendNumb);
		}
		else if (transferAccOption == -1) return;
		else {
			cout << "How much amount of money do you want to transfer: ";
			string transferMoney;
			getline(cin, transferMoney);
			bool transferSuccess = getTransferMoney(transferMoney, id, friendlyAcc[transferAccOption - 1]);
			if (transferSuccess == false) return;
			cout << "Transfer successfully!" << endl;
		}
	}
	else {
		cout << "You have no friendly account." << endl;
		transferOtherAcc(id, password, accountAmount, friendlyAcc, friendNumb);
	}
}

int main()
{
	string userInput1, loginID;
	bool flag = true;
	while (true) {
		flag = true;
		cout << "--ATM MENU--\n1. Login\n2. Create new account\n3. Exit\nType \"back\" or \"BACK\" or \"Back\" to go back to the previous option.\nYour option : ";
		getline(cin, userInput1);
		int userOption1 = getInput1(userInput1);
		switch (userOption1) {
		case 1:
			loginID = login();
			if (loginID == "back" || loginID == "BACK" || loginID == "Back") break;
			while (flag) {
				cout << "1. Account Information\n2. Withdraw Money\n3. Deposit Money\n4. Transfer Money\n5. Log out\nYour Option: ";
				string userInput2, userInput3;
				getline(cin, userInput2);
				int userOption2 = getInput2(userInput2);
				if (userOption2 == -1) break;
				int userOption3;
				switch (userOption2) {
				case 1:
					accountInfo(loginID);
					break;
				case 2:
					cout << "1. 10\n2. 20\n3. 50\n4. 100\n5. Other\nYour Option: ";
					getline(cin, userInput3);
					userOption3 = getInput2(userInput3);
					if (userOption3 == -1) break;
					switch (userOption3) {
					case 1:
						withdraw(loginID, userOption3);
						break;
					case 2:
						withdraw(loginID, userOption3);
						break;
					case 3:
						withdraw(loginID, userOption3);
						break;
					case 4:
						withdraw(loginID, userOption3);
						break;
					case 5:
						withdraw(loginID, userOption3);
						break;
					}
					break;
				case 3:
					deposit(loginID);
					break;
				case 4:
					transfer(loginID);
					break;
				case 5:
					flag = false;
				}
			}
			break;
		case 2:
			createNewAccount();
			break;
		case 3:
			exit(0);
		}
	}

	return 0;
}