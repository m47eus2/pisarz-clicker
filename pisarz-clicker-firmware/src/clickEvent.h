#ifndef CLICKEVENT_H
#define CLICKEVENT_H

#include "servoDrivers.h"
#include "key.h"

typedef enum{
    EMPTY,
    CREATED,
    CLICKING,
    RETURNING,
    DONE
} clickEventState;

typedef struct{
    Key key;
    clickEventState state;
    unsigned long clickingTime;

} ClickEvent;

ClickEvent clickEvent_create(uint8_t key, uint8_t *returnCode);
ClickEvent clickEvent_createEmpty();
void clickEvent_update(ClickEvent *event, ClickEvent *prevEvent);


#endif