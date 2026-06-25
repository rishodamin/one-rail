#include "coach.hpp"
#include <stdexcept>
#include <cassert>

namespace onerail {

Coach::Coach(int id, int num_seats) 
    : id_(id), num_seats_(num_seats), available_seats_(num_seats) {
    // Determine how many 64-bit integers we need.
    int num_masks = (num_seats + 63) / 64;
    seat_masks_.resize(num_masks, 0ULL);
}

int Coach::get_id() const {
    return id_;
}

int Coach::get_num_seats() const {
    return num_seats_;
}

int Coach::get_available_seats() const {
    return available_seats_;
}

bool Coach::is_seat_free(int seat_idx) const {
    if (seat_idx < 0 || seat_idx >= num_seats_) return false;
    int mask_idx = seat_idx / 64;
    int bit_idx = seat_idx % 64;
    return (seat_masks_[mask_idx] & (1ULL << bit_idx)) == 0;
}

void Coach::set_seat(int seat_idx, bool booked) {
    if (seat_idx < 0 || seat_idx >= num_seats_) return;
    int mask_idx = seat_idx / 64;
    int bit_idx = seat_idx % 64;
    
    if (booked) {
        seat_masks_[mask_idx] |= (1ULL << bit_idx);
    } else {
        seat_masks_[mask_idx] &= ~(1ULL << bit_idx);
    }
}

std::vector<int> Coach::allocate_seats(int num_seats) {
    if (num_seats <= 0 || num_seats > 3) {
        throw std::invalid_argument("Can only allocate 1, 2, or 3 seats.");
    }
    if (available_seats_ < num_seats) {
        return {};
    }

    if (num_seats == 1) return allocate_one();
    if (num_seats == 2) return allocate_two();
    if (num_seats == 3) return allocate_three();

    return {};
}

std::vector<int> Coach::allocate_one() {
    for (int i = 0; i < num_seats_; ++i) {
        if (is_seat_free(i)) {
            set_seat(i, true);
            available_seats_--;
            return {i};
        }
    }
    return {};
}

std::vector<int> Coach::allocate_two() {
    // 1. Try to find two consecutive seats in the same triplet.
    // Triplets are: [0,1,2], [3,4,5], [6,7,8], etc.
    for (int t = 0; t < num_seats_; t += 3) {
        // Within triplet t, we have pairs: (t, t+1) and (t+1, t+2)
        if (t + 1 < num_seats_ && is_seat_free(t) && is_seat_free(t + 1)) {
            set_seat(t, true);
            set_seat(t + 1, true);
            available_seats_ -= 2;
            return {t, t + 1};
        }
        if (t + 2 < num_seats_ && is_seat_free(t + 1) && is_seat_free(t + 2)) {
            set_seat(t + 1, true);
            set_seat(t + 2, true);
            available_seats_ -= 2;
            return {t + 1, t + 2};
        }
    }

    // 2. Fallback: Any two available seats.
    std::vector<int> allocated;
    for (int i = 0; i < num_seats_ && allocated.size() < 2; ++i) {
        if (is_seat_free(i)) {
            allocated.push_back(i);
        }
    }
    
    if (allocated.size() == 2) {
        for (int seat : allocated) set_seat(seat, true);
        available_seats_ -= 2;
        return allocated;
    }
    
    return {};
}

std::vector<int> Coach::allocate_three() {
    // 1. Try to find an entire triplet.
    for (int t = 0; t < num_seats_; t += 3) {
        if (t + 2 < num_seats_ && is_seat_free(t) && is_seat_free(t + 1) && is_seat_free(t + 2)) {
            set_seat(t, true);
            set_seat(t + 1, true);
            set_seat(t + 2, true);
            available_seats_ -= 3;
            return {t, t + 1, t + 2};
        }
    }

    // 2. Fallback: Any three available seats.
    std::vector<int> allocated;
    for (int i = 0; i < num_seats_ && allocated.size() < 3; ++i) {
        if (is_seat_free(i)) {
            allocated.push_back(i);
        }
    }

    if (allocated.size() == 3) {
        for (int seat : allocated) set_seat(seat, true);
        available_seats_ -= 3;
        return allocated;
    }
    
    return {};
}

void Coach::free_seats(const std::vector<int>& seats) {
    for (int seat : seats) {
        if (!is_seat_free(seat)) {
            set_seat(seat, false);
            available_seats_++;
        }
    }
}

} // namespace onerail
