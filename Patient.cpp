#include "Patient.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>


int Patient::letztePatientennr = 100000;

Patient::Patient(std::string _vorName, std::string _nachName, std::string _zugeteilterArtzt, int _generateZahl)
	:
	vorName(_vorName),
	nachName(_nachName),
	zugeteilterArtzt(_zugeteilterArtzt)

{

	int randomNumber = rand() % 4;
	zufallsgeburtsdatum();
	generateGender(_generateZahl);

	switch (randomNumber)
	{
	case 0:
		diagnose = Diagnose::Infektion;
		behandlungsdauer = 14;
		break;
	case 1:
		diagnose = Diagnose::Fraktur;
		behandlungsdauer = 42;
		break;
	default:
		diagnose = Diagnose::Simulant;
		behandlungsdauer = 2;

	}

	patientenNummer = letztePatientennr;
	letztePatientennr = patientenNummer + 1;
}


Patient::Patient(std::string _vorName, std::string _nachName)
	:
	vorName(_vorName),
	nachName(_nachName)
{
}



void Patient::generateGender(int genderZahl)
{
	switch (genderZahl) {

	case 0:
		geschlecht = Geschlecht::Frau;
		break;
	case 1:
		geschlecht = Geschlecht::Mann;
		break;
	default:
		geschlecht = Geschlecht::Anders;

	};

}


void Patient::zeigePatientenAkte() const
{
	const char* geschlechtListe[] = { "Frau", "Mann", "Anders" };
	int checkDiagnose = (int)diagnose;
	int checkGeschlecht = (int)geschlecht;
	std::cout << vorName << " " << nachName << "\t\t  " << geburtsdatum << "\t " << geschlechtListe[checkGeschlecht] << "\t \t" << patientenNummer << "\t \t";

	switch (checkDiagnose) {
	case 0:
		std::cout << "Infektion \t" << behandlungsdauer;
		zeichne(behandlungsdauer);
		break;
	case 1:
		std::cout << "Fraktur \t" << behandlungsdauer;
		zeichne(behandlungsdauer);
		break;
	case 2:
		std::cout << "Simulant \t" << behandlungsdauer;
		zeichne(behandlungsdauer);
		break;
	case 3:
		std::cout << "geheilt \t" << behandlungsdauer;
		zeichne(behandlungsdauer);
		break;
	}

	std::cout << "\t" << zugeteilterArtzt << "\n";
}
void Patient::zeichne(int zahl) const
{
	if (behandlungsdauer < 10) {
		std::cout << "  Tage\t";
	}
	else {
		std::cout << " Tage\t";
	}
}

//Dekrementierung der Behandlungsdauer mit Defaultwert = 1
void Patient::reduziereBehandlungsdauer(int _behandlungsdauer)
{
	if (behandlungsdauer - _behandlungsdauer >= 0) {
		behandlungsdauer -= _behandlungsdauer;
	}
	else {
		diagnose = Diagnose::Geheilt;
	}
}

//Aenderung der Diagnose eines Patienten
void Patient::setDiagnose(Diagnose _diagnose)
{
	if (diagnose != _diagnose) {
		diagnose = _diagnose;
		int checkDiagnose = (int)diagnose;
		switch (checkDiagnose) {
		case 0:
			behandlungsdauer = 14;
			break;
		case 1:
			behandlungsdauer = 42;
			break;
		case 2:
			behandlungsdauer = 2;
			break;
		case 3:
			behandlungsdauer = 0;
			break;
		}
		std::cout << "Diagnose wurde geaendert" << "\n";
	}
	else {
		std::cout << "Die Diagnose wurde bereits festgestellt" << "\n";
	}
}

int Patient::getDiagnose() const
{
	return (int)diagnose;
}

// fuer jene, die unzufrieden mit ihrem Koerper sind
// uebernimmt die AOK die Kosten fuer die Geschlechtsumwandlung
void Patient::setGender(int zahl)
{
	int checkGeschlecht = (int)geschlecht;
	if (checkGeschlecht != zahl && zahl >= 0 && zahl <= 2) {
		generateGender(zahl);
	}
}

//Vergleiche ob die neu erzeugten Namen bereits in der Patientenliste vorhanden sind.
bool Patient::neuerPatient(std::string _vorName, std::string _name) const
{
	if (_vorName == vorName && _name == nachName) {
		return false;
	}
	else {
		return true;
	}
}

int Patient::getPatientenNr() const
{
	return patientenNummer;
}

int Patient::getLetztePatientennr()
{
	return letztePatientennr;
}

std::string Patient::getVorname() const
{
	return vorName;
}

std::string Patient::getName() const
{
	return nachName;
}

bool Patient::vergleichePatienten(Patient* ptr1, Patient* ptr2)
{
	//Vergleichsoperator zwischen Objekten (Definierung in .h Datei)

	if (*ptr1 == *ptr2) {
		return true;
	}
	else {
		return false;
	}
}

void Patient::zufallsgeburtsdatum()
{
	int jahr;
	int monat;
	int tag;

	jahr = rand() % 101 + 1921;
	monat = rand() % 12 + 1;

	//Zuteilung des letzten Datums des Monats
	if (monat == 1 || monat == 3 || monat == 5 || monat == 7 || monat == 8 || monat == 10 || monat == 12)
	{
		tag = rand() % 31 + 1;
	}
	else if (monat == 2)
	{
		//Beruecksichtigung, ob das Jahr ein Schaltjahr ist
		if (jahr % 4 == 0) {
			tag = 29;
		}
		else {
			tag = 28;
		}
	}
	else
	{
		tag = rand() % 30 + 1;
	}
	if (tag < 10 && monat < 10) {
		geburtsdatum = "0" + std::to_string(tag) + ".0" + std::to_string(monat) + "." + std::to_string(jahr);
	}
	else if (tag >= 10 && monat < 10)
	{
		geburtsdatum = std::to_string(tag) + ".0" + std::to_string(monat) + "." + std::to_string(jahr);
	}
	else if (tag < 10 && monat >= 10)
	{
		geburtsdatum = "0" + std::to_string(tag) + "." + std::to_string(monat) + "." + std::to_string(jahr);
	}
	else
	{
		geburtsdatum = std::to_string(tag) + "." + std::to_string(monat) + "." + std::to_string(jahr);
	}
}
