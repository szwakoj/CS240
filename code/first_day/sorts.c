#include "demo_2.c"

typedef struct {
    void (*sort_func)(ArrayVis* vis);
    char name[256];
} Sort;

// Bubble Sort
void bubble_sort(ArrayVis* vis)
{
    for (int i = 0; i < vis->size - 1; i++) {
        for (int j = 0; j < vis->size - i - 1; j++) {
            if (vis_compare(vis, j, j + 1, greater_than)) {
                vis_swap(vis, j, j + 1);
            }
            vis_draw(vis);
            tigrUpdate(vis->bmp);
        }
    }
    vis->highlight_i = -1;
    vis->highlight_j = -1;
}

// Selection Sort
void selection_sort(ArrayVis* vis)
{
    for (int i = 0; i < vis->size - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < vis->size; j++) {
            if (vis_compare(vis, j, min_idx, less_than)) {
                min_idx = j;
            }
            vis_draw(vis);
            tigrUpdate(vis->bmp);
        }
        if (min_idx != i) {
            vis_swap(vis, i, min_idx);
        }
    }
    vis->highlight_i = -1;
    vis->highlight_j = -1;
}

// Insertion Sort
void insertion_sort(ArrayVis* vis)
{
    for (int i = 1; i < vis->size; i++) {
        int j = i;
        while (j > 0 && vis_compare(vis, j - 1, j, greater_than)) {
            vis_swap(vis, j - 1, j);
            j--;
            vis_draw(vis);
            tigrUpdate(vis->bmp);
        }
    }
    vis->highlight_i = -1;
    vis->highlight_j = -1;
}

// Quick Sort Helper
int partition(ArrayVis* vis, int low, int high)
{
    int pivot = vis_get(vis, high);
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (vis_compare(vis, j, high, less_than)) {
            i++;
            vis_swap(vis, i, j);
            vis_draw(vis);
            tigrUpdate(vis->bmp);
        }
    }
    vis_swap(vis, i + 1, high);
    vis_draw(vis);
    tigrUpdate(vis->bmp);
    return i + 1;
}

void quick_sort_recursive(ArrayVis* vis, int low, int high)
{
    if (low < high) {
        int pi = partition(vis, low, high);
        quick_sort_recursive(vis, low, pi - 1);
        quick_sort_recursive(vis, pi + 1, high);
    }
}

void quick_sort(ArrayVis* vis)
{
    quick_sort_recursive(vis, 0, vis->size - 1);
    vis->highlight_i = -1;
    vis->highlight_j = -1;
}

// Merge Sort Helper
void merge(ArrayVis* vis, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[MAX_SIZE], R[MAX_SIZE];
    
    for (int i = 0; i < n1; i++)
        L[i] = vis_get(vis, left + i);
    for (int j = 0; j < n2; j++)
        R[j] = vis_get(vis, mid + 1 + j);
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        vis->highlight_i = left + i;
        vis->highlight_j = mid + 1 + j;
        if (L[i] <= R[j]) {
            vis->array[k] = L[i];
            i++;
        } else {
            vis->array[k] = R[j];
            j++;
        }
        k++;
        vis_draw(vis);
        tigrUpdate(vis->bmp);
    }
    
    while (i < n1) {
        vis->array[k] = L[i];
        i++;
        k++;
        vis_draw(vis);
        tigrUpdate(vis->bmp);
    }
    
    while (j < n2) {
        vis->array[k] = R[j];
        j++;
        k++;
        vis_draw(vis);
        tigrUpdate(vis->bmp);
    }
}

void merge_sort_recursive(ArrayVis* vis, int left, int right)
{
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort_recursive(vis, left, mid);
        merge_sort_recursive(vis, mid + 1, right);
        merge(vis, left, mid, right);
    }
}

void merge_sort(ArrayVis* vis)
{
    merge_sort_recursive(vis, 0, vis->size - 1);
    vis->highlight_i = -1;
    vis->highlight_j = -1;
}

// Heap Sort Helpers
void heapify(ArrayVis* vis, int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && vis_compare(vis, left, largest, greater_than))
        largest = left;
    
    if (right < n && vis_compare(vis, right, largest, greater_than))
        largest = right;
    
    if (largest != i) {
        vis_swap(vis, i, largest);
        vis_draw(vis);
        tigrUpdate(vis->bmp);
        heapify(vis, n, largest);
    }
}

void heap_sort(ArrayVis* vis)
{
    for (int i = vis->size / 2 - 1; i >= 0; i--) {
        heapify(vis, vis->size, i);
    }
    
    for (int i = vis->size - 1; i > 0; i--) {
        vis_swap(vis, 0, i);
        vis_draw(vis);
        tigrUpdate(vis->bmp);
        heapify(vis, i, 0);
    }
    vis->highlight_i = -1;
    vis->highlight_j = -1;
}

// Shell Sort
void shell_sort(ArrayVis* vis)
{
    for (int gap = vis->size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < vis->size; i++) {
            int j = i;
            while (j >= gap && vis_compare(vis, j - gap, j, greater_than)) {
                vis_swap(vis, j - gap, j);
                j -= gap;
                vis_draw(vis);
                tigrUpdate(vis->bmp);
            }
        }
    }
    vis->highlight_i = -1;
    vis->highlight_j = -1;
}

// Cocktail Shaker Sort
void cocktail_sort(ArrayVis* vis)
{
    bool swapped = true;
    int start = 0;
    int end = vis->size - 1;
    
    while (swapped) {
        swapped = false;
        
        for (int i = start; i < end; i++) {
            if (vis_compare(vis, i, i + 1, greater_than)) {
                vis_swap(vis, i, i + 1);
                swapped = true;
                vis_draw(vis);
                tigrUpdate(vis->bmp);
            }
        }
        
        if (!swapped) break;
        
        swapped = false;
        end--;
        
        for (int i = end - 1; i >= start; i--) {
            if (vis_compare(vis, i, i + 1, greater_than)) {
                vis_swap(vis, i, i + 1);
                swapped = true;
                vis_draw(vis);
                tigrUpdate(vis->bmp);
            }
        }
        start++;
    }
    vis->highlight_i = -1;
    vis->highlight_j = -1;
}

// Comb Sort
void comb_sort(ArrayVis* vis)
{
    int gap = vis->size;
    bool swapped = true;
    
    while (gap != 1 || swapped) {
        gap = (gap * 10) / 13;
        if (gap < 1) gap = 1;
        
        swapped = false;
        
        for (int i = 0; i < vis->size - gap; i++) {
            if (vis_compare(vis, i, i + gap, greater_than)) {
                vis_swap(vis, i, i + gap);
                swapped = true;
                vis_draw(vis);
                tigrUpdate(vis->bmp);
            }
        }
    }
    vis->highlight_i = -1;
    vis->highlight_j = -1;
}

// Gnome Sort
void gnome_sort(ArrayVis* vis)
{
    int i = 0;
    while (i < vis->size) {
        if (i == 0 || !vis_compare(vis, i - 1, i, greater_than)) {
            i++;
        } else {
            vis_swap(vis, i - 1, i);
            i--;
            vis_draw(vis);
            tigrUpdate(vis->bmp);
        }
    }
    vis->highlight_i = -1;
    vis->highlight_j = -1;
}

// Odd-Even Sort
void odd_even_sort(ArrayVis* vis)
{
    bool sorted = false;
    
    while (!sorted) {
        sorted = true;
        
        for (int i = 1; i < vis->size - 1; i += 2) {
            if (vis_compare(vis, i, i + 1, greater_than)) {
                vis_swap(vis, i, i + 1);
                sorted = false;
                vis_draw(vis);
                tigrUpdate(vis->bmp);
            }
        }
        
        for (int i = 0; i < vis->size - 1; i += 2) {
            if (vis_compare(vis, i, i + 1, greater_than)) {
                vis_swap(vis, i, i + 1);
                sorted = false;
                vis_draw(vis);
                tigrUpdate(vis->bmp);
            }
        }
    }
    vis->highlight_i = -1;
    vis->highlight_j = -1;
}

// Cycle Sort
void cycle_sort(ArrayVis* vis)
{
    for (int cycle_start = 0; cycle_start < vis->size - 1; cycle_start++) {
        int item = vis_get(vis, cycle_start);
        int pos = cycle_start;
        
        for (int i = cycle_start + 1; i < vis->size; i++) {
            if (vis_compare(vis, i, cycle_start, less_than)) {
                pos++;
            }
        }
        
        if (pos == cycle_start) continue;
        
        while (item == vis_get(vis, pos)) {
            pos++;
        }
        
        if (pos != cycle_start) {
            int temp = vis->array[pos];
            vis->array[pos] = item;
            item = temp;
            vis->num_swap++;
            vis_draw(vis);
            tigrUpdate(vis->bmp);
        }
        
        while (pos != cycle_start) {
            pos = cycle_start;
            
            for (int i = cycle_start + 1; i < vis->size; i++) {
                if (vis->array[i] < item) {
                    pos++;
                }
            }
            
            while (item == vis_get(vis, pos)) {
                pos++;
            }
            
            if (item != vis_get(vis, pos)) {
                int temp = vis->array[pos];
                vis->array[pos] = item;
                item = temp;
                vis->num_swap++;
                vis_draw(vis);
                tigrUpdate(vis->bmp);
            }
        }
    }
    vis->highlight_i = -1;
    vis->highlight_j = -1;
}

bool is_sorted(ArrayVis* vis, bool (*compare)(int, int)) 
{
    for(int i = 0; i < vis->size-1; i++) {
        if (!compare(vis->array[i], vis->array[i+1])){
            return false;
        }
    }
    return true;
}

void bogo_sort(ArrayVis* vis)
{
    while (!is_sorted(vis, greater_than)) {
        vis_randomize(vis);
        vis_draw(vis);
        tigrUpdate(vis->bmp);
    }

    vis->highlight_i = -1;
    vis->highlight_j = -1;
}

int num_sorted(ArrayVis* vis, bool (*compare)(int, int)) 
{
    for(int i = 0; i < vis->size-1; i++) {
        if (!compare(vis->array[i], vis->array[i+1])){
            return i;
        }
    }
    return vis->size;
}

void better_bogo_sort(ArrayVis* vis)
{
    int sorted_count = num_sorted(vis, less_than);
    do {
        sorted_count = num_sorted(vis, less_than);

        for (int i = sorted_count; i < vis->size; i++) {
            int j = sorted_count + (rand() % (vis->size - sorted_count));
            vis_swap(vis, i, j);
        }

        vis_draw(vis);
        tigrUpdate(vis->bmp);
    } while (!is_sorted(vis, less_than));

    vis->highlight_i = -1;
    vis->highlight_j = -1;
}

Sort sorts[] = {
    {bubble_sort, "Bubble Sort"},
    {selection_sort, "Selection Sort"},
    {insertion_sort, "Insertion Sort"},
    {quick_sort, "Quick Sort"},
    {merge_sort, "Merge Sort"},
    {heap_sort, "Heap Sort"},
    {shell_sort, "Shell Sort"},
    {cocktail_sort, "Cocktail Sort"},
    {comb_sort, "Comb Sort"},
    {odd_even_sort, "Odd-Even_Sort"},
    {cycle_sort, "Cycle Sort"},
    {gnome_sort, "Gnome Sort"},
    {bogo_sort, "Bogo Sort"},
    {better_bogo_sort, "Better Bogo Sort"},
};