#include "controler.h"

unsigned char PServoControler::control(unsigned int v0, unsigned int v1, unsigned int v2) {
    return v0 / 400;
}
