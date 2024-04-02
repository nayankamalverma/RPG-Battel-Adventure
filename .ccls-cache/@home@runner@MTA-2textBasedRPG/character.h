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