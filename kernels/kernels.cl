/*! \file kernels.cl
 *  \brief It contains a kernel that performs a vector addition.
 *  \author Nick Lamprianidis
 *  \version 1.0
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


/*! \brief It performs a vector addition.
 *  \param[in] A first operand (buffer) to the vector addition.
 *  \param[in] B second operand (buffer) to the vector addition.
 *  \param[out] C holds the result (buffer) of the vector addition.
 */
__kernel
void vecAdd (__global int *A, __global int *B, __global int *C)
{
    size_t idx = get_global_id (0);
    C[idx] = A[idx] + B[idx];
}
