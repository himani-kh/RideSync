#Cab Booking System

This is a command-line cab booking system implemented in C++. The system uses Dijkstra's algorithm to calculate the shortest distance between locations and books the closest available cab for the user. It also handles dynamic cab availability and includes functionalities for customer booking and location management.

## Features

- *Shortest Path Calculation*: Uses Dijkstra's algorithm to determine the shortest path between locations.
- *Dynamic Cab Availability*: Tracks cab availability and resets all cabs to available after a set threshold of bookings.
- *Location Management*: Displays available locations and neighbors with distances.
- *Customer and Booking Management*: Tracks customers and their bookings, including pickup and drop-off locations.
- *Input Validation*: Ensures valid input for locations and prevents bookings with the same pickup and drop-off points.

## How It Works

1. *Locations*: Locations are represented as nodes (e.g., 'a', 'b') with human-readable names (e.g., 'Westminster', 'Camden Town').
2. *Cabs*: Cabs have unique IDs, driver names, car types, current locations, and availability status.
3. *Booking*: Users provide their current location and destination. The system assigns the closest available cab.
4. *Threshold Handling*: When the number of bookings reaches a threshold, all cabs are reset to available status.

## Getting Started

### Prerequisites

- A C++ compiler (e.g., g++).
- Basic understanding of how to run C++ programs.

### Running the Program

1. *Clone the Repository*:

    bash
    git clone https://github.com/<your-username>/cab-booking-system.git
    cd cab-booking-system
    

2. *Compile the Code*:

    bash
    g++ -o cab_booking cab_booking.cpp
    

3. *Run the Program*:

    bash
    ./cab_booking
    

4. *Interact with the Program*:

    The program will prompt you to choose options for booking cabs or exiting the system.

## Usage

1. On running the program, choose an option:
    - 1: Book a cab.
    - 2: Exit.

2. If you select *Book a cab*:
    - View available locations and their neighbors.
    - Enter your *name* and select your current location and destination by typing the corresponding letter.
    - If a cab is available, the system books it and displays the booking details.

3. If no cabs are available, the system informs the user.

4. After the set booking threshold (default: 6 bookings), all cabs are reset to available.