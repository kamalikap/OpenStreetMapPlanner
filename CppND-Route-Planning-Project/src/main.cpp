#include <optional>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <io2d.h>
#include "route_model.h"
#include "render.h"
#include "route_planner.h"

using namespace std::experimental;

static std::optional<std::vector<std::byte>> ReadFile(const std::string &path)
{   
  	
    // ReadFile creates an input file stream called 'is'. 'is' is initialized with standard
    // ios binary(reads only binary data)
    //  and standard ios ate(at the end: This is will immediately set to the end of the input stream)
    std::ifstream is{path, std::ios::binary | std::ios::ate};
    if( !is )
        return std::nullopt;
    
  	// tellg determines the size of the input file.  
 	auto size = is.tellg();
    std::vector<std::byte> contents(size);    
    
  	// seeks back to the beginning of the input stream.
    is.seekg(0);
  
  	//read all the input stream to the contents vector
    is.read((char*)contents.data(), size);

    if( contents.empty() )
        return std::nullopt;
  	// move allows the contents of the vector to transfer to another vector.
    return std::move(contents);
}

int main(int argc, const char **argv)
{    
    std::string osm_data_file = "";
    if( argc > 1 ) {
        for( int i = 1; i < argc; ++i )
          	// '-f' allows to specify the osm data file to be used.
            if( std::string_view{argv[i]} == "-f" && ++i < argc )
                osm_data_file = argv[i];
    }
  	// if there is no osm data file, then it would be set to map.osm

    else {
        std::cout << "To specify a map file use the following format: " << std::endl;
        std::cout << "Usage: [executable] [-f filename.osm]" << std::endl;
        osm_data_file = "../map.osm";
    }
    
  	//vector of bytes called data
    std::vector<std::byte> osm_data;
 	
  	//Here the contents of the osm_data_file is read into osm_data.
    if( osm_data.empty() && !osm_data_file.empty() ) {
        std::cout << "Reading OpenStreetMap data from the following file: " <<  osm_data_file << std::endl;
        auto data = ReadFile(osm_data_file);
        if( !data )
            std::cout << "Failed to read." << std::endl;
        else
            osm_data = std::move(*data);
    }
    
    // TODO 1: Declare floats `start_x`, `start_y`, `end_x`, and `end_y` and get
    // user input for these values using std::cin. Pass the user input to the
    // RoutePlanner object below in place of 10, 10, 90, 90.
  
  	float start_x;
  	float start_y;
  	float end_x;
  	float end_y;
	
  	std::cout << "Enter the 'x' co-ordinate of start point: ";
  	std::cin >> start_x;
      
	std::cout << "Enter the 'y' co-ordinate of start point: ";
  	std::cin >> start_y;
  
  
  	std::cout << "Enter the 'x' co-ordinate of end point: ";
  	std::cin >> end_x;
  
  
  	std::cout << "Enter the 'y' co-ordinate of end point: ";
  	std::cin >> end_y;
  
  	//std::cout << "The co-ordinates of start point are: " << start_x << ', ' << start_y <<'\n';
  	//std::cout << "The co-ordinates of end point are: " << end_x << ', ' << end_y << '\n';

    // Build Model.
  // RouteModel object called model uses the OSM data.
    RouteModel model{osm_data};

    // Create RoutePlanner object and perform A* search.
  // 10, 10 are the starting points and 90, 90 are the x, y co-ordinates of end points.
    // start = (10, 10) , end = (90, 90)
    RoutePlanner route_planner{model, start_x, start_y, end_x, end_y};
  	 // AStarSearch is performed by route_planner which records the result of the search.
    route_planner.AStarSearch();

    std::cout << "Distance: " << route_planner.GetDistance() << " meters. \n";

    // Render results of search.
  // Render object is created using model
    Render render{model};
  
	//io2d code to display the results.
    auto display = io2d::output_surface{400, 400, io2d::format::argb32, io2d::scaling::none, io2d::refresh_style::fixed, 30};
    display.size_change_callback([](io2d::output_surface& surface){
        surface.dimensions(surface.display_dimensions());
    });
    display.draw_callback([&](io2d::output_surface& surface){
        render.Display(surface);
    });
    display.begin_show();
}
