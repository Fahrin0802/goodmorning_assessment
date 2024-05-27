#include "MyRequest.hpp"
#include <iostream>
#include <map>
#include <vector>
#include <numeric> // for std::accumulate
#include <cmath> //for transform
#include <algorithm>

#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;


void MyRequest::start(const std::string& uri){
    std::cout << "Starting request for URI: " << uri << std::endl;
    startTime = std::chrono::high_resolution_clock::now();
    temp_uri = uri;

}

void MyRequest::finish(){
    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = endTime - startTime;
    double elapsedTime = elapsed.count() * 1000; // Convert to milliseconds

    // Add the elapsed time to the map
    if (timingsMap.find(temp_uri) == timingsMap.end())
    {
        timingsMap[temp_uri] = std::vector<double>();
    }
    timingsMap[temp_uri].push_back(elapsedTime);

    std::cout << "Finished request. Time taken: " << elapsedTime << " ms" << std::endl;
}

double MyRequest::mean(const std::string& uri){
    if (timingsMap.find(uri) == timingsMap.end())
        return -1.0; 

    double sum = std::accumulate(timingsMap[uri].begin(), timingsMap[uri].end(), 0.0);
    return sum / timingsMap[uri].size();
}

double MyRequest::standardDeviation(const std::string& uri){
    if (timingsMap.find(uri) == timingsMap.end())
        return -1.0;

    const std::vector<double>& times = timingsMap.at(uri);
    double meanValue = mean(uri);
    std::vector<double> diff(times.size());
    
    std::transform(times.begin(), times.end(), diff.begin(),
        [meanValue](double x) { return x - meanValue; });

    double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
    double stdev = std::sqrt(sq_sum / times.size());
    return stdev;
}