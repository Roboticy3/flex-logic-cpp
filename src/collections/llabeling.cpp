#include "llabeling.h"

#include <string>

// Implementation for Labeling class (inherits from LLabeling<T, ll>)

template<typename T>
size_t Labeling<T>::size() {
  return this->block.size();
}

template<typename T>
size_t Labeling<T>::count() {
    // Count non-empty elements in the block
    size_t count = 0;
    for (const auto& elem : this->block) {
        if (elem != T{}) {  // Check if element is not empty/default constructed
            count++;
        }
    }
    return count;
}

template<typename T>
ll Labeling<T>::add(T element) {
    // Find the lowest available empty index
    for (ll i = 0; i < this->block.size(); i++) {
        if (this->block[i] == T{}) {  // Empty slot found
            this->block[i] = element;
            return i;
        }
    }
    
    // No empty slots found, add to end
    this->block.push_back(element);
    return this->block.size() - 1;
}

template<typename T>
ll Labeling<T>::set(T element, ll at) {
    // Ensure block is large enough
    if (at >= this->block.size()) {
        this->block.resize(at + 1, T{});
    }
    
    this->block[at] = element;
    return at;
}

template<typename T>
T *Labeling<T>::get(ll at) {
    if (at >= this->block.size()) {
        return nullptr;
    }
    
    // Return nullptr if slot is empty, otherwise return pointer to element
    if (this->block[at] == T{}) {
        return nullptr;
    }
    
    return &this->block[at];
}

template<typename T>
bool Labeling<T>::remove(ll at) {
    if (at >= this->block.size()) {
        return false;
    }
    
    if (this->block[at] == T{}) {
        return false;  // Already empty
    }
    
    this->block[at] = T{};  // Set to empty/default value
    return true;
}

template<typename T>
void Labeling<T>::compress(std::vector<T> &out) {
    for (const auto& elem : this->block) {
        if (elem != T{}) {  // Only add non-empty elements
            out.push_back(elem);
        }
    }
}

// Explicit instantiations for common types
template class Labeling<std::string>;
template class Labeling<int>;
template class Labeling<double>;

