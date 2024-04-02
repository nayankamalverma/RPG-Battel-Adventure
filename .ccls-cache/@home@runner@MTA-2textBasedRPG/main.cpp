#include <iostream>
#include<ctime>
#include <memory>
#include <vector>
#include <stdlib.h>

using namespace std;

int randNumber(int min=0, int max=100){
	srand(time(0));
	return rand() % (max - min + 1) + min;
}

//method returns true with x% probablity
bool probablity(int x){
	srand(time(0));
	if(rand()%100<=x)return true;
	return false;
}

//Character class is used in both player and enemie classess
class Character{
	
	protected:
		int currentHealth;
		int maxhealth;
		int meleeDamage;
		int maxHealpoint;// max healthPoint for randomizing healing
	public:
		Character(){}
		Character(int currHp, int maxHp, int meleeDmg,int hp):currentHealth(currHp),maxhealth(maxHp),meleeDamage(meleeDmg),maxHealpoint(hp){}
		virtual ~Character()=default;
		virtual void takeDamage(int dmg)=0;
		virtual int heal()=0;
		virtual int melleeAttack()=0;

		//getter setters
		int getHealth(){
			return currentHealth;
		}
		void setHealth(int health){
			currentHealth=health;
		}

		int getMaxHealth(){
			return maxhealth;
		}
		void setMaxHealth(int health){
			maxhealth=health;
		}

		int getMeleeDamage(){
			return meleeDamage;
		}
		void setMeleeDamage(int dmg){
			meleeDamage=dmg;
		}
};

class player: public Character{
	
	int rangedDamage;
	int specialAbilitiesChance; //consider as percent
	bool isInvincible;
	string specialAbilities[4]={"CriticalHit","Blocker","LifeSteal","RangedAttack"};
	string collectibles[5]={"Map" ,"Sword","Shield", "Armour","Bow"};
	int specialAbliityCount; //special abilities activated
	int collectibleCount; // items collected
	int rangedAttackCount; //ranged attacks used 
	public:
		bool isAlive;
		player(int currHp=100,int maxHp=100,int mDmg=15, int hp=15, int rDmg=10, int spAbChance= 10, bool isInv=false, int spAbCnt=0, int collectibleCnt=0):Character(currHp,maxHp,mDmg,hp),rangedDamage(rDmg), specialAbilitiesChance(spAbChance), isInvincible(isInv), specialAbliityCount(spAbCnt), collectibleCount(collectibleCnt) {
			isAlive=true;
		}

		void playerStats(int lvl){
			cout<<"-----------------Player Stats-----------------"<<endl;
			cout<<"Current Health: "<<currentHealth<<endl;
			cout<<"Melee Damage: "<<meleeDamage<<endl;
			if(lvl>5)cout<<"Ranged Damage: "<<rangedDamage<<endl;
			cout<<"Items collected: "<<endl;
			for(int i=1;i<=collectibleCount;i++){
				cout<<collectibles[i-1]<<",";
			}
			cout<<endl;
			cout<<"Special Abilities: "<<endl;
			for(int i=1;i<=specialAbliityCount;i++){
				cout<<specialAbilities[i-1]<<",";
			}
			cout<<endl;
			cout<<"--------------------------------------------\n";
		}

		void upadteHealth(int health){
			currentHealth += health;
			if(currentHealth > maxhealth){
				currentHealth = maxhealth;
			}
		}

		void upgradePlayer(int lvl){
			cout<<"\nPlayer advanced to next level\n"<<endl;
			maxhealth+=20;
			currentHealth=maxhealth;
			meleeDamage+=5;
			updateC();
			if(lvl> 2)updateSA();
			cout<<"----------------------------\n";
			cout<<"\nPlayer Stats after upgrade"<<endl;
			playerStats(lvl);
		}

		// updating special ability
		void updateSA(){
			cout << "you got a new Special Abiliity: " << specialAbilities[specialAbliityCount++] <<endl;
		}
		// updating collectible
		void updateC(){
			cout << "you got a new Collectible: " << collectibles[collectibleCount++] <<endl;
		}

		void setSpecialAbilitiesChance(int x){
			specialAbilitiesChance=x;
		}
		

		//method returnd the damage done by player
 		int melleeAttack() override{
			int dmg = randNumber(meleeDamage-7, meleeDamage);
			if(probablity(specialAbilitiesChance) && specialAbliityCount >=1){
				dmg += 5*dmg;
				cout<<"\nSpecial Ability: Critical Hit\n";
				cout<<"You slams weapon across the enemy's face";
			}
			else if(probablity(specialAbilitiesChance) && specialAbliityCount >=3){
				int hp=randNumber(5,15)*3;
				upadteHealth(hp);
				cout<<"\nSpecial Ability: Life-Steal\nyou healed "<<hp<<" health\n";
			}
			cout<<"you have dealt "<<dmg<<" damage\n\n";
			rangedAttackCount++;
			return dmg;
		}

		// method to perforn ranged attack
		int attckRanged(){
			int dmg=0;
			if(rangedAttackCount >2 && specialAbliityCount >=4){
				cout << "!!! Ranged Hit Special Ability Activated !!!\n";
				cout << "Your hero is invinsible for the next turn!\n";
				isInvincible = true;
				dmg=rangedDamage;
				rangedAttackCount=1;
			}
			else{
				cout<<"Ranged attack failed.\nPerforming mellee attack instead.\n";
				dmg=melleeAttack();
			}
			return dmg;
		}

		// method to heal player
		int heal() override{
			cout<<"Player used heal spell\n";
			int hp=randNumber(maxHealpoint-8,maxHealpoint);
			upadteHealth(hp);
			cout<<"You healed "<<hp<<" health\n"<<endl;
			rangedAttackCount++;
			return 0;
		}

		void takeDamage(int dmg) override{
			//player is invenciible if performed ranged attack last turn
			if(isInvincible){
				cout<<"You are invinsible. No damage taken.\n";
				isInvincible = false;
				dmg=0;
			}
			// bloker special ability
			//hero takes damage, but he can avoid it if he has blocker ability and some luck
			else if(probablity(specialAbilitiesChance)&& specialAbliityCount >=2){
				cout<<"\nSpecial Ability: Blocker\n";
				cout<<"You blocked the attack\n"<<endl;
				dmg=0;
			}
			currentHealth-=dmg;		
		}

		~player(){}
};

class goblin: public Character{
	public:
		goblin(int currHp=55, int maxHp=50, int mDmg=10,int hp=10):Character(currHp,maxHp,mDmg,hp){}

		virtual ~goblin(){};

		char RandomChoice()
		{
			return (rand() % 5) ? 'M' : 'H'; // 20% chance of H 80% of M
		}

		//upgrade Goblins
		void upgradeGoblins(int lvl){
			maxhealth=currentHealth=50+(lvl*5);
			meleeDamage=5+(lvl*5)/2;
		}

		//overriding take damage functon
		virtual void takeDamage(int dmg) override{
			if(!(bool)(rand()%10)){
				cout<<"\nGoblin blocked your attak\n";
				dmg=0;
			}
			currentHealth-=dmg;
		}

		//overriding heal function
		virtual	int heal() override{
			cout << "The enemy drank his healing potion!\n";
			currentHealth += randNumber(maxHealpoint-5,maxHealpoint);
			return 0;
		}

		//overriding attack function
		virtual int melleeAttack() override{
			int dmg = randNumber(meleeDamage-7,meleeDamage);
			cout << "Goblin attacks you!\ngiven "<<dmg<<" damage\n"<<endl;
			return dmg;
		}
		
};

class Murloc: public goblin{
	public:
		Murloc(int currHp=300,int maxHp=300, int meleeDmg=30, int hp =20):goblin(currHp,maxHp,meleeDmg,hp){
		}

		//overriding attack function
		int melleeAttack() override{
			int dmg = randNumber(meleeDamage-10,meleeDamage);
			if(probablity(10)){
				cout<< "Murloc used his ultimate ability: Spell Crash!\n";
				dmg *= 2;
			}
			cout << "Murloc attacks you!\ngiven "<<dmg<<" damage\n"<<endl;
			return dmg;
		}

		//overriding heal function
		int heal() override{
			cout << "Murloc used health regenration!!!\n"<<endl;
			currentHealth+=randNumber(maxHealpoint-8,maxHealpoint);
			return 0;
		}

		void takeDamage(int dmg) override{
			if(!(bool)(rand()%5))
			{
				cout << "Murlock has blocked your damage with his shield!!!!\n";
				dmg = 0;
			}
			currentHealth-=dmg;
		}
};

class Level{
	private:
		int numOfGoblins;
		int currLevel;
		vector<std::shared_ptr<goblin>> goblins;

		void addGoblins(){
			int health= 50+(currLevel*5);
			int meleeDmg=10+(currLevel*5)/2;
			int healPoint=8+(currLevel*4);
			for(int i=0;i<currLevel;i++){
				goblins.push_back(std::shared_ptr<goblin> (new goblin(health, health, meleeDmg, healPoint)));
			}
		}

	public:
		Level(int lvl){
			cout<<"Level: "<<lvl<<endl;
			cout<<"Danger waits ahead...\n\n";
			numOfGoblins=lvl;
			currLevel=lvl;
			addGoblins();
		}

		int getLvl(){
			return currLevel;
		}

		int getNumOfGoblins(){
			return numOfGoblins;
		}

		//return list of goblins
		vector<std::shared_ptr<goblin>> getGoblins(){
			return goblins;
		}
};


class Game{
	unique_ptr<player> p;
	
	public:
		void startGame(){
			gameStory();
			rules();
			spawnPlayer();
		}

		void gameLoop()
		{
			if(!p)
			{
				cout << "Player has not been spawned correctly!\n";
				return;
			}
			int i = 1;
			p->playerStats(i);
			for( ; i < 6 ; i++)
			{
				LoadLevel(i);
				cout << "----------------------------------\n";
				//after level complete update special abilities and collectibles
				//upgrade player stats => health, damage, level
				if(p->isAlive){
					p->upgradePlayer(i);
					cout << "----------------------------------\n";
				}else{
					break;
				}
			}
			if(p->isAlive && i==6){
				Level6();
			}
		}

	void spawnPlayer() // instantiate the player
	{
		p = make_unique<player>();
	}

	// mechanism of first 5 levels
	void LoadLevel(int lvl){
		unique_ptr<Level> currLevel = make_unique<Level>(lvl);
		vector<std::shared_ptr<goblin>> levelEnemies = currLevel->getGoblins();
		cout<<"There are "<< currLevel->getNumOfGoblins() <<"goblins in this level.\nTo pass you have kill all the goblins in a sequence\n";
		std::shared_ptr<goblin> enemy = levelEnemies[0];
		
		//loop till all goblins are killed and player is alive
		while(p->getHealth() > 0 && enemy->getHealth() > 0){
			cout << "----------------------------------\n";

			//handling input from user
			cout<< "Press H(to heal) or M(melee attack) " <<endl;
			char playerIp;
			cin >> playerIp;
			//convert palyer input to uppercase
			playerIp = toupper(playerIp);
			while(playerIp!='M' && playerIp!='H'){
				cout << "Invalid input. Please enter H or M\n";
				cin >> playerIp;
				playerIp = toupper(playerIp);
			}

			// action performed by player
			int dmgToEnimy = playerChoice(playerIp);
			enemy->takeDamage(dmgToEnimy);
			if(enemy->getHealth()<1){
				cout << "You have killed the goblin\n";
				levelEnemies.erase(levelEnemies.begin());
				if(!levelEnemies.empty()){
					enemy= levelEnemies[0];
					cout<<"Another goblin is approaching with health "<<enemy->getHealth()<<endl;
				}
			}
			// action performed by enemy
			if(enemy->getHealth()>0){
				p->takeDamage(enemyChoice(enemy->RandomChoice(),enemy)); 
			}
			if(p->getHealth()>1 && enemy->getHealth()>1){
				cout<<"Player health: "<<p->getHealth()<<endl;
				cout<<"Enemy health: "<<enemy->getHealth()<<endl;}
		}
		if(p->getHealth()<1){
			cout << "You have died\n";
			p->isAlive=false;
		}
	}

	int playerChoice(char _ch) // player action decider based on the input
	{
		if(_ch=='H' || _ch=='h')
		{
			p->heal();
			return 0;
		}
		else if(_ch=='M' || _ch=='m')
		{
			return p->melleeAttack();
		}
		else
		{
			return p->attckRanged();
		}

	}

	int enemyChoice(char _ch, shared_ptr<goblin> e) //enemy action decider based on random generated input
	{
		if(_ch=='M')
		{
			return e->melleeAttack();
		}
		else
		{
			return e->heal();
		}
	}
	
	void Level6(){
		cout<<"You have reached the final level\nMurloc Arriving!!!!!"<<endl;
		shared_ptr<Murloc> murloc = make_unique<Murloc>();
		p->setSpecialAbilitiesChance(20);
		while(p->getHealth()>0 && murloc->getHealth()>0){
			cout<< "Press H(to heal) or M(melee attack) or R(Ranged attack)"<<endl;
			char playerIp;
			cin>>playerIp;
			playerIp = toupper(playerIp);
			while(playerIp!='M' && playerIp!='H' && playerIp!='R'){
				cout << "Invalid input. Please enter H, M or R.\n";
				cin >> playerIp;
				playerIp = toupper(playerIp);
			}
			int dmgToEnemy = playerChoice(playerIp);
			murloc->takeDamage(dmgToEnemy);
			if(murloc->getHealth()<1){
				cout << "You have killed a Murloc\n";
				cout<<"Villagers are safe now\n";
				break;
			}
			p->takeDamage(enemyChoice(murloc->RandomChoice(),murloc));
			if(p->getHealth()<1){
				cout << "You have died\n";
				p->isAlive=false;
				break;
			}
			cout<<"Player health: "<<p->getHealth()<<endl;
			cout<<"Murloc health: "<<murloc->getHealth()<<endl;
		}
		
	}

	void gameStory(){
		cout<<"Once upon a time, in the peaceful village of Eldoria, nestled deep within the enchanted forests, a darkness began to stir.\n Murlocs, fearsome monsters known for their ruthless nature, invaded the village, spreading chaos and despair. \nThe villagers were defenseless against the onslaught, and their only hope lay in the hands of a courageous hero."<<endl;

		cout<<"\nThe hero, Arthur, embarked on a perilous journey to confront the Murlocs and restore peace to the village."<<endl;
	}

	void rules() // print game rules
		{
			cout << "\nRules:\n";
			cout << "1. You hero has the ability to perform melee as well as ranged attack.\n";
			cout << "2. You can also perform a special attack once every level.\n";
			cout << "3. Kill enemies, collect all four gear of arms and survie till the end to fight Murlocs.\n";
			cout << "4. If your hero dies, the game is over.\n\n";
		}
};

int main(){
	srand(time(0));
	char ch;
	Game* game= new Game();
	game->startGame();//dispaly game story and rules
	cout<<"\nPress S to start the game or any other key to exit\n";
	do{
		cin>>ch;
		if(ch=='S' || ch == 's') {
			game->gameLoop(); //game loop
			delete game;
			cout<<"\nPress S to restart the game or any other key to exit\n";
			game = new Game();
		}
	}while(ch=='S' || ch=='s');
	return 0;
}