#ifndef MAGICALCONTAINER_HPP
#define MAGICALCONTAINER_HPP
#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

// source- namespace - https://www.appmarq.com/public/changeability,8066,Avoid-using-using-namespace-or-using-declarations-in-header-files
// source- push_back vs. emplace_back - https://www.codingninjas.com/codestudio/library/vector-push_back-vs-emplace_back
// source - inline functions - https://www.geeksforgeeks.org/inline-functions-cpp/
// source - private functions - https://stackoverflow.com/questions/4505938/when-why-to-make-function-private-in-class

/* general idea: I've used nested classes to create the iterators , so there are 3 non-static inner classes in the MagicalContainer class.
 * not-static means that each iterator class have access to the  instance members of MagicalContainer, i.e, the pointer vectors and the set
 */

namespace ariel
{
    class MagicalContainer
    {
    private:
        /*
         * @brief The container's elements.
         * @note The elements are stored in a set to ensure uniqueness and sorted order.
         */
        std::set<int> _elements;
        /*
         * @brief The container's elements pointers in ascending order.
         * @note The elements are stored in a vector to allow random access and fast iteration.
         */
        std::vector<const int *> _elements_ascending_order;
        /*
         * @brief The container's elements pointers in sidecross order.
         * @note The elements are stored in a vector to allow random access and fast iteration.
         */
        std::vector<const int *> _elements_sidecross_order;
        /*
         * @brief The container's elements pointers in ascending order, with prime numbers only.
         * @note The elements are stored in a vector to allow random access and fast iteration.
         */
        std::vector<const int *> _elements_prime_order;

        /*
         * @brief Checks if a given number is prime.
         * @param num The number to check.
         * @return True if the number is prime, false otherwise.
         * @note We assume that the number is positive, any negative number will return false.
         */
        bool _isPrime(int num); // private, since it is not used outside the class MagicalContainer

    public:
        MagicalContainer();
        void addElement(int element);
        void removeElement(int element);
        size_t size() const;

        ~MagicalContainer() = default;

        // for tidy: a copy constructor, a copy assignment operator, a move constructor or a move assignment operator
        MagicalContainer(MagicalContainer &other);                     // copy constructor
        MagicalContainer &operator=(const MagicalContainer &other);    // copy assignment
        MagicalContainer(MagicalContainer &&other) noexcept = default; // move constructor
        MagicalContainer &operator=(MagicalContainer &&) noexcept;     // move assignment

        // Iterator classes
        class AscendingIterator;
        class SideCrossIterator;
        class PrimeIterator;

        // getters setters
        std::set<int> getElements() const { return _elements; }
        std::vector<const int *> getAsscendingElements() const { return _elements_ascending_order; }
        std::vector<const int *> getSortedElements() const { return _elements_sidecross_order; }
        std::vector<const int *> getPrimeElements() const { return _elements_prime_order; }
    };

    class MagicalContainer::AscendingIterator
    {
    private:
        MagicalContainer &_container;
        size_t _index;
        AscendingIterator(MagicalContainer &container, size_t _index);

    public:
        AscendingIterator(MagicalContainer &container);

        AscendingIterator &operator=(const AscendingIterator &other); // assignment
        ~AscendingIterator() = default;                               // destructor

        // for tidy satisfaction:
        AscendingIterator(const AscendingIterator &other) noexcept;      // copy constructor
        AscendingIterator(AscendingIterator &&other) noexcept = default; // move costructor
        AscendingIterator &operator=(AscendingIterator &&) noexcept;     // move assignment

        int operator*() const;                                // dereference
        AscendingIterator &operator++();                      // increment
                                                              // const AscendingIterator operator++(int);
        bool operator==(const AscendingIterator &rhs) const;  // compare
        bool operator!=(const AscendingIterator &rhs) const;  // compare
        bool operator>(const AscendingIterator &other) const; // greater
        bool operator<(const AscendingIterator &other) const; // smaller

        AscendingIterator begin()
        {
            return AscendingIterator(_container, 0);
        }
        AscendingIterator end() const
        {
            return AscendingIterator(_container, _container._elements_ascending_order.size());
        }

        int getIndex()
        {
            return _index;
        }

    }; // end of AscendingIterator class

    class MagicalContainer::SideCrossIterator
    {
    private:
        MagicalContainer &_container;
        size_t _index;
        size_t forward;
        size_t backward;
        bool isForward;
        SideCrossIterator(MagicalContainer &container, size_t index);

    public:
        SideCrossIterator(MagicalContainer &container); // constructor

        SideCrossIterator &operator=(const SideCrossIterator &other); // assignment
        ~SideCrossIterator() = default;                               // destructor

        // for tidy satisfaction:
        SideCrossIterator(const SideCrossIterator &other) noexcept;      // copy constructor
        SideCrossIterator(SideCrossIterator &&other) noexcept = default; // move constructor
        SideCrossIterator &operator=(SideCrossIterator &&) noexcept;     // move assignment

        int operator*() const;           // dereference
        SideCrossIterator &operator++(); // increment
        // const SideCrossIterator operator++(int);
        bool operator==(const SideCrossIterator &rhs) const;  // compare
        bool operator!=(const SideCrossIterator &rhs) const;  // compare
        bool operator>(const SideCrossIterator &other) const; // greater
        bool operator<(const SideCrossIterator &other) const; // smaller

        SideCrossIterator begin()
        {
            return SideCrossIterator(_container, 0);
        }
        SideCrossIterator end() const
        {
            return SideCrossIterator(_container, _container._elements_sidecross_order.size());
        }
        int getIndex()
        {
            return _index;
        }
    }; // end of SideCrossIterator class

    class MagicalContainer::PrimeIterator
    {
    private:
        MagicalContainer &_container;
        size_t _index;
        PrimeIterator(MagicalContainer &container, size_t index);

    public:
        PrimeIterator(MagicalContainer &container);

        PrimeIterator &operator=(const PrimeIterator &other); // assignment
        ~PrimeIterator() = default;                           // destructor

        // for tidy satisfaction:
        PrimeIterator(const PrimeIterator &other) noexcept;      // copy constructor
        PrimeIterator(PrimeIterator &&other) noexcept = default; // move constructor
        PrimeIterator &operator=(PrimeIterator &&) noexcept;     // move assignment

        int operator*() const;       // dereference
        PrimeIterator &operator++(); // increment
        // const PrimeIterator operator++(int);
        bool operator==(const PrimeIterator &rhs) const;  // compare
        bool operator!=(const PrimeIterator &rhs) const;  // compare
        bool operator>(const PrimeIterator &other) const; // greater
        bool operator<(const PrimeIterator &other) const; // smaller

        PrimeIterator begin()
        {
            return PrimeIterator(_container, 0);
        }
        PrimeIterator end() const
        {
            return PrimeIterator(_container, _container._elements_prime_order.size());
        }
        int getIndex()
        {
            return _index;
        }
    }; // end of PrimeIterator class

};
#endif