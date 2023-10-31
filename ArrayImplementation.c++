#include <iostream>
#include <vector>
#include <algorithm>

struct SensorReading {
    int timestamp;
    double value;
};

class SensorDataArray {
private:
    std::vector<SensorReading> data;

public:
    void insertReading(int timestamp, double value) {
        data.push_back({timestamp, value});
    }

    std::vector<SensorReading> retrieveDataInTimeWindow(int startTime, int endTime) {
        std::vector<SensorReading> dataInWindow;
        for (const SensorReading& reading : data) {
            if (reading.timestamp >= startTime && reading.timestamp <= endTime) {
                dataInWindow.push_back(reading);
            }
        }
        return dataInWindow;
    }

    void removeOutdatedData(int cutoffTime) {
        data.erase(std::remove_if(data.begin(), data.end(), [cutoffTime](const SensorReading& reading) {
            return reading.timestamp < cutoffTime;
        }), data.end());
    }
};

int main() {
    SensorDataArray sensorDataArray;
    sensorDataArray.insertReading(1, 25.0);
    sensorDataArray.insertReading(2, 30.0);
    sensorDataArray.insertReading(3, 22.0);

    std::vector<SensorReading> dataInWindow = sensorDataArray.retrieveDataInTimeWindow(1, 2);
    for (const SensorReading& reading : dataInWindow) {
        std::cout << "Timestamp: " << reading.timestamp << ", Value: " << reading.value << std::endl;
    }

    sensorDataArray.removeOutdatedData(2);
    dataInWindow = sensorDataArray.retrieveDataInTimeWindow(1, 3);
    for (const SensorReading& reading : dataInWindow) {
        std::cout << "Timestamp: " << reading.timestamp << ", Value: " << reading.value << std::endl;
    }

    return 0;
}
