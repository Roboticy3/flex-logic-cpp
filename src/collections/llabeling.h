#pragma once

#include <cstddef>
#include <string>
#include <functional>
#include <vector>

/*
Buffers are vectors that should not be moved.
*/
template<typename T>
class Buffer : public std::vector<T> {};

typedef long long ll;

#define LABEL_EMPTY -1

template<typename T>
inline bool is_empty(T element) {
  return element == T{};
}

inline bool is_empty(ll label) {
  return label == -1;
}

/*
Mapping between indices and elements where an element is assigned the lowest
empty index.
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

Empty values correspond IsEmpty, and T must be a literal.
*/
template<typename T>
class Labeling : public LLabeling<T, ll> {
  protected:
    Buffer<T> buffer;
  public:
    Labeling() {};
    Labeling(Buffer<T> buffer) : buffer(buffer) {};

    size_t size();
    size_t count();
    ll add(T element);
    ll set(T element, ll at);
    T *get(ll at);
    bool remove(ll at);
    void compress(std::vector<T> &out);

    std::vector<T> copy_buffer();

    T &operator[](size_t idx) { return buffer[idx]; }
};

/*
Spans are slices of buffers that are retained when the buffer grows.
*/
template<typename T>
struct span {
  Labeling<T> *base;
  size_t index;
  size_t size;
  
  T& operator[](size_t idx) { return (*base)[index + idx]; }
};

template<typename T>
class BlockLabeling : private Labeling<T> {
  protected:
    /*
    Equal in length to `this->buffer`, each entry points to the beginning of an
    allocated block in the labeling. If the entry is -1, the index is not part
    of any block.
    */
    std::vector<ll> blocks;
  public:

    /*
    Find the first available contiguous span of entries with block start -1,
    reserve them and return the span.

    `start` is the starting index in the container where the method will start
    searching for blocks.

    If no blocks are found, grow `buffer` and `blocks`.

    O(n)
    */
    span<T> add_block(size_t size, ll start=0);

    /*
    Remove the block allocated to `from`. Returns false if `from` is not in an
    allocated block.

    O(n)
    */
    bool remove_block(ll from);

    /*
    Return the block allocated to `from`. If `from` is not in an allocated
    block, return { 0 }.

    O(n)
    */
    span<T> get_block(ll from);
    
    /*
    Overwrite a block starting at `start` with the contents of a span. This
    copies the contents of the span and returns the copy.

    If the span size + `start` is longer than the internal container, grow
    the container.

    This function is more of just an exercise. In practice, this is dangerous to
    use because it invalidates spans referencing blocks that it writes into.

    O(n)
    */
    span<T> set_block(ll start, span<T> block);

    using Labeling<T>::compress;

    /*
    Return a 2d vector copying all the blocks into separate rows.

    O(n)
    */
    std::vector<std::vector<T>> compress_blocks();

    using Labeling<T>::copy_buffer;
    std::vector<ll> copy_blocks();
};

