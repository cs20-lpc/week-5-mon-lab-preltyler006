#include <iostream>
#include <stdexcept>
#include <cassert>
#include "DoublyList.hpp"

using std::cout;
using std::endl;

void print(const DoublyList<int>& lst, const char* label) {
    cout << label << " (len=" << lst.getLength() << "): ";
    cout << lst;
}

int main() {
    DoublyList<int> a;

    cout << "=== Start ===\n";
    cout << "isEmpty? " << (a.isEmpty() ? "true" : "false") << "\n";
    assert(a.isEmpty());

    a.append(10);
    a.append(20);
    a.append(30);
    print(a, "after append 10,20,30");
    assert(a.getLength() == 3);

    a.insert(0, 5);                          
    a.insert(2, 15);                         
    a.insert(a.getLength(), 40);             
    print(a, "after inserts @0,@2,@end");


    cout << "getElement(0): " << a.getElement(0) << "\n";   
    cout << "getElement(3): " << a.getElement(3) << "\n";  
    cout << "getElement(last): " << a.getElement(a.getLength()-1) << "\n";


    bool threwLow=false, threwHigh=false;
    try { (void)a.getElement(-1); } catch (const std::out_of_range&) { threwLow = true; }
    try { (void)a.getElement(a.getLength()); } catch (const std::out_of_range&) { threwHigh = true; }
    cout << "getElement(-1) threw? " << (threwLow ? "yes" : "no") << "\n";
    cout << "getElement(len) threw? " << (threwHigh ? "yes" : "no") << "\n";
    assert(threwLow && threwHigh);

    cout << "search(15): " << (a.search(15) ? "true" : "false") << "\n";
    cout << "search(999): " << (a.search(999) ? "true" : "false") << "\n";
    assert(a.search(15) && !a.search(999));


    a.replace(2, 17);   
    a.replace(4, 33);   
    print(a, "after replace idx2->17, idx4->33");

    a.remove(0);                        
    a.remove(a.getLength()-1);          
    if (a.getLength() >= 3) a.remove(1); 
    print(a, "after remove first,last,middle");


    DoublyList<int> b(a);
    print(b, "copy(b) from a");

    if (!a.isEmpty()) a.replace(0, 999);
    print(a, "a after replace(0,999)");
    print(b, "b should be unchanged");
    if (!b.isEmpty()) assert(b.getElement(0) != 999);


    DoublyList<int> c;
    c.append(111);
    c = a;             
    print(c, "c = a");
    c = c;             
    print(c, "c self-assign");
    if (!c.isEmpty()) c.remove(0);
    print(c, "c after remove(0)");
    print(a, "a unchanged by c's remove");
    if (!a.isEmpty() && !c.isEmpty())
        assert(a.getElement(0) != c.getElement(0));


    a.clear();
    cout << "a cleared. isEmpty? " << (a.isEmpty() ? "true" : "false") << "\n";
    assert(a.isEmpty());

    cout << "=== Done ===\n";
    return 0;
}