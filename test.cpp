#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "MyRequest.hpp"  // Include the header file of the class we want to test

TEST_CASE("Mean Calculation") {
    MyRequest myRequest(10);
    
    std::map<std::string, std::vector<double>> timingsMap;
    timingsMap["example_uri"] = {1.0, 2.0, 3.0, 4.0, 5.0};
    
    // // Use the protected setter method
    myRequest.setTimingsMap(timingsMap);
    
    // Calculate the mean
    double mean = myRequest.mean("example_uri");
    CHECK(mean == doctest::Approx(3.0));
}
    
   
TEST_CASE("Standard Deviation Calculation") {
    MyRequest myRequest(10);
    
    std::map<std::string, std::vector<double>> timingsMap;
    timingsMap["example_uri"] = {1.0, 2.0, 3.0, 4.0, 5.0};
    myRequest.setTimingsMap(timingsMap);

    // Calculate the standard deviation
    double sd = myRequest.standardDeviation("example_uri");
    CHECK(sd == doctest::Approx(1.414213));
}

