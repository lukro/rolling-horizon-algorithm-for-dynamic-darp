/*
// ANSI color codes
#define FORMAT_STOP             "\033[0m"
#define WHITE                   "\033[37m"
#define MANJ_GREEN              "\033[1m\033[38;2;22;160;133m"
#define MANJ_GREEN_BG           "\033[48;2;22;160;133m"
#define YELLOW_UNDERLINED       "\033[33m"  
#define WHITE_YELLOW_BG         "\033[1;37m\033[43m"
#define WHITE_MANJ_GREEN_BG     "\033[1;37m\033[48;2;22;160;133m"
#define BLACK_YELLOW_BG         "\033[0;30m\033[43m"

#include <sys/ioctl.h>
#include <unistd.h>
#include <map>

#include <sstream>
#include <map>
#include "DARPH.h" // or wherever NODE and ARC are defined

typedef std::array<int,6> NODE;
typedef std::array<NODE,2> ARC;

void printNode(std::string before, std::string color, NODE node, std::string after, int n);
std::string get_printable_header(int num_milps, double time);
std::string get_printable_event_block(int node, double time, int& characters_printed, int terminal_width);
int get_current_terminal_width();

void incorporate_delay(std::stringstream& name, IloEnv& env, IloModel& model, IloNumVarArray& B, IloRangeArray& fixed_B, std::map<NODE, double>& node_delay, std::vector<ARC>& fixed_edges, std::vector<std::pair<NODE, double>>& active_node, std::map<NODE, int>& vmap, double epsilon, double probability, double bv_delay, std::default_random_engine& gen, int n);
void propagate_delay(NODE delayed_event, std::map<NODE, double>& node_delay, std::vector<ARC>& fixed_edges);*/

