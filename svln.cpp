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