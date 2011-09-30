#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define EB_PORT 3100
#define TB_PORT 3000

#define EB_USAGE usage1
#define TB_USAGE usage2

#define LOG_FILE "eva-sr.log"
#define CPU_FILE "cpu-usage.csv"

#define SKIP_COLUMN_NUM 3 // count of columns before interval in log file
#define NUM_CORES 24

using namespace std;

int main() {
  ifstream sr_log;
  sr_log.open(LOG_FILE);
  if (sr_log.fail()) {
    cerr << "No log of sequential requests (named 'SR.log') is found." << endl;
    return -1;
  }

  ifstream cpu_file;
  cpu_file.open(CPU_FILE);
  const bool is_cpu = !cpu_file.fail();
  char c;
  string token;
  if (is_cpu) {
    while (c = cpu_file.peek(), c < '0' || c > '9') {
      getline(cpu_file, token); // read in comments
    }
  }
  long long cur_time_cpu;
  cpu_file >> cur_time_cpu;
    
  while (sr_log >> token) {
    if (token != "SR") continue;
    // Abstract execution mode
    string exec_mode;
    sr_log >> exec_mode;
    if (exec_mode == "SequentialExecute") {
      exec_mode = "SE";
    } else if (exec_mode == "ParallelExecute") {
      exec_mode = "PE";
    } else {
      cerr << "Wrong excecution mode: " << exec_mode << endl;
      return -1;
    }
    // Abstract port number
    while(sr_log >> c, c != ':');
    int port_num;
    string impl_type;
    sr_log >> port_num;
    if (port_num == TB_PORT) {
      impl_type = "TB";
    } else if (port_num == EB_PORT) {
      impl_type = "EB";
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
    
    long long begin_time, end_time;
    int cur_usage, usage1, usage2;

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
            cpu_file >> usage1 >> usage2;
            if (port_num == TB_PORT) {
              cur_usage = usage2; //TB_USAGE;
            } else if (port_num == EB_PORT) {
              cur_usage = usage1; // EB_USAGE;
            }
            if (cur_usage > 3) {
              ++valid_cnt;
              cpu_usage += cur_usage;
            }
          } else if (cur_time_cpu < begin_time) {
            cpu_file >> usage1 >> usage2;
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
