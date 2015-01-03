CLUtils
=======

CLUtils offers utilities that help setup and manage an OpenCL environment. It aims to allow rapid prototyping by hiding away all the boilerplate code necessary for establishing an OpenCL environment.

This meant to be an exercise on how I would go about containing the OpenCL objects, and developing an API to interface them all. But since I didn't have a solid idea of what I needed, I started writing the code and ended up adapting the API around it. The result was an API that made use of indices to refer to OpenCL objects which only makes it efficient to use under a known environment. Nonetheless, the library works pretty robustly. Now that I have a better understanding on the problem, I intent to come back at some point and reconfigure the whole thing.

If you would like something more appropriate and complete, take a look at [`boost.compute`](https://github.com/kylelutz/compute) or [`AMD APP SDK's CLUtil`](http://developer.amd.com/tools-and-sdks/opencl-zone/amd-accelerated-parallel-processing-app-sdk/).


API
===

![api](https://img.shields.io/badge/API-experimental-red.svg?style=flat)

The simplest case covered by the library is one where a context is created for the first platform returned by the OpenCL API, and a command queue is created for the first device in that platform. Programs are built for all devices in the associated context. This case is covered automatically when a kernel filename is provided on the definition of a `CLEnv` instance.

```cpp
#include <CLUtils.hpp>

using namespace clutils;

int main ()
{
    CLEnv clEnv ("myKernels.cl");
    cl::Context &context (clEnv.getContext ());
    cl::CommandQueue &queue (clEnv.getQueue ());
    cl::Kernel &kernel (clEnv.getKernel ("myKernel"));
    cl::NDRange global (1024), local (256);

    cl::Buffer dBuf (context, CL_MEM_READ_WRITE, 1024 * sizeof (int));
    kernel.setArg (0, dBuf);

    queue.enqueueNDRangeKernel (kernel, cl::NullRange, global, local);

    return 0;
}
```

The complete `documentation` is available [here](http://clutils.paign10.me).


Build & Install
===============

```bash
git clone https://github.com/pAIgn10/CLUtils.git
cd CLUtils

mkdir build
cd build

cmake ..
# or, to build the tests too
# cmake -DBUILD_TESTS=ON ..

make

# to run the example
./bin/clUtils_vecAdd

# to install the library
sudo make install

# to build the documentation
make doxygen
firefox docs/html/index.html
```
