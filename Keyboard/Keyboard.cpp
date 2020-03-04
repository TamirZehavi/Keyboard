//Keyboard.cpp

#include "Keyboard.h"

//CONSTRUCTORS DESTRUCTORS:

Keyboard::Keyboard(int num_lang, int num_special_keys, int num_keys)
	:num_lang(num_lang), num_special_keys(num_special_keys)
{
	while (!this->SetNumKeys(num_keys))
		cin >> num_keys;
	this->SetLangueges();
	this->SetKeys(num_keys);
}


Keyboard::Keyboard()
	:num_lang(1),num_special_keys(0)
{
	this->SetLangueges();
	this->num_keys = 0; //If I'll use a setter I'll get an error for zero keys. The Setkeys function will define the four default keys for me.
	this->SetKeys(0);
}

Keyboard::Keyboard(const Keyboard&other)
	:num_lang(other.num_lang),num_special_keys(other.num_special_keys)
{
	this->SetLangueges();
	this->SetNumKeys(other.num_keys);
	this->SetKeys(other.num_keys);
}


Keyboard::~Keyboard()
{
	if (this->keys)
	{
		delete[]this->keys;
	}

	if (this->languages)
	{
		for (int i = 0; i < this->num_lang; i++)
			delete[]this->languages[i];

		delete[] this->languages;
	}
}


//FUNCTIONS:


void Keyboard::SetLangueges()
{
	this->languages = new char*[this->num_lang]{ nullptr };

	//First you gotta define how many words u wanna have. num_lang will be the number of arrays.

	assert(this->languages!=NULL);

	this->languages[0] = new char[strlen(DEFAULT_LANGUAGE) + 1];

	assert(languages[0] != NULL);

	strcpy_s(this->languages[0], strlen(DEFAULT_LANGUAGE) + 1, DEFAULT_LANGUAGE);

	//setting up default language as English

	for (int i = 1; i < this->num_lang; i++)//Then for as how many languages you've inserted you'll allocate memory
	{
		cout << "Enter Language " << i+1 << " :"<< endl;
		char tmp[30]{0};

		cin >> tmp;

		add_language(tmp);
	}

	system("cls");

	cout << "Languages:" << endl;

	for (int i = 0; i < num_lang; i++)
	{
		cout << i + 1 << ". " << languages[i] << endl;
	}

	system("pause");
}


void Keyboard::SetKeys(int num_keys)
{
	if (this->num_lang == 1)// If there's only one language, I'll need the 123 key
	{
		this->keys = new Key*[num_keys + 4] {NULL};
		assert(this->keys !=NULL);

		this->keys[0] = new Key("123", 1, false, "123");
		assert(this->keys[0] != NULL);

		this->keys[1] = new Key("SHIFT", 2, true, "SHIFT");
		assert(this->keys[1] != NULL);

		this->keys[2] = new Key("ESCAPE", 3, true, "ESCAPE");
		assert(this->keys[2] != NULL);

		this->keys[3] = new Key("CONTROL", 4, true, "CONTROL");
		assert(this->keys[3] != NULL);

		print_keys();

		cout << endl << "Special keys: " << endl << endl;

		for (int i = 4; i < this->num_special_keys + 4; i++)//add special keys
		{
			string value;
			string description;
			int key_code;
			bool is_shiftable = false;//special key is not shiftable

			cout << "Please enter special key code: " << endl;
			cin >> key_code;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			while (!IsKeyCodeValid(key_code, is_shiftable) || (find(key_code) != -1))
			{
				if ((find(key_code) != -1))
					cout << "Key already exists!" << endl;
				cin >> key_code;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

			cout << "Please enter special key value, seperated by white space: " << endl;
			getline(cin, value);

			cout << "Please enter special key description: " << endl;
			getline(cin, description);

			Key specialKey(value.c_str(), key_code, is_shiftable, description.c_str());

			add_key(specialKey);
			system("cls");
		}

		print_keys();
		system("pause");
		system("cls");

		cout << "Normal keys: " << endl;

		for (int i = 4 + this->num_special_keys; i < num_keys + 4; i++)//add normal keys
		{
			char answer = 'n';
			while (answer != 'y'&&answer != 'Y')
			{
				string value;
				string description;
				int key_code;
				bool is_shiftable(true);//regular key is shiftable

				cout << "Please enter key code: " << endl;
				cin >> key_code;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				while (!IsKeyCodeValid(key_code, is_shiftable) || (find(key_code) != -1))
				{
					if ((find(key_code) != -1))
						cout << "Key already exists!" << endl;
					cin >> key_code;
				}

				cout << "Please enter special key value, seperated by white space: " << endl;
				cin.ignore();
				getline(cin, value);

				cout << "Please enter key description: " << endl;
				cin.ignore();
				getline(cin, description);

				Key normalKey(value.c_str(), key_code, is_shiftable, description.c_str());

				system("cls");
				normalKey.print();
				cout << "Please press 'y' to confirm your new key" << endl;
				cin >> answer;

				if (answer == 'y')
				{
					add_key(normalKey);
					system("cls");
				}

				system("cls");
				cout << endl;
			}

		}

	}

	else //If there's more than one language I won't need 123 key
	{
		this->keys = new Key*[num_keys+3] { NULL };
		assert(this->keys != NULL);

		//default keys:

		cout << "Setting default keys:" << endl << endl;

		this->keys[0] = new Key("SHIFT", 1, true, "SHIFT");
		assert(this->keys[0] != NULL);

		this->keys[1] = new Key("CONTROL", 2, true, "CONTROL");
		assert(this->keys[1] != NULL);

		this->keys[2] = new Key("ESCAPE", 3, true, "ESCAPE");
		assert(this->keys[2] != NULL);

		print_keys();

		cout << endl << "Special keys: " << endl << endl;

		for (int i = 3; i < this->num_special_keys + 3; i++)//add special keys
		{
			string value;
			string description;
			int key_code;
			bool is_shiftable = false;//special key is not shiftable

			cout << "Please enter special key code: " << endl;
			cin >> key_code;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			while (!IsKeyCodeValid(key_code, is_shiftable) || (find(key_code) != -1))
			{
				if ((find(key_code) != -1))
					cout << "Key already exists!" << endl;
				cin >> key_code;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

			cout << "Please enter special key value, seperated by white space: " << endl;
			getline(cin, value);

			cout << "Please enter special key description: " << endl;
			getline(cin, description);

			Key specialKey(value.c_str(), key_code, is_shiftable, description.c_str());

			add_key(specialKey);
			system("cls");
		}

		print_keys();
		system("pause");
		system("cls");

		cout << "Normal keys: " << endl;

		for (int i = 3 + this->num_special_keys; i < num_keys+3; i++)//add normal keys
		{
			char answer = 'n';
			while (answer != 'y'&&answer != 'Y')
			{
				string value;
				string description;
				int key_code;
				bool is_shiftable(true);//regular key is shiftable

				cout << "Please enter key code: " << endl;
				cin >> key_code;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				while (!IsKeyCodeValid(key_code, is_shiftable) || (find(key_code) != -1))
				{
					if ((find(key_code) != -1))
						cout << "Key already exists!" << endl;
					cin >> key_code;
				}

				cout << "Please enter special key value, seperated by white space: " << endl;
				cin.ignore();
				getline(cin, value);

				cout << "Please enter key description: " << endl;
				cin.ignore();
				getline(cin, description);

				Key normalKey(value.c_str(), key_code, is_shiftable, description.c_str());

				system("cls");
				normalKey.print();
				cout << "Please press 'y' to confirm your new key" << endl;
				cin >> answer;

				if (answer == 'y')
				{
					add_key(normalKey);
					system("cls");
				}

				system("cls");
				cout << endl;
			}

		}
	}
		
}

bool Keyboard::SetNumKeys(int num_keys)
{
	if (num_keys>= MIN_KEYS && num_keys <= MAX_KEYS)
	{
		this->num_keys = num_keys;
		return true;
	}
	else
	{
		cout << "Error: Number of keys out of bounds. try again." << endl;
		return false;
	}
}

//functions:

void Keyboard::print_keys() const
{
	int total_keys = this->num_keys+3;
	if (this->num_lang == 1)
		total_keys++;
	for (int i = 0; i < total_keys; i++)
	{
		if (!this->keys[i])//If key is not yet initiallized don't attempt to print an empty key
			break;
		this->keys[i]->print();
	}
}

void Keyboard::print_pressed_keys() const
{
	int total_keys = this->num_keys+3;
	if (this->num_lang == 1)
		total_keys++;
	for (int i = 0; i < total_keys; i++)
	{
		if (this->keys[i]->GetIsPressed())
			this->keys[i]->print();
	}
}

bool Keyboard::add_language(const char*language)
{
	static int index = 1;
	if (!this->languages[index])//If this index in the language array is empty then insert language
	{
		this->languages[index] = new char[strlen(language) + 1];
		strcpy_s(this->languages[index], strlen(language) + 1, language);
		index++;
		return true;
	}
	else return false;
}

bool Keyboard::remove_language(int index)
{
	if (index >= 1 && index <= 3)
	{
		if (this->languages[index]!=NULL && index < num_lang)
		{
			delete this->languages[index];
			this->languages[index] = new char[strlen("EMPTY") + 1];
			strcpy_s(this->languages[index], strlen("EMPTY") + 1, "EMPTY");
			return true;
		}
		else return false;
	}
	else return false;
}

bool Keyboard::add_key(Key key)
{
	if (num_lang == 1)
	{
		static int index = 4;
		if (!this->keys[index]) //If the current index is empty, than insert key
		{
			this->keys[index] = new Key(key);
			index++;
			return true;
		}
		else return false;
	}
	else
	{
	static int index=3;
	if (!this->keys[index]) //If the current index is empty, than insert key
	{
		this->keys[index] = new Key(key);
		index++;
		return true;
	}
	else return false;
	}
}

bool Keyboard::replace_special_key(Key src, Key target)
{
	if (src.getKeyCode() == target.getKeyCode())
	{
		this->keys[this->find(target.getKeyCode())] =  new Key(src);
		return true;
	}
	else
	{
		cout << "Not the same key_code. Cannot switch." << endl;
		return false;
	}
}

int Keyboard::find(int key_code) const
{
	int total_keys = this->num_keys + 3;
	if (this->num_lang == 1)
		total_keys++;
	for (int i = 0; i < total_keys; i++)
	{
		if (!this->keys[i])//do not check if a key is uninitiallized 
			break;
		if ((*this->keys[i]).getKeyCode() == key_code)
		{
			return i;
		}
	}
	return -1;
}

void Keyboard::print_special_keys() const 
{
	int total_keys = this->num_keys + 3;
	if (this->num_lang == 1)
		total_keys++;
	for (int i = 0; i < total_keys; i++)
	{
		if (!(this->keys[i]->GetShiftabe()))
		{
			this->keys[i]->print();
		}
	}
}

//Validations:

bool Keyboard::IsKeyCodeValid(unsigned int key_code, bool is_shiftable)
{
	if (is_shiftable)
	{
		if (key_code > 0 && key_code < 200)
		{
			return true;
		}
		else
		{
			cout << "Invalid key code. Try again" << endl;
			return false;
		}
	}
	else if (!(is_shiftable))
	{
		if (key_code >= 200 && key_code <= 203)
		{
			return true;
		}
		else
		{
			cout << "Invalid key code. Try again." << endl;
			return false;
		}
	}
	return false;
}

