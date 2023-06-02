#ifndef MAGICALCONTAINER_HPP
#define MAGICALCONTAINER_HPP_HPP

#include <string>
namespace ariel
{
	class MagicalContainer
	{
		private:
            


        public:
        MagicalContainer();
        void addElement(int);
        void removeElement(int);
        virtual int size();
        


	

    public:
        class AscendingIterator{
            private:
                MagicalContainer& container;
                size_t current;
            public:
                AscendingIterator( MagicalContainer& container);
                AscendingIterator& operator=(const AscendingIterator& other); // assignment
                ~AscendingIterator()=default; // destructor

                int& operator*() const; // dereference
                AscendingIterator& operator++(); // increment
                const AscendingIterator operator++(int);
                bool operator==(const AscendingIterator& rhs) const; // compare
                bool operator!=(const AscendingIterator& rhs) const; // compare
                bool operator>(const AscendingIterator& other) const; // greater 
                bool operator<(const AscendingIterator& other) const; // smaller
                
                AscendingIterator begin();
                AscendingIterator end();


        


        }; // end of AscendingIterator class

     


    };
};
#endif