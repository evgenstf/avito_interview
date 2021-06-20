#include <algorithm>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "frequency_counter/frequency_counter.h"

using namespace std;

int main() {
  string line;

  FrequencyCounter counter;

  while (getline(cin, line)) {
    counter.add_text(line);
  }

  auto statistics = counter.build_sorted_statistics_vector();
  for (const auto& [word, frequency] : statistics) {
    cout << frequency << ' ' << word << endl;
  }
}
