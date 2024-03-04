#include "DARPH.h"
#include "TerminalOutput.h"
#include <sstream>
#include <map>

class DelayIntegration {
private:
    typedef std::array<int,6> NODE;
    typedef std::array<NODE,2> ARC;

    //manual delays
    //TODO: auf ein Schema festlegen
    double tt_delay;
    double bv_delay;
    double probability;

    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_real_distribution<> dis{0, 1};

public:
    void incorporate_delay(std::stringstream& name, 
                        IloEnv& env, 
                        IloModel& model, 
                        IloNumVarArray& B, 
                        IloRangeArray& fixed_B, 
                        std::vector<ARC> fixed_edges,
                        std::pair<NODE,double>* active_node,
                        int n);

    void propagate_delay(NODE delayed_event, std::map<NODE, double> &node_delay, std::vector<ARC> fixed_edges);
};