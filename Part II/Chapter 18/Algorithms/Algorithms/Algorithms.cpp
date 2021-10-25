#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

// ==== NON-MODIFYING SEQUENCE OPERATIONS ====

// Checks if all of the half-opened range returns true
TEST_CASE("all_of") {
    vector<string> words{ "Auntie", "Anne's", "alligator" };
    const auto starts_with_a =
        [](const auto& word) {
            if (word.empty()) return false;
            return word[0] == 'A' || word[0] == 'a';
        };
    REQUIRE(all_of(words.cbegin(), words.cend(), starts_with_a));
    const auto has_length_six = [](const auto& word) {
        return word.length() == 6;
    };
    REQUIRE_FALSE(all_of(words.cbegin(), words.cend(), has_length_six));
}

// Checks if any of the half-opened range returns true
TEST_CASE("any_of") {
    vector<string> words{ "Barber", "baby", "bubbles" };
    const auto contains_bar = [](const auto& word) {
        return word.find("Bar") != string::npos;
    };
    REQUIRE(any_of(words.cbegin(), words.cend(), contains_bar));

    const auto is_empty = [](const auto& word) { return word.empty(); };
    REQUIRE_FALSE(any_of(words.cbegin(), words.cend(), is_empty));
}

// Checks if none of the half-opened range returns true
TEST_CASE("none_of") {
    vector<string> words{ "Camel", "on", "the", "ceiling" };
    const auto is_hump_day = [](const auto& word) {
        return word == "hump day";
    };
    REQUIRE(none_of(words.cbegin(), words.cend(), is_hump_day));

    const auto is_definite_article = [](const auto& word) {
        return word == "the" || word == "ye";
    };
    REQUIRE_FALSE(none_of(words.cbegin(), words.cend(), is_definite_article));
}

// a higher level of abstraction for each loop
TEST_CASE("for_each") {
    vector<string> words{ "David", "Donald", "Doo" };
    size_t number_of_Ds{};
    const auto count_Ds = [&number_of_Ds](const auto& word) {
        if (word.empty()) return;
        if (word[0] == 'D') ++number_of_Ds;
    };
    for_each(words.cbegin(), words.cend(), count_Ds);
    REQUIRE(3 == number_of_Ds);
}

// dereferences the iterators, then does the same as a for each loop
TEST_CASE("for_each_n") {
    vector<string> words{ "ear", "egg", "elephant" };
    size_t characters{};
    const auto count_characters = [&characters](const auto& word) {
        characters += word.size();
    };
    // apply count_characters to words.cbegin() for words.size() elements.
    for_each_n(words.cbegin(), words.size(), count_characters);
    REQUIRE(characters == 14);
}

// DIFFERENT FROM std::string::find, DO NOT CONFUSE THE TWO  
// find: returns pointer to exact match
// find_if: returns pointer to whatever returns true first
// find_if_not: returns pointer to whatever returns false first
// all return ipt_end otherwise
TEST_CASE("find find_if find_if_not") {
    vector<string> words{ "fiffer", "feffer", "feff" };
    // find whatever matches
    const auto find_result = find(words.cbegin(), words.cend(), "feff");
    REQUIRE(*find_result == words.back());

    const auto defends_digital_privacy = [](const auto& word) {
        return string::npos != word.find("eff");
    };
    // finds first that's true
    const auto find_if_result = find_if(words.cbegin(), words.cend(), defends_digital_privacy);
    REQUIRE(*find_if_result == "feffer");
    
    // finds first that's false
    const auto find_if_not_result = find_if_not(words.cbegin(), words.cend(), defends_digital_privacy);
    REQUIRE(*find_if_not_result == words.front());
}

// returns pointer to last instance of sequence, returns fwd_end1 otherwise
TEST_CASE("find_end") {
    vector<string> words1{ "Goat", "girl", "googoo", "goggles" };
    vector<string> words2{ "girl", "googoo" };
    const auto find_end_result1 = find_end(words1.cbegin(), words1.cend(),
        words2.cbegin(), words2.cend());
    REQUIRE(*find_end_result1 == words1[1]);

    const auto has_length = [](const auto& word, const auto& len) {
        return word.length() == len;
    };
    vector<size_t> sizes{ 4, 6 };
    // which words in words1 match the length of the sizes, in order
    const auto find_end_result2 = find_end(words1.cbegin(), words1.cend(),
        sizes.cbegin(), sizes.cend(), has_length);
    REQUIRE(*find_end_result2 == words1[1]); // "Goat"[4] ["girl"][4] "googoo"[6] "goggles"[7]
}

// finds first occurence in sequence 1 that is equal to something in sequence 2
// returns ipt_end1 otherwise, but if it is a ForwardIterator, it just returns a ForwardIterator
TEST_CASE("find_first_of") {
    vector<string> words{ "Hen", "in", "a", "hat" };
    vector<string> indefinite_articles{ "a", "an" };

    const auto find_first_of_result = find_first_of(words.cbegin(), words.cend(),
        indefinite_articles.cbegin(), indefinite_articles.cend());

    REQUIRE(*find_first_of_result == words[2]);
}

// finds the first repeat in a sequence, returns fwd_end otherwise
TEST_CASE("adjacent_find") {
    vector<string> words{ "Icabod", "is", "itchy" };
    const auto first_letters_match = [](const auto& word1, const auto& word2) {
        if (word1.empty() || word2.empty()) return false;
        return word1.front() == word2.front();
    };

    const auto adjacent_find_result = adjacent_find(words.cbegin(), words.cend(), first_letters_match);
    REQUIRE(*adjacent_find_result == words[1]); // [1] because Icabod is capitalized
}

// count: counts elements matching a criteria
// count_if: the same, but for more complicated predicates
TEST_CASE("count") {
    vector<string> words{ "jelly", "jar", "and", "jam" };
    const auto n_ands = count(words.cbegin(), words.cend(), "and");
    REQUIRE(n_ands == 1);

    const auto contains_a = [](const auto& word) {
        return word.find('a') != string::npos;
    };
    const auto count_if_result = count_if(words.cbegin(), words.cend(), contains_a);
}

// finds first mismatch in 2 sequences
// returns a pair of iterators, the first to the matching element in sequence 1
// the second being the matching element in sequence 2, other wise,
// a pair of iterators pointing to the ends of each sequence
TEST_CASE("mismatch") {
    vector<string> words1{ "Kitten", "Kangaroo", "Kick" };
    vector<string> words2{ "Kitten", "bandicoot", "roundhouse" };
    const auto mismatch_result1 = mismatch(words1.cbegin(), words1.cend(), words2.cbegin());

    REQUIRE(*mismatch_result1.first == "Kangaroo");
    REQUIRE(*mismatch_result1.second == "bandicoot");

    const auto second_letter_matches = [](const auto& word1, const auto& word2) {
        if (word1.size() < 2 || word2.size() < 2) return false;
        return word1[1] == word2[1];
    };
    const auto mismatch_result2 = mismatch(words1.cbegin(), words1.cend(),
        words2.cbegin(), second_letter_matches); // predicate is optional
    REQUIRE(*mismatch_result2.first == "Kick");
    REQUIRE(*mismatch_result2.second == "roundhouse");
}

// checks whether the 2 sequences are equal
TEST_CASE("equal") {
    vector<string> words1{ "Lazy", "lion", "licks" };
    vector<string> words2{ "Lazy", "lion", "kicks" };
    const auto equal_results1 = equal(words1.cbegin(), words1.cend(), words2.cbegin());
    REQUIRE_FALSE(equal_results1);

    words2[2] = words1[2];
    const auto equal_results2 = equal(words1.cbegin(), words1.cend(), words2.cbegin());
    REQUIRE(equal_results2);
}

// 10/25/2021
// the same as equal, except order of the elements does not matter
TEST_CASE("is_permutation") {
    vector<string> words1{ "moonlight", "mighty", "nice" };
    vector<string> words2{ "nice", "moonlight", "mighty" };
    const auto result = is_permutation(words1.cbegin(), words1.cend(), words2.cbegin());
    
    REQUIRE(result);
}

// returns iterator where sequence 2 begins in sequence 1, otherwise, an ipt_begin2 iterator.
TEST_CASE("search") {
    vector<string> words1{ "Nine", "new", "neckties", "and", "a", "nightshirt" };
    vector<string> words2{ "and", "a", "nightshirt" };
    const auto search_result1 = search(words1.cbegin(), words1.cend(),
        words2.cbegin(), words2.cend());
    REQUIRE(*search_result1 == "and"); // returns pointer to beginning of subsequence

    vector<string> words3{ "and", "a", "nightpant" };
    const auto search_result2 = search(words1.cbegin(), words1.cend(),
        words3.cbegin(), words3.cend());
    REQUIRE(search_result2 == words1.cend());
}

// returns iterator where subsequence is found n times consecutively, 
TEST_CASE("search_n") {
    vector<string> words{ "an", "orange", "owl", "owl", "owl", "today" };
    const auto result = search_n(words.cbegin(), words.cend(), 3, "owl");
    REQUIRE(result == words.cbegin() + 2);
}

// ==== MUTATING SEQUENCE OPERATIONS ====

// copies sequence 2 into sequence 1
// they cannot overlap, meaning what you are copying can not be the same as where you are copying to
// unless the beginning 
TEST_CASE("copy") {
    vector<string> words1{ "and", "prosper" };
    vector<string> words2{ "Live", "long" };
    // back_inserter pushes the copied stuff to the back of words2
    copy(words1.cbegin(), words1.cend(), back_inserter(words2));
    REQUIRE(words2 == vector<string>{ "Live", "long", "and", "prosper" });
}

// does the same, except it copies n many words from sequence 1 to sequence 2
TEST_CASE("copy_n") {
    vector<string> words1{ "on", "the", "wind" };
    vector<string> words2{ "I'm", "a", "leaf" };
    copy_n(words1.cbegin(), words1.size(), back_inserter(words2));
    REQUIRE(words2 == vector<string>{ "I'm", "a", "leaf", "on", "the", "wind" });
}

// swaps two sequences
TEST_CASE("swap_ranges") {
    vector<string> words1{ "The", "king", "is", "dead." };
    vector<string> words2{ "Long", "live", "the", "king." };
    swap_ranges(words1.begin(), words1.end(), words2.begin());
    REQUIRE(words1 == vector<string>{ "Long", "live", "the", "king." });
    REQUIRE(words2 == vector<string>{ "The", "king", "is", "dead." });
}

// modifies the elements of a sequence and writes them into another
TEST_CASE("transform") {
    vector<unsigned short> nums1{ 1, 2, 3, 4 };
    vector<unsigned short> result1;
    auto increment = [](size_t x) {
        return ++x;
    };
    transform(nums1.begin(), nums1.end(), back_inserter(result1), increment);
    REQUIRE(result1 == vector<unsigned short>)
}
// 10/25/2021