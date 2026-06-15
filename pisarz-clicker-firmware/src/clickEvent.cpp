#include "clickEvent.h"
#include "servoDrivers.h"

ClickEvent clickEvent_create(uint8_t character, uint8_t *returnCode){
    Key key = key_create(character, returnCode);

    ClickEvent event;
    event.key = key;
    event.state = CREATED;

    return event;
}

ClickEvent clickEvent_createEmpty(){
    Key key = key_createEmpty();
    ClickEvent event;
    event.key = key;
    event.state = EMPTY;
    event.clickingTime = 0;

    return event;
}

void clickEvent_update(ClickEvent *event, ClickEvent *prevEvent){
    unsigned long time = millis();
    if(event->state == CREATED){        /* CREATED -> CLICKING jeśli poprzedni event jest w trakcie klikania i minął czas BEETWEEN_CLICKS */
        if((prevEvent->state >= CLICKING && time - prevEvent->clickingTime >= SERVO_TIME_BEETWEEN_CLICKS) || prevEvent->state == EMPTY){
            servoDown(event->key);
            event->state = CLICKING;
            event->clickingTime = time;
        }
    }
    else if(event->state == CLICKING){  /* CLICKING -> RETURNING jeśli znajduje sie w stanie CLICKING dłużej niż CLICKING_TIME */
        if(time - event->clickingTime >= SERVO_CLICKING_TIME){
            servoUp(event->key);
            event->state = RETURNING;
        }
    }
    else if(event->state == RETURNING){ /* RETURNING -> DONE jeśli znajduje się w stanach CLICKING i RETURNING dłużej niż RETURNING_TIME */
        if(time - event->clickingTime >= SERVO_RETURNING_TIME){
            event->state = DONE;
        }
    }
}