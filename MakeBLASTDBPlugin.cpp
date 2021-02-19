#include "PluginManager.h"
#include <stdio.h>
#include <stdlib.h>
#include "MakeBLASTDBPlugin.h"
#include <dirent.h>
#include <errno.h>
#include <string.h>

int MakeBLASTDBPlugin::isFile(const char* name)
{
    DIR* directory = opendir(name);
    if(directory != NULL)
    {
     closedir(directory);
     return 0;
    }

    if(errno == ENOTDIR)
     return 1;

    return -1;
}



void MakeBLASTDBPlugin::input(std::string file) {
 inputfile = file;
 std::ifstream ifile(inputfile.c_str(), std::ios::in);
 while (!ifile.eof()) {
   std::string key, value;
   ifile >> key;
   ifile >> value;
   parameters[key] = value;
 }


}

void MakeBLASTDBPlugin::run() {}

void MakeBLASTDBPlugin::output(std::string file) {
 std::string outputfile = file;
 std::string myCommand = "";

if (isFile(file.c_str())) {
 //makeblastdb -in PA14.txt -out PA14.db
myCommand += "makeblastdb";
myCommand += " ";
myCommand += "-in";
myCommand += " ";
myCommand += std::string(PluginManager::prefix()) + "/" + parameters["fasta"] + " ";
if (parameters["dbtype"] == "nucleotide") {
                      myCommand += "-dbtype nucl";
                      myCommand += " ";
}
myCommand += "-out";
myCommand += " ";
myCommand += outputfile + " ";
std::cout << myCommand << std::endl;
 system(myCommand.c_str());
}
else {
   // Directory, do for each FASTA file in folder
      DIR *di;
    char *ptr1,*ptr2;
    int retn;
    struct dirent *dir;
    di = opendir(inputfile.c_str()); //specify the directory name
    if (di)
    {
        while ((dir = readdir(di)) != NULL)
        {
            ptr1=strtok(dir->d_name,".");
            ptr2=strtok(NULL,".");
            if(ptr2!=NULL)
            {
                retn=strcmp(ptr2,"fasta");
                if(retn==0)
                {
                   myCommand = "";
                   myCommand += "makeblastdb";
                   myCommand += " ";
                   myCommand += "-in";
                   myCommand += " ";
                   myCommand += std::string(PluginManager::prefix()) + "/" + parameters["fasta"] + "/" + ptr1 + ".fasta" + " ";
                   if (parameters["dbtype"] == "nucleotide") {
                      myCommand += "-dbtype nucl";
                      myCommand += " ";
                   }
                   myCommand += "-out";
                   myCommand += " ";
                   myCommand += outputfile + "/" + ptr1 + ".db" + " ";
                   system(myCommand.c_str());
                   printf("%s\t",ptr1);
                }
            }
        }
        closedir(di);
    }
 
}
}

PluginProxy<MakeBLASTDBPlugin> MakeBLASTDBPluginProxy = PluginProxy<MakeBLASTDBPlugin>("MakeBLASTDB", PluginManager::getInstance());
