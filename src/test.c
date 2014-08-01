/*
 *	IONS test
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
#include <string.h>

#include <sing.h>
#include <stack.h>

void show_help() {
	printf("Usage: test [file]\n");
}

void test_file(char *cpFile) {
	FILE *fBin;
	unsigned long ulSize = 0;
	unsigned long ulPos = 0;
	unsigned long ulOccur = 0;
	Ion ioTest;

	// open file
	fBin = fopen(cpFile,"rb");
	printf("Loading %s ....\n",cpFile);
	if(fBin) {
		// check size
		fseek(fBin,0,SEEK_END);
		ulSize = ftell(fBin);
		printf("%u bytes in file....\n",ulSize);
		// go back to beginning
		fseek(fBin,0,SEEK_SET);

		// start processing..
		printf("Starting processing....\n");

		// prepare stack
		open_stack();

		// read and process
		for(ulPos = 0; ulPos < ulSize; ulPos++) {
			// push to stack
			push_stack(fgetc(fBin));
			// if stack is full.. process
			if(stack_filled() == 1) {
				// read Ion from stack
				ioTest = pop_stack();

				// feed to compiler
				ioTest = IonExecute(ioTest);

				// check if found
				if(ioTest.ucFlags != 0) {
					printf("Found #%d on pos %u\n",ioTest.ucFlags,ulPos);
					ulOccur++;
				}
			}
		}

		// close
		fclose(fBin);

		// overview
		printf("Found %d ions..\n",ulOccur);
	} else {
		printf("Can't open %s!\n",cpFile);
	}
}

int main(int argc, char *argv[]) {
	printf("Singularity test\n\tCopyright (c) 2005 Royi Eltink\n\n");
	if(argc == 1) {
		show_help();
		return 0;
	}

	test_file(argv[1]);
	return 0;
}
