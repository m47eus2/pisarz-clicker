#ifndef CLICKEVENTTAB_H
#define CLICKEVENTTAB_H

#include "clickEvent.h"

#define CLICKEVENT_TAB_MAX_LEN 50

void clickEventTab_addEvent(uint8_t incommingByte);
void clickEventTab_removeDoneEvents();
void clickEventTab_updateEvents();
void clickEventTab_showEventTab();

#endif