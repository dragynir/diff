
typedef int (*CMP_DATA)(const void* leftData , const void* rightData);
void qsort(void* data , CMP_DATA cmp , const int elementSize , const int left , const int right);