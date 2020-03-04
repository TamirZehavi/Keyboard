//Keyboard.h

#pragma once

#include "Key.h"

#define MAX_LANG 3
#define MIN_LANG 1
#define MAX_SPECIAL_KEYS 4
#define MIN_SPECIAL_KEYS 0
#define MAX_KEYS 101
#define MIN_KEYS 1
#define DEFAULT_LANGUAGE "English"

using namespace std;

class Keyboard
{
private:

	char**languages;
	const int num_lang;
	Key** keys;
	int num_keys;
	const int num_special_keys;

public:

	//constructors destructors:

	Keyboard();
	Keyboard(int num_lang, int num_special_keys, int num_keys);
	Keyboard(const Keyboard&other);
	~Keyboard();

	//getters:

	char**GetLanguages()const { return languages; }
	int GetNumLang() const { return num_lang; }
	Key**GetKeys() const { return keys; }
	int GetNumkeys() const { return num_keys; }
	int GetNumSpecialKeys() const { return num_special_keys; }

	//setters:

	void SetLangueges();
	void SetKeys(int num_keys);
	bool SetNumKeys(int);

	//functions:

	void print_keys() const;
	void print_pressed_keys() const;
	void print_special_keys() const;
	bool add_language(const char*language);
	bool remove_language(int index);
	bool add_key(Key key);
	bool replace_special_key(Key src, Key target);
	int find(int key_code) const;

	//Validations:

	static bool IsKeyCodeValid(unsigned int, bool);
};

