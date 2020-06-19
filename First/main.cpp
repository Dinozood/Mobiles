#include <iostream>
#include <string>
#include <fstream>

void feel_data(std::string *str, float *outcalls, int *sms, std::string *my_number);
void cut_prev(std::string *str);

void calculate(int *sms, float *outcalls);

using namespace std;

int main(int argc, char* argv[]) {
    if (argc > 3) {
        cerr << "To many argc, need 2, got " << argc-1 << endl;
        exit(-1);
    }
    char* path = argv[1];
    string my_number = argv[2];

    int sms = 0;
    float  outcall = 0;
    string str;
    fstream csv;

    csv.open(path, ios::in | ios::out);
    if(!csv.is_open()) {
        cerr << "Can't open csv file" << endl;
        exit(-2);
    }
    while (getline(csv, str))
        feel_data(&str, &outcall, &sms, &my_number);

    calculate(&sms, &outcall);

    return 0;
}

void calculate(int *sms, float *outcalls) {
    int total = 0;
    total += *sms * 2;
    total += ((int)*outcalls-20)*2;
    if (*outcalls-(int)*outcalls>0)
        total+=2;
    if (total < 0)
        cout << 0 << endl;
    else
        cout << total <<endl;
}

void feel_data(string *str, float *outcalls, int *sms, string *my_number) {
    int i = 0;
    char nums[9];
    cut_prev(str);
    for (i = 0; ; ++i) {
        try {
            if (str[0][i] == ',') {
                if (str[0].substr(0, i) == *my_number) {
                    cut_prev(str);
                    cut_prev(str);
                    for (i = 0; ; ++i) {
                        if (str[0][i] == ',') {
                            *outcalls += stof(str[0].substr(0, i));
                            break;
                        }
                    }
                    cut_prev(str);
                    *sms += stoi(str[0]);
                }
                break;
            }
        }
        catch (const std::invalid_argument) {
            break;
        }
    }

}
void cut_prev(string* str){
    for (int i = 0; ; ++i) {
        if (str[0][i] == ',') {
            str[0] = str[0].substr(i+1, -1);
            break;
        }
    }
}
