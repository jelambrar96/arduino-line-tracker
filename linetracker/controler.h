#ifndef CONTROLER_H
#define CONTROLER_H


class Controler {
public:
    virtual unsigned char control(unsigned int v0, unsigned int v1, unsigned int v2) = 0;
};

class PServoControler: Controler {
public:
    virtual unsigned char control(unsigned int v0, unsigned int v1, unsigned int v2);
private:
    const int k0 = 0.1;
};


#endif