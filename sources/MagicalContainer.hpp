#ifndef MAGICALCONTAINER_HPP
#define MAGICALCONTAINER_HPP
#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
using namespace std;

namespace ariel
{
    class MagicalContainer
    {
    private:
        vector<int> elements;
        vector<int> sortedElements;
        vector<int> primeElements;
    public:
        MagicalContainer();
        void addElement(int element);
        void removeElement(int element);
        virtual int size();

        //MagicalContainer(const MagicalContainer& other) = default;
        virtual ~MagicalContainer() = default;
        
        
        //for tidy: a copy constructor, a copy assignment operator, a move constructor or a move assignment operator
        MagicalContainer(MagicalContainer &other); // copy constructor
        MagicalContainer& operator=(const MagicalContainer& other); // copy assignment 
        MagicalContainer(MagicalContainer&& other) noexcept = default; // move constructor
        MagicalContainer& operator=(MagicalContainer&&) noexcept; // move assignment
        
        // MagicalContainer& operator==(const MagicalContainer& other);
        // MagicalContainer& operator!=(const MagicalContainer& other);
       

        // Iterator classes
        class AscendingIterator;
        class SideCrossIterator; 
        class PrimeIterator;
        
        //getters setters
        vector<int> getElements() const { return elements; }
        vector<int> getSortedElements() const { return sortedElements; }
        vector<int> getPrimeElements() const { return primeElements; }


    };

       class  MagicalContainer::AscendingIterator
        {
        private:
            MagicalContainer &container;
            size_t current;

        public:
            AscendingIterator(MagicalContainer &container);
            AscendingIterator &operator=(const AscendingIterator &other); // assignment
            ~AscendingIterator() = default;                               // destructor

            // for tidy satisfaction:
            AscendingIterator(const AscendingIterator &other) noexcept; // copy constructor
            AscendingIterator(AscendingIterator&& other) noexcept = default;
            AscendingIterator& operator=(AscendingIterator&&) noexcept;

            int operator*() const;                               // dereference
            AscendingIterator &operator++();                      // increment
                                                                  // const AscendingIterator operator++(int);
            bool operator==(const AscendingIterator &rhs) const;  // compare
            bool operator!=(const AscendingIterator &rhs) const;  // compare
            bool operator>(const AscendingIterator &other) const; // greater
            bool operator<(const AscendingIterator &other) const; // smaller

            AscendingIterator& begin();
            AscendingIterator& end();

        }; // end of AscendingIterator class

        class  MagicalContainer::SideCrossIterator
        {
        private:
            MagicalContainer &container;
            size_t forward;
            size_t backward;
            bool isForward;

        public:
            SideCrossIterator(MagicalContainer &container);
            SideCrossIterator &operator=(const SideCrossIterator &other); // assignment
            ~SideCrossIterator() = default;                               // destructor

            // for tidy satisfaction:
            SideCrossIterator(const SideCrossIterator &other) noexcept; // copy constructor
            SideCrossIterator(SideCrossIterator&& other) noexcept = default;
            SideCrossIterator& operator=(SideCrossIterator&&) noexcept ;

            

            int operator*() const;                               // dereference
            SideCrossIterator &operator++();                      // increment
            // const SideCrossIterator operator++(int);
            bool operator==(const SideCrossIterator &rhs) const;  // compare
            bool operator!=(const SideCrossIterator &rhs) const;  // compare
            bool operator>(const SideCrossIterator &other) const; // greater
            bool operator<(const SideCrossIterator &other) const; // smaller


            SideCrossIterator& begin();
            SideCrossIterator& end();
        };  // end of SideCrossIterator class


        class  MagicalContainer::PrimeIterator
        {
        private:
            MagicalContainer &container;
            size_t current;

        public:
            PrimeIterator(MagicalContainer &container);
            PrimeIterator &operator=(const PrimeIterator &other); // assignment
            ~PrimeIterator() = default;                               // destructor

            // for tidy satisfaction:
           PrimeIterator(const PrimeIterator &other) noexcept; // copy constructor
            PrimeIterator(PrimeIterator&& other) noexcept = default;
            PrimeIterator& operator=(PrimeIterator&&) noexcept;


            int operator*() const;                               // dereference
            PrimeIterator &operator++();                      // increment
            // const PrimeIterator operator++(int);
            bool operator==(const PrimeIterator &rhs) const;  // compare
            bool operator!=(const PrimeIterator &rhs) const;  // compare
            bool operator>(const PrimeIterator &other) const; // greater
            bool operator<(const PrimeIterator &other) const; // smaller


            PrimeIterator& begin();
            PrimeIterator& end();
        };  // end of PrimeIterator class

};
#endif