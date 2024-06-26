#pragma once
#include <string>
#include<iostream>
using namespace std;

struct Sharingan {
public:
	void activate() {
		cout << "Sharingan is active\n";
	}
};
struct Byakugan {
public:
	void activate() {
		cout << "Byakugan is active\n";
	}
};
struct Normal {
public:
	void activate() {
		cout << "No effects\n";
	}
};
template <typename T>
concept normElse = (same_as<T, Byakugan> or same_as<T, Sharingan> == false);

template <typename T>
concept byakuganElse = (same_as<T, Byakugan> == true);

template <typename T>
concept sharinganElse = (same_as<T, Sharingan> == true);


class jutsu_Style {
public:
	virtual void jutsu() = 0;
	virtual ~jutsu_Style() {}
};
class fire_Jutsu : public jutsu_Style {
	void jutsu() override {
		cout << "use fire style jutsu\n";
	}
};
class water_Jutsu :public jutsu_Style {
	void jutsu() override {
		cout << "use water style jutsu\n";
	}
};
class wind_Jutsu :public jutsu_Style {
	void jutsu() override {
		cout << "use wind style jutsu\n";
	}
};
class Shinobi {
public:
	string tagline = "will of fire";
	string getName() {
		return name;
	};
	string getRang() {
		return rang;
	}
	string getClan() {
		return clanName;
	}
	Shinobi* operator+(string nameunit) {
		auto temp = this;
		temp->setClan(temp->getClan() + "-" + nameunit);
		return temp;
	}
	void setClan(string c) {
		clanName = c;
	}
	void setShinobi(string s) {
		name = s;
		int i = rand() % 3;
		switch (i) {
		case 0:rang = "Jounin";
			break;
		case 1:rang = "Chuunin";
			break;
		case 2:rang = "Genin";
			break;
		default:
			break;
		}
	}
	void setJutsuStyle(jutsu_Style* newstyle) {
		delete style;
		style = newstyle;
	}
	template <typename T>
		requires sharinganElse<T>
	void UseSharingan(T a) {
		a.activate();
	}
	template <typename T>
		requires byakuganElse<T>
	void UseByakugan(T a) {
		a.activate();
	}
	template <typename T>
		requires normElse<T>
	void UseNorm(T a) {
		a.activate();
	}
	void jutsu() {
		style->jutsu();
	}
	virtual void RootSpell() = 0;

private:
	jutsu_Style* style;
	string clanName;
	string name;
	string rang;
};
class teams {
public:
	friend ostream& operator<<(ostream& os, const teams* team) {
		os << "Team " << team->number << "\n";
		os << "Leader: " << team->leader << "\n";
		os << team->name1 << "\n";
		os << team->name2 << "\n";
		os << team->name3 << "\n";
		return os;
	}
	teams(Shinobi* unit1, Shinobi* unit2, Shinobi* unit3) {
		name1 = unit1->getName() + " " + unit1->getClan();
		name2 = unit2->getName() + " " + unit2->getClan();
		name3 = unit3->getName() + " " + unit3->getClan();
		if (unit1->getRang() == "Jounin") {
			leader = unit1->getName();
		}
		else if (unit2->getRang() == "Jounin") {
			leader = unit2->getName();
		}
		else if (unit3->getRang() == "Jounin") {
			leader = unit3->getName();
		}
		else if (unit1->getRang() == "Chuunin") {
			leader = unit1->getName();
		}
		else if (unit2->getRang() == "Chuunin") {
			leader = unit2->getName();
		}
		else if (unit3->getRang() == "Chuunin") {
			leader = unit3->getName();
		}
		else {
			int num = rand() % 3;
			switch (num) {
			case(0):leader = unit1->getName();
				break;
			case(1):leader = unit2->getName();
				break;
			default:leader = unit3->getName();
				break;
			}
		}
	};
private:
	int number = rand() % 7 + 1;
	string leader;
	string name1;
	string name2;
	string name3;
};

class Uchiha :public Shinobi {
public:
	Uchiha(string Name , jutsu_Style* style) {
		setShinobi(Name);
		setClan("Uchiha");
		setJutsuStyle(style);
	}
	Sharingan getEyes() {
		return eye;
	}
	void RootSpell() {
		cout << "Great Fireball" << endl;
	}
private:
	Sharingan eye;
};

class Hugo :public Shinobi {
public:
	Hugo(string Name, jutsu_Style* style) {
		setShinobi(Name);
		setClan("Hugo");
		setJutsuStyle(style);
	}
	void RootSpell() {
		cout << "Eight Trigrams Palms Revolving Heaven" << endl;
	}
	Byakugan getEyes() {
		return eye;
	}
private:
	Byakugan eye;
};

class Udzumaki :public Shinobi {
public:
	Udzumaki(string Name, jutsu_Style* style) {
		setShinobi(Name);
		setClan("Udzumaki");
		setJutsuStyle(style);
	}
	void RootSpell() {
		cout << "Shiki Fujin" << endl;
	}
	Normal getEyes() {
		return eye;
	}
private:
	Normal eye;
};
