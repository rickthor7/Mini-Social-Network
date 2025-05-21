#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <queue>
#include <stack> // Meskipun tidak digunakan secara eksplisit di fitur utama, ada untuk kelengkapan
#include <map>
#include <algorithm> // Untuk find, sort, unique
#include <set>       // Untuk kemudahan mencari mutual friends dan unique friend suggestions
#include <limits>    // Untuk std::numeric_limits

// Menggunakan namespace std untuk menghindari penulisan std:: berulang kali
using namespace std;

class SocialNetwork {
private:
    int next_user_id;
    map<string, int> user_to_id;
    vector<string> id_to_user;
    vector<list<int>> adj_list; // Adjacency list

    // Helper untuk mengecek apakah user ada dan mendapatkan ID
    bool get_id_by_name(const string& name, int& id) const {
        auto it = user_to_id.find(name);
        if (it != user_to_id.end()) {
            id = it->second;
            return true;
        }
        return false;
    }

public:
    SocialNetwork() : next_user_id(0) {}

    // 1. Tambah Pengguna
    bool addUser(const string& user_name) {
        if (user_to_id.count(user_name)) {
            cout << "Error: Pengguna '" << user_name << "' sudah ada." << endl;
            return false;
        }
        user_to_id[user_name] = next_user_id;
        id_to_user.push_back(user_name);
        adj_list.resize(next_user_id + 1); // Pastikan adj_list cukup besar
        cout << "Pengguna '" << user_name << "' berhasil ditambahkan dengan ID " << next_user_id << "." << endl;
        next_user_id++;
        return true;
    }

    // 2. Buat Pertemanan
    bool addFriendship(const string& user1_name, const string& user2_name) {
        if (user1_name == user2_name) {
            cout << "Error: Tidak bisa berteman dengan diri sendiri." << endl;
            return false;
        }

        int id1, id2;
        if (!get_id_by_name(user1_name, id1)) {
            cout << "Error: Pengguna '" << user1_name << "' tidak ditemukan." << endl;
            return false;
        }
        if (!get_id_by_name(user2_name, id2)) {
            cout << "Error: Pengguna '" << user2_name << "' tidak ditemukan." << endl;
            return false;
        }

        // Cek apakah sudah berteman
        bool already_friends = false;
        for (int friend_id : adj_list[id1]) {
            if (friend_id == id2) {
                already_friends = true;
                break;
            }
        }

        if (already_friends) {
            cout << "'" << user1_name << "' dan '" << user2_name << "' sudah berteman." << endl;
            return false;
        }

        adj_list[id1].push_back(id2);
        adj_list[id2].push_back(id1); // Pertemanan dua arah
        cout << "Pertemanan antara '" << user1_name << "' dan '" << user2_name << "' berhasil ditambahkan." << endl;
        return true;
    }

    // 3. Tampilkan Teman dari Seorang Pengguna
    void displayFriends(const string& user_name) const {
        int id;
        if (!get_id_by_name(user_name, id)) {
            cout << "Error: Pengguna '" << user_name << "' tidak ditemukan." << endl;
            return;
        }

        cout << "Teman-teman dari '" << user_name << "':" << endl;
        if (adj_list[id].empty()) {
            cout << "  (Tidak memiliki teman)" << endl;
        } else {
            for (int friend_id : adj_list[id]) {
                cout << "  - " << id_to_user[friend_id] << endl;
            }
        }
    }

    // 4. Cari Teman Bersama (Mutual Friends)
    void displayMutualFriends(const string& user1_name, const string& user2_name) const {
        int id1, id2;
        if (!get_id_by_name(user1_name, id1)) {
            cout << "Error: Pengguna '" << user1_name << "' tidak ditemukan." << endl;
            return;
        }
        if (!get_id_by_name(user2_name, id2)) {
            cout << "Error: Pengguna '" << user2_name << "' tidak ditemukan." << endl;
            return;
        }

        if (id1 == id2) {
            cout << "Error: Tidak bisa mencari teman bersama dengan diri sendiri." << endl;
            return;
        }

        cout << "Teman bersama antara '" << user1_name << "' dan '" << user2_name << "':" << endl;
        
        set<int> friends_of_user1;
        for (int friend_id : adj_list[id1]) {
            friends_of_user1.insert(friend_id);
        }

        list<string> mutuals;
        for (int friend_id_of_user2 : adj_list[id2]) {
            if (friends_of_user1.count(friend_id_of_user2)) {
                if (friend_id_of_user2 != id1 && friend_id_of_user2 != id2) {
                     mutuals.push_back(id_to_user[friend_id_of_user2]);
                }
            }
        }
        
        if (mutuals.empty()) {
            cout << "  (Tidak ada teman bersama)" << endl;
        } else {
            for (const string& name : mutuals) {
                cout << "  - " << name << endl;
            }
        }
    }

    // 5. Hitung Jarak Pertemanan Terpendek (Degrees of Separation) menggunakan BFS
    int getDegreesOfSeparation(const string& start_user_name, const string& end_user_name) const {
        int start_id, end_id;
        if (!get_id_by_name(start_user_name, start_id)) {
            cout << "Error: Pengguna awal '" << start_user_name << "' tidak ditemukan." << endl;
            return -1;
        }
        if (!get_id_by_name(end_user_name, end_id)) {
            cout << "Error: Pengguna akhir '" << end_user_name << "' tidak ditemukan." << endl;
            return -1;
        }

        if (start_id == end_id) return 0;

        queue<pair<int, int>> q; // {user_id, distance}
        q.push({start_id, 0});

        vector<bool> visited(next_user_id, false);
        visited[start_id] = true;

        while (!q.empty()) {
            int current_id = q.front().first;
            int distance = q.front().second;
            q.pop();

            for (int neighbor_id : adj_list[current_id]) {
                if (neighbor_id == end_id) {
                    return distance + 1;
                }
                if (!visited[neighbor_id]) {
                    visited[neighbor_id] = true;
                    q.push({neighbor_id, distance + 1});
                }
            }
        }
        return -1; // Tidak ada jalur
    }

    // 6. Tampilkan Saran Teman (Teman dari Teman)
    void suggestFriends(const string& user_name) const {
        int user_id;
        if (!get_id_by_name(user_name, user_id)) {
            cout << "Error: Pengguna '" << user_name << "' tidak ditemukan." << endl;
            return;
        }

        set<int> suggestions_ids;
        set<int> direct_friends_ids;
        for (int friend_id : adj_list[user_id]) {
            direct_friends_ids.insert(friend_id);
        }

        for (int friend_id : adj_list[user_id]) {
            for (int fof_id : adj_list[friend_id]) { 
                if (fof_id != user_id && !direct_friends_ids.count(fof_id)) {
                    suggestions_ids.insert(fof_id);
                }
            }
        }
        
        cout << "Saran teman untuk '" << user_name << "':" << endl;
        if (suggestions_ids.empty()) {
            cout << "  (Tidak ada saran teman saat ini)" << endl;
        } else {
            for (int suggested_id : suggestions_ids) {
                cout << "  - " << id_to_user[suggested_id] << endl;
            }
        }
    }

    void displayAllUsers() const {
        cout << "\nDaftar Semua Pengguna Terdaftar:" << endl;
        if (next_user_id == 0) {
            cout << "  (Belum ada pengguna terdaftar)" << endl;
            return;
        }
        for (int i = 0; i < next_user_id; ++i) {
            cout << "  - " << id_to_user[i] << " (ID: " << i << ")" << endl;
        }
    }
};


int main() {
    SocialNetwork sn;
    int choice;
    string name1, name2;

    // Contoh beberapa pengguna dan pertemanan awal
    sn.addUser("Alice");
    sn.addUser("Bob");
    sn.addUser("Charlie");
    sn.addUser("David");
    sn.addUser("Eve");
    sn.addUser("Fiona");

    sn.addFriendship("Alice", "Bob");
    sn.addFriendship("Alice", "Charlie");
    sn.addFriendship("Bob", "David");
    sn.addFriendship("Charlie", "David");
    sn.addFriendship("Charlie", "Eve");
    sn.addFriendship("David", "Fiona");
    sn.addFriendship("Eve", "Fiona");


    do {
        cout << "\n--- Mini Social Network Menu ---" << endl;
        cout << "1. Tambah Pengguna" << endl;
        cout << "2. Tambah Pertemanan" << endl;
        cout << "3. Tampilkan Teman Pengguna" << endl;
        cout << "4. Cari Teman Bersama" << endl;
        cout << "5. Hitung Jarak Pertemanan (Degrees of Separation)" << endl;
        cout << "6. Saran Teman" << endl;
        cout << "7. Tampilkan Semua Pengguna" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilihan Anda: ";
        cin >> choice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

        switch (choice) {
            case 1:
                cout << "Masukkan nama pengguna baru: ";
                getline(cin, name1);
                sn.addUser(name1);
                break;
            case 2:
                cout << "Masukkan nama pengguna pertama: ";
                getline(cin, name1);
                cout << "Masukkan nama pengguna kedua: ";
                getline(cin, name2);
                sn.addFriendship(name1, name2);
                break;
            case 3:
                cout << "Masukkan nama pengguna untuk melihat teman-temannya: ";
                getline(cin, name1);
                sn.displayFriends(name1);
                break;
            case 4:
                cout << "Masukkan nama pengguna pertama: ";
                getline(cin, name1);
                cout << "Masukkan nama pengguna kedua: ";
                getline(cin, name2);
                sn.displayMutualFriends(name1, name2);
                break;
            case 5:
                cout << "Masukkan nama pengguna awal: ";
                getline(cin, name1);
                cout << "Masukkan nama pengguna akhir: ";
                getline(cin, name2);
                {
                    int degrees = sn.getDegreesOfSeparation(name1, name2);
                    if (degrees == 0 && name1 == name2) {
                         cout << "Jarak ke diri sendiri adalah 0." << endl;
                    } else if (degrees != -1) {
                        cout << "Jarak pertemanan antara '" << name1 << "' dan '" << name2 << "' adalah: " << degrees << endl;
                    } else {
                        cout << "Tidak ada jalur pertemanan antara '" << name1 << "' dan '" << name2 << "'." << endl;
                    }
                }
                break;
            case 6:
                cout << "Masukkan nama pengguna untuk mendapatkan saran teman: ";
                getline(cin, name1);
                sn.suggestFriends(name1);
                break;
            case 7:
                sn.displayAllUsers();
                break;
            case 0:
                cout << "Keluar dari program..." << endl;
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (choice != 0);

    return 0;
}
