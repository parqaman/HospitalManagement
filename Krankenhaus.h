#pragma once
#include "Patient.h"
#include <random>

class Krankenhaus {

public:
	Krankenhaus();
	void addPatient();
	void showLetztePatientennr();
	void changeGender(int index, int genderRange);
	void showData()const;
	void newDay();
	bool suchePatient(Patient* pt1, int* PatientenNr);

private:
	void updatePatientenliste();
	void fullList();
	int belegteBetten = 0;
	static constexpr int size = 10;
	const char* arztliste[size] = { "Dr. House", "Dr. Strange", "Dr.Meredith Grey","Lexie Grey", "Dr. Addison Montgomery", "Maggie Pierce", "Richard Weber" , "Nathan Riggs", "Megan Hunt", "Dr Heather Brooks" };

	std::mt19937 rng;
	std::uniform_int_distribution<int> vornameIndexRange;
	std::uniform_int_distribution<int> nachnameIndexRange;
	std::uniform_int_distribution<int> genderRange;
	std::vector<Patient> liste;


};

