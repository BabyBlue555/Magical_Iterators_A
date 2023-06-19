#include "MagicalContainer.hpp"
#include <iostream>
#include <stdexcept>
#include <stdexcept>

// #include <cmath>
using namespace std;
namespace ariel
{

    MagicalContainer::MagicalContainer() {}
    bool MagicalContainer::_isPrime(int num)
    {
        if (num <= 1)
        {
            return false;
        }
        for (int i = 2; i * i <= num; ++i)
        {
            if (num % i == 0)
            {
                return false;
            }
        }
        return true;
    }
    void MagicalContainer::addElement(int element)
    {
        /* @note - insert function returns A pair, an iterator that points to the possibly inserted element, and a bool that is true if the element was actually inserted.
         * @note - insertion requires logarithmic time.
         */
        auto in = _elements.insert(element);

        // edge case - if the added element is smaller than the element the iterator is currently pointing to , change thr index
        // so that the iterator will keep pointing at the same element

        if (in.second) // if the element was actually inserted
        {
            const int *address = &(*in.first); // a reference to the iterator

            _elements_ascending_order.emplace_back(address);

            if (_isPrime(element))
            {
                _elements_prime_order.emplace_back(address);
                sort(_elements_prime_order.begin(), _elements_prime_order.end(), [](const int *a, const int *b)
                     { return *a < *b; });
            }

            sort(_elements_ascending_order.begin(), _elements_ascending_order.end(), [](const int *a, const int *b)
                 { return *a < *b; });

            /*@note - it is needed to remove all the elements from the sidecross vector in order to insert the new element in a correct order
             * the reserve function preallocate enough memory for the elements, since clear function turns the vector to size 0
             */
            _elements_sidecross_order.clear();
            _elements_sidecross_order.reserve(_elements_ascending_order.size());

            size_t start = 0, end = _elements_ascending_order.size() - 1;

            /*@note - it is needed to use this loop in order to insert the existing elements in the right order in the sidecross order
            */
            while (start <= end && end != 0)
            {
                _elements_sidecross_order.emplace_back(_elements_ascending_order.at(start));

                if (start != end)
                    _elements_sidecross_order.emplace_back(_elements_ascending_order.at(end));

                start++;
                end--;
            }
            if (end == 0)
            { // single element edge case

                _elements_sidecross_order.emplace_back(_elements_ascending_order.at(start));
            }
        }
    }
    // int MagicalContainer::size(){ return ;}
    size_t MagicalContainer::size() const
    {
        return _elements.size();
    }

    void MagicalContainer::removeElement(int element)
    {
        auto it = _elements.find(element); // find function : https://cplusplus.com/reference/algorithm/find/

        if (it == _elements.end())
            throw runtime_error("Element not found");

        // Handle prime order - O(n) in this case, as we need to find the element in the vector to remove it.
        if (_isPrime(element))
        {
            auto it_prime = find(_elements_prime_order.begin(), _elements_prime_order.end(), &(*it));
            _elements_prime_order.erase(it_prime);
        }

        // Handle ascending order - O(n) in this case, as we need to find the element in the vector to remove it.
        auto it_ascending = find(_elements_ascending_order.begin(), _elements_ascending_order.end(), &(*it));
        _elements_ascending_order.erase(it_ascending);

        // Delete the element - O(logn)
        _elements.erase(element);

        // Handle sidecross order - O(n) in this case, as we need to rebuild the vector (Easier than reordering it).
        _elements_sidecross_order.clear();

        // edge case-  In case the main container is empty, we don't need to rebuild the vector.
        if (size() == 0)
            return;

        _elements_sidecross_order.reserve(_elements.size());

         // edge case - single element left in sidecross
        if (size() == 1)
            _elements_sidecross_order.push_back(_elements_ascending_order.at(0));

        // solves problem after removing element and iterating with new Sidecross iterator
        else
        {
            size_t start = 0, end = size() - 1;

            while (start <= end && end != 0) 
            {
                _elements_sidecross_order.push_back(_elements_ascending_order.at(start));

                if (start != end)
                    _elements_sidecross_order.push_back(_elements_ascending_order.at(end));

                start++;
                end--;
            }
        }
    }

    MagicalContainer &MagicalContainer::operator=(const MagicalContainer &other)
    {
        if (this != &other)
        {
            _elements_ascending_order = other._elements_ascending_order;
            _elements_sidecross_order = other._elements_sidecross_order;
            _elements_prime_order = other._elements_prime_order;
        }
        return *this;
    }

    /*----------------------------------
    *AscendingIterator functions
    ----------------------------------*/
    // constructor
    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container) : _container(container), _index(0) {}
    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container, size_t index) : _container(container), _index(index) {}
    // assignment
    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other)
    {
        if (&_container != &other._container)
        {
            throw runtime_error("Cannot assign iterators of different containers");
        }

        if (this != &other)
        {
            _container = other._container;
            _index = other._index;
        }

        return *this;
    }
    // copy constructor
    MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &other) noexcept
        : _container(other._container), _index(other._index) {}

    // dereference
    int MagicalContainer::AscendingIterator::operator*() const
    {
        if (_index > _container._elements_ascending_order.size())
        {
            throw std::out_of_range("Iterator out of range");
        }

        return *(_container._elements_ascending_order.at(_index));
    }
    // increment
    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++()
    {
        ++_index;
        if (_index > _container._elements_ascending_order.size())
        {
            throw std::runtime_error("Iterator out of range");
        }
        return *this;
    }
    //
    bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &rhs) const
    {
        return _index == rhs._index;
    }

    bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &rhs) const
    {
        // return (_index!=rhs._index);
        return !(*this == rhs); // use of last function -operator==
    }

    bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator &other) const
    {
        return _index > other._index;
    }

    bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator &other) const
    {
        return !((*this > other || *this == other));
    }

    /*----------------------------------
    *SideCrossIterator functions
    ----------------------------------*/
    // constructor
    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container)
        : _container(container), _index(0) {}
    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container, size_t index) : _container(container), _index(index) {}

    // assignment
    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other)
    {
        if (&_container != &other._container)
        {
            throw runtime_error("Cannot assign iterators of different containers");
        }

        if (this != &other)
        {
            _container = other._container;
            _index = other._index;
            forward = other.forward;
            backward = other.backward;
            isForward = other.isForward;
        }

        return *this;
    }

    // copy constructor
    MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other) noexcept : _container(other._container), _index(other._index), forward(other.forward), backward(other.backward), isForward(other.isForward) {}

    // dereference
    int MagicalContainer::SideCrossIterator::operator*() const
    {
        if (_index > _container._elements_sidecross_order.size())
        {
            throw std::out_of_range("Iterator out of range, ****");
        }

        return *(_container._elements_sidecross_order.at(_index));
    }
    // increment
    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++()
    {
        ++_index;
        if (_index > _container._elements_sidecross_order.size())
        {
            throw std::runtime_error("Iterator out of range");
        }

        return *this;
    }
    //
    bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &rhs) const
    {
        return _index == rhs._index;
    }

    bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &rhs) const
    {
        return !(*this == rhs);
    }

    bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const
    {
        return _index > other._index;
    }

    bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const
    {
        return !((*this > other || *this == other));
    }

    /*----------------------------------
    *PrimeIterator functions
    ----------------------------------*/

    // constructor
    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &container)
        : _container(container), _index(0) {}

    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &container, size_t index) : _container(container), _index(index) {}
    // assignment
    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other)
    {
        if (&_container != &other._container)
        {
            throw runtime_error("Cannot assign iterators of different containers");
        }
        if (this != &other)
        {
            _container = other._container;
            _index = other._index;
        }
        return *this;
    }

    // copy constructor
    MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other) noexcept : _container(other._container), _index(other._index) {}

    // dereference
    int MagicalContainer::PrimeIterator::operator*() const
    {
        if (_index > _container._elements_prime_order.size())
        {
            throw std::out_of_range("Iterator out of range");
        }

        return *(_container._elements_prime_order.at(_index));
    }
    // increment
    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++()
    {
        ++_index;
        if (_index > _container._elements_prime_order.size())
        {
            throw std::runtime_error("Iterator out of range");
        }

        return *this;
    }
    //
    bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &rhs) const
    {
        return _index == rhs._index;
    }

    bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &rhs) const
    {
        return !(*this == rhs);
    }

    bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &other) const
    {
        return _index > other._index;
        ;
    }

    bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator &other) const
    {
        return !((*this > other || *this == other));
    }

};
