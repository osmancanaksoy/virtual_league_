#ifndef TEAM_H
#define TEAM_H

#include <iostream>
#include <string>
#include <vector>
#include "coach.h"
#include "player.h"
#include "employee.h"

using namespace std;

enum Formations { F_442, F_433, F_4231, F_451, F_352, F_343 };

class Team {
private:
    double avg_perf_object;
    double avg_age_object;
    double perf_D_object;
    double perf_MF_object;
    double perf_F_object;
    static vector<string> teamAbbrevations;
    static vector<string> teamNamesData;

    static Team* instance;
    static int objCounter;
    int id;

    string name;
    string abbreviation;
    int pts;
    int GF;
    int GA;
    int GD;
    int win;
    int draw;
    int lose;
    
    Coach coach;
    vector<Player> players;
    Formations formation;

    static vector<string> formation_442;
    static vector<string> formation_433;
    static vector<string> formation_451;
    static vector<string> formation_352;
    static vector<string> formation_343;
public:
    static double average_perf;
    static double average_age;
    static double perf_D;
    static double perf_MF;
    static double perf_F;
    Team();
    Team(Coach coach, vector<Player> players, Formations formation = Formations::F_442);
    ~Team();
    void setFormation(Formations formation);
    static Team* const getInstance();
    string generateTeamName(string& name);
    string generateAbbrevation(string& name);
    void addPlayer(Player player);
    void calculatePerf();
    void calculateDPerf();
    void calculateMFPerf();
    void calculateFPerf();
    void calculateAvgAge();
    void setTeamUniformNumbers();
    void calculateGD();
    string getName() const;
    double getTeamAgeAvg() const;
    double getTeamPerf() const;
    double getDPerf() const;
    double getMFPerf() const;
    double getFPerf() const;
    int getGF() const;
    int getGA() const;
    int getGD();
    int getWin() const;
    int getDraw() const;
    int getLose() const;
    int getPoint() const;

    

    

    void readData(const string file_name);
    void clearData();
    void print();
    void printData() const;


    Team& operator++();
    Team& operator++(int);
    Team& operator--();
    Team& operator--(int);
    Team& operator+=(int);
    Team& operator-=(int);
};

#endif // TEAM_H