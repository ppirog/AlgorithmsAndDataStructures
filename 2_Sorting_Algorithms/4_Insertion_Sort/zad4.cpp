#include <iostream>

using namespace std;

char *command;

class Student {
private:
    string studentCode;
    float gradeAverage;
    int distanceFromHomeInMeters;
    int birthMonthNumber;
public:
    Student(const string &studentCode, float gradeAverage, int distanceFromHomeInMeters, int birthMonthNumber)
            : studentCode(studentCode), gradeAverage(gradeAverage), distanceFromHomeInMeters(distanceFromHomeInMeters),
              birthMonthNumber(birthMonthNumber) {}

    Student() {}

    const string &getStudentCode() const {
        return studentCode;
    }

    float getGradeAverage() const {
        return gradeAverage;
    }

    int getDistanceFromHomeInMeters() const {
        return distanceFromHomeInMeters;
    }

    int getBirthMonthNumber() const {
        return birthMonthNumber;
    }

};

double averageGradesComparator(const Student &firstStudent, const Student &secondStudent) {
    return firstStudent.getGradeAverage() - secondStudent.getGradeAverage();
}

int distanceFromHomeInMetersComparator(const Student &firstStudent, const Student &secondStudent) {
    return firstStudent.getDistanceFromHomeInMeters() - secondStudent.getDistanceFromHomeInMeters();
}

int birthMonthNumberComparator(const Student &firstStudent, const Student &secondStudent) {
    return firstStudent.getBirthMonthNumber() - secondStudent.getBirthMonthNumber();
}

void printOneLineData(const Student &femaleStudent, const Student &maleStudent) {
    cout << femaleStudent.getStudentCode() << " " << maleStudent.getStudentCode() << " ";
}

void printData(Student *girls, Student *boys, int size) {
    for (int i = 0; i < size; ++i) {
        printOneLineData(girls[i], boys[i]);
    }
}

bool generalComparator(const Student &firstStudent, const Student &secondStudent) {

    double firstBenchmark = 0;
    double secondBenchmark = 0;
    double thirdBenchmark = 0;

    if (command[0] == 's' && command[1] == 'd' && command[2] == 'm') {
        firstBenchmark = averageGradesComparator(firstStudent, secondStudent);
        secondBenchmark = distanceFromHomeInMetersComparator(firstStudent, secondStudent);
        thirdBenchmark = birthMonthNumberComparator(firstStudent, secondStudent);
    } else if (command[0] == 's' && command[1] == 'm' && command[2] == 'd') {
        firstBenchmark = averageGradesComparator(firstStudent, secondStudent);
        secondBenchmark = birthMonthNumberComparator(firstStudent, secondStudent);
        thirdBenchmark = distanceFromHomeInMetersComparator(firstStudent, secondStudent);
    } else if (command[0] == 'd' && command[1] == 's' && command[2] == 'm') {
        firstBenchmark = distanceFromHomeInMetersComparator(firstStudent, secondStudent);
        secondBenchmark = averageGradesComparator(firstStudent, secondStudent);
        thirdBenchmark = birthMonthNumberComparator(firstStudent, secondStudent);
    } else if (command[0] == 'd' && command[1] == 'm' && command[2] == 's') {
        firstBenchmark = distanceFromHomeInMetersComparator(firstStudent, secondStudent);
        secondBenchmark = birthMonthNumberComparator(firstStudent, secondStudent);
        thirdBenchmark = averageGradesComparator(firstStudent, secondStudent);
    } else if (command[0] == 'm' && command[1] == 's' && command[2] == 'd') {
        firstBenchmark = birthMonthNumberComparator(firstStudent, secondStudent);
        secondBenchmark = averageGradesComparator(firstStudent, secondStudent);
        thirdBenchmark = distanceFromHomeInMetersComparator(firstStudent, secondStudent);
    } else if (command[0] == 'm' && command[1] == 'd' && command[2] == 's') {
        firstBenchmark = birthMonthNumberComparator(firstStudent, secondStudent);
        secondBenchmark = distanceFromHomeInMetersComparator(firstStudent, secondStudent);
        thirdBenchmark = averageGradesComparator(firstStudent, secondStudent);
    }

    if (firstBenchmark < 0) {
        return true;
    } else {
        if (firstBenchmark == 0) {
            if (secondBenchmark < 0) {
                return true;
            } else {
                if (secondBenchmark == 0) {
                    if (thirdBenchmark < 0) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void insertionSort(Student *tab, unsigned int n) {

    int j;
    Student pom;

    for (int i = 1; i < n; i++) {
        pom = tab[i];
        j = i - 1;

        while (j >= 0 && generalComparator(tab[j], pom)) {
            tab[j + 1] = tab[j];
            --j;
        }
        tab[j + 1] = pom;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int size;
    cin >> size;
    cin.ignore();

    Student *femaleStudents = new Student[size];
    Student *maleStudents = new Student[size];

    string commandLine;
    getline(cin, commandLine);
    command = new char[3];

    command[0] = commandLine[0];
    command[1] = commandLine[2];
    command[2] = commandLine[4];

    for (int i = 0; i < size; ++i) {
        string femaleStudentCode;
        float femaleGradeAverage;
        int femaleDistanceFromHomeInMeters;
        int femaleBirthMonthNumber;

        string maleStudentCode;
        float maleGradeAverage;
        int maleDistanceFromHomeInMeters;
        int maleBirthMonthNumber;

        cin >> femaleStudentCode >> femaleGradeAverage >> femaleDistanceFromHomeInMeters >> femaleBirthMonthNumber
            >> maleStudentCode >> maleGradeAverage >> maleDistanceFromHomeInMeters
            >> maleBirthMonthNumber;
        cin.ignore();

        maleStudents[i] = Student(maleStudentCode, maleGradeAverage, maleDistanceFromHomeInMeters,
                                  maleBirthMonthNumber);
        femaleStudents[i] = Student(femaleStudentCode, femaleGradeAverage, femaleDistanceFromHomeInMeters,
                                    femaleBirthMonthNumber);

    }

    insertionSort(maleStudents, size);
    insertionSort(femaleStudents, size);

    printData(femaleStudents, maleStudents, size);

    delete[] femaleStudents;
    delete[] maleStudents;
    delete[] command;
    return 0;
}
