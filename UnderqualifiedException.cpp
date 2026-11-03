#ifndef FNB_UNDERQUALIFIED_EXCEPTION_CPP
#define FNB_UNDERQUALIFIED_EXCEPTION_CPP

#include <exception>
#include <string>
#include <utility>
using namespace std;

// Exception khusus untuk menjelaskan persyaratan lowongan yang belum dipenuhi
// oleh pelamar, seperti pengalaman minimum atau sertifikat keamanan pangan.
class UnderqualifiedException : public exception {
private:
    string message;

public:
    explicit UnderqualifiedException(string reason)
        : message(move(reason)) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif
