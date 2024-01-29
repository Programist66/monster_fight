#include <iostream>
#include <time.h>
#include <list>
#include <math.h>

using namespace std;

class Weapon
{
    protected:
        int damage;
        int ammoCount;
        int maxAmmo;
        string nameWeapon;
    public:

        Weapon(int damage, int ammoCount, int maxAmmo, string nameWeapon) : damage(damage), ammoCount(ammoCount), maxAmmo(maxAmmo), nameWeapon(nameWeapon) {}
        virtual int shoot()
        {
            if (ammoCount == 0)
            {
                return 0;
            }
            else
            {
                ammoCount -= 1;
                return damage;
            }
        }

        virtual int GetAmmo() { return ammoCount; }
        string GetName() { return nameWeapon; }
};

class Blaster : public Weapon
{
    public:
        Blaster() : Weapon(10, -1, -1, "Blaster") {}
        int GetAmmo() override { return abs(ammoCount); }
};

class Pistol : public Weapon
{
    public:
        Pistol() : Weapon(20, 6, 6, "Pistol") {}
};

class MachineGun : public Weapon
{
    public:
        MachineGun() : Weapon(5, 100, 100, "MachineGun") {}
};

class Enemy
{
    private:
        int health;
        int count_weapon;
        string Name;
        list<Weapon*>::iterator it;
    public:
        list<Weapon*> weapons;
        Enemy(int health, int count_weapon, string name) : health(health), count_weapon(count_weapon), Name(name)
        {
            for (int i = 0; i < count_weapon; i++)
            {
                int choise = rand() % 3;
                switch (choise)
                {
                case 0:
                    weapons.push_back(new Blaster());
                    cout << Name << "`s " << i + 1 << "-th weapon is " << weapons.back()->GetName() << endl;
                    break;
                case 1:
                    weapons.push_back(new Pistol());
                    cout << Name << "`s " << i + 1 << "-th weapon is " << weapons.back()->GetName() << endl;
                    break;
                case 2:
                    weapons.push_back(new MachineGun());
                    cout << Name << "`s " << i + 1 << "-th weapon is " << weapons.back()->GetName() << endl;
                    break;
                default:
                    break;
                }
            }
            it = weapons.begin();
        };
        void TakeDamage(int damage)
        {
            health -= damage;
            cout << Name << " has " << health << " HP left" << endl;
        }

        void MakeDamage(Enemy* target)
        {
            if (((*it) -> GetAmmo()) == 0)
            {
                if (*it == weapons.back())
                {
                    it = weapons.begin();
                }
                else
                {
                    it++;
                }
            }
            int damage = (*it)->shoot();
            if (damage == 0)
            {
                cout << Name << " has run out of ammo:(" << endl;
            }
            else
            {
                cout << Name << " fires a " << (*it)->GetName() << " and takes away " <<  damage << " HP from " << target->GetName() << endl;
            }
            target->TakeDamage(damage);
            if (*it == weapons.back())
            {
                it = weapons.begin();
            }
            else
            {
                it++;
            }
        }        

        bool isAmmoAvaible()
        {
            int AmmoAvaible = 0;
            for (Weapon* weapon : weapons)
            {
                AmmoAvaible += weapon->GetAmmo();
            }
            return AmmoAvaible > 0;
        }
        int GetHealth() { return health; }
        string GetName() { return Name; }
        ~Enemy()
        {
            weapons.clear();
        }
};

int main()
{
    srand(time(NULL));
    Enemy monstr1(1000, 2, "Monstr 1");
    Enemy monstr2(1000, 2, "Monstr 2");

    int round = 1;
    while (monstr1.GetHealth() > 0 and monstr2.GetHealth() > 0 and (monstr1.isAmmoAvaible() > 0 or monstr2.isAmmoAvaible() > 0))
    {
        cout << "============================ROUND " << round << "============================" << endl;
        monstr1.MakeDamage(&monstr2);
        if (monstr2.GetHealth() <= 0)
        {
            cout << "============================RESULT============================" << endl;
            cout << monstr1.GetName() << " is win!!!" << endl;
        }
        else
        {
            monstr2.MakeDamage(&monstr1);
        }
        round++;
    }    
    if (monstr1.isAmmoAvaible() <= 0 and monstr2.isAmmoAvaible() <= 0)
    {
        cout << "============================RESULT============================" << endl;
        cout << "\t\t\t\tDRAW\nBoth opponents ran out of ammo" << endl;
    }
    else if(monstr1.GetHealth() <= 0)
    {
        cout << "============================RESULT============================" << endl;
        cout << monstr2.GetName() << " is win!!!" << endl;
    }

    return 0;
}
