#include "clickEventTab.h"

ClickEvent clickEventTab[CLICKEVENT_TAB_MAX_LEN];
uint8_t clickEventTabLen = 0;

void clickEventTab_addEvent(ClickEvent event){
    if(clickEventTabLen < CLICKEVENT_TAB_MAX_LEN){
        clickEventTab[clickEventTabLen] = event;
        clickEventTabLen++;
    }
}

void clickEventTab_removeDoneEvents(){
    while(clickEventTab[0].state == DONE){
            for(uint8_t i=0; i < clickEventTabLen-1; i++)
                clickEventTab[i] = clickEventTab[i+1];
            clickEventTab[clickEventTabLen-1] = clickEvent_createEmpty();
            clickEventTabLen--;
        }
}

void clickEventTab_updateEvents(){
    ClickEvent prevEvent = clickEvent_createEmpty();
    for(uint8_t i=0; i < clickEventTabLen; i++){
        if(clickEventTab[i].state != EMPTY){
            if(key_checkEqual(clickEventTab[i].key, prevEvent.key))
                break;
            clickEvent_update(&(clickEventTab[i]), prevEvent);
            prevEvent = clickEventTab[i];
        }
    }
}

void clickEventTab_showEventTab(){
    uint8_t loops = clickEventTabLen;
    if(loops){
        Serial.print("Events: ");
        Serial.println(loops);
        if(loops > 5)
            loops = 5;
        Serial.print("=== === Event Tab === ");
        for(int i=0; i < loops; i++){
            Serial.print("Idx: ");
            Serial.print(i);
            Serial.print("   state: ");
            Serial.print(clickEventTab[i].state);
            Serial.print("   driver: ");
            Serial.print((uintptr_t)clickEventTab[i].key.driver, HEX);
            Serial.print("   key.channel: ");
            Serial.print(clickEventTab[i].key.channel);
            Serial.print("   key.dir: ");
            Serial.println(clickEventTab[i].key.dir);
        }
        Serial.println();
    }
}