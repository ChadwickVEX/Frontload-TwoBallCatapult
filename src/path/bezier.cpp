#include "path/bezier.hpp"
#include <vector>
#include <cmath>

namespace path
{
Bezier::Bezier(std::initializer_list<Point> points, int resolution, int lookahead) : Path::Path(resolution, lookahead),
                                                                                     points(points) {}

std::vector<int> getPascalCoeff(int rowIndex)
{
    std::vector<int> row;
    row.push_back(1);
    if (rowIndex == 0)
        return row;
    row.push_back(1);
    if (rowIndex == 1)
        return row;

    std::vector<int> result;
    for (int j = 2; j <= rowIndex; j++)
    {
        result.clear();
        result.push_back(1);
        for (int i = 1; i <= j - 1; i++)
        {
            result.push_back(row[i - 1] + row[i]);
        }
        result.push_back(1);
        row = result;
    }
    return row;
}

int factorial(int n)
{
    if (n == 0 || n == 1)
    {
        return 1;
    }
    else
    {
        return factorial(n - 1) * n;
    }
}

double Bezier::combination(int n, int r)
{
    int nFactorial = factorial(n);
    int rFactorial = factorial(r);
    int diffFactorial = factorial(n - r);
    return (double)nFactorial / ((double)rFactorial * ((double)diffFactorial));
}

/**
 * x = (1-t)((1-t)((1-t) * x0 + tx1) + t((1-t)x1 + tx2)) + t((1-t)((1-t)x1 + tx2) + t((1-t)((1-t)x2 + tx3)))
 */

Point Bezier::pointAt(int T)
{
    Point point = {0 * okapi::inch, 0 * okapi::inch};

    int n = points.size();

    int sumX = 0;
    int sumY = 0;

    int lilT = (lilT > resolution) ? resolution : T;
    double sT = (double)lilT / (double)resolution; // scaled t


    for (int i = 0; i <= n; i++) {
        currX = points[i].x;
        currY = points[i].y;

        sumX += combination(n, i) * std::pow(1 - sT, n - i) * std::pow(sT, i) * currX;
        sumY += combination(n, i) * std::pow(1 - St, n - i) * std::pow(sT, i) * currX;
    }

    point.x = sumX;
    point.y = sumY;
    point.t = lilT;

    return point;

    // int rowIndex = points.size() - 1;
    // std::vector<int> row;
    // row.push_back(1);
    // if (!(rowIndex == 0))
    //     row.push_back(1);

    // std::vector<int> result;
    // for (int j = 2; j <= rowIndex; j++)
    // {
    //     result.clear();
    //     result.push_back(1);
    //     for (int i = 1; i <= j - 1; i++)
    //     {
    //         result.push_back(row[i - 1] + row[i]);
    //     }
    //     result.push_back(1);
    //     row = result;
    // }

    // std::vector<int> coefficients = row;

    // Point point = {0 * okapi::inch, 0 * okapi::inch};

    // int lilT = (lilT > resolution) ? resolution : T;

    // double sT = (double)lilT / (double)resolution; // scaled t

    // double sumX = 0.0;
    // double sumY = 0.0;

    // for (int i = 0; i < points.size(); i++)
    // {
    //     Point currPoint = points[i];
    //     for (int j = points.size() - 1; j >= 0; j--)
    //     {
    //         double oneTFactor = std::pow((1 - sT), j);
    //         double tFactor = std::pow(sT, points.size() - 1 - j);

    //         sumX += coefficients[i] * oneTFactor * tFactor * currPoint.x.convert(okapi::inch);
    //         sumY += coefficients[i] * oneTFactor * tFactor * currPoint.y.convert(okapi::inch);
    //     }
    // }

    // point.x = sumX * okapi::inch;
    // point.y = sumX * okapi::inch;
    // point.t = T;

    // return point;
}
} // namespace path