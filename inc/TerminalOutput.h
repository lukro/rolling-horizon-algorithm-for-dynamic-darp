// ANSI color codes
#define FORMAT_STOP             "\033[0m"
#define WHITE                   "\033[37m"
#define MANJ_GREEN              "\033[1m\033[38;2;22;160;133m"
#define MANJ_GREEN_BG           "\033[48;2;22;160;133m"
#define YELLOW_UNDERLINED       "\033[33m"  
#define WHITE_YELLOW_BG         "\033[1;37m\033[43m"
#define WHITE_MANJ_GREEN_BG     "\033[1;37m\033[48;2;22;160;133m"
#define BLACK_YELLOW_BG         "\033[0;30m\033[43m"

#include "DARPH.h" // or wherever NODE and ARC are defined

#include <sys/ioctl.h>
#include <unistd.h>
#include <sstream>

class TerminalOutput {
    private:
        typedef std::array<int,6> NODE;
        typedef std::array<NODE,2> ARC;
    public: 
    namespace TerminalOutput {
        static void print_node(std::string before, std::string color, NODE node, std::string after, int n);
        
        static std::string get_printable_header(int num_milps, double time);
        static std::string get_printable_event_block(int node, 
                                            double time, 
                                            double time_passed, 
                                            int &characters_printed, 
                                            int terminal_width, 
                                            int n);
        static int get_current_terminal_width();
        static std::string convertDoubleToMinutes(double time);
    }
};