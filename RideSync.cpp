#include <iostream>
#include <vector>
#include <map>
#include <climits>
#include <ctime>
#include <cstdlib>
#include <set>
#include <stdexcept>  // For exception handling

using namespace std;

// Function to add an edge with weight to the adjacency list
void addEdge(map<char, vector<pair<char, int>>>& adj, char u, char v, int w) {
    adj[u].push_back({v, w});
    adj[v].push_back({u, w}); // For undirected graph
}

// Function to print the neighbors and weights of a vertex
void printNeighborsAndWeights(map<char, vector<pair<char, int>>>& adj, char v, const map<char, string>& locationMap) {
    cout << "Neighbors of " << locationMap.at(v) << ": ";
    for (const auto& neighbor : adj[v]) {
        cout << locationMap.at(neighbor.first) << "(" << neighbor.second << " km) ";
    }
    cout << endl;
}

// Class for managing cabs
class Cab {
public:
    string cab_id;
    string driver_name;
    string car_type;
    char current_location;
    bool is_available;

    Cab(string id, string name, string type, char location, bool available)
        : cab_id(id), driver_name(name), car_type(type), current_location(location), is_available(available) {}
};

// Class for managing customers
class Customer {
public:
    string customer_id;
    string name;
    char current_location;
    char destination_location;

    Customer(string id, string name, char current, char destination)
        : customer_id(id), name(name), current_location(current), destination_location(destination) {}
};

// Class for managing bookings
class Booking {
public:
    string booking_id;
    string customer_id;
    string cab_id;
    char pickup_location;
    char drop_location;

    Booking(string id, string cust_id, string cab_id, char pickup, char drop)
        : booking_id(id), customer_id(cust_id), cab_id(cab_id), pickup_location(pickup), drop_location(drop) {}
};

// Dijkstra's algorithm to find the shortest path between two nodes
int findShortestDistance(char start, char end, map<char, vector<pair<char, int>>>& adj) {
    map<char, int> dist;
    for (auto& [node, _] : adj)
        dist[node] = INT_MAX;

    dist[start] = 0;
    set<pair<int, char>> pq;
    pq.insert({0, start});

    while (!pq.empty()) {
        char node = pq.begin()->second;
        pq.erase(pq.begin());

        for (const auto& neighbor : adj[node]) {
            char next = neighbor.first;
            int weight = neighbor.second;

            if (dist[node] + weight < dist[next]) {
                pq.erase({dist[next], next});
                dist[next] = dist[node] + weight;
                pq.insert({dist[next], next});
            }
        }
    }

    return dist[end];
}

// Function to reset all cabs to available
void resetCabs(vector<Cab>& cabs) {
    for (auto& cab : cabs) {
        cab.is_available = true;
    }
}

// Function to book a cab for a customer
void bookCab(Customer& customer, vector<Cab>& cabs, vector<Booking>& bookings, map<char, vector<pair<char, int>>>& adj, const map<char, string>& locationMap) {
    int closestCabIndex = -1;
    int minDistance = INT_MAX;

    // Find the closest available cab to the customer's current location
    for (int i = 0; i < cabs.size(); i++) {
        if (cabs[i].is_available) {
            int distance = findShortestDistance(customer.current_location, cabs[i].current_location, adj);
            if (distance < minDistance) {
                closestCabIndex = i;
                minDistance = distance;
            }
        }
    }

    // If no available cabs were found, inform the customer and return
    if (closestCabIndex == -1) {
        cout << "Sorry, no available cabs were found.\n";
        return;
    }

    // Cab found, create a booking and update availability
    Cab& selectedCab = cabs[closestCabIndex]; // Reference to the selected cab
    selectedCab.is_available = false;         // Mark cab as unavailable

    // Create a new booking
    string booking_id = "B" + to_string(bookings.size() + 1); // Unique booking ID
    bookings.emplace_back(booking_id, customer.customer_id, selectedCab.cab_id,
                          customer.current_location, customer.destination_location);

    // Inform the customer
    cout << "Cab booked successfully! \nCab ID: " << selectedCab.cab_id << " \nDriver: " << selectedCab.driver_name
         << " \nPick Up: " << locationMap.at(customer.current_location) << " \nDrop: " << locationMap.at(customer.destination_location) << "\n";

    // Update cab's current location to the destination
    selectedCab.current_location = customer.destination_location;
}

// Function to validate customer input locations
void validateLocation(char location, const map<char, string>& locationMap) {
    if (locationMap.find(location) == locationMap.end()) {
        throw invalid_argument("Invalid location entered.");
    }
}

// Function to print all available locations with their corresponding letter (a), (b), etc.
void printAvailableLocations(map<char, string>& locationMap) {
    cout << "\nAvailable locations:\n";
    char letter = 'a'; // Start with 'a'
    for (const auto& location : locationMap) {
        cout << letter << ") " << location.second << endl; // Print letter and location name
        letter++; // Move to the next letter
    }
}



int main() {
    map<char, vector<pair<char, int>>> adj; // Create an adjacency list to represent the graph

    // Location names mapped to characters
    map<char, string> locationMap = {
        {'a', "Westminster"},
        {'b', "Camden Town"},
        {'c', "Kensington"},
        {'d', "Greenwich"},
        {'e', "Notting Hill"},
        {'f', "Chelsea"},
        {'g', "Hammersmith"},
        {'h', "Soho"},
        {'i', "Shoreditch"},
        {'j', "Covent Garden"},
        {'k', "Paddington"}
    };

    // Add edges with weights to the graph (representing roads and distances between locations)
    addEdge(adj, 'a', 'b', 3);
    addEdge(adj, 'a', 'd', 5);
    addEdge(adj, 'a', 'c', 4);
    addEdge(adj, 'b', 'e', 6);
    addEdge(adj, 'c', 'f', 3);
    addEdge(adj, 'c', 'g', 6);
    addEdge(adj, 'd', 'h', 7);
    addEdge(adj, 'h', 'k', 6);
    addEdge(adj, 'g', 'k', 5);
    addEdge(adj, 'f', 'g', 4);
    addEdge(adj, 'e', 'i', 9);
    addEdge(adj, 'i', 'j', 6);
    addEdge(adj, 'j', 'k', 8);

    // Initialize cabs
    vector<Cab> cabs = {
        Cab("C001", "John Doe", "Sedan", 'k', true),
        Cab("C002", "Jane Smith", "SUV", 'e', true),
        Cab("C003", "Bob Johnson", "Hatchback", 'j', false), // Unavailable cab
        Cab("C004", "Alice Brown", "Sedan", 'd', true),
    };

    vector<Booking> bookings; // List to store all bookings
    int bookingCount = 0;    // Count of completed bookings
    int threshold = 6;       // Threshold for resetting all cabs to available

    // Initialize random number generator for customer ID generation
    srand(time(0));

    while (true) {
        int choice;
        cout << "\nEnter your choice:\n";
        cout << "1. Book a cab\n";
        cout << "2. Exit\n";
        cin >> choice;

        switch (choice) {
            case 1: {
                printAvailableLocations(locationMap); // Show available locations and neighbors

                string customer_id = "C" + to_string(rand() % 10000); // Generate random customer ID
                string name;
                char current_location, destination_location;

                cout << "Customer ID: " << customer_id << endl;
                cout << "Enter name: ";
                cin >> name;

                try {
                    cout << "Enter current location (choose letter from above): ";
                    cin >> current_location;
                    validateLocation(current_location, locationMap);

                    cout << "Enter destination location (choose letter from above): ";
                    cin >> destination_location;
                    validateLocation(destination_location, locationMap);

                    if (current_location == destination_location) {
                        cout << "Current location and destination are the same.\n";
                        break;
                    }

                    Customer customer(customer_id, name, current_location, destination_location);
                    bookingCount++;
                    if(bookingCount>=threshold){
                        resetCabs(cabs);
                        bookingCount=0;
                    }
                    bookCab(customer, cabs, bookings, adj, locationMap);

                } catch (const invalid_argument& e) {
                    cout << e.what() << endl;
                }
                break;
            }
            case 2:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice.\n";
                break;
        }
    }
}
