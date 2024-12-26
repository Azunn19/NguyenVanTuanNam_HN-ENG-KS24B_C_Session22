#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STUDENTS 100
#define FILENAME "students.dat"
struct Student {
    int id;
    char name[50];
    int age;
};
int readFromFile(struct Student students[]) {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        return 0;
    }

    int count = 0;
    while (fread(&students[count], sizeof(struct Student), 1, file)) {
        count++;
    }
    fclose(file);
    return count;
}
void saveToFile(struct Student students[], int size) {
    FILE *file = fopen(FILENAME, "wb");
    if (file == NULL) {
        printf("Khong the mo file de ghi.\n");
        return;
    }
    fwrite(students, sizeof(struct Student), size, file);
    fclose(file);
}
void printStudents(struct Student students[], int size) {
    if (size == 0) {
        printf("Danh sach sinh vien rong.\n");
    } else {
        printf("Danh sach sinh vien:\n");
        for (int i = 0; i < size; i++) {
            printf("ID: %d, Ten: %s, Tuoi: %d\n", students[i].id, students[i].name, students[i].age);
        }
    }
}
int addStudent(struct Student students[], int size) {
    if (size >= MAX_STUDENTS) {
        printf("Mang sinh vien da day. Khong the them sinh vien moi.\n");
        return size;
    }
    struct Student newStudent;
    printf("Nhap ID sinh vien: ");
    scanf("%d", &newStudent.id);
    getchar();
    printf("Nhap ten sinh vien: ");
    fgets(newStudent.name, sizeof(newStudent.name), stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = '\0';
    printf("Nhap tuoi sinh vien: ");
    scanf("%d", &newStudent.age);

    students[size] = newStudent;
    size++;
    saveToFile(students, size);
    printf("Sinh vien moi da duoc them.\n");

    return size;
}
int editStudent(struct Student students[], int size) {
    int id;
    printf("Nhap ID sinh vien can sua: ");
    scanf("%d", &id);
    for (int i = 0; i < size; i++) {
        if (students[i].id == id) {
            printf("Sinh vien tim thay: %s\n", students[i].name);
            getchar();
            printf("Nhap ten moi sinh vien: ");
            fgets(students[i].name, sizeof(students[i].name), stdin);
            students[i].name[strcspn(students[i].name, "\n")] = '\0';
            printf("Nhap tuoi moi sinh vien: ");
            scanf("%d", &students[i].age);
            saveToFile(students, size); 
            printf("Thong tin sinh vien da duoc sua.\n");
            return size;
        }
    }

    printf("Khong tim thay sinh vien voi ID %d.\n", id);
    return size;
}
int deleteStudent(struct Student students[], int size) {
    int id;
    printf("Nhap ID sinh vien can xoa: ");
    scanf("%d", &id);

    int found = -1;
    for (int i = 0; i < size; i++) {
        if (students[i].id == id) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        for (int i = found; i < size - 1; i++) {
            students[i] = students[i + 1];
        }
        size--;
        saveToFile(students, size);
        printf("Sinh vien voi ID %d da bi xoa.\n", id);
    } else {
        printf("Khong tim thay sinh vien voi ID %d.\n", id);
    }

    return size;
}
void searchStudent(struct Student students[], int size) {
    int id;
    printf("Nhap ID sinh vien can tim: ");
    scanf("%d", &id);

    for (int i = 0; i < size; i++) {
        if (students[i].id == id) {
            printf("Sinh vien tim thay: ID: %d, Ten: %s, Tuoi: %d\n",
                   students[i].id, students[i].name, students[i].age);
            return;
        }
    }

    printf("Khong tim thay sinh vien voi ID %d.\n", id);
}
void sortStudentsByName(struct Student students[], int size) {
    struct Student temp;
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (strcmp(students[i].name, students[j].name) > 0) {
                temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
    saveToFile(students, size);
    printf("Danh sach sinh vien da duoc sap xep theo ten.\n");
}

int main() {
    struct Student students[MAX_STUDENTS];
    int size = readFromFile(students);
    int choice;
    do {
        printf("\nMENU\n");
        printf("1. In danh sach sinh vien\n");
        printf("2. Them sinh vien\n");
        printf("3. Sua thong tin sinh vien\n");
        printf("4. Xoa sinh vien\n");
        printf("5. Tim kiem sinh vien\n");
        printf("6. Sap xep danh sach sinh vien\n");
        printf("7. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printStudents(students, size);
                break;
            case 2:
                size = addStudent(students, size);
                break;
            case 3:
                size = editStudent(students, size);
                break;
            case 4:
                size = deleteStudent(students, size);
                break;
            case 5:
                searchStudent(students, size);
                break;
            case 6:
                sortStudentsByName(students, size);
                break;
            case 7:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le\n");
        }
    } while (choice != 7);

    return 0;
}
