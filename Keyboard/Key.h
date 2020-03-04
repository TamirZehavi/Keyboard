//Key.h

#pragma once

#include <iostream>
#include <string.h>
#include <string>
#include <cassert>

using namespace std;

#define MAXLEN 30


class Key
{
private:
	char values[MAXLEN];
	unsigned int const key_code;
	bool is_shiftable;
	char*description;
	bool is_pressed;

public:

	//constructors & destructors:

	Key();
	Key(const char* values, unsigned int key_code, bool is_shiftable, const char* description);
	Key(const Key&);
	~Key();

	//getters:

	char* GetValue() { return this->values; } 
	unsigned int getKeyCode() const { return this->key_code; }
	bool GetShiftabe() const { return this->is_shiftable; }
	char* GetDescription() const { return this->description; }
	bool GetIsPressed() const { return this->is_pressed; }

	//setters:

	bool SetValues(const char*);
	void SetShiftable(bool);
	void SetDescription(const char*);
	void SetIsPressed(bool);

	//functions:

	void print() const;

};

