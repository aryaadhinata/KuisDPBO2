#ifndef FNB_PROFESSIONAL_CPP
#define FNB_PROFESSIONAL_CPP

#include <iostream>
#include <string>
#include <utility>

#include "CulinaryProfile.cpp"
using namespace std;

class FnbVacancy;
class Application;

// Profesional memiliki CulinaryProfile secara langsung (composition), sehingga
// profil menjadi bagian dari siklus hidup objek profesional.
class FnbProfessional {
private:
    string name;
    string contact;
    CulinaryProfile profile;

public:
    FnbProfessional(string professionalName, string professionalContact, CulinaryProfile culinaryProfile)
        : name(move(professionalName)),
            contact(move(professionalContact)),
            profile(move(culinaryProfile)) {}

    const string& getName() const noexcept {
        return name;
    }

    const string& getContact() const noexcept {
        return contact;
    }

    const CulinaryProfile& getProfile() const noexcept {
        return profile;
    }

    // Implementasi diletakkan setelah deklarasi Application agar tipe hasil
    // fungsi sudah lengkap ketika objek Application dibuat.
    Application applyForVacancy(const FnbVacancy& vacancy) const;

    void display() const {
        cout << name << " (" << contact << ")\n";
        profile.display();
    }
};

#endif
