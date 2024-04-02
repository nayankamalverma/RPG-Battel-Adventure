#include <iostream>
#include<ctime>
#include <memory>
#include <vector>


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

class Character{
	protected:
		int currentHealth;
		int maxhealth;
		int meleeDamage;
	public:
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