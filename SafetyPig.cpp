//=============================================================================
// From
// https://www.quora.com/What-is-the-best-comment-in-a-source-code-that-you-have-ever-encountered/answer/Costya-Perepelitsa
//
/*
 * WARNING: the code that follows will make you cry;
 *          a safety pig is provided below for your benefit
 * 
 *                           _
 *   _._ _..._ .-',     _.._(`))
 *  '-. `     '  /-._.-'    ',/
 *     )         \            '.
 *    / _    _    |             \
 *   |  a    a    /              |
 *   \   .-.                     ;  
 *    '-('' ).-'       ,'       ;
 *       '-;           |      .'
 *          \           \    /
 *          | 7  .__  _.-\   \
 *          | |  |  ``/  /`  /
 *         /,_|  |   /,_/   /
 *            /,_/      '`-'
 *            
 */
// Note, the safety pig is in C style comments as there are lines ending in "\"
// which is an error in some compilers.
#include <iostream>

//=============================================================================
int main()
{
  std::cout << "Safety pig." << std::endl;
  std::cout << ""
               "                          _     \n"   
               "  _._ _..._ .-',     _.._(`))   \n"
               " '-. `     '  /-._.-'    ',/    \n"
               "    )         \\            '.  \n"
               "   / _    _    |             \\ \n"
               "  |  a    a    /              | \n"
               "  \\   .-.                      \n" 
               "   '-('' ).-'       ,'       ;  \n"
               "      '-;           |      .'   \n"
               "         \\           \\    /   \n"
               "         | 7  .__  _.-\\   \\   \n"
               "         | |  |  ``/  /`  /     \n"
               "        /,_|  |   /,_/   /      \n"
               "           /,_/      '`-'       \n"
               "                                \n";
  return 0;
}
