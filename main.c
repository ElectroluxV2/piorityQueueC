#include <stdio.h>
#include <stdlib.h>

const long long RAW_INPUT_BUFFER_NUMBER = 50;
struct array getArrayFromStdIn();
void printArray(struct array array);
void swap(long long* first, long long* second);

struct array {
    long long* pointer;
    unsigned long long length;
};

void heapify(struct array* array, const unsigned long long index) {
    unsigned long long largestIndex = index;
    unsigned long long leftIndex = (2 * index) + 1;
    unsigned long long rightIndex = (2 * index) + 2;

    if (leftIndex < array->length && *(array->pointer + leftIndex) < *(array->pointer + largestIndex)) {
        largestIndex = leftIndex;
    }

    if (rightIndex < array->length && *(array->pointer + rightIndex) < *(array->pointer + largestIndex)) {
        largestIndex = rightIndex;
    }

    if (largestIndex != index) {
        swap(array->pointer + index, array->pointer + largestIndex);
        heapify(array, largestIndex);
    }
}

void buildHeap(struct array* array) {
    for (unsigned long long i = (array->length / 2) - 1; i != (unsigned long long) (-1); --i) {
        heapify(array, i);
    }
}

long long extract(struct array* queue) {
    long long item = *(queue->pointer);
    *(queue->pointer) = *(queue->pointer + queue->length - 1);
    *(queue->pointer + queue->length - 1) = (long long int) NULL;
    queue->length = queue->length - 1;
    buildHeap(queue);
    return item;
}

void insert(struct array* queue, long long item) {
    // WARNING this is totally unsafe, and you must manually control not leading to overflow.
    // Maximum items in queue is constant and assigned during array creation.
    *(queue->pointer + queue->length) = item;
    queue->length = queue->length + 1;
    buildHeap(queue);
}

void freeArray(struct array* array) {
    free(array->pointer);
}

int main() {
    struct array array = getArrayFromStdIn();

    buildHeap(&array);

    unsigned long long originalLength = array.length;

    for (unsigned long long i = 0; i < originalLength - 1; i++) {
        long long left = extract(&array);
        long long right = extract(&array);

        printf("left: %lld, right: %lld\n", left, right);
        insert(&array, left + right);
    }

    freeArray(&array);
    return 0;
}

struct array getArrayFromStdIn() {
    struct array array;

    char* buffer = malloc(sizeof(char) * RAW_INPUT_BUFFER_NUMBER);
    scanf("%s", buffer);
    array.length = strtol(buffer, NULL, 10);
    free(buffer);

    array.pointer = malloc(sizeof(long long) * array.length);

    for (long long i = 0; i < array.length; i++) {
        buffer = malloc(sizeof(char) * RAW_INPUT_BUFFER_NUMBER);
        scanf("%s",  buffer);
        *(array.pointer + i) = strtoll(buffer, NULL, 10);
        free(buffer);
    }

    return array;
}

void printArray(const struct array array) {
    printf("Array (%lld) [", array.length);
    for (long long i = 0; i < array.length; i++) {
        printf("%lld%s", *(array.pointer + i), i + 1 == array.length ? "" : ", ");
    }
    printf("]\n");
}

void swap(long long* first, long long* second) {
    const long long tmp = *first;
    *first = *second;
    *second = tmp;
}
