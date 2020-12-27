CLUtils
=======

CLUtils offers utilities that help setup and manage an OpenCL environment. It aims to allow rapid prototyping by hiding away all the boilerplate code necessary for establishing an OpenCL environment.

This meant to be an exercise on how I would go about containing the OpenCL entities, and developing an API to interface them all. But since I didn't have a solid idea of what I needed, I started writing the code and ended up adapting the API around it. The result was an API that made use of indices to refer to OpenCL objects which only makes it efficient to use under a known environment. Nonetheless, the library works pretty robustly.

If you would like something more general and complete, take a look at [`boost.compute`](https://github.com/kylelutz/compute) or [`AMD APP SDK's CLUtil`](http://developer.amd.com/tools-and-sdks/opencl-zone/amd-accelerated-parallel-processing-app-sdk/).

**Utilities** offered by the library involve procedures like **compiling source files**, sharing **OpenCL environment configurations**, setting up **OpenCL-OpenGL interoperability**, **profiling** **host** and **device** code, and getting **summarizing results** on **profiling data**.

**New on version 0.2:**

* Updated **CLEnv** API to support command queue profiling
* Added support in **CLEnv** for OpenCL-OpenGL interoperability
* Added **CLEnvInfo** to support conveyance of OpenCL env configurations
* Added **CPUTimer** for profiling host code
* Added **GPUTimer** for profiling device code
* Added **ProfilingInfo** for manipulating profiling data

API
---

![api](https://img.shields.io/badge/API-experimental-red.svg?style=flat)

The simplest case handled by the library is one where a context is created for the first platform returned by the OpenCL API and a command queue is created for the first device in that platform. Programs are built for all devices in the associated context. This case is realized automatically when a **kernel filename** is provided on the definition of a `CLEnv` **instance**. Omitting the **kernel filename** in the **CLEnv constructor** allows to later specify exactly the **OpenCL environment configuration** to set up.

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

Having defined all the necessary **OpenCL entities** in **CLEnv**, an **OpenCL configuration** can now be specified with `CLEnvInfo` and communicated to a class that manages and executes some kind of algorithm.

```cpp
#include <CLUtils.hpp>

using namespace clutils;

class PrefixSum;

int main ()
{
    CLEnv clEnv ("myKernels.cl");
    cl::Context &context (clEnv.getContext ());
    cl::CommandQueue &queue (clEnv.getQueue ());

    CLEnvInfo<1> info (0, 0, 0, { 0 }, 0);
    PrefixSum scan (clEnv, info);

    scan.run ();

    return 0;
}
```

The complete `documentation` is available [here](https://clutils.nlamprian.me).


Build & Install
---------------

```bash
git clone https://github.com/nlamprian/CLUtils.git
cd CLUtils

mkdir build
cd build

cmake -DBUILD_EXAMPLES=ON ..
# or to build the tests too
cmake -DBUILD_EXAMPLES=ON -DBUILD_TESTS=ON ..

make

# to run the example (from the build directory!)
./bin/clutils_vecAdd

# to run the tests
./bin/clutils_tests

# to install the library
sudo make install

# to build the docs
make doxygen
firefox docs/html/index.html
```
