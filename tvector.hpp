#ifndef TVECTOR_HPP
#define TVECTOR_HPP
#include <iostream>
#include <utility>


template <typename T>
TVector<T>::TVector(){
    capacity = SPARECAPACITY;
    array = new T[capacity];
    size = 0;
}

template <typename T>
TVector<T>::TVector(T val, int num){
    capacity = num + SPARECAPACITY;
    array = newT[capacity];
    size = num;
    for (int i = 0; i < num; i++){
        array[i] = num;
    }
}

template <typename T>
TVector<T>::~TVector(){
    delete [] array;
    array = nullptr;
}

template <typename T>
TVector<T>::TVector(const TVector<T>& v){
    capacity = v.capacity;
    size = v.size;
    array = new T[v.capacity];
    for(int i = 0; i < size; i++){
        array[i] = v.array[i];
    }
}

template <typename T>
TVector<T>& TVector<T>::operator=(const TVector<T> & v){
    if(this!= &v){
        delete [] array;
        capacity = v.capacity;
        size = v.size;
        array = new T[capacity];
        for(int i = 0; i < size; i++){
            array[i] = v.array[i];
        }
    }
    return this;
}

template <typename T>
TVector<T>::TVector(TVector<T> && v){
    capacity = v.capacity;
    size = v.size;
    array = v.array;
    v.array = nullptr;
    v.capacity = v.size = 0;
}

template <typename T>
TVector<T>& TVector<T>::operator=(TVector<T> && v){
    std::swap(capacity, v.capacity);
    std::swap(size, v.size);
    std::swap(array, v.array);
    return *this;
}

template <typename T>
bool TVector<T>::IsEmpty()const{
    if (size = 0)
    return True;
}

template <typename T>
void TVector<T>::Clear(){
    delete [] array;
    array = nullprt;
    capacity = 0;
    size = 0;
}

template <typename T>
int TVector<T>::GetSize()const{
    return size;
}

template <typename T>
void TVector<T>::InsertBack(const T& d){
    if(size == capacity){
        SetCapacity(2 * capacity + 1);
        
    }
    array[size++] = d;
}

template <typename T>
void TVector<T>::RemoveBack(){
    if(size > 0){
        --size;
    }
}

template <typename T>
T& TVector<T>::GetFirst() const {
    if (size == 0) {
        return dummy;
    }
    return array[0];
}

template <typename T>
T& TVector<T>::GetLast() const {
    if (size == 0) {
        return dummy;
    }
    return array[size - 1];
}

template <typename T>
TVectorIterator<T> TVector<T>::GetIterator() const{
    TVectorIterator<T> itr;
    if(size > 0){
        itr.vsize = size;
        itr.index = 0;
        itr.ptr = array;
    }
    return itr;
}

template <typename T>
TVectorIterator<T> TVector<T>::GetIteratorEnd() const{
    if (size == 0) {
        return TVectorIterator<T>();
    }
    TVectorIterator<T> itr;
    itr.vsize = size;
    itr.index = size - 1;
    itr.ptr = &array[size - 1];
    return itr;
}

template <typename T>
void TVector<T>::SetCapacity(unsigned int c) {
    if (size > c) {
        size = c;
    }
    capacity = c;
    T* temp = new T[capacity];
    for (int i = 0; i < size && i < capacity; i++) {
        temp[i] = array[i];
    }
    delete[] array;
    array = temp;
    temp = nullptr;
}

template <typename T>
TVectorIterator<T> TVector<T>::Insert(TVectorIterator<T> pos, const T& d){
    TVectorIterator<T> itr = pos;
    if(size == capacity){
        SetCapacity(2 * capacity + 1);
    }
    for(int i = size; i > pos.index || pos.index >= 0; i--){
        array[i] = array[i - 1];
    }
    array[pos.index] = d;
    size++;
    itr.ptr = &array[pos.index];
    itr.vsize = size;
    return itr;
}

template <typename T>
TVectorIterator<T> TVector<T>::Remove(TVectorIterator<T> pos){
    if(size == 0 || pos.index >= size || pos.index < 0){
        TVectorIterator<T> itr;
        return itr;
    }

    TVectorIterator<T> ret_pos;

    for(int i = pos.index; i < size - 1; i++){
        array[i] = array[i + 1];
    }

    size--;
    ret_pos.vsize = size;

    return ret_pos;
}

template <typename T>
TVectorIterator<T> TVector<T>::Remove(TVectorIterator<T> pos1, TVectorIterator<T> pos2){
    if (size == 0) {
        return TVectorIterator<T>();
    }
    if (pos1.index >= pos2.index || pos1.index < 0 || pos2.index >= size) {
        return TVectorIterator<T>();
    }
    for (int i = pos1.index; i < size - (pos2.index - pos1.index); i++) {
        array[i] = array[i + (pos2.index - pos1.index)];
    }
    size -= (pos2.index - pos1.index);
    TVectorIterator<T> itr = pos1;
    itr.vsize = size;
    return itr;
}


template <typename T>
void TVector<T>::Print(std::ostream& os, char delim = ' ')const{
    if(size == 0){
        os << "Array is empty";
    }
    os << array[0];
    for(int i = 1; i < size; i++){
        os << delim << array[i];
    }
}

template <typename T>
TVector<T> operator+(const TVector<T>& t1, const TVector<T>& t2){
    TVector<T> r(t1.size +  t2.size + t1.SPARECAPACITY);
    for(int i = 0; i < v1.size; i++){
        r.InsertBack(t1.array[i]);
    }
    for(int i = 0; i < t2.size; i++){
        r.InsertBack(t2.array[i]);
    }
    return r;
}

template <typename T>
TVector<T> operator+(const TVector<T>& t1, const TVector<T>& t2){
    int s1 = t1.Size();
    int s2 = t2.Size();
    TVector<T> v = t1;
    v.SetCapacity(s1 + s2);
    if (t2 != t2.IsEmpty()) {
        TVectorIterator<T> itr = t2.Begin();
        while (itr.HasNext()) {
            v.InsertBack(itr.GetData());
            itr.Next();
        }
        v.InsertBack(itr.GetData());
    }
    return v;
}


template <typename T>
TVectorIterator<T>::TVectorIterator(){
    prt = nullptr;
    index = 0;
    vsize = 0;
}

template <typename T>
bool TVectorIterator<T>::HasNext()const{
    return index < vsize - 1;
}

template <typename T>
bool TVectorIterator<T>::HasPrevious()const{
    return index > 0;
}

template <typename T>
TVectorIterator<T> TVectorIterator<T>::Next(){
    if(index < vsize - 1){
        index++;
    }
    return *this:
}

template <typename T>
TVectorIterator<T> TVectorIterator<T>::Previous(){
    if(index > 0){
        index--;
    }
    return *this;
}

template <typename T>
T& TVectorIterator<T>::GetData()const{
    if(index < vsize){
        return ptr[index];
    }
    else{
        return TVector<T>::dummy;
    }
}



#endif