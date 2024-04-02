#include "Character.h"
#include <iostream>

using namespace std;

//Character class is used in both player and enemie classess

class player: public Character{

	int currentLevel;	
	int rangedDamage;
	int specialAbilitiesChance;
	bool isInvincible;
	string specialAbilities[4]={"CriticalHit","Blocker","LifeSteal","RangedAttack"};
	string collectibles[5]={"Map" ,"Sword","Shield", "Armour","Bow"};
	int specialAbliityCount; //special abilities activated
	int collectibleCount; // items collected
	public:
		bool isAlive;
		player(){
			currentHealth = maxhealth = 100;
			meleeDamage = 15; 
			rangedDamage = 10;
			currentLevel=1;
			specialAbilitiesChance = 10;
			isInvincible = false;
			specialAbliityCount = 0;
			collectibleCount = 0;
			isAlive=true;
		}

		void playerStats(){
			cout<<"-----------------Player Stats-----------------"<<endl;
			cout<<"Current Health: "<<currentHealth<<endl;
			cout<<"Melee Damage: "<<meleeDamage<<"\nRanged Damage: "<<rangedDamage<<endl;
			cout<<"Current Level: "<<currentLevel<<endl;
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

		void pgradePlayer(){
			cout<<"\n Player advanced to next level"<<endl;
			maxhealth+=20;
			currentHealth=maxhealth;
			meleeDamage+=5;
			cout<<"\n Player Stats after upgrade"<<endl;
			currentLevel++;
			updateC();
			if(currentLevel>1)updateSA();
			playerStats();
		}

		// updating special ability
		void updateSA(){
			cout << "you got a new Special Abiliity: " << specialAbilities[++specialAbliityCount] <<endl;
		}
		// updating collectible
		void updateC(){
			cout << "you got a new Collectible: " << collectibles[++collectibleCount] <<endl;
		}

		void setSpecialAbilitiesChance(int x){
			specialAbilitiesChance=x;
		}
		void setCurrentLevel(int _level)
		{
			currentLevel = _level;
		}
		int getCurrentLevel ()
		{
			return currentLevel;
		}

		//method returnd the damage done by player
		int melleeAttack() override{
			int dmg = meleeDamage;
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
			cout<<"you have dealt "<<dmg<<" damage\n";
			return dmg;
		}

		// method to perforn ranged attack
		int attckRanged(){
			int dmg=0;
			if(probablity(specialAbilitiesChance) && specialAbliityCount >=4){
				cout << "!!! Ranged Hit Special Ability Activated !!!\n";
				cout << "Your hero is invinsible for the next turn!\n";
				isInvincible = true;
				dmg=rangedDamage;
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
			int hp=currentLevel*10;
			upadteHealth(hp);
			cout<<"You healed "<<hp<<" health\n";
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
				cout<<"You blocked the attack\n";
				dmg=0;
			}
			currentHealth-=dmg;		
		}

		~player(){}
};