#include "items.h"

Items::Items()
{
    cooldown=0;
}

void Items::putOnCooldown(){
    cooldown=5;
}
void Items::reduceCooldown(){
    cooldown-=1;
}
int Items::getCooldown(){
    return cooldown;
}
void Items::resetCooldown(){
    cooldown=0;
}
