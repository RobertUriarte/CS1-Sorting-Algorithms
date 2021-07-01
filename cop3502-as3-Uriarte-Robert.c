// all-monster-sorts.c - Sort monsters by name and weight.

/* The idea of sorting is simple: take unordered objects, and arrange them in an
   order.  It has a lot of uses, so there's been a lot of work done with it.  Here,
   we're going to demonstrate a few of the simpler, more classic sorting techniques.
   */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include <time.h>

/* Monster structure and helper functions - DO NOT MODIFY THESE. */

typedef struct monster {
	int id;
	char name[64];
	char element[64];
	int population;
	double weight;
} monster;

monster *make_some_monsters(int n)
{
  monster *monsters = malloc(sizeof(monster) * n);

  time_t t;

  srand((unsigned) time(&t));

  for(int i = 0; i < n; i++)
  {
    monsters[i].id = i;
    sprintf(monsters[i].name, "Monster #%d", rand());
    sprintf(monsters[i].element, "Element #%d", rand());
    monsters[i].population = rand();
    monsters[i].weight = 500.0 * ((double) rand() / (double) RAND_MAX);
  }

  return monsters;
}

void output_monster_list(monster *list, int n, char *title) {
    printf("List %s:\n", title);
    for(int i = 0; i < n; i++) {
    printf("  Monster %d: %s %s %d %lf\n", i, list[i].name, list[i].element, list[i].population, list[i].weight);
    }
    printf("\n");
}

void print_clocks(clock_t clocks) {
    printf("  %lfs CPU time used\n", ((double) clocks) / CLOCKS_PER_SEC);
}

void swap_monsters(monster *list, int i, int j)
{
    monster temp;

    memcpy(&temp, list + i, sizeof(monster));
    memcpy(list + i, list + j, sizeof(monster));
    memcpy(list + j, &temp, sizeof(monster));
}

/* The core comparison function. */

int compare_monsters(monster *m1, monster *m2, int use_name, int use_weight)
{
    //YOUR CODE GOES HERE..
    if(use_name == 1){  //Use 1 if we are sorting by name
        return (strcmp(m1->name, m2->name) > 0);
    }

    if(use_weight == 1){ //Use 1 if we are sorting by weight
        if(m1->weight > m2->weight){
            return 1;
        }
        else{
            return 0;
        }
    }
}

void check_monster_sort(monster *list, int n, int use_name, int use_weight)
{
    for(int i = 1; i < n; i++) {
        if(compare_monsters(list + i - 1, list + i, use_name, use_weight) > 0) {
            printf("*** The list is NOT sorted.\n\n");
            return;
        }
    }
    printf("The list is sorted.\n\n");
}

/* The core comparison function. */

//Credit Professor Gerber - Integer sorts template
int repartition(monster *list, int low_index, int high_index, int *comparisons, int *swaps, int use_name, int use_weight)
{
    //YOUR CODE GOES HERE.

    monster* pivot_value = &list[high_index]; //Pivot value is last value in our list

    int i = low_index;
    int temp;


        for(int j = low_index; j < high_index; j++) //Runs through all elements of list
        {
            (*comparisons)++;
            temp = compare_monsters(&list[j], pivot_value, use_name, use_weight); //Compares current monster j to the pivot value
            if(temp == 0) { // If j is less than the pivot value, swap j and the lowest index
                (*swaps)++;
                swap_monsters(list, i, j);
                i++;
            }
        }

        swaps++;
        swap_monsters(list, i, high_index); //Swaps i to be highest index and returns i
        return i;

}

/* Recursive function for quick sort. */

void quick_sort_recursive(monster *list, int low_index, int high_index, int *comparisons, int *swaps, int use_name, int use_weight)
{
    // YOUR CODE GOES HERE.
    int pivot_index = repartition(list, low_index, high_index, comparisons, swaps, use_name, use_weight);
    if(pivot_index-1 > low_index) quick_sort_recursive(list, low_index, pivot_index-1, comparisons, swaps, use_name, use_weight); //Sorts values lower than pivot index
    if(high_index > pivot_index+1) quick_sort_recursive(list, pivot_index+1, high_index, comparisons, swaps, use_name, use_weight); //Sorts values greater than pivot index
}

/* Shell function for quick sort. */

void quick_sort(monster *list, int n, int use_name, int use_weight)
{
    int comparisons = 0;
    int swaps = 0;
    clock_t start_cpu, end_cpu;

    printf("\nQuick sort %d monsters by %s...\n", n, use_name ? "name" : "weight");

    start_cpu = clock();
    quick_sort_recursive(list, 0, n-1, &comparisons, &swaps, use_name, use_weight);
    end_cpu = clock();

    printf("Sort complete with %d comparisons and %d swaps.\n", comparisons, swaps);
    print_clocks(end_cpu - start_cpu);
}

/* Implement ascending bubble sort. */

//Credit Professor Gerber - Integer sorts template
void bubble_sort(monster *list, int n, int use_name, int use_weight)
{
    int i;
    int j;
    int temp;
    int comparisons = 0;
    int swaps = 0;
    clock_t start_cpu, end_cpu;

    printf("Bubble sort %d monsters by %s...\n", n, use_name ? "name" : "weight");

    start_cpu = clock();

    // YOUR CODE GOES HERE.

        for(i = n-1; i >= 0; i--) // Runs for number of elements in list, n-1 though since the last index is 1 less than total elements
        {
            for(j = 0; j < i; j++)
            {
              comparisons++;
              temp = compare_monsters(&list[j], &list[j+1], use_name, use_weight);
              if(temp == 1) //If j is greater than j + 1, swap the two
              {
                swaps++;
                swap_monsters(list, j, j+1);
              }
            }
        }



    end_cpu = clock();
    printf("Sort complete with %d comparisons and %d swaps.\n", comparisons, swaps);
    print_clocks(end_cpu - start_cpu);
}

/* Highest-value finder for selection sort. */

//Credit Professor Gerber - Integer sorts template
int find_highest(monster *list, int n, int *comparisons, int use_name, int use_weight)
{
    // YOUR CODE GOES HERE.
    monster* temp = malloc(sizeof(monster));
    monster* highest_val = &temp;
    int highest_loc;
    int i;
    int temp2;


    for(i = 0; i <= n; i++)
    {
        temp2 = compare_monsters(&list[i], highest_val, use_name, use_weight);
        (*comparisons)++;

        if(temp2 == 1) //If i is the highest value, makes i the highest value
        {
            highest_loc = i;
            highest_val = &list[i];
        }
    }

    return highest_loc; // returns index of highest value
}

/* Implement ascending selection sort. */

//Credit Professor Gerber - Integer sorts template
void selection_sort(monster *list, int n, int use_name, int use_weight)
{
    int i;
    int highest;
    int comparisons = 0;
    int swaps = 0;
    clock_t start_cpu, end_cpu;

    printf("\nSelection sort %d monsters by %s...\n", n, use_name ? "name" : "weight");
    start_cpu = clock();

    // YOUR CODE GOES HERE.

        for(i = n-1; i > 0; i--) // Starts loop at end of list so we can put highest value at the end.
        {
            highest = find_highest(list, i, &comparisons, use_name, use_weight);
            if(highest != i)
            {
                swaps++;
                swap_monsters(list, highest, i); //Puts the highest value found at the end of our unsorted list
            }
        }

    end_cpu = clock();
    printf("Sort complete with %d comparisons and %d swaps.\n", comparisons, swaps);
    print_clocks(end_cpu - start_cpu);
}

/* Find position for insertion sort. */

int insertion_sort_find_position(monster *list, int low_index, int high_index, monster *k, int *comparisons, int use_name, int use_weight)
{
    //YOUR CODE GOES HERE.
    int i;
    int temp2;
    monster* key;

    for(i = low_index; i < high_index; i++){

        key = &list[i];
        temp2 = compare_monsters(k, key, use_name, use_weight);
        (*comparisons)++;

        if (temp2 == 0){ //When the constant monster k is not greater than the lowest index/key we choose to insert there
            return i;
        }
    }

    return high_index; //Returns high_index if there are no values less than k

    free(key);
}

/* Implement insertion sort. */

void insertion_sort_internal(monster *list, int n, int *comparisons, int *copies, int *block_copies, int use_name, int use_weight)
{
  // YOUR CODE GOES HERE. //Main insertion sort code
    int temp;
    monster temp2;

    for(int i = 1; i < n; i++){

        temp = insertion_sort_find_position(list, 0, i , &list[i], comparisons, use_name, use_weight); //Find position we need to insert at

        if (temp != i){
            temp2 = list[i]; //temporarily stores what value we want to insert


            memmove(&list[temp + 1], &list[temp], sizeof(monster) * (i - temp)); //Memmoves everything up to make room for our new insertion
            (*block_copies)++;
            (*copies) = (*copies) + (*block_copies);

            list[temp] = temp2; //Inserts our value in correct position
        }
    }

}

/* Shell for insertion sort. */

void insertion_sort(monster *list, int n, int use_name, int use_weight)
{
  int comparisons = 0;
  int block_copies = 0;
  int total_copies = 0;
  clock_t start_cpu, end_cpu;
  printf("\nInsertion sort %d monsters by %s...\n", n, use_name ? "name" : "weight");
  start_cpu = clock();

  insertion_sort_internal(list, n, &comparisons, &total_copies, &block_copies, use_name, use_weight);

  end_cpu = clock();
  printf("Sort complete with %d comparisons and %d block copies (%d total copies).\n", comparisons, block_copies, total_copies);
  print_clocks(end_cpu - start_cpu);


  return;
}

/* Merge function for merge sort.  Merges sub-arrays [l1..h1] and [l2..h2].
   Must have l2 = l1 + 1 or bad things will happen. */

void merge_sort_merge(monster *list, int l1, int h1, int l2, int h2, int *comparisons, int *copies, int *block_copies, int *mallocs, int use_name, int use_weight)
{
  //YOUR CODE GOES HERE.
    int size1 = (h1 - l1 + 1);
    int size2 = (h2 - l2 + 1);
    monster* left = malloc(sizeof(monster) * size1); //Creates two monster array to temporarily split up our unsorted list
    (*mallocs)++;
    monster* right = malloc(sizeof(monster)* size2);
    (*mallocs)++;

    int i, j, k;

    for (i = 0; i < size1; i++){
        left[i] = list[l1 + i]; //Stores half of list in left array
    }

    for (j = 0; j < size2; j++){
        right[j] = list[l2 + j]; //Stores other half of list in right array
    }

    i = 0;
    j = 0;
    k = l1;
    int temp;

    while (i < size1 && j < size2) {
        temp = compare_monsters(&left[i], &right[j],use_name, use_weight); //Compares the left and right array values starting from index 0
        (*comparisons)++;
        if (temp == 0) { //If right is greater than the left array we store the left array value
            list[k] = left[i];
            (*copies)++;
            i++;
        }
        else { //If left is greater than the right array we store the right array value
            list[k] = right[j];
            j++;
            (*copies)++;
        }
        k++;
    }

    while (i < size1) { //Store the remaining elements of left array if necessary
        list[k] = left[i];
        (*copies)++;
        i++;
        k++;
    }

    while (j < size2) { //Stores the remaining elements of right array if necessary
        list[k] = right[j];
        (*copies)++;
        j++;
        k++;
    }

    (*block_copies)++;

    free(left);
    free(right);
}

/* Recursive function for merge sort. */

void merge_sort_recursive(monster *list, int low_index, int high_index, int *comparisons, int *copies, int *block_copies, int *mallocs, int use_name, int use_weight)
{
  // YOUR CODE GOES HERE.
  int middle_index;
  if(low_index != high_index){
    middle_index = (low_index + (high_index - 1) )/2;
    merge_sort_recursive(list, low_index , middle_index, comparisons, copies, block_copies, mallocs, use_name, use_weight); //Sorts from low to middle
    merge_sort_recursive(list, middle_index+1, high_index, comparisons, copies, block_copies, mallocs, use_name, use_weight); //Sorts from middle to high
    merge_sort_merge(list, low_index,middle_index, middle_index +1, high_index, comparisons, copies, block_copies, mallocs,use_name, use_weight); //Uses two previous sorts to sort completely
  }

}

/* Implement merge sort. */

void merge_sort(monster *list, int n, int use_name, int use_weight)
{
  int comparisons = 0;
  int copies = 0;
  int block_copies = 0;
  int mallocs = 0;
  clock_t start_cpu, end_cpu;

  printf("Merge sort %d monsters...\n", n);

  start_cpu = clock();
  merge_sort_recursive(list, 0, n-1, &comparisons, &copies, &block_copies, &mallocs,
                       use_name, use_weight);
  end_cpu = clock();

  printf("Sort complete with %d comparisons, %d block copies, %d total copies, %d mallocs.\n", comparisons, block_copies, copies, mallocs);
  print_clocks(end_cpu - start_cpu);

}

/* Recursive function for merge-insertion sort. */

void merge_insertion_sort_recursive(monster *list, int low_index, int high_index, int *comparisons, int *copies, int *block_copies, int *mallocs, int use_name, int use_weight)
{
  // YOUR CODE GOES HERE.
  if(low_index < high_index){

    if(high_index - low_index <= 50){ //Uses the threshold of 50 to use insertion sort
    insertion_sort_internal(list, high_index + 1 , comparisons, copies, block_copies, use_name, use_weight);
    }

    else{ //Uses merge sort if list amount is greater than 50
        int middle_index = (high_index - low_index)/2;
        merge_sort_recursive(list, low_index, high_index, comparisons, copies, block_copies, mallocs, use_name, use_weight);
    }
  }

}

/* Implement merge sort. */

void merge_insertion_sort(monster *list, int n, int use_name, int use_weight)
{
  int comparisons = 0;
  int copies = 0;
  int block_copies = 0;
  int mallocs = 0;
  clock_t start_cpu, end_cpu;

  printf("Merge-insertion sort %d monsters...\n", n);

  start_cpu = clock();
  merge_insertion_sort_recursive(list, 0, n-1, &comparisons, &copies, &block_copies, &mallocs,
                                 use_name, use_weight);
  end_cpu = clock();

  printf("Sort complete with %d comparisons, %d block copies, %d total copies, %d mallocs.\n", comparisons, block_copies, copies, mallocs);
  print_clocks(end_cpu - start_cpu);
}

void print_ordered_monsters(monster* our_unsorted_list, int use_name, int use_weight, int n){
    if (use_weight == 1){
        for (int i = 0; i < n; i++){
            printf("Monster weight is: %lf\n", our_unsorted_list[i].weight);
        }
      }

    if(use_name == 1){
        for (int i = 0; i < n; i++){
            printf("Monster name is: %s\n", our_unsorted_list[i].name);
        }
    }
}
/* Main program. */

void run_all_sorts(int n, int only_fast, int use_name, int use_weight) {
  monster *our_list = make_some_monsters(n);
  monster *our_unsorted_list = malloc(sizeof(monster) * n);

  printf("SORT SET: n = %d, %s, by %s\n\n", n, only_fast ? "fast sorts only" : "all sorts", use_name ? "name" : "weight");

  if(only_fast == 0) {
    memcpy(our_unsorted_list, our_list, sizeof(monster) * n);
    bubble_sort(our_unsorted_list, n, use_name, use_weight);
    check_monster_sort(our_unsorted_list, n, use_name, use_weight);

    memcpy(our_unsorted_list, our_list, sizeof(monster) * n);
    selection_sort(our_unsorted_list, n, use_name, use_weight);
    check_monster_sort(our_unsorted_list, n, use_name, use_weight);

    memcpy(our_unsorted_list, our_list, sizeof(monster) * n);
    insertion_sort(our_unsorted_list, n, use_name, use_weight);
    check_monster_sort(our_unsorted_list, n, use_name, use_weight);
  }

  memcpy(our_unsorted_list, our_list, sizeof(monster) * n);
  quick_sort(our_unsorted_list, n, use_name, use_weight);
  check_monster_sort(our_unsorted_list, n, use_name, use_weight);

  memcpy(our_unsorted_list, our_list, sizeof(monster) * n);
  merge_sort(our_unsorted_list, n, use_name, use_weight);
  check_monster_sort(our_unsorted_list, n, use_name, use_weight);

  memcpy(our_unsorted_list, our_list, sizeof(monster) * n);
  merge_insertion_sort(our_unsorted_list, n, use_name, use_weight);
  check_monster_sort(our_unsorted_list, n, use_name, use_weight);

  printf("SORT SET COMPLETE\n\n");

  free(our_list);
  free(our_unsorted_list);
}

int main(void) {
  run_all_sorts(50, 0, 0, 1);
  run_all_sorts(50, 0, 1, 0);
  run_all_sorts(500, 0, 0, 1);
  run_all_sorts(500, 0, 1, 0);
  run_all_sorts(5000, 0, 0, 1);
  run_all_sorts(5000, 0, 1, 0);
  run_all_sorts(50000, 1, 0, 1);
  run_all_sorts(50000, 1, 1, 0);
  run_all_sorts(500000, 1, 0, 1);
  run_all_sorts(500000, 1, 1, 0);
}
