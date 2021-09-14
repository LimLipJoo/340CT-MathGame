#include "hearts.h"

Hearts::Hearts()
{
    hearts=3;
}

void Hearts::addHearts(){
    hearts+=1;
}
void Hearts::minusHearts(){
    hearts-=1;
}
int Hearts::getHearts(){
    return hearts;
}
void Hearts::resetHearts(){
    hearts=3;
}
