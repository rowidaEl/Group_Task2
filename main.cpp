#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

// ========== ENUMERATIONS ========== //
enum Department
{
    CARDIOLOGY,
    NEUROLOGY,
    ORTHOPEDICS,
    PEDIATRICS,
    EMERGENCY,
    GENERAL
};

enum RoomType
{
    GENERAL_WARD,
    ICU,
    PRIVATE_ROOM,
    SEMI_PRIVATE
};

// ========== PATIENT CLASS ========== //
class Patient
{
private:
    int id;
    string name;
    int age;
    string contact;
    stack<string> medicalHistory;
    queue<string> testQueue;
    bool isAdmitted;
    RoomType roomType;

public:
    Patient(int pid, string n, int a, string c){
    id = pid;
    name = n;
    age = a;
    contact = c;
    isAdmitted = false;
    }


    void admitPatient(RoomType type)
    {


        if(isAdmitted)
        {
            cout << "Patient " << name << " is already admitted" << endl ;
            return;
        }
        isAdmitted = true;
        roomType = type;
         string patientRoom;
        switch(roomType)
        {
            case GENERAL_WARD : patientRoom = "General Ward"; break;
            case ICU : patientRoom = "ICU"; break;
            case PRIVATE_ROOM : patientRoom = "Private Room"; break;
            case SEMI_PRIVATE : patientRoom = "Semi-Private Room";break;
        }
        cout << "Patient " << name << " is admitted to " << patientRoom << endl;
    }


    void dischargePatient()
    {
        if(!isAdmitted)
        {
            cout << "Patient " << name << " is not currently admitted" << endl;
            return;
        }
        isAdmitted = false ;
        cout << "Patient " << name << " has been discharged" << endl;

    }

    void addMedicalRecord(string record)
    {
        medicalHistory.push(record);
        cout << "Medical Record added for " << name << ": " << record << endl;
    }

    void requestTest(string testName)
    {
        testQueue.push(testName);
        cout << "Test requested for " << name << ": " << testName << endl;

    }

    void admitPatient(RoomType type);
    void dischargePatient();
    void addMedicalRecord(string record);
    void requestTest(string testName);
    string performTest()
    {
        if(testQueue.empty())
        {
            cout<<"No pending tests for "<<name;
            return "";
        }
        string test=testQueue.front();
        testQueue.pop();
        cout<<"Performing test for "<<name<<":"<<test;
        return test;


    }
    void displayHistory()
    {
        stack<string> m=medicalHistory;
        if(!m.empty())
        {
            cout<<"Medical History for "<<name<<":"<<endl;
        }
        else
        {
            cout<<"No medical history";
            return;
        }
        while(!m.empty())
        {
            string history=m.top();
            cout<<history<<" -[record]"<<endl;
            m.pop();
        }



    }


    int getId()
    {
        return id;
    }


    string getName()
    {
        return name;
    }
    bool getAdmissionStatus()
    {
        return isAdmitted;
    }
};

// ========== DOCTOR CLASS ========== //
class Doctor
{
private:
    int id;
    string name;
    Department department;
    queue<int> appointmentQueue;

public:
    Doctor(int did, string n, Department d)
    {
        id=did;
        name=n;
        department=d;
    }

    void addAppointment(int patientId) {
    appointmentQueue.push(patientId);
    cout << "Appointment added for patient ID: " << patientId << endl;
}
    int seePatient(){
    if (appointmentQueue.empty()) {
        cout << "No patients in appointment queue." << endl;
        return -1; // indicates no patient
    }

    int nextPatient = appointmentQueue.front();
    appointmentQueue.pop();

    cout << "Doctor is seeing patient ID: " << nextPatient << endl;
    return nextPatient;
}

    int getId()
    {
        return id;

    }
    string getName()
    {
        return name;

    }
    string getDepartment()
    {
        switch(department)
        {
        case CARDIOLOGY:
            return "Cardiology";
        case NEUROLOGY:
            return "Neurology";
        case ORTHOPEDICS:
            return "Orthopedics";
        case  PEDIATRICS:
            return "Pediatrics";
        case  EMERGENCY:
            return "Emergency";
        case GENERAL:
            return "General";
        default:
            return "Unknown";





        }

    }
};

// ========== HOSPITAL CLASS ========== //
class Hospital
{
private:
    vector<Patient> patients;
    vector<Doctor> doctors;
    queue<int> emergencyQueue;
    int patientCounter;
    int doctorCounter;

public:
    Hospital(){
    patientCounter = 0;
    doctorCounter = 0;
}

    int registerPatient(string name, int age, string contact);
    int addDoctor(string name, Department dept) {
    doctorCounter++;  // generate new ID

    doctors.emplace_back(doctorCounter, name, dept);

    cout << "Doctor added successfully. ID: " << doctorCounter << endl;

    return doctorCounter;
}
    void admitPatient(int patientId, RoomType type);
    void addEmergency(int patientId);
    int handleEmergency();
    void bookAppointment(int doctorId, int patientId);
    void displayPatientInfo(int patientId);
    void displayDoctorInfo(int doctorId);
};

// ========== MAIN PROGRAM ========== //
int main()
{
    Hospital hospital;

    // Test Case 1: Registering patients
    int p1 = hospital.registerPatient("John Doe", 35, "555-1234");
    int p2 = hospital.registerPatient("Jane Smith", 28, "555-5678");
    int p3 = hospital.registerPatient("Mike Johnson", 45, "555-9012");

    // Test Case 2: Adding doctors
    int d1 = hospital.addDoctor("Dr. Smith", CARDIOLOGY);
    int d2 = hospital.addDoctor("Dr. Brown", NEUROLOGY);
    int d3 = hospital.addDoctor("Dr. Lee", PEDIATRICS);

    // Test Case 3: Admitting patients
    hospital.admitPatient(p1, PRIVATE_ROOM);
    hospital.admitPatient(p2, ICU);
    // Try admitting already admitted patient
    hospital.admitPatient(p1, SEMI_PRIVATE);

    // Test Case 4: Booking appointments
    hospital.bookAppointment(d1, p1);
    hospital.bookAppointment(d1, p2);
    hospital.bookAppointment(d2, p3);
    // Try booking with invalid doctor/patient
    hospital.bookAppointment(999, p1); // Invalid doctor
    hospital.bookAppointment(d1, 999); // Invalid patient

    // Test Case 5: Handling medical tests
    // These would normally be called on Patient objects
    // In a real implementation, we'd need a way to access patients

    // Test Case 6: Emergency cases
    hospital.addEmergency(p3);
    hospital.addEmergency(p1);
    int emergencyPatient = hospital.handleEmergency();
    emergencyPatient = hospital.handleEmergency();
    emergencyPatient = hospital.handleEmergency(); // No more emergencies

    // Test Case 7: Discharging patients
    // Would normally call dischargePatient() on Patient objects

    // Test Case 8: Displaying information
    hospital.displayPatientInfo(p1);
    hospital.displayPatientInfo(p2);
    hospital.displayPatientInfo(999); // Invalid patient

    hospital.displayDoctorInfo(d1);
    hospital.displayDoctorInfo(d2);
    hospital.displayDoctorInfo(999); // Invalid doctor

    // Test Case 9: Doctor seeing patients
    // These would normally be called on Doctor objects
    // In a real implementation, we'd need a way to access doctors

    // Test Case 10: Edge cases
    Hospital emptyHospital;
    emptyHospital.displayPatientInfo(1); // No patients
    emptyHospital.displayDoctorInfo(1);  // No doctors
    emptyHospital.handleEmergency();     // No emergencies

    return 0;
}
