#include "train.hpp"

namespace onerail {

Train::Train(int num_coaches, int seats_per_coach) {
    for (int i = 0; i < num_coaches; ++i) {
        coaches_.emplace_back(i + 1, seats_per_coach); // Coach IDs 1-indexed
    }
}

std::vector<std::pair<int, int>> Train::allocate_seats(int num_seats) {
    // 1. Try to allocate entirely within a single coach.
    for (auto& coach : coaches_) {
        auto allocated = coach.allocate_seats(num_seats);
        if (!allocated.empty()) {
            std::vector<std::pair<int, int>> result;
            for (int seat : allocated) {
                result.push_back({coach.get_id(), seat});
            }
            return result;
        }
    }

    // 2. Fallback: split across coaches (only for 2 or 3 seats)
    if (get_total_available_seats() >= num_seats) {
        std::vector<std::pair<int, int>> result;
        int remaining = num_seats;
        for (auto& coach : coaches_) {
            while (remaining > 0 && coach.get_available_seats() > 0) {
                auto alloc = coach.allocate_seats(1);
                if (!alloc.empty()) {
                    result.push_back({coach.get_id(), alloc[0]});
                    remaining--;
                }
            }
            if (remaining == 0) {
                return result;
            }
        }
    }

    return {};
}

void Train::free_seats(const std::vector<std::pair<int, int>>& seats) {
    for (const auto& seat_info : seats) {
        int coach_id = seat_info.first;
        int seat_idx = seat_info.second;
        
        for (auto& coach : coaches_) {
            if (coach.get_id() == coach_id) {
                coach.free_seats({seat_idx});
                break;
            }
        }
    }
}

int Train::get_total_available_seats() const {
    int total = 0;
    for (const auto& coach : coaches_) {
        total += coach.get_available_seats();
    }
    return total;
}

} // namespace onerail
