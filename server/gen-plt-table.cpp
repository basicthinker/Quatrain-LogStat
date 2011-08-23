#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

#define CASE_CNT 2
#define GRP_CNT 3
#define MAX_RET 24

using namespace std;

struct Value {
  double mean;
  double stdev;
};

bool compare(const Value& a, const Value& b) {
  return a.mean < b.mean;
}

int main() {
  if (!freopen("file.list", "r", stdin)) {
    cout << "Please list target log files and save their names in a file 'file.list'." << endl;
    return 1;
  }

  string file_name;
  vector<string> file_names;
  while (cin >> file_name)
    file_names.push_back(file_name);

  for (vector<string>::iterator it = file_names.begin(); it < file_names.end(); ++it) {
    ifstream latency_file;
    latency_file.open((*it + ".latency").c_str());
    ofstream table_file;
    table_file.open((*it + ".table").c_str());

    Value value[CASE_CNT][MAX_RET][GRP_CNT+1];
    /* Input */
    int task_time;
    for (int gn = 0; gn < GRP_CNT; ++gn) {
      for (int cn = 0; cn < CASE_CNT; ++cn) {
        latency_file >> task_time;
        for (int rn = 0; rn < MAX_RET; ++rn) {
          latency_file >> value[cn][rn][gn].mean;
        }
        for (int rn = 0; rn < MAX_RET; ++rn) {
          latency_file >> value[cn][rn][gn].stdev;
        }
      }
    }
    /* Calculate */
    int mid = GRP_CNT / 2;
    for (int cn = 0; cn < CASE_CNT; ++cn) {
      for (int rn = 0; rn < MAX_RET; ++rn) {
        sort(value[cn][rn], value[cn][rn]+GRP_CNT, compare);
        value[cn][rn][GRP_CNT] = value[cn][rn][mid];
      }
    }
    /* Output */
    table_file << "# Return number\t[Mean\tStandard deviation]..." << endl;
    for (int rn = 0; rn < MAX_RET; ++rn) {
      table_file << rn + 1 << "\t";
      for (int cn = 0; cn < CASE_CNT; ++cn) {
        table_file << value[cn][rn][GRP_CNT].mean << "\t";
        table_file << value[cn][rn][GRP_CNT].stdev << "\t";
      }
      table_file << endl;
    }
    latency_file.close();
    table_file.close();
  }

  return 0;
}

