#ifndef FNB_HIRING_MIXER_EVENT_CPP
#define FNB_HIRING_MIXER_EVENT_CPP

#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "Restaurant.cpp"
using namespace std;

// Event menyimpan pointer non-owning ke restoran yang berpartisipasi; objek
// restoran dikelola oleh registry dan harus hidup selama event digunakan.
class HiringMixerEvent {
private:
    string eventName;
    string location;
    vector<Restaurant*> participatingRestaurants;
    vector<string> liveCookingTestAgenda;

public:
    HiringMixerEvent(string name, string eventLocation)
        : eventName(move(name)), location(move(eventLocation)) {}

    void addRestaurant(Restaurant& restaurant) {
        // Hanya restoran yang telah diverifikasi dan memiliki izin kesehatan
        // yang boleh mengikuti acara perekrutan.
        if (!restaurant.getIsVerified() || !restaurant.getHasHealthClearance()) {
            throw invalid_argument(
                "Only verified restaurants with health clearance can join.");
        }
        participatingRestaurants.push_back(&restaurant);
    }

    void addLiveCookingTest(string agendaItem) {
        liveCookingTestAgenda.push_back(move(agendaItem));
    }

    void display() const {
        cout << "\n" << eventName << " - " << location << '\n';
        cout << "Participating restaurants:\n";
        for (size_t i = 0; i < participatingRestaurants.size(); ++i) {
            cout << "\n[" << (i + 1) << "]\n";
            participatingRestaurants[i]->display();
        }
        cout << "Live cooking test agenda:\n";
        for (size_t i = 0; i < liveCookingTestAgenda.size(); ++i) {
            cout << "  " << (i + 1) << ". "
                << liveCookingTestAgenda[i] << '\n';
        }
    }
};

#endif
