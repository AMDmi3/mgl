/* Copyright [2013-2018] [Aaron Springstroh, Minimal Graphics Library]

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#ifndef __TEST_THREAD_POOL__
#define __TEST_THREAD_POOL__

#include <min/test.h>
#include <min/thread_pool.h>
#include <stdexcept>

bool test_thread_pool()
{
    bool out = true;

    // Create a threadpool for doing work in parallel
    min::thread_pool pool;

    // Work items
    std::vector<int> items = {0, 1, 2, 3, 4, 5, 6, 7};

    // Create working function
    const auto work = [&items](std::mt19937 &gen, const size_t i) {
        items[i]++;
    };

    // Run the job in parallel
    pool.run(std::cref(work), 0, 8);

    // Run the job in parallel
    pool.run(std::cref(work), 0, 8);

    // Run the job in parallel
    pool.run(std::cref(work), 0, 8);

    // Kill the pool
    pool.kill();

    // Run test
    bool passed = true;
    for (int i = 0; i < 8; i++)
    {
        if (items[i] != (i + 3))
        {
            passed = false;
        }
    }

    // Test thread map
    out = out && passed;
    if (!out)
    {
        throw std::runtime_error("Failed thread pool test");
    }

    // return status
    return out;
}

#endif
