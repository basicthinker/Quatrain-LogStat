#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define SECOND 1000 // ms

using namespace std;

int main() {
  if (!freopen("file.list", "r", stdin)) {
    cout << "Please list target log files and save their names in a file 'file.list'." << endl;
    return 1;
  }
  string file_name;
  vector<string> file_names;
  while (cin >> file_name)
    file_names.push_back(file_name);

  ofstream check_file;
  check_file.open("check.stat");

  for (vector<string>::iterator it = file_names.begin(); it < file_names.end(); ++it) {
    ifstream log_file;
    log_file.open(it->c_str());

    ofstream latency_file;
    latency_file.open((file_name + ".latency").c_str());

    ofstream interval_file;
    interval_file.open((file_name + ".interval").c_str());

    double time;
    int task_time;
    int rtn_cnt;
    char type;
    string name;

    log_file >> time;
    while (log_file >> name >> task_time >> rtn_cnt) {

      vector<int> req_cnt_ps(10, 0); // number of requests per second
      vector<double> rply_cmlt(rtn_cnt, 0); // total time of replies
      vector<double> rply_sq_cmlt(rtn_cnt, 0); // total squared time of replies
      vector<int> rply_cnt(rtn_cnt, 0); // number of replies
      vector<double> begin_time(rtn_cnt, 1.7e+308); // time of first request
      vector<double> end_time(rtn_cnt, 0); // time of last reply

      int rtn_num;
      while (log_file >> time && time != -1) { // until next case begins with -1
        log_file >> type >> rtn_num; // input

        if (type == 'R') {
          /* Request's log record */
          if (time < begin_time[rtn_num-1])
            begin_time[rtn_num-1] = time;
          else if (time > end_time[rtn_num-1])
            end_time[rtn_num-1] = time;

          int index = (time - begin_time[0]) / SECOND;
          if (index >= req_cnt_ps.size()) req_cnt_ps.resize(index + 1, 0);
          req_cnt_ps[index]++; // calculate requests per second
        } else if (type == 'L') {
          /* Reply's log record */
          rply_cmlt[rtn_num-1] += time;
          rply_sq_cmlt[rtn_num-1] += pow(time, 2);
          rply_cnt[rtn_num-1]++;
        }
      } // while for each log record
      
      /* Print check file (overall info) */
      check_file << name << " for " << task_time << " ms" << endl;
      check_file << "requests each second:" << endl;
      int req_cnt = 0; // total number of requests
      int zero_cnt = 0; // number of seconds with zero requests
      for (vector<int>::iterator it = req_cnt_ps.begin(); it < req_cnt_ps.end(); ++it) {
        check_file << "\t" << *it;
        req_cnt += *it;
        if (*it == 0) ++zero_cnt; 
      }
      check_file << endl;

      check_file << "for any return number:\t" << (double)req_cnt / rtn_cnt;
      check_file << "\t" << (double)req_cnt_ps.size() / rtn_cnt << " s";
      check_file << "\t" << (double)req_cnt / (req_cnt_ps.size() - zero_cnt) << " rps" << endl;

      /* Print data file (for each return number) */
      vector<double> avg(rtn_cnt);
      latency_file << task_time;
      for (int i = 0; i < rtn_cnt; ++i) {
        avg[i] = rply_cmlt[i] / rply_cnt[i];
        latency_file << "\t" << avg[i];
      }
      latency_file << endl;

      for (int i = 0; i < rtn_cnt; ++i) {
        double s = sqrt((rply_sq_cmlt[i] + avg[i] * (rply_cnt[i] * avg[i] - 2 * rply_cmlt[i])) / (rply_cnt[i] - 1));
        latency_file << "\t" << s; // / sqrt((double)rply_cnt[i]);
      }
      latency_file << endl;
    
      /* Print input file for usage analysis */
      interval_file << fixed;
      interval_file.precision(0);
      for (int i = 0; i < rtn_cnt; ++i) {
        interval_file << task_time << "\t" << i + 1 << "\t";
        interval_file << begin_time[i] << "\t" << end_time[i] << endl;
      }
    } // while for each eva case

    log_file.close();
    latency_file.close();
    interval_file.close();
  } // for each file

  check_file.close();

  return 0;
}
