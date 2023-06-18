#include "doctest.h"
#include <stdexcept>
#include <iostream>
#include <sstream>
#include "MagicalContainer.hpp"

using namespace ariel;
using namespace std;

TEST_CASE("1 - adding elements to MagicalContainer")
{
    MagicalContainer container;

    container.addElement(1);
    container.addElement(2);
    container.addElement(3);
    container.addElement(4);
    CHECK(container.size() == 4);
}

TEST_CASE("2 - removing elements from MagicalContainer")
{
    MagicalContainer container;
    CHECK_THROWS_AS(container.removeElement(1), runtime_error); // Removing a non-existing element
    container.addElement(1);
    CHECK(container.size() == 1);
    CHECK_NOTHROW(container.removeElement(1)); // Removing an existing element
    CHECK(container.size() == 0);
}

TEST_CASE("3 - AscendingIterator test ")
{
    MagicalContainer container;
    MagicalContainer::AscendingIterator it(container);
    CHECK(it == it.end()); // the container is empty
    container.addElement(10);
    container.addElement(3);

    CHECK(*it == 3);
    ++it;
    CHECK(*it == 10);
    ++it;
    CHECK(it == it.end());

    container.addElement(1);
    it=it.begin();
    CHECK(*it == 1); 
    ++it;
    CHECK(*it == 3);
    ++it;
    CHECK(*it == 10);
    ++it;
    CHECK(it == it.end());
}

TEST_CASE("4 - SideCrossIterator test ")
{
    MagicalContainer container;
    MagicalContainer::SideCrossIterator it(container);
    CHECK(it == it.end()); // since the container is empty
    container.addElement(10);
    container.addElement(3);
    container.addElement(50);
    container.addElement(33);
    container.addElement(1);
    CHECK(*it == 10);
    ++it;
    CHECK(*it == 1);
    ++it;
    CHECK(*it == 3);
    ++it;
    CHECK(*it == 33);
    ++it;
    CHECK(*it == 50);
    ++it;
    CHECK(it == it.end());
    container.removeElement(10);
    container.removeElement(1);
    it=it.begin();
    CHECK(*it == 3);
    ++it;
    CHECK(*it == 33);
    ++it;
    CHECK(*it == 50);
    ++it;
    CHECK(it == it.end());


}


TEST_CASE("5 - PrimeIterator test ")
{
    MagicalContainer container;
    MagicalContainer::PrimeIterator it(container);
    CHECK(it == it.end()); // the container is empty
    container.addElement(10);
    container.addElement(3);
    container.addElement(50);
    container.addElement(11);
    container.addElement(1);
    CHECK(*it == 3);
    ++it;
    CHECK(*it == 11);
    ++it;
    CHECK(it == it.end());
    //remove primes:
    container.removeElement(3);
    container.removeElement(11);
    it=it.begin();
    CHECK(it == it.end()); // since there are no primes in the container, there is nothing to iterate on
    

}

// TEST_CASE("")



