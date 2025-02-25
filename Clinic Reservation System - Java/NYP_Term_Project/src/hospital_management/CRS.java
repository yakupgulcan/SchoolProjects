package hospital_management;

import java.io.*;
import java.time.LocalDate;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Scanner;



public class CRS {
	
    private HashMap<Long, Patient> patients = new HashMap<>();
    private LinkedList<Rendezvous> rendezvous = new LinkedList<>();
    private HashMap<Integer, Hospital> hospitals = new HashMap<>();

    public synchronized boolean makeRendezvous(long patientID, int hospitalID, int sectionID, int diplomaId, LocalDate desiredDate) throws IDException {
        Patient patient = patients.get(patientID);
        if (patient == null) {
            throw new IDException("Patient not found.");
        }

        Hospital hospital = hospitals.get(hospitalID);
        if (hospital == null) {
            throw new IDException("Hospital not found.");
        }

        Section section = hospital.getSection(sectionID);
        if (section == null) {
            throw new IDException("Section not found in hospital.");
        }

        Doctor doctor = section.getDoctor(diplomaId);
        if (doctor == null) {
            throw new IDException("Doctor not found in section.");
        }

        Schedule schedule = doctor.getDr_schedule();
        boolean success = schedule.addRendezvous(patient, desiredDate);
        if (!success) {
            System.out.println("Rendezvous limit reached for the given date.");
            return false;
        }

        rendezvous.add(schedule.getLastRendezvous());
        return true;
    }

    public synchronized boolean addHospital(Hospital h) {
    	if(hospitals.containsKey(h.getId()))
    		throw new IDException("Hospital ID is used for another hospital");
    	
        hospitals.put(h.getId(), h);
        return true;
    }

    public synchronized void addPatient(Patient p) throws IDException {
    	if(patients.containsKey(p.getNational_id()))
    		throw new IDException("Patient ID is used for another patient.");
        patients.put(p.getNational_id(), p);
    }

    public synchronized void saveTablesToDisk(String fullPath) {
        try (ObjectOutputStream writer = new ObjectOutputStream(new FileOutputStream(fullPath))) {
            writer.writeObject(patients);
            writer.writeObject(hospitals);
            writer.writeObject(rendezvous);
            System.out.println("Data successfully saved to file: " + fullPath);
        } catch (IOException e) {
            System.out.println("An error occurred while saving data to file.");
            e.printStackTrace();
        }
    }

    @SuppressWarnings("unchecked")
    public synchronized void loadTablesFromDisk(String fullPath) {
        try (ObjectInputStream reader = new ObjectInputStream(new FileInputStream(fullPath))) {
            patients = (HashMap<Long, Patient>) reader.readObject();
            hospitals = (HashMap<Integer, Hospital>) reader.readObject();
            rendezvous = (LinkedList<Rendezvous>) reader.readObject();
            System.out.println("Data successfully loaded from file: " + fullPath);
        } catch (IOException | ClassNotFoundException e) {
            System.out.println("An error occurred while loading data from file.");
            e.printStackTrace();
        }
    }

    public LinkedList<Rendezvous> getRendezvousList() {
        return rendezvous;
    }

    public HashMap<Long, Patient> getPatients() {
        return patients;
    }

    public HashMap<Integer, Hospital> getHospitals() {
        return hospitals;
    }
    
    public void showOptions() {
        System.out.println("\nOptions:");
        System.out.println("1. Add a hospital");
        System.out.println("2. Add a patient");
        System.out.println("3. Add a section to a hospital");
        System.out.println("4. Add a doctor to a section");
        System.out.println("5. Make a rendezvous");
        System.out.println("6. Save data to disk");
        System.out.println("7. Load data from disk");
        System.out.println("8. Show current situation : ");
        System.out.println("9. Exit");
    }
    
    public void showCurrentSituation() {
    	System.out.println("\n-------- Current Situation --------");
    	for(Hospital hospital : hospitals.values()) {
    		System.out.print("-");
    		System.out.println("Hospital : " + hospital.getName() + " - ID : " + hospital.getId());
    		LinkedList<Section> hospital_sections = hospital.getSections();
    		for(Section section : hospital_sections) {
        		System.out.print("--");
    			System.out.println("Section : " + section.getName() + " - ID : " + section.getId());
    			LinkedList<Doctor> doctors = section.getDoctors();
    			for(Doctor doctor : doctors) {
    	    		System.out.print("---");
    				System.out.println(doctor);
    	    		System.out.print("----");
    				doctor.showSchedule();
    				System.out.println("----------------------");
    			}
    			System.out.println("----------------------");
    		}
    		System.out.println("----------------------");
    	}
    	System.out.println("----------------------");
    	System.out.println("Patients");
    	
    	for(Patient p : patients.values()) {
    		System.out.println(p);
    	}
    	
    }
    
    public void handleWithMultithreading() {
        Patient patient1 = new Patient("Esma Gulcan", 12345);
        Patient patient2 = new Patient("Beyza Gulcan", 67890);
        Hospital hospital = new Hospital(1, "HealthCenter");
        Section section = new Section(1, "Cardiology");
        Doctor doctor = new Doctor("Said Gunduz", 11111, 101, 5);
        
        try {
            hospital.addSection(section);
            section.addDoctor(doctor);
            addHospital(hospital);
            
            Thread addPatientsThread = new Thread(() -> {
                try {
                    System.out.println("Adding patients");
                    addPatient(patient1);
                    addPatient(patient2);
                    System.out.println("Patients added");
                } catch (IDException e) {
                    System.out.println("Error adding patients: " + e.getMessage());
                }
            });

            Thread makeRendezvousThread = new Thread(() -> {
                try {
                    System.out.println("Making rendezvous for patients");
                    makeRendezvous(12345, 1, 1, 101, LocalDate.now());
                    makeRendezvous(67890, 1, 1, 101, LocalDate.now().plusDays(1));
                    System.out.println("Rendezvous made");
                } catch (IDException e) {
                    System.out.println("Error making rendezvous: " + e.getMessage());
                }
            });

            Thread showSituationThread = new Thread(() -> {
                try {
                    Thread.sleep(1000);
                    System.out.println("\ncurrent situation");
                    showCurrentSituation();
                } catch (InterruptedException e) {
                    System.out.println("interrupted");
                }
            });

            System.out.println("Starting all threads");
            addPatientsThread.start();
            makeRendezvousThread.start();
            showSituationThread.start();

            try {
                addPatientsThread.join();
                makeRendezvousThread.join();
                showSituationThread.join();
                System.out.println("All threads completed!");
            } catch (InterruptedException e) {
                System.out.println("Thread joining interrupted: " + e.getMessage());
            }

        } catch (Exception e) {
            System.out.println("Error in handleWithMultithreading: " + e.getMessage());
        }
    }
    
    
    public static void launchCLI() {
        CRS crs = new CRS();
        Scanner scanner = new Scanner(System.in);

        System.out.println("Welcome to the Clinic Reservation System");
        boolean running = true;

        while (running) {
            crs.showOptions();
            System.out.print("Enter your choice: ");
            int choice = scanner.nextInt();
            scanner.nextLine();
            int hospitalID;
            long nationalID;

            switch (choice) {
                case 1: 
                	try {
                		System.out.print("Enter hospital ID: ");
                        hospitalID = scanner.nextInt();
                        scanner.nextLine();
                        System.out.print("Enter hospital name: ");
                        String hospitalName = scanner.nextLine();
                        crs.addHospital(new Hospital(hospitalID, hospitalName));
                        System.out.println("Hospital added successfully.");
                	}catch (IDException e) {
                		e.printStackTrace();
                		System.out.println("Hospital not added.");
                	}
                    break;

                case 2: 
                	try {
                		System.out.print("Enter patient name: ");
                        String patientName = scanner.nextLine();
                        System.out.print("Enter national ID: ");
                        nationalID = scanner.nextLong();
                        crs.addPatient(new Patient(patientName, nationalID));
                        System.out.println("Patient added successfully.");
                		
                	}catch(IDException e) {
                		e.printStackTrace();
                		System.out.println("Patient not added.");
                	}
                    
                    break;

                case 3:
                    System.out.print("Enter hospital ID: ");
                    hospitalID = scanner.nextInt();
                    scanner.nextLine();
                    System.out.print("Enter section ID: ");
                    int sectionID = scanner.nextInt();
                    scanner.nextLine();
                    System.out.print("Enter section name: ");
                    String sectionName = scanner.nextLine();

                    Hospital hospital = crs.getHospitals().get(hospitalID);
                    if (hospital != null) {
                        try {
                            hospital.addSection(new Section(sectionID, sectionName));
                            System.out.println("Section added successfully.");
                        } catch (DuplicateInfoException e) {
                            System.out.println("Error: " + e.getMessage());
                        }
                    } else {
                        System.out.println("Hospital not found.");
                    }
                    break;

                case 4:
                    System.out.print("Enter hospital ID: ");
                    hospitalID = scanner.nextInt();
                    System.out.print("Enter section ID: ");
                    sectionID = scanner.nextInt();
                    scanner.nextLine();
                    System.out.print("Enter doctor name: ");
                    String doctorName = scanner.nextLine();
                    System.out.print("Enter national ID: ");
                    nationalID = scanner.nextLong();
                    System.out.print("Enter diploma ID: ");
                    int diplomaID = scanner.nextInt();
                    System.out.print("Enter max patients per day: ");
                    int maxPatients = scanner.nextInt();

                    hospital = crs.getHospitals().get(hospitalID);
                    if (hospital != null) {
                        Section section = hospital.getSection(sectionID);
                        if (section != null) {
                            try {
                                section.addDoctor(new Doctor(doctorName, nationalID, diplomaID, maxPatients));
                                System.out.println("Doctor added successfully.");
                            } catch (DuplicateInfoException e) {
                                System.out.println("Error: " + e.getMessage());
                            }
                        } else {
                            System.out.println("Section not found.");
                        }
                    } else {
                        System.out.println("Hospital not found.");
                    }
                    break;

                case 5:
                    System.out.print("Enter patient national ID: ");
                    nationalID = scanner.nextLong();
                    System.out.print("Enter hospital ID: ");
                    hospitalID = scanner.nextInt();
                    System.out.print("Enter section ID: ");
                    sectionID = scanner.nextInt();
                    System.out.print("Enter doctor diploma ID: ");
                    diplomaID = scanner.nextInt();
                    System.out.print("Enter desired date and time (YYYY-MM-DD): ");
                    String dateInput = scanner.next();
                    LocalDate date = LocalDate.parse(dateInput);


                    try {
                        if (crs.makeRendezvous(nationalID, hospitalID, sectionID, diplomaID, date)) {
                            System.out.println("Rendezvous created successfully.");
                        } else {
                            System.out.println("Rendezvous limit reached for the selected doctor.");
                        }
                    } catch (IDException e) {
                        System.out.println("Error: " + e.getMessage());
                    }
                    break;

                case 6:
                    System.out.print("Enter file path to save data: ");
                    String savePath = scanner.next();
                    crs.saveTablesToDisk(savePath);
                    break;

                case 7: 
                    System.out.print("Enter file path to load data: ");
                    String loadPath = scanner.next();
                    crs.loadTablesFromDisk(loadPath);
                    break;

                case 8: 
                	crs.showCurrentSituation();
                    break;
                    
                case 9: 
                    running = false;
                    System.out.println("Exiting the system...");
                    break;     
                    

                default:
                    System.out.println("Invalid choice. Please try again.");
            }
        }

        scanner.close();
    }

}
