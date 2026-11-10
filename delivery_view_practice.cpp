//Sebastian Ortiz
// Lab 12 - Quicksort and Searching
// 11/10/2026

#include <iostream>
#include <string>
using namespace std;
 
struct OrderPreview
{
    int orderId;
    string orderType;
    string status;
    string building;
    int priority;
};
 
void displayOrders(const OrderPreview orders[], int count);
void displayView(OrderPreview *view[], int count);
int buildDeliveryView(OrderPreview orders[], int count, OrderPreview *view[]);
bool comesBefore(const OrderPreview *left, const OrderPreview *right);
void swapOrderPointers(OrderPreview *&left, OrderPreview *&right);
int partitionView(OrderPreview *view[], int first, int last);
void quickSortView(OrderPreview *view[], int first, int last);
int findOrderInView(OrderPreview *view[], int count, int targetId);
bool sameOrders(const OrderPreview a[], const OrderPreview b[], int count);
 
int main()
{
    const int COUNT = 6;
    OrderPreview orders[COUNT] = {
        {420, "DELIVERY", "PENDING",     "Biblioteca",      1},
        {180, "DELIVERY", "IN_PROGRESS", "Ingenieria",      3},
        {650, "DINE_IN",  "PENDING",     "Cafeteria-Lunch", 1},
        {310, "DELIVERY", "PENDING",     "Biblioteca",      3},
        {205, "DELIVERY", "PENDING",     "Biblioteca",      3},
        {900, "DELIVERY", "COMPLETED",   "Ingenieria",      2}
    };
    OrderPreview snapshot[COUNT]; // Copy used only to verify orders did not change.
    for (int i = 0; i < COUNT; i++)
    {
        snapshot[i] = orders[i];
    }
 
    OrderPreview *view[COUNT]; // Borrowed addresses; never deleted.
 
    cout << "Original orders BEFORE:" << endl;
    displayOrders(orders, COUNT);
 
    int viewCount = buildDeliveryView(orders, COUNT, view);
    quickSortView(view, 0, viewCount - 1);
 
    cout << endl << "Delivery report (" << viewCount << " orders):" << endl;
    displayView(view, viewCount);
 
    int target;
    cout << endl << "Enter an order ID: ";
    if (!(cin >> target))
    {
        cout << "Invalid ID input." << endl;
        return 1;
    }
 
    int position = findOrderInView(view, viewCount, target);
    if (position == -1)
    {
        cout << "Order " << target << " is not in the delivery report." << endl;
    }
    else
    {
        cout << "Order " << view[position]->orderId
             << " | Building: " << view[position]->building
             << " | Status: " << view[position]->status
             << " | Priority: " << view[position]->priority << endl;
    }
 
    cout << endl << "Original orders AFTER:" << endl;
    displayOrders(orders, COUNT);
    cout << "Original unchanged: "
         << (sameOrders(orders, snapshot, COUNT) ? "yes" : "NO") << endl;
 
    return 0;
}
 
void displayOrders(const OrderPreview orders[], int count)
{
    for (int i = 0; i < count; i++)
    {
        cout << "Index " << i
             << " | ID: " << orders[i].orderId
             << " | " << orders[i].orderType
             << " | " << orders[i].status
             << " | " << orders[i].building
             << " | Priority: " << orders[i].priority << endl;
    }
}
 
void displayView(OrderPreview *view[], int count)
{
    for (int i = 0; i < count; i++)
    {
        cout << "View " << i
             << " | ID: " << view[i]->orderId
             << " | " << view[i]->building
             << " | Priority: " << view[i]->priority
             << " | " << view[i]->status << endl;
    }
}
 
// E1: keep only active (PENDING or IN_PROGRESS) DELIVERY orders; borrow addresses.
int buildDeliveryView(OrderPreview orders[], int count, OrderPreview *view[])
{
    int viewCount = 0;
    for (int i = 0; i < count; i++)
    {
        bool isDelivery = (orders[i].orderType == "DELIVERY");
        bool isActive = (orders[i].status == "PENDING" ||
                         orders[i].status == "IN_PROGRESS");
        if (isDelivery && isActive)
        {
            view[viewCount] = &orders[i];
            viewCount++;
        }
    }
    return viewCount;
}
 
// E2: building ascending, then priority descending, then ID ascending.
bool comesBefore(const OrderPreview *left, const OrderPreview *right)
{
    if (left->building != right->building)
    {
        return left->building < right->building;
    }
    if (left->priority != right->priority)
    {
        return left->priority > right->priority;
    }
    return left->orderId < right->orderId;
}
 
void swapOrderPointers(OrderPreview *&left, OrderPreview *&right)
{
    OrderPreview *saved = left; // Only addresses are exchanged.
    left = right;
    right = saved;
}
 
int partitionView(OrderPreview *view[], int first, int last)
{
    int middle = first + (last - first) / 2;
    swapOrderPointers(view[first], view[middle]);
    OrderPreview *pivot = view[first];
    int boundary = first;
 
    for (int scan = first + 1; scan <= last; scan++)
    {
        if (comesBefore(view[scan], pivot))
        {
            boundary++;
            swapOrderPointers(view[boundary], view[scan]);
        }
    }
    swapOrderPointers(view[first], view[boundary]);
    return boundary;
}
 
void quickSortView(OrderPreview *view[], int first, int last)
{
    if (first >= last)
    {
        return;
    }
    int pivotIndex = partitionView(view, first, last);
    quickSortView(view, first, pivotIndex - 1);
    quickSortView(view, pivotIndex + 1, last);
}
 
// E3: linear search; returns a view position or -1. Does not modify data.
int findOrderInView(OrderPreview *view[], int count, int targetId)
{
    for (int i = 0; i < count; i++)
    {
        if (view[i]->orderId == targetId)
        {
            return i;
        }
    }
    return -1;
}
 
bool sameOrders(const OrderPreview a[], const OrderPreview b[], int count)
{
    for (int i = 0; i < count; i++)
    {
        if (a[i].orderId != b[i].orderId || a[i].orderType != b[i].orderType ||
            a[i].status != b[i].status || a[i].building != b[i].building ||
            a[i].priority != b[i].priority)
        {
            return false;
        }
    }
    return true;
}