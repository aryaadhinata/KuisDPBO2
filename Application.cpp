#ifndef FNB_APPLICATION_CPP
#define FNB_APPLICATION_CPP

#include <iostream>
#include <string>
#include <utility>

#include "FnbProfessional.cpp"
#include "FnbVacancy.cpp"
#include "UnderqualifiedException.cpp"
using namespace std;

enum class ApplicationStatus {
    Pending,
    Accepted,
    Rejected
};

// Mengubah enum status menjadi teks yang konsisten untuk laporan CLI.
inline const char* toString(ApplicationStatus status) noexcept {
    switch (status) {
    case ApplicationStatus::Pending:
        return "Pending";
    case ApplicationStatus::Accepted:
        return "Accepted";
    case ApplicationStatus::Rejected:
        return "Rejected";
    }
    return "Unknown";
}

// Lamaran menyimpan salinan data pelamar dan lowongan pada saat pengajuan,
// beserta status proses yang dapat diperbarui oleh sistem.
class Application {
private:
    FnbProfessional applicant;
    FnbVacancy vacancy;
    ApplicationStatus status;

public:
    Application(FnbProfessional professional, FnbVacancy job)
        : applicant(move(professional)),
            vacancy(move(job)),
            status(ApplicationStatus::Pending) {}

    const FnbProfessional& getApplicant() const noexcept {
        return applicant;
    }

    const FnbVacancy& getVacancy() const noexcept {
        return vacancy;
    }

    ApplicationStatus getStatus() const noexcept {
        return status;
    }

    void setStatus(ApplicationStatus newStatus) noexcept {
        status = newStatus;
    }

    void display() const {
        cout << "Applicant: " << applicant.getName()
                << "\nContact: " << applicant.getContact()
                << "\nApplied position: " << vacancy.getRoleTitle()
                << "\nRestaurant: " << vacancy.getRestaurant().getName()
                << "\nStatus: " << toString(status)
                << "\nApplicant profile:\n";
        applicant.getProfile().display();
    }
};

inline Application
FnbProfessional::applyForVacancy(const FnbVacancy& vacancy) const {
    // Periksa seluruh syarat sebelum membuat lamaran. Jika satu syarat gagal,
    // exception dikirim ke pemanggil dan tidak ada lamaran yang disimpan.
    if (profile.getYearsOfExperience() < vacancy.getRequiredExp()) {
        throw UnderqualifiedException(
            name + " does not meet the experience requirement for "
            + vacancy.getRoleTitle() + ".");
    }
    if (vacancy.requiresFoodSafetyCertificate()
        && !profile.hasFoodSafetyCertificate()) {
        throw UnderqualifiedException(
            name + " does not have the required food safety certificate for "
            + vacancy.getRoleTitle() + ".");
    }
    return Application(*this, vacancy);
}

#endif
