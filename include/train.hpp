#pragma once

#include "coach.hpp"
#include <vector>
#include <utility>

namespace onerail {

/**
 * @brief Represents a train with multiple coaches.
 */
class Train {
public:
    Train(int num_coaches, int seats_per_coach);

    /**
     * @brief Allocates seats across the train.
     * @param num_seats Number of seats to allocate.
     * @return A vector of pairs {coach_id, seat_idx}, empty if allocation fails.
     */
    std::vector<std::pair<int, int>> allocate_seats(int num_seats);

    /**
     * @brief Frees allocated seats across coaches.
     * @param seats A vector of pairs {coach_id, seat_idx}.
     */
    void free_seats(const std::vector<std::pair<int, int>>& seats);

    int get_total_available_seats() const;

private:
    std::vector<Coach> coaches_;
};

} // namespace onerail
