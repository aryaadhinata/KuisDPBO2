#ifndef FNB_RESTAURANT_CPP
#define FNB_RESTAURANT_CPP

#include <iostream>
#include <string>
#include <utility>
using namespace std;

class PlatformAdmin;

// Status verifikasi dan izin kesehatan hanya dapat diubah oleh PlatformAdmin.
// Pembatasan ini menjaga agar data kepatuhan tidak diubah sembarang bagian
// program.
class Restaurant {
private:
    string restaurantName;
    string cuisineType;
    bool isVerified;
    bool hasHealthClearance;

    friend class PlatformAdmin;

public:
    Restaurant(string name, string cuisine)
        : restaurantName(move(name)),
            cuisineType(move(cuisine)),
            isVerified(false),
            hasHealthClearance(false) {}

    const string& getName() const noexcept {
        return restaurantName;
    }

    const string& getCuisineType() const noexcept {
        return cuisineType;
    }

    bool getIsVerified() const noexcept {
        return isVerified;
    }

    bool getHasHealthClearance() const noexcept {
        return hasHealthClearance;
    }

    void display() const {
        cout << "Restaurant: " << restaurantName
                << "\n  Cuisine: " << cuisineType
                << "\n  Verified: " << (isVerified ? "Yes" : "No")
                << "\n  Health clearance: "
                << (hasHealthClearance ? "Yes" : "No") << '\n';
    }
};

#endif
