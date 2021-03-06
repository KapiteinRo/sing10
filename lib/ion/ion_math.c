/*
 *	ION math
 *
 * Copyright (C) 2005 Royi Eltink <r.eltink@live.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 */

#include <stdio.h>
#include <limits.h>
#include <ions.h>

// divide max
unsigned long IOML_HALFMAX() {
	return (ULONG_MAX)/2;
}

// check if we can safely add without overflow
unsigned char IOML_CheckAdd(unsigned long a, unsigned long b, unsigned long ulCheck) {
	// divide by half
	unsigned long aHalf = (a == ULONG_MAX ? IOML_HALFMAX() : (a+1)/2 + 1);
	unsigned long bHalf = (b == ULONG_MAX ? IOML_HALFMAX() : (b+1)/2 + 1);

	if(ulCheck < (aHalf + bHalf)) return ION_TRUE;
	return ION_FALSE;
}
