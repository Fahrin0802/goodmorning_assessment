#ifndef MYREQUEST_HPP
#define MYREQUEST_HPP

#include "Request.hpp"
#include <iostream>
#include <map>
#include <vector>


/**
 * Derived class from Request 
 * 
 * This class enables processing of requests ar various URIs
 * and allows tracking of processing times
 */
class MyRequest : public Request
{
private:
    /**
     * Time point representing the start time of request processing.
     */
    std::chrono::high_resolution_clock::time_point startTime;

    /**
     * A map storing URIs as keys and vectors of processing times as values.
     */
    std::map<std::string, std::vector<double>> timingsMap;

    /**
     * Temporary storage for the URI of the request.
     */
    std::string temp_uri;

    /**
     * Maximum number of bins for histogram generation.
     */
    int maxBins;

protected:

    /**
     * Start processing the request in the child class
     * This starts the timer to track processing time
     *
     * @param [in] uri The URI of the request endpoint
     */
    void start(const std::string& uri) override;

    
    /** 
     * Finish processing the request in the child class 
     * This stops the timer and adds processing time to timingsMap
     */
    void finish() override;

    /**
     * Calculate the normalized histogram for a given URI.
     *
     * @param [in] uri The URI of the request endpoint.
     * @return A vector of pairs representing histogram bins and their normalized frequencies.
     */
    std::vector<std::pair<double, double>> getNormalizedHistogram(const std::string& uri);

public:
    /**
     * Constructor for MyRequest class.
     *
     * @param [in] maxBins Maximum number of bins for histogram generation.
     */
    MyRequest(int maxBins);

    /**
     * Set the timings map with a new map of timings.
     *
     * @param [in] newTimingsMap The new timings map to set.
     */
    void setTimingsMap(const std::map<std::string, std::vector<double>>& newTimingsMap);

    /**
     * Calculate the mean processing time for a given URI.
     *
     * @param [in] uri The URI of the request endpoint.
     * @return The mean processing time for the specified URI.
     */
    double mean(const std::string& uri);

    /**
     * Calculate the standard deviation of processing times for a given URI.
     *
     * @param [in] uri The URI of the request endpoint.
     * @return The standard deviation of processing times for the specified URI.
     */
    double standardDeviation(const std::string& uri);

    /**
     * Draw a histogram of processing times for a given URI.
     *
     * @param [in] uri The URI of the request endpoint.
     */
    void drawHistogram(const std::string& uri);

};

#endif // MYREQUEST_HPP