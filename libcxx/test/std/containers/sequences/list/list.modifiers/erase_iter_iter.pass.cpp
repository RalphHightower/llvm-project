//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <list>

// iterator erase(const_iterator first, const_iterator last); // constexpr since C++26

#include <list>
#include <cassert>

#include "test_macros.h"
#include "min_allocator.h"

TEST_CONSTEXPR_CXX26 bool test() {
  int a1[] = {1, 2, 3};
  {
    std::list<int> l1(a1, a1 + 3);
    std::list<int>::iterator i = l1.erase(l1.cbegin(), l1.cbegin());
    assert(l1.size() == 3);
    assert(std::distance(l1.cbegin(), l1.cend()) == 3);
    assert(i == l1.begin());
  }
  {
    std::list<int> l1(a1, a1 + 3);
    std::list<int>::iterator i = l1.erase(l1.cbegin(), std::next(l1.cbegin()));
    assert(l1.size() == 2);
    assert(std::distance(l1.cbegin(), l1.cend()) == 2);
    assert(i == l1.begin());
    assert(l1 == std::list<int>(a1 + 1, a1 + 3));
  }
  {
    std::list<int> l1(a1, a1 + 3);
    std::list<int>::iterator i = l1.erase(l1.cbegin(), std::next(l1.cbegin(), 2));
    assert(l1.size() == 1);
    assert(std::distance(l1.cbegin(), l1.cend()) == 1);
    assert(i == l1.begin());
    assert(l1 == std::list<int>(a1 + 2, a1 + 3));
  }
  {
    std::list<int> l1(a1, a1 + 3);
    std::list<int>::iterator i = l1.erase(l1.cbegin(), std::next(l1.cbegin(), 3));
    assert(l1.size() == 0);
    assert(std::distance(l1.cbegin(), l1.cend()) == 0);
    assert(i == l1.begin());
  }
#if TEST_STD_VER >= 11
  {
    std::list<int, min_allocator<int>> l1(a1, a1 + 3);
    std::list<int, min_allocator<int>>::iterator i = l1.erase(l1.cbegin(), l1.cbegin());
    assert(l1.size() == 3);
    assert(std::distance(l1.cbegin(), l1.cend()) == 3);
    assert(i == l1.begin());
  }
  {
    std::list<int, min_allocator<int>> l1(a1, a1 + 3);
    std::list<int, min_allocator<int>>::iterator i = l1.erase(l1.cbegin(), std::next(l1.cbegin()));
    assert(l1.size() == 2);
    assert(std::distance(l1.cbegin(), l1.cend()) == 2);
    assert(i == l1.begin());
    assert((l1 == std::list<int, min_allocator<int>>(a1 + 1, a1 + 3)));
  }
  {
    std::list<int, min_allocator<int>> l1(a1, a1 + 3);
    std::list<int, min_allocator<int>>::iterator i = l1.erase(l1.cbegin(), std::next(l1.cbegin(), 2));
    assert(l1.size() == 1);
    assert(std::distance(l1.cbegin(), l1.cend()) == 1);
    assert(i == l1.begin());
    assert((l1 == std::list<int, min_allocator<int>>(a1 + 2, a1 + 3)));
  }
  {
    std::list<int, min_allocator<int>> l1(a1, a1 + 3);
    std::list<int, min_allocator<int>>::iterator i = l1.erase(l1.cbegin(), std::next(l1.cbegin(), 3));
    assert(l1.size() == 0);
    assert(std::distance(l1.cbegin(), l1.cend()) == 0);
    assert(i == l1.begin());
  }
#endif

  return true;
}

int main(int, char**) {
  assert(test());
#if TEST_STD_VER >= 26
  static_assert(test());
#endif

  return 0;
}
