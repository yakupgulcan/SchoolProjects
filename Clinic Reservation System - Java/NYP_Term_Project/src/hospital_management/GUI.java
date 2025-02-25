package hospital_management;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.time.LocalDate;
import javax.swing.border.EmptyBorder;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import javax.swing.JFileChooser;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;

public class GUI extends JFrame {
    /**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private CRS crs;
    private JPanel mainPanel;
    private CardLayout cardLayout;
    
    private JButton addHospitalBtn;
    private JButton addPatientBtn;
    private JButton addSectionBtn;
    private JButton addDoctorBtn;
    private JButton makeRendezvousBtn;
    private JButton saveDataBtn;
    private JButton loadDataBtn;
    private JButton showSituationBtn;
    
    public GUI() {
        crs = new CRS();
        setupFrame();
        initializeComponents();
        createMainMenu();
        createCards();
    }
    
    private void setupFrame() {
        setTitle("Clinic Reservation System");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(800, 600);
        setLocationRelativeTo(null);
        
        cardLayout = new CardLayout();
        mainPanel = new JPanel(cardLayout);
        add(mainPanel);
    }
    
    private void initializeComponents() {
        addHospitalBtn = new JButton("Add Hospital");
        addPatientBtn = new JButton("Add Patient");
        addSectionBtn = new JButton("Add Section");
        addDoctorBtn = new JButton("Add Doctor");
        makeRendezvousBtn = new JButton("Make Rendezvous");
        saveDataBtn = new JButton("Save Data");
        loadDataBtn = new JButton("Load Data");
        showSituationBtn = new JButton("Show Current Situation");
    }
    
    private void createMainMenu() {
        JPanel menuPanel = new JPanel(new GridBagLayout());
        menuPanel.setBorder(new EmptyBorder(20, 20, 20, 20));
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.gridwidth = GridBagConstraints.REMAINDER;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.insets = new Insets(5, 0, 5, 0);
        
        menuPanel.add(addHospitalBtn, gbc);
        menuPanel.add(addPatientBtn, gbc);
        menuPanel.add(addSectionBtn, gbc);
        menuPanel.add(addDoctorBtn, gbc);
        menuPanel.add(makeRendezvousBtn, gbc);
        menuPanel.add(saveDataBtn, gbc);
        menuPanel.add(loadDataBtn, gbc);
        menuPanel.add(showSituationBtn, gbc);
        
        mainPanel.add(menuPanel, "MAIN_MENU");
        
        addHospitalBtn.addActionListener(e -> cardLayout.show(mainPanel, "ADD_HOSPITAL"));
        addPatientBtn.addActionListener(e -> cardLayout.show(mainPanel, "ADD_PATIENT"));
        addSectionBtn.addActionListener(e -> cardLayout.show(mainPanel, "ADD_SECTION"));
        addDoctorBtn.addActionListener(e -> cardLayout.show(mainPanel, "ADD_DOCTOR"));
        makeRendezvousBtn.addActionListener(e -> cardLayout.show(mainPanel, "MAKE_RENDEZVOUS"));
        saveDataBtn.addActionListener(e -> saveData());
        loadDataBtn.addActionListener(e -> loadData());
        showSituationBtn.addActionListener(e -> showSituation());
    }
    
    private void createCards() {
        createAddHospitalCard();
        createAddPatientCard();
        createAddSectionCard();
        createAddDoctorCard();
        createMakeRendezvousCard();
    }
    
    private void createAddHospitalCard() {
        JPanel panel = new JPanel(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(5, 5, 5, 5);
        gbc.fill = GridBagConstraints.HORIZONTAL;
        
        JTextField idField = new JTextField(20);
        JTextField nameField = new JTextField(20);
        JButton submitBtn = new JButton("Add Hospital");
        JButton backBtn = new JButton("Back to Menu");
        
        gbc.gridx = 0; gbc.gridy = 0;
        panel.add(new JLabel("Hospital ID:"), gbc);
        gbc.gridx = 1;
        panel.add(idField, gbc);
        
        gbc.gridx = 0; gbc.gridy = 1;
        panel.add(new JLabel("Hospital Name:"), gbc);
        gbc.gridx = 1;
        panel.add(nameField, gbc);
        
        gbc.gridx = 0; gbc.gridy = 2; gbc.gridwidth = 2;
        panel.add(submitBtn, gbc);
        
        gbc.gridy = 3;
        panel.add(backBtn, gbc);
        
        submitBtn.addActionListener(e -> {
            try {
                int id = Integer.parseInt(idField.getText());
                String name = nameField.getText();
                crs.addHospital(new Hospital(id, name));
                JOptionPane.showMessageDialog(this, "Hospital added successfully!");
                idField.setText("");
                nameField.setText("");
            } catch (NumberFormatException ex) {
                JOptionPane.showMessageDialog(this, "Please enter a valid ID");
            } catch (IDException ex) {
                JOptionPane.showMessageDialog(this, ex.getMessage());
            }
        });
        
        backBtn.addActionListener(e -> cardLayout.show(mainPanel, "MAIN_MENU"));
        
        mainPanel.add(panel, "ADD_HOSPITAL");
    }
    
    private void createAddPatientCard() {
        JPanel panel = new JPanel(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(5, 5, 5, 5);
        gbc.fill = GridBagConstraints.HORIZONTAL;
        
        JTextField nameField = new JTextField(20);
        JTextField idField = new JTextField(20);
        JButton submitBtn = new JButton("Add Patient");
        JButton backBtn = new JButton("Back to Menu");
        
        gbc.gridx = 0; gbc.gridy = 0;
        panel.add(new JLabel("Patient Name:"), gbc);
        gbc.gridx = 1;
        panel.add(nameField, gbc);
        
        gbc.gridx = 0; gbc.gridy = 1;
        panel.add(new JLabel("National ID:"), gbc);
        gbc.gridx = 1;
        panel.add(idField, gbc);
        
        gbc.gridx = 0; gbc.gridy = 2; gbc.gridwidth = 2;
        panel.add(submitBtn, gbc);
        
        gbc.gridy = 3;
        panel.add(backBtn, gbc);
        
        submitBtn.addActionListener(e -> {
            try {
                long id = Long.parseLong(idField.getText());
                String name = nameField.getText();
                crs.addPatient(new Patient(name, id));
                JOptionPane.showMessageDialog(this, "Patient added successfully!");
                nameField.setText("");
                idField.setText("");
            } catch (NumberFormatException ex) {
                JOptionPane.showMessageDialog(this, "Please enter a valid ID!");
            } catch (IDException ex) {
                JOptionPane.showMessageDialog(this, ex.getMessage());
            }
        });
        
        backBtn.addActionListener(e -> cardLayout.show(mainPanel, "MAIN_MENU"));
        
        mainPanel.add(panel, "ADD_PATIENT");
    }
    
    private void createAddSectionCard() {
        JPanel panel = new JPanel(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(5, 5, 5, 5);
        gbc.fill = GridBagConstraints.HORIZONTAL;
        
        JComboBox<Hospital> hospitalCombo = new JComboBox<>();
        JTextField idField = new JTextField(20);
        JTextField nameField = new JTextField(20);
        JButton submitBtn = new JButton("Add Section");
        JButton backBtn = new JButton("Back to Menu");
        
        gbc.gridx = 0; gbc.gridy = 0;
        panel.add(new JLabel("Select Hospital:"), gbc);
        gbc.gridx = 1;
        panel.add(hospitalCombo, gbc);
        
        gbc.gridx = 0; gbc.gridy = 1;
        panel.add(new JLabel("Section ID:"), gbc);
        gbc.gridx = 1;
        panel.add(idField, gbc);
        
        gbc.gridx = 0; gbc.gridy = 2;
        panel.add(new JLabel("Section Name:"), gbc);
        gbc.gridx = 1;
        panel.add(nameField, gbc);
        
        gbc.gridx = 0; gbc.gridy = 3; gbc.gridwidth = 2;
        panel.add(submitBtn, gbc);
        
        gbc.gridy = 4;
        panel.add(backBtn, gbc);
        
        panel.addComponentListener(new ComponentAdapter() {
            @Override
            public void componentShown(ComponentEvent e) {
                hospitalCombo.removeAllItems();
                for (Hospital hospital : crs.getHospitals().values()) {
                    hospitalCombo.addItem(hospital);
                }
            }
        });
        
        submitBtn.addActionListener(e -> {
            try {
                Hospital selectedHospital = (Hospital) hospitalCombo.getSelectedItem();
                if (selectedHospital == null) {
                    JOptionPane.showMessageDialog(this, "Please select a hospital!");
                    return;
                }
                
                int id = Integer.parseInt(idField.getText());
                String name = nameField.getText();
                selectedHospital.addSection(new Section(id, name));
                JOptionPane.showMessageDialog(this, "Section added successfully!");
                idField.setText("");
                nameField.setText("");
            } catch (NumberFormatException ex) {
                JOptionPane.showMessageDialog(this, "Please enter a valid ID!");
            } catch (DuplicateInfoException ex) {
                JOptionPane.showMessageDialog(this, ex.getMessage());
            }
        });
        
        backBtn.addActionListener(e -> cardLayout.show(mainPanel, "MAIN_MENU"));
        
        mainPanel.add(panel, "ADD_SECTION");
    }
    
    private void createAddDoctorCard() {
        JPanel panel = new JPanel(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(5, 5, 5, 5);
        gbc.fill = GridBagConstraints.HORIZONTAL;
        
        JComboBox<Hospital> hospitalCombo = new JComboBox<>();
        JComboBox<Section> sectionCombo = new JComboBox<>();
        JTextField nameField = new JTextField(20);
        JTextField nationalIdField = new JTextField(20);
        JTextField diplomaIdField = new JTextField(20);
        JTextField maxPatientsField = new JTextField(20);
        JButton submitBtn = new JButton("Add Doctor");
        JButton backBtn = new JButton("Back to Menu");
        
        gbc.gridx = 0; gbc.gridy = 0;
        panel.add(new JLabel("Select Hospital:"), gbc);
        gbc.gridx = 1;
        panel.add(hospitalCombo, gbc);
        
        gbc.gridx = 0; gbc.gridy = 1;
        panel.add(new JLabel("Select Section:"), gbc);
        gbc.gridx = 1;
        panel.add(sectionCombo, gbc);
        
        gbc.gridx = 0; gbc.gridy = 2;
        panel.add(new JLabel("Doctor Name:"), gbc);
        gbc.gridx = 1;
        panel.add(nameField, gbc);
        
        gbc.gridx = 0; gbc.gridy = 3;
        panel.add(new JLabel("National ID:"), gbc);
        gbc.gridx = 1;
        panel.add(nationalIdField, gbc);
        
        gbc.gridx = 0; gbc.gridy = 4;
        panel.add(new JLabel("Diploma ID:"), gbc);
        gbc.gridx = 1;
        panel.add(diplomaIdField, gbc);
        
        gbc.gridx = 0; gbc.gridy = 5;
        panel.add(new JLabel("Max Patients/Day:"), gbc);
        gbc.gridx = 1;
        panel.add(maxPatientsField, gbc);
        
        gbc.gridx = 0; gbc.gridy = 6; gbc.gridwidth = 2;
        panel.add(submitBtn, gbc);
        
        gbc.gridy = 7;
        panel.add(backBtn, gbc);
        
        panel.addComponentListener(new ComponentAdapter() {
            @Override
            public void componentShown(ComponentEvent e) {
                hospitalCombo.removeAllItems();
                for (Hospital hospital : crs.getHospitals().values()) {
                    hospitalCombo.addItem(hospital);
                }
            }
        });
        
        hospitalCombo.addActionListener(e -> {
            sectionCombo.removeAllItems();
            Hospital selectedHospital = (Hospital) hospitalCombo.getSelectedItem();
            if (selectedHospital != null) {
                for (Section section : selectedHospital.getSections()) {
                    sectionCombo.addItem(section);
                }
            }
        });
        
        submitBtn.addActionListener(e -> {
            try {
                Section selectedSection = (Section) sectionCombo.getSelectedItem();
                if (selectedSection == null) {
                    JOptionPane.showMessageDialog(this, "Please select a section!");
                    return;
                }
                
                String name = nameField.getText();
                long nationalId = Long.parseLong(nationalIdField.getText());
                int diplomaId = Integer.parseInt(diplomaIdField.getText());
                int maxPatients = Integer.parseInt(maxPatientsField.getText());
                
                selectedSection.addDoctor(new Doctor(name, nationalId, diplomaId, maxPatients));
                JOptionPane.showMessageDialog(this, "Doctor added successfully!");
                
                nameField.setText("");
                nationalIdField.setText("");
                diplomaIdField.setText("");
                maxPatientsField.setText("");
            } catch (NumberFormatException ex) {
                JOptionPane.showMessageDialog(this, "Please enter valid numbers!");
            } catch (DuplicateInfoException ex) {
            	JOptionPane.showMessageDialog(this, ex.getMessage());
            }
        });
        
        backBtn.addActionListener(e -> cardLayout.show(mainPanel, "MAIN_MENU"));
        
        mainPanel.add(panel, "ADD_DOCTOR");
    }
    
    private void createMakeRendezvousCard() {
        JPanel panel = new JPanel(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(5, 5, 5, 5);
        gbc.fill = GridBagConstraints.HORIZONTAL;
        
        JComboBox<Patient> patientCombo = new JComboBox<>();
        JComboBox<Hospital> hospitalCombo = new JComboBox<>();
        JComboBox<Section> sectionCombo = new JComboBox<>();
        JComboBox<Doctor> doctorCombo = new JComboBox<>();
        JTextField dateField = new JTextField(20);
        JButton submitBtn = new JButton("Make Rendezvous");
        JButton backBtn = new JButton("Back to Menu");
        
        gbc.gridx = 0; gbc.gridy = 0;
        panel.add(new JLabel("Select Patient:"), gbc);
        gbc.gridx = 1;
        panel.add(patientCombo, gbc);
        
        gbc.gridx = 0; gbc.gridy = 1;
        panel.add(new JLabel("Select Hospital:"), gbc);
        gbc.gridx = 1;
        panel.add(hospitalCombo, gbc);
        
        gbc.gridx = 0; gbc.gridy = 2;
        panel.add(new JLabel("Select Section:"), gbc);
        gbc.gridx = 1;
        panel.add(sectionCombo, gbc);
        
        gbc.gridx = 0; gbc.gridy = 3;
        panel.add(new JLabel("Select Doctor:"), gbc);
        gbc.gridx = 1;
        panel.add(doctorCombo, gbc);
        
        gbc.gridx = 0; gbc.gridy = 4;
        panel.add(new JLabel("Date (YYYY-MM-DD):"), gbc);
        gbc.gridx = 1;
        panel.add(dateField, gbc);
        
        gbc.gridx = 0; gbc.gridy = 5; gbc.gridwidth = 2;
        panel.add(submitBtn, gbc);
        
        gbc.gridy = 6;
        panel.add(backBtn, gbc);
        
        panel.addComponentListener(new ComponentAdapter() {
            @Override
            public void componentShown(ComponentEvent e) {
                patientCombo.removeAllItems();
                for (Patient patient : crs.getPatients().values()) {
                    patientCombo.addItem(patient);
                }
                
                hospitalCombo.removeAllItems();
                for (Hospital hospital : crs.getHospitals().values()) {
                    hospitalCombo.addItem(hospital);
                }
            }
        });
        
        hospitalCombo.addActionListener(e -> {
            sectionCombo.removeAllItems();
            doctorCombo.removeAllItems();
            Hospital selectedHospital = (Hospital) hospitalCombo.getSelectedItem();
            if (selectedHospital != null) {
                for (Section section : selectedHospital.getSections()) {
                    sectionCombo.addItem(section);
                }
            }
        });
        
        sectionCombo.addActionListener(e -> {
            doctorCombo.removeAllItems();
            Section selectedSection = (Section) sectionCombo.getSelectedItem();
            if (selectedSection != null) {
                for (Doctor doctor : selectedSection.getDoctors()) {
                    doctorCombo.addItem(doctor);
                }
            }
        });
        
        submitBtn.addActionListener(e -> {
            try {
                Patient selectedPatient = (Patient) patientCombo.getSelectedItem();
                Hospital selectedHospital = (Hospital) hospitalCombo.getSelectedItem();
                Section selectedSection = (Section) sectionCombo.getSelectedItem();
                Doctor selectedDoctor = (Doctor) doctorCombo.getSelectedItem();
                
                if (selectedPatient == null || selectedHospital == null || 
                    selectedSection == null || selectedDoctor == null) {
                    JOptionPane.showMessageDialog(this, "Please select all required fields!");
                    return;
                }
                
                LocalDate date = LocalDate.parse(dateField.getText());
                
                boolean success = crs.makeRendezvous(
                    selectedPatient.getNational_id(),
                    selectedHospital.getId(),
                    selectedSection.getId(),
                    selectedDoctor.getDiploma_id(),
                    date
                );
                
                if (success) {
                    JOptionPane.showMessageDialog(this, "Rendezvous created successfully!");
                    dateField.setText("");
                }
            } catch (Exception ex) {
                JOptionPane.showMessageDialog(this, ex.getMessage());
            }
        });
        
        backBtn.addActionListener(e -> cardLayout.show(mainPanel, "MAIN_MENU"));
        
        mainPanel.add(panel, "MAKE_RENDEZVOUS");
    }
    
    private void saveData() {
        JFileChooser fileChooser = new JFileChooser();
        if (fileChooser.showSaveDialog(this) == JFileChooser.APPROVE_OPTION) {
            String filePath = fileChooser.getSelectedFile().getAbsolutePath();
            crs.saveTablesToDisk(filePath);
        }
    }
    
    private void loadData() {
        JFileChooser fileChooser = new JFileChooser();
        if (fileChooser.showOpenDialog(this) == JFileChooser.APPROVE_OPTION) {
            String filePath = fileChooser.getSelectedFile().getAbsolutePath();
            crs.loadTablesFromDisk(filePath);
        }
    }
    
    private void showSituation() {
        JTextArea textArea = new JTextArea(20, 40);
        textArea.setEditable(false);
        
        PrintStream originalOut = System.out;
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        PrintStream ps = new PrintStream(baos);
        System.setOut(ps);
        
        crs.showCurrentSituation();
        
        System.setOut(originalOut);
        
        textArea.setText(baos.toString());
        
        JScrollPane scrollPane = new JScrollPane(textArea);
        JOptionPane.showMessageDialog(this, scrollPane, "Current Situation", JOptionPane.INFORMATION_MESSAGE);
    }
    
    

}