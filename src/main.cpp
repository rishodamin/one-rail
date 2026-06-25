#include "booking_engine.hpp"
#include <iostream>
#include <vector>

using namespace onerail;

void print_ticket(const Ticket& t) {
    if (t.status == BookingStatus::Confirmed) {
        std::cout << "Ticket ID: " << t.ticket_id << " | Passenger: " << t.passenger_id 
                  << " | Status: Confirmed | Seats: ";
        for (const auto& seat : t.allocated_seats) {
            std::cout << "[Coach " << seat.first << ", Seat " << seat.second << "] ";
        }
        std::cout << "\n";
    } else if (t.status == BookingStatus::Waitlisted) {
        std::cout << "Ticket ID: " << t.ticket_id << " | Passenger: " << t.passenger_id 
                  << " | Status: Waitlisted | WL Number: WL" << t.waitlist_number << "\n";
    } else {
        std::cout << "Ticket ID: " << t.ticket_id << " | Passenger: " << t.passenger_id 
                  << " | Status: Cancelled\n";
    }
}

int main() {
    std::cout << "=== OneRail Booking Engine Demo ===\n";
    
    // Create a small train: 1 coach, 10 seats for easy waitlist demonstration
    BookingEngine engine(1, 10);
    std::vector<int> ticket_ids;
    
    std::cout << "\n--- Booking seats until capacity is exhausted ---\n";
    for (int i = 1; i <= 4; ++i) {
        Request req{100 + i, 3}; // 3 seats per request
        std::cout << "Requesting 3 seats for Passenger " << req.passenger_id << "...\n";
        Ticket t = engine.book(req);
        print_ticket(t);
        ticket_ids.push_back(t.ticket_id);
    }
    
    std::cout << "\n--- Booking additional 2 seats ---\n";
    Request req5{105, 2};
    std::cout << "Requesting 2 seats for Passenger " << req5.passenger_id << "...\n";
    Ticket t5 = engine.book(req5);
    print_ticket(t5);
    ticket_ids.push_back(t5.ticket_id);
    
    std::cout << "\n--- Cancelling Ticket ID " << ticket_ids[0] << " (3 seats) ---\n";
    engine.cancel(ticket_ids[0]);
    std::cout << "Cancelled ticket ID " << ticket_ids[0] << ".\n";
    
    std::cout << "\n--- Checking waitlist promotions ---\n";
    std::cout << "Ticket ID " << ticket_ids[3] << " (was WL1, requested 3 seats):\n";
    print_ticket(engine.get_ticket(ticket_ids[3]));
    
    std::cout << "Ticket ID " << ticket_ids[4] << " (was WL2, requested 2 seats):\n";
    print_ticket(engine.get_ticket(ticket_ids[4]));

    std::cout << "\n=== Demo Complete ===\n";
    return 0;
}
