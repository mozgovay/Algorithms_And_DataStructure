#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

typedef struct {
    int key;
    int value;
} data_type;

typedef struct {
    data_type data[MAX_SIZE];
    int front;
    int back;
    int size;
} udt;

void udt_create(udt *d) {
    d->front = 0;
    d->back = -1;
    d->size = 0;
}

bool udt_is_empty(const udt *d) {
    return d->size == 0;
}

int udt_size(const udt *d) {
    return d->size;
}

void udt_push_back(udt *d, data_type elem) {
    if (d->size == MAX_SIZE) {
        printf("Дек переполнен\n");
        return;
    }
    d->back = (d->back + 1) % MAX_SIZE;
    d->data[d->back] = elem;
    d->size++;
}

void udt_push_front(udt *d, data_type elem) {
    if (d->size == MAX_SIZE) {
        printf("Дек переполнен\n");
        return;
    }
    d->front = (d->front - 1 + MAX_SIZE) % MAX_SIZE;
    d->data[d->front] = elem;
    d->size++;
    if (d->size == 1)
        d->back = d->front;
}

void udt_pop_front(udt *d) {
    if (udt_is_empty(d)) {
        printf("Дек пуст\n");
        return;
    }
    d->front = (d->front + 1) % MAX_SIZE;
    d->size--;
}

void udt_pop_back(udt *d) {
    if (udt_is_empty(d)) {
        printf("Дек пуст\n");
        return;
    }
    d->back = (d->back - 1 + MAX_SIZE) % MAX_SIZE;
    d->size--;
}

data_type udt_get_front(const udt *d) {
    if (udt_is_empty(d)) {
        printf("Дек пуст\n");
        exit(1);
    }
    return d->data[d->front];
}

data_type udt_get_back(const udt *d) {
    if (udt_is_empty(d)) {
        printf("Дек пуст\n");
        exit(1);
    }
    return d->data[d->back];
}

void udt_print(const udt *d) {
    int i;
    printf("Дек: ");
    for (i = 0; i < d->size; i++) {
        int index = (d->front + i) % MAX_SIZE;
        printf("(%d,%d) ", d->data[index].key, d->data[index].value);
    }
    printf("\n");
}

void udt_to_array(const udt *d, data_type arr[]) {
    int i;
    for (i = 0; i < d->size; i++) {
        int index = (d->front + i) % MAX_SIZE;
        arr[i] = d->data[index];
    }
}

void array_to_udt(udt *d, data_type arr[], int n) {
    int i;
    udt_create(d);
    for (i = 0; i < n; i++) {
        udt_push_back(d, arr[i]);
    }
}

int partition(data_type arr[], int low, int high) {
    int pivot = arr[high].key;
    int i = low - 1;
    int j;
    for (j = low; j < high; j++) {
        if (arr[j].key <= pivot) {
            i++;
            data_type temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    data_type temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

void quick_sort(data_type arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

void udt_sort(udt *d) {
    data_type arr[MAX_SIZE];
    udt_to_array(d, arr);
    quick_sort(arr, 0, d->size - 1);
    array_to_udt(d, arr, d->size);
}

void udt_concatenate(const udt *d1, const udt *d2, udt *result) {
    int i;
    udt_create(result);
    for (i = 0; i < d1->size; i++) {
        int index = (d1->front + i) % MAX_SIZE;
        udt_push_back(result, d1->data[index]);
    }
    for (i = 0; i < d2->size; i++) {
        int index = (d2->front + i) % MAX_SIZE;
        udt_push_back(result, d2->data[index]);
    }
}

int main() {
    udt d1, d2, result;
    int n1, n2;
    int i;
    
    udt_create(&d1);
    udt_create(&d2);
    
    printf("Введите количество элементов первого дека: ");
    scanf("%d", &n1);
    printf("Введите key и value для первого дека:\n");
    for (i = 0; i < n1; i++) {
        data_type temp;
        printf("Элемент %d: ", i + 1);
        scanf("%d %d", &temp.key, &temp.value);
        udt_push_back(&d1, temp);
    }
    
    printf("\nВведите количество элементов второго дека: ");
    scanf("%d", &n2);
    printf("Введите key и value для второго дека:\n");
    for (i = 0; i < n2; i++) {
        data_type temp;
        printf("Элемент %d: ", i + 1);
        scanf("%d %d", &temp.key, &temp.value);
        udt_push_back(&d2, temp);
    }
    
    printf("\nПервый дек:\n");
    udt_print(&d1);
    printf("Второй дек:\n");
    udt_print(&d2);
    
    udt_sort(&d1);
    udt_sort(&d2);
    
    printf("\nПосле сортировки:\n");
    printf("Первый дек:\n");
    udt_print(&d1);
    printf("Второй дек:\n");
    udt_print(&d2);
    
    udt_concatenate(&d1, &d2, &result);
    
    printf("\nРезультат конкатенации:\n");
    udt_print(&result);
    
    return 0;
}
