#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <fstream>
#include <string>

using namespace std;

// -----------------------------------------------------
// Definisi Data Mahasiswa
struct Mahasiswa {
    string nama;
    string nik;
    string fakultas;
    string jurusan;
    string email;
    double ipk;
};

// Linked List
struct Node {
    Mahasiswa data;
    Node *next;
};

// Deklarasi fungsi
void Create(Node **head_ref, Mahasiswa data);
void Read(Node *head);
void sorting(Node *head, bool ascending);
void searching(Node *head);
void Update(Node *head);
void Delete(Node **head_ref, string nik);
void login();

// Baca data dari file
void file() {
    Node *head = NULL;
    ifstream file_in("mahasiswa.txt");
    if (file_in.is_open()) {
        Mahasiswa data;
        while (getline(file_in, data.nama)) {
            getline(file_in, data.nik);
            getline(file_in, data.fakultas);
            getline(file_in, data.jurusan);
            getline(file_in, data.email);
            file_in >> data.ipk;
            file_in.ignore();
            Create(&head, data);
        }
        file_in.close();
    }
}
// -----------------------------------------------------

/*** [ MAIN MENU ] ***/
int main() {
    char op;
    bool sort;
    Node *head = NULL;
    file();

    // Login
    login();

    // Tampilkan Menu
    do {
        cout << "== [ MAIN MENU ] ==" << endl << endl;
        cout << "- - -\n";
        cout << "[1] Create Data" << endl;
        cout << "[2] Read Data" << endl;
        cout << "[3] Update Data" << endl;
        cout << "[4] Delete Data" << endl;
        cout << "[5] Searching" << endl;
        cout << "[E] Exit" << endl;
        cout << "- - -\n";
        cout << ">";
        cin >> op;
        cin.ignore();

        switch (op) {

            case '1': {
                // Tambah data
                Mahasiswa data;
                cout << "Nama\t\t: ";
                getline(cin, data.nama);
                cout << "NIK\t\t: ";
                getline(cin, data.nik);
                cout << "Fakultas\t: ";
                getline(cin, data.fakultas);
                cout << "Jurusan\t\t: ";
                getline(cin, data.jurusan);
                cout << "Email\t\t: ";
                getline(cin, data.email);
                cout << "IPK\t\t: ";
                cin >> data.ipk;
                cin.ignore();
                Create(&head, data);
                system("cls");
                break;
            }
            case '2': {
                cout << "1. Ascending\n";
                cout << "2. Descending\n";
                cin >> op;
                if (op == '1') {
                    sort = true;
                } else {
                    sort = false;
                }
                sorting(head, sort);
                Read(head);
                system("pause");
                system("cls");
                break;
            }

            case '3': {
                // Ubah data
                Update(head);
                system("pause");
                system("cls");
                break;
            }

            case '4': {
                // Hapus data
                string nik;
                cout << "Masukkan NIK mahasiswa yang ingin dihapus: ";
                getline(cin, nik);
                Delete(&head, nik);
                system("cls");
                break;
            }

            case '5':
                searching(head);
                system("pause");
                system("cls");
                break;

            case 'E':
            case 'e':
                cout << "Exiting..." << endl;
                system("pause");
                return 0;
            default:
                cout << "Error user input." << endl;
                break;
        }
    } while (op != 0);
    return 0;
}

/** LOGIN **/
void animate() {
    system("cls");

    SetConsoleCP(437);
    SetConsoleOutputCP(437);
    int bar1 = 177, bar2 = 219;

    cout << "Loading...\n";

    for (int i = 0; i < 25; i++) {
        cout << (char) bar1;
    }
    cout << "\r";
    for (int i = 0; i < 25; i++) {
        cout << (char) bar2;
        Sleep(150);
    }
    cout << "\n";
    system("Pause");
    system("cls");
}

void login() {
    animate();
    string username, password;
    char ch;
    do {
        cout << "+===========================================+" << endl;
        cout << "|                  LOGIN                    |" << endl;
        cout << "+===========================================+" << endl;
        cout << "Username\t: ";
        getline(cin, username);
        cout << "Password\t: ";
        ch = _getch();
        while (ch != 13) { // 13 adalah ASCII code untuk tombol "Enter"
            password.push_back(ch);
            cout << '*';
            ch = _getch();
        }
        cout << endl;
        system("cls");
    } while ((username != "admin" && password != "ganteng") || (username != "admin" && password != "cantik"));
    animate();
}

/** CREATE **/
void Create(Node **head_ref, Mahasiswa data) {
    // Buat node baru
    Node *new_node = new Node;
    new_node->data = data;
    new_node->next = NULL;

    // Jika linked list masih kosong
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }

    // Cari node terakhir
    Node *last_node = *head_ref;
    while (last_node->next != NULL) {
        last_node = last_node->next;
    }

    // Tambahkan node baru di akhir
    last_node->next = new_node;

    // Simpan data ke file
    ofstream file_out("mahasiswa.txt", ios::app);
    if (file_out.is_open()) {
        file_out << data.nama << endl;
        file_out << data.nik << endl;
        file_out << data.fakultas << endl;
        file_out << data.jurusan << endl;
        file_out << data.email << endl;
        file_out << data.ipk << endl;
        file_out.close();
    }
}

/** READ **/
void Read(Node *head) {
    // Jika linked list masih kosong
    if (head == NULL) {
        cout << "Data kosong" << endl;
        return;
    }

    // Tampilkan data
    Node *curr = head;
    while (curr != NULL) {
        cout << "Nama: " << curr->data.nama << endl;
        cout << "NIK: " << curr->data.nik << endl;
        cout << "Fakultas: " << curr->data.fakultas << endl;
        cout << "Jurusan: " << curr->data.jurusan << endl;
        cout << "Email: " << curr->data.email << endl;
        cout << "IPK: " << curr->data.ipk << endl;
        cout << endl;
        curr = curr->next;
    }
}

/** SORTING **/
void sorting(Node *head, bool ascending) {
    if (head == NULL) {
        return;
    }

    Node *i = head;
    while (i != NULL) {
        Node *j = i->next;
        while (j != NULL) {
            if ((ascending && i->data.nik > j->data.nik) || (!ascending && i->data.nik < j->data.nik)) {
                Mahasiswa temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
            j = j->next;
        }
        i = i->next;
    }
}

/** SEARCHING **/
void searching(Node *head) {
    // Jika linked list masih kosong
    if (head == NULL) {
        cout << "Data kosong" << endl;
        return;
    }

    // Cari node dengan NIK tertentu
    string nik;
    cout << "NIK yang dicari: ";
    getline(cin, nik);
    Node *curr = head;
    while (curr != NULL && curr->data.nik != nik) {
        curr = curr->next;
        // Jika NIK tidak ditemukan
        if (curr == NULL) {
            cout << "Data tidak ditemukan" << endl;
            return;
        }
    }
    // Tampilkan data sebelum diubah
    cout << "Nama: " << curr->data.nama << endl;
    cout << "NIK: " << curr->data.nik << endl;
    cout << "Fakultas: " << curr->data.fakultas << endl;
    cout << "Jurusan: " << curr->data.jurusan << endl;
    cout << "Email: " << curr->data.email << endl;
    cout << "IPK: " << curr->data.ipk << endl;
}

/** UPDATE **/
void Update(Node *head) {
    // Jika linked list masih kosong
    if (head == NULL) {
        cout << "Data kosong" << endl;
        return;
    }

    // Cari node dengan NIK tertentu
    string nik;
    cout << "Masukkan NIK mahasiswa yang ingin diubah: ";
    getline(cin, nik);
    Node *curr = head;
    while (curr != NULL && curr->data.nik != nik) {
        curr = curr->next;
        // Jika NIK tidak ditemukan
        if (curr == NULL) {
            cout << "Data tidak ditemukan" << endl;
            return;
        }
    }
    // Tampilkan data sebelum diubah
    cout << "Data sebelum diubah: " << endl;
    cout << "Nama: " << curr->data.nama << endl;
    cout << "NIK: " << curr->data.nik << endl;
    cout << "Fakultas: " << curr->data.fakultas << endl;
    cout << "Jurusan: " << curr->data.jurusan << endl;
    cout << "Email: " << curr->data.email << endl;
    cout << "IPK: " << curr->data.ipk << endl;

    // Masukkan data baru
    Mahasiswa data;
    cout << "Masukkan data baru: " << endl;
    cout << "Nama: ";
    getline(cin, data.nama);
    cout << "NIK: ";
    getline(cin, data.nik);
    cout << "Fakultas: ";
    getline(cin, data.fakultas);
    cout << "Jurusan: ";
    getline(cin, data.jurusan);
    cout << "Email: ";
    getline(cin, data.email);
    cout << "IPK: ";
    cin >> data.ipk;
    cin.ignore();

    // Ubah data pada node yang dipilih
    curr->data = data;

    // Simpan data ke file
    ofstream file_out("mahasiswa.txt");
    if (file_out.is_open()) {
        Node *curr = head;
        while (curr != NULL) {
            file_out << curr->data.nama << endl;
            file_out << curr->data.nik << endl;
            file_out << curr->data.fakultas << endl;
            file_out << curr->data.jurusan << endl;
            file_out << curr->data.email << endl;
            file_out << curr->data.ipk << endl;
            curr = curr->next;
        }
        file_out.close();
    }
}

/** DELETE **/
void Delete(Node **head_ref, string nik) {
    // Jika linked list masih kosong
    if (*head_ref == NULL) {
        cout << "Data kosong" << endl;
        return;
    }

    // Cari node dengan NIK tertentu
    Node *curr = *head_ref;
    Node *prev = NULL;
    while (curr != NULL && curr->data.nik != nik) {
        prev = curr;
        curr = curr->next;
    }

    // Jika NIK tidak ditemukan
    if (curr == NULL) {
        cout << "Data tidak ditemukan" << endl;
        return;
    }

    // Hapus node yang dipilih
    if (prev == NULL) {
        *head_ref = curr->next;
    } else {
        prev->next = curr->next;
    }
    delete curr;

    cout << "Data berhasil dihapus" << endl;
    // Simpan data ke file
    ofstream file_out("mahasiswa.txt");
    if (file_out.is_open()) {
        Node *curr = *head_ref;
        while (curr != NULL) {
            file_out << curr->data.nama << endl;
            file_out << curr->data.nik << endl;
            file_out << curr->data.fakultas << endl;
            file_out << curr->data.jurusan << endl;
            file_out << curr->data.email << endl;
            file_out << curr->data.ipk << endl;
            curr = curr->next;
        }
        file_out.close();
    }
}