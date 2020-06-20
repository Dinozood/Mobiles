#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>


using namespace std;

struct user_data {
    string date;
    string str_time;
    string event;
    string x_event;
    string proto;
    string src_ip_addr_port;
    string dst_ip_addr_port;
    string x_src_ip_addr_port;
    string x_dst_ip_addr_port;
    string in_byte;
    string out_byte;
    int time = 0;
};

void feel_data(string str, string *ip, long *data_value, user_data *data);
void calculate(int *period_table, int i);
void compare(user_data *data, int *period_table, int *period, string ip);

int main(int argc, char* argv[]) {

    if (argc > 4) {
        cerr << "To many argc, need 3, got " << argc-1 << endl;
        exit(-1);
    }

    char* path = argv[1];
    string ip = argv[2];
    int period = stoi(argv[3]);
    int table_size;
    if (86400%period == 0)
        table_size = 86400/period;
    else
        table_size = 86400/period + 1;

    long int data_value = 0;
    string str;
    fstream source;
    user_data data;
    int *period_table = new int[table_size];
    source.open(path, ios::in | ios::out);
    if(!source.is_open()) {
        cerr << "Can't open csv file" << endl;
        exit(-2);
    }


        while (getline(source, str)) {
            try {
                feel_data(str, &ip, &data_value, &data);
                compare(&data, period_table, &period, ip);
            } catch (const std::invalid_argument &ia) {
//                cerr << ia.what() << endl;
                /*cout << '|' << data.date << "|\t|" << data.str_time << "|\t|" << data.event << "|\t|" << data.x_event
                     << "|\t|" << data.proto << "|\t|" << data.src_ip_addr_port << "|\t|" << data.dst_ip_addr_port << "|\t|"
                     << data.x_src_ip_addr_port << "|\t|" << data.x_dst_ip_addr_port << "|\t|" << data.in_byte
                     << "|\t|" << data.out_byte << "|" << endl;*/
                continue;
            }
        }

    calculate(period_table, table_size);
    return 0;
}

void feel_data(string str, string *ip, long *data_value, user_data *data) {
    int i = 0;

    for (i = 0; str[i] != 0; ++i) {
        if (str[i] == ' ') {
            data->date = str.substr(0, i);
            str = str.substr(i, -1);
            break;
        }
    }
    for (i = 0; str[i] == ' '; ++i);
    str = str.substr(i, -1);

    for (i = 0; str[i] != 0; ++i) {
        if (str[i] == ' ') {
            data->str_time = str.substr(0, i);
            str = str.substr(i, -1);
            break;
        }
    }
    for (i = 0; str[i] == ' '; ++i);
    str = str.substr(i, -1);

    for (i = 0; str[i] != 0; ++i) {
        if (str[i] == ' ') {
            data->event = str.substr(0, i);
            str = str.substr(i, -1);
            break;
        }
    }
    for (i = 0; str[i] == ' '; ++i);
    str = str.substr(i, -1);

    for (i = 0; str[i] != 0; ++i) {
        if (str[i] == ' ') {
            data->x_event = str.substr(0, i);
            str = str.substr(i, -1);
            break;
        }
    }
    for (i = 0; str[i] == ' '; ++i);
    str = str.substr(i, -1);

    for (i = 0; str[i] != 0; ++i) {
        if (str[i] == ' ') {
            data->proto = str.substr(0, i);
            str = str.substr(i, -1);
            break;
        }
    }
    for (i = 0; str[i] == ' '; ++i);
    str = str.substr(i, -1);

    for (i = 0; str[i] != 0; ++i) {
        if (str[i] == ' ') {
            data->src_ip_addr_port = str.substr(0, i);
            str = str.substr(i, -1);
            break;
        }
    }
    for (i = 0; str[i] == ' ' || str[i] == '-' || str[i] == '>'; ++i);
    str = str.substr(i, -1);

    for (i = 0; str[i] != 0; ++i) {
        if (str[i] == ' ') {
            data->dst_ip_addr_port = str.substr(0, i);
            str = str.substr(i, -1);
            break;
        }
    }
    for (i = 0; str[i] == ' ' || str[i] == '-' || str[i] == '>'; ++i);
    str = str.substr(i, -1);

    for (i = 0; str[i] != 0; ++i) {
        if (str[i] == ' ') {
            data->x_src_ip_addr_port = str.substr(0, i);
            str = str.substr(i, -1);
            break;
        }
    }
    for (i = 0; str[i] == ' ' || str[i] == '-' || str[i] == '>'; ++i);
    str = str.substr(i, -1);

    for (i = 0; str[i] != 0; ++i) {
        if (str[i] == ' ') {
            data->x_dst_ip_addr_port = str.substr(0, i);
            str = str.substr(i, -1);
            break;
        }
    }
    for (i = 0; str[i] == ' ' || str[i] == '-' || str[i] == '>'; ++i);
    str = str.substr(i, -1);

    for (i = 0; str[i] != 0; ++i) {
        if (str[i] == ' ') {
            data->in_byte = str.substr(0, i);
            str = str.substr(i, -1);
            break;
        }
    }
    for (i = 0; str[i] == ' ' || str[i] == '-' || str[i] == '>'; ++i);
    str = str.substr(i, -1);
    if (str[0] == 'M')
        data->in_byte = to_string(stof(data->in_byte) * 1024 * 1024);
//    str = str.substr(1, -1);
    if (str[0] > 57) {
//        cout << "RRR" <<  str << endl;
        for (i = 0; str[i] > 57; ++i);
        str = str.substr(i, -1);
    }
    data->out_byte = str;

    for (i = 0; data->str_time[i] != 0; ++i) {
        if (data->str_time[i] == ':') {
            data->time = stoi(data->str_time.substr(0, i))*3600;
            i++;
            break;
        }
    }
    for (int j = i; data->str_time[j] != 0 ; ++j) {
        if (data->str_time[j] == ':') {
            data->time += stoi(data->str_time.substr(i, j-i))*60;
            i = j+1;
            break;
        }
    }
    for (int k = i; data->str_time[k] != 0 ; ++k) {
        if (data->str_time[k] == '.') {
            data->time += stoi(data->str_time.substr(i, k-i));
            break;
        }
    }
    /*cout << '|' << data->date << "|\t|" << data->str_time << "|\t|" << data->event << "|\t|" << data->x_event
     << "|\t|" << data->proto << "|\t|" << data->src_ip_addr_port << "|\t|" << data->dst_ip_addr_port << "|\t|"
     << data->x_src_ip_addr_port << "|\t|" << data->x_dst_ip_addr_port << "|\t|" << data->in_byte
     << "|\t|" << data->out_byte << "|" << endl;*/
}

void calculate(int *period_table, int i) {
    float result = 0;
    float del = 1024;
    for (int j = 0; j < i; ++j) {
        result += period_table[j];
//        cout << j << "\t" << period_table[j] << endl;
    }
    result = result / del / del;
    if (result - (int)result > 0)
        result = (int)result + 1;
    else
        result = (int)result;
    cout << (int)result << endl;
}

void compare(user_data *data, int *period_table, int *period, string ip) {
    for (int i = 0; data->src_ip_addr_port[i] != 0; ++i) {
        if (data->src_ip_addr_port[i] == ':') {
            if (data->src_ip_addr_port.substr(0, i) == ip) {
                period_table[data->time / *period] += stoi(data->in_byte) + stoi(data->out_byte);
            }
            if (data->dst_ip_addr_port.substr(0, i) == ip) {
                period_table[data->time / *period] += stoi(data->in_byte) + stoi(data->out_byte);
            }
        }
    }
}
