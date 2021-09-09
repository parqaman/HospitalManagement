#include "Krankenhaus.h"
#include "Krankenhaus.h"
#include "NameList.h"
#include <time.h>
#include <iostream>
#include <vector>

static std::vector<Patient> warteListe;

Krankenhaus::Krankenhaus()
	:
	rng(time(NULL)),
	vornameIndexRange(0, 49),
	nachnameIndexRange(0, 49),
	genderRange(0, 1)
{

	updatePatientenliste();

	for (int i = 0; i < warteListe.size(); i++) {
		addPatient();
		if (warteListe.size() > 149) {
			std::cout << "Stopp";
		}
	}


	std::cout << " Warteliste size Danach: " << warteListe.size() << "\n";

}

void Krankenhaus::addPatient()
{

	if (warteListe.empty()) {
		updatePatientenliste();
	}
	int i = 0;
	int sizeWarteListe = warteListe.size();
	const int maxPatient = 10; //Maximale Anzahl der Patienten in einem Krankenhaus
	while (i < sizeWarteListe) {

		if (belegteBetten < maxPatient)
		{
			liste.push_back(warteListe.at(i));
			belegteBetten++;
			//Loesche Patientendaten aus der WARTELISTE, die bereits in einem Krankenhaus eingewiesen sind
			warteListe.erase(warteListe.begin() + i);
		}
		i++;
	}


}


void Krankenhaus::showLetztePatientennr()
{
	int letzteNummer = Patient::getLetztePatientennr();
	std::cout << "Die Nr ist " << letzteNummer << std::endl;

}

void Krankenhaus::changeGender(int index, int genderRange)
{
	liste.at(index).setGender(genderRange);
}


void Krankenhaus::showData() const
{
	std::cout << "Patienten daten: \n";
	std::cout << "Name: \t \t\t" << "  Geburtstag\t" << "(m/w/d): \t" << "Patientennr: \t" << "Diagnose \t" << "stationaer: \t" << "zugeteilter Arzt: \t" << std::endl;

	for (int i = 0; i < liste.size(); i++) {
		liste.at(i).zeigePatientenAkte();
	}
}

void Krankenhaus::newDay()
{
	for (int i = 0; i < liste.size(); i++)
	{
		liste.at(i).reduziereBehandlungsdauer();
		// 3 = geheilt
		if (liste.at(i).getDiagnose() == 3) {
			liste.erase(liste.begin() + i);
			belegteBetten--;
			addPatient();

		}
	}
}

//Generierung der Patienten
void Krankenhaus::updatePatientenliste()
{
	//Patienten wird wieder generiert, sobald alle davor generierten Patienten bereits eingewiesen wurden
	if (warteListe.empty()) {
		while (warteListe.size() < 150) {
			fullList();
		}
	}
}

void Krankenhaus::fullList()
{
	int generateVoname = vornameIndexRange(rng);
	int generateNachname = vornameIndexRange(rng);
	int generateGender = genderRange(rng);

	std::string string2 = lastNames[generateNachname];
	std::string string1;

	if (generateGender == 0) {
		string1 = firstNames_female[generateVoname];
	}
	else {
		string1 = firstNames_male[generateVoname];
	}
	int randomNumber = rand() % 10;
	std::string arzt = arztliste[randomNumber];

	int j = 0;
	bool neuerPatient = true;
	if (warteListe.size() > 148) {
		std::cout << "Stopp";
	}
	while (j < warteListe.size()) {

		//Ueberprufung, ob der neu erzeugten Namen bereits in der Liste ist
		if (!warteListe.at(j).neuerPatient(string1, string2)) {
			neuerPatient = false;
			break;
		}

		j++;
	}

	if (!neuerPatient) {
		fullList();
	}
	Patient newPatient(string1, string2, arzt, generateGender);
	warteListe.push_back(newPatient);
}

bool Krankenhaus::suchePatient(Patient* ptr1, int* patientenPtr)
{
	bool gefunden = false;
	int i = 0;
	Patient* ptr2 = nullptr;

	while (i < liste.size()) {
		ptr2 = &liste.at(i);
		if (Patient::vergleichePatienten(ptr1, ptr2)) {
			*patientenPtr = liste.at(i).getPatientenNr();
			std::cout << "Gefunden.\n" << "Vorname: " << ptr1->getVorname() << "\nNachname: " << ptr1->getName()
				<< "\nPatientnummer: " << *patientenPtr << "\n";
			gefunden = true;
			break;
		};
		i++;
	}

	return gefunden;
}
