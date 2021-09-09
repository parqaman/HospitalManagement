#pragma once
#include <string>
#include <random>
#include <vector>


class Patient
{

public:
	enum class Geschlecht { Frau, Mann, Anders };
	enum class Diagnose { Infektion, Fraktur, Simulant, Geheilt };

public:

	Patient(std::string _vorName, std::string _nachName, std::string _zugeteilterArtzt, int _generateGender);
	Patient(std::string _vorName, std::string _nachName);
	void zeigePatientenAkte() const;
	void reduziereBehandlungsdauer(int _behandlungsdauer = 1);
	void setDiagnose(Diagnose _diagnose);
	void setGender(int Zahl);
	int getDiagnose()const;
	int getPatientenNr()const;
	std::string getVorname()const;
	std::string getName()const;
	bool neuerPatient(std::string _vorname, std::string _name)const;
	//Vergleichsoperator zwischen Patienten
	//Basis hierfuer: Vor- und Nachname 
	bool operator==(const Patient& pat) const
	{
		return (pat.getVorname() == vorName && pat.getName() == nachName);

	};

	static bool vergleichePatienten(Patient* ptr1, Patient* ptr2);
	static int getLetztePatientennr();
	static int letztePatientennr;
private:
	void zufallsgeburtsdatum();
	void generateGender(int genderZahl);
	void zeichne(int zahl)const;

private:
	std::string vorName;
	std::string nachName;
	std::string zugeteilterArtzt;
	std::string geburtsdatum;
	Geschlecht geschlecht;
	Diagnose diagnose;
	int behandlungsdauer;
	int patientenNummer;



};
