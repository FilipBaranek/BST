#include "Person.h"

Person::Person(std::string birthNumber, std::string firstName, std::string lastName, unsigned int birthDay, unsigned int birthMonth, unsigned int birthYear)
{
	m_birthNumber = birthNumber;
	m_firstName = firstName;
	m_lastName = lastName;
	m_birthDay = birthDay;
	m_birthMonth = birthMonth;
	m_birthYear = birthYear;
}

inline std::string Person::birthNumber()
{
	return m_birthNumber;
}

inline std::string Person::firstName()
{
	return m_firstName;
}

inline std::string Person::lastName()
{
	return m_lastName;
}

inline unsigned int Person::birthDay()
{
	return m_birthDay;
}

inline unsigned int Person::birthMonth()
{
	return m_birthMonth;
}

inline unsigned int Person::birthYear()
{
	return m_birthYear;
}
