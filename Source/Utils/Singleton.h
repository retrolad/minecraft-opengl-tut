#ifndef SINGLETON_H
#define SINGLETON_H

#include "NonCopyable.h"
#include "NonMovable.h"

class Singleton : public NonCopyable, public NonMovable
{

};

#endif 