#include "booking_engine.hpp"

namespace onerail {

BookingEngine::BookingEngine(int num_coaches, int seats_per_coach)
    : train_(num_coaches, seats_per_coach), next_ticket_id_(1) {}

Ticket BookingEngine::book(const Request& req) {
    int ticket_id = next_ticket_id_++;
    
    // Attempt to allocate seats
    auto allocated = train_.allocate_seats(req.num_seats);
    
    if (!allocated.empty()) {
        // Booking successful
        Ticket t(ticket_id, req.passenger_id, allocated, BookingStatus::Confirmed);
        tickets_[ticket_id] = t;
        return t;
    } else {
        // Put on waitlist
        int wl_num = waitlist_.enqueue(ticket_id, req);
        Ticket t(ticket_id, req.passenger_id, {}, BookingStatus::Waitlisted, wl_num);
        tickets_[ticket_id] = t;
        return t;
    }
}

bool BookingEngine::cancel(int ticket_id) {
    auto it = tickets_.find(ticket_id);
    if (it == tickets_.end()) {
        return false;
    }

    Ticket& t = it->second;
    if (t.status == BookingStatus::Confirmed) {
        train_.free_seats(t.allocated_seats);
        t.status = BookingStatus::Cancelled;
        t.allocated_seats.clear();
        
        // Attempt to promote waitlisted tickets
        process_waitlist();
        return true;
    } else if (t.status == BookingStatus::Waitlisted) {
        // If it's already waitlisted, we mark it Cancelled. 
        // When process_waitlist encounters it at the front, it will discard it.
        t.status = BookingStatus::Cancelled;
        return true;
    }
    
    return false; // Already cancelled
}

void BookingEngine::process_waitlist() {
    while (waitlist_.has_entries()) {
        WaitlistEntry entry = waitlist_.peek();
        
        // Check if the queued ticket was cancelled while waiting
        Ticket& t = tickets_[entry.ticket_id];
        if (t.status == BookingStatus::Cancelled) {
            waitlist_.pop();
            continue;
        }

        // Try to allocate
        auto allocated = train_.allocate_seats(entry.request.num_seats);
        if (!allocated.empty()) {
            t.status = BookingStatus::Confirmed;
            t.allocated_seats = allocated;
            t.waitlist_number = 0;
            waitlist_.pop();
        } else {
            // Strict FIFO: Cannot satisfy the first in queue, so stop processing.
            break;
        }
    }
}

Ticket BookingEngine::get_ticket(int ticket_id) const {
    auto it = tickets_.find(ticket_id);
    if (it != tickets_.end()) {
        return it->second;
    }
    return Ticket(); // Returns default constructed ticket if not found
}

} // namespace onerail
