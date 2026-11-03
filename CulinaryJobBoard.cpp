#ifndef FNB_CULINARY_JOB_BOARD_CPP
#define FNB_CULINARY_JOB_BOARD_CPP

#include <iostream>
#include <utility>
#include <vector>

#include "Application.cpp"
#include "FnbProfessional.cpp"
#include "FnbVacancy.cpp"
#include "Registry.cpp"
#include "Restaurant.cpp"
using namespace std;

// Facade yang menjadi pintu utama CLI untuk mengelola registry dan alur
// pengajuan lamaran tanpa mengekspos detail penyimpanan internal.
class CulinaryJobBoard {
private:
    Registry<Restaurant> restaurants;
    Registry<FnbProfessional> professionals;
    Registry<FnbVacancy> vacancies;
    vector<Application> applications;

public:
    Restaurant& addRestaurant(Restaurant restaurant) {
        return restaurants.add(move(restaurant));
    }

    FnbProfessional& addProfessional(FnbProfessional professional) {
        return professionals.add(move(professional));
    }

    FnbVacancy& publishVacancy(FnbVacancy vacancy) {
        return vacancies.add(move(vacancy));
    }

    Application& submitApplication(const FnbProfessional& professional,
                                const FnbVacancy& vacancy) {
        applications.push_back(professional.applyForVacancy(vacancy));
        return applications.back();
    }

    Registry<Restaurant>& getRestaurants() noexcept {
        return restaurants;
    }

    Registry<FnbProfessional>& getProfessionals() noexcept {
        return professionals;
    }

    Registry<FnbVacancy>& getVacancies() noexcept {
        return vacancies;
    }

    const vector<Application>& getApplications() const noexcept {
        return applications;
    }

    void displayApplications() const {
        cout << "\nApplications:\n";
        if (applications.empty()) {
            cout << "No applications submitted.\n";
            return;
        }
        for (size_t i = 0; i < applications.size(); ++i) {
            cout << "\n[" << (i + 1) << "]\n";
            applications[i].display();
        }
    }
};

#endif
