#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define EB_PORT 3000
#define TB_PORT 3100

#define SKIP_COLUMN_NUM 3
#define NUM_CORES 24

using namespace std;

int main() {
  ifstream sr_log;
  sr_log.open("SR.log");
  if (sr_log.fail()) {
    cerr << "No log of sequential requests (named 'SR.log') is found." << endl;
    return -1;
  }

  ifstream cpu_file;
  cpu_file.open("cpu-usage.csv");
  const bool is_cpu = !cpu_file.fail();
  char c;
  string token;
  if (is_cpu) {
    while (c = cpu_file.peek(), c < '0' || c > '9') {
      getline(cpu_file, token); // read in comments
    }
  }
    
  while (sr_log >> token) {
    if (token != "SR") continue;
    // Abstract execution mode
    string exec_mode;
    sr_log >> exec_mode;
    
    // Abstract port number
    while(sr_log >> c, c != ':');
    int port_num;
    string impl_type;
    sr_log >> port_num;
    if (port_num == 3000) {
      impl_type = "EB";
    } else if (port_num == 3100) {
      impl_type = "TBB";
    } else if (port_num == 3200) {
      impl_type = "TB";
    }
    // Abstract task time
    while (sr_log >> c, c != '='); // reach repeat count
    while (sr_log >> c, c != '='); // reach task time
    string task_time;
    sr_log >> task_time;
    
    // Compose output file name
    ofstream fout;
    string file_name;
    file_name.append("SR").append(exec_mode).append("-").append(impl_type);
    file_name.append(task_time).append(".in");
    fout.open(file_name.c_str());

    getline(sr_log, token);
    while (c = sr_log.peek(), c < '0' || c > '9') {
      getline(sr_log, token);
    } // reach the end of comments
    
    long long begin_time, end_time, cur_time_cpu;
    int usage1, usage2, usage3;

    cpu_file >> cur_time_cpu;

    while (c = sr_log.peek(), c >= '0' && c <= '9') {
      for (int i = 0; i < SKIP_COLUMN_NUM; ++i) {
        sr_log >> token;
        fout << token << '\t';
      }
      sr_log >> begin_time >> end_time;
      getline(sr_log, token); // eat the rest of current line

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
      fout << cpu_usage << token << endl;
    }
    fout.close();
  } // for each case

  sr_log.close();
  cpu_file.close();
}
