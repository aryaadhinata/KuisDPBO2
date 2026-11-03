#ifndef FNB_CULINARY_PROFILE_CPP
#define FNB_CULINARY_PROFILE_CPP

#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
using namespace std;

// Menyatukan keahlian, pengalaman, dan sertifikat keamanan pangan seorang
// profesional agar seluruh data kualifikasi dapat dikelola sebagai satu profil.
class CulinaryProfile {
private:
    vector<string> specialties;
    int yearsOfExperience;
    bool hasFoodSafetyCert;

public:
    CulinaryProfile(vector<string> profileSpecialties,int experience, bool hasCertificate)
        : specialties(move(profileSpecialties)),
            yearsOfExperience(experience),
            hasFoodSafetyCert(hasCertificate) {
        // Pengalaman negatif tidak mungkin terjadi dan menandakan data profil
        // tidak valid, sehingga objek tidak dibuat.
        if (yearsOfExperience < 0) {
            throw invalid_argument("Experience cannot be negative.");
        }
    }

    const vector<string>& getSpecialties() const noexcept {
        return specialties;
    }

    int getYearsOfExperience() const noexcept {
        return yearsOfExperience;
    }

    bool hasFoodSafetyCertificate() const noexcept {
        return hasFoodSafetyCert;
    }

    void display() const {
        cout << "  Specialties: ";
        if (specialties.empty()) {
            cout << "None";
        } else {
            for (size_t i = 0; i < specialties.size(); ++i) {
                if (i != 0) {
                    cout << ", ";
                }
                cout << specialties[i];
            }
        }
        cout << "\n  Experience: " << yearsOfExperience << " years"
                << "\n  Food safety certificate: "
                << (hasFoodSafetyCert ? "Yes" : "No") << '\n';
    }
};

#endif
