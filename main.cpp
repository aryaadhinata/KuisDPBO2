#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "UnderqualifiedException.cpp"
#include "CulinaryProfile.cpp"
#include "Restaurant.cpp"
#include "FnbVacancy.cpp"
#include "FnbProfessional.cpp"
#include "Application.cpp"
#include "HiringMixerEvent.cpp"
#include "PlatformAdmin.cpp"
#include "Registry.cpp"
#include "CulinaryJobBoard.cpp"
using namespace std;

void printSection(const string& title) {
    cout << "\n"
            << string(64, '=') << '\n'
            << title << '\n'
            << string(64, '=') << '\n';
}

int main() {
    try {
        // CulinaryJobBoard mengelola seluruh registry. Admin memverifikasi
        // restoran dan memberikan izin kesehatan sebelum lowongan dibuat.
        CulinaryJobBoard jobBoard;
        PlatformAdmin admin;

        jobBoard.addRestaurant(Restaurant("Kopi Senja", "Cafe & Indonesian"));
        jobBoard.addRestaurant(
            Restaurant("Maison de Saveur", "French Fine Dining"));
        jobBoard.addRestaurant(Restaurant("Roti Pagi", "Bakery"));

        vector<Restaurant>& restaurants =
            jobBoard.getRestaurants().getItems();
        for (Restaurant& restaurant : restaurants) {
            admin.verifyRestaurant(restaurant);
            admin.grantHealthClearance(restaurant);
        }

        Restaurant& cafe = restaurants[0];
        Restaurant& fineDining = restaurants[1];
        Restaurant& bakery = restaurants[2];

        cout << "F&B JOBS CENTER\n"
                << "Restaurant, culinary professional, and vacancy system\n";
        printSection("REGISTERED RESTAURANTS");
        jobBoard.getRestaurants().displayAll();

        jobBoard.addProfessional(FnbProfessional(
            "Rani Putri", "rani@example.com",
            CulinaryProfile({"Indonesian", "Pastry"}, 6, false)));
        jobBoard.addProfessional(FnbProfessional(
            "Bima Santoso", "bima@example.com",
            CulinaryProfile({"French", "Fine Dining"}, 8, true)));

        printSection("REGISTERED CULINARY PROFESSIONALS");
        jobBoard.getProfessionals().displayAll();

        jobBoard.publishVacancy(FnbVacancy("Head Chef", 5, true, fineDining));
        jobBoard.publishVacancy(FnbVacancy("Waiter", 0, false, cafe));
        jobBoard.publishVacancy(
            FnbVacancy("Pastry Assistant", 1, true, bakery));

        // Cari data setelah seluruh objek ditambahkan. Registry menggunakan
        // vector yang dapat memindahkan elemen saat kapasitasnya bertambah;
        // pencarian ulang memastikan referensi menunjuk ke elemen yang benar.
        const auto findProfessional = [&](const string& name)
            -> FnbProfessional& {
            auto& professionals = jobBoard.getProfessionals().getItems();
            const auto found = find_if(
                professionals.begin(), professionals.end(),
                [&](const FnbProfessional& professional) {
                    return professional.getName() == name;
                });
            if (found == professionals.end()) {
                throw logic_error("Registered professional was not found.");
            }
            return *found;
        };
        FnbProfessional& rani = findProfessional("Rani Putri");
        FnbProfessional& bima = findProfessional("Bima Santoso");

        const auto findVacancy = [&](const string& title) -> FnbVacancy& {
            auto& vacancies = jobBoard.getVacancies().getItems();
            const auto found = find_if(
                vacancies.begin(), vacancies.end(),
                [&](const FnbVacancy& vacancy) {
                    return vacancy.getRoleTitle() == title;
                });
            if (found == vacancies.end()) {
                throw logic_error("Published vacancy was not found.");
            }
            return *found;
        };
        FnbVacancy& headChef = findVacancy("Head Chef");
        FnbVacancy& waiter = findVacancy("Waiter");

        printSection("APPLICATION SUBMISSION");
        // Setiap lamaran ditangani terpisah: kegagalan satu pelamar ditampilkan,
        // tetapi tidak menghentikan pemrosesan pelamar berikutnya.
        try {
            jobBoard.submitApplication(rani, headChef);
        } catch (const UnderqualifiedException& exception) {
            cout << "[REJECTED] " << exception.what() << '\n';
        }

        try {
            Application& application = jobBoard.submitApplication(rani, waiter);
            application.setStatus(ApplicationStatus::Accepted);
            cout << "[SUBMITTED] " << rani.getName() << " -> "
                    << waiter.getRoleTitle() << '\n';
        } catch (const UnderqualifiedException& exception) {
            cout << "[REJECTED] " << exception.what() << '\n';
        }

        try {
            Application& application = jobBoard.submitApplication(bima, headChef);
            application.setStatus(ApplicationStatus::Accepted);
            cout << "[SUBMITTED] " << bima.getName() << " -> "
                    << headChef.getRoleTitle() << '\n';
        } catch (const UnderqualifiedException& exception) {
            cout << "[REJECTED] " << exception.what() << '\n';
        }

        HiringMixerEvent mixer("Bandung Culinary Fair", "Bandung");
        mixer.addRestaurant(cafe);
        mixer.addRestaurant(fineDining);
        mixer.addLiveCookingTest("Pastry plating challenge - 10:00");
        mixer.addLiveCookingTest("Live kitchen service simulation - 13:00");
        printSection("HIRING MIXER EVENT");
        mixer.display();

        printSection("APPLICATION DETAILS");
        jobBoard.displayApplications();

        printSection("VACANCIES (LOWEST EXPERIENCE REQUIREMENT FIRST)");
        jobBoard.getVacancies().displayAll();
    } catch (const exception& exception) {
        cerr << "System error: " << exception.what() << '\n';
        return 1;
    }

    return 0;
}
