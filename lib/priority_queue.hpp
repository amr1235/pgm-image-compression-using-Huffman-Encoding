#ifndef __priorityQ__
#define __priorityQ__

#include <iostream>
#include <vector>

template<class valuetype>
struct heapNode
{
    valuetype value;
    int frequancy;
    heapNode<valuetype> * leftChild;
    heapNode<valuetype> * rightChild ;
};

template <class T>
class min_heap{

public : 
    std::vector<heapNode<T> *> A;
    void Insertion(heapNode<T> * info){
    A.push_back(info);
        size_t childidx = A.size() - 1;
        FixAfterInsertion(childidx);
    }
    heapNode<T> * Extraction(){
        if (A.empty() ) exit(1);
        size_t childidx = A.size() -1; 
        std::swap(A[childidx], A[0]);
        heapNode<T> * Value_of_root = A.back();
        A.pop_back();
        FixAfterExtraction(0);
        return Value_of_root;
    }

    int size(){
        return A.size();
    }
private:
    static size_t LeftChildIndex(size_t Parentindex){
        size_t L_child_idx = (Parentindex*2) + 1;
        return L_child_idx;
    }  

    static size_t RightChildIndex (size_t Parentindex){
        size_t R_child_idx = (Parentindex*2) +2 ;
        return R_child_idx;
    }
    static size_t ParentIndex (size_t Childindex){
        size_t P_idx;
        if (Childindex%2 == 1){
            P_idx = (Childindex-1)/2;
        }
        else
        {
            P_idx = (Childindex-2)/2;
        }

        return P_idx;
    }

    void FixAfterInsertion(size_t child_idx){
        size_t parent_idx = ParentIndex(child_idx);
        if (child_idx > 0 && A[child_idx]->frequancy < A[parent_idx]->frequancy){
            std::swap(A[child_idx], A[parent_idx]);
            FixAfterInsertion(parent_idx);
        }
    }

    void FixAfterExtraction(size_t parent_idx){
        size_t left_idx = LeftChildIndex(parent_idx);
        size_t right_idx = RightChildIndex(parent_idx);
        size_t minimum = parent_idx;
        if (left_idx < A.size() && A[left_idx]->frequancy < A[parent_idx]->frequancy ) {
            minimum = left_idx;
        }
        if (right_idx < A.size() && A[right_idx]->frequancy < A[parent_idx]->frequancy && A[right_idx]->frequancy < A[left_idx]->frequancy){
            minimum = right_idx;
        }
        if (minimum != parent_idx){
            std::swap(A[minimum],A[parent_idx]);
            FixAfterExtraction(minimum);
        }
    }
};

#endif