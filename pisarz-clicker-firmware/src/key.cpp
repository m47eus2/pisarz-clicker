#include "key.h"
#include "lut.h"

Key key_create(uint16_t character, uint8_t *returnCode){
    Key key;
    *returnCode = 0;

    key.driver = getServoDriverFromLUT(character, returnCode);
    key.channel = getServoChannelFromLUT(character, returnCode);
    key.dir = getServoDirFromLUT(character, returnCode);

    return key;
}

Key key_createEmpty(){
    Key key;
    key.driver = 0;
    key.channel = 0;
    key.dir = LEFT;
    return key;
}