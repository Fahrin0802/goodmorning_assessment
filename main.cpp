#include "MyRequest.hpp"

int main()
{
    MyRequest request(50); // Maximum 10 bins
    std::string response = request.process("uri1");
    std::cout << response << std::endl;

    // Simulate more requests
    request.process("uri1");
    request.process("uri1");
    request.process("uri1");
    request.process("uri1");
    request.process("uri2");

    // Print out the statistics
    std::cout << "Mean time for uri1: " << request.mean("uri1") << " ms" << std::endl;
    std::cout << "Standard deviation for uri1: " << request.standardDeviation("uri1") << " ms" << std::endl;

    // Draw the histogram
    request.drawHistogram("uri1");

    return 0;
}
