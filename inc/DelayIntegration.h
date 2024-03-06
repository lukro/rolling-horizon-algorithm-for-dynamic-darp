#include <ilcplex/ilocplex.h>
#include <ilconcert/iloexpression.h>

template<int S>
class DelayIntegration {
private:
    typedef std::array<int,S> NODE;
    typedef std::array<NODE,2> ARC;

    double delay;
    double probability;

    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_real_distribution<> dis{0, 1};

    TerminalOutputFormatter<S>* tof;

public:
    DelayIntegration(double probability, double delay, TerminalOutputFormatter<S>* tof);

    void incorporate_delay(std::stringstream& name, 
                        IloEnv& env, 
                        IloModel& model, 
                        IloNumVarArray& B, 
                        IloRangeArray& fixed_B, 
                        std::vector<ARC> fixed_edges,
                        std::pair<NODE,double>* active_node,
                        std::unordered_map<NODE, uint64_t, HashFunction<S>> vmap,
                        const double epsilon,
                        int n);

    void propagate_delay(NODE delayed_event, 
                        std::map<NODE, double> &node_delay, 
                        std::vector<ARC> fixed_edges, 
                        int n);
};

