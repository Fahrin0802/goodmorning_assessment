#ifndef MYREQUEST_HPP
#define MYREQUEST_HPP

#include "Request.hpp"
#include <iostream>
#include <map>
#include <vector>

// Derived class from Request
class MyRequest : public Request
{
private:
    std::chrono::high_resolution_clock::time_point startTime;
    std::map<std::string, std::vector<double>> timingsMap;
    std::string temp_uri;
    int maxBins;

protected:
    void start(const std::string& uri) override;

    void finish() override;

public:
    MyRequest(int maxBins);
    
    double mean(const std::string& uri);

    double standardDeviation(const std::string& uri);

    void drawHistogram(const std::string& uri);
};

#endif // MYREQUEST_HPP