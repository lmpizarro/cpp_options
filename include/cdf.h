#ifndef CDF_HH
#define CDF_HH

template <typename Type> class NormalCDF
{
public:
    Type loc;
    Type scale;
    NormalCDF(Type, Type);
    Type cdf(Type x);
};

template <typename Type> class StandardNormalCDF: public NormalCDF<Type>
{
public:
    StandardNormalCDF(void);
    Type cdf(Type x);
};
#endif
