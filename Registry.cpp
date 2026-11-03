#ifndef FNB_REGISTRY_CPP
#define FNB_REGISTRY_CPP

#include <algorithm>
#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>

#include "FnbVacancy.cpp"
using namespace std;

template <typename T>
// Wadah generik untuk menyimpan entitas jobs center. Pengurutan disesuaikan
// dengan tipe data: lowongan berdasarkan pengalaman, entitas lain berdasarkan
// nama.
class Registry {
private:
    vector<T> items;

public:
    T& add(T item) {
        items.push_back(move(item));
        return items.back();
    }

    void sortItems() {
        // if constexpr memilih aturan saat kompilasi, sehingga setiap jenis
        // Registry memakai pembanding yang sesuai dengan atribut kelasnya.
        if constexpr (is_same_v<T, FnbVacancy>) {
            sort(items.begin(), items.end(),
                    [](const T& left, const T& right) {
                        if (left.getRequiredExp() != right.getRequiredExp()) {
                            return left.getRequiredExp()
                                    < right.getRequiredExp();
                        }
                        return left.getRoleTitle() < right.getRoleTitle();
                    });
        } else {
            sort(items.begin(), items.end(),
                    [](const T& left, const T& right) {
                        return left.getName() < right.getName();
                    });
        }
    }

    void displayAll() {
        sortItems();
        for (size_t i = 0; i < items.size(); ++i) {
            cout << "\n[" << (i + 1) << "]\n";
            items[i].display();
        }
    }

    vector<T>& getItems() noexcept {
        return items;
    }

    const vector<T>& getItems() const noexcept {
        return items;
    }
};

#endif
