#pragma once

#include <vector>
#include <cstdint>
#include <optional>

namespace onerail {

/**
 * @brief Represents a single coach in the train.
 * Manages seats using bitmasks.
 */
class Coach {
public:
    Coach(int id, int num_seats);

    int get_id() const;
    int get_num_seats() const;
    int get_available_seats() const;

    /**
     * @brief Attempts to allocate the specified number of seats (1, 2, or 3).
     * Follows the logical triplet allocation rules.
     * @param num_seats The number of seats requested.
     * @return A vector of allocated seat indices (0-based relative to the coach), or empty if unavailable.
     */
    std::vector<int> allocate_seats(int num_seats);

    /**
     * @brief Frees the given seats.
     * @param seats The seats to free (0-based relative to the coach).
     */
    void free_seats(const std::vector<int>& seats);

private:
    int id_;
    int num_seats_;
    int available_seats_;
    
    // Each 64-bit integer represents 64 seats. 
    // 0 = free, 1 = booked.
    std::vector<uint64_t> seat_masks_;

    bool is_seat_free(int seat_idx) const;
    void set_seat(int seat_idx, bool booked);
    
    std::vector<int> allocate_one();
    std::vector<int> allocate_two();
    std::vector<int> allocate_three();
};

} // namespace onerail
