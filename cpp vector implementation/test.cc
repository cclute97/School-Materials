#include <iostream>
#include <string>

#include "basic_vector.h"

void test_basic_constructor() {
    typedef basic_vector<int> int_vector;
    int_vector vector;
    std::cout << "Testing basic_vector(): ";
    if (vector.size() == 0 && vector.capacity() == 1) {
        std::cout << "Pass";
    } else {
        std::cout << "Fail";
    }
    std::cout << std::endl;
}

void test_constructor_args() {
    typedef basic_vector<int> int_vector;
    size_t capacity = 10;
    int_vector vector(capacity);
    std::cout << "Testing basic_vector(size_t capacity): ";
    if (vector.size() == 0 && vector.capacity() == capacity) {
        std::cout << "Pass";
    } else {
        std::cout << "Fail";
    }
    std::cout << std::endl;
}

void test_copy_constructor() {
    typedef basic_vector<int> int_vector;
    int_vector vector_2;
    for (int i = 0; i < 10; i++) {
        vector_2.push_back(i);
    }

    int_vector vector(vector_2);

    bool fail = false;

    std::cout << "Testing basic_vector copy constructor: ";
    if (vector.size() == vector_2.size() && vector.capacity() == vector_2.capacity()) {
        for (size_t i = 0; i < vector.size(); i++) {
            if (vector[i] != vector_2[i]) {
                fail = true;
                break;
            }
        }
        if (fail) {
            std::cout << "Fail";
        } else {
            std::cout << "Pass";
        }
    } else {
        std::cout << "Fail";
    }
    std::cout << std::endl;
} 

void test_assignment_operator() {
    typedef basic_vector<int> int_vector;
    int_vector vector_2;
    for (int i = 0; i < 10; i++) {
        vector_2.push_back(i);
    }

    int_vector vector = vector_2;

    bool fail = false;

    std::cout << "Testing assignment operator =: ";
    if (vector.size() == vector_2.size() && vector.capacity() == vector_2.capacity()) {
        for (size_t i = 0; i < vector.size(); i++) {
            if (vector[i] != vector_2[i]) {
                fail = true;
                break;
            }
        }
        if (fail) {
            std::cout << "Fail";
        } else {
            std::cout << "Pass";
        }
    } else {
        std::cout << "Fail";
    }
    std::cout << std::endl;
}

void test_resize() {
    typedef basic_vector<int> int_vector;
    typedef basic_vector<std::string> str_vector;

    int_vector iv(45);
    str_vector sv(45);

    for (int i = 0; i < 25; i++) {
        iv.push_back(i);
    }
    for (int i = 0; i < 25; i++) {
        sv.push_back("string");
    }

    // Before resize: Capacity is 45 for both, size is 25 for both 
    // After resize: size is 10 for iv and sv, capacity is 45

    iv.resize(10);
    sv.resize(10);

    std::cout << "Testing resize(size_t n) <1 of 2>: ";
    if ((iv.size() == 10 && iv.capacity() == 45) && (sv.size() == 10 && sv.capacity() == 45)) {
        iv.resize(100);
        sv.resize(100);
        if ((iv.size() == 100 && iv.capacity() == 100) && (sv.size() == 100 && sv.capacity() == 100)) {
            std::cout << "Pass";
        } else {
            std::cout << "Fail";
        }
    } else {
        std::cout << "Fail -- " << "iv.size() = " << iv.size() << ", iv.capacity() = " << iv.capacity();
    }
    std::cout << std::endl;
} 

void test_resize_2() {
    typedef basic_vector<int> int_vector;
    typedef basic_vector<std::string> str_vector;

    int_vector iv(110);
    str_vector sv(110);

    for (int i = 0; i < 68; i++) {
        iv.push_back(i);
    }
    for (int i = 0; i < 68; i++) {
        sv.push_back("string");
    }

    // Before resize: Capacity is 110 for both, size is 68 for both 
    // After resize: size is 10 for iv and sv, capacity is 45

    iv.resize(10);
    sv.resize(10);

    std::cout << "Testing resize(size_t n) <2 of 2>: ";
    if ((iv.size() == 10 && iv.capacity() == 110) && (sv.size() == 10 && sv.capacity() == 110)) {
        iv.resize(40);
        sv.resize(40);
        if ((iv.size() == 40 && iv.capacity() == 110) && (sv.size() == 40 && sv.capacity() == 110)) {
            std::cout << "Pass";
        } else {
            std::cout << "Fail";
        }
    } else {
        std::cout << "Fail -- " << "iv.size() = " << iv.size() << ", iv.capacity() = " << iv.capacity();
    }
    std::cout << std::endl;
} 

void test_resize_over_max() {
    typedef basic_vector<int> int_vector;
    
    int_vector iv(30);

    for (int i = 0; i < 15; i++) {
        iv.push_back(i);
    }

    iv.resize(iv.max_size() + 1);

    std::cout << "Testing resize(size_t n) where n > max_size(): ";
    if (iv.size() == 1073741823 && iv.capacity() == 1073741823) {
        int_vector iv_2(50);
        iv_2.resize(25);
        iv_2.reserve(iv.max_size() + 1);
        if (iv_2.size() == 25 && iv_2.capacity() == 1073741823) {
           std::cout << "Pass";
        } else {
            std::cout << "Fail";
        }
    } else {
        std::cout << "Fail -- " << "iv.size() = " << iv.size() << ", iv.capacity() = " << iv.capacity();
    }
    std::cout << std::endl;
}

void test_index_operator() {
    typedef basic_vector<int> int_vector;
    typedef basic_vector<std::string> str_vector;

    int_vector iv;
    str_vector sv;

    for (int i = 0; i < 10; i++) {
        iv.push_back(i);
    }
    for (int i = 0; i < 10; i++) {
        if (i == 5) {
            sv.push_back("special_string");
        } else {
            sv.push_back("string");
        }
    }

    std::cout << "Testing index operator []: ";
    if (iv[5] == 5 && sv[5] == "special_string") {
        std::cout << "Pass";
    } else {
        std::cout << "Fail";
    }
    std::cout << std::endl;
}

void test_at() {
    typedef basic_vector<int> int_vector;
    int_vector iv;

    for (int i = 0; i < 10; i++) {
        iv.push_back(i);
    }

    std::cout << "Testing at(size_t n): ";
    if (iv.at(5) == 5) {
        try {
            iv.at(-1);
        } catch (const std::out_of_range &e) {
            std::cout << "Pass";
        }

    } else {
        std::cout << "Fail";
    }
    std::cout << std::endl;
}

void test_push_back() {
    typedef basic_vector<int> int_vector;
    typedef basic_vector<std::string> str_vector;

    int_vector iv;
    str_vector sv;

    for (int i = 0; i < 10; i++) {
        iv.push_back(i);
    }
    for (int i = 0; i < 10; i++) {
        sv.push_back("string");
    }

    std::cout << "Testing push_back(const T& val): ";
    if ((iv.size() == 10 && iv.capacity() == 16) && (sv.size() == 10 && sv.capacity() == 16)) {
        std::cout << "Pass";
    } else {
        std::cout << "Fail";
    }
    std::cout << std::endl;
}

void test_pop_back() {
    typedef basic_vector<int> int_vector;
    typedef basic_vector<std::string> str_vector;

    int_vector iv;
    str_vector sv;

    for (int i = 0; i < 10; i++) {
        iv.push_back(i);
    }
    for (int i = 0; i < 10; i++) {
        sv.push_back("string");
    }

    for (int i = 0; i < 5; i++) {
        iv.pop_back();
        sv.pop_back();
    }

    bool fail = false;

    std::cout << "Testing pop_back(): ";
    if ((iv.size() == 5 && iv.capacity() == 16) && (sv.size() == 5 && sv.capacity() == 16)) {
        for (size_t i = iv.size(); i < iv.capacity(); i++) {
            if (iv[i] != 0 || !sv[i].empty()) { // check each empty value, if not correct, print "Fail", then break
                fail = true;
                break;
            }
        }
        if (fail) {
            std::cout << "Fail";
        } else {
            std::cout << "Pass";
        }
    } else {
        std::cout << "Fail";
    }
    std::cout << std::endl;
}

void test_swap() {
    typedef basic_vector<int> int_vector;

    int_vector iv;
    int_vector iv_2;

    for (int i = 0; i < 10; i++) {
        iv.push_back(i);    }

    for (int i = 0; i < 20; i++) {
        iv_2.push_back(i * 2);
    }

    iv.swap(iv_2);

    int sum_iv = 0;
    int sum_iv_2 = 0;

    for (size_t i = 0; i < iv.size(); i++) {
        sum_iv += iv[i];
    }

    for (size_t i = 0; i < iv_2.size(); i++) {
        sum_iv_2 += iv_2[i];
    }
    
    std::cout << "Testing swap(basic_vector &other): ";
    if (sum_iv == 380 && sum_iv_2 == 45) {
        std::cout << "Pass";
    } else {
        std::cout << "Fail";
    }
    std::cout << std::endl;
}

int main() {

    test_basic_constructor();
    test_constructor_args();
    test_copy_constructor();
    test_assignment_operator();
    test_resize();
    test_resize_2();
    test_resize_over_max();
    test_index_operator();
    test_at();
    test_push_back();
    test_pop_back();
    test_swap();

    return 0;
}