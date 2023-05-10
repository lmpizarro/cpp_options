#ifndef CDF_HH
#define CDF_HH


class NormalCDF{
    public:
        float loc;
        float scale;
    NormalCDF(float , float );
    float cdf(float x);
};

class StandardNormalCDF:public NormalCDF{
    public:
    explicit StandardNormalCDF(void);
    float cdf(float x);
};
#endif

