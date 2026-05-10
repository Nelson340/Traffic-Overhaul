#include "CustomThread.h"
#include "Scripting.h"
#include "../ScriptHook/Log.h"

#include <iostream>
#include <string>
#include <map>
#include <windows.h>

#define countof( array ) ( sizeof( array )/sizeof( array[0] ) )

// Pull in all our scripting functions/types
using namespace Scripting;
using std::string;

CustomThread::CustomThread()
{
    // Give your own name here!
	SetName("TrafficOverhaul");
}

void CustomThread::RunTick()
{
	Wait(5000);									// Script executes every 5 seconds.
	count = 0;									// Reset the counter, recounting will happen in the tick.

	// Read TrafficOverhaul.ini
	int CarsPerCycle = GetPrivateProfileInt(TEXT("Options"),TEXT("CarsPerCycle"),8,TEXT("./TrafficOverhaul.ini"));
	int CustomCars = GetPrivateProfileInt(TEXT("AddedCars"),TEXT("Enable"),0,TEXT("./TrafficOverhaul.ini"));

	// Initializing and getting player info
	Player PlayerIndex = ConvertIntToPlayerIndex(GetPlayerId());
	Ped PlayerChar;
    GetPlayerChar(PlayerIndex, &PlayerChar);
	GetCharCoordinates(PlayerChar, &x, &y, &z);
	b8 airport = IsCharInArea2D(PlayerChar, 2165.92f, 912.35f, 2924.75f, -145.64f, false);
	//this location needs to be the first entry in every neighborhood list so that the actual first entry works, the coordinates are far up north inbetween bohan and northwood
	b8 filler = IsCharInArea2D(PlayerChar, 69.11f, 2199.22f, 69.33f, 2199.44f, false);
	//North Algonquin and Bohan
	b8 harbron = IsCharInArea2D(PlayerChar, -648.99f, 1194.48f, 1409.72f, 1927.28f, false);
	b8 holland = IsCharInArea2D(PlayerChar, -648.99f, 1194.48f, 71.82f, 1598.12f, false);
	b8 grummer = IsCharInArea2D(PlayerChar, -562.80f, 1585.99f, -24.02f, 1876.39f, false);
	b8 bhindus = IsCharInArea2D(PlayerChar, 863.135f, 1377.35f, 1348.83f, 1661.61f, false);
	b8 charge = IsCharInArea2D(PlayerChar, 397.20f, 1121.32f, 674.00f, 605.271f, false);
	//Rest of Algonquin
	b8 varsity = IsCharInArea2D(PlayerChar, -702.852f, 906.696f, -381.711f, 1191.31f, false);
	b8 lancast = IsCharInArea2D(PlayerChar, -31.3146f, 906.696f, 233.733f, 1191.31f, false);
	b8 mpeast = IsCharInArea2D(PlayerChar, -31.3146f, 609.361f, 211.533f, 906.696f, false);
	b8 mpcent = IsCharInArea2D(PlayerChar, -381.711f, 609.361f, -31.3146f, 1191.31f, false);
	b8 mpwest = IsCharInArea2D(PlayerChar, -702.852f, 609.361f, -381.711f, 906.696f, false);
	b8 purgatory = IsCharInArea2D(PlayerChar, -778.416f, 361.597f, -381.724f, 609.361f, false);
	b8 hatton = IsCharInArea2D(PlayerChar, -31.3146f, 369.954f, 267.099f, 609.361f, false);
	b8 lancent = IsCharInArea2D(PlayerChar, -31.3146f, 148.235f, 267.099f, 369.954f, false);
	b8 starjunc = IsCharInArea2D(PlayerChar, -381.711f, 148.235f, -31.3146f, 609.361f, false);
	b8 westmin = IsCharInArea2D(PlayerChar, -796.099f, 148.235f, -381.724f, 361.597f, false);
	b8 meat = IsCharInArea2D(PlayerChar, -883.699f, -139.945f, -381.724f, 148.235f, false);
	b8 triangle = IsCharInArea2D(PlayerChar, -381.724f, -139.945f, -31.3146f, 148.235f, false);
	b8 easton = IsCharInArea2D(PlayerChar, -31.3146f, -139.945f, 108.875f, 148.235f, false);
	b8 prescity = IsCharInArea2D(PlayerChar, 108.875f, -139.945f, 343.176f, 148.235f, false);
	b8 fmnorth = IsCharInArea2D(PlayerChar, 212.278f, -303.904f, 394.167f, -139.945f, false);
	b8 fmsouth = IsCharInArea2D(PlayerChar, 212.278f, -505.423f, 490.904f, -690.606f, false);
	b8 loweast = IsCharInArea2D(PlayerChar, -76.2142f, -298.546f, 212.278f, -139.945f, false);
	b8 litaly = IsCharInArea2D(PlayerChar, -483.208f, -346.624f, -254.508f, -222.048f, false);
	b8 wcgc = IsCharInArea2D(PlayerChar, -513.87f, -150.47f, -757.06f, -410.06f, false);
	b8 ecgc = IsCharInArea2D(PlayerChar, -513.87f, -410.06f, -305.93f, -642.82f, false);
	b8 cityhall = IsCharInArea2D(PlayerChar, -304.118f, -602.863f, -76.2143f, -346.624f, false);
	b8 chinatown = IsCharInArea2D(PlayerChar, -76.2143f, -505.423f, 212.278f, -298.546f, false);
	b8 southalgo = IsCharInArea2D(PlayerChar, -304.118f, -602.863f, -76.2143f, -1065.73f, false);
	//Colony Island
	b8 colony = IsCharInArea2D(PlayerChar, 345.71f, -59.50f, 598.31f, 228.28f, false);
	//Alderney neighborhoods
	b8 westdyke = IsCharInArea2D(PlayerChar, -1563.42f, 1417.7f, -711.262f, 1954.73f, false);
	b8 leftwood = IsCharInArea2D(PlayerChar, -1601.43f, 1147.54f, -738.262f, 1417.7f, false);
	b8 aldcit = IsCharInArea2D(PlayerChar,  -1659.55f, 882.454f, -758.41f, 1110.75f, false);
	b8 berchem = IsCharInArea2D(PlayerChar, -2023.89f, 434.333f, -1338.83f, 751.09f, false);
	b8 normandy = IsCharInArea2D(PlayerChar,  -1313.85f, 374.04f, -855.416f, 641.471f, false);
	b8 acter = IsCharInArea2D(PlayerChar, -2023.89f, 203.392f, -1383.78f, 641.471f,  false);
	b8 portudor = IsCharInArea2D(PlayerChar, -1294.57f, -234.742f, -897.531f, 289.462f, false);
	b8 tudor = IsCharInArea2D(PlayerChar, -2281.2f, -234.742f, -1294.57f, 203.392f, false);
	b8 actindus = IsCharInArea2D(PlayerChar, -2281.2f, -839.742f, -872.306f, -261.129f, false);
	//Dukes and Broker
	b8 stein = IsCharInArea2D(PlayerChar, 1408.6f, 1089.52f, 833.92f, 659.51f, false);
	b8 willis = IsCharInArea2D(PlayerChar, 1659.9f, 345.809f, 1873.7f, 795.065f, false);
	b8 meadow = IsCharInArea2D(PlayerChar, -2281.2f, -839.742f, -872.306f, -261.129f, false);
	b8 eicity = IsCharInArea2D(PlayerChar, 833.92f, 659.51f, 1262.27f, 539.4f, false);
	b8 cerveza = IsCharInArea2D(PlayerChar, 1558.8f, 539.984f, 1050.76f, 273.548f, false);
	b8 mpark = IsCharInArea2D(PlayerChar, 1923.78f, 1167.53f, 1406.2f, 428.33f, false);
	b8 fiaterm = IsCharInArea2D(PlayerChar, 1895.01f, 655.61f, 2165.92f, 65.32f, false);
	b8 beechwood = IsCharInArea2D(PlayerChar, 1870.69f, 344.63f, 1525.35f, -5.05f, false);
	b8 schottler = IsCharInArea2D(PlayerChar, 1119.97f, -12.7522f, 1409.97f, 321.351f, false);
	b8 downtown = IsCharInArea2D(PlayerChar, 954.063f, -12.7522f, 1119.97f, 321.351f, false);
	b8 outlook = IsCharInArea2D(PlayerChar, 954.063f, -280.181f, 1139.43f, -12.7522f, false);
	b8 sslopes = IsCharInArea2D(PlayerChar, 1139.43f, -280.181f, 1519.08f, -12.7521f, false);
	b8 hove = IsCharInArea2D(PlayerChar, 720.266f, -472.138f, 1180.09f, -232.36f, false);
	b8 ffprojects = IsCharInArea2D(PlayerChar, 1190.97f, -562.36f, 1513.38f, -309.04f, false);
	b8 rotterdam = IsCharInArea2D(PlayerChar, 946.63f, 247.03f, 838.35f, -100.04f, false);
	b8 ehook1 = IsCharInArea2D(PlayerChar, 838.35f, -100.04f, 730.35f, -234.28f, false);
	b8 ehook2 = IsCharInArea2D(PlayerChar, 830.1f, 25.76f, 738.64f, -100.04f, false);
	b8 boabo1 = IsCharInArea2D(PlayerChar, 908.72f, 47.45f, 607.04f, 234.95f, false);
	b8 boabo2 = IsCharInArea2D(PlayerChar, 870.84f, 284.93f, 743.03f, 435.45f, false);
	b8 boabo3 = IsCharInArea2D(PlayerChar, 762.52f, 384.56f, 1048.63f, 444.90f, false);
	// cops
	b8 police = IsWantedLevelGreater(PlayerIndex, 3);
	
	// Liberty City traffic
	eModel veh[] = { MODEL_BURRITO, MODEL_PONY, MODEL_SPEEDO, MODEL_MULE, MODEL_STEED, MODEL_YANKEE, MODEL_BOXVILLE, MODEL_BENSON };
	GenerateRandomIntInRange(0, countof(veh) * 9, &vrand);
	
	// Transport
	eModel service[] = { MODEL_TAXI, MODEL_TAXI2, MODEL_CABBY, MODEL_BUS, MODEL_POLICE, MODEL_POLICE2 };
	GenerateRandomIntInRange(0, /*countof(service) - 1*/6, &srand);
	
	// Taxi group now repurposed for vehicles that should have little to no precense in traffic
	eModel taxi[] = { MODEL_BURRITO2, MODEL_FORKLIFT, MODEL_ROMERO, MODEL_ROM, MODEL_HELLFURY, MODEL_ZOMBIEB, ANGEL, BATI2, DAEMON, DIABOLUS, DOUBLE2, GBURRITO, HAKUCHOU2, HEXER, INNOVATION, LYCAN, NIGHTBLADE, PACKER2, PBUS, REVENANT, SLAMVAN, WAYFARER, WOLFSBANE, APC, AVAN, BUZZARD, CADDY, CAVALCADE2, POLICE3, POLICE4, POLICEB, POLICEW, SERRANO2, SKYLIFT, SUPERD2, SWIFT };

	// Special police vehicles
	eModel policeveh[] = { MODEL_NOOSE, MODEL_NSTOCKADE, MODEL_POLPATRIOT };

	// Stuff allowed to spawn at the airport
	eModel airportveh[] = { MODEL_AIRTUG, MODEL_FEROCI2, MODEL_PERENNIAL2, MODEL_RIPLEY, MODEL_BENSON, MODEL_BOXVILLE, MODEL_FORKLIFT, MODEL_MULE, MODEL_PACKER, MODEL_PONY, MODEL_STOCKADE, MODEL_SPEEDO, MODEL_YANKEE, MODEL_STEED, MODEL_TAXI, MODEL_TAXI2, MODEL_CABBY };
	GenerateRandomIntInRange(0, countof(airportveh) * 1, &arand);

	// Stuff exclusively spawning at the airport
	eModel airportvehex[] = { MODEL_AIRTUG, MODEL_FEROCI2, MODEL_PERENNIAL2, MODEL_RIPLEY, MODEL_STOCKADE };
	
	// poor cars
	eModel poorveh[] = { MODEL_CHAVOS, MODEL_EMPEROR, MODEL_EMPEROR2, MODEL_ESPERANTO, MODEL_INGOT, MODEL_MARBELLA, MODEL_MERIT, MODEL_PREMIER, MODEL_PRIMO, MODEL_WILLARD, MODEL_BUCCANEER, MODEL_MANANA, MODEL_SABRE, MODEL_SABRE2, MODEL_STALION, MODEL_VIGERO2, MODEL_URANUS, MODEL_BLISTA, MODEL_FUTO, MODEL_BOBCAT, MODEL_MOONBEAM, MODEL_RANCHER, MODEL_SANCHEZ, REGINA, RHAPSODY, TOWTRUCK };
	GenerateRandomIntInRange(0, countof(poorveh) * 1, &arand);
	
	// Stuff to spawn in the ghetto (in the ghettoooooo...)
	eModel ghettoveh[] = { MODEL_PMP600, MODEL_DUKES, MODEL_FACTION, MODEL_PEYOTE, MODEL_RUINER, MODEL_SABREGT, MODEL_VIGERO, MODEL_VIRGO, MODEL_VOODOO, MODEL_CAVALCADE, MODEL_FXT, MODEL_HUNTLEY, MODEL_PATRIOT, MODEL_HAKUMAI, TAMPA, BUFFALO };
	GenerateRandomIntInRange(0, countof(ghettoveh) * 1, &arand);

	// middle class
	eModel midveh[] = { MODEL_FELTZER, MODEL_CHAVOS, MODEL_FEROCI, MODEL_MERIT, MODEL_PREMIER, MODEL_PRIMO, MODEL_SOLAIR, MODEL_STRATUM, MODEL_SULTAN, MODEL_FORTUNE, MODEL_E109, MODEL_HABANERO, MODEL_HUNTLEY, MODEL_LANDSTALKER, MODEL_MINIVAN, MODEL_PATRIOT, MODEL_PERENNIAL, MODEL_FAGGIO };
	GenerateRandomIntInRange(0, countof(midveh) * 1, &arand);
	
	// rich businessmen
	eModel richbizveh[] = { MODEL_ADMIRAL, MODEL_COGNOSCENTI, MODEL_INTRUDER, MODEL_LOKUS, MODEL_ORACLE, MODEL_PINNACLE, MODEL_PRES, MODEL_SCHAFTER, MODEL_WASHINGTON, MODEL_SENTINEL, MODEL_CAVALCADE, MODEL_FXT, MODEL_REBLA, SCHAFTER2, SERRANO };
	GenerateRandomIntInRange(0, countof(richbizveh) * 1, &arand);
	
	// rich party dudes
	eModel richfunveh[] = { MODEL_BANSHEE, MODEL_COMET, MODEL_COQUETTE, MODEL_INFERNUS, MODEL_SUPERGT, MODEL_TURISMO, MODEL_DF8, MODEL_DILETTANTE, MODEL_PMP600, MODEL_STRETCH, MODEL_VINCENT, MODEL_NRG900, MODEL_SULTANRS, BATI, DOUBLET, HAKUCHOU, BUFFALO, BULLET, F620, SCHAFTER3, LIMO2, SUPERD, AKUMA, FAGGIO2, VADER };
	GenerateRandomIntInRange(0, countof(richfunveh) * 1, &arand);
	
	//small mix of the two rich groups plus missing bikes
	eModel richliteveh[] = { MODEL_DF8, MODEL_DILETTANTE, MODEL_VINCENT, MODEL_BOBBER, MODEL_PCJ, MODEL_ADMIRAL, MODEL_INTRUDER, MODEL_LOKUS, MODEL_SCHAFTER, MODEL_SENTINEL, MODEL_PMP600, BUFFALO, SERRANO };
	GenerateRandomIntInRange(0, countof(richliteveh) * 1, &arand);
	
	// industrial vehicles
	eModel industryveh[] = { MODEL_BURRITO, MODEL_PONY, MODEL_SPEEDO, MODEL_MULE, MODEL_STEED, MODEL_YANKEE, MODEL_BOXVILLE, MODEL_BENSON, MODEL_BOBCAT, MODEL_MOONBEAM, MODEL_RANCHER, MODEL_BIFF, MODEL_PACKER, MODEL_PHANTOM, MODEL_STOCKADE, YANKEE2 };
	GenerateRandomIntInRange(0, countof(industryveh) - 1, &arand);
	
	eModel industryvehex[] = { MODEL_BOBCAT, MODEL_RANCHER, MODEL_BIFF, MODEL_PACKER, MODEL_PHANTOM, YANKEE2, MODEL_STOCKADE };
	
	// Count everything
	for (int i = 0; i < countof(veh); i++){
		if (HasModelLoaded(veh[i])) {
			count++;
		}
	}
	for (int i = 0; i < countof(airportvehex); i++){
		if (HasModelLoaded(airportvehex[i])) {
			count++;
		}
	}
	for (int i = 0; i < countof(policeveh); i++){
		if (HasModelLoaded(policeveh[i])) {
			count++;
		}
	}
	for (int i = 0; i < countof(taxi); i++){
		if (HasModelLoaded(taxi[i])) {
			count++;
		}
	}

	// Custom cars from the .ini are read. Behind the counting for the added cars to be counted with everything else
	if (CustomCars == 1) {
		int AmountAdded = GetPrivateProfileInt(TEXT("AddedCars"), TEXT("Amount"), 0, TEXT("./TrafficOverhaul.ini")); //counts added cars
		char Carm[128][128]; //defines the carm variable
		char thing[128]; //defines the temporary name thing
		for (int n = AmountAdded; n>0; n--){ //loop thingy to get the car names
			sprintf_s(thing, "%d", n); //number to string
			GetPrivateProfileString("addedcars", thing, NULL, Carm[n], 128, "./TrafficOverhaul.ini"); //gets names and saves for future use
		}

		for (int n = AmountAdded; n>0 ; n--){
			if (HasModelLoaded(GetModelHash(Carm[n]))) {
				count++;
			}
		}

		if ((int(count) >= CarsPerCycle) || police || airport) {
			for (int n = AmountAdded; n>0; n--) {
				MarkModelAsNoLongerNeeded(GetModelHash(Carm[n])); //SHOULD unload all called cars
			}
		}

		//loading added models with its down random integer
		for (int n = AmountAdded; n > 0; n--) {
			GenerateRandomIntInRange(1, 2, &customrand);
			if (((HasModelLoaded(GetModelHash(Carm[n]))) == false) && (customrand == 2) && filler || aldcit || berchem || leftwood || westdyke || holland || varsity || lancast || mpeast || mpcent || mpwest || purgatory || hatton || lancent || starjunc || westmin || meat || easton || fmsouth || loweast || wcgc || ecgc || chinatown || stein || willis || meadow || mpark || fiaterm || downtown || outlook || sslopes || rotterdam) {
				Wait(5000);
				RequestModel(GetModelHash(Carm[n]));
			}
			else
				for (int n = AmountAdded; n>0; n--) {
				MarkModelAsNoLongerNeeded(GetModelHash(Carm[n])); //SHOULD unload all called cars
			}
		}
	}
	// Debug info, display exact number of loaded cars including added cars
	//PrintHelpWithNumber("NUMBER", count);

	// Try to not load anything while the game is not finished unloading models, player has wantedlevel >=3 or is in airport
	if ((int(count) < CarsPerCycle) && !police && !airport) {
		// Service cars, have more of a chance to load (Only loads bus now), chance is 1/12th per 5 seconds.
		for (int i = 0; i < countof(service); i++){
			if ((HasModelLoaded(service[i]) == false) && (srand == i)) {
				RequestModel(service[i]);
			}
		}

		// Normal traffic
		for (int i = 0; i < countof(veh); i++){
			if ((HasModelLoaded(veh[i]) == false) && (vrand == i)) {
				RequestModel(veh[i]);
			}
		}
	}

	// Airport traffic
	if ((int(count) < CarsPerCycle) && filler || airport) {
		for (int i = 0; i < countof(airportveh); i++){
			if ((HasModelLoaded(airportveh[i]) == false)) {
				RequestModel(airportveh[i]);
			}
		}
	}
	else {
		for (int i = 0; i < countof(airportvehex); i++){
			MarkModelAsNoLongerNeeded(airportvehex[i]);
		}
	}
	
	// ghetto traffic
	if ((int(count) < CarsPerCycle) && filler || harbron || colony || schottler || tudor) {
		for (int i = 0; i < countof(ghettoveh); i++){
			if ((HasModelLoaded(ghettoveh[i]) == false)) {
				RequestModel(ghettoveh[i]);
			}
		}
	}
	else {
		for (int i = 0; i < countof(ghettoveh); i++){
			MarkModelAsNoLongerNeeded(ghettoveh[i]);
		}
	}
	if ((int(count) < CarsPerCycle) && filler || harbron || colony || acter || tudor || berchem || prescity || chinatown || loweast || willis || eicity || cerveza || beechwood || schottler || hove || ffprojects || boabo2 || boabo3) {
		for (int i = 0; i < countof(poorveh); i++){
			if ((HasModelLoaded(poorveh[i]) == false)) {
				RequestModel(poorveh[i]);
			}
		}
	}
	else {
		for (int i = 0; i < countof(poorveh); i++){
			MarkModelAsNoLongerNeeded(poorveh[i]);
		}
	}
	//mid traffic (ayo dis traffic mid fr fr on god)
	if ((int(count) < CarsPerCycle) && filler || aldcit || berchem || leftwood || westdyke || holland || varsity || lancast || mpeast || mpcent || mpwest || purgatory || hatton || lancent || starjunc || westmin || meat || easton || fmsouth || loweast || wcgc || ecgc || chinatown || stein || willis || meadow || mpark || fiaterm || downtown || outlook || sslopes || rotterdam) {
		for (int i = 0; i < countof(midveh); i++){
			if ((HasModelLoaded(midveh[i]) == false)) {
				RequestModel(midveh[i]);
			}
		}
	}
	else {
		for (int i = 0; i < countof(midveh); i++){
			MarkModelAsNoLongerNeeded(midveh[i]);
		}
	}
	
	//rich business traffic
	if ((int(count) < CarsPerCycle) && filler || aldcit || mpeast || lancast || hatton || lancent || litaly || wcgc || ecgc || cityhall || southalgo) {
		for (int i = 0; i < countof(richbizveh); i++){
			if ((HasModelLoaded(richbizveh[i]) == false)) {
				RequestModel(richbizveh[i]);
			}
		}
	}
	else {
		for (int i = 0; i < countof(richbizveh); i++){
			MarkModelAsNoLongerNeeded(richbizveh[i]);
		}
	}
	//rich pleasure traffic
	if ((int(count) < CarsPerCycle) && filler || westdyke || leftwood || varsity || mpwest || purgatory || westmin || triangle || litaly) {
		for (int i = 0; i < countof(richfunveh); i++){
			if ((HasModelLoaded(richfunveh[i]) == false)) {
				RequestModel(richfunveh[i]);
			}
		}
	}
	else {
		for (int i = 0; i < countof(richfunveh); i++){
			MarkModelAsNoLongerNeeded(richfunveh[i]);
		}
	}
	//rich mix traffic
	if ((int(count) < CarsPerCycle) && filler || mpcent || downtown || fiaterm || berchem || mpark || starjunc) {
		for (int i = 0; i < countof(richliteveh); i++){
			if ((HasModelLoaded(richliteveh[i]) == false)) {
				RequestModel(richliteveh[i]);
			}
		}
	}
	else {
		for (int i = 0; i < countof(richliteveh); i++){
			MarkModelAsNoLongerNeeded(richliteveh[i]);
		}
	}
	//industrial traffic
	if ((int(count) < CarsPerCycle) && filler || actindus || normandy || tudor || portudor || bhindus || charge || fmnorth || eicity || ehook1 || ehook2 || boabo1 || boabo2 || boabo3 || grummer) {
		for (int i = 0; i < countof(industryveh); i++){
			if ((HasModelLoaded(industryveh[i]) == false)) {
				RequestModel(industryveh[i]);
			}
		}
	}
	else {
		for (int i = 0; i < countof(industryvehex); i++){
			MarkModelAsNoLongerNeeded(industryvehex[i]);
		}
	}
	// If more cars are loaded than the number given in TrafficOverhaul.ini, try to unload all unused models
	if ((int(count) >= CarsPerCycle)/* || police*/ || airport) {
		for (int i = 0; i < countof(veh); i++){
			MarkModelAsNoLongerNeeded(veh[i]);
		}
		for (int i = 0; i < countof(taxi); i++){
			MarkModelAsNoLongerNeeded(taxi[i]);
		}
		for (int i = 0; i < countof(airportvehex); i++){
			MarkModelAsNoLongerNeeded(airportvehex[i]);
		}
		for (int i = 0; i < countof(policeveh); i++){
			MarkModelAsNoLongerNeeded(policeveh[i]);
		}
		for (int i = 0; i < countof(industryvehex); i++){
			MarkModelAsNoLongerNeeded(industryvehex[i]);
		}
		for (int i = 0; i < countof(poorveh); i++){
			MarkModelAsNoLongerNeeded(poorveh[i]);
		}
		for (int i = 0; i < countof(ghettoveh); i++){
			MarkModelAsNoLongerNeeded(ghettoveh[i]);
		}
		for (int i = 0; i < countof(richbizveh); i++){
			MarkModelAsNoLongerNeeded(richbizveh[i]);
		}
		for (int i = 0; i < countof(richfunveh); i++){
			MarkModelAsNoLongerNeeded(richfunveh[i]);
		}
	}

	/*
	for (auto eModel : veh){

	}
	*/
	

	// Unloads on all cycles
	for (int i = 0; i < countof(taxi); i++){
		MarkModelAsNoLongerNeeded(taxi[i]);
	}
	
}

