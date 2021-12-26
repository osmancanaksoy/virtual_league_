#include "league.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

struct SinglyNode {

	int match_ID;
	Team* team_one;
	Team* team_two;

	SinglyNode* next;
};

struct SinglyLinkedList {

	SinglyNode* head = NULL;

	void addBack(int match_ID, Team* team_one, Team* team_two) {
		SinglyNode* v = new SinglyNode;
		v->match_ID = match_ID;
		v->team_one = team_one;
		v->team_two = team_two;
		v->next = NULL;

		if (head == NULL)
			head = v;
		else
		{
			SinglyNode* first = head;
			while (first->next != NULL) first = first->next;
			first->next = v;
		}
	}

	void print() {

		SinglyNode* first = head;
		while (first != NULL)
		{
			cout << first->match_ID << " " << first->team_one->getName() << " - " << first->team_two->getName() << endl;
			first = first->next;
		}

	}

	void makeMatch(Team* team_one, Team* team_two);

	void match() {

		SinglyNode* first = head;
		while (first != NULL)
		{
			makeMatch(first->team_one, first-> team_two);
			first = first->next;
		}
	}
};


League::League(vector<Team>& team_list) : teamList(team_list) {

}

League::~League() {

}


void League::generateFixture() {

	srand((unsigned)time(NULL));

	int randomMatchID = rand() % 1000;
	SinglyLinkedList matchList;

	vector<Team*> teamlist_copy;
	for (int i = 0; i < teamList.size(); i++) {
		teamlist_copy.push_back(&teamList[i]);
	}

	int random = rand() % 19;
	Team* fixed_team = teamlist_copy[random];

	teamlist_copy.erase(teamlist_copy.begin() + random);

	for (int i = 0; i < teamlist_copy.size(); i++) {

		cout << "--------" << (i + 1) << ". Hafta Fiksturu" << "--------" << endl;
		cout << "1. Mac" << " " <<  fixed_team->getName() << " - " << teamlist_copy[0]->getName() << endl;
		matchList.addBack(1, fixed_team, teamlist_copy[0]);

		for (int j = 0; j < (teamlist_copy.size() - 1) / 2; j++) {
			cout << (j + 2) << ". Mac" << " " << teamlist_copy[j + 1]->getName() << " - " << teamlist_copy[teamlist_copy.size() - 1 - j]->getName() << endl;
			matchList.addBack(1, teamlist_copy[j + 1], teamlist_copy[teamlist_copy.size() - 1 - j]);

		}
		teamlist_copy.push_back(teamlist_copy[0]);
		teamlist_copy.erase(teamlist_copy.begin());
	}
	matchList.match();
}

void SinglyLinkedList::makeMatch(Team* team_one, Team* team_two) {

	Team* home = team_one;
	Team* away = team_two;

	int team_home_goals = rand() % 7;
	int team_away_goals = rand() % 7;

	if (home->getFPerf() > away->getFPerf()) {
		team_home_goals++;
	}
	else if (home->getFPerf() < away->getFPerf()) {
		team_away_goals++;
	}

	if (home->getDPerf() > away->getDPerf()) {

		if (team_away_goals > 0) {
			team_away_goals--;
		}
	}
	else if (home->getDPerf() < away->getDPerf()) {

		if (team_home_goals > 0) {
			team_home_goals--;
		}
	}

	if (home->getMFPerf() > away->getMFPerf()) {
		team_home_goals++;
		if (team_away_goals > 0) {
			team_away_goals--;
		}
	}
	else if (home->getMFPerf() < away->getMFPerf()) {
		team_away_goals++;
		if (team_home_goals > 0) {
			team_home_goals--;
		}

	}

	if (home->getTeamPerf() > away->getTeamPerf()) {
		team_home_goals++;
		if (team_away_goals > 0) {
			team_away_goals--;
		}
	}

	else if (home->getTeamPerf() < away->getTeamPerf()) {
		team_away_goals++;
		if (team_home_goals > 0) {
			team_home_goals--;
		}
	}

	*home += team_home_goals;
	*away += team_away_goals;
	*home -= team_away_goals;
	*away -= team_home_goals;

	if (team_home_goals > team_away_goals) {
		cout << home->getName() << ": " << team_home_goals << " - " << away->getName() << ": " << team_away_goals << endl;
		cout << "Kazanan Takim: " << home->getName() << endl;
		++(*home);
		(*away)--;
	}
	else if (team_home_goals < team_away_goals) {

		cout << home->getName() << ": " << team_home_goals << " - " << away->getName() << ": " << team_away_goals << endl;
		cout << "Kazanan Takim: " << away->getName() << endl;
		++(*away);
		(*home)--;
	}
	else if (team_home_goals == team_away_goals) {

		cout << home->getName() << ": " << team_home_goals << " - " << away->getName() << ": " << team_away_goals << endl;
		cout << "Mac Sonucu: Berabere" << endl;
		(*home)++;
		(*away)++;
	}
}

void League::printStandings() {

	cout << left << setw(4) << "##" << 
		left << setw(30) << "Team Name" <<
		left << setw(4) << "MP" <<
		left << setw(4) << "W" << 
		left << setw(4) << "D" <<
		left << setw(4) << "L" <<
		left << setw(4) << "GF" <<
		left << setw(4) << "GA" <<
		right << setw(3) << "GD" <<
		right << setw(5) << "Pts" << endl;
	
	for (int i = 0; i < teamList.size(); i++) {

		for (int j = 0; j < teamList.size() - 1; j++) {
			if (teamList[j].getPoint() < teamList[j + 1].getPoint()) {
				Team temp;
				temp = teamList[j];
				teamList[j] = teamList[j + 1];
				teamList[j + 1] = temp;
			}
		}
	}

	for (int k = 0; k < teamList.size(); k++) {
		cout << right << setw(2) << k + 1 << left << setw(2) << "." <<
			left << setw(30) << teamList[k].getName() <<
			left << setw(4) << (teamList.size() - 1) << 
			left << setw(4) << teamList[k].getWin() <<
			left << setw(4) << teamList[k].getDraw() <<
			left << setw(4) << teamList[k].getLose() <<
			left << setw(4) << teamList[k].getGF() <<
			left << setw(4) << teamList[k].getGA() <<
			right << setw(3) << teamList[k].getGD() <<
			right << setw(4) << teamList[k].getPoint() << endl;
	}


	// cout << setfill(' ') << setw(15) << left << "Name" << " "
}