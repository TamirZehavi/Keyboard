//Main

#include "Keyboard.h"

void PrintMenu();
bool SetNumLang(int num_lang);
bool SetNumSpecialKeys(int num_special_keys);
void Menu(Keyboard &keyboard);


int main()
{
	int num_lang, num_regular_keys, num_special_keys;

	cout << "Please enter how many languages you want to have:" << endl;
	cin >> num_lang;

	while (!SetNumLang(num_lang))
	{
		cout << "Error. Please try again: " << endl;
		cin >> num_lang;
	}

	cout << "Please enter how many special keys you want to have:" << endl;
	cin >> num_special_keys;

	while (!SetNumSpecialKeys(num_special_keys))
	{
		cin >> num_special_keys;
	}

	cout << "Please enter how many reguler keys you want to have:" << endl;
	cin >> num_regular_keys;

	int num_keys=num_regular_keys + num_special_keys;

	system("pause");
	system("cls");

	Keyboard keyboard(num_lang,num_special_keys,num_keys);

	Menu(keyboard);

	system("cls");

	return 0;
}

void PrintMenu()
{
	cout << "----------TESTER MENU---------- :" << endl;
	cout << "[a|A] - Show all keys information;" << endl;
	cout << "[s|S] - Show only special keys information;" << endl;
	cout << "[r|R] - Replace a special key;" << endl;
	cout << "[p|P] - Press on a key;" << endl;
	cout << "[k|K] - Show key information;" << endl;
	cout << "[o|O] - Show currently pressed keys;" << endl;
	cout << "[h|H] - Print this menu again;" << endl;
}

bool SetNumLang(int num_lang)
{
	if (num_lang >= MIN_LANG && num_lang <= MAX_LANG)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool SetNumSpecialKeys(int num_special_keys)
{
	if (num_special_keys >= MIN_SPECIAL_KEYS && num_special_keys <= MAX_SPECIAL_KEYS)
	{
		return true;
	}
	else
	{
		cout << "Error. Special keys out of bounds. Try again." << endl;
		return false;
	}
}

void Menu(Keyboard &keyboard)
{

	char menu;
	int key_code;

	while (!(keyboard.GetKeys()[2]->GetIsPressed()))
	{
		PrintMenu();
		cin >> menu;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		switch (menu)
		{
		case 'a':
		case 'A':
			keyboard.print_keys();
			system("pause");
			system("cls");
			break;

		case 's':
		case 'S':
			keyboard.print_special_keys();
			system("pause");
			system("cls");
			break;

		case 'r':
		case 'R':
			keyboard.print_special_keys();
			cout << "Enter key code: " << endl;
			cin >> key_code;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (keyboard.find(key_code) == -1)//If the key is not present, break
			{
				cout << "Couldn't identify key" << endl;
				system("pause");
				system("cls");
				break;
			}
			else if (!keyboard.GetKeys()[keyboard.find(key_code)]->GetShiftabe() )//if the key IS present, check if it's special
			{
				system("cls");

				string value;
				string description;

				cout << "Please enter special key value, seperated by white space: " << endl;
				getline(cin, value);

				cout << "Please enter special key description: " << endl;
				getline(cin, description);

				Key temp_key(value.c_str(), key_code, false, description.c_str());

				cout << "Success!" << endl;

				keyboard.replace_special_key(temp_key, (*keyboard.GetKeys()[keyboard.find(key_code)]));
				keyboard.print_special_keys();
				system("pause");
				system("cls");
				break;
			}
			else
			{
				cout << "Incorrect key. Try again" << endl;
				system("pause");
				system("cls");
				break;
			}

		case 'p':
		case 'P':
			keyboard.print_keys();
			cout << "Enter key code: " << endl;
			cin >> key_code;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (keyboard.find(key_code) == -1)
			{
				cout << "Couldn't identify key" << endl;
				system("pause");
				system("cls");
				break;
			}
			else
			{
				if (keyboard.GetKeys()[keyboard.find(key_code)]->GetIsPressed())//if it's pressed make it unpressed
				{
					keyboard.GetKeys()[keyboard.find(key_code)]->SetIsPressed(false);
					keyboard.GetKeys()[keyboard.find(key_code)]->print();
					system("pause");
					system("cls");
					break;
				}

				else
				{
					keyboard.GetKeys()[keyboard.find(key_code)]->SetIsPressed(true);//if it's not pressed make it pressed
					keyboard.GetKeys()[keyboard.find(key_code)]->print();
					system("pause");
					system("cls");
					break;
				}
			}

		case 'k':
		case 'K':
			keyboard.print_keys();
			cout << "Enter key code: " << endl;
			cin >> key_code;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (keyboard.find(key_code) == -1)
			{
				cout << "Couldn't identify key" << endl;
				system("pause");
				system("cls");
				break;
			}
			else
			{
				keyboard.GetKeys()[keyboard.find(key_code)]->print();
				system("pause");
				system("cls");
				break;
			}

		case 'o':
		case 'O':
			keyboard.print_pressed_keys();
			system("pause");
			system("cls");
			break;

		case 'h':
		case 'H':
			system("cls");
			break;
		}
	}
}

