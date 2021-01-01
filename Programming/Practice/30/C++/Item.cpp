#include <ostream>
#include <cstdlib>

enum ItemType {
   COIN, RUNE, WEAPON, ARMOR
};

struct Coin {
   int count;
};

enum Element {
   FIRE, WATER, EARTH, AIR
};

struct Rune {
   int level;
   Element element;
};

struct Weapon {
   int damage;
   int critical;
   int durability;
};

struct Armor {
   int guard;
   int durability;
};

struct Item {
   ItemType item_type;
   union {
      Coin coin;
      Rune rune;
      Weapon weapon;
      Armor armor;
   } item;
};

Item randomItem() {
   /*
   SORTED BY POSSIBILITY
   0.06   	Rune 	   level = 10; element = FIRE
   0.07   	Rune 	   level = 10; element = EARTH
   0.13   	Rune 	   level = 10; element = WATER
   0.14   	Rune 	   level = 10; element = AIR
   0.6   	Rune 	   level = 5;  element = FIRE
   0.7   	Rune 	   level = 5;  element = EARTH
   1.3   	Rune 	   level = 5;  element = WATER
   1.4   	Rune 	   level = 5;  element = AIR
   1.4   	Weapon 	damage = 100; critical = 0;  durability = 100
   1.4   	Weapon 	damage = 75;  critical = 50; durability = 100
   2.8   	Armor 	guard = 50; durability = 100
   6   	   Rune 	   level = 1;  element = FIRE
   7   	   Rune 	   level = 1;  element = EARTH
   13   	   Rune 	   level = 1;  element = WATER
   14   	   Rune 	   level = 1;  element = AIR
   50   	   Coin 	   count = 1000
   "IF" IMPLEMENTATION BELOW
   ELSE UNNECESSARY BECAUSE OF RETURN
   */
   double randPercent = ((double)rand() / (RAND_MAX)) * 100;
   if (randPercent < 0.06) {
      return Item{
         RUNE, {.rune = { 10, FIRE }}
      };
   }
   randPercent -= 0.06;
   if (randPercent < 0.07) {
      return Item{
         RUNE, {.rune = { 10, EARTH }}
      };
   }
   randPercent -= 0.07;
   if (randPercent < 0.13) {
      return Item{
         RUNE, {.rune = { 10, WATER }}
      };
   }
   randPercent -= 0.13;
   if (randPercent < 0.14) {
      return Item{
         RUNE, {.rune = { 10, AIR }}
      };
   }
   randPercent -= 0.14;
   if (randPercent < 0.6) {
      return Item{
         RUNE, {.rune = { 5, FIRE }}
      };
   }
   randPercent -= 0.6;
   if (randPercent < 0.7) {
      return Item{
         RUNE, {.rune = { 5, EARTH }}
      };
   }
   randPercent -= 0.7;
   if (randPercent < 1.3) {
      return Item{
         RUNE, {.rune = { 5, WATER }}
      };
   }
   randPercent -= 1.3;
   if (randPercent < 1.4) {
      return Item{
         RUNE, {.rune = { 5, AIR }}
      };
   }
   randPercent -= 1.4;
   if (randPercent < 1.4) {
      return Item{
         WEAPON, {.weapon = { 100, 0, 100 }}
      };
   }
   randPercent -= 1.4;
   if (randPercent < 1.4) {
      return Item{
         WEAPON, {.weapon = { 75, 50, 100 }}
      };
   }
   randPercent -= 1.4;
   if (randPercent < 2.8) {
      return Item{
         ARMOR, {.armor = { 50, 100 }}
      };
   }
   randPercent -= 2.8;
   if (randPercent < 6) {
      return Item{
         RUNE, {.rune = { 1, FIRE }}
      };
   }
   randPercent -= 6;
   if (randPercent < 7) {
      return Item{
         RUNE, {.rune = { 1, EARTH }}
      };
   }
   randPercent -= 7;
   if (randPercent < 13) {
      return Item{
         RUNE, {.rune = { 1, WATER }}
      };
   }
   randPercent -= 13;
   if (randPercent < 14) {
      return Item{
         RUNE, {.rune = { 1, AIR }}
      };
   }
   randPercent -= 14;
   if (randPercent < 50) {
      return Item{
         COIN, {.coin = { 1000 }}
      };
   }
   else {
      throw "WTF randPercent > 100";
   }
}

Item operator ++ (Item item) {
   item = randomItem();
   return item;
}

std::ostream& operator << (std::ostream& o, Item item) {
   std::string res;
   switch (item.item_type) {

   case COIN:
      res = "1000 gold";
      break;

   case RUNE:
      res = "Rune of ";

      switch (item.item.rune.element) {
      case FIRE: res += "fire"; break;
      case EARTH: res += "earth"; break;
      case WATER: res += "water"; break;
      case AIR: res += "air"; break;
      };

      res += " " + std::to_string(item.item.rune.level) + " lvl";
      break;

   case WEAPON:
      if (item.item.weapon.critical == 0) res = "Weapon God Killer";
      else if (item.item.weapon.critical == 50) res = "Weapon Demon Slayer";
      break;

   case ARMOR:
      res = "Bronezhiletka";
      break;
   }

   return o << res;
}