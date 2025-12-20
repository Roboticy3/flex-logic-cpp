#include <string>

#include "collections/llabeling.h"

// Implementation for Labeling class (inherits from LLabeling<T, ll>)

template<typename T>
size_t Labeling<T>::size() {
  return this->buffer.size();
}

template<typename T>
size_t Labeling<T>::count() {
    // Count non-empty elements in the buffer
    size_t count = 0;
    for (const auto& elem : this->buffer) {
        if (!is_empty(elem)) {  // Check if element is not empty/default constructed
            count++;
        }
    }
    return count;
}

template<typename T>
ll Labeling<T>::add(T element) {
    // Find the lowest available empty index
    for (ll i = 0; i < this->buffer.size(); i++) {
        if (is_empty(this->buffer[i])) {  // Empty slot found
            this->buffer[i] = element;
            return i;
        }
    }
    
    // No empty slots found, add to end
    this->buffer.push_back(element);
    return this->buffer.size() - 1;
}

template<typename T>
ll Labeling<T>::set(T element, ll at) {
    // Ensure buffer is large enough
    if (at >= this->buffer.size()) {
        this->buffer.resize(at + 1, T{});
    }
    
    this->buffer[at] = element;
    return at;
}

template<typename T>
T *Labeling<T>::get(ll at) {
    if (at >= this->buffer.size()) {
        return nullptr;
    }
    
    // Return nullptr if slot is empty, otherwise return pointer to element
    if (is_empty(this->buffer[at])) {
        return nullptr;
    }
    
    return &this->buffer[at];
}

template<typename T>
bool Labeling<T>::remove(ll at) {
    if (at >= this->buffer.size()) {
        return false;
    }
    
    if (is_empty(this->buffer[at])) {
        return false;  // Already empty
    }
    
    this->buffer[at] = T{};  // Set to empty/default value
    return true;
}

template<typename T>
void Labeling<T>::compress(std::vector<T> &out) {
    for (const auto& elem : this->buffer) {
        if (!is_empty(elem)) {  // Only add non-empty elements
            out.push_back(elem);
        }
    }
}

// Explicit instantiations for common types
template class Labeling<std::string>;
template class Labeling<int>;
template class Labeling<double>;

template<typename T>
span<T> BlockLabeling<T>::add_block(size_t size, ll start) {
    span<T> new_block = { 0 };

    if (start < 0) {
        return new_block;
    }

    new_block.base = this;
    new_block.size = size;

    for (ll i = start; i < this->buffer.size(); i++) {
        ll j = i;
        ll end = j + size;
        for (; i < end && i < this->buffer.size(); i++) {
            if (this->blocks[i] != LABEL_EMPTY) {
                break;
            }
        }
        if (i == end) {
            new_block.index = j;
            for (size_t k = 0; k < size; k++) {
                this->blocks[j + k] = j;
            }
            return new_block;
        }
    }

    new_block.index = this->buffer.size();

    for (size_t i = 0; i < size; i++) {
        this->buffer.push_back(T{});
        this->blocks.push_back(new_block.index);
    }

    return new_block;
}

template<typename T>
bool BlockLabeling<T>::remove_block(ll from) {
    if (from < 0 || from >= this->blocks.size()) {
        return false;
    }

    ll start = this->blocks[from];
    if (start == LABEL_EMPTY) {
        return false;
    }

    for (ll i = start; i < this->blocks.size(); i++) {
        if (this->blocks[i] != from) {
            break;
        }

        this->blocks[i] = LABEL_EMPTY;
    }

    return true;
}

template<typename T>
span<T> BlockLabeling<T>::get_block(ll from) {
    span<T> result = { 0 };

    if (from < 0 || from >= this->blocks.size()) {
        return result;
    }

    ll start = this->blocks[from];
    if (start == LABEL_EMPTY) {
        return result;
    }

    result.base = this;
    result.index = this->blocks[from];

    for (ll i = start; i < this->blocks.size(); i++) {
        if (this->blocks[i] != from) {
            break;
        }

        result.size++;
    }

    return result;
}

template<typename T>
span<T> BlockLabeling<T>::set_block(ll start, span<T> source) {

    if (start < 0 || start >= this->blocks.size()) {
        return { 0 };
    }

    size_t size = start + source.size < this->buffer.size() ? source.size : this->buffer.size() - start;
    
    for (int i = 0; i < size; i++) {
        this->buffer[start + i] = source[i];
        this->blocks[start + i] = start;
    }

    return span<T>{this, size_t(start), size};
}

template<typename T>
std::vector<std::vector<T>> BlockLabeling<T>::compress_blocks() {
    std::vector<std::vector<T>> result;
    
    if (this->blocks.empty()) {
        return result;
    }

    ll current_block_start = LABEL_EMPTY;
    std::vector<T> current_block_data;

    for (ll i = 0; i < this->blocks.size(); i++) {
        ll block_start = this->blocks[i];
        
        // Skip empty slots
        if (block_start == LABEL_EMPTY) {
            continue;
        }

        // If we found a new block start
        if (block_start == i) {
            // If we were building a block, add it to results
            if (!current_block_data.empty()) {
                result.push_back(std::move(current_block_data));
                current_block_data.clear();
            }
            current_block_start = block_start;
        }

        // Add the element to the current block
        if (i < this->buffer.size()) {
            current_block_data.push_back(this->buffer[i]);
        }
    }

    // Add the last block if there is one
    if (!current_block_data.empty()) {
        result.push_back(std::move(current_block_data));
    }

    return result;
}

template class BlockLabeling<std::string>;
template class BlockLabeling<int>;
template class BlockLabeling<double>;
template class BlockLabeling<char>;