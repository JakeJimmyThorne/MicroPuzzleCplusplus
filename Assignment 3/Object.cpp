#include "Object.h"

Object::Object()
{
	b_obtained = false;
	b_used = false;
	name = "";
}

Object::~Object()
{

}

void Object::SetUsed()
{
	b_used = true;
	return;
}
bool Object::IsUsed()
{
	return b_used;
}

void Object::SetName(std::string newName)
{
	name = newName;
	return;
}
std::string Object::GetName()
{
	return name;
}

void Object::ToggleObtained()
{
	b_obtained = !b_obtained;
	return;
}
bool Object::HasObtained()
{
	return b_obtained;
}


