/*
 *	IONS
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

#ifndef __IONS_H
#define __IONS_H

#define ION_FLAG_1	0xfb
#define ION_FLAG_2	0xfe
#define ION_FLAG_F	0xaa

#define ION_INPUTLEN	12

#define ION_SHIFT	255

#define ION_TRUE	1
#define	ION_FALSE	0

/*
 *	structure of an Ion-object
 */
typedef struct {
	// input
	unsigned char ucFlags;
	unsigned long ulLeft;
	unsigned long ulRight;
	unsigned long ulInput;
	// output
	unsigned char ucResult;
	unsigned long ulOutput;
} Ion;

#ifdef FROM_SING_DLL

Ion ion_read(unsigned char szInput[ION_INPUTLEN]);
Ion ion_run(Ion io);
unsigned int ion_write(unsigned char *szBuffer, Ion *io);

// from math lib
unsigned long IOML_HALFMAX();
unsigned char IOML_CheckAdd(unsigned long a, unsigned long b, unsigned long ulCheck);

// from compiler
Ion ion_compile(Ion io);

#endif

#endif

