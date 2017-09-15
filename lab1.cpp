/**
 * @file lab1.cpp
 * @author Troy Dowling`
 * @Date   9/13/2017
 * @version 1.0
 * @section DESCRIPTION Phone call billing calculator
 */
// I declare that this assignment is my own work and that I have correctly
// acknowledged the work of others.  I acknowledged that I have read and
// following the Academic Honesty and Integrity related policies as
// outlined in the syllabus.
//
// Troy Dowling, 2017-09-13
//
// 301216033

// Define call time periods in 24h (Prime time, off-peak, and weekend).
#define T_PRIME_S 8     // Prime-time starts at 08:00
#define T_PRIME_P 18    // Ends at 18:00
// Define call time period rates (cents/minute).
const double R_PRIME = 0.40;
const double R_OFFPEAK = 0.25;
const double R_WEEKEND = 0.15;

#include <iostream>     // Basic IO
#include <iomanip>      // setprecision() and fixed()
#include <cstdlib>      // atoi()
#include <vector>       // Vectors of call prices
#include <map>          // Map between day string and weekend membership
#include <string>       // Strings
#include <algorithm>    // transform() for down-casing

using namespace std;    // Given in template, so don't remove I guess.

// The total bill the customer receives.
typedef struct Bill{
    double totalCost;           // What the customer is required to pay
    int numCalls;               // The number of individual calls made
    vector<double> callCosts;   // A list of what each call cost
} Bill;

// An individual call made by the customer.
typedef struct Call{
    int duration;               // The duration of the call made
    double rate;                // The rate at which this call was billed
} Call;
	
int main()
{
    // Create a running bill for the customer.
    Bill bill = {0, 0};

    // Map human-readable weekdays to billing booleans.
    map <string, bool> billingDays;
    billingDays["mo"] = false;
    billingDays["tu"] = false;
    billingDays["we"] = false;
    billingDays["th"] = false;
    billingDays["fr"] = false;
    billingDays["sa"] = true;
    billingDays["su"] = true;

    string termStr = "quit";
    string day;
    string time;
    int duration;
    cout << "Enter \"" << termStr <<
        "\" for the day of week to terminate loop." << endl;
    do
    {
        // Prompt user for WK, 24:00, and int(duration).
        cout << endl << "Day of week (or \"quit\"): " << flush;
        cin >> day;
        // First transform the string to lower case
        transform(day.begin(), day.end(), day.begin(), ::tolower);
        if(day.compare(termStr) == 0)
            break;
        cout << "Time: " << flush;
        cin >> time;
        cout << "Duration: " << flush;
        cin >> duration;

        // Extract hour from time HH:xx.
        int index = time.find(":");
        string hour = time.substr(0, index);

        // Declare Call struct.
        Call c;

        // Set the call's billing rate depending on the day and time.
        // Map lookup for weekend membership boolean.
        if(billingDays[day])
            // Weekend
            c.rate = R_WEEKEND;
        else
        {
            // Weekday
            // Check if it's primetime or not.
            int ih = atoi(hour.c_str());
            if(ih < T_PRIME_S || ih > T_PRIME_P)
                c.rate = R_OFFPEAK;
            else
                c.rate = R_PRIME;
        }

        // Set the call duration.
        c.duration = duration;

        // Calculate cost of this call.
        double charge = c.rate * c.duration;

        // Add it to the customer's bill
        bill.totalCost += charge;
        bill.numCalls++;
        bill.callCosts.push_back(charge);

    } while(true); // Break condition handled during day input

    cout << fixed << setprecision(2);   // Use fixed-point two decimal places
    cout << endl << "Total bill: $" << bill.totalCost << endl;
    cout << "List of call charges:" << endl;
    for(unsigned int i=0; i < bill.callCosts.size(); i++)
        cout << "\t" << i+1 << ") $" << bill.callCosts[i] << endl;
}

