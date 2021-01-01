#include "./Item.cpp"

#include <vector>
#include <ostream>

using LootBox = std::vector<Item>;

LootBox& operator << (LootBox& lootBox, Item item) {
   lootBox.push_back(item);
   return lootBox;
}

std::ostream& operator << (std::ostream& o, LootBox lootBox) {
   return o << lootBox[0] << std::endl << lootBox[1] << std::endl << lootBox[2] << std::endl;
}

LootBox generateLootBox() {
   LootBox lootBox;
   for (int i = 0; i < 3; i++) {
      Item item;
      lootBox << ++item;
   }
   return lootBox;
}