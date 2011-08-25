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
    str_buf << "SR-" << task_len[i] << "-ideal.in";
    ofstream ideal_file;
    ideal_file.open(str_buf.str().c_str());
    if (ideal_file.fail()) {
      cerr << "Failed to create file:" << str_buf.str() << endl;
    } else ideal_file << "# NumReturn\tSeqExec\tParExec" << endl;

    for (int r = 1; r <= MAX_RETURN; ++r) {
      double task_time = task_len[i];
      ideal_file << r << '\t';
      ideal_file << task_time * (r + 1) / (r * 2) << '\t';
      ideal_file << task_time / r << endl;
    }

    ideal_file.close();
  }
}
