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
    container.addElement(50);
    container.addElement(33);
    container.addElement(1);
    CHECK(*it == 1);
    ++it;
    CHECK(*it == 3);
    ++it;
    CHECK(*it == 10);
    ++it;
    CHECK(*it == 33);
    ++it;
    CHECK(*it == 50);
    ++it;

    CHECK(it == it.end());
    CHECK_THROWS_AS(++it, runtime_error); // iterator out of range

    container.removeElement(10);
    container.removeElement(1);
    CHECK(container.size() == 3);

    MagicalContainer::AscendingIterator it2(container);
    CHECK(*it2 == 3);
    ++it2;
    CHECK(*it2 == 33);
    ++it2;
    CHECK(*it2 == 50);
    ++it2;
    CHECK(it2 == it2.end());
    CHECK_THROWS_AS(++it2, runtime_error); // iterator out of range
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
    CHECK(*it == 1);
    ++it;
    CHECK(*it == 50);
    ++it;
    CHECK(*it == 3);
    ++it;
    CHECK(*it == 33);
    ++it;
    CHECK(*it == 10);
    ++it;
    CHECK(it == it.end());
    CHECK_THROWS_AS(++it, runtime_error); // iterator out of range

    container.removeElement(10);
    container.removeElement(1);
    CHECK(container.size() == 3);

    MagicalContainer::SideCrossIterator it2(container);
    CHECK(*it2 == 3);
    ++it2;
    CHECK(*it2 == 50);
    ++it2;
    CHECK(*it2 == 33);
    ++it2;
    CHECK(it2 == it2.end());
    CHECK_THROWS_AS(++it2, runtime_error); // iterator out of range
}

TEST_CASE("5 - PrimeIterator test ")
{
    MagicalContainer container;
    MagicalContainer::PrimeIterator it1(container);

    CHECK(it1 == it1.end()); // the container is empty
    container.addElement(10);
    container.addElement(3);
    container.addElement(50);
    container.addElement(11);
    container.addElement(1);
    CHECK(*it1 == 3);
    ++it1;
    CHECK(*it1 == 11);
    ++it1;
    CHECK(it1 == it1.end());
    // remove primes:
    container.removeElement(3);
    container.removeElement(11);
    CHECK(container.size() == 3);          // all the non-primes are left
    CHECK_THROWS_AS(++it1, runtime_error); // iterator out of range
    MagicalContainer::PrimeIterator it2(container);
    MagicalContainer::AscendingIterator it3(container); // there are still non-primes to iterate on
    CHECK(it2 == it2.end());                            // there are no primes left - nothing to iterate on
    CHECK_THROWS_AS(++it2, runtime_error);              // iterator out of range
    CHECK(*it3 == 1);
    ++it3;
    CHECK(*it3 == 10);
    ++it3;
    CHECK(*it3 == 50);
    ++it3;
    CHECK_THROWS_AS(++it3, runtime_error); // iterator out of range
}

TEST_CASE("6 -Comparing AscendingIterator ")
{
    MagicalContainer container;
    MagicalContainer::AscendingIterator it1(container);
    MagicalContainer::AscendingIterator it2(container);
    container.addElement(1);
    container.addElement(2);
    container.addElement(4);
    container.addElement(5);
    container.addElement(14);

    CHECK((*it1 == 1 && *it2 == 1));
    CHECK((it1 == it2));
    CHECK_FALSE((it1 != it2));
    CHECK_FALSE((it1 > it2));
    CHECK_FALSE((it1 < it2));

    ++it1;
    CHECK((*it1 == 2 && *it2 == 1));
    CHECK_FALSE((it1 == it2));
    CHECK((it1 != it2));
    CHECK((it1 > it2));
    CHECK_FALSE((it1 < it2));

    ++it2;
    CHECK((*it1 == 2 && *it2 == 2));
    CHECK((it1 == it2));
    CHECK_FALSE((it1 != it2));
    CHECK_FALSE((it1 > it2));
    CHECK_FALSE((it1 < it2));

    ++it1;
    ++it1;
    CHECK((*it1 == 5 && *it2 == 2));
    CHECK_FALSE((it1 == it2));
    CHECK((it1 != it2));
    CHECK((it1 > it2));
    CHECK_FALSE((it1 < it2));

    for (int i = 0; i <= 2; i++)
    {
        ++it2;
    }
    CHECK((*it1 == 5 && *it2 == 14));
    CHECK_FALSE((it1 == it2));
    CHECK((it1 != it2));
    CHECK((it1 < it2));
    CHECK_FALSE((it1 > it2));

    ++it1;
    CHECK((*it1 == 14 && *it2 == 14));
    CHECK((it1 == it2));
    CHECK_FALSE((it1 != it2));
    CHECK_FALSE((it1 > it2));
    CHECK_FALSE((it1 < it2));

    ++it1;
    ++it2;
    CHECK(it1 == it1.end());
    CHECK(it2 == it2.end());
}

TEST_CASE("7 -Comparing SideCrossIterator ")
{
    MagicalContainer container;
    MagicalContainer::SideCrossIterator it1(container);
    MagicalContainer::SideCrossIterator it2(container);
    container.addElement(1);
    container.addElement(2);
    container.addElement(4);
    container.addElement(5);
    container.addElement(14);

    CHECK((*it1 == 1 && *it2 == 1));
    CHECK((it1 == it2));
    CHECK_FALSE((it1 != it2));
    CHECK_FALSE((it1 > it2));
    CHECK_FALSE((it1 < it2));

    ++it1;
    CHECK((*it1 == 14 && *it2 == 1));
    CHECK_FALSE((it1 == it2));
    CHECK((it1 != it2));
    CHECK((it1 > it2));
    CHECK_FALSE((it1 < it2));

    ++it2;
    CHECK((*it1 == 14 && *it2 == 14));
    CHECK((it1 == it2));
    CHECK_FALSE((it1 != it2));
    CHECK_FALSE((it1 > it2));
    CHECK_FALSE((it1 < it2));

    ++it1;
    ++it1;
    CHECK((*it1 == 5 && *it2 == 14));
    CHECK_FALSE((it1 == it2));
    CHECK((it1 != it2));
    CHECK((it1 > it2));
    CHECK_FALSE((it1 < it2));

    for (int i = 0; i <= 2; i++)
    {
        ++it2;
    }
    CHECK((*it1 == 5 && *it2 == 4));
    CHECK_FALSE((it1 == it2));
    CHECK((it1 != it2));
    CHECK((it1 < it2));
    CHECK_FALSE((it1 > it2));

    ++it1;
    CHECK((*it1 == 4 && *it2 == 4));
    CHECK((it1 == it2));
    CHECK_FALSE((it1 != it2));
    CHECK_FALSE((it1 > it2));
    CHECK_FALSE((it1 < it2));

    ++it1;
    ++it2;
    CHECK(it1 == it1.end());
    CHECK(it2 == it2.end());
}

TEST_CASE("8 -Comparing PrimeIterator ")
{
    MagicalContainer container;
    MagicalContainer::PrimeIterator it1(container);
    MagicalContainer::PrimeIterator it2(container);
    container.addElement(1);
    container.addElement(2);
    container.addElement(4);
    container.addElement(5);
    container.addElement(14);

    CHECK((*it1 == 2 && *it2 == 2));
    CHECK((it1 == it2));
    CHECK_FALSE((it1 != it2));
    CHECK_FALSE((it1 > it2));
    CHECK_FALSE((it1 < it2));

    ++it1;
    CHECK((*it1 == 5 && *it2 == 2));
    CHECK_FALSE((it1 == it2));
    CHECK((it1 != it2));
    CHECK((it1 > it2));
    CHECK_FALSE((it1 < it2));

    ++it2;
    CHECK((*it1 == 5 && *it2 == 5));
    CHECK((it1 == it2));
    CHECK_FALSE((it1 != it2));
    CHECK_FALSE((it1 > it2));
    CHECK_FALSE((it1 < it2));

    ++it1;
    ++it2;
    CHECK(it1 == it1.end());
    CHECK(it2 == it2.end());
}

TEST_CASE("9 -AscendingIterator with Negative and Positive Numbers")
{
    MagicalContainer container;
    container.addElement(-3);
    container.addElement(5);
    container.addElement(-2);
    container.addElement(0);
    container.addElement(4);
    container.addElement(-1);
    container.addElement(3);
    container.addElement(-4);
    container.addElement(2);
    container.addElement(1);

    MagicalContainer::AscendingIterator it(container);
    CHECK(*it == -4);
    ++it;
    CHECK(*it == -3);
    ++it;
    CHECK(*it == -2);
    ++it;
    CHECK(*it == -1);
    ++it;
    CHECK(*it == 0);
    ++it;
    CHECK(*it == 1);
    ++it;
    CHECK(*it == 2);
    ++it;
    CHECK(*it == 3);
    ++it;
    CHECK(*it == 4);
    ++it;
    CHECK(*it == 5);
    ++it;
    CHECK(it == it.end());
}

TEST_CASE("10 - operator= throws when iterators are pointing at different containers")
{
    MagicalContainer container1;
    MagicalContainer container2;

    container1.addElement(1);
    container1.addElement(2);
    container1.addElement(3);

    container2.addElement(4);
    container2.addElement(5);
    container2.addElement(6);

    SUBCASE("AscendingIterator")
    {
        MagicalContainer::AscendingIterator it1(container1);
        MagicalContainer::AscendingIterator it2(container2);

        CHECK_THROWS_AS(it1 = it2, std::runtime_error);
    }
    SUBCASE("SideCrossIterator")
    {
        MagicalContainer::SideCrossIterator it1(container1);
        MagicalContainer::SideCrossIterator it2(container2);

        CHECK_THROWS_AS(it1 = it2, std::runtime_error);
    }
    SUBCASE("AscendingIterator")
    {
        MagicalContainer::PrimeIterator it1(container1);
        MagicalContainer::PrimeIterator it2(container2);

        CHECK_THROWS_AS(it1 = it2, std::runtime_error);
    }
}