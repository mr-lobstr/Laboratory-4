#include <iostream>
#include <random>
#include <vector>
#include <cstdint>
#include <algorithm>
using namespace std;

using Alg_type = bool (*) (int32_t, vector<bool>, vector<bool>);

bool play_game(Alg_type a1, Alg_type a2, int num_rounds)
{
    int score1 = 0;
    int score2 = 0;

    vector<bool> self_choices1;
    vector<bool> self_choices2;
    vector<bool> enemy_choices1;
    vector<bool> enemy_choices2;

    for (int i = 0; i < num_rounds; ++i)
    {
        bool choice1 = a1(i, self_choices1, enemy_choices1);
        bool choice2 = a2(i, self_choices2, enemy_choices2);

        self_choices1.push_back(choice1);
        self_choices2.push_back(choice2);
        enemy_choices1.push_back(choice2);
        enemy_choices2.push_back(choice1);

        if (choice1 == choice2)
        {
            score1 += (choice1 ? 24 : 4);
            score2 += (choice1 ? 24 : 4);
        }
        else
        {
            (choice1 ? score2 : score1) += 20;
        }
    }
    
    return score1 > score2;
}

bool alg1(int32_t round_number, vector<bool> self_choices, vector<bool> enemy_choices)
{
    if (round_number == 0)
        return true;

    return enemy_choices[round_number - 1];
}

bool alg2(int32_t round_number, vector<bool> self_choices, vector<bool> enemy_choices)
{
    return false;
}

bool alg3(int32_t round_number, vector<bool> self_choices, vector<bool> enemy_choices)
{
    bool anyBetrayed = any_of(enemy_choices.begin(), enemy_choices.end(), [] (bool b) {
        return b;
    });
    
    return not anyBetrayed;
}

int main() {
    // Запустить игру
    bool res1 = play_game(alg1, alg2, 100);
    bool res2 = play_game(alg1, alg3, 100);
    bool res3 = play_game(alg2, alg3, 100);

    cout << "Первый бой выиграл " << (res1 ? "alg1" : "alg2") << endl
         << "Второй бой выиграл " << (res2 ? "alg1" : "alg3") << endl
         << "Третий бой выиграл " << (res3 ? "alg2" : "alg3") << endl;
}