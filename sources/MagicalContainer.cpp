#include "MagicalContainer.hpp"
#include <iostream>

// #include <cmath>
using namespace std;
namespace ariel{
    
    MagicalContainer::MagicalContainer(){}
    void MagicalContainer::addElement(int){}
    int MagicalContainer::size(){}
    void MagicalContainer::removeElement(int){}

    MagicalContainer::AscendingIterator::AscendingIterator( MagicalContainer& container) : container(container), current(0){}
    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(const AscendingIterator& other){}
    int& MagicalContainer::AscendingIterator::operator*() const{}
    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++(){}




};


