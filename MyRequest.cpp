#include "MyRequest.hpp"
#include <iostream>
#include <map>
#include <vector>
#include <numeric> // for std::accumulate
#include <cmath> //for transform
#include <algorithm>
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

MyRequest::MyRequest(int maxBins) {
    this->maxBins = maxBins;
}

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

void MyRequest::setTimingsMap(const std::map<std::string, std::vector<double>>& newTimingsMap) {
    timingsMap = newTimingsMap;
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

std::vector<std::pair<double, double>> MyRequest::getNormalizedHistogram(const std::string& uri) {
    if (timingsMap.find(uri) == timingsMap.end()) {
        std::cerr << "No data for URI: " << uri << std::endl;
        return {};
    }

    const std::vector<double>& times = timingsMap.at(uri);
    if (times.empty())
        return {};

    // Determine the range of the data
    auto min_it = std::min_element(times.begin(), times.end());
    auto max_it = std::max_element(times.begin(), times.end());
    double minValue = *min_it;
    double maxValue = *max_it;

    // Compute bin width and count
    int binCount = std::min(maxBins, static_cast<int>(times.size()/2) + 1);
    double binWidth = (maxValue - minValue) / binCount;

    // Create bins
    std::vector<int> bins(binCount, 0);
    for (double time : times) {
        int binIndex = std::min(static_cast<int>((time - minValue) / binWidth), binCount - 1);
        bins[binIndex]++;
    }

    // Normalize the histogram
    double total = times.size();
    std::vector<std::pair<double, double>> histogram;
    for (int i = 0; i < binCount; ++i) {
        double binStart = minValue + i * binWidth;
        double frequency = bins[i] / total;
        histogram.emplace_back(binStart, frequency);
    }

    return histogram;
}

void MyRequest::drawHistogram(const std::string& uri) {
    auto histogram = getNormalizedHistogram(uri);
    if (histogram.empty()) {
        return;
    }

    std::cout << "-----------------------------------" << std::endl;
    std::cout << "Ploting Histogram: " << std::endl;
    
    std::vector<double> bins, frequencies;
    for (const auto& entry : histogram) {
        bins.push_back(entry.first);
        frequencies.push_back(entry.second);
        std::cout << "bin_start: " << entry.first << " || frequency: " << entry.second << std::endl;
    }

    // Using python's matplotlib library, plot the histogram
    plt::hist(frequencies, bins.size());
    plt::title("Normalized Histogram of processing times for URI: " + uri);
    plt::xlabel("Time (ms)");
    plt::ylabel("Normalized Frequency");
    plt::show();
}