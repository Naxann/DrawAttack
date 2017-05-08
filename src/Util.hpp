#ifndef DRAWATTACK_UTIL_HPP
#define DRAWATTACK_UTIL_HPP

#include <sys/stat.h>
#include <string>

#ifndef EMULATION
#include <3ds.h>
#endif
namespace DrawAttack
{

bool pathExists(const char* path, bool escape = true);
bool fileExists (const std::string& name);
void makeDirectory(const char *dir, mode_t mode = 0777);
int removeDirectory(const char *path, bool onlyIfEmpty = false);

} // namespace DrawAttack

#endif // DRAWATTACK_UTIL_HPP
