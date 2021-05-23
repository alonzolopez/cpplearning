#include <iostream>

struct Advertising
{
    int ads_viewed{};
    double percent_ads_clicked{}; // a percentage
    double earnings_per_ad{};
};

void printValuesAndCalculate(Advertising advertising)
{
    std::cout << "Ads shown to readers: " << advertising.ads_viewed << '\n';
    std::cout << "Percentage of ads clicked on by readers: " << advertising.percent_ads_clicked << '\n';
    std::cout << "Average dollar amount earned from each ad clicked: " << advertising.earnings_per_ad << '\n';

    std::cout << "Earnings today (dollars): " << advertising.ads_viewed * advertising.percent_ads_clicked * advertising.earnings_per_ad << '\n';
}

int main()
{
    Advertising adv{};

    std::cout << "Enter the number of ads shown to readers: ";
    std::cin >> adv.ads_viewed;

    std::cout << "Enter the percentage of ads clicked on by users: ";
    std::cin >> adv.percent_ads_clicked;

    std::cout << "Enter the average dollar amount earned from each ad clicked: ";
    std::cin >> adv.earnings_per_ad;
    std::cout << '\n';

    printValuesAndCalculate(adv);


    return 0;
}