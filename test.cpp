#include <iostream>
#include <tuple>
#include <cmath>
#include "Manager.hpp"

using CmdList = std::vector<std::string>;

CmdList&& readCmd(int argc, char** argv, CmdList&& out = CmdList()) {
    out.reserve(argc);
    for (int i=0; i<argc; ++i)
        out.emplace_back(argv[i]);

    return std::move(out);
}


Type::PathSpec pathSpecOrigin() {
    return {
        {1.0, 90.0},
        {std::sqrt(2.0), 45.0},
        {std::sqrt(5.0), 63.435},
        {std::sqrt(5.0), 26.565},
        {2.0 * std::sqrt(2.0), 45.0},
        {std::sqrt(12.5), 8.13},
        {std::sqrt(5.0), -26.565},
        {2.0, 0.0},
        {std::sqrt(2.0), -45.0},
        {1.0, 0.0},
        {0.0, 0.0}
    };
}

Type::PathSpec pathSpecP2P() {
    return {
        {1.0, 90.0},
        {1.0, 0.0},
        {1.0, 90.0},
        {std::sqrt(2.0), -45.0},
        {1.0, 90.0},
        {3.0/std::sqrt(2.0), -45.0},
        {3.0/std::sqrt(2.0), -135.0},
        {1.0, 90.0},
        {std::sqrt(2), -135.0},
        {1.0, 90.0},
        {1.0, 180.0}
    };
}

void printHelp() {
    std::cout << "usage: test <latitude> <longitude> <length unit> <heading> <altitude> <model> <name>" << std::endl;
}

int main(int argc, char** argv) {
    if (argc!=8) {
        printHelp();
        return 1;
    }
    const auto cmdList = readCmd(argc,argv);
    const PathCalculatorManager mP2P(pathSpecP2P(), cmdList.back()+"_p2p", false);
    const PathCalculatorManager mFO(pathSpecOrigin(), cmdList.back()+"_fo", true);

    bool success = mP2P.genPath(
        std::stof(cmdList[1]),
        std::stof(cmdList[2]),
        std::stof(cmdList[3]),
        std::stof(cmdList[4]),
        std::stof(cmdList[5]),
        std::stoi(cmdList[6])
    );
    if (!success)
        std::cerr << "Error: problems opening P2P output file." << std::endl;

    success = mFO.genPath(
        std::stof(cmdList[1]),
        std::stof(cmdList[2]),
        std::stof(cmdList[3]),
        std::stof(cmdList[4]),
        std::stof(cmdList[5]),
        std::stoi(cmdList[6])
    );
    if (!success)
        std::cerr << "Error: problems opening FO output file." << std::endl;
    

    return 0;
}