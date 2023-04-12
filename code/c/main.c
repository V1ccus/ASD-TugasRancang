#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include <conio.h>

// Definisi Data Mahasiswa
struct Mahasiswa {
    char nama[50];
    char nik[20];
    char fakultas[50];
    char jurusan[50];
    char email[50];
    double ipk;
};

// Linked List
struct Node {
    struct Mahasiswa data;
    struct Node *next;
};

// Deklarasi fungsi
void Create(struct Node **head_ref, struct Mahasiswa data);
void Read(struct Node *head);
void sorting(struct Node *head, bool ascending);
void searching(struct Node *head);
void Update(struct Node *head);
void Delete(struct Node **head_ref, char nik[]);

// Baca data dari file
void file() {
    struct Node *head = NULL;
    FILE *fp = fopen("mahasiswa.txt", "r");
    if (fp != NULL) {
        struct Mahasiswa data;
        while (fgets(data.nama, sizeof(data.nama), fp) != NULL) {
            fgets(data.nik, sizeof(data.nik), fp);
            fgets(data.fakultas, sizeof(data.fakultas), fp);
            fgets(data.jurusan, sizeof(data.jurusan), fp);
            fgets(data.email, sizeof(data.email), fp);
            fscanf(fp, "%lf", &data.ipk);
            fgetc(fp);
            Create(&head, data);
        }
        fclose(fp);
    }
}

// -----------------------------------------------------

/*** [ MAIN MENU ] ***/
int main() {
    char op;
    bool sort;
    struct Node *head = NULL;
    file();

    // Login
    login();

    // Tampilkan Menu
    do {
        printf("== [ MAIN MENU ] ==\n\n");
        printf("- - -\n");
        printf("[1] Create Data\n");
        printf("[2] Read Data\n");
        printf("[3] Update Data\n");
        printf("[4] Delete Data\n");
        printf("[5] Searching\n");
        printf("[E] Exit\n");
        printf("- - -\n");
        printf(">");
        scanf("%c", &op);
        fflush(stdin);

        switch (op) {
        case '1': {
            // Tambah data
            struct Mahasiswa data;
            printf("Nama\t\t: ");
            fgets(data.nama, sizeof(data.nama), stdin);
            printf("NIK\t\t: ");
            fgets(data.nik, sizeof(data.nik), stdin);
            printf("Fakultas\t: ");
            fgets(data.fakultas, sizeof(data.fakultas), stdin);
            printf("Jurusan\t\t: ");
            fgets(data.jurusan, sizeof(data.jurusan), stdin);
            printf("Email\t\t: ");
            fgets(data.email, sizeof(data.email), stdin);
            printf("IPK\t\t: ");
            scanf("%lf", &data.ipk);
            fflush(stdin);
            Create(&head, data);
            system("cls");
            break;
        }
        case '2': {
            printf("1. Ascending\n");
            printf("2. Descending\n");
            scanf("%c", &op);
            fflush(stdin);
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
            char nik[20];
            printf("Masukkan NIK mahasiswa yang ingin dihapus: ");
            fgets(nik, 20, stdin);
            nik[strcspn(nik, "\n")] = 0; // menghapus karakter newline dari nik
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
            printf("Exiting...\n");
            system("pause");
            return 0;
        default:
            printf("Error user input.\n");
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

    printf("Loading...\n");

    for (int i = 0; i < 25; i++) {
        printf("%c", bar1);
    }
    printf("\r");
    for (int i = 0; i < 25; i++) {
        printf("%c", bar2);
        Sleep(150);
    }
    printf("\n");
    system("Pause");
    system("cls");
}

void login() {
    animate();
    char username[50], password[50], ch;
    bool isLogin = false;
    do {
        printf("+===========================================+\n");
        printf("|                  LOGIN                    |\n");
        printf("+===========================================+\n");
        printf("Username\t: ");
        fgets(username, 50, stdin);
        strtok(username, "\n"); // menghapus karakter newline dari username
        printf("Password\t: ");
        ch = _getch();
        int i = 0;
        while (ch != 13) { // 13 adalah ASCII code untuk tombol "Enter"
            password[i] = ch;
            i++;
            printf("*");
            ch = _getch();
        }
        password[i] = '\0';
        printf("\n");
        if ((strcmp(username, "admin") == 0) && ((strcmp(password, "ganteng") == 0) || (strcmp(password, "cantik") == 0))) {
            isLogin = true;
        } else {
            printf("Username atau password salah. Silahkan coba lagi.\n");
            system("Pause");
            system("cls");
        }
    } while (!isLogin);
    animate();
}

/** CREATE **/
void Create(struct Node **head_ref, struct Mahasiswa data) {
    // Buat node baru
    struct Node *new_node = (struct Node*) malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->next = NULL;

    // Jika linked list masih kosong
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }

    // Cari node terakhir
    struct Node *last_node = *head_ref;
    while (last_node->next != NULL) {
        last_node = last_node->next;
    }

    // Tambahkan node baru di akhir
    last_node->next = new_node;

    // Simpan data ke file
    FILE *file_out = fopen("mahasiswa.txt", "a");
    if (file_out != NULL) {
        fprintf(file_out, "%s\n", data.nama);
        fprintf(file_out, "%s\n", data.nik);
        fprintf(file_out, "%s\n", data.fakultas);
        fprintf(file_out, "%s\n", data.jurusan);
        fprintf(file_out, "%s\n", data.email);
        fprintf(file_out, "%f\n", data.ipk);
        fclose(file_out);
    }
}

/** READ **/
void Read(struct Node *head) {
    // Jika linked list masih kosong
    if (head == NULL) {
        printf("Data kosong\n");
        return;
    }

    // Tampilkan data
    struct Node *curr = head;
    while (curr != NULL) {
        printf("Nama: %s\n", curr->data.nama);
        printf("NIK: %s\n", curr->data.nik);
        printf("Fakultas: %s\n", curr->data.fakultas);
        printf("Jurusan: %s\n", curr->data.jurusan);
        printf("Email: %s\n", curr->data.email);
        printf("IPK: %f\n", curr->data.ipk);
        printf("\n");
        curr = curr->next;
    }
}

/** SORTING **/
void sorting(struct Node *head, bool ascending) {
    if (head == NULL) {
        return;
    }

    struct Node *i = head;
    while (i != NULL) {
        struct Node *j = i->next;
        while (j != NULL) {
            if ((ascending && strcmp(i->data.nik, j->data.nik) > 0) || (!ascending && strcmp(i->data.nik, j->data.nik) < 0)) {
                struct Mahasiswa temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
            j = j->next;
        }
        i = i->next;
    }
}

/** SEARCHING **/
void searching(struct Node *head) {
    // Jika linked list masih kosong
    if (head == NULL) {
        printf("Data kosong\n");
        return;
    }

    // Cari node dengan NIK tertentu
    char nik[16];
    printf("NIK yang dicari: ");
    fgets(nik, sizeof(nik), stdin);
    nik[strcspn(nik, "\n")] = 0; // hapus karakter newline dari input

    struct Node *curr = head;
    while (curr != NULL && strcmp(curr->data.nik, nik) != 0) {
        curr = curr->next;
        // Jika NIK tidak ditemukan
        if (curr == NULL) {
            printf("Data tidak ditemukan\n");
            return;
        }
    }
    // Tampilkan data sebelum diubah
    printf("Nama: %s\n", curr->data.nama);
    printf("NIK: %s\n", curr->data.nik);
    printf("Fakultas: %s\n", curr->data.fakultas);
    printf("Jurusan: %s\n", curr->data.jurusan);
    printf("Email: %s\n", curr->data.email);
    printf("IPK: %f\n", curr->data.ipk);
}

/** UPDATE **/
void Update(struct Node *head) {
    // Jika linked list masih kosong
    if (head == NULL) {
        printf("Data kosong\n");
        return;
    }

    // Cari node dengan NIK tertentu
    char nik[50];
    printf("Masukkan NIK mahasiswa yang ingin diubah: ");
    fgets(nik, 50, stdin);
    nik[strcspn(nik, "\n")] = '\0'; // Hapus karakter newline dari input
    struct Node *curr = head;
    while (curr != NULL && strcmp(curr->data.nik, nik) != 0) {
        curr = curr->next;
        // Jika NIK tidak ditemukan
        if (curr == NULL) {
            printf("Data tidak ditemukan\n");
            return;
        }
    }
    // Tampilkan data sebelum diubah
    printf("Data sebelum diubah: \n");
    printf("Nama: %s\n", curr->data.nama);
    printf("NIK: %s\n", curr->data.nik);
    printf("Fakultas: %s\n", curr->data.fakultas);
    printf("Jurusan: %s\n", curr->data.jurusan);
    printf("Email: %s\n", curr->data.email);
    printf("IPK: %.2f\n", curr->data.ipk);

    // Masukkan data baru
    struct Mahasiswa data;
    printf("Masukkan data baru: \n");
    printf("Nama: ");
    fgets(data.nama, 50, stdin);
    data.nama[strcspn(data.nama, "\n")] = '\0'; // Hapus karakter newline dari input
    printf("NIK: ");
    fgets(data.nik, 50, stdin);
    data.nik[strcspn(data.nik, "\n")] = '\0'; // Hapus karakter newline dari input
    printf("Fakultas: ");
    fgets(data.fakultas, 50, stdin);
    data.fakultas[strcspn(data.fakultas, "\n")] = '\0'; // Hapus karakter newline dari input
    printf("Jurusan: ");
    fgets(data.jurusan, 50, stdin);
    data.jurusan[strcspn(data.jurusan, "\n")] = '\0'; // Hapus karakter newline dari input
    printf("Email: ");
    fgets(data.email, 50, stdin);
    data.email[strcspn(data.email, "\n")] = '\0'; // Hapus karakter newline dari input
    printf("IPK: ");
    scanf("%f", &data.ipk);
    getchar(); // Hapus karakter newline dari input

    // Ubah data pada node yang dipilih
    curr->data = data;

    // Simpan data ke file
    FILE *fp;
    fp = fopen("mahasiswa.txt", "w");
    if (fp == NULL) {
        printf("Error: file tidak dapat dibuka.\n");
        exit(1);
    } else {
        struct Node *curr = head;
        while (curr != NULL) {
            fprintf(fp, "%s\n", curr->data.nama);
            fprintf(fp, "%s\n", curr->data.nik);
            fprintf(fp, "%s\n", curr->data.fakultas);
            fprintf(fp, "%s\n", curr->data.jurusan);
            fprintf(fp, "%s\n", curr->data.email);
            fprintf(fp, "%.2f\n", curr->data.ipk);
            curr = curr->next;
        }
        fclose(fp);
    }
}

/** DELETE **/
void Delete(struct Node **head_ref, char* nik) {
    // Jika linked list masih kosong
    if (*head_ref == NULL) {
        printf("Data kosong\n");
        return;
    }

    // Cari node dengan NIK tertentu
    struct Node *curr = *head_ref;
    struct Node *prev = NULL;
    while (curr != NULL && strcmp(curr->data.nik, nik) != 0) {
        prev = curr;
        curr = curr->next;
    }

    // Jika NIK tidak ditemukan
    if (curr == NULL) {
        printf("Data tidak ditemukan\n");
        return;
    }

    // Hapus node yang dipilih
    if (prev == NULL) {
        *head_ref = curr->next;
    } else {
        prev->next = curr->next;
    }
    free(curr);

    printf("Data berhasil dihapus\n");
    // Simpan data ke file
    FILE *file_out = fopen("mahasiswa.txt", "w");
    if (file_out != NULL) {
        struct Node *curr = *head_ref;
        while (curr != NULL) {
            fprintf(file_out, "%s\n", curr->data.nama);
            fprintf(file_out, "%s\n", curr->data.nik);
            fprintf(file_out, "%s\n", curr->data.fakultas);
            fprintf(file_out, "%s\n", curr->data.jurusan);
            fprintf(file_out, "%s\n", curr->data.email);
            fprintf(file_out, "%.2f\n", curr->data.ipk);
            curr = curr->next;
        }
        fclose(file_out);
    }
}
