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
		ifile.close();
		return true;
	} else {
		ifile.close();
		return false;
	}
	
}

void svMan(string type, string service) {
	if (type == "enable") {
		if (svExists(svDir, service) && !svExists(varSvDir, service))  {
			string svEnable = "sudo ln -s /etc/sv/" + service + " /etc/runit/runsvdir/default";
			system(svEnable.c_str());
			cout << "Service " << service << " enabled" << endl;
		} else if (!svExists(svDir, service)) {
			cout << "Service " << service <<  " does not exist" << endl;
		}  else if (svExists(varSvDir, service)) {
			cout << "Service " << service << " is already enabled" << endl;
		}
	}
	if (type == "disable") {
		if (svExists(varSvDir, service)) {
			string svDisable = "sudo rm -r /etc/runit/runsvdir/default/"+service;
			system(svDisable.c_str());
			cout << "Service " << service << " disabled" << endl;
		} else if (!svExists(varSvDir, service) && svExists(svDir, service)) {
			cout << "Service " << service << " is already disabled" << endl;
		} else if (!svExists(svDir, service)) {
			cout << "Service " << service << " does not exist" << endl;
		}
	}
}

void svListCmd(bool enabled) {
	if (enabled == true) {
		string svListEnabled = "ls /var/service/";
		system(svListEnabled.c_str());
	} else {
		string svList = "ls /etc/sv/";
		system(svList.c_str());
	}
} 


int main (int argc, char *argv[]) {
	
	if (argc > 2) {
		if (!strcmp(argv[1], "enable")) {
			svMan("enable", argv[2]);
		}
		if (!strcmp(argv[1], "disable")) {
			svMan("disable", argv[2]);
		}
		if (!strcmp(argv[1], "list") || !strcmp(argv[1], "-l") && !strcmp(argv[2], "enabled")) {
			svListCmd(true);
		}
	
	} else {
		if (!strcmp(argv[1], "list") || !strcmp(argv[1], "-l")) {
			svListCmd(false);
		}
		if (!strcmp(argv[1], "about") || !strcmp(argv[1], "-ab")) {
			cout << "\nDeveloped by lnz222 (Luan Carlos Adão)" << endl;
			cout << "Version: 0.2\n" << endl;
			cout << "License: BSD 2-Clause License" << endl;
			cout << "Copyright (c) 2021, Luan Carlos Adão (lnz222)\nAll rights reserved.\n" << endl;
		}
	}
	
	
	return 0;
}























