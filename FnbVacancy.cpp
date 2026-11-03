#ifndef FNB_VACANCY_CPP
#define FNB_VACANCY_CPP

#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

#include "Restaurant.cpp"
using namespace std;

// Lowongan menyimpan pointer non-owning ke restoran. Objek Restaurant harus
// tetap hidup selama lowongan digunakan agar pointer selalu valid.
class FnbVacancy {
private:
    string roleTitle;
    int requiredExp;
    bool requiresFoodSafetyCert;
    Restaurant* restaurant;

public:
    FnbVacancy(string title, int experienceRequired, bool requiresCertificate, Restaurant& hiringRestaurant)
        : roleTitle(move(title)),
            requiredExp(experienceRequired),
            requiresFoodSafetyCert(requiresCertificate),
            restaurant(&hiringRestaurant) {
        // Tolak data pengalaman yang tidak masuk akal dan restoran yang belum
        // lolos verifikasi serta pemeriksaan kesehatan.
        if (requiredExp < 0) {
            throw invalid_argument("Required experience cannot be negative.");
        }
        if (!restaurant->getIsVerified()
            || !restaurant->getHasHealthClearance()) {
            throw invalid_argument(
                "A vacancy can only be published by a verified restaurant "
                "with health clearance.");
        }
    }

    const string& getRoleTitle() const noexcept {
        return roleTitle;
    }

    int getRequiredExp() const noexcept {
        return requiredExp;
    }

    bool requiresFoodSafetyCertificate() const noexcept {
        return requiresFoodSafetyCert;
    }

    const Restaurant& getRestaurant() const noexcept {
        return *restaurant;
    }

    void display() const {
        cout << "Position: " << roleTitle
                << "\n  Restaurant: " << restaurant->getName()
                << "\n  Cuisine: " << restaurant->getCuisineType()
                << "\n  Required experience: " << requiredExp << " years"
                << "\n  Food safety certificate: "
                << (requiresFoodSafetyCert ? "Required" : "Not required")
                << "\n  Restaurant verified: "
                << (restaurant->getIsVerified() ? "Yes" : "No")
                << "\n  Health clearance: "
                << (restaurant->getHasHealthClearance() ? "Yes" : "No")
                << '\n';
    }
};

#endif
