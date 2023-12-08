#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
using namespace std;
unordered_map<char, uint> card;
unordered_map<char, uint> getMapOfCard()
{
    unordered_map<char, uint> card;
    card['2'] = 2;
    card['3'] = 3;
    card['4'] = 4;
    card['5'] = 5;
    card['6'] = 6;
    card['7'] = 7;
    card['8'] = 8;
    card['9'] = 9;
    card['T'] = 10;
    card['J'] = 11;
    card['Q'] = 12;
    card['K'] = 13;
    card['A'] = 14;
    return card;
}
enum class Combinations{kiker= 1, pair = 2, twoPairs = 3, set = 4, fullHouse = 5, four = 6, five = 7};
auto compareHighCards(const char& card1, const char& card2)
{
    if(card1 != card2)
    {
        return card[card1] > card[card2];
    }
    
    return false;
}
auto maxSameCardsInHand(unordered_map<char, int>& cardsInHand)
{
    return (*max_element(begin(cardsInHand), end(cardsInHand), [](const auto& card1, const auto& card2){
        return card1.second < card2.second;
    }));
}
auto getCardFrequency(const string& cards)
{
    unordered_map<char, int> cardsInHand;
    for(auto& elem : cards)
    {
        cardsInHand[elem]++;
    }
    return cardsInHand;
}
auto compMm(const pair<int, char>& card1, const pair<int, char>& card2)
{
    if(card1.first != card2.first)
    {
        return card1.first > card2.first;
    }
    else
    {
        return compareHighCards(card1.second, card2.second);
    }
    return false;
}
auto getCardFrequencyMap(const unordered_map<char, int>& frequency)
{
    multimap<pair<int, char>, char, decltype(compMm)*> orderedHand(compMm);
    for(const auto& elem : frequency)
    {
        orderedHand.insert({{elem.second, elem.first}, elem.first});
    }
    return orderedHand;
}
Combinations sortHands(string& cards)
{
    unordered_map<char, int> cardsInHand = getCardFrequency(cards);
    auto maxCombination = maxSameCardsInHand(cardsInHand);
    // cout << " " << maxCombination.second << " ";
    Combinations combinations;
    switch(maxCombination.second)
    {
        case 1:
            combinations = Combinations::kiker; 
            break;
        case 2:
            cardsInHand.erase(maxCombination.first);
            if(maxSameCardsInHand(cardsInHand).second == 2)
            {
                combinations = Combinations::twoPairs;
            }
            else
            {
                combinations = Combinations::pair;
            }
            break;
        case 3:
            cardsInHand.erase(maxCombination.first);
            if(maxSameCardsInHand(cardsInHand).second == 2)
            {
                combinations = Combinations::fullHouse;
            }
            else
            {
                combinations = Combinations::set;
            }
            break;
        case 4:
            combinations = Combinations::four;
            break;
        case 5:
            combinations = Combinations::five;
            break;
    }
    // cout << cards << " " << static_cast<std::underlying_type<Combinations>::type>(combinations) << endl;
    return combinations;
}
auto sortCombination(string& hand1)
{
    const auto& cardFrequency1 = getCardFrequency(hand1);
    const auto& frequencyMap1 = getCardFrequencyMap(cardFrequency1);
    // cout << endl;
    // cout << hand1 << " " << endl;
    int k = 0;
    for(const auto& elem : frequencyMap1)
    {
        // cout << elem.first.first << " " << elem.second << " "; 

        for(int i = 0; i < elem.first.first; i++)
        {
            // cout << elem.first.first << " " << elem.second << " "; 
            hand1[k] = elem.first.second;
            k++;
            // cout << " " << newHand << " ";
        }
    }
    // cout << newHand << " s" << endl;
    // cout << endl;
    return ;
}
auto comparePair(const string& hand1, const string& hand2)
{
    const auto& cardFrequency1 = getCardFrequency(hand1);
    const auto& cardFrequency2 = getCardFrequency(hand2); 
    const auto& frequencyMap1 = getCardFrequencyMap(cardFrequency1);
    auto card1It = frequencyMap1.begin();
    const auto& frequencyMap2 = getCardFrequencyMap(cardFrequency2);
    auto card2It = frequencyMap2.begin();

    while(card1It != frequencyMap1.end() && card2It != frequencyMap2.end())
    {
        // cout << card1It->first.first << " it " << card1It->second << endl; 
        // cout << card2It->first.first << " it " << card2It->second << endl; 
        if(card1It->second == card2It->second)
        {
            card1It++;
            card2It++;
        }
        else
        {
            return compareHighCards(card1It->second, card2It->second);
        }
    }
    cout << endl;
    return false;
}

// auto compareCombinations(, )

int main()
{
    string file_path = "input.txt";
    // string file_path = "test_full_house.txt";
    ifstream stream(file_path.c_str());
    card = getMapOfCard();
    string line, hand, bid;
    auto comp = [](const auto& hand1, const auto& hand2){
       if(hand1.second == hand2.second)
       {
            // return !comparePair(hand1.first, hand2.first);
            for(int i = 0; hand1.first.size(); i++)    
            {
                if(hand1.first[i] != hand2.first[i])
                {
                    return !compareHighCards(hand1.first[i], hand2.first[i]);
                }
            }
       }
        if(hand1.second < hand2.second)
        {
            return true;
        }
        return false;
    };
    map<pair<string, int>, int, decltype(comp)> sortingHands(comp);
    while(getline(stream, line)) 
    {
        auto index = line.find(' ');
        auto pair = make_pair<string, int>(line.substr(0, index), stoi(line.substr(index + 1)));

        // sort(pair.first.begin(), pair.first.end(), compareHighCards);
        // sortCombination(pair.first);
        auto piarHandCombination = make_pair<string, int>(move(pair.first),  static_cast<int>(sortHands(pair.first)));
        auto res = sortingHands.insert(std::make_pair(piarHandCombination, pair.second));
        // if(res.second)
            // cout << "insetrt ";
        // cout << piarHandCombination.first << " " << piarHandCombination.second << endl;
    }
    long i = 1;
    long res = 0;
    for(auto& elem : sortingHands)
    {
        res += i * elem.second;
        i++;
        cout << elem.first.first << " " << elem.first.second << " " << elem.second << endl;
    }
    cout << res << " " << i - 1 << endl;
    return 0;
}