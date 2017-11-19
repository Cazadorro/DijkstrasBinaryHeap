//
// Created by shae on 6/28/17.
//

#ifndef BINARYHEAP_BINARYHEAP_H
#define BINARYHEAP_BINARYHEAP_H

#include <vector>
#include <ostream>
#include <unordered_map>

template<typename PriorityKey, typename Value, class Comparison>
class BinaryHeap {

    using KeyValue = std::pair<PriorityKey, Value>;
    Comparison m_compare;
    std::vector<std::pair<PriorityKey, Value>> m_array;
    std::unordered_map<Value, std::size_t> m_value_index_map;

    std::size_t parent(std::size_t index) const {
        return index ? (index - 1) / 2 : index;
    }

    std::size_t left_child(std::size_t index) const {
        return 2 * index + 1;
    }

    std::size_t right_child(std::size_t index) const {
        return 2 * index + 2;
    }

    void swapIndex(std::size_t index0, std::size_t index1) {
        m_array[index0] = m_array[index1];
        m_value_index_map[m_array[index1].second] = index0;
    }

    void updateFinalIndex(std::size_t index, const KeyValue &keyvalue) {
        m_array[index] = keyvalue;
        m_value_index_map[m_array[index].second] = index;
    }

    void decreaseKey(size_t index) {
        KeyValue keyvalue = m_array[index];
        while (index != 0 && m_compare(m_array[index].first, m_array[parent(index)].first)) {
            swapIndex(index, parent(index));
            index = parent(index);
        }
        updateFinalIndex(index, keyvalue);
    }

public:
    BinaryHeap(std::size_t reserve_size) {
        m_array.reserve(reserve_size);
    }

    BinaryHeap(const Comparison &comparison) {
        m_compare = comparison;
    }

    Value top() const {
        return m_array.at(0).second;
    }

    Value pop() {
        Value temp = m_array.at(0).second;
        //m_array.erase(m_array.begin());
        std::swap(m_array[0], m_array[size() - 1]);
        m_array.erase(m_array.end() - 1);
        m_value_index_map[m_array[0].second] = 0;
        m_value_index_map.erase(m_value_index_map.find(temp));
        heapify(0);
        return std::move(temp);
    }

    bool isEmpty() const {
        return m_array.empty();
    }

    std::size_t size() const {
        return m_array.size();
    }

    void push(const PriorityKey &key, const Value &value) {
        std::size_t index = m_array.size();
        m_array.push_back(KeyValue(key, value));
        while (index > 0 && m_compare(key, m_array[parent(index)].first)) {
            swapIndex(index, parent(index));
            index = parent(index);
        }
        updateFinalIndex(index, KeyValue(key, value));
    }

    void heapify(std::size_t index) {
        std::size_t left = left_child(index);
        std::size_t right = right_child(index);
        std::size_t compare_index = index;
        KeyValue keyvalue = m_array[index];
        while (true) {
            if (left < size() && m_compare(m_array[left].first, m_array[index].first)) {
                compare_index = left;
            }
            if (right < size() && m_compare(m_array[right].first, m_array[compare_index].first)) {
                compare_index = right;
            };
            if (compare_index != index) {
                swapIndex(index, compare_index);
                index = compare_index;
            } else {
                break;
            }
        }
        updateFinalIndex(index, keyvalue);
    }

    void updateKey(const PriorityKey &key, const Value &value) {
        std::size_t index = m_value_index_map[value];
        if (m_array[index].first > key) {
            m_array[index] = KeyValue(key, value);
            decreaseKey(index);
        } else {
            m_array[index] = KeyValue(key, value);
            heapify(index);
        }
    }

    friend std::ostream &operator<<(std::ostream &stream, const BinaryHeap &binheap) {
        for (auto element : binheap.m_array) {
            stream << element.first << " : " << element.second << ", ";
        }
        return stream;
    }
};


#endif //BINARYHEAP_BINARYHEAP_H
