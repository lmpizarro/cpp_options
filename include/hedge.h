#ifndef HEDGE_H
#define HEDGE_H

class Hedge
{
public:
    float sigma;
    float deltaT;
    float rFr;
    float mu;

    Hedge(float s, float d, float r, float mu);

    float u();
    float d();
    float p();
    float pp();
};
#endif
