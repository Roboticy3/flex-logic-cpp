#pragma once

#include <vector>

typedef long long ll;

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

/*
Specialized labeling for numeric labels ll

Empty values correspond to { 0 } or T{}, and T must be a literal.
*/
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

/*
Specialized labeling on labels

Empty labels are -1
*/
class LabelLabeling : public LLabeling<ll, ll> {
  private:
    std::vector<ll> block;
    static constexpr ll EMPTY_VALUE = -1;
  public:
    size_t size();
    size_t count();
    ll add(ll element);
    ll set(ll element, ll at);
    ll *get(ll at);
    bool remove(ll at);
    void compress(std::vector<ll> &out);
};