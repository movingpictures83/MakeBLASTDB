#ifndef MAKEBLASTDBPLUGIN_H
#define MAKEBLASTDBPLUGIN_H

#include "Plugin.h"
#include "PluginProxy.h"
#include <string>

class MakeBLASTDBPlugin : public Plugin
{
public: 
 std::string toString() {return "MakeBLASTDB";}
 void input(std::string file);
 void run();
 void output(std::string file);

private: 
 std::string inputfile;
 std::string outputfile;
std::map<std::string, std::string> parameters;

private:
 int MakeBLASTDBPlugin::isFile(const char*);

};

#endif
