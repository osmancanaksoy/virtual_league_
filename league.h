#ifndef LEAGUE_H
#define LEAGUE_H

#include <iostream>
#include <vector>
#include <string>
#include "team.h"



class League {

private:
    //int number_of_coachs;
    //int number_of_players;
    //int number_of_teams;

    vector<Team>& teamList;

public:

    League(vector<Team>& team_list);
    ~League();

    void generateFixture();
    //void makeMatch(Team& team_one, Team& team_two);
    void printStandings();
};

#endif // LEAGUE_H
