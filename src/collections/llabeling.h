#pragma once

#include <vector>

typedef long long ll;

/*
IsEmpty from the Go library will be replaced here with simply { 0 } in general.

Any emptyable type should be a struct that can be initialize using this macro.
*/
#define EMPTY = { 0 }

/*
Mapping between indices and elements where an element is assigned the lowest
empty index.

Use Godot Vector type since this structure will have to interact a lot with the engine.
*/
template<typename T, typename L>
class LLabeling {
  public:
    /*
    Number of accessible labels, including those mapped to empty entries
    */
    size_t size();

    /*
    Number of labeled elements
    */
    size_t count();

    /*
    Add `element` to the labeling at lowest possible label
    */
    L add(T element);

    /*
    Overwrite exact label `at` with `element`
    */
    L set(T element, L at);

    /*
    Get pointer to element with label `at`, or `nullptr` if that label is empty.
    */
    T *get(L at);

    /*
    Remove label `at`, such that `get(at) == nullptr` after removal.
    */
    bool remove(L at);

    /*
    Copy the elements onto the end of `out`. Used for printing contents.
    */
    void compress(std::vector<T> &out);
};

//forward declare with the default labeling type `ll`
template<typename T>
class Labeling : public LLabeling<T, ll> {
  private:
    std::vector<T> block;
  public:
    size_t size();
    size_t count();
    ll add(T element);
    ll set(T element, ll at);
    T *get(ll at);
    bool remove(ll at);
    void compress(std::vector<T> &out);
};