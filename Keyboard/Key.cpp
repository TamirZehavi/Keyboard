//Key.cpp

#include "Key.h"

//constructors & destructors:

Key::Key() 
	:key_code(0)
{
	for (int i = 0; i < MAXLEN; i++)
		this->values[i] = '0';

	this->is_shiftable = false;

	this->description = new char[4] {"---"};

	if (!this->description)
	{
		cout << "Ran out of RAM" << endl;
		exit(1);
	}

	this->is_pressed = false;
}

Key::Key(const char* values, unsigned int key_code, bool is_shiftable, const char* description)
	:key_code(key_code)
{
	this->SetIsPressed(false);

	while (!this->SetValues(values))
	{
		cout << "Value out of bounds. Setting to default" << endl;
		system("pause");
		this->SetValues("Default value");
		break;
	}

	this->SetShiftable(is_shiftable);

	this->SetDescription(description);
}

Key::Key(const Key&other)
	:key_code(other.key_code)
{
	this->SetIsPressed(other.is_pressed);
	this->SetValues(other.values);
	this->SetShiftable(other.is_shiftable);
	this->SetDescription(other.description);
}

Key::~Key()
{
	//cout << "DESTRUCTION" << endl;
	if (this->description)
	{
		delete[] this->description;
	}
}

//setters:

bool Key::SetValues(const char*values)
{
	int value_length = strlen(values);
	if(value_length<MAXLEN)
	{
		strcpy_s(this->values, value_length + 1, values);
		return true;
	}
	else
	{
		return false;
	}
	
}

void Key::SetShiftable(bool is_shiftable)
{
	this->is_shiftable = is_shiftable;
}
void Key::SetDescription(const char* description)
{
	int word_length = strlen(description);
	this->description = new char[word_length + 1];

	if (!this->description)
	{
		cout << "Ran out of RAM" << endl;
		exit(2);
	}

	strcpy_s(this->description, word_length + 1, description);
}

void Key::SetIsPressed(bool is_pressed)
{
	this->is_pressed = is_pressed;
}

//functions:

void Key::print() const
{
	cout << "Key value: " << this->values << "-------";
	cout << "Key code: " << this->key_code << "-------";
	if (this->is_shiftable)
		cout << "Special key: no" << "-------";
	else cout << "Special key: yes" << "-------";
	if (this->is_pressed)
		cout << "Key pressed: yes" << "-------";
	else cout << "Key pressed: no" << "-------";
	cout << "Key dscreption: " << this->description << endl;
}

