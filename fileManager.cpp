#include "fileManager.h"

//function implementation

void listDir(const String& path)
{
  DIR *dir;
  struct dirent *ent;

  if((dir = opendir (path.c_str())) != nullptr)
  {
    while ((ent = readdir (dir)) != nullptr)
    {
      if(String(ent->d_name).compare(".") != 0)
      {
        cout<< ent->d_name << endl;
      }
      else
      {
        String nextDir = String(ent -> d_name);
        nextDir += "\\";

// files vector & folder vector
// pass in two vec by Ref -> call function on folder to further find files
// For each file with certain type (.cpp, .h, .hpp, .c, .cc, .cxx) read in the file
// *NEED* Read the whole file so I can assess comments and format
        
        //current visit function
        cout <<  nextDir << endl;

        listDir(nextDir);
      }
    }
  }

  closedir (dir);
}
