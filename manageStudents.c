#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define STUDENTS_MAX_SIZE 5000
#define LINE_MAX_SIZE 151
#define FIELD_MAX_SIZE 41
#define ID_MAX_SIZE 10
#define GRADE_UPPER 100
#define GRADE_LOWER 0
#define AGE_UPPER 120
#define AGE_LOWER 18

/**
 * a struct that represents a student, each student has its 6 necessary fields and a score for
 * the best check.
 */
typedef struct Student
{
    char name[FIELD_MAX_SIZE];
    char country[FIELD_MAX_SIZE];
    char city[FIELD_MAX_SIZE];
    char id[FIELD_MAX_SIZE];
    int grade;
    int age;
    float score;
} Student;

/**
 * checks if the given string is in the correct id format: 10 digits and starts not with zero.
 * @param id_str - the string that we check
 * @return true if the string is in the correct format (above) and false otherwise.
 */
int checkId(char *id_str)
{
    if ((strlen(id_str) != ID_MAX_SIZE) || (strncmp(id_str, "0", 1)) == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/**
 * checks if the given string is in the correct name format: only has english letters, whitespaces
 * or '-'.
 * @param name_str - the string that we check.
 * @return true if the string is in the correct format (above) and false otherwise.
 */
int checkName(char *name_str)
{
    int i = 0;
    // checks that all the name is letters
    while (strncmp(&name_str[i], "\0", 1) != 0)
    {
        if (!(isalpha(name_str[i])) && (!(isspace(name_str[i]))) &&
            ((strncmp(&name_str[i], "-", 1) != 0)))
        {
            return 0;
        }
        i++;
    }
    return 1;
}

/**
 * checks if the given int is in the correct grade format: lower then GRADE_UPPER and above
 * GRADE_LOWER, representing bounds.
 * @param grade_num - the int that we check.
 * @return true if the int is in the correct format (above) and false otherwise.
 */
int checkGrade(int grade_num)
{
    if ((GRADE_LOWER <= grade_num) && (grade_num <= GRADE_UPPER))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * checks if the given int is in the correct age format: lower then AGE_UPPER and above AGE_LOWER,
 * representing bounds.
 * @param age_num - the int that we check.
 * @return true if the int is in the correct format (above) and false otherwise.
 */
int checkAge(int age_num)
{
    if ((AGE_LOWER <= age_num) && (age_num <= AGE_UPPER))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * if the string is a number then returns an int the is equal to it.
 * @param string - the string that we check.
 * @return the number that the string represents, if indeed it does, and -1 otherwise
 * the -1 is because later we check if this number is a correct age or grade and -1 is not.
 */
int stringToInt(char *string)
{
    int i = 0;
    int end_num = 0;
    int check;
    while (strncmp(&string[i], "\0", 1) != 0)
    {
        end_num *= 10;
        check = string[i] - '0';
        if (0 <= check && check <= 9)
        {
            end_num += check;
        }
        else
        {
            return -1;
        }
        i++;
    }
    return end_num;
}

/**
 * checks if the given string is in the correct country/city format: only has english letters or
 * '-'.
 * @param region_str - the string that we check.
 * @return true if the string is in the correct format (above) and false otherwise.
 */
int checkRegion(char *region_str)
{
    int i = 0;
    while (strncmp(&region_str[i], "\0", 1) != 0)
    {
        if (!(isalpha(region_str[i])) && ((strncmp(&region_str[i], "-", 1) != 0)))
        {
            return 0;
        }
        i++;
    }
    return 1;
}

/**
 * receives input from the user, each line represents a student in the format of:
 * <ID> TAB <NAME> TAB <GRADE> TAB <AGE> TAB <COUNTRY> TAB <CITY>
 * (whitespace here is not actual whitespace) then if the best_bool flag is true it prints the
 * best student among them,
 * otherwise it adds them to the given array of students to be sorted elsewhere.
 * @param best_bool - a flag that says if we are looking for the best student.
 * @param students_arr - the array of students we build with the input
 * (if the other flag is false).
 * @return the number of students added through the program, if any.
 */
int getStudent(int best_bool, Student students_arr[])
{
    char str[LINE_MAX_SIZE];
    Student best_student;
    best_student.score = -1;
    Student current_student;
    int temp;
    int line_counter = -1;
    int student_arr_index = 0;
    printf("Enter student info. To exit press q, then enter\n");
    fgets(str, LINE_MAX_SIZE, stdin);
    char *token = "";
    while (strncmp(str, "q", 1) != 0)
    {
        // raise the line counter for each line
        line_counter++;
        // id input
        token = strtok(str, "\t");
        if (checkId(token))
        {
            strcpy(current_student.id, token);
        }
        else
        {
            printf("ERROR: ID should be exactly 10 digits and not start with 0\nin line %d\n",
                   line_counter);
            printf("Enter student info. To exit press q, then enter\n");
            fgets(str, LINE_MAX_SIZE, stdin);
            continue;
        }
        // name input
        token = strtok(NULL, "\t");
        if (checkName(token))
        {
            strcpy(current_student.name, token);
        }
        else
        {
            printf("ERROR: name could only a combination of : english letters"
                   "(upper or lowercase), the character '-' and spaces\nin line %d\n",
                   line_counter);
            printf("Enter student info. To exit press q, then enter\n");
            fgets(str, LINE_MAX_SIZE, stdin);
            continue;
        }
        // grade input
        token = strtok(NULL, "\t");
        temp = stringToInt(token);
        if (checkGrade(temp))
        {
            current_student.grade = temp;
        }
        else
        {
            printf("ERROR: grade should be an integer between 0 and 100 only\nin line %d\n",
                   line_counter);
            printf("Enter student info. To exit press q, then enter\n");
            fgets(str, LINE_MAX_SIZE, stdin);
            continue;
        }
        // age input
        token = strtok(NULL, "\t");
        temp = stringToInt(token);
        if (checkAge(temp))
        {
            current_student.age = temp;
        }
        else
        {
            printf("ERROR: age should be an integer between 18 and 120 only\nin line %d\n",
                   line_counter);
            printf("Enter student info. To exit press q, then enter\n");
            fgets(str, LINE_MAX_SIZE, stdin);
            continue;
        }
        // country input
        token = strtok(NULL, "\t");
        if (checkRegion(token))
        {
            strcpy(current_student.country, token);
        }
        else
        {
            printf("ERROR: country could only a combination of:"
                   " english letters (upper or lowercase) and the character '-'\nin line %d\n",
                   line_counter);
            printf("Enter student info. To exit press q, then enter\n");
            fgets(str, LINE_MAX_SIZE, stdin);
            continue;
        }
        // city input
        token = strtok(NULL, "\t");
        if (checkRegion(token))
        {
            strcpy(current_student.city, token);
        }
        else
        {
            printf("ERROR: city could only a combination of:"
                   " english letters (upper or lowercase) and the character '-'\nin line %d\n",
                   line_counter);
            printf("Enter student info. To exit press q, then enter\n");
            fgets(str, LINE_MAX_SIZE, stdin);
            continue;
        }
        if (best_bool)
        {
            current_student.score = (float) current_student.grade / (float) current_student.age;
            if (current_student.score > best_student.score)
            {
                best_student = current_student;
            }
        }
        else
        {
            students_arr[student_arr_index] = current_student;
            student_arr_index++;
        }
        printf("Enter student info. To exit press q, then enter\n");
        fgets(str, LINE_MAX_SIZE, stdin);
    }
    if (best_student.score != -1 && best_bool)
    {
        printf("best student info is: %s\t%s\t%d\t%d\t%s\t%s\t\n", best_student.id,
               best_student.name, best_student.grade,
               best_student.age, best_student.country, best_student.city);
    }
    return student_arr_index;
}

/**
 * the associated merge function fot the merge sort algorithm, receives two small arrays and
 * merges them into one that is sorted.
 * @param students_arr1 - the first array.
 * @param students_arr2 - the second array.
 * @param length - the total length of both arrays.
 */
void merge(Student students_arr1[], Student students_arr2[], int length)
{
    // i - first array index runner, j - second array index runner, r - total array index runner.
    int i = 0;
    int j = 0;
    int r = 0;
    int half_length = length / 2;
    Student new_arr[STUDENTS_MAX_SIZE];
    while (r < length)
    {
        if (i == half_length)
        {
            new_arr[r] = students_arr2[j];
            j++;
            r++;
        }
        else if (j == length - half_length)
        {
            new_arr[r] = students_arr1[i];
            i++;
            r++;
        }
        else if (students_arr1[i].grade > students_arr2[j].grade)
        {
            new_arr[r] = students_arr2[j];
            j++;
            r++;
        }
        else
        {
            new_arr[r] = students_arr1[i];
            i++;
            r++;
        }
    }
    // copies all the new array to the first array, which will overflow to the second one as well
    // since we know they will be put one after the other in the memory.
    r = 0;
    while (r < length)
    {
        students_arr1[r] = new_arr[r];
        r++;
    }
}

/**
 * merge sort algorithm for students by grade (ascending).
 * @param students_arr - the students array we want to sort.
 * @param length - the length of the array.
 */
void mergeStudents(Student students_arr[], int length)
{
    if (length == 1)
    {
        return;
    }
    else
    {
        int small_length = length / 2;
        mergeStudents(students_arr, small_length);
        mergeStudents(&students_arr[small_length], length - small_length);
        merge(students_arr, &students_arr[small_length], length);
    }
}

/**
 * a function that prints all the students in the given student array.
 * @param student_arr - the array of students.
 * @param arr_length - the length of the array.
 */
void printStudents(Student student_arr[], int arr_length)
{
    for (int i = 0; i < arr_length; i++)
    {
        printf("%s\t%s\t%d\t%d\t%s\t%s\t\n", student_arr[i].id, student_arr[i].name,
               student_arr[i].grade,
               student_arr[i].age, student_arr[i].country, student_arr[i].city);
    }
}

/**
 * the partition function for the student quick sort, returns the index of the item that is in
 * its final correct place after partitioning.
 * @param students_arr - the current array we are working on.
 * @param low - the lower barrier of the current sort.
 * @param high - the upper barrier of the current sort.
 * @return the index of the item that is in its final correct place after partitioning.
 */
int partition(Student students_arr[], int low, int high)
{
    // choose pivot and move it to the side
    int pivot_location = low + (high - low) / 2;
    Student pivot_student = students_arr[pivot_location];
    Student temp = students_arr[pivot_location];
    students_arr[pivot_location] = students_arr[high];
    students_arr[high] = temp;
    int i = low - 1;
    int j = high;
    while (1)
    {
        do
        {
            i++;
        } while (strcmp(students_arr[i].name, pivot_student.name) < 0 && i <= high);

        do
        {
            j--;
        } while (strcmp(students_arr[j].name, pivot_student.name) > 0 && j >= 0);
        if (i >= j)
        {
            temp = students_arr[j + 1];
            students_arr[j + 1] = students_arr[high];
            students_arr[high] = temp;
            return j + 1;
        }
        temp = students_arr[j];
        students_arr[j] = students_arr[i];
        students_arr[i] = temp;
    }
}

/**
 * quick sort algorithm for students by name alphabetically (ascending).
 * @param students_arr - the array of students to sort.
 * @param low - the lower barrier of the current sort.
 * @param high - the upper barrier of the current sort.
 */
void quickStudents(Student students_arr[], int low, int high)
{
    int partition_index;
    if (low < high)
    {
        partition_index = partition(students_arr, low, high);
        quickStudents(students_arr, low, partition_index - 1);
        quickStudents(students_arr, partition_index + 1, high);
    }
}

/**
 * the main program, depends on the argument eceived either collects student info and prints
 * the best one among them or sorts the given students with merge sort/quick sort.
 * @param argc - the number of arguments.
 * @param argv - the arguments themselves.
 * @return 1 if there was a usage problem, 0 if it finished regular.
 */
int main(int argc, char **argv)
{
    (void) argc;
    Student students_arr[STUDENTS_MAX_SIZE];
    int arr_length = 0;
    if (strncmp(argv[1], "best", 4) == 0)
    {
        getStudent(1, students_arr);
    }
    else if (strncmp(argv[1], "quick", 5) == 0)
    {
        arr_length = getStudent(0, students_arr);
        if (arr_length > 0)
        {
            quickStudents(students_arr, 0, arr_length - 1);
            printStudents(students_arr, arr_length);
        }
    }
    else if (strncmp(argv[1], "merge", 5) == 0)
    {
        arr_length = getStudent(0, students_arr);
        if (arr_length > 0)
        {
            mergeStudents(students_arr, arr_length);
            printStudents(students_arr, arr_length);
        }
    }
    else
    {
        printf("USAGE: the program only accepts three possible arguments:\n"
               "best - to find the best student among the given students\n"
               "merge - to sort the students given using merge sort\n"
               "quick - to sort the students given using quick sort\n"
               "any different argument set will result in this message and exit.\n");
        return 1;
    }
}