#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#define CASE_CNT 2
#define GRP_CNT 3
#define MAX_RET 24

using namespace std;

int main() {
  ifstream file_list;
  file_list.open("file.list");
  if (file_list.fail()) {
    cerr << "Failed to open file 'file.list'." << endl;
  }

  string file_name;
  while (file_list >> file_name) {
    ifstream raw;
    raw.open((file_name + ".raw-usage").c_str());
    if (raw.fail()) {
      cerr << "Failed to open file '" << file_name << ".raw-usage'." << endl;
      continue;
    }

    ofstream usage;
    usage.open((file_name + ".usage").c_str());
    if (usage.fail()) {
      cerr << "Failed to open file '" << file_name << ".usage'." << endl;
      continue;
    }

    double cpu[CASE_CNT][MAX_RET][GRP_CNT+1];
    int conn[CASE_CNT][MAX_RET][GRP_CNT+1];
    int task, ret, recv, send;
    string line;
    while (raw.peek() < '0' || raw.peek() > '9') {
      getline(raw, line); // read in comments
    }

    // Input raw usage data
    for (int g = 0; g < GRP_CNT; ++g) {
      for (int c = 0; c < CASE_CNT; ++c) {
        for (int r = 0; r < MAX_RET; ++r) {
          raw >> task >> ret >> cpu[c][r][g] >> conn[c][r][g];
          getline(raw, line);
        }
      }
    }

    // Calculate median values
    int mi = GRP_CNT / 2;
    for (int c = 0; c < CASE_CNT; ++c) {
      for (int r = 0; r < MAX_RET; ++r) {
        sort(cpu[c][r], cpu[c][r] + GRP_CNT);
        cpu[c][r][GRP_CNT] = cpu[c][r][mi];
        sort(conn[c][r], conn[c][r] + GRP_CNT);
        conn[c][r][GRP_CNT] = conn[c][r][mi];
      }
    }

    // Output
    for (int r = 0; r < MAX_RET; ++r) {
      usage << r + 1 << '\t';
      for (int c = 0; c < CASE_CNT; ++c) {
        usage << cpu[c][r][GRP_CNT] << '\t';
        usage << conn[c][r][GRP_CNT] << '\t';
      }
      usage << endl;
    }

    raw.close();
    usage.close();
  }

  file_list.close();
}
