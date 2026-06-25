#pragma once

namespace onerail {

/**
 * @brief Represents a request for booking tickets.
 */
struct Request {
    int passenger_id;
    int num_seats; // Expected to be 1, 2, or 3.
};

} // namespace onerail
