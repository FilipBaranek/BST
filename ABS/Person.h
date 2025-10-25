#pragma once
#include <string>

class Person
{
private:
	std::string m_birthNumber;
	std::string m_firstName;
	std::string m_lastName;
	unsigned int m_birthDay;
	unsigned int m_birthMonth;
	unsigned int m_birthYear;

public:
	Person(std::string birthNumber, std::string firstName, std::string lastName, unsigned int birthDay, unsigned int birthMonth, unsigned int birthYear);
	inline std::string birthNumber();
	inline std::string firstName();
	inline std::string lastName();
	inline unsigned int birthDay();
	inline unsigned int birthMonth();
	inline unsigned int birthYear();
	~Person() = default;
};