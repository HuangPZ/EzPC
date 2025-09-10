#include <nvml.h>
#include <cstdio>
#include <chrono>
#include <thread>
#include <atomic>
#include <iostream>

// Global atomic variable to signal the monitoring thread to stop
std::atomic<bool> stopMonitoring{false};

void monitorGpuPowerUsage(unsigned int deviceIndex, int intervalMs) {
    nvmlReturn_t result;
    nvmlDevice_t device;

    // Initialize NVML
    result = nvmlInit();
    if (result != NVML_SUCCESS) {
        fprintf(stderr, "Failed to initialize NVML: %s\n", nvmlErrorString(result));
        return;
    }

    // Get GPU handle
    result = nvmlDeviceGetHandleByIndex(deviceIndex, &device);
    if (result != NVML_SUCCESS) {
        fprintf(stderr, "Failed to get device handle for GPU %u: %s\n", deviceIndex, nvmlErrorString(result));
        nvmlShutdown();
        return;
    }

    // Monitoring loop
    while (!stopMonitoring.load()) {
        unsigned int power_mW = 0;
        result = nvmlDeviceGetPowerUsage(device, &power_mW);
        if (result == NVML_SUCCESS) {
            double power_W = power_mW / 1000.0;
            printf("GPU %u Power Usage: %.2f W\n", deviceIndex, power_W);
        } else {
            fprintf(stderr, "Failed to get power usage: %s\n", nvmlErrorString(result));
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(intervalMs));
    }

    // Cleanup NVML
    result = nvmlShutdown();
    if (result != NVML_SUCCESS) {
        fprintf(stderr, "Failed to shut down NVML: %s\n", nvmlErrorString(result));
    }
}

int main(int argc, char *argv[]) {
    // Parse optional arguments: device index and interval
    unsigned int deviceIndex = 0;
    int intervalMs = 100;

    if (argc > 1) {
        deviceIndex = static_cast<unsigned int>(atoi(argv[1]));
    }
    if (argc > 2) {
        intervalMs = atoi(argv[2]);
    }

    printf("Starting GPU power monitoring for GPU %u at %d ms intervals.\n", deviceIndex, intervalMs);
    printf("Press ENTER to stop monitoring.\n");

    // Start the monitoring in a separate thread
    std::thread monitoringThread(monitorGpuPowerUsage, deviceIndex, intervalMs);

    // Wait for the user to press ENTER (or another key) to stop monitoring
    // This simulates the "certain command" to stop
    std::cin.get();

    // Signal the monitoring thread to stop
    stopMonitoring.store(true);

    // Wait for the monitoring thread to finish
    monitoringThread.join();

    printf("Monitoring stopped.\n");
    return 0;
}
