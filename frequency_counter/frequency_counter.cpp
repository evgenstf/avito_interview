#include "frequency_counter.h"

#include <algorithm>
#include <cctype>
#include <vector>

using namespace std;

namespace {

vector<string> extract_words(const string& text) {
  vector<string> words;
  size_t index = 0;
  while (index < text.size()) {
    string word;
    while (index < text.size() && isalpha(text[index])) {
      word.push_back(text[index++]);
    }
    while (index < text.size() && !isalpha(text[index])) {
      ++index;
    }
    if (!word.empty()) {
      words.emplace_back(move(word));
    }
  }
  return words;
}

string to_lower_word(string&& word) {
  for_each(word.begin(), word.end(), [](char& c){ c = tolower(c); });
  return word;
}

}

const FrequencyStatistics& FrequencyCounter::statistics() const {
  return statistics_;
}

void FrequencyCounter::add_text(const string& text) {
  auto words = extract_words(text);

  for (auto& word : words) {
    ++statistics_[to_lower_word(move(word))];
  }
}

std::vector<std::pair<std::string, int>> FrequencyCounter::build_sorted_statistics_vector() const {
  vector<pair<string, int>> words_with_frequency;

  for (const auto& [word, frequency] : statistics_) {
    words_with_frequency.emplace_back(word, frequency);
  }

  sort(
      words_with_frequency.begin(),
      words_with_frequency.end(),
      [](const auto& lhs, const auto& rhs){
        return (
            lhs.second > rhs.second ||
            (lhs.second == rhs.second && lhs.first < rhs.first)
        );
      }
  );

  return words_with_frequency;
}
