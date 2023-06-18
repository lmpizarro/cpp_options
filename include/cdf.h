#ifndef __CDF_H
#define __CDF_H

class NormalCDF
{
public:
    float loc;
    float scale;
    NormalCDF(const float, const float);
    float cdf(const float x) const;
};

class StandardNormalCDF : public NormalCDF
{
public:
    explicit StandardNormalCDF(void);
    float cdf(const float x) const;
};
#endif
