#include <iostream>
#include <vector>

struct SensorReading {
    int timestamp;
    double value;
    SensorReading* next;
};

class SensorDataLinkedList {
private:
    SensorReading* head;

public:
    SensorDataLinkedList() : head(nullptr) {}

    void insertReading(int timestamp, double value) {
        SensorReading* newReading = new SensorReading{timestamp, value, head};
        head = newReading;
    }

    std::vector<SensorReading> retrieveDataInTimeWindow(int startTime, int endTime) {
        std::vector<SensorReading> dataInWindow;
        SensorReading* current = head;
        while (current) {
            if (current->timestamp >= startTime && current->timestamp <= endTime) {
                dataInWindow.push_back(*current);
            }
            current = current->next;
        }
        return dataInWindow;
    }

    void removeOutdatedData(int cutoffTime) {
        SensorReading* current = head;
        SensorReading* prev = nullptr;
        while (current) {
            if (current->timestamp < cutoffTime) {
                if (prev) {
                    prev->next = current->next;
                } else {
                    head = current->next;
                }
                SensorReading* temp = current;
                current = current->next;
                delete temp;
            } else {
                prev = current;
                current = current->next;
            }
        }
    }
};

int main() {
    SensorDataLinkedList sensorDataLinkedList;
    sensorDataLinkedList.insertReading(1, 25.0);
    sensorDataLinkedList.insertReading(2, 30.0);
    sensorDataLinkedList.insertReading(3, 22.0);

    std::vector<SensorReading> dataInWindow = sensorDataLinkedList.retrieveDataInTimeWindow(1, 2);
    for (const SensorReading& reading : dataInWindow) {
        std::cout << "Timestamp: " << reading.timestamp << ", Value: " << reading.value << std::endl;
    }

    sensorDataLinkedList.removeOutdatedData(2);
    dataInWindow = sensorDataLinkedList.retrieveDataInTimeWindow(1, 3);
    for (const SensorReading& reading : dataInWindow) {
        std::cout << "Timestamp: " << reading.timestamp << ", Value: " << reading.value << std::endl;
    }

    return 0;
}
