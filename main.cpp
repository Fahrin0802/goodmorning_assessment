#include "MyRequest.hpp"

int main()
{
    MyRequest request;
    std::string response = request.process("uri1");
    std::cout << response << std::endl;

    // Add more processing if needed
    request.process("uri1");
    request.process("uri2");
    
    // Print out the statistics
    std::cout << "Mean time for uri1: " << request.mean("uri1") << " ms" << std::endl;
    std::cout << "Standard deviation for uri1: " << request.standardDeviation("uri1") << " ms" << std::endl;

    return 0;
}
