/*! \file tests.cpp
 *  \brief Google Test Unit Tests
 *  \author Nick Lamprianidis
 *  \version 0.2.2
 *  \date 2014-2015
 *  \copyright The MIT License (MIT)
 *  \par
 *  Copyright (c) 2014 Nick Lamprianidis
 *  \par
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  \par
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *  \par
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <cmath>
#include <thread>
#include <gtest/gtest.h>
#include <CLUtils.hpp>


const std::string kernel_filename { "kernels/kernels.cl" };
const std::string kernel_filename2 { "kernels/kernels2.cl" };
const std::vector<std::string> kernel_filenames { kernel_filename, kernel_filename2 };
const int n_elements = 1 << 12;  // 4K elements

auto seed = std::chrono::system_clock::now ().time_since_epoch ().count ();
std::default_random_engine generator (seed);
std::uniform_int_distribution<int> distribution (1, 32);
/*! Produces a random integer with which device buffers will be initialized */
auto rNum = std::bind (distribution, generator);


/*! \brief Performs a buffer initialization under default environment.
 */
TEST (CLEnv, BasicFunctionality)
{
    int num = rNum ();
    const std::string options = "-D INIT_NUM=" + std::to_string (num);
    
    clutils::CLEnv clEnv (kernel_filename2, options.c_str ());
    cl::Context &context (clEnv.getContext ());
    cl::CommandQueue &queue (clEnv.getQueue ());
    cl::Kernel &kernel (clEnv.getKernel ("initRand"));
    cl::NDRange global (n_elements), local (256);

    cl::Buffer dBufA (context, CL_MEM_WRITE_ONLY, n_elements * sizeof (int));
    kernel.setArg (0, dBufA);

    queue.enqueueNDRangeKernel (kernel, cl::NullRange, global, local);

    int hBufA[n_elements];
    queue.enqueueReadBuffer (dBufA, CL_TRUE, 0, n_elements * sizeof (int), hBufA);

    for (int elmt : hBufA)
        ASSERT_EQ (num, elmt);
}


/*! \brief Performs a buffer initializations and a vector addition 
 *         under user created environment.
 */
TEST (CLEnv, AddMoreCLObjects)
{ 
    int num = rNum ();
    const std::string options = "-D INIT_NUM=" + std::to_string (num);

    clutils::CLEnv clEnv;
    cl::Context &context (clEnv.addContext (0));
    cl::CommandQueue &queue (clEnv.addQueue (0, 0));
    cl::Kernel &kernel_init (clEnv.addProgram (0, kernel_filename2, "initRand", options.c_str ()));
    cl::Kernel &kernel_add (clEnv.addProgram (0, kernel_filename, "vecAdd"));
    
    cl::NDRange global (n_elements), local (256);

    cl::Buffer dBufA (context, CL_MEM_READ_WRITE, n_elements * sizeof (int));
    cl::Buffer dBufB (context, CL_MEM_READ_WRITE, n_elements * sizeof (int));
    
    kernel_init.setArg (0, dBufA);
    queue.enqueueNDRangeKernel (kernel_init, cl::NullRange, global, local);
    kernel_init.setArg (0, dBufB);
    queue.enqueueNDRangeKernel (kernel_init, cl::NullRange, global, local);

    cl::Buffer dBufC (context, CL_MEM_WRITE_ONLY, n_elements * sizeof (int));

    kernel_add.setArg (0, dBufA);
    kernel_add.setArg (1, dBufB);
    kernel_add.setArg (2, dBufC);
    queue.enqueueNDRangeKernel (kernel_add, cl::NullRange, global, local);

    int hBufC[n_elements];
    queue.enqueueReadBuffer (dBufC, CL_TRUE, 0, n_elements * sizeof (int), hBufC);

    for (int elmt : hBufC)
        ASSERT_EQ (2*num, elmt);
}


/*! \brief Tests functionality on 2 vectors of 10 floats and compares them.
 */
TEST (ProfilingInfo, BasicFunctionality)
{ 
    const int nRepeat = 10;
    clutils::ProfilingInfo<nRepeat, float> pInfo ("Test");

    // Fill the array ( 1 1 ... 1 1 | 2 2 ... 2 2)
    for (int i = 0; i < nRepeat; ++i)
        pInfo[i] = i / (nRepeat / 2) + 1;

    // Check the total
    ASSERT_EQ (pInfo.total (), (nRepeat / 2) * (float) (1 + 2));

    // Check the mean
    ASSERT_EQ (pInfo.mean (), 1.5);

    // Check the min
    ASSERT_EQ (pInfo.min (), 1.0);

    // Check the max
    ASSERT_EQ (pInfo.max (), 2.0);

    // Create a second to benchmark
    clutils::ProfilingInfo<nRepeat, float> pInfo2 ("Test2");

    // Fill the array ( 1 1 ... 1 1 | 2 2 ... 2 2)
    for (int i = 0; i < nRepeat; ++i)
        pInfo2[i] = i / (nRepeat / 2) + 1;

    // Check the speedup
    ASSERT_EQ (pInfo2.speedup (pInfo), 1.0);
    
    // pInfo.print (pInfo2, "Testing");
}


/*! \brief Tests functionality on a 100,000 us interval.
 */
TEST (CPUTimer, BasicFunctionality)
{ 
    clutils::CPUTimer<double, std::micro> timer (10);

    // Check that the timer initializes correctly
    ASSERT_EQ (timer.duration (), 10);

    // Check that the timer resets
    timer.reset ();
    ASSERT_EQ (timer.duration (), 0);

    // Check that the timer measures appropriately
    timer.start ();
    std::this_thread::sleep_for (std::chrono::duration<int64_t, std::milli> (100));  // 100 ms
    timer.stop ();
    ASSERT_LE (timer.duration () - 100000, 1000);  // 1 ms (OS scheduling) tolerance
}


/*! \brief Tests functionality on a ~12 us execution time kernel.
 */
TEST (GPUTimer, BasicFunctionality)
{
    clutils::CLEnv clEnv;
    cl::Context &context (clEnv.addContext (0));
    cl::CommandQueue &queue (clEnv.addQueue (0, 0, CL_QUEUE_PROFILING_ENABLE));
    cl::Kernel &kernel (clEnv.addProgram (0, kernel_filename, "vecAdd"));
    cl::NDRange global (256);

    cl::Buffer dBufA (context, CL_MEM_READ_ONLY, n_elements * sizeof (int));
    cl::Buffer dBufB (context, CL_MEM_WRITE_ONLY, n_elements * sizeof (int));
    kernel.setArg (0, dBufA);
    kernel.setArg (1, dBufA);
    kernel.setArg (2, dBufB);

    clutils::GPUTimer<std::milli> timer (clEnv.devices[0][0]);
    queue.enqueueNDRangeKernel (kernel, cl::NullRange, global, cl::NullRange, NULL, &timer.event ());
    queue.flush (); timer.wait ();

    ASSERT_LE (timer.duration (), 0.2);
}


int main (int argc, char **argv)
{
    ::testing::InitGoogleTest (&argc, argv);

    return RUN_ALL_TESTS ();
}
