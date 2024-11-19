    #include <iostream>
    #include <iomanip>
    #include <Windows.h>
    #include <string.h>

    using namespace std;

    #pragma region enums
    enum Majors {
        ComputerScience = 1,
        Informatics,
        MathematicsAndEconomics,
        PhysicsAndInformatics,
        LaborTraining
    };
    enum Subjects {
        Physics = 1,
        Math,
        Prog,
        Num_methods,
        Pedagogika
    };
    #pragma endregion enums

    #pragma region student_struct
    #pragma pack(push, 1) //less memory using
    struct Student {
        string return_prizv() {
            return this->prizv;
        }
        unsigned short return_course() {
            return this->course;
        }
        string return_major_name() {
            switch (this->major) {
            case ComputerScience:
                return "����'����� �����";
            case Informatics:
                return "�����������";
            case MathematicsAndEconomics:
                return "���������� & ��������";
            case PhysicsAndInformatics:
                return "Գ���� & �����������";
            case LaborTraining:
                return "������� ��������";
            }
        }
        Majors return_major() {
            return this->major;
        }
        unsigned short return_physics() {
            return this->physics;
        }
        unsigned short return_math() {
            return this->math;
        }
        unsigned short return_prog() {
            return this->prog;
        }
        unsigned short return_num_methods() {
            return this->num_methods;
        }
        unsigned short return_pedagogika() {
            return this->pedagogika;
        }
        unsigned short return_third() {
            switch (this->major) {
            case ComputerScience:
                return this->prog;
            case Informatics:
                return this->num_methods;
            default:
                return this->pedagogika;
            }
        }
        void fill_struct(int i) {
            int temp;
            cout << "������� �" << i + 1 << endl;
            cout << "�������: "; cin >> this->prizv;
            cout << "����: "; cin >> this->course;
            cout << "������������: (����'����� ����� = 1, ����������� = 2, ���������� & �������� = 3, Գ���� & ����������� = 4, ������� �������� = 5): "; cin >> temp;
            this->major = (Majors)temp;
            cout << "������ � ������: "; cin >> this->physics;
            cout << "������ � ����������: "; cin >> this->math;
            switch (this->major) {
            case ComputerScience:
                cout << "������ � �������������: "; cin >> this->prog;
                break;
            case Informatics:
                cout << "������ � ��������� ������: "; cin >> this->num_methods;
                break;
            case MathematicsAndEconomics:
                cout << "������ � ���������: "; cin >> this->pedagogika;
                break;
            case PhysicsAndInformatics:
                cout << "������ � ���������: "; cin >> this->pedagogika;
                break;
            case LaborTraining:
                cout << "������ � ���������: "; cin >> this->pedagogika;
                break;
            }
        }
    private:
        string prizv;
        unsigned short course;
        Majors major;
        unsigned short physics;
        unsigned short math;
        union {
            unsigned short prog;
            unsigned short num_methods;
            unsigned short pedagogika;
        };
    };
    #pragma pack(pop)    // return old config 
    #pragma endregion student_struct

    #pragma region functions
    void fill_arr(Student* arr, int n) {
        for (int i = 0; i < n; i++) {
            arr[i] = Student();
            arr[i].fill_struct(i);
            cout << endl;
        }
    }

    int calc_n(int n) {
        int res = 0;
        while (n != 0) {
            n /= 10;
            res++;
        }
        return res;
    }

    int lenOfLongestPrizv(Student* arr, int n) {
        int res = -1;
        for (int i = 0; i < n; i++) {
            if (static_cast<int>(arr[i].return_prizv().length()) > res) {
                res = static_cast<int>(arr[i].return_prizv().length());
            }
        }
        return res;
    }

    void printHeader(Student* arr, int n) {
        int width = lenOfLongestPrizv(arr, n);
        (width <= 8) ? (width = 8) : (NULL);
        int maxDigits = calc_n(n);

        for (int i = 0; i < (maxDigits - 1) + (width - 8) + 111; i++) {
            cout << "=";
        }
        cout << endl;

        cout << "|" << setw(maxDigits) << right << "�";
        cout << "|" << setw(width) << left << "�������" << "| ���� |     ������������    | Գ���� | ���������� | ������������� | ������� ������ | ��������� |" << endl;

        for (int i = 0; i < (maxDigits - 1) + (width - 8) + 111; i++) {
            cout << "-";
        }
        cout << endl;


        for (int i = 0; i < n; i++) {
            cout << "|" << setw(maxDigits) << right << i + 1;
            cout << "|" << setw(width) << left << arr[i].return_prizv();
            cout << "|" << setw(6) << left << arr[i].return_course();
            cout << "|" << setw(22) << left << arr[i].return_major_name();
            cout << "|" << setw(8) << left << arr[i].return_physics();
            cout << "|" << setw(12) << left << arr[i].return_math();
            cout << "|" << setw(15) << left;
            (arr[i].return_major() == ComputerScience ? cout << arr[i].return_prog() : cout << "-");
            cout << "|" << setw(17) << left;
            (arr[i].return_major() == Informatics ? cout << arr[i].return_num_methods() : cout << "-");
            cout << "|" << setw(12) << left;
            (arr[i].return_major() != ComputerScience && arr[i].return_major() != Informatics ? cout << arr[i].return_pedagogika() : cout << "-");
            cout << setw(13) << "|" << endl;
        }

        for (int i = 0; i < (maxDigits - 1) + (width - 8) + 111; i++) {
            cout << "-";
        }
        cout << endl;
    }

    int counter(Student* arr, int n) {
        int result = 0;
        for (int i = 0; i < n; i++) {
            if (arr[i].return_physics() == 5) {
                result++;
            }
        }
        return result * 100 / n;
    }

    int calculateExcellentStudents(Student* arr, int n) {
        int excellentCount = 0;
        for (int i = 0; i < n; i++) {
            // ���� ������� �� �� ������ 5, �� �� �������
            if (arr[i].return_physics() == 5 &&
                arr[i].return_math() == 5) {
                switch (arr[i].return_major()) {
                case ComputerScience:
                    if (arr[i].return_prog() == 5) {
                        excellentCount++;
                    }
                    break;
                case Informatics:
                    if (arr[i].return_num_methods() == 5) {
                        excellentCount++;
                    }
                    break;
                default:
                    if (arr[i].return_pedagogika()) {
                        excellentCount++;
                    }
                }
            }
        }
        return excellentCount;
    }

    #pragma endregion functions

    int main()
    {
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);
        int n;
        cout << "������ ������� ��������: "; cin >> n;

        Student* arr = new Student[n];
        fill_arr(arr, n);

        printHeader(arr, n);

        cout << "ʳ������ ��������, �� �������� 5 � ������: " << counter(arr, n) << '%' << endl;
        cout << "ʳ������ ��������, �� ������� �� ������: " << calculateExcellentStudents(arr, n) << endl;

        delete[] arr;
    }
