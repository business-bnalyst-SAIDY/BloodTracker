#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct user {
    char username[50];
    char password[50];
};

struct donor {
    int id;
    char name[50];
    char blood_group[4];
    char contact[15];
    char address[100];
};

struct ambulance {
    int id;
    char driver_name[50];
    char contact[15];
    char status[10];
};

struct blood_request {
    int id;
    char requester_name[50];
    char blood_group[4];
    int quantity;
    char hospital_name[100];
    char status[10];
};

struct hospital {
    char name[100];
    char blood_group[4];
    int quantity;
    float price_per_bag;
};


void register_user();
int login();
void add_donor();
void view_donor_list();
void search_blood_group();
void delete_donor();
void manage_ambulance();
void view_ambulance_list();
void add_blood_request();
void view_blood_requests();
void update_request_status();
void manage_hospital_inventory();
void view_hospital_inventory();
void menu();
void main_menu();


int check_credentials(const char *username, const char *password);

void register_user() {
    FILE *file = fopen("users.dat", "a+");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    struct user new_user;
    printf("\n--- Register ---\n");
    printf("Enter Username: ");
    scanf("%s", new_user.username);
    printf("Enter Password: ");
    scanf("%s", new_user.password);

    fwrite(&new_user, sizeof(struct user), 1, file);
    fclose(file);

    printf("User registered successfully!\n");
}

int login() {
    char username[50], password[50];
    printf("\n--- Login ---\n");
    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    return check_credentials(username, password);
}

int check_credentials(const char *username, const char *password) {
    FILE *file = fopen("users.dat", "r");
    if (!file) {
        printf("Error opening file!\n");
        return 0;
    }

    struct user u;
    while (fread(&u, sizeof(struct user), 1, file)) {
        if (strcmp(u.username, username) == 0 && strcmp(u.password, password) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void add_donor() {
    FILE *file = fopen("donors.dat", "a+");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    struct donor new_donor;
    printf("\n--- Add New Donor ---\n");
    printf("Enter Donor ID: ");
    scanf("%d", &new_donor.id);
    printf("Name: ");
    scanf(" %[^\n]", new_donor.name);
    printf("Blood Group (e.g. O+, O-, A+, A-): ");
    scanf("%s", new_donor.blood_group);
    printf("Contact: ");
    scanf("%s", new_donor.contact);
    printf("Address: ");
    scanf(" %[^\n]", new_donor.address);

    fwrite(&new_donor, sizeof(struct donor), 1, file);
    fclose(file);

    printf("Donor added successfully!\n");
}

void view_donor_list() {
    FILE *file = fopen("donors.dat", "r");
    if (!file) {
        printf("No records found!\n");
        return;
    }

    struct donor d;
    printf("\n--- Donor List ---\n");
    printf("ID\tName\tBlood Group\tContact\t\tAddress\n");
    while (fread(&d, sizeof(struct donor), 1, file)) {
        printf("%d\t%s\t%s\t\t%s\t%s\n", d.id, d.name, d.blood_group, d.contact, d.address);
    }
    fclose(file);
}

void search_blood_group() {
    FILE *file = fopen("donors.dat", "r");
    if (!file) {
        printf("No records found!\n");
        return;
    }

    char blood_group[4];
    printf("Enter Blood Group to Search (e.g. O+, O-, A+, A-): ");
    scanf("%s", blood_group);

    struct donor d;
    int found = 0;
    printf("\n--- Search Results ---\n");
    printf("ID\tName\tBlood Group\tContact\t\tAddress\n");
    while (fread(&d, sizeof(struct donor), 1, file)) {
        if (strcmp(d.blood_group, blood_group) == 0) {
            printf("%d\t%s\t%s\t\t%s\t%s\n", d.id, d.name, d.blood_group, d.contact, d.address);
            found = 1;
        }
    }
    fclose(file);

    if (!found) {
        printf("No donors found with blood group %s!\n", blood_group);
    }
}

void delete_donor() {
    FILE *file = fopen("donors.dat", "r");
    FILE *temp = fopen("temp.dat", "w");
    if (!file || !temp) {
        printf("Error opening file!\n");
        return;
    }

    int id, found = 0;
    struct donor d;
    printf("Enter Donor ID to Delete: ");
    scanf("%d", &id);

    while (fread(&d, sizeof(struct donor), 1, file)) {
        if (d.id != id) {
            fwrite(&d, sizeof(struct donor), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(temp);

    remove("donors.dat");
    rename("temp.dat", "donors.dat");

    if (found) {
        printf("Donor deleted successfully!\n");
    } else {
        printf("Donor not found!\n");
    }
}

void manage_ambulance() {
    FILE *file = fopen("ambulances.dat", "a+");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    struct ambulance new_ambulance;
    printf("\n--- Add New Ambulance ---\n");
    printf("Enter Ambulance ID: ");
    scanf("%d", &new_ambulance.id);
    printf("Driver Name: ");
    scanf(" %[^\n]", new_ambulance.driver_name);
    printf("Contact: ");
    scanf("%s", new_ambulance.contact);
    strcpy(new_ambulance.status, "Available");

    fwrite(&new_ambulance, sizeof(struct ambulance), 1, file);
    fclose(file);

    printf("Ambulance added successfully!\n");
}

void view_ambulance_list() {
    FILE *file = fopen("ambulances.dat", "r");
    if (!file) {
        printf("No records found!\n");
        return;
    }

    struct ambulance a;
    printf("\n--- Ambulance List ---\n");
    printf("ID\tDriver Name\tContact\t\tStatus\n");
    while (fread(&a, sizeof(struct ambulance), 1, file)) {
        printf("%d\t%s\t%s\t\t%s\n", a.id, a.driver_name, a.contact, a.status);
    }
    fclose(file);
}

void add_blood_request() {
    FILE *file = fopen("blood_requests.dat", "a+");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    struct blood_request new_request;
    printf("\n--- Add New Blood Request ---\n");
    printf("Enter Request ID: ");
    scanf("%d", &new_request.id);

    printf("Requester Name: ");
    scanf(" %[^\n]", new_request.requester_name);
    printf("Blood Group (e.g. O+, O-, A+, A-): ");
    scanf("%s", new_request.blood_group);

    while (strcmp(new_request.blood_group, "O+") != 0 && strcmp(new_request.blood_group, "O-") != 0 &&
           strcmp(new_request.blood_group, "A+") != 0 && strcmp(new_request.blood_group, "A-") != 0 &&
           strcmp(new_request.blood_group, "B+") != 0 && strcmp(new_request.blood_group, "B-") != 0 &&
           strcmp(new_request.blood_group, "AB+") != 0 && strcmp(new_request.blood_group, "AB-") != 0) {
        printf("Invalid Blood Group! Please enter a valid one (O+, O-, A+, A-, B+, B-, AB+, AB-): ");
        scanf("%s", new_request.blood_group);
    }

    printf("Quantity (in units): ");
    scanf("%d", &new_request.quantity);
    printf("Hospital Name: ");
    scanf(" %[^\n]", new_request.hospital_name);
    strcpy(new_request.status, "Pending");

    fwrite(&new_request, sizeof(struct blood_request), 1, file);
    fclose(file);

    printf("Blood request added successfully!\n");
}

void view_blood_requests() {
    FILE *file = fopen("blood_requests.dat", "r");
    if (!file) {
        printf("No records found!\n");
        return;
    }

    struct blood_request br;
    printf("\n--- Blood Requests ---\n");
    printf("ID\tRequester Name\tBlood Group\tQuantity\tHospital\tStatus\n");
    while (fread(&br, sizeof(struct blood_request), 1, file)) {
        printf("%d\t%s\t%s\t\t%d\t\t%s\t%s\n", br.id, br.requester_name, br.blood_group, br.quantity, br.hospital_name, br.status);
    }
    fclose(file);
}

void update_request_status() {
    FILE *file = fopen("blood_requests.dat", "r");
    FILE *temp = fopen("temp_requests.dat", "w");
    if (!file || !temp) {
        printf("Error opening file!\n");
        return;
    }

    int id, found = 0;
    struct blood_request br;
    printf("Enter Request ID to Update Status: ");
    scanf("%d", &id);

    while (fread(&br, sizeof(struct blood_request), 1, file)) {
        if (br.id == id) {
            printf("Enter New Status (Approved/Rejected/Pending): ");
            scanf("%s", br.status);
            found = 1;
        }
        fwrite(&br, sizeof(struct blood_request), 1, temp);
    }

    fclose(file);
    fclose(temp);

    remove("blood_requests.dat");
    rename("temp_requests.dat", "blood_requests.dat");

    if (found) {
        printf("Blood request status updated successfully!\n");
    } else {
        printf("Request ID not found!\n");
    }
}

void manage_hospital_inventory() {
    FILE *file = fopen("hospital_inventory.dat", "a+");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    struct hospital new_hospital;
    printf("\n--- Manage Hospital Inventory ---\n");
    printf("Enter Hospital Name: ");
    scanf(" %[^\n]", new_hospital.name);
    printf("Blood Group (e.g. O+, O-, A+, A-): ");
    scanf("%s", new_hospital.blood_group);

    while (strcmp(new_hospital.blood_group, "O+") != 0 && strcmp(new_hospital.blood_group, "O-") != 0 &&
           strcmp(new_hospital.blood_group, "A+") != 0 && strcmp(new_hospital.blood_group, "A-") != 0 &&
           strcmp(new_hospital.blood_group, "B+") != 0 && strcmp(new_hospital.blood_group, "B-") != 0 &&
           strcmp(new_hospital.blood_group, "AB+") != 0 && strcmp(new_hospital.blood_group, "AB-") != 0) {
        printf("Invalid Blood Group! Please enter a valid one (O+, O-, A+, A-, B+, B-, AB+, AB-): ");
        scanf("%s", new_hospital.blood_group);
    }

    printf("Quantity (in bags): ");
    scanf("%d", &new_hospital.quantity);
    printf("Price per Bag: ");
    scanf("%f", &new_hospital.price_per_bag);

    fwrite(&new_hospital, sizeof(struct hospital), 1, file);
    fclose(file);

    printf("Hospital inventory managed successfully!\n");
}

void view_hospital_inventory() {
    FILE *file = fopen("hospital_inventory.dat", "r");
    if (!file) {
        printf("No records found!\n");
        return;
    }

    struct hospital h;
    printf("\n--- Hospital Inventory ---\n");
    printf("Hospital Name\tBlood Group\tQuantity\tPrice per Bag\n");
    while (fread(&h, sizeof(struct hospital), 1, file)) {
        printf("%s\t%s\t\t%d\t\t%.2f\n", h.name, h.blood_group, h.quantity, h.price_per_bag);
    }
    fclose(file);
}

void menu() {
    int choice;
    while (1) {
        printf("\n--- Blood Bank Management System ---\n");
        printf("1. Add Donor\n");
        printf("2. View Donor List\n");
        printf("3. Search Blood Group\n");
        printf("4. Delete Donor\n");
        printf("5. Manage Ambulance\n");
        printf("6. View Ambulance List\n");
        printf("7. Add Blood Request\n");
        printf("8. View Blood Requests\n");
        printf("9. Update Request Status\n");
        printf("10. Manage Hospital Inventory\n");
        printf("11. View Hospital Inventory\n");
        printf("12. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_donor();
                break;
            case 2:
                view_donor_list();
                break;
            case 3:
                search_blood_group();
                break;
            case 4:
                delete_donor();
                break;
            case 5:
                manage_ambulance();
                break;
            case 6:
                view_ambulance_list();
                break;
            case 7:
                add_blood_request();
                break;
            case 8:
                view_blood_requests();
                break;
            case 9:
                update_request_status();
                break;
            case 10:
                manage_hospital_inventory();
                break;
            case 11:
                view_hospital_inventory();
                break;
            case 12:
                exit(0);
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

void main_menu() {
    int choice;
    while (1) {
        printf("\n--- Main Menu ---\n");
        printf("1. Login\n");
        printf("2. Register\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (login()) {
                    menu();
                } else {
                    printf("Invalid credentials! Please try again.\n");
                }
                break;
            case 2:
                register_user();
                break;
            case 3:
                exit(0);
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

int main() {
    main_menu();
    return 0;
}
