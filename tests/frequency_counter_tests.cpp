#include "../frequency_counter/frequency_counter.h"

using namespace std;

#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <unordered_set>


namespace {

void check_statistics_for_text(string text, vector<pair<string, int>> expeted_statistics) {
  FrequencyCounter counter;
  counter.add_text(text);

  auto statistics = counter.build_sorted_statistics_vector();
  EXPECT_THAT(statistics, testing::ContainerEq(expeted_statistics));
}

}

TEST(FrequencyCounter, OneWord) {
  check_statistics_for_text("word", {{"word", 1}});
}

TEST(FrequencyCounter, DifferentCaseWord) {
  check_statistics_for_text("word WoRd", {{"word", 2}});
}


TEST(FrequencyCounter, CommaSeparatedWord) {
  check_statistics_for_text("word,WoRd", {{"word", 2}});
}


TEST(FrequencyCounter, SeveralWords) {
  check_statistics_for_text(
    "One two, three. \n\n four Four FiVe5five_FIVE",
    {
      {"five", 3},
      {"four", 2},
      {"one", 1},
      {"three", 1},
      {"two", 1},
    }
  );
}


TEST(FrequencyCounter, SomeText) {
  check_statistics_for_text(
    "The time has come, the Walrus said, to talk of many things...",
    {
      {"the", 2},
      {"come", 1},
      {"has", 1},
      {"many", 1},
      {"of", 1},
      {"said", 1},
      {"talk", 1},
      {"things", 1},
      {"time", 1},
      {"to", 1},
      {"walrus", 1}
    }
  );
}


int main(int argc, char** argv) {
   ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

