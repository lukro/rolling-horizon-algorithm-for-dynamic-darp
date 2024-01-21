import osmnx as ox
import geopandas as gpd
import numpy as np
import networkx as nx

def get_bus_stops(city_name, number_of_stops=100):
    # Define the tags for bus stops
    tags = {'public_transport': 'stop_position'}

    # Use OSMnx to download the data
    bus_stops = ox.features_from_place(city_name, tags)[:number_of_stops]

    return bus_stops

def calculate_driving_distance(G, point1, point2):
    """
    Calculate the driving distance between two points using the road network G.
    Points are given as (latitude, longitude).
    """
    # Get the nearest nodes to the points on the road network
    node1 = ox.nearest_nodes(G, point1[1], point1[0])
    node2 = ox.nearest_nodes(G, point2[1], point2[0])

    # Calculate the shortest path length
    length = nx.shortest_path_length(G, node1, node2, weight='length')
    return length / 1000  # Convert to kilometers

def get_points_from_geometry(geometry):
    """
    Extracts a point from geometry, which can be Point or Polygon.
    If it's a Polygon, returns the centroid.
    """
    if isinstance(geometry, gpd.geoseries.GeoSeries):
        return [(geom.centroid.y, geom.centroid.x) if geom.type == 'Polygon' 
                else (geom.centroid.y, geom.centroid.x) for geom in geometry]
    else:
        return (geometry.centroid.y, geometry.centroid.x) if geometry.type == 'Polygon' else (geometry.y, geometry.x)

def get_distance_matrix(city_name):
    G = ox.graph_from_place(city_name, network_type='drive')
    bus_stops = get_bus_stops(city_name,50)

    # Convert bus stops to suitable format (GeoDataFrame to list of tuples)
    #bus_stops['geometry'] = bus_stops['geometry'].to_crs(epsg=4326)  # Ensure CRS is WGS84 (lat, long)

    coords = [(point.y, point.x) for point in bus_stops['geometry']]
    nodes = [ox.nearest_nodes(G, coord[0], coord[1]) for coord in coords]

    # Initialize a 2D array for distances
    distances = np.zeros((len(nodes), len(nodes)))

    # Calculate the shortest path length between each pair of bus stops
    for i, node_start in enumerate(nodes):
        for j, node_end in enumerate(nodes[i+1:]):
            try:
                distances[i, j] = nx.shortest_path_length(G, node_start, node_end, weight='length')
            except nx.NetworkXNoPath:
                distances[i, j] = float('inf')

    return distances

#save output of get_bus_stop_distances for the first 100 bus stops in a file
distances = get_distance_matrix('Kitzingen, Germany')
np.savetxt("distances.txt", distances)


#print("Test")