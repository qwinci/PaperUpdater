#include <iostream>
#include "cstdlib"
#include "fstream"
#include "sstream"
#include "vector"
#include "json.hpp"

using json = nlohmann::json;

int main(int argc, char *argv[]) {
    std::string minecraftversion;
    std::cout << "Input Minecraft version:";
    std::cin >> minecraftversion;

    std::ostringstream command;
    command << "curl https://papermc.io/api/v2/projects/paper/versions/" << minecraftversion << "/" << " -o temp.txt";
    system(command.str().c_str());
    std::fstream File("temp.txt");
    json version;
    File >> version;
    std::string temp;
    std::string tempFull;
    while (std::getline(File, temp)) {
        tempFull += temp;
    }
    if (tempFull.empty()) {
        std::cout << "Invalid minecraft version.";
        return 1;
    }
    File.close();

    std::vector<int> builds;
    version["builds"].get_to(builds);
    int latestversion = *std::max_element(std::begin(builds), std::end(builds));
    std::ostringstream paperfilecommand;
    paperfilecommand << "curl https://papermc.io/api/v2/projects/paper/versions/" << minecraftversion << "/builds/" << latestversion << "/downloads/" << "paper-" << minecraftversion << "-" << latestversion << ".jar" << " > paper.jar";
    system(paperfilecommand.str().c_str());
    return 0;
}
