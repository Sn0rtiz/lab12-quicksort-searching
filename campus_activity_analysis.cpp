/*
 * Course: COEN 2220 - Programming 2
 * Name: [Your Name]
 * Lab: Lab 8 - Big-O / Time Complexity
 * Description: Resolved code for time-complexity analysis
 * Due date: [Date]
 */

#include <iostream>
using namespace std;

/* Returns the ID stored at a valid position already known by the caller. */
int getActivityIdAt(const int activityIds[], int activityIndex)
{
    return activityIds[activityIndex]; // Read one known array position.
}

/* Returns how many activities have an active status. */
int countActiveActivities(const bool isActive[], int activityCount)
{
    int activeCount = 0;

    for (int index = 0; index < activityCount; index++)
    {
        if (isActive[index])
        {
            activeCount++;
        }
    }

    return activeCount;
}

/*
 * Returns how many middle IDs binary search compares before finding targetId.
 * Precondition: activityIds is sorted in ascending order and contains targetId.
 */
int countBinaryComparisons(const int activityIds[], int activityCount, int targetId)
{
    int first = 0;
    int last = activityCount - 1;
    int comparisons = 0;

    while (first <= last)
    {
        int middle = (first + last) / 2;
        comparisons++;

        if (activityIds[middle] == targetId)
        {
            break;
        }
        else if (activityIds[middle] < targetId)
        {
            first = middle + 1;
        }
        else
        {
            last = middle - 1;
        }
    }

    return comparisons;
}

/* Returns how many times a positive count can be reduced by half before reaching 1. */
int countHalvingSteps(int itemCount)
{
    int steps = 0;

    while (itemCount > 1)
    {
        itemCount = itemCount / 2; // Remove approximately half of the remaining items.
        steps++;
    }

    return steps;
}

/* Returns the number of distinct activity pairs visited by two nested loops. */
int countPossiblePairs(int activityCount)
{
    int pairCount = 0;

    for (int first = 0; first < activityCount; first++)
    {
        for (int second = first + 1; second < activityCount; second++)
        {
            pairCount++; // One distinct pair would be compared here.
        }
    }

    return pairCount;
}

int main()
{
    // These activity IDs are sorted so binary search is valid.
    int activityIds[] = {101, 104, 108, 115, 130, 136, 140, 155};
    bool isActive[] = {true, false, true, true, false, false, true, false};
    int activityCount = 8;

    cout << "Activity at index 2: "
         << getActivityIdAt(activityIds, 2) << endl;
    cout << "Active activities: "
         << countActiveActivities(isActive, activityCount) << endl;
    cout << "Binary comparisons for 140: "
         << countBinaryComparisons(activityIds, activityCount, 140) << endl;
    cout << "Halving steps for 8: " << countHalvingSteps(8) << endl;
    cout << "Halving steps for 16: " << countHalvingSteps(16) << endl;
    cout << "Halving steps for 32: " << countHalvingSteps(32) << endl;
    cout << "Possible pairs for 4 activities: " << countPossiblePairs(4) << endl;
    cout << "Possible pairs for 8 activities: " << countPossiblePairs(8) << endl;

    return 0;
}

/*
 * Analysis Answers
 *
 * C1 — Direct access
 * Answer: getActivityIdAt peforms a single read no matter how many activitues there are.
 * The work does not depend on n, so it is 0(1), constant time. If n doubles, the work stays the same.
 *
 * C2 — Count active activities
 * Answer: countActiveActivities loops through the whole array onece and checks each element exacly once.
 * The work is proportional to n, so it is O(n), linear time. If n doubles, the work doubles. With 8 activities it returns 4.
 *
 * C3 — Binary search
 * Answer:Each comparison discards half of the remaining range, so the number of comparisons grows with long n.
 * Searching for 140 in an array of 8 elements takes 3 comparisons. 
 * The work is O(log n), logarithmic time. If n doubles, the work increases by 1 comparison.
 *
 * C4 — Halving steps
 * Answer: countHalvingSteps counts how many times a positive count can be reduced by half before reaching 1.
 * The work is O(log n), logarithmic time. If n doubles, the work increases by 1 step.
 *
 * C5 — Distinct pairs
 * Answer: countPossiblePairs counts the number of unique pairs that can be formed from a set of activities.
 * The work is O(n^2), quadratic time. If n doubles, the work increases by a factor of 4.
 *
 * C6 — Compare the observed patterns
 * Answer: When comparing the observed patterns, we can see:
 * 
 * that direct access is constant time
 * counting active activities is linear time 
 * binary search and halving steps are logarithmic time
 * counting distinct pairs is quadratic time
 * 
 * This shows how different algorithms can have vastly different performance characteristics based on their time complexity.
 *
 * C7 — Sorting decision
 * Answer:
 * Binary only works with sorted data so if the data insin't is better to not use binary.
 * If only one search will be done, linear search 0(n) is the better choice.
 * If many searches will be done on the same data, it is better to sort onve and the  use binary.
 *
 */