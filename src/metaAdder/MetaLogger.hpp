#pragma once
#include <chrono>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <mutex>

class MetaLogger {
public:
    MetaLogger(std::ostream& stream) : out(stream) {}

    void log(const std::string& message) {
        std::lock_guard<std::mutex> lock(mtx);
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        std::tm tm = *std::localtime(&now_c);

        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << " - " << message;
        out << oss.str() << std::endl;
    }

private:
    std::ostream& out;
    std::mutex mtx;
};