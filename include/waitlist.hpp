#pragma once

#include "request.hpp"
#include <queue>
#include <stdexcept>

namespace onerail {

/**
 * @brief Represents an entry in the waitlist.
 */
struct WaitlistEntry {
    int ticket_id;
    Request request;
};

/**
 * @brief Manages the waitlist for the booking engine.
 */
class Waitlist {
public:
    Waitlist();

    /**
     * @brief Adds a request to the waitlist and returns the assigned waitlist number.
     * @param ticket_id The ID of the ticket.
     * @param req The original booking request.
     * @return The waitlist number (e.g., WL1 -> 1).
     */
    int enqueue(int ticket_id, const Request& req);

    bool has_entries() const;
    
    /**
     * @brief Returns the next waitlist entry without removing it.
     */
    WaitlistEntry peek() const;
    
    /**
     * @brief Removes the front entry from the waitlist.
     */
    void pop();

private:
    int current_wl_number_;
    std::queue<WaitlistEntry> queue_;
};

} // namespace onerail
