#ifndef FNB_PLATFORM_ADMIN_CPP
#define FNB_PLATFORM_ADMIN_CPP

#include <stdexcept>

#include "Restaurant.cpp"
using namespace std;

// Sebagai friend Restaurant, admin dapat memperbarui status kepatuhan secara
// langsung tanpa menyediakan setter publik pada kelas Restaurant.
class PlatformAdmin {
public:
    void verifyRestaurant(Restaurant& restaurant) const {
        restaurant.isVerified = true;
    }

    void grantHealthClearance(Restaurant& restaurant) const {
        if (!restaurant.isVerified) {
            throw invalid_argument(
                "Verify a restaurant before granting health clearance.");
        }
        restaurant.hasHealthClearance = true;
    }

    void revokeHealthClearance(Restaurant& restaurant) const {
        restaurant.hasHealthClearance = false;
    }
};

#endif
