// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <exception>
#include <map>
#include <set>
#include <unordered_set>
#include <queue>
#include <list>

// Types for IDs
using AffiliationID = std::string;
using PublicationID = unsigned long long int;
using Name = std::string;
using Year = unsigned short int;
using Weight = int;
struct Connection;
// Type for a distance (in arbitrary units)
using Distance = int;

using Path = std::vector<Connection>;
using PathWithDist = std::vector<std::pair<Connection, Distance>>;

// Return values for cases where required thing was not found
AffiliationID const NO_AFFILIATION = "---";
PublicationID const NO_PUBLICATION = -1;
Name const NO_NAME = "!NO_NAME!";
Year const NO_YEAR = -1;
Weight const NO_WEIGHT = -1;

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};

// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1 == c2); } // Not strictly necessary

struct CoordHash
{
    std::size_t operator()(Coord xy) const
    {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y)
    {
        return true;
    }
    else if (c2.y < c1.y)
    {
        return false;
    }
    else
    {
        return c1.x < c2.x;
    }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

struct Connection
{
    AffiliationID aff1 = NO_AFFILIATION;
    AffiliationID aff2 = NO_AFFILIATION;
    Weight weight = NO_WEIGHT;
    bool operator==(const Connection &c1) const
    {
        return (aff1 == c1.aff1) && (aff2 == c1.aff2) && (weight == c1.weight);
    }
};
const Connection NO_CONNECTION{NO_AFFILIATION, NO_AFFILIATION, NO_WEIGHT};

// Return value for cases where Distance is unknown
Distance const NO_DISTANCE = NO_VALUE;

// This exception class is there just so that the user interface can notify
// about operations which are not (yet) implemented
class NotImplemented : public std::exception
{
public:
    NotImplemented() : msg_{} {}
    explicit NotImplemented(std::string const &msg) : msg_{msg + " not implemented"} {}

    virtual const char *what() const noexcept override
    {
        return msg_.c_str();
    }

private:
    std::string msg_;
};

// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance:
    // Short rationale for estimate:
    unsigned int get_affiliation_count();

    // Estimate of performance:
    // Short rationale for estimate:
    void clear_all();

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<AffiliationID> get_all_affiliations();

    // Estimate of performance:
    // Short rationale for estimate:
    bool add_affiliation(AffiliationID id, Name const &name, Coord xy);

    // Estimate of performance:
    // Short rationale for estimate:
    Name get_affiliation_name(AffiliationID id);

    // Estimate of performance:
    // Short rationale for estimate:
    Coord get_affiliation_coord(AffiliationID id);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<AffiliationID> get_affiliations_alphabetically();

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<AffiliationID> get_affiliations_distance_increasing();

    // Estimate of performance:
    // Short rationale for estimate:
    AffiliationID find_affiliation_with_coord(Coord xy);

    // Estimate of performance:
    // Short rationale for estimate:
    bool change_affiliation_coord(AffiliationID id, Coord newcoord);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance:
    // Short rationale for estimate:
    bool add_publication(PublicationID id, Name const &name, Year year, const std::vector<AffiliationID> &affiliations);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<PublicationID> all_publications();

    // Estimate of performance:
    // Short rationale for estimate:
    Name get_publication_name(PublicationID id);

    // Estimate of performance:
    // Short rationale for estimate:
    Year get_publication_year(PublicationID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<AffiliationID> get_affiliations(PublicationID id);

    // Estimate of performance:
    // Short rationale for estimate:
    bool add_reference(PublicationID id, PublicationID parentid);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<PublicationID> get_direct_references(PublicationID id);

    // Estimate of performance:
    // Short rationale for estimate:
    bool add_affiliation_to_publication(AffiliationID affiliationid, PublicationID publicationid);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<PublicationID> get_publications(AffiliationID id);

    // Estimate of performance:
    // Short rationale for estimate:
    PublicationID get_parent(PublicationID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<std::pair<Year, PublicationID>> get_publications_after(AffiliationID affiliationid, Year year);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<PublicationID> get_referenced_by_chain(PublicationID id);

    // Non-compulsory operations

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<PublicationID> get_all_references(PublicationID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<AffiliationID> get_affiliations_closest_to(Coord xy);

    // Estimate of performance:
    // Short rationale for estimate:
    bool remove_affiliation(AffiliationID id);

    // Estimate of performance:
    // Short rationale for estimate:
    PublicationID get_closest_common_parent(PublicationID id1, PublicationID id2);

    // Estimate of performance:
    // Short rationale for estimate:
    bool remove_publication(PublicationID publicationid);

    // PRG 2 functions:

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: using for-loop twice
    // Each time complexity is O(n).
    std::vector<Connection> get_connected_affiliations(AffiliationID id);

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: using for-loop twice
    // Each time complexity is O(n).
    std::vector<Connection> get_all_connections();

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: using for-loop twice
    // Each time complexity is O(n).
    Path get_any_path(AffiliationID source, AffiliationID target);

    // PRG2 optional functions

    // Estimate of performance:
    // Short rationale for estimate:
    Path get_path_with_least_affiliations(AffiliationID source, AffiliationID target);

    // Estimate of performance:
    // Short rationale for estimate:
    Path get_path_of_least_friction(AffiliationID source, AffiliationID target);

    // Estimate of performance:
    // Short rationale for estimate:
    PathWithDist get_shortest_path(AffiliationID source, AffiliationID target);

private:
    struct Affiliation
    {
        Name _name = NO_NAME;
        Coord _xy = NO_COORD;
        std::vector<PublicationID> _publications = {};
    };

    struct Publication
    {
        Name _name = NO_NAME;
        Year _year = NO_YEAR;
        std::vector<AffiliationID> _affiliations = {};
        std::vector<PublicationID> _references = {};
        PublicationID _parentId = NO_PUBLICATION;
    };

    struct CompareCoords
    {

        int get_squared_distance_from_original(const Coord &xy) const
        {
            int x = xy.x;
            int y = xy.y;
            return x * x + y * y;
        }

        bool operator()(const Coord &c1, const Coord &c2) const
        {
            int dist1 = get_squared_distance_from_original(c1);
            int dist2 = get_squared_distance_from_original(c2);

            if (dist1 < dist2)
            {
                return true;
            }
            else if (dist2 < dist1)
            {
                return false;
            }
            else
            {
                return c1.y < c2.y;
            }
        }
    };

    std::unordered_map<AffiliationID, Affiliation> _affiliations = {};
    std::unordered_map<PublicationID, Publication> _publications = {};
    std::set<std::pair<Name, AffiliationID>> _setAlpha = {};
    std::map<Coord, AffiliationID, CompareCoords> _mapCoord = {};
    bool _alphaChanged = false;
    bool _distChanged = false;
    std::vector<AffiliationID> _affiliationsByAlpha = {};
    std::vector<AffiliationID> _affiliationsByDist = {};
    int NUM_OF_CLOSEST = 3;

    struct Node
    {
        std::unordered_map<AffiliationID, std::pair<Weight, int>> neighbors = {};
        Node *to = nullptr;
    };
    std::unordered_map<AffiliationID, Node> _graph;
    std::unordered_map<PublicationID, std::vector<AffiliationID>> _connectedAffs = {};
    std::unordered_map<AffiliationID, std::unordered_set<AffiliationID>> _addedAffs = {};
    std::unordered_set<AffiliationID> _distChangedAffs = {};

    void update_graph();
    void update_dist();
    Path reconstruct_path(const std::unordered_map<AffiliationID, AffiliationID> &parent,
                          AffiliationID source, AffiliationID target);
    PathWithDist reconstruct_pathWithDist(const std::unordered_map<AffiliationID, AffiliationID> &parent,
                                          AffiliationID source, AffiliationID target);
};

#endif // DATASTRUCTURES_HH
