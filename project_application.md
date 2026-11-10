# Lab 12 - Project Application

## E1 - Filter and ownership
Identify selected and excluded IDs, their reasons, and who owns each object.
- **Selected:** 420, 180, 310, 205. All are DELIVERY and either PENDING or IN_PROGRESS.
- **Excluded:** 650, because it is "DINE_IN" that is not the same type, and 900, because it is "COMPLETED" not longer active.

The orders array in main owns all six OrderPreview objects. The view (OrderPreview *view[]) only stores borrowed addresses of the four selected objects. Because the objects were not created with new, the view never calls delete on them.

## E2 - Report order and algorithm
List the observed report IDs and explain how each comparison rule affects them.
State the sorting algorithm used and its time and auxiliary-space bounds.

**Observed report IDs:** 205, 310, 420, 180.
 
- **Building ascending:** "Biblioteca" comes before "Ingenieria" in string comparison, so 205, 310, and 420 come before 180.

- **Priority descending (same building):** inside Biblioteca, priority 3 orders (205 and 310) come before the priority 1 order (420).

- **ID ascending (same building and priority):** 205 and 310 are both Biblioteca with priority 3, so the ID decides and 205 goes first.

**Algorithm:** quicksort on the view of pointers, with the middle element moved to the front as the pivot and the comparison done by comesBefore.
 
- Time: O(n log n) on average (balanced partitions) and O(n^2) in the worst case.
- Auxiliary space: O(log n) of recursion stack when balanced and O(n) in the worst case. The view itself is O(n) extra storage (one pointer per selected order).

## E3 - Lookup choice and tests
Explain why this report cannot support binary search by orderId as currently sorted.
Give one found, one excluded, and one nonexistent test with observed results.
Describe what an additional ID-sorted view would cost and enable.

The report is sorted by building, then priority, then ID, so the IDs are not in ascending order across the whole view (the report order is 205, 310, 420, 180). Binary search needs the whole range to be sorted by the same key it searches. Comparing a target ID with the middle ID would say nothing about which half contains it, so half of the records could not be discarded. That is why findOrderInView uses a linear search, which is O(n).
 
**Tests (observed):**
 
| Test | Input | Result |
|---|---|---|
| Found | 310 | Order 310 \| Building: Biblioteca \| Status: PENDING \| Priority: 3 |
| Excluded | 650 (DINE_IN) | Order 650 is not in the delivery report. |
| Nonexistent | 999 | Order 999 is not in the delivery report. |
 
**Additional ID-sorted view:** a second array of pointers sorted by orderId would allow binary search in O(log n) per query. It would cost an extra O(n) memory for the pointers and an O(n log n) sort (plus keeping it updated if orders change). It makes sense only if there are many ID queries.

## E4 - Evidence and project connection
Source: delivery_report_practice.cpp
Output: delivery_report_output.txt
Explain how you verified that original records kept their order and field values.
Explain how this separation protects the operational FIFO sequence in the project.
**How I verified the original records were not changed:**
My program prints orders before and after produciong the report and doing the lookup. Both prints show the same records in the same order (420,180,650,310,205,900) with the same fields. The program also keeps a copy of the array and compares it field by field at the end, printing "Original unchanged: yes". The sorting only swaps pointers in the view, so the objects never move.

**Connection to the project:** the cafeteria needs the original sequence to keep preparing orders in FIFO order. By sorting a temporary view of pointers instead of the original records, the delivery report can be organized differently without changing that operational sequence. The report can be discarded or rebuilt at any time and the FIFO order stays intact.