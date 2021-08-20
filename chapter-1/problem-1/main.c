#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

void print_array(unsigned int *array, size_t array_size, unsigned int numbers_in_row)
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

int main()
{
    unsigned int random_numbers[ARRAY_SIZE];
    make_random_numers_array(random_numbers, ARRAY_SIZE, ARRAY_MAX_NUMBER);
    print_array(random_numbers, ARRAY_SIZE, 10);
}
