/*
BSD 2-Clause License

Copyright (c) 2021, Luan Carlos Adão (lnz222)
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/



#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>
using namespace std;

string svDir = "/etc/sv/";
string varSvDir = "/etc/runit/runsvdir/default/";

bool svExists(string path, string name) {
	ifstream ifile;
	ifile.open(path+name);
	if(ifile){
		return true;
	} else {
		return false;
	}
	
}


int main (int argc, char *argv[]) {
	
	if (argc > 2) {
		string svName = argv[2];
		if (!strcmp(argv[1], "enable")) {
			if (svExists(svDir, svName) && !svExists(varSvDir, svName))  {
				string svEnable = "ln -s /etc/sv/" + svName + " /etc/runit/runsvdir/default";
				system(svEnable.c_str());
				cout << "Service " << svName << " enabled" << endl;
			} else if (!svExists(svDir, svName)) {
				cout << "Service " << svName <<  " does not exist" << endl;
			}  else if (svExists(varSvDir, svName)) {
				cout << "Service " << svName << " is already enabled" << endl;
			}
		}
		if (!strcmp(argv[1], "disable")) {
			if (svExists(varSvDir, svName)) {
				string svDisable = "rm -r /etc/runit/runsvdir/default/"+svName;
				system(svDisable.c_str());
				cout << "Service " << svName << " disabled" << endl;
			} else if (!svExists(varSvDir, svName) && svExists(svDir, svName)) {
				cout << "Service " << svName << " is already disabled" << endl;
			} else if (!svExists(svDir, svName)) {
				cout << "Service " << svName << " does not exist" << endl;
			}
		}
	}
	
	return 0;
}