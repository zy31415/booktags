#include "currentdirectoryconfigurer.h"

#include "directoryinitializer.h"

CurrentDirectoryConfigurer::CurrentDirectoryConfigurer(QString dir) :
    dir(dir)
{
    DirectoryInitializer initializer(dir);

}

