#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> maximizeContainerWeight(int k, const std::vector<int>& containers) {
    std::vector<int> sortedContainers(containers);
    std::sort(sortedContainers.rbegin(), sortedContainers.rend()); // Sort in non-increasing order
    
    std::vector<int> selectedContainers;
    int remainingCapacity = k;

    for (int container : sortedContainers) {
        if (container <= remainingCapacity) {
            selectedContainers.push_back(container);
            remainingCapacity -= container;
        }
    }

    return selectedContainers;
}

int main() {
    int k = 25;
    std::vector<int> containers = {6, 5, 3, 15, 20};

    std::vector<int> selectedContainers = maximizeContainerWeight(k, containers);

    std::cout << "Selected containers: ";
    for (int container : selectedContainers) {
        std::cout << container << " ";
    }
    std::cout << std::endl;

    return 0;
}
