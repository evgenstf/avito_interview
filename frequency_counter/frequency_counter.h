#pragma once

#include <unordered_map>
#include <string>
#include <vector>

typedef std::unordered_map<std::string, int> FrequencyStatistics ;

class FrequencyCounter {
public:
  const FrequencyStatistics& statistics() const;
  std::vector<std::pair<std::string, int>> build_sorted_statistics_vector() const;

  void add_text(const std::string& text);

private:
  FrequencyStatistics statistics_;
};
