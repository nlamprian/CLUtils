/*! \file CLUtils.hpp
 *  \brief Declarations of objects, 
 *         functions and classes for the CLUtils library.
 *  \details CLUtils offers utilities that help 
             setup and manage an OpenCL environment.
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

#ifndef CLUTILS_HPP
#define CLUTILS_HPP

#include <vector>
#include <unordered_map>

#define __CL_ENABLE_EXCEPTIONS

#if defined(__APPLE__) || defined(__MACOSX)
#include <OpenCL/cl.hpp>
#else
#include <CL/cl.hpp>
#endif

/*! \brief It brings together functionality common to all OpenCL projects.
 *  
 *  It offers structures that aim to ease the process of setting up and 
 *  maintaining an OpenCL environment.
 */
namespace clutils
{
    /*! \brief Returns the name of an error code. */
    const char* getOpenCLErrorCodeString (int errorCode);

    /*! \brief Reads in the contents from the requested files. */
    void readSource (const std::vector<std::string> &kernel_filenames, 
                     std::vector<std::string> &sourceCodes);

    /*! \brief Splits a string on the requested delimiter. */
    void split (const std::string &str, char delim, 
                std::vector<std::string> &names);


    /*! \brief Creates a pair of a char array (source code) and its size. */
    std::pair<const char *, size_t> 
        make_kernel_pair (const std::string &kernel_filename);


    /*! \brief Sets up an OpenCL environment.
     *
     *  Prepares the essential OpenCL objects for the execution of kernels.
     *  This class aims to allow rapid prototyping by hiding away all the 
     *  boilerplate code necessary for establishing an OpenCL environment.
     */
    class CLEnv
    {
    public:
        CLEnv (const std::vector<std::string> &kernel_filenames = std::vector<std::string> (), 
               const char *build_options = NULL);
        CLEnv (const std::string &kernel_filename, 
               const char *build_options = NULL);
        ~CLEnv () {};
        /*! \brief Gets back one of the existing contexts. */
        cl::Context& getContext (unsigned int pIdx = 0);
        /*! \brief Gets back one of the existing command queues 
         *         in the specified context. */
        cl::CommandQueue& getQueue (unsigned int ctIdx = 0, unsigned int qIdx = 0);
        /*! \brief Gets back one of the existing kernels in some program. */
        cl::Kernel& getKernel (const char *kernelName, unsigned int pgIdx = 0);
        /*! \brief Creates a context for all devices in the requested platform. */
        cl::Context& addContext (unsigned int pIdx);
        /*! \brief Creates a queue for the specified device in the specified context. */
        cl::CommandQueue& addQueue (unsigned int ctIdx, unsigned int dIdx);
        /*! \brief Creates a program for the specified context. */
        cl::Kernel& addProgram (unsigned int ctIdx, 
                                const std::vector<std::string> &kernel_filenames, 
                                const char *kernel_name = NULL, 
                                const char *build_options = NULL);
        cl::Kernel& addProgram (unsigned int ctIdx, 
                                const std::string &kernel_filename, 
                                const char *kernel_name = NULL, 
                                const char *build_options = NULL);

        // Objects associated with an OpenCL environment.
        // For each of a number of objects, there is a vector that 
        // can hold all instances of that object.

        std::vector<cl::Platform> platforms;
        /*! \brief Holds a vector of devices per platform. */
        std::vector< std::vector<cl::Device> > devices;
        std::vector<cl::Context> contexts;
        /*! \brief Holds a vector of queues per context. */
        std::vector< std::vector<cl::CommandQueue> > queues;
        std::vector<cl::Program> programs;
        /*! \brief Holds a vector of kernels per program. */
        std::vector< std::vector<cl::Kernel> > kernels;

    private:
        /*! \brief Maps kernel names to kernel indices.
         *         There is one unordered_map for every program.
         *  
         *  For every program in programs, there is an element in kernelIdx.
         *  For every kernel in program i, there is a mapping from the kernel 
         *  name to the kernel index in kernels[i].
         */
        std::vector< std::unordered_map<std::string, unsigned int> > kernelIdx;
    };

}

#endif  // CLUTILS_HPP
