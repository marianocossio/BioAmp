#ifndef CHEBYSHEV3035_H
#define CHEBYSHEV3035_H

#include <vector>

#include "filter.h"

using namespace std;

class Chebyshev3035 : public Filter
{
public:
    Chebyshev3035(QObject *parent = 0);

    virtual ~Chebyshev3035();

    virtual vector < double > filter(deque < DataSet > &signal, int channel);

private:
    vector < vector <double> > filterConstants;
};

#endif // CHEBYSHEV3035_H
