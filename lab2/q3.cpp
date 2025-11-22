#include <iostream>
using namespace std;

int main() {
    const int candidates = 5;
    int votes[candidates] = {0};
    int totalVoters;

    cout << "Enter total number of voters: ";
    cin >> totalVoters;

    cout << "Enter your vote (1 to 5) for each voter:\n";
    for (int i = 0; i < totalVoters; ++i) {
        int vote;
        cin >> vote;
        if (vote >= 1 && vote <= 5) {
            votes[vote - 1]++;
        } else {
            cout << "Invalid vote. Skipped.\n";
        }
    }

    cout << "\nTotal votes for each candidate:\n";
    for (int i = 0; i < candidates; ++i) {
        cout << "Candidate " << i + 1 << ": " << votes[i] << " votes\n";
    }

    int maxVotes = votes[0];
    int winner = 0;
    for (int i = 1; i < candidates; ++i) {
        if (votes[i] > maxVotes) {
            maxVotes = votes[i];
            winner = i;
        }
    }

    cout << "\nWinner: Candidate " << winner + 1 << " with " << maxVotes << " votes\n";

    return 0;
}
