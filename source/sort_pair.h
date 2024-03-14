/* date = March 2nd 2024 0:50 am */

#ifndef SORT_PAIR_H
#define SORT_PAIR_H



typedef struct
{
    u32 id;
    f32 key;
}SortPair;



extern inline void
sort_pair_swap(SortPair *a, SortPair *b)
{
    SortPair c = *b;
    *b = *a;
    *a = c;
}

void
quick_sort_recursive(SortPair* items, i32 first, i32 last)
{
    i32 i, j, pivot;
    
    if(first < last)
    {
        pivot = first;
        i = first;
        j = last;
        
        while(i < j)
        {
            while(items[i].key <= items[pivot].key && i < last)
                i++;
            while(items[j].key > items[pivot].key)
                j--;
            if(i < j)
            {
                sort_pair_swap(&items[i], &items[j]);
            }
        }
        sort_pair_swap(&items[pivot], &items[j]);
        quick_sort_recursive(items, first, j - 1);
        quick_sort_recursive(items, j+1, last);
    }
}

void
quick_sort(SortPair *first, u32 count)
{
    if(count > 0)
    {
        quick_sort_recursive(first, 0, count - 1);
    }
}



#endif //SORT_PAIR_H
