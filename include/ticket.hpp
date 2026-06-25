#pragma once

#include <vector>
#include <utility>

namespace onerail {

/**
 * @brief Represents the booking status of a ticket.
 */
enum class BookingStatus {
    Confirmed,
    Waitlisted,
    Cancelled
};

/**
 * @brief Represents a ticket in the system.
 */
class Ticket {
public:
    int ticket_id;
    int passenger_id;
    std::vector<std::pair<int, int>> allocated_seats; // pair<coach_id, seat_id>
    BookingStatus status;
    int waitlist_number;      // Only relevant if status == Waitlisted

    Ticket() = default;

    Ticket(int t_id, int p_id, std::vector<std::pair<int, int>> seats, BookingStatus st, int wl_num = 0)
        : ticket_id(t_id), passenger_id(p_id), allocated_seats(std::move(seats)), status(st), waitlist_number(wl_num) {}
};

} // namespace onerail
