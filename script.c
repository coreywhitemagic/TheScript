#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

double similarityPercentage(const std::string& s1, const std::string& s2) {
    const size_t len1 = s1.size();
    const size_t len2 = s2.size();

    std::vector<std::vector<int>> dp(len1 + 1, std::vector<int>(len2 + 1));

    for (size_t i = 0; i <= len1; ++i)
        dp[i][0] = i;

    for (size_t j = 0; j <= len2; ++j)
        dp[0][j] = j;

    for (size_t i = 1; i <= len1; ++i) {
        for (size_t j = 1; j <= len2; ++j) {
            dp[i][j] = std::min({
                dp[i - 1][j] + 1,
                dp[i][j - 1] + 1,
                dp[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1)
                });
        }
    }

    int maxLen = std::max(len1, len2);
    double similarity = 100.0 - (static_cast<double>(dp[len1][len2]) / maxLen * 100.0);
    return similarity;
}

int main(int argc, char* argv[]) {

    std::string answersFileName;
    std::cout << std::endl;

    if (argc > 1) {
        answersFileName = argv[1];        
    }
    else {
        std::cout << "Script File: ";        
        std::getline(std::cin, answersFileName);
        std::cout << std::endl;
    }

    ifstream answersFile(answersFileName);
    if (!answersFile) {
        cerr << "Error opening answers file." << endl;
        return 1;
    }

    vector<string> answers;
    string line;
    while (getline(answersFile, line)) {
        answers.push_back(line);
    }
    answersFile.close();

    std::string planet[] = {
      "sun",
      "mercury",
      "venus",
      "earth",
      "mars",
      "jupiter",
      "saturn",
      "uranus",
      "neptune",
      "pluto",
      "full moon",
      "new moon",
      "waxing moon",
      "waning moon",
      "aries",
      "taurus",
      "gemini",
      "cancer",
      "leo",
      "virgo",
      "libra",
      "scorpio",
      "sagittarius",
      "capricorn",
      "aquarius",
      "pisces"
    };

    std::string userAnswer;
    int questionNumber = 0;
    int attempts = 0;
    int planetNumber = 0;

    while (questionNumber < answers.size()) {
        if (planetNumber > 25) {
            planetNumber = 0;
        }
        std::cout << "Line " << questionNumber + 1 << "\n("
            << planet[planetNumber] << ")\n";
        std::getline(std::cin, userAnswer);
        std::cout << std::endl;
        double similarity = similarityPercentage(userAnswer, answers[questionNumber]);
        if (similarity > 65) {
            std::cout << "'"<<answers[questionNumber]<<"'\nCorrect! (" << similarity << "%)\n\n";
            questionNumber++;
            planetNumber++;
        }
        else {
            std::cout << "The correct answer was, '"
                << answers[questionNumber] << "' (" << similarity << "%)\n" <<
                "Starting over.\n\n";
            questionNumber = 0;
            planetNumber = 0;
        }
    }

    std::cout << "You remembered everything!\n";

    return 0;
}
