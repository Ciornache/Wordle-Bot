#include <chrono>
#include <fstream>

class Timer
{

public:
    Timer(std::ofstream &fout, std::string name = "Time") : fout(fout), name(name) { startTime = std::chrono::high_resolution_clock::now(); }

    ~Timer() { Stop(); }

    void Stop()
    {
        auto endTime = std::chrono::high_resolution_clock::now();

        auto start = std::chrono::time_point_cast<std::chrono::seconds>(startTime).time_since_epoch().count();
        auto end = std::chrono::time_point_cast<std::chrono::seconds>(endTime).time_since_epoch().count();

        auto duration = end - start;

        double m=duration/60;

        fout << name << ": " << duration << "s (" << m << "m)" << std::endl;
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;

    std::string name = "Time";

    std::ofstream &fout;
};
