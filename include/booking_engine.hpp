#pragma once

#include "train.hpp"
#include "waitlist.hpp"
#include "ticket.hpp"
#include "request.hpp"
#include <unordered_map>
#include <vector>

namespace onerail {

/**
 * @brief The main booking engine coordinating the Train and Waitlist.
 */
class BookingEngine {
public:
    BookingEngine(int num_coaches, int seats_per_coach);

    /**
     * @brief Books seats for a given request.
     * @param req The booking request (passenger ID and number of seats).
     * @return The generated Ticket (Confirmed or Waitlisted).
     */
    Ticket book(const Request& req);

    /**
     * @brief Cancels a ticket by ID.
     * @param ticket_id The ID of the ticket to cancel.
     * @return true if successful, false if ticket not found or already cancelled.
     */
    bool cancel(int ticket_id);

    /**
     * @brief Retrieves a ticket by its ID.
     */
    Ticket get_ticket(int ticket_id) const;

private:
    Train train_;
    Waitlist waitlist_;
    std::unordered_map<int, Ticket> tickets_;
    int next_ticket_id_;

    void process_waitlist();
};

} // namespace onerail
