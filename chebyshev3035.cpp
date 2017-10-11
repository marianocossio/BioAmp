#include "chebyshev3035.h"

Chebyshev3035::Chebyshev3035(QObject *parent) : Filter(parent)
{
    filterConstants.push_back({1, -13.1330890463812, 86.7784872836581, -380.154499706078, 1231.76150961663, -3126.66462411918, 6435.20098201258, -10977.1500958741, 15741.6236667157, -19148.7033440180, 19857.2374540384, -17582.4815948128, 13271.8204992033, -8497.85959163263, 4574.24465519683, -2040.67574249725, 738.164127997152, -209.179349710925, 43.8433089871770, -6.09247706997514, 0.425964099270843});
    filterConstants.push_back({0.00785946987492684, -0.104044286384076, 0.694992078450746, -3.08758847339235, 10.1799255063858, -26.3878972459921, 55.6681125194456, -97.7075026504831, 144.744094480407, -182.623439386185, 197.231038442379, -182.623439386184, 144.744094480406, -97.7075026504830, 55.6681125194456, -26.3878972459920, 10.1799255063857, -3.08758847339234, 0.694992078450744, -0.104044286384076, 0.00785946987492682});
}

Chebyshev3035::~Chebyshev3035()
{

}

vector < double > Chebyshev3035::filter(deque < DataSet > &signal, int channel)
{
    vector < double > filteredSignal, input;

    for (unsigned index = 0; index < filterConstants[0].size(); index++)
    {
        filteredSignal.push_back(0);
        input.push_back(0);
    }

    for (unsigned index = 0; index < signal.size(); index++)
    {
        input.push_back(signal[index].channelData(channel));
    }

    for (unsigned n = filterConstants[1].size(); n < input.size(); n++)
    {
        double Yn = filterConstants[1][0] * input[n];

        for (unsigned k = 1; k < filterConstants[0].size(); k++)
            Yn = Yn + (filterConstants[1][k] * input[n - k]) - (filterConstants[0][k] * filteredSignal[n - k]);

        Yn = Yn / filterConstants[0][0];

        filteredSignal.push_back(Yn);
    }

    return filteredSignal;
}
