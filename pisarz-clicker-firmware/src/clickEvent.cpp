#include "clickEvent.h"

ClickEvent clickEvent_create(uint16_t character, uint8_t *returnCode){
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

void clickEvent_update(ClickEvent *event, ClickEvent prevEvent ,unsigned long time){
    // if(event->state == CREATED && (prevEvent.state == EMPTY || (prevEvent.state >= CLICKING && time - prevEvent.clickingTime >= SERVO_SEPARATE_KEY_DELAY))){
    //     servoDown(event->key);
    //     event->clickingTime = time;
    //     event->state = CLICKING;
    // }
    // else if(event->state == CLICKING && time - event->clickingTime >= SERVO_CLICKING_TIME){
    //     servoUp(event->key);
    //     event->state = RETURNING;
    // }
    // else if(event->state == RETURNING && time - event->clickingTime >= SERVO_DONE_TIME){
    //     event->state = DONE;
    // }
    time = millis();
    if(event->state == CREATED){
        if(key_checkEqual(event->key, prevEvent.key))
            return; // Break must be inserted here
        if(prevEvent.state >= DONE || prevEvent.state == EMPTY){
            servoDown(event->key);
            event->state = CLICKING;
            event->clickingTime = time;
        }
    }
    else if(event->state == CLICKING){
        if(time - event->clickingTime >= SERVO_CLICKING_TIME){
            servoUp(event->key);
            event->state = RETURNING;
        }
    }
    else if(event->state == RETURNING){
        if(time - event->clickingTime >= SERVO_DONE_TIME){
            event->state = DONE;
        }
    }
}