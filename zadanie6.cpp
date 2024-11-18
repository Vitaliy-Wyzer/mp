#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>

struct Node {
    int id;
    float x, y;
};

struct Polygon {
    int* nodeIds;
    int size;
};

float distance(float x1, float y1, float x2, float y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

float Area(const Node* nodes, const Polygon& polygon) {
    float ar = 0.0f;
    for (int i = 0; i < polygon.size; ++i) { 
        const Node& current = nodes[polygon.nodeIds[i] - 1];
        const Node& next = nodes[polygon.nodeIds[(i + 1) % polygon.size] - 1];
        ar += current.x * next.y - next.x * current.y;
    }
    return std::abs(ar) / 2.0f;
}

float Perimeter(const Node* nodes, const Polygon& polygon) {
    float p = 0.0f;
    for (int i = 0; i < polygon.size; ++i) { 
        const Node& current = nodes[polygon.nodeIds[i] - 1];
        const Node& next = nodes[polygon.nodeIds[(i + 1) % polygon.size] - 1];
        p += distance(current.x, current.y, next.x, next.y); 
    }
    return p;
}

int main() {
    std::ifstream inputFile("ok.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open file!" << std::endl;
        return 1;
    }

    std::string line;
    int numberOfNodes = 0;
    Node* nodes = nullptr;
    Polygon polygon;

    polygon.nodeIds = nullptr;
    polygon.size = 0;

    while (std::getline(inputFile, line)) {
        if (line.find("[NUMBER OF NODES]") != std::string::npos) {
            inputFile >> numberOfNodes;
            nodes = new Node[numberOfNodes];
            std::getline(inputFile, line);
        } else if (line.find("[NODES]") != std::string::npos) {
            for (int i = 0; i < numberOfNodes; ++i) {
                inputFile >> nodes[i].id >> nodes[i].x >> nodes[i].y;
            }
        } else if (line.find("[POLYGON]") != std::string::npos) {
            std::getline(inputFile, line);
            std::istringstream polygonStream(line);
            int tempNodeCount = 0;

            while (polygonStream >> tempNodeCount) {
                ++polygon.size;
            }

            polygon.nodeIds = new int[polygon.size];

            polygonStream.clear();
            polygonStream.seekg(0, std::ios::beg);
            for (int i = 0; i < polygon.size; ++i) {
                polygonStream >> polygon.nodeIds[i];
            }
        }
    }

    inputFile.close();

    float perimeter = Perimeter(nodes, polygon);
    float area = Area(nodes, polygon);

    std::cout << "Perimeter: " << perimeter << std::endl;
    std::cout << "Area: " << area << std::endl;

    delete[] nodes;
    delete[] polygon.nodeIds;

    return 0;
}
