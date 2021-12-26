#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "utils.h"
#include "coach.h"
#include "player.h"
#include "team.h"
#include "league.h"


using namespace std;

/*void begin(){


playerNamesData.clear();
playerSurnamesData.clear();
playerNamesBitmapData.clear();
playerSurnamesBitmapData.clear();
}

void init() {


}

void start() {


}*/

void makeMatch(Team& team_one, Team& team_two);
void setFixture(vector<Team> teamlist);

int main()
{
	Coach::getInstance()->clearData();
	Player::getInstance()->clearData();
	Team::getInstance()->clearData();

	Coach::getInstance()->readData("takimlar.txt");
    Player::getInstance()->readData("isim.txt", "soyisim.txt");
	Team::getInstance()->readData("takimlar.txt");

	/*Coach::getInstance()->printData();
	Player::getInstance()->printData();
	Team::getInstance()->printData();*/


	vector<Team> team_list;


	int k = -1;
	Player* p_p = Player::getInstance();
	Coach* c_p = Coach::getInstance();


	for (int i = 0; i < 18; i++) {

		vector<Player> player_list;

		for(int j = 0; j < 11; j++) {

			Player p(p_p->getPlayerNamesData()[(11*i)+j], p_p->getPlayerSurnamesData()[(11*i)+j]);

			player_list.push_back(p);
		}

		Coach c(c_p->getCoachNamesData()[i], c_p->getCoachSurnamesData()[i]);
		Team t(c, player_list, F_352);
		t.calculatePerf();
		t.calculateDPerf();
		t.calculateMFPerf();
		t.calculateFPerf();
		t.calculateAvgAge();
		t.setTeamUniformNumbers();
		
		team_list.push_back(t);
		Team::average_perf = 0;
		Team::average_age = 0;
		Team::perf_D = 0;
		Team::perf_MF = 0;
		Team::perf_F = 0;
	}


	//for (int i = 0; i < team_list.size(); i++) {

	//	team_list[i].print();
	//}

	//team_list[0]++;
	//++team_list[0];
	//team_list[0]--;
	//team_list[0] += 5;
	//team_list[0] -= 10;
	//team_list[0].calculateGD();

	//makeMatch(team_list[0], team_list[1]);
	//team_list[0].calculateGD();
	//team_list[1].calculateGD();
	//team_list[0].print();
	//team_list[1].print();
	//makeMatch(team_list[0], team_list[2]);
	//team_list[0].calculateGD();
	//team_list[2].calculateGD();
	//team_list[0].print();
	//team_list[2].print();

	/*setFixture(team_list);*/

	//cout << &team_list[0] << endl;
	League L(team_list);
	L.generateFixture();
	L.printStandings();
	//team_list[0].print();




	

	return 0;
}


//void makeMatch(Team& team_one, Team& team_two) {
//
//	srand((unsigned)time(NULL));
//
//	Team* home;
//	Team* away;
//	
//	int number = rand() % 2;
//
//	if (number == 0) {
//		home = &team_one;
//		away = &team_two;
//	}
//	else {
//		home = &team_two;
//		away = &team_one;
//	}
//
//	int team_home_goals = rand() % 7;
//	int team_away_goals = rand() % 7;
//
//	
//
//	if (home->getFPerf() > away->getFPerf()) {
//		team_home_goals++;
//	}
//	else if(home->getFPerf() < away->getFPerf()) {
//		team_away_goals++;
//	}
//
//	if (home->getDPerf() > away->getDPerf()) {
//		
//		if (team_away_goals > 0) {
//			team_away_goals--;
//		}
//	}
//	else if (home->getDPerf() < away->getDPerf()) {
//		
//		if (team_home_goals > 0) {
//			team_home_goals--;
//		}
//	}
//
//	if (home->getMFPerf() > away->getMFPerf()) {
//		team_home_goals++;
//		if (team_away_goals > 0) {
//			team_away_goals--;
//		}
//	}
//	else if (home->getMFPerf() < away->getMFPerf()) {
//		team_away_goals++;
//		if (team_home_goals > 0) {
//			team_home_goals--;
//		}
//		
//	}
//
//	if (home->getTeamPerf() > away->getTeamPerf()) {
//		team_home_goals++;
//		if (team_away_goals > 0) {
//			team_away_goals--;
//		}
//	}
//
//	else if (home->getTeamPerf() < away->getTeamPerf()) {
//		team_away_goals++;
//		if (team_home_goals > 0) {
//			team_home_goals--;
//		}
//	}
//
//	*home += team_home_goals;
//	*away += team_away_goals;
//	*home -= team_away_goals;
//	*away -= team_home_goals;
//
//
//
//	if (team_home_goals > team_away_goals) {
//		cout << home->getName() << ": " << team_home_goals << " - " << away->getName() << ": " << team_away_goals << endl;
//		cout << "Kazanan Takim: " << home->getName() << endl;
//		++(*home);
//		(*away)--;
//	}
//	else if(team_home_goals < team_away_goals) {
//
//		cout << home->getName() << ": " << team_home_goals << " - " << away->getName() << ": " << team_away_goals << endl;
//		cout << "Kazanan Takim: " << away->getName() << endl;
//		++(*away);
//		(*home)--;
//	}
//	else if(team_home_goals == team_away_goals) {
//
//		cout << home->getName() << ": " << team_home_goals << " - " << away->getName() << ": " << team_away_goals << endl;
//		cout << "Mac Sonucu: Berabere" << endl;
//		(*home)++;
//		(*away)++;
//	}
//	delete home;
//	delete away;
//}
//
//void setFixture(vector<Team> teamlist) {
//
//	srand((unsigned)time(NULL));
//
//	vector<Team> teamlist_copy;
//	teamlist_copy = teamlist;
//	
//	int random = rand() % 19;
//	Team const_team = teamlist_copy[random];
//
//	teamlist_copy.erase(teamlist_copy.begin() + random);
//
//	for (int i = 0; i < teamlist_copy.size(); i++) {
//
//		cout << "--------" << (i + 1) << ". Hafta Fiksturu" << "--------" << endl;
//		cout << "1. Mac" << " " << const_team.getName() << " - " << teamlist_copy[0].getName() << endl;
//
//		for (int j = 0; j < (teamlist_copy.size() - 1) / 2; j++) {
//			cout << (j + 2) << ". Mac" << " " << teamlist_copy[j + 1].getName() << " - " << teamlist_copy[teamlist_copy.size() - 1 - j].getName() << endl;
//
//		}
//
//		teamlist_copy.push_back(teamlist_copy[0]);
//		teamlist_copy.erase(teamlist_copy.begin());
//
//
//	}
//}


