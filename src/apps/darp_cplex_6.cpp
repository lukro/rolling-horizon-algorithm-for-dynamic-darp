#include "DARPH.h"


void runBenchmark(double node_arrival_delay, double probability, int run) {
    std::string instance = "no_011_6_req";
    std::string data_directory = "data/WSW/"; 
    std::string path_to_instance = data_directory + instance + ".txt";
    int num_requests = DARPGetDimension(path_to_instance)/2;

    auto D = DARP(num_requests);
    auto RH = RollingHorizon<6>(num_requests, 0, node_arrival_delay, probability);

    D.set_instance_mode(2);
    D.read_file(path_to_instance, data_directory, instance);
    D.transform_dynamic();

    bool accept_all = false;
    bool consider_excess_ride_time = true;
    bool dynamic = true; 
    bool heuristic = true;
    auto G = DARPGraph<6>(num_requests);
    auto lsg = RH.solve(accept_all, consider_excess_ride_time, dynamic, heuristic, D, G);
    
    RH.compute_stats(D);
}


void benchmark() {
    std::streambuf* originalCoutBuffer = std::cout.rdbuf();

    for(double node_arrival_delay = 0; node_arrival_delay <= 1; node_arrival_delay += 0.05) {
        for(double probability = 0.1; probability <= 1; probability += 0.1) {
            for(int run = 0; run < 10; run++) {
                std::ostringstream output_filename;
    
                output_filename << "output/probability_travel-delay_run/"
                                << std::setprecision(2) << probability << "p_"
                                << std::setprecision(2) << std::setprecision(2) << node_arrival_delay
                                << "nd";
                if(run!=-1)
                    output_filename << "_run" << run;
                output_filename << ".txt";
                std::ofstream outFile(output_filename.str());

                std::cout.rdbuf(outFile.rdbuf()); 
                runBenchmark(node_arrival_delay, probability, run);
                std::cout.rdbuf(originalCoutBuffer); 

                outFile.close();
            }
        }
    }
}

int main(int argc,char* argv[]) 
{
    bool accept_all = false;
    bool consider_excess_ride_time = true;
    bool dynamic = true; 
    bool heuristic = true;
    std::string instance;
    std::string data_directory;

    std::string inst(argv[1]);
    if(inst == "no6") {
        instance = "no_011_6_req";
        data_directory = "data/WSW/"; 
    } else if (inst == "-bm") {
        benchmark();
        return 0;
    } else {
        instance = argv[1];
        data_directory = "data/a_b_first_line_modified/"; 
    }

    //optional arguments
    double travel_time_delay = 0, node_arrival_delay = 0, probability = 0;
    for (int i = 2; i < argc; i++) {
        std::string arg(argv[i]);
        if ((arg == "--travel-time-delay") && i + 1 < argc) {
            travel_time_delay = std::stod(argv[++i]);
        } else if ((arg == "--node-delay" || arg == "-nd") && i + 1 < argc) {
            node_arrival_delay = std::stod(argv[++i]);
        } else if ((arg == "-p") && i + 1 < argc) {
            probability = std::stod(argv[++i]);
        } else {
            std::cerr << "Unknown argument: " << arg << std::endl;
        }
    }
        
    std::string path_to_instance = data_directory + instance + ".txt";
    int num_requests = DARPGetDimension(path_to_instance)/2;
    
    auto D = DARP(num_requests);
    auto RH = RollingHorizon<6>(num_requests, travel_time_delay, node_arrival_delay, probability);  
    
    // switch between different types of instances
    // 1: instances Berbeglia et al. (2012)
    // 2: WSW
    D.set_instance_mode(1);
    if (data_directory == "data/WSW/")
        D.set_instance_mode(2);

    // read instance from file
    D.read_file(path_to_instance, data_directory, instance);
    
    if (D.get_instance_mode() == 1)
        D.preprocess();

    // instance mode 1: transform instance into dynamic instance, see Berbeglia et al. (2012)
    // instance mode 2: save times of show-up to become_known_array
    D.transform_dynamic();

    auto G = DARPGraph<6>(num_requests);
    
    // consider excess ride time or not 
    if (D.get_instance_mode() == 2)
        consider_excess_ride_time = true;
    else
        consider_excess_ride_time = false;

    // solve instance
    auto lsg = RH.solve(accept_all, consider_excess_ride_time, dynamic, heuristic, D, G);
 
    RH.compute_stats(D);    
    return 0;
}

