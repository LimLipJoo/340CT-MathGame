#ifndef ITEMS_H
#define ITEMS_H


 class Items
{
public:
    Items();
    void putOnCooldown();
    void reduceCooldown();
    int getCooldown();
    void resetCooldown();
private:
    int cooldown;
};

#endif // ITEMS_H
