#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

#define NUM_CORES 24

using namespace std;

int main() {
  ifstream file_list;
  file_list.open("file.list");
  if (file_list.fail()) {
    cerr << "No file.list is provided." << endl;
    return -1;
  }
  vector<string> file_names;
  string file_name;
  while (file_list >> file_name) {
    file_names.push_back(file_name);
  }
  file_list.close();

  ifstream cpu_file;
  cpu_file.open("cpu-usage.csv");
  const bool is_cpu = !cpu_file.fail();

  ifstream net_file;
  net_file.open("net-stat.csv");
  const bool is_net = !net_file.fail();
  
  if (!is_cpu && !is_net) {
    cerr << "Neither cpu usage nor net stat files are provided." << endl;
    return -1;
  }

  for (vector<string>::iterator it = file_names.begin(); it != file_names.end(); ++it) {
    // For each log file
    ifstream interval_file;
    interval_file.open((*it + ".interval").c_str());
    if (interval_file.fail()) {
      cerr << "Failed to open .interval file: " << *it << endl;
      continue;
    }

    ofstream usage_file;
    usage_file.open((*it + ".usage").c_str());
    usage_file << "# Task time\t" << "Num of returns\t" << "CPU usage per core\t";
    usage_file << "Num of connections\t" << "Median of Recv-Q\t" << "Median of Send-Q" << endl;

    int task_time, num_return;
    long long begin_time, end_time, cur_time_cpu, cur_time_net;
    int usage1, usage2, usage3;
    int port_usage1, port_usage2, port_usage3, recv_q1, recv_q2, recv_q3, send_q1, send_q2, send_q3, cur_port_usage, cur_recv_q, cur_send_q;

    char c;
    string comment;
    while (c = cpu_file.peek(), c < '0' || c > '9') {
      getline(cpu_file, comment); // read in comments
    }
    cpu_file >> cur_time_cpu;
    
    while (c = net_file.peek(), c < '0' || c > '9') {
      getline(net_file, comment); // read in comments
    }
    net_file >> cur_time_net;

    while (interval_file >> task_time >> num_return >> begin_time >> end_time) {
      usage_file << task_time << "\t" << num_return << "\t"; 
      double cpu_usage = 0;
      if (is_cpu) {
        int valid_cnt = 0;
        do {
          if (cur_time_cpu >= begin_time && cur_time_cpu <= end_time) {
            cpu_file >> usage1 >> usage2 >> usage3;
            int cur_usage = usage1 + usage2 + usage3;
            if (cur_usage > 3) {
              ++valid_cnt;
              cpu_usage += cur_usage;
            }
          } else if (cur_time_cpu < begin_time) {
            cpu_file >> usage1 >> usage2 >> usage3;
            continue;
          } else if (cur_time_cpu > end_time) {
            break;
          }
        } while (cpu_file >> cur_time_cpu);
        if (valid_cnt != 0) {
          cpu_usage = cpu_usage / valid_cnt / NUM_CORES;
        }
      } 
      usage_file << cpu_usage << "\t";
      
      int max_conn = 0;
      int median_recv = 0;
      int median_send = 0;
      if (is_net) {
        vector<int> valid_recv;
        vector<int> valid_send;
        do {
          if (cur_time_net >= begin_time && cur_time_net <= end_time) {
            net_file >> port_usage1 >> recv_q1 >> send_q1;
            net_file >> port_usage2 >> recv_q2 >> send_q2;
            net_file >> port_usage3 >> recv_q3 >> send_q3;

            cur_port_usage = port_usage1 + port_usage2 + port_usage3 - 2; // only one of the three should be included, and the other two are, in most cases, separately equal to 1
            cur_recv_q = recv_q1 + recv_q2 + recv_q3;
            cur_send_q = send_q1 + send_q2 + send_q3;

            if (cur_port_usage > max_conn) max_conn = cur_port_usage;
            if (cur_recv_q > 0) {
              valid_recv.push_back(cur_recv_q);
            }
            if (cur_send_q > 0) {
              valid_send.push_back(cur_send_q);
            }
          } else if (cur_time_net < begin_time) {
            net_file >> port_usage1 >> recv_q1 >> send_q1;
            net_file >> port_usage2 >> recv_q2 >> send_q2;
            net_file >> port_usage3 >> recv_q3 >> send_q3;
          } else if (cur_time_net > end_time) {
            break;
          }
        } while (net_file >> cur_time_net);
        int mi;
        if (mi = valid_recv.size() / 2, mi != 0) {
          sort(valid_recv.begin(), valid_recv.end());
          if (valid_recv.size() % 2) {
            median_recv = valid_recv[mi];
          } else {
            median_recv = (valid_recv[mi - 1] + valid_recv[mi]) / 2;
          }
        }
        if (mi = valid_send.size() / 2, mi != 0) {
          sort(valid_send.begin(), valid_send.end());
          if (valid_send.size() % 2) {
            median_send = valid_send[mi];
          } else {
            median_send = (valid_send[mi - 1] + valid_send[mi]) / 2;
          }
        }
      }
      usage_file << max_conn << "\t" << median_recv << "\t" << median_send << endl;
    }

    usage_file.close();
    interval_file.close();
  } // for each log file

  cpu_file.close();
  net_file.close();
}
