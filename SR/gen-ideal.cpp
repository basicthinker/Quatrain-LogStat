#include <iostream>
#include <fstream>
#include <sstream>

#define NUM_TASK 3
#define TASK_LEN {100, 1000, 10000}
#define MAX_RETURN 24

using namespace std;

int task_len[NUM_TASK] = TASK_LEN;

int main() {
  for (int i = 0; i < NUM_TASK; ++i) {
    stringstream str_buf;
    str_buf << "SRSE-" << task_len[i] << "-ideal.in";
    string file_name;
    str_buf >> file_name;
    ofstream se_file;
    se_file.open(file_name.c_str());
    if (se_file.fail()) {
      cerr << "Failed to create file:" << file_name << endl;
    } else se_file << "# NumReturn\tSeqExec" << endl;

    for (int r = 1; r <= MAX_RETURN; ++r) {
      double task_time = task_len[i];
      se_file << r << '\t';
      se_file << task_time * (r + 1) / (r * 2) << endl;
    }

    se_file.close();

    str_buf.clear();
    str_buf << "SRPE-" << task_len[i] << "-ideal.in";
    str_buf >> file_name;
    ofstream pe_file;
    pe_file.open(file_name.c_str());
    if (pe_file.fail()) {
      cerr << "Failed to create file:" << file_name << endl;
    } else pe_file << "# NumReturn\tParExec" << endl;

    for (int r = 1; r <= MAX_RETURN; ++r) {
      double task_time = task_len[i];
      pe_file << r << '\t';
      pe_file << task_time / r << endl;
    }

    pe_file.close();
  }
}
