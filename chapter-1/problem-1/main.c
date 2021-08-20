#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <valgrind/callgrind.h>

#define ARRAY_SIZE 100
#define ARRAY_MAX_NUMBER 500

void make_random_numers_array(unsigned int *array, size_t array_size, unsigned max_number)
{
    srand(time(NULL));
    unsigned int i;
    for (i = 0; i < array_size; i++)
    {
        array[i] = rand() % max_number;
    }
}

int should_break_line(unsigned int index, unsigned int line_break_position)
{
    return !((index + 1) % line_break_position);
}

void print_array(const unsigned int *array, size_t array_size, unsigned int numbers_in_row)
{
    unsigned int i;
    for (i = 0; i < array_size; i++)
    {
        printf("%4d ", array[i]);
        if (should_break_line(i, numbers_in_row))
        {
            printf("\n");
        }
    }
}

struct Extremums
{
    unsigned int min;
    unsigned int max;
    unsigned int comparisons_counter;
};

int is_greater_with_counter(unsigned int a, unsigned int b, unsigned int *counter)
{
    (*counter)++;
    return a > b;
}

int is_lesser_with_counter(unsigned int a, unsigned int b, unsigned int *counter)
{
    (*counter)++;
    return a < b;
}

struct Extremums find_extremums_v1(const unsigned int *array, size_t array_size)
{
    struct Extremums extremums = {.min = array[0], .max = array[0], .comparisons_counter = 0};

    int i;
    for (i = 0; i < array_size; i++)
    {
        if (is_greater_with_counter(array[i],
                                    extremums.max,
                                    &extremums.comparisons_counter))
        {
            extremums.max = array[i];
        }

        if (is_lesser_with_counter(array[i],
                                   extremums.min,
                                   &extremums.comparisons_counter))
        {
            extremums.min = array[i];
        }
    }

    return extremums;
}

struct Extremums find_extremums_v2(const unsigned int *array, size_t array_size)
{
    struct Extremums extremums = {.min = array[0], .max = array[0]};

    int i;
    for (i = 0; i < array_size; i++)
    {
        if (is_greater_with_counter(array[i],
                                    extremums.max,
                                    &extremums.comparisons_counter))
        {
            extremums.max = array[i];
        }
        else if (is_lesser_with_counter(array[i],
                                        extremums.min,
                                        &extremums.comparisons_counter))
        {
            extremums.min = array[i];
        }
    }

    return extremums;
}

int main()
{
    unsigned int random_numbers[ARRAY_SIZE];

    make_random_numers_array(random_numbers, ARRAY_SIZE, ARRAY_MAX_NUMBER);
    // print_array(random_numbers, ARRAY_SIZE, 10);

    struct Extremums extremums_1 = find_extremums_v1(random_numbers, ARRAY_SIZE);
    struct Extremums extremums_2 = find_extremums_v2(random_numbers, ARRAY_SIZE);

    printf("v1 | Found min = %d, max = %d, comparison_count = %d\n",
           extremums_1.min, extremums_1.max, extremums_1.comparisons_counter);
    printf("v2 | Found min = %d, max = %d, comparison_count = %d\n",
           extremums_2.min, extremums_2.max, extremums_2.comparisons_counter);

    return 0;
}
