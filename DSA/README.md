# Data Structures and Algorithms

## Overview
Creats the ScholarNet affiliation graph. 
This graph connects affiliations based on shared publications and enables the implementation of new algorithms, such as finding the shortest path between affiliations.

## Contents
- **Graph Implementation**: Includes the creation and manipulation of the ScholarNet affiliation graph.
- **Compulsory Functions**: Essential functions that must be implemented for the assignment to be considered complete.
- **Optional Functions**: Additional functions that can enhance your grade if implemented efficiently.

## Terminology
- **Connection**: A link between two affiliations. The length of a connection is calculated based on the distance between (x, y) coordinates of both affiliations, with an additional weight for each common publication.
- **Weight**: Each common publication between two affiliations increases the connection weight by one.
- **Friction**: Defined as the reverse of weight. The larger the weight, the less friction. If the friction of two paths is the same, the path with fewer connections has lower friction.

## Examples
- **Path A**: Two connections with weights 2 and 3, minimum connection weight of 2, total distance of 2 connections.
- **Path B**: Three connections with weights 3, 3, and 2, same minimum connection weight as Path A, but longer distance and higher friction.
- **Path C**: Four connections with weights 10, 5, 3, and 4, minimum connection weight of 3, and the lowest friction.
- **Path D**: Two connections with weights 1 and 20, minimum connection weight of 1, and the highest friction.

## Structure and Functionality
### Provided Files
The following files are provided and should not be modified:
- `mainprogram.hh`
- `mainprogram.cc`
- `mainwindow.hh`
- `mainwindow.cc`
- `mainwindow.ui`

### Files to Modify
- **File `datastructures.hh`**: The public interface of the `Datastructures` class is provided. No changes to the public interface are allowed. New methods and data members can be added to the private side.
- **File `datastructures.cc`**: Implement the required operations for the assignment.

### Graphical User Interface
The GUI provided by QtCreator allows for interactive testing and visualization:
- **get_all_affiliations()**: Returns a list of affiliations.
- **get_all_connections()**: Provides a list of all connections.
- **get_affiliation_coord()**: Retrieves affiliation coordinates.
- **get_affiliation_name()**: Obtains affiliation names.

### Running the Program
To execute the program, use command-line parameters or run it from the QtCreator GUI. Commands that require member functions will be linked to the corresponding function in the `Datastructures` class.

## Compulsory Functions
- **get_connected_affiliations**
  std::vector<Connection> get_connected_affiliations(AffiliationID id)
This function returns the connections from the given source affiliation to target affiliations. If an affiliation with the given ID does not exist, an empty vector is returned. The connections can be returned in arbitrary order, but for each connection, the first affiliation (aff1) must be the given ID, and the second affiliation (aff2) must be connected to the given one.

- **get_all_connections**
    std::vector<Connection> get_all_connections()
Returns all connections as a vector. Each connection must contain the smaller affiliation ID first (in Connection aff1 < aff2). There should be no duplicate connections, and the connections are returned in an arbitrary order. If there are no connections, an empty vector is returned.

- **get_any_path**
    std::vector<Connection> get_any_path(AffiliationID source, AffiliationID target)
Returns an arbitrary path between two given affiliations. The returned vector contains connections from the source to the target. For a single connection, the order of IDs must be such that the path can be followed along the connections from aff1 to aff2 at all times. If the source, target, or path does not exist, an empty vector is returned.

## Optional Functions
- **get_path_with_least_affiliations**
    std::vector<Connection> get_path_with_least_affiliations(AffiliationID source, AffiliationID target)
Optional. Returns a path between the given affiliations with as few affiliations as possible. If several paths with the same number of affiliations exist, any of those can be returned. The returned vector contains connections from the source to the target. If the source, target, or path does not exist, an empty vector is returned.

- **get_path_of_least_friction**
    std::vector<Connection> get_path_of_least_friction(AffiliationID source, AffiliationID target)
Optional. Returns a path between the given affiliations so that the friction is as small as possible. If several paths with equal friction exist, any of those can be returned. The returned vector contains connections from the source to the target. If the source, target, or path does not exist, an empty vector is returned. (The friction is defined in the "Terminology" section.)

- **get_shortest_path**
    PathWithDist get_shortest_path(AffiliationID source, AffiliationID target)
Returns the shortest path between affiliations as a PathWithDist vector. If there are multiple equally valid options, any of them can be returned. The path includes affiliations starting from the initial point and ending at the destination point. PathWithDist has the format: std::vector<std::pair<Connection, Distance>>, where, in addition to the connection, the distance between the affiliations connected by that connection is specified. If the initial point, destination point, or the connecting path between them does not exist, an empty vector is returned.