#include <iostream>
#include <vector>
#include <string>
#include <fstream>

struct Job {
    int id;
    std::string title;
    std::string company;
    std::string status;
};

std::vector<Job> jobs;
int currentId = 1;

void displayMenu() {
    std::cout << "Job Tracker Menu:\n";
    std::cout << "1. Add Job\n";
    std::cout << "2. Update Job\n";
    std::cout << "3. Delete Job\n";
    std::cout << "4. View Jobs\n";
    std::cout << "5. Save and Exit\n";
    std::cout << "Choose an option: ";
}

void addJob() {
    Job newJob;
    newJob.id = currentId++;
    std::cout << "Enter job title: ";
    std::cin.ignore();
    std::getline(std::cin, newJob.title);
    std::cout << "Enter company: ";
    std::getline(std::cin, newJob.company);
    std::cout << "Enter status: ";
    std::getline(std::cin, newJob.status);
    jobs.push_back(newJob);
    std::cout << "Job added successfully!\n";
}

void updateJob() {
    int id;
    std::cout << "Enter job ID to update: ";
    std::cin >> id;

    for (auto &job : jobs) {
        if (job.id == id) {
            std::cout << "Enter new job title: ";
            std::cin.ignore();
            std::getline(std::cin, job.title);
            std::cout << "Enter new company: ";
            std::getline(std::cin, job.company);
            std::cout << "Enter new status: ";
            std::getline(std::cin, job.status);
            std::cout << "Job updated successfully!\n";
            return;
        }
    }
    std::cout << "Job not found.\n";
}

void deleteJob() {
    int id;
    std::cout << "Enter job ID to delete: ";
    std::cin >> id;

    for (auto it = jobs.begin(); it != jobs.end(); ++it) {
        if (it->id == id) {
            jobs.erase(it);
            std::cout << "Job deleted successfully!\n";
            return;
        }
    }
    std::cout << "Job not found.\n";
}

void viewJobs() {
    if (jobs.empty()) {
        std::cout << "No jobs available.\n";
        return;
    }

    for (const auto &job : jobs) {
        std::cout << "ID: " << job.id << "\n";
        std::cout << "Title: " << job.title << "\n";
        std::cout << "Company: " << job.company << "\n";
        std::cout << "Status: " << job.status << "\n";
        std::cout << "-------------------\n";
    }
}

void saveJobsToFile() {
    std::ofstream outFile("jobs.txt");
    for (const auto &job : jobs) {
        outFile << job.id << '\n' << job.title << '\n' << job.company << '\n' << job.status << '\n';
    }
    outFile.close();
}

void loadJobsFromFile() {
    std::ifstream inFile("jobs.txt");
    if (!inFile) return;

    Job job;
    while (inFile >> job.id) {
        inFile.ignore();  // Ignore the newline character after the ID
        std::getline(inFile, job.title);
        std::getline(inFile, job.company);
        std::getline(inFile, job.status);
        jobs.push_back(job);
    }
    inFile.close();
}

int main() {
    loadJobsFromFile();
    int choice;
    while (true) {
        displayMenu();
        std::cin >> choice;
        switch (choice) {
            case 1:
                addJob();
                break;
            case 2:
                updateJob();
                break;
            case 3:
                deleteJob();
                break;
            case 4:
                viewJobs();
                break;
            case 5:
                saveJobsToFile();
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}
