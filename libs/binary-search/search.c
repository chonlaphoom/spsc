#include "stdio.h"
/*
 * nums is sorted in ascending order, and all values are unique.
 * numsSize is the number of elements in nums.
 * target is the value to search for.
 *
 * If target exists, return its index. Otherwise, return -1.
 */
extern int search(int *nums, int numsSize, int target) {
  if (nums == NULL || numsSize < 0) {
    return -1;
  }
  int low = 0;
  int high = numsSize;
  while (low <= high) {
    int mid = low + ((high - low) / 2);
    if (mid < 0 || mid >= numsSize) {
      break;
    }
    if (nums[mid] == target) {
      return mid;
    }
    if (nums[mid] < target) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  return -1;
}

static int test1();
static int test2();

int main(void) {
  printf("Test 1: %s\n", test1() ? "Passed" : "Failed");
  printf("Test 2: %s\n", test2() ? "Passed" : "Failed");
  return 1;
}

static int test1(void) {
  int nums[6] = {-1, 0, 3, 5, 9, 12};
  int target = 9;
  return search(&nums[0], 6, target) == 4;
}
static int test2(void) {
  int nums[6] = {-1, 0, 3, 5, 9, 12};
  int target = 2;
  return search(&nums[0], 6, target) == -1;
}
