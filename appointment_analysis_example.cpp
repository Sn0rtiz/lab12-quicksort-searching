/*
 * Course: COEN 2220 - Programming 2
 * Name: [Sebastian Ortiz]
 * Lab: Lab 8 - Big-O / Time Complexity
 * Description: Guided example - compare algorithm work patterns
 * Due date: [11/10/2026]
 */

#include <iostream>
using namespace std;

// Function prototypes let main use these functions before their definitions.
int getAppointmentAt(const int appointmentIds[], int appointmentIndex);
int countLinearComparisons(const int appointmentIds[], int appointmentCount, int targetId);
int countBinaryComparisons(const int appointmentIds[], int appointmentCount, int targetId);
int countPossiblePairs(int appointmentCount);
void fillSortedAppointmentIds(int appointmentIds[], int appointmentCount);

int main()
{
    const int SMALL_COUNT = 50;
    const int MEDIUM_COUNT = 100;
    const int LARGE_COUNT = 200;

    int appointments50[SMALL_COUNT];
    int appointments100[MEDIUM_COUNT];
    int appointments200[LARGE_COUNT];

    // The helper creates ascending IDs so binary search is valid.
    fillSortedAppointmentIds(appointments50, SMALL_COUNT);
    fillSortedAppointmentIds(appointments100, MEDIUM_COUNT);
    fillSortedAppointmentIds(appointments200, LARGE_COUNT);

   //  --- B1: Direct access to one known position ---
    cout << "Appointment ID at a known index for 50 appointments: "
         << getAppointmentAt(appointments50, 25)
         << " (Direct accesses: 1)" << endl;
    cout << "Appointment ID at a known index for 100 appointments: "
         << getAppointmentAt(appointments100, 50)
         << " (Direct accesses: 1)" << endl;
    cout << "Appointment ID at a known index for 200 appointments: "
         << getAppointmentAt(appointments200, 100)
         << " (Direct accesses: 1)" << endl;
    
   //  --- B2: Average linear-search comparisons for ten controlled targets ---
    const int SEARCH_COUNT = 10;

    // Every value below appears in its corresponding ordered appointment list.
    // The values are distributed from the beginning to the end of each list.
    const int searchTargets50[SEARCH_COUNT] =
        {1000, 1008, 1018, 1028, 1038, 1048, 1058, 1068, 1078, 1098};
    const int searchTargets100[SEARCH_COUNT] =
        {1000, 1018, 1038, 1058, 1078, 1098, 1118, 1138, 1158, 1198};
    const int searchTargets200[SEARCH_COUNT] =
        {1000, 1038, 1078, 1118, 1158, 1198, 1238, 1278, 1318, 1398};

    int linearTotal50 = 0;
    int linearTotal100 = 0;
    int linearTotal200 = 0;

    // Use every target once and add its linear-search comparison count.
    for (int query = 0; query < SEARCH_COUNT; query++)
    {
        linearTotal50 += countLinearComparisons(appointments50, SMALL_COUNT,
                                                 searchTargets50[query]);
        linearTotal100 += countLinearComparisons(appointments100, MEDIUM_COUNT,
                                                  searchTargets100[query]);
        linearTotal200 += countLinearComparisons(appointments200, LARGE_COUNT,
                                                  searchTargets200[query]);
    }

    cout << "Average linear comparisons for 50 appointments: "
         << static_cast<double>(linearTotal50) / SEARCH_COUNT << endl;
    cout << "Average linear comparisons for 100 appointments: "
         << static_cast<double>(linearTotal100) / SEARCH_COUNT << endl;
    cout << "Average linear comparisons for 200 appointments: "
         << static_cast<double>(linearTotal200) / SEARCH_COUNT << endl;
    

   //  --- B3: Average binary-search comparisons for the same ten targets ---
    // Keep B2 active: it declares the target ID lists used below.
    int binaryTotal50 = 0;
    int binaryTotal100 = 0;
    int binaryTotal200 = 0;

    // Reuse the B2 target lists; only the search algorithm changes here.
    for (int query = 0; query < SEARCH_COUNT; query++)
    {
        binaryTotal50 += countBinaryComparisons(appointments50, SMALL_COUNT,
                                                 searchTargets50[query]);
        binaryTotal100 += countBinaryComparisons(appointments100, MEDIUM_COUNT,
                                                  searchTargets100[query]);
        binaryTotal200 += countBinaryComparisons(appointments200, LARGE_COUNT,
                                                  searchTargets200[query]);
    }

    cout << "Average binary comparisons for 50 appointments: "
         << static_cast<double>(binaryTotal50) / SEARCH_COUNT << endl;
    cout << "Average binary comparisons for 100 appointments: "
         << static_cast<double>(binaryTotal100) / SEARCH_COUNT << endl;
    cout << "Average binary comparisons for 200 appointments: "
         << static_cast<double>(binaryTotal200) / SEARCH_COUNT << endl;
    

   //  --- B4: Distinct appointment pairs that two nested loops would visit ---
    cout << "Possible pairs for 50 appointments: "
         << countPossiblePairs(SMALL_COUNT) << endl;
    cout << "Possible pairs for 100 appointments: "
         << countPossiblePairs(MEDIUM_COUNT) << endl;
    cout << "Possible pairs for 200 appointments: "
         << countPossiblePairs(LARGE_COUNT) << endl;
    

    return 0;
}

/* Returns the ID stored at a valid position already known by the caller. */
int getAppointmentAt(const int appointmentIds[], int appointmentIndex)
{
    return appointmentIds[appointmentIndex]; // Read one known array position.
}

/* Returns how many IDs linear search compares before finding targetId. */
int countLinearComparisons(const int appointmentIds[], int appointmentCount, int targetId)
{
    int comparisons = 0;

    for (int index = 0; index < appointmentCount; index++)
    {
        comparisons++; // One ID is compared with the target.

        if (appointmentIds[index] == targetId)
        {
            break;     // Stop after the matching ID is found.
        }
    }

    return comparisons;
}

/*
 * Returns how many middle IDs binary search compares before finding targetId.
 * Precondition: appointmentIds is sorted in ascending order and contains targetId.
 */
int countBinaryComparisons(const int appointmentIds[], int appointmentCount, int targetId)
{
    int first = 0;
    int last = appointmentCount - 1;
    int comparisons = 0;

    while (first <= last)
    {
        int middle = (first + last) / 2;
        comparisons++; // Compare the middle ID with the target.

        if (appointmentIds[middle] == targetId)
        {
            break;
        }
        else if (appointmentIds[middle] < targetId)
        {
            first = middle + 1; // Discard the lower half.
        }
        else
        {
            last = middle - 1;  // Discard the upper half.
        }
    }

    return comparisons;
}

/* Returns the number of distinct appointment pairs visited by two nested loops. */
int countPossiblePairs(int appointmentCount)
{
    int pairCount = 0;

    for (int first = 0; first < appointmentCount; first++)
    {
        for (int second = first + 1; second < appointmentCount; second++)
        {
            pairCount++; // One distinct pair would be compared here.
        }
    }

    return pairCount;
}

/* Fills the array with ascending dummy IDs so binary search is valid. */
void fillSortedAppointmentIds(int appointmentIds[], int appointmentCount)
{
    for (int index = 0; index < appointmentCount; index++)
    {
        appointmentIds[index] = 1000 + (index * 2); // Keep IDs in ascending order.
    }
}