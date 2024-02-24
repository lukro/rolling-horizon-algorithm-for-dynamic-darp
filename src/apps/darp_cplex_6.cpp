#include "DARPH.h"

int main(int argc,char* argv[]) 
{
    bool accept_all = false;
    bool consider_excess_ride_time = true;
    bool dynamic = true; 
    bool heuristic = true;

    std::string instance(argv[1]);

    //optional arguments
    double tt_delay = 0, bv_delay = 0, probability = 1;
    for (int i = 2; i < argc; i++) {
        std::string arg(argv[i]);
        if ((arg == "-td") && i + 1 < argc) {
            tt_delay = std::stod(argv[++i]);
        } else if ((arg == "-bd") && i + 1 < argc) {
            bv_delay = std::stod(argv[++i]);
        } else if ((arg == "-p") && i + 1 < argc) {
            probability = std::stod(argv[++i]);
        } else {
            std::cerr << "Unknown argument: " << arg << std::endl;
        }
    }
    
    //const std::string data_directory = "data/WSW/"; 
    const std::string data_directory = "data/a_b_first_line_modified/"; 

    
    std::string path_to_instance = data_directory + instance + ".txt";
   
    
    int num_requests = DARPGetDimension(path_to_instance)/2;
    
    auto D = DARP(num_requests);
    auto RH = RollingHorizon<6>(num_requests, tt_delay, bv_delay, probability);  
    
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
    
    RH.detailed_file(D,argv[1]);
    
    return 0;
}

