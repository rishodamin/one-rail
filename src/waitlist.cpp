#include "waitlist.hpp"

namespace onerail {

Waitlist::Waitlist() : current_wl_number_(1) {}

int Waitlist::enqueue(int ticket_id, const Request& req) {
    queue_.push({ticket_id, req});
    return current_wl_number_++;
}

bool Waitlist::has_entries() const {
    return !queue_.empty();
}

WaitlistEntry Waitlist::peek() const {
    if (queue_.empty()) {
        throw std::runtime_error("Waitlist is empty.");
    }
    return queue_.front();
}

void Waitlist::pop() {
    if (!queue_.empty()) {
        queue_.pop();
    }
}

} // namespace onerail
