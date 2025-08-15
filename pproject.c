#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char id[10];
    char Name[30];
    char specialization[30];
} Doctor;

Doctor Doctor_S[100];
int Doctor_Count = 0;


typedef struct Patients {
    char id[15];
    char Name[40];
    int Age;
    struct Patients* Next;
} Patients;

Patients* Patients_Head = NULL;


typedef struct {
    char Patients_ID[15];
    char Doctor_ID[15];
} Appointment;

Appointment Appointment_Queue[100];
int front = -1, rear=-1;

struct stack {
    Appointment STR[5];
    int top;
};
typedef struct stack STACK;
STACK s;

void Add_Doctor() {
    if (Doctor_Count == 100) {
        printf("Doctor list is full!\n");
        return;
    }
    printf("Enter Doctor ID: ");
    scanf("%s", Doctor_S[Doctor_Count].id);
    printf("Enter Doctor Name: ");
    getchar();
    fgets(Doctor_S[Doctor_Count].Name, 30, stdin);
    Doctor_S[Doctor_Count].Name[strcspn(Doctor_S[Doctor_Count].Name, "\n")] = 0;
    printf("Enter Specialization: ");
    fgets(Doctor_S[Doctor_Count].specialization, 30, stdin);
    Doctor_S[Doctor_Count].specialization[strcspn(Doctor_S[Doctor_Count].specialization, "\n")] = 0;
    Doctor_Count++;
    printf("Doctor added.\n");
}

void displayDoctor_S() {
    if (Doctor_Count == 0) {
        printf("No Doctor\n");
        return;
    }
    printf("Doctor:\nID---Name---Specialization\n");
    for (int i = 0; i < Doctor_Count; i++) {
        printf("%s---%s---%s\n", Doctor_S[i].id, Doctor_S[i].Name, Doctor_S[i].specialization);
    }
}

int Find_Doctor(char* id) {
    for (int i = 0; i < Doctor_Count; i++) {
        if (strcmp(Doctor_S[i].id, id) == 0) {
        return i;
        }
    }
    return -1;
}

void addPatients() {
    Patients* New_Patients = (Patients*)malloc(sizeof(Patients));
    printf("type Patients ID: ");
    scanf("%s", New_Patients->id);
    printf("type the Patients Name: ");
    getchar();
    fgets(New_Patients->Name, 30, stdin);
    New_Patients->Name[strcspn(New_Patients->Name, "\n")] = 0;
    printf("Enter patient Age: ");
    scanf("%d", &New_Patients->Age);
    New_Patients->Next = NULL;

    if (Patients_Head == NULL) {
        Patients_Head = New_Patients;
    } else {
        Patients* Temp = Patients_Head;
        while (Temp->Next != NULL)
            Temp = Temp->Next;
        Temp->Next = New_Patients;
    }
    printf("Patients added.\n");
}

void displayPatientss() {
    if (Patients_Head == NULL) {
        printf("No Patients to show\n");
        return;
    }
    printf("Patients\nID---Name---Age\n");
    Patients* Temp = Patients_Head;
    while (Temp != NULL) {
        printf("%s---%s---%d\n", Temp->id, Temp->Name, Temp->Age);
        Temp = Temp->Next;
    }
}

Patients* Find_Patients(char* id) {
    Patients* Temp = Patients_Head;
    while (Temp != NULL) {
        if (strcmp(Temp->id, id) == 0)
        return Temp;
        Temp = Temp->Next;
    }
    return NULL;
}

int is_Queue_Empty() {
    return front == -1;
}

int is_Queue_Full() {
    return (rear + 1) % 100 == front;
}

void enqueue(Appointment remove_Appointment) {
    if (is_Queue_Full()) {
        printf("sorry, Appointment queue is full.\n");
        return;
    }
    if (is_Queue_Empty()) {
    front = rear = 0;
    }
    else {
    rear = (rear + 1) % 100;
    Appointment_Queue[rear] = remove_Appointment;
    printf("congratulation! ,Appointment booked.\n");
    }
}

Appointment dequeue() {
    Appointment remove_Appointment = {"", ""};
    if (is_Queue_Empty()) {
        printf("sorry, No appointments.\n");
        return remove_Appointment ;
    }
    remove_Appointment = Appointment_Queue[front];
    if (front == rear) front = rear = -1;
    else front = (front + 1) % 100;
    return remove_Appointment;
}

void Display_Appointments() {
    if (is_Queue_Empty()) {
        printf("sorry, No appointments.\n");
        return;
    }
    printf("Appointments:\nPatients_ID---Doctor_ID\n");
    int i = front;
    while (1) {
        printf("%s------%s\n", Appointment_Queue[i].Patients_ID, Appointment_Queue[i].Doctor_ID);
        if (i == rear) break;
        i = (i + 1) % 100;
    }
}

void resetStack() {
    s.top = -1;
}

int isFull() {
    return s.top == 5 - 1;
}

int isEmpty() {
    return s.top == -1;
}

void push() {
    Appointment cancelled_Appointment;
    if (isFull()) {
        printf("Cancel stack is full.\n");
        return;
    }
    printf("Enter Patients ID to push (cancelled): ");
    scanf("%s", cancelled_Appointment.Patients_ID);
    printf("Enter Doctor ID to push (cancelled): ");
    scanf("%s", cancelled_Appointment.Doctor_ID);
    s.top = s.top + 1;
    s.STR[s.top] = cancelled_Appointment;
    printf("Cancelled appointment saved to stack.\n");
}

Appointment pop() {
    Appointment empty = {"", ""};
    if (isEmpty()) {
        printf("Cancel stack is empty.\n");
        return empty;
    }
    Appointment cancelled_Appointment = s.STR[s.top];
    printf("Popped cancelled appointment: Patients_ID = %s, Doctor_ID = %s\n", cancelled_Appointment.Patients_ID, cancelled_Appointment.Doctor_ID);
    s.top = s.top - 1;
    return cancelled_Appointment;
}

void displayStack() {
    if (isEmpty()) {
        printf("Cancel stack empty.\n");
        return;
    }
    printf("Cancelled appointments stack:\n");
    for (int i = s.top; i >= 0; i--) {
        printf("Patients_ID: %s, Doctor_ID: %s\n", s.STR[i].Patients_ID, s.STR[i].Doctor_ID);
    }
}

void undo_Last_Cancelled() {
    if (isEmpty()) {
        printf("sorry,No cancelled appointments to undo.\n");
        return;
    }
    Appointment cancelled_Appointment = pop();
    enqueue(cancelled_Appointment);
    printf("congratulations, Last cancelled appointment restored.\n");
}

void Patients_Linked_List() {
    struct Node {
        char id[10];
        char Name[30];
        int Age;
        struct Node* Next;
    };

    struct Node* head = NULL;
    struct Node* second = NULL;
    struct Node* third = NULL;

    head = (struct Node*)malloc(sizeof(struct Node));
    second = (struct Node*)malloc(sizeof(struct Node));
    third = (struct Node*)malloc(sizeof(struct Node));

    strcpy(head->id, "Patient-0001");
    strcpy(head->Name, "Rana");
    head->Age = 40;
    head->Next = second;

    strcpy(second->id, "Patient-0002");
    strcpy(second->Name, "Hasan");
    second->Age = 25;
    second->Next = third;

    strcpy(third->id, "Patient-0003");
    strcpy(third->Name, "Rohim");
    third->Age = 35;
    third->Next = NULL;

    struct Node* temp = head;
    int count = 1;
    while (temp != NULL) {
        printf("Node %d: ID = %s, Name = %s, Age = %d\n",
               count, temp->id, temp->Name, temp->Age);
        temp = temp->Next;
        count++;
    }

    free(head);
    free(second);
    free(third);
}

void adminMenu() {
    int choice;
    do {
        printf("\n Admin Menu:\n1. Add Doctor\n2. Display Doctor_S\n3. Back\nChoice: ");
        scanf("%d", &choice);

        if (choice == 1) Add_Doctor();
        else if (choice == 2) displayDoctor_S();
    } while (choice != 3);
}

void Patients_Menu() {
    int choice;
    do {
        printf("\nPatients Menu:"
               "\n1. Add Patients"
               "\n2. Display Patients"
               "\n3. patients List"
               "\n4. Back"
               "\nChoice:"
               );

        scanf("%d", &choice);
        if (choice == 1) addPatients();
        else if (choice == 2) displayPatientss();
        else if (choice == 3) Patients_Linked_List();
    } while (choice != 4);
}

void Appointment_Menu() {
    int choice;
    do {
        printf("\nAppointment Menu:"
               "\n1. Book Appointment"
               "\n2. Cancel Appointment"
               "\n3. View Appointments"
               "\n4. Undo Cancel"
               "\n5. Display Cancel Stack"
               "\n6. Back\nChoice: "
               );
        scanf("%d", &choice);
        if (choice == 1) {
            Appointment a;
            printf("Enter Patients ID: ");
            scanf("%s", a.Patients_ID);
            if (Find_Patients(a.Patients_ID) == NULL) {
                printf("Patients not found! Add Patients first.\n");
                continue;
            }
            printf("Enter Doctor ID: ");
            scanf("%s", a.Doctor_ID);
            if (Find_Doctor(a.Doctor_ID) == -1) {
                printf("Doctor not found! Check doctor ID.\n");
                continue;
            }
            enqueue(a);
        } else if (choice == 2) {
            if (is_Queue_Empty()) {
                printf("No appointments to cancel.\n");
            } else {
                Appointment c = dequeue();
                if (isFull()) {
                    printf("sorry, Cancel stack full\n");
                } else {
                    s.top++;
                    s.STR[s.top] = c;
                    printf("Appointment cancelled: Patients_ID=%s, Doctor_ID=%s\n", c.Patients_ID, c.Doctor_ID);
                }
            }
        } else if (choice == 3) {
            Display_Appointments();
        } else if (choice == 4) {
        undo_Last_Cancelled();
        } else if (choice == 5) {
            displayStack();
        }
    } while (choice != 6);
}

int main() {
    int choice;
    resetStack();
    printf("=== Clinic Appointment Scheduling System ===\n");
    do {
        printf("\nMain Menu:"
               "\n1. Admin"
               "\n2. Patientss"
               "\n3. Appointments"
               "\n4. Exit"
               "\nChoice: "
               );
        scanf("%d", &choice);
        if (choice == 1) {adminMenu();}
        else if (choice == 2){Patients_Menu();}
        else if (choice == 3){ Appointment_Menu();}
    } while (choice != 4);
    printf("Thank you!\n");
    return 0;
}
