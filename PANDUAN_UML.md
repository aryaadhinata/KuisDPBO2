# Panduan UML F&B Jobs Center

Setiap kelas berada di file `.cpp` terpisah tanpa file `.hpp`. `main.cpp`
meng-include file kelas tersebut untuk menyediakan definisinya saat kompilasi.
Dokumen ini menjadi panduan untuk menggambar class diagram sistem pusat
lowongan kerja kuliner dan restoran.

## Langkah menggambar

1. Buat kotak untuk setiap kelas: `UnderqualifiedException`,
   `CulinaryProfile`, `FnbProfessional`, `Restaurant`, `FnbVacancy`,
   `Application`, `HiringMixerEvent`, `PlatformAdmin`, `Registry<T>`, dan
   `CulinaryJobBoard`.
2. Bagi kotak kelas menjadi nama, atribut, dan operasi. Gunakan `-` untuk
   `private` dan `+` untuk `public`.
3. Hubungkan kelas menggunakan relasi UML:
   - `FnbProfessional` memiliki `CulinaryProfile` (composition, belah ketupat
     hitam di sisi `FnbProfessional`).
   - `Application` menyimpan satu `FnbProfessional` dan satu `FnbVacancy`.
   - `FnbVacancy` merujuk ke satu `Restaurant`.
   - `HiringMixerEvent` menyimpan kumpulan restoran peserta.
   - `CulinaryJobBoard` mengelola registry restoran, profesional, lowongan,
     serta kumpulan lamaran.
   - `PlatformAdmin` memiliki dependency `<<friend>>` terhadap `Restaurant`.
   - `UnderqualifiedException` mewarisi `std::exception`.
   - `Registry<T>` adalah template yang menyimpan dan mengurutkan entitas.
4. Tempelkan PlantUML di bawah ke editor PlantUML atau gunakan relasinya untuk
   menggambar diagram secara manual di draw.io.

## PlantUML

```plantuml
@startuml
skinparam classAttributeIconSize 0

class UnderqualifiedException {
  -message: string
  +what() const: const char*
}

class CulinaryProfile {
  -specialties: vector<string>
  -yearsOfExperience: int
  -hasFoodSafetyCert: bool
  +getSpecialties() const: vector<string>
  +getYearsOfExperience() const: int
  +hasFoodSafetyCertificate() const: bool
  +display() const: void
}

class FnbProfessional {
  -name: string
  -contact: string
  -profile: CulinaryProfile
  +getName() const: string
  +getContact() const: string
  +getProfile() const: CulinaryProfile
  +applyForVacancy(vacancy: FnbVacancy) const: Application
  +display() const: void
}

class Restaurant {
  -restaurantName: string
  -cuisineType: string
  -isVerified: bool = false
  -hasHealthClearance: bool = false
  +getName() const: string
  +getCuisineType() const: string
  +getIsVerified() const: bool
  +getHasHealthClearance() const: bool
  +display() const: void
}

class FnbVacancy {
  -roleTitle: string
  -requiredExp: int
  -requiresFoodSafetyCert: bool
  -restaurant: Restaurant*
  +getRoleTitle() const: string
  +getRequiredExp() const: int
  +requiresFoodSafetyCertificate() const: bool
  +getRestaurant() const: Restaurant
  +display() const: void
}

class Application {
  -applicant: FnbProfessional
  -vacancy: FnbVacancy
  -status: ApplicationStatus
  +getStatus() const: ApplicationStatus
  +setStatus(status: ApplicationStatus): void
  +display() const: void
}

enum ApplicationStatus {
  Pending
  Accepted
  Rejected
}

class HiringMixerEvent {
  -eventName: string
  -location: string
  -participatingRestaurants: vector<Restaurant*>
  -liveCookingTestAgenda: vector<string>
  +addRestaurant(restaurant: Restaurant): void
  +addLiveCookingTest(item: string): void
  +display() const: void
}

class PlatformAdmin {
  +verifyRestaurant(restaurant: Restaurant): void
  +grantHealthClearance(restaurant: Restaurant): void
  +revokeHealthClearance(restaurant: Restaurant): void
}

class "Registry<T>" as Registry {
  -items: vector<T>
  +add(item: T): T&
  +sortItems(): void
  +displayAll(): void
}

class CulinaryJobBoard {
  -restaurants: Registry<Restaurant>
  -professionals: Registry<FnbProfessional>
  -vacancies: Registry<FnbVacancy>
  -applications: vector<Application>
  +addRestaurant(restaurant: Restaurant): Restaurant&
  +addProfessional(professional: FnbProfessional): FnbProfessional&
  +publishVacancy(vacancy: FnbVacancy): FnbVacancy&
  +submitApplication(professional, vacancy): Application&
  +displayApplications() const: void
}

UnderqualifiedException --|> std::exception
FnbProfessional *-- "1" CulinaryProfile
Application *-- "1" FnbProfessional
Application *-- "1" FnbVacancy
FnbVacancy --> "1" Restaurant : references
HiringMixerEvent o-- "0..*" Restaurant
CulinaryJobBoard *-- Registry : restaurants
CulinaryJobBoard *-- Registry : professionals
CulinaryJobBoard *-- Registry : vacancies
CulinaryJobBoard *-- "0..*" Application
Registry ..> Restaurant : T
Registry ..> FnbProfessional : T
Registry ..> FnbVacancy : T
PlatformAdmin ..> Restaurant : <<friend>>

note right of Restaurant
  PlatformAdmin dapat mengubah
  status verifikasi dan health clearance.
end note
@enduml
```

## Catatan implementasi

- `FnbProfessional` memiliki `CulinaryProfile` sebagai composition.
- Pembuatan lowongan mensyaratkan restoran sudah terverifikasi dan memiliki
  health clearance.
- Pelamar ditolak dengan `UnderqualifiedException` ketika pengalaman tidak
  cukup atau sertifikat keamanan pangan diwajibkan tetapi tidak dimiliki.
- `Registry<FnbVacancy>` mengurutkan lowongan berdasarkan pengalaman minimum.
- Tambahkan semua restoran ke registry sebelum membuat lowongan atau event yang
  menyimpan pointer ke restoran, agar alamat objek tetap valid.
