#include <stdlib.h> // srand, rand
#include <iostream>
#include <vector>

#include "DistUtils.h"

int main()
{
    std::vector<std::vector<double> > data;
    int n_row = 1000;
    int n_col = 6;

    // create random data for testing
    srand(0);
    data.resize(n_row);
    for (size_t r=0; r<n_row; r++) {
        data[r].resize(n_col);
        for (size_t c=0; c<n_col; c++) {
            data[r][c] = rand() % 100;
        }
    }

    int dist_metric = 2; // euclidean metric
    GeoDa::DistUtils du(data, dist_metric);

    std::cout << "Max threshold:" << du.GetMaxThreshold() << std::endl;
    std::cout << "Min threshold:" << du.GetMinThreshold() << std::endl;
    return 0;
}
