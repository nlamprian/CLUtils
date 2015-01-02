/*! \file vecAdd.cpp
 *  \brief An example showcasing the use of the CLUtils library.
 *         The executed kernel performs a vector addition.
 *  \author Nick Lamprianidis
 *  \version 0.1
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

#define __CL_ENABLE_EXCEPTIONS

#if defined(__APPLE__) || defined(__MACOSX)
#include <OpenCL/cl.hpp>
#else
#include <CL/cl.hpp>
#endif
#include <CLUtils.hpp>


const std::string kernel_filename { "kernels/kernels.cl" };
const int n_elements = 1<<24;  // 16M elements


/*! \brief Creates an OpenCL environment, and then
 *         performs a vector addition on the GPU.
 */
class vecAdd
{
public:
    vecAdd (const std::string &kernel_filename);
    ~vecAdd () {};
    void run ();

private:
    clutils::CLEnv clEnv;
    cl::Context &context;  /*!< Reference to one of the clEnv's contexts */
    cl::CommandQueue &queue;  /*!< Reference to one of the clEnv's queues */
    cl::Kernel &kernel_vecAdd;
    cl::NDRange global, local;  /*!< Global and local workspaces */
    cl::Buffer hBufferA, hBufferB;  /*!< Staging buffers */
    cl::Buffer dBufferA, dBufferB, dBufferC;  /*!< Device buffers */
};


/*! \param[in] kernel_filename a vector of strings with all the kernel files 
 *                             (.cl) that are to be compiled for all devices 
 *                             in the first platform.
 */
vecAdd::vecAdd (const std::string &kernel_filename)
                    : clEnv (kernel_filename), 
                      context (clEnv.getContext ()),
                      queue (clEnv.getQueue ()),
                      kernel_vecAdd (clEnv.getKernel ("vecAdd")),
                      global (n_elements), local (256)
{
    // Create staging buffers
    hBufferA = cl::Buffer (context, CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR, 
                           n_elements * sizeof (int));
    hBufferB = cl::Buffer (context, CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR, 
                           n_elements * sizeof (int));

    // Create device buffers
    dBufferA = cl::Buffer (context, CL_MEM_READ_ONLY, n_elements * sizeof (int));
    dBufferB = cl::Buffer (context, CL_MEM_READ_ONLY, n_elements * sizeof (int));
    dBufferC = cl::Buffer (context, CL_MEM_WRITE_ONLY, n_elements * sizeof (int));

    // Set kernel arguments
    kernel_vecAdd.setArg (0, dBufferA);
    kernel_vecAdd.setArg (1, dBufferB);
    kernel_vecAdd.setArg (2, dBufferC);
}


/*! \brief Prepares the buffers, initializes the data, and executes the kernels. */
void vecAdd::run ()
{
    // Get pointers to the staging buffers
    int *A = (int *) queue.enqueueMapBuffer 
                (hBufferA, CL_FALSE, CL_MEM_WRITE_ONLY, 0, n_elements * sizeof (int));
    int *B = (int *) queue.enqueueMapBuffer 
                (hBufferB, CL_FALSE, CL_MEM_WRITE_ONLY, 0, n_elements * sizeof (int));
    queue.finish ();

    // Initialize the staging buffers
    for (int i = 0; i < n_elements; ++i)
    {
        A[i] = i;
        B[i] = i;
    }

    // Unmap the staging buffers
    queue.enqueueUnmapMemObject (hBufferA, A);
    queue.enqueueUnmapMemObject (hBufferB, B);

    // Transfer the data to the device
    queue.enqueueCopyBuffer (hBufferA, dBufferA, 0, 0, n_elements * sizeof (int));
    queue.enqueueCopyBuffer (hBufferB, dBufferB, 0, 0, n_elements * sizeof (int));

    // Dispatch the kernel
    queue.enqueueNDRangeKernel (kernel_vecAdd, cl::NullRange, global, local);

    // Read back the output data
    queue.enqueueCopyBuffer (dBufferC, hBufferA, 0, 0, n_elements * sizeof (int));

    queue.finish ();

    // Verify the results
    bool status = true;
    for (int i = 0; i < n_elements; ++i)
    {
        if (A[i] != i+i)
        {
            status = false;
            break;
        }
    }

    if (status) 
        std::cout << "Success!" << std::endl;
    else 
        std::cout << "Failed!" << std::endl;
}


int main (/*int argc, char **argv*/)
{
    try
    {
        vecAdd vAdd (kernel_filename);
        vAdd.run ();

        return 0;
    }
    catch (const cl::Error &error)
    {
        std::cerr << error.what ()
                  << " (" << clutils::getOpenCLErrorCodeString (error.err ()) 
                  << ")"  << std::endl;
        exit (EXIT_FAILURE);
    }
}
