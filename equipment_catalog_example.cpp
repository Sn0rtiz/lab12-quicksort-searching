/*
 * Course: COEN 2220 - Programming 2
 * Name: [Sebastian Ortiz]
 * Lab: Lab 12 - Quicksort and Searching
 * Description: Guided equipment catalog and code lookup
 * Due date: [11/10/2026]
 */

#include <iostream>
#include <string>
using namespace std;

struct Equipment
{
    int assetCode;   // Identify one physical device; codes are unique.
    string cabinet; // Keep its storage location attached to the code.
};

void displayEquipment(const Equipment equipment[], int count);
void swapEquipment(Equipment& left, Equipment& right);
int partitionEquipment(Equipment equipment[], int first, int last);
void quickSortEquipment(Equipment equipment[], int first, int last);
int binaryFindEquipment(const Equipment equipment[], int first, int last, int target);

int main()
{
    const int COUNT = 8;
    Equipment equipment[COUNT] = {
        {48, "C-4"}, {21, "A-2"}, {63, "D-1"}, {35, "B-3"},
        {57, "C-2"}, {14, "A-1"}, {72, "D-4"}, {29, "B-1"}
    };

    cout << "Inspection order:" << endl;
    displayEquipment(equipment, COUNT);

    // --- STEP B2: Prepare the catalog for repeated code searches ---
    
    quickSortEquipment(equipment, 0, COUNT - 1);
    cout << "Sorted by asset code:" << endl;
    displayEquipment(equipment, COUNT);
    

    // --- STEP B3: Read a code and retrieve its cabinet safely ---
    
    int target;
    cout << "Enter an asset code: ";
    if (!(cin >> target))
    {
        cout << "Invalid code input." << endl;
        return 1; // Stop before searching with an unread value.
    }

    int position = binaryFindEquipment(equipment, 0, COUNT - 1, target);
    if (position == -1)
    {
        cout << "Equipment not found." << endl;
    }
    else
    {
        cout << "Found code " << equipment[position].assetCode
             << " in cabinet " << equipment[position].cabinet << endl;
    }
    
    return 0;
}

void displayEquipment(const Equipment equipment[], int count)
{
    for (int index = 0; index < count; index++)
    {
        cout << "Code: " << equipment[index].assetCode
             << " | Cabinet: " << equipment[index].cabinet << endl;
    }
}

// --- STEP B2: Define the sorting operations ---

void swapEquipment(Equipment& left, Equipment& right)
{
    Equipment saved = left; // Preserve both fields during the exchange.
    left = right;
    right = saved;
}

int partitionEquipment(Equipment equipment[], int first, int last)
{
    int middle = first + (last - first) / 2;
    swapEquipment(equipment[first], equipment[middle]);
    int pivotCode = equipment[first].assetCode; // Keep this value fixed during the scan.
    int boundary = first; // The smaller group initially has no elements.

    for (int scan = first + 1; scan <= last; scan++)
    {
        if (equipment[scan].assetCode < pivotCode)
        {
            boundary++; // Reserve the next position in the smaller group.
            swapEquipment(equipment[boundary], equipment[scan]);
        }
    }
    swapEquipment(equipment[first], equipment[boundary]); // Complete the partition.
    return boundary; // This final position divides the next recursive ranges.
}

void quickSortEquipment(Equipment equipment[], int first, int last)
{
    if (first >= last)
    {
        return; // Empty and one-record ranges need no partition.
    }
    int pivotIndex = partitionEquipment(equipment, first, last);
    quickSortEquipment(equipment, first, pivotIndex - 1);
    quickSortEquipment(equipment, pivotIndex + 1, last);
}


// --- STEP B3: Define recursive lookup on the sorted catalog ---

int binaryFindEquipment(const Equipment equipment[], int first, int last, int target)
{
    if (first > last)
    {
        return -1; // An empty search range proves that the code is absent.
    }
    int middle = first + (last - first) / 2;
    if (equipment[middle].assetCode == target)
    {
        return middle; // A one-record range must still be checked for a match.
    }
    if (equipment[middle].assetCode < target)
    {
        return binaryFindEquipment(equipment, middle + 1, last, target);
    }
    return binaryFindEquipment(equipment, first, middle - 1, target);
}


/*
 * Analysis Answers
 *
 * B4 - Partition and recursive control
 * After the first partition, identify the pivot code, its returned index, and
 * the two next ranges. Is the whole catalog already sorted? Explain using data.
 * Answer: 
 * The first pivot is 35 (cabinet B-3), taken from the middle (index 3).
 * After the partition it is returned at index 3. The array then becomes:
 * 29, 21, 14, 35, 57, 63, 72, 48
 * The next ranges are indices 0-2 on the left and 4-7 on the right.
 * The catalog is not sorted yet. Only 35 is in its final place. The left and
 * right parts are still out of order, so quicksort has to run on both of them.
 *
 * B5 - A search that fails
 * Trace the recursive search for code 36. List each first, last, middle,
 * inspected code, and next range. At the empty range, explain which calls resume
 * and how -1 reaches main without an invalid array access.
 * Answer:
 * Sorted codes: 14, 21, 29, 35, 48, 57, 63, 72. Searching for 36:
 *
 * Call 1: first = 0, last = 7, middle = 3, code = 35. 35 < 36, so go right (4 to 7).
 * Call 2: first = 4, last = 7, middle = 5, code = 57. 57 > 36, so go left (4 to 4).
 * Call 3: first = 4, last = 4, middle = 4, code = 48. 48 > 36, so go left (4 to 3).
 * Call 4: first = 4, last = 3. The range is empty, so it returns -1.
 *
 * Call 4 returns -1 before it reads the array, so there is no invalid access.
 * Then calls 3, 2, and 1 each return that same -1 back up to main. Main checks
 * if position == -1 first and prints "Equipment not found."
 */