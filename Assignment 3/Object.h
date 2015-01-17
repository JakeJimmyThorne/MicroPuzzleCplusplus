#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>

class Object
{
public:
	Object();
	~Object();

	void SetUsed();
	bool IsUsed();

	void SetName(std::string newName);
	std::string GetName();
	
	void ToggleObtained();
	bool HasObtained();
	
private:
	std::string name;

	bool b_obtained;
	bool b_used;
};

#endif