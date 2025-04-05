# Clinic Management System 🏥 (C Language)

A C-based console application created with care to simulate a simplified clinic’s patient and appointment management system.
Built during my programming fundamentals course using structured design principles, modular header/source files and user-driven interaction.

## 🧠 Key Features

- Add, edit and remove patient records  
- Book appointments within working hours (10 AM – 2 PM, 30-min slots)  
- Display all appointments or filter by date  
- Import/export from `txt` files  
- Full console UI with structured navigation

## 🛠️ Tech Stack

- C (Structured Programming)
- Header files for modularity
- Standard I/O and `stdio.h`
- File I/O and static memory allocation

## 📸 Screenshots

![Clinic System Screenshot](./media/Screenshot_Clinic.png)

## 🗃️ Files Included

- `core.c` / `core.h`: Utility and input validation functions  
- `clinic.c` / `clinic.h`: Logic for patient and appointment management  
- `a1ms3.c`: Entry point to launch the app  
- `patientData.txt` / `appointmentData.txt`: Sample patient & appointment data  
- `media/`: Screenshots and sample output

## 📥 How To Run

```bash
gcc a1ms3.c clinic.c core.c -o clinicApp
./clinicApp

💡 Created with care and caffeine ☕ by Kemono
