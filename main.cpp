#include <iostream>
#include "Krankenhaus.h"
#include "Patient.h"

void suchePatient(std::string vorname, std::string nachname, Krankenhaus k[], int size);
int main()
{


	srand(time(NULL));
	const int size = 3;
	Krankenhaus k[size];

	int hour = 0;

	suchePatient("Felix", "Zimmer", k, size);

	while (true) {

		if (hour == 10) {
			for (int i = 0; i < size; i++)
			{
				k[i].newDay();
			}
			hour = 0;
		}

		for (int i = 0; i < size; i++)
		{
			std::cout << "\nKrankenhaus: " << i + 1 << "\n";
			k[i].showData();
		}

		hour++;
		system("cls");

	}

	return 0;
}


void suchePatient(std::string vorname, std::string nachname, Krankenhaus k[], int size) {

	Patient newPatient(vorname, nachname);
	Patient* patientPtr = &newPatient;
	int gefundeneNummer = -1;
	int* ptr = &gefundeneNummer;
	for (int i = 0; i < size; i++) {
		if (k[i].suchePatient(patientPtr, ptr)) {
			std::cout << "Patient ist registiriert im Krankenhaus " << i + 1 << "\n";
			break;
		}
		else
		{
			if (i == size - 1)
				std::cout << "Patient ist nicht registriert" << std::endl;
		}
	}
}