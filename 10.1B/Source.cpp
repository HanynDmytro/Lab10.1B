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
                return "Комп'ютерні науки";
            case Informatics:
                return "Інформатика";
            case MathematicsAndEconomics:
                return "Математика & Економіка";
            case PhysicsAndInformatics:
                return "Фізика & Інформатика";
            case LaborTraining:
                return "Трудове навчання";
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
            cout << "Студент №" << i + 1 << endl;
            cout << "Прізвище: "; cin >> this->prizv;
            cout << "Курс: "; cin >> this->course;
            cout << "Спеціальність: (Комп'ютерні науки = 1, Інформатика = 2, Математика & Економіка = 3, Фізика & Інформатика = 4, Трудове навчання = 5): "; cin >> temp;
            this->major = (Majors)temp;
            cout << "Оцінка з фізики: "; cin >> this->physics;
            cout << "Оцінка з математики: "; cin >> this->math;
            switch (this->major) {
            case ComputerScience:
                cout << "Оцінка з програмування: "; cin >> this->prog;
                break;
            case Informatics:
                cout << "Оцінка з чисельних методів: "; cin >> this->num_methods;
                break;
            case MathematicsAndEconomics:
                cout << "Оцінка з педагогіки: "; cin >> this->pedagogika;
                break;
            case PhysicsAndInformatics:
                cout << "Оцінка з педагогіки: "; cin >> this->pedagogika;
                break;
            case LaborTraining:
                cout << "Оцінка з педагогіки: "; cin >> this->pedagogika;
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

        cout << "|" << setw(maxDigits) << right << "№";
        cout << "|" << setw(width) << left << "Прізвище" << "| Курс |     Спеціальність    | Фізика | Математика | Програмування | Чисельні методи | Педагогіка |" << endl;

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
            // Якщо студент має всі оцінки 5, то він відмінник
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
        cout << "Введіть кількість студентів: "; cin >> n;

        Student* arr = new Student[n];
        fill_arr(arr, n);

        printHeader(arr, n);

        cout << "Кількість студентів, які отримали 5 з фізики: " << counter(arr, n) << '%' << endl;
        cout << "Кількість студентів, які вчяться на відмінно: " << calculateExcellentStudents(arr, n) << endl;

        delete[] arr;
    }
