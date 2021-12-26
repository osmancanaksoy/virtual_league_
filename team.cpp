#include "team.h"
#include "coach.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <stdlib.h>

Team* Team::instance = 0;
int Team::objCounter = 0;
double Team::average_perf = 0;
double Team::average_age = 0;
double Team::perf_D = 0;
double Team::perf_MF = 0;
double Team::perf_F = 0;


vector<string> Team::teamNamesData;
vector<string> Team::teamAbbrevations;
vector<string> Team::formation_442 = { "GK", "D", "D", "D", "D", "MF", "MF", "MF", "MF", "F", "F" };
vector<string> Team::formation_433 = { "GK", "D", "D", "D", "D", "MF", "MF", "MF", "F", "F", "F" };
vector<string> Team::formation_451 = { "GK", "D", "D", "D", "D", "MF", "MF", "MF", "MF", "MF", "F" };
vector<string> Team::formation_352 = { "GK", "D", "D", "D", "MF", "MF", "MF", "MF", "MF", "F", "F" };
vector<string> Team::formation_343 = { "GK", "D", "D", "D", "MF", "MF", "MF", "MF", "F", "F", "F" };


Team::Team() {

    // id = ++objCounter;
    //cout << "Constructor calisti" << " " << "ObjCounter: " << objCounter << endl;
}

Team::Team(Coach coach, vector<Player> players, Formations formation) {

    this->name = generateTeamName(name);
    this->abbreviation = generateAbbrevation(name);
    this->coach = coach;
    this->players = players;
    setFormation(formation);
    //this->average_perf = calculatePerf();
    id = ++objCounter;
}

Team::~Team() {
    
    // objCounter--;
    //cout << "Destrcutor calisti" << " " << "ObjCounter: " << objCounter << endl;
}

void Team::setFormation(Formations formation) {

    this->formation = formation;

    switch (formation)
    {
    case F_442:
        
        for (int i = 0; i < players.size(); i++) {
            players[i].setPosition(formation_442[i]);
        }
        break;

    case F_433:

        for (int i = 0; i < players.size(); i++) {
            players[i].setPosition(formation_433[i]);
        }
        break;

    case F_451:

        for (int i = 0; i < players.size(); i++) {
            players[i].setPosition(formation_451[i]);
        }
        break;

    case F_352:

        for (int i = 0; i < players.size(); i++) {
            players[i].setPosition(formation_352[i]);
        }
        break;

    case F_343:

        for (int i = 0; i < players.size(); i++) {
            players[i].setPosition(formation_343[i]);
        }
        break;

    default:
        cout << "Team::setFormation: Invalid formation information..!" << endl;
        exit(EXIT_FAILURE);
        break;
    }  
}

Team* const Team::getInstance() {
    
    if (!instance) {

        instance = new Team;
        // objCounter--;
    }

    return instance;
}

string Team::generateTeamName(string& name) {

    name = teamNamesData[objCounter];

    return name;
}

string Team::generateAbbrevation(string& name) {

    bool isUnique = true;
    string a = name.substr(0,2);

    for(int i = 0; i < teamAbbrevations.size(); i++) {
        if(teamAbbrevations[i].compare(a) == 0){
            isUnique = false;
        }
    }
    if(isUnique) {
        teamAbbrevations.push_back(a);
    }
    else {
        a = name.substr(0,3);
        teamAbbrevations.push_back(a);
    }

    return a;
}

void Team::addPlayer(Player player) {

    if (players.size() < 11) {
        players.push_back(player);
    }

    else {
        cout << "Team::addPlayer: " << "Exceeded maximum allowed players number..!" << endl;
    }

}

void Team::calculatePerf() {

    // avg = (A - r_min) / (i + 1);
    // A = (avg_perf * i)
    // B = i + 1
    // r_min = 60B - A;

    int r_min;
    int A;
    int B;

    for (int i = 0; i < players.size(); i++) {

        if (i == 0) {
            players[0].setPerformance(100);
            average_perf = 100;
            continue;
        }

        A = average_perf * i;
        B = i + 1;
        r_min = ((60 * B) - A);

        if (r_min < 60) {
            r_min = 60;
        }

        int max = 99;
        int min = r_min + 1;
        
        int random = (rand() % (max - (min + 1)) + min);
        players[i].setPerformance(random);

        average_perf = (double)(A + random) / B;
        avg_perf_object = average_perf;

    }
}

void Team::calculateDPerf() {

    int i = 0;

    for (int j = 0; j < players.size(); j++) {
        
        if (players[j].getPosition() == "D") {

            perf_D += players[j].getPerformance();
            i++;
        }
    }

    perf_D /= i;

    perf_D_object = perf_D;

}

void Team::calculateMFPerf() {

    int i = 0;

    for (int j = 0; j < players.size(); j++) {

        if (players[j].getPosition() == "MF") {

            perf_MF += players[j].getPerformance();
            i++;
        }
    }

    perf_MF /= i;

    perf_MF_object = perf_MF;

}

void Team::calculateFPerf() {

    int i = 0;

    for (int j = 0; j < players.size(); j++) {

        if (players[j].getPosition() == "F") {

            perf_F += players[j].getPerformance();
            i++;
        }
    }

    perf_F /= i;

    perf_F_object = perf_F;

}

void Team::calculateAvgAge() {
    // avg = (A - r_min) / (i + 1);
    // A = (avg_age * i)
    // B = i + 1
    // r_min = B - A;

    int r_min;
    int A;
    int B;

    for (int i = 0; i < players.size(); i++) {

        if (i == 0) {
            players[0].setAge(32);
            average_age = 32;
            continue;
        }

        A = average_age * i;
        B = i + 1;
        r_min = ((25 * B) - A);

        if (r_min < 25) {
            r_min = 25;
        }

        int max = 31;
        int min = r_min + 1;

        int random = (rand() % (max - (min + 1)) + min);
        players[i].setAge(random);

        average_age = (double)(A + random) / B;
        avg_age_object = average_age;

    }

}

void Team::calculateGD() {
    GD = GF - GA;
}

string Team::getName() const {
    return name;
}

double Team::getTeamAgeAvg() const {
    return avg_age_object;
}

double Team::getTeamPerf() const {
    return avg_perf_object;
}

double Team::getDPerf() const {
    return perf_D_object;
}

double Team::getMFPerf() const {
    return perf_MF_object;
}

double Team::getFPerf() const {
    return perf_F_object;
}

int Team::getGF() const {
    return GF;
}

int Team::getGA() const {
    return GA;
}

int Team::getGD() {
    calculateGD();
    return GD;
}

int Team::getWin() const {
    return win;
}

int Team::getDraw() const {
    return draw;
}

int Team::getLose() const {
    return lose;
}

int Team::getPoint() const {
    return pts;
}

void Team::setTeamUniformNumbers() {

    srand((unsigned)time(NULL));

    vector<bool> bitmapUniformNumber;

    for (int i = 0; i < 99; i++) {
        bitmapUniformNumber.push_back(false);
    }

    for (int i = 0; i < players.size(); i++) {
        bool isNumberFinded = false;

        while (!isNumberFinded) {
            int number = rand() % 99;
            if (bitmapUniformNumber[number] == false) {
                bitmapUniformNumber[number] = true;
                players[i].setUniformNumber(number);
                isNumberFinded = true;
            }
        }
    }
}


void Team::readData(const string file_name) {

    ifstream file(file_name, ios::in);

	if (!file.good()) {

		cout << "Team::readData: " << file_name << " not found..!" << endl;

		exit(EXIT_FAILURE);
	}

    vector<vector<string>> result;
    string line;

    while(getline(file, line)) {
        stringstream ss(line);
        string token;

        vector<string> tokens;

        while(getline(ss, token, ';')) {

            tokens.push_back(token);
        }

        result.push_back(tokens);
    }

    file.close();

    cout << "Team::readData: " << result.size() << " rows are loaded successfully from " << file_name << "." << endl;

    for (int i = 0; i < result.size(); i++) {

        string data_team = result[i][0];

        Team::teamNamesData.push_back(data_team);
    }
}

void Team::clearData() {

    teamNamesData.clear();
    teamAbbrevations.clear();
}

void Team::print() {

    cout << "**********" << name << " " << "(" << abbreviation << ")" << " " << "Coach: " << coach.getName() << " " << coach.getSurname() << "**********" << endl;
    cout << "Formation: " << formation << " " << "Average Perf: " << fixed << setprecision(2) << avg_perf_object << " " << "Average Age: " << avg_age_object << " " <<
        "Average D: " << perf_D_object << " " << "Average MF: " << perf_MF_object << " " << "Average F: " << perf_F_object << endl 
        << "GF: " << GF << " " << "GA: " << GA << " " << "GD: " << getGD() << endl;

    cout << setfill(' ') << setw(15) << left << "Name" << " "
        << setfill(' ') << setw(15) << left << "Surname" << " "
        << setfill(' ') << setw(8) << left << "Age" << " "
        << setfill(' ') << setw(8) << left << "Kit" << " "
        << setfill(' ') << setw(8) << left << "Avg." << " "
        << setfill(' ') << setw(8) << left << "Pos" << endl;

    cout << "----" << "            " << "-------" << "         " << "---" << "      " << "---" << "      " << "---" << "      " << "---" << endl;

    for (int i = 0; i < players.size(); i++) {

        players[i].print();
    }
}

void Team::printData() const {

    cout << "Team Name" << endl;

    for (int i = 0; i < Team::teamNamesData.size(); i++) {
        cout << teamNamesData[i] << endl;
    }
}

Team& Team::operator++() {

    win++;
    pts += 3;

    return *this;
}

Team& Team::operator++(int) {

    draw++;
    pts += 1;

    return *this;
}

Team& Team::operator--() {

    lose++;

    return *this;
}

Team& Team::operator--(int) {

    lose++;

    return *this;
}

Team& Team::operator+=(int gf) {

    GF += gf;

    return *this;
}

Team& Team::operator-=(int ga) {

    GA += ga;

    return *this;
}