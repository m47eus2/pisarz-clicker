#include "clickEventTab.h"

ClickEvent clickEventTab[CLICKEVENT_TAB_MAX_LEN];
uint8_t clickEventTabLen = 0;

void clickEventTab_addEvent(uint8_t incommingByte){
    if(clickEventTabLen < CLICKEVENT_TAB_MAX_LEN){
        static uint8_t polishMode = 0;
        uint8_t retCode;

        // Polish character
        if(polishMode == 1){
            ClickEvent altEvent = clickEvent_create(ALT_CODE, &retCode);

            ClickEvent event = clickEvent_createEmpty();
            switch(incommingByte){
                case 133:
                    event = clickEvent_create('a', &retCode);
                    break;
                case 135:
                    event = clickEvent_create('c', &retCode);
                    break;
                case 153:
                    event = clickEvent_create('e', &retCode);
                    break;
                case 130:
                    event = clickEvent_create('l', &retCode);
                    break;
                case 132:
                    event = clickEvent_create('n', &retCode);
                    break;
                case 179:
                    event = clickEvent_create('o', &retCode);
                    break;
                case 155:
                    event = clickEvent_create('s', &retCode);
                    break;
                case 186:
                    event = clickEvent_create('z', &retCode);
                    break;
                case 188:
                    event = clickEvent_create('z', &retCode);
                    break;
                default:
                    retCode = 1;
            }
            if(retCode == 0 && clickEventTabLen+1 < CLICKEVENT_TAB_MAX_LEN){
                clickEventTab[clickEventTabLen] = altEvent;
                clickEventTabLen++;
                clickEventTab[clickEventTabLen] = event;
                clickEventTabLen++;
            }
            polishMode = 0;
        }
        // Big character
        else if(incommingByte >= 65 && incommingByte <= 90){
            ClickEvent shiftEvent = clickEvent_create(SHIFT_CODE, &retCode);
            ClickEvent event = clickEvent_create(incommingByte+32, &retCode);

            if(retCode == 0 && clickEventTabLen+1 < CLICKEVENT_TAB_MAX_LEN){
                clickEventTab[clickEventTabLen] = shiftEvent;
                clickEventTabLen++;
                clickEventTab[clickEventTabLen] = event;
                clickEventTabLen++;
            }
        }
        else{
            // Polish character
            if(incommingByte == 196 || incommingByte == 197)
                polishMode = 1;
            else{
                // Normal character
                ClickEvent event = clickEvent_create(incommingByte, &retCode);
                if(retCode == 0){
                    clickEventTab[clickEventTabLen] = event;
                    clickEventTabLen++;
                }
            }
        }
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
            // Double click
            // if(key_checkEqual(clickEventTab[i].key, prevEvent.key))
            //     break;

            if(i != 0 && prevEvent.state < CLICKING)
                break;

            // Sprawdzenie czy nie istnieje event z tym samym key
            uint8_t breakingUpdateLoop = 0;
            for(uint8_t j=0; j<i; j++){
                if(key_checkServoEqual(clickEventTab[i].key, clickEventTab[j].key))
                    breakingUpdateLoop = 1;
            }
            if(breakingUpdateLoop)
                break;

            clickEvent_update(&(clickEventTab[i]), &prevEvent);
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
        Serial.println("=== === Event Tab === ");
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