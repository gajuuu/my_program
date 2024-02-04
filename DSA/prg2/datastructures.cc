// Datastructures.cc

#include "datastructures.hh"
#include <random>
#include <cmath>
#include <unordered_set>
#include <stack>
#include <QDebug>
#include <queue>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end - start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range - 1)(rand_engine);

    return static_cast<Type>(start + num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{
    // Write any initialization you need here
}

Datastructures::~Datastructures()
{
    // Write any cleanup you need here
}

unsigned int Datastructures::get_affiliation_count()
{
    return _affiliations.size();
}

void Datastructures::clear_all()
{
    _affiliations.clear();
    _publications.clear();
    _setAlpha.clear();
    _alphaChanged = true;
    _distChanged = true;
    _affiliationsByAlpha.clear();
    _affiliationsByDist.clear();
    _mapCoord.clear();
    _graph.clear();
}

std::vector<AffiliationID> Datastructures::get_all_affiliations()
{
    std::vector<AffiliationID> v = {};
    v.reserve(get_affiliation_count());
    for (const auto &key : _affiliations)
    {
        v.push_back(key.first);
    }
    return v;
}

int get_distance(Coord xy1, Coord xy2)
{
    int x = xy1.x - xy2.x;
    int y = xy1.y - xy2.y;
    return sqrt(pow(x, 2) + pow(y, 2));
}

bool Datastructures::add_affiliation(AffiliationID id, const Name &name, Coord xy)
{
    if (_affiliations.find(id) != _affiliations.end())
    {
        return false;
    }
    _affiliations[id] = {name, xy};
    _setAlpha.insert({name, id});
    _mapCoord[xy] = id;
    _alphaChanged = true;
    _distChanged = true;
    return true;
}

Name Datastructures::get_affiliation_name(AffiliationID id)
{
    if (_affiliations.find(id) == _affiliations.end())
    {
        return NO_NAME;
    }
    return _affiliations[id]._name;
}

Coord Datastructures::get_affiliation_coord(AffiliationID id)
{
    if (_affiliations.find(id) == _affiliations.end())
    {
        return NO_COORD;
    }
    return _affiliations[id]._xy;
}

std::vector<AffiliationID> Datastructures::get_affiliations_alphabetically()
{
    if (_alphaChanged)
    {
        std::vector<AffiliationID> vecId = {};
        vecId.reserve(get_affiliation_count());
        _affiliationsByAlpha.clear();
        for (const auto &element : _setAlpha)
        {
            vecId.push_back(element.second);
        }
        _affiliationsByAlpha = vecId;
        _alphaChanged = false;
    }

    return _affiliationsByAlpha;
}

std::vector<AffiliationID> Datastructures::get_affiliations_distance_increasing()
{
    if (_distChanged)
    {
        std::vector<AffiliationID> vecId = {};
        vecId.reserve(get_affiliation_count());
        _affiliationsByDist.clear();
        for (const auto &element : _mapCoord)
        {
            vecId.push_back(element.second);
        }
        _affiliationsByDist = vecId;
        _distChanged = false;
    }

    return _affiliationsByDist;
}

AffiliationID Datastructures::find_affiliation_with_coord(Coord xy)
{
    if (_mapCoord.find(xy) != _mapCoord.end())
    {
        return _mapCoord[xy];
    }
    else
    {
        return NO_AFFILIATION;
    }
}

bool Datastructures::change_affiliation_coord(AffiliationID id, Coord newcoord)
{
    auto target = _affiliations.find(id);

    if (target == _affiliations.end())
    {
        return false;
    }

    Coord currentCoord = _affiliations[id]._xy;
    _mapCoord.erase(currentCoord);
    _mapCoord[newcoord] = id;
    _distChanged = true;
    _distChangedAffs.insert(id);
    _affiliations[id]._xy = newcoord;
    return true;
}

bool Datastructures::add_publication(PublicationID id, const Name &name, Year year,
                                     const std::vector<AffiliationID> &affiliations)
{
    if (_publications.find(id) != _publications.end())
    {
        return false;
    }
    _publications[id] = {name, year, affiliations};

    for (const auto &affiliation : affiliations)
    {
        _affiliations[affiliation]._publications.push_back(id);
    }

    _connectedAffs[id] = affiliations;
    return true;
}

std::vector<PublicationID> Datastructures::all_publications()
{
    std::vector<PublicationID> v;
    v.reserve(_publications.size());
    for (const auto &element : _publications)
    {
        v.push_back(element.first);
    }
    return v;
}

Name Datastructures::get_publication_name(PublicationID id)
{
    if (_publications.find(id) == _publications.end())
    {
        return NO_NAME;
    }
    return _publications[id]._name;
}

Year Datastructures::get_publication_year(PublicationID id)
{
    if (_publications.find(id) == _publications.end())
    {
        return NO_YEAR;
    }
    return _publications[id]._year;
}

std::vector<AffiliationID> Datastructures::get_affiliations(PublicationID id)
{
    if (_publications.find(id) == _publications.end())
    {
        return {NO_AFFILIATION};
    }
    return _publications[id]._affiliations;
}

bool Datastructures::add_reference(PublicationID id, PublicationID parentid)
{
    if (_publications.find(id) == _publications.end() || _publications.find(parentid) == _publications.end())
    {
        return false;
    }
    _publications[parentid]._references.push_back(id);
    _publications[id]._parentId = parentid;
    return true;
}

std::vector<PublicationID> Datastructures::get_direct_references(PublicationID id)
{
    if (_publications.find(id) == _publications.end())
    {
        return {NO_PUBLICATION};
    }
    return _publications[id]._references;
}

bool Datastructures::add_affiliation_to_publication(AffiliationID affiliationid, PublicationID publicationid)
{
    if (_publications.find(publicationid) == _publications.end() || _affiliations.find(affiliationid) == _affiliations.end())
    {
        return false;
    }

    _addedAffs[affiliationid].insert(_publications[publicationid]._affiliations.begin(),
                                     _publications[publicationid]._affiliations.end());

    _publications[publicationid]._affiliations.push_back(affiliationid);
    _affiliations[affiliationid]._publications.push_back(publicationid);
    return true;
}

std::vector<PublicationID> Datastructures::get_publications(AffiliationID id)
{
    if (_affiliations.find(id) == _affiliations.end())
    {
        return {NO_PUBLICATION};
    }
    return _affiliations[id]._publications;
}

PublicationID Datastructures::get_parent(PublicationID id)
{
    if (_publications.find(id) == _publications.end())
    {
        return NO_PUBLICATION;
    }
    return _publications[id]._parentId;
}

std::vector<std::pair<Year, PublicationID>>
Datastructures::get_publications_after(AffiliationID affiliationid, Year year)
{
    std::vector<std::pair<Year, PublicationID>> v = {};
    if (_affiliations.find(affiliationid) == _affiliations.end())
    {
        return {{NO_YEAR, NO_PUBLICATION}};
    }

    std::vector<PublicationID> pubIds = _affiliations[affiliationid]._publications;
    v.reserve(pubIds.size());

    for (const PublicationID &id : pubIds)
    {
        if (_publications.at(id)._year >= year)
        {
            v.push_back({_publications.at(id)._year, id});
        }
    }

    std::sort(v.begin(), v.end(), [](const auto &a, const auto &b)
              {
        if (a.first != b.first) {
            return a.first < b.first;
        } else {
            return a.second < b.second;
        } });

    return v;
}

std::vector<PublicationID> Datastructures::get_referenced_by_chain(PublicationID id)
{
    std::vector<PublicationID> parentIDs = {};
    PublicationID parentId = get_parent(id);

    while (parentId != NO_PUBLICATION)
    {
        if (std::find(parentIDs.begin(), parentIDs.end(), parentId) == parentIDs.end())
        {
            parentIDs.push_back(parentId);
        }
        else
        {
            break;
        }
        auto it = _publications.find(parentId);
        parentId = it->second._parentId;
    }

    return parentIDs;
}

// Non-compulsory operations
std::vector<PublicationID> Datastructures::get_all_references(PublicationID id)
{
    if (_publications.find(id) == _publications.end())
    {
        return {NO_PUBLICATION};
    }
    std::vector<PublicationID> references = _publications[id]._references;
    std::set<PublicationID> setResult(references.begin(), references.end());

    for (const PublicationID ref : references)
    {
        std::vector<PublicationID> indirectRefs = _publications[ref]._references;
        setResult.insert(indirectRefs.begin(), indirectRefs.end());
    }

    std::vector<PublicationID> result(setResult.begin(), setResult.end());
    return result;
}

std::vector<AffiliationID> Datastructures::get_affiliations_closest_to(Coord xy)
{
    std::set<std::pair<int, AffiliationID>> setDist;
    for (const auto &pair : _mapCoord)
    {
        int dx = pair.first.x - xy.x;
        int dy = pair.first.y - xy.y;
        int dist = dx * dx + dy * dy;
        setDist.insert({dist, pair.second});
    }

    std::vector<AffiliationID> v;
    v.reserve(NUM_OF_CLOSEST);
    auto it = setDist.begin();
    for (int i = 0; i < NUM_OF_CLOSEST && it != setDist.end(); ++i, ++it)
    {
        v.push_back(it->second);
    }

    return v;
}

bool Datastructures::remove_affiliation(AffiliationID id)
{
    auto target = _affiliations.find(id);

    if (target == _affiliations.end())
    {
        return false;
    }

    Name targetName = _affiliations[id]._name;
    Coord targetCoord = _affiliations[id]._xy;
    const std::vector<PublicationID> &targetPubs = _affiliations[id]._publications;

    _setAlpha.erase({targetName, id});
    _mapCoord.erase(targetCoord);

    if (!targetPubs.empty())
    {
        for (const PublicationID &pubId : targetPubs)
        {
            auto &affiliations = _publications[pubId]._affiliations;
            affiliations.erase(std::remove(affiliations.begin(), affiliations.end(), id),
                               affiliations.end());
        }
    }

    _alphaChanged = true;
    _distChanged = true;
    _distChangedAffs.insert(id);
    _affiliations.erase(target);
    return true;
}

PublicationID Datastructures::get_closest_common_parent(PublicationID id1, PublicationID id2)
{
    std::vector<PublicationID> references1 = get_referenced_by_chain(id1);
    std::vector<PublicationID> references2 = get_referenced_by_chain(id2);
    for (const PublicationID &id : references1)
    {
        auto it = std::find(references2.begin(), references2.end(), id);
        if (it != references2.end())
        {
            return *it;
        }
    }
    return NO_PUBLICATION;
}

bool Datastructures::remove_publication(PublicationID publicationid)
{
    auto target = _publications.find(publicationid);

    if (target == _publications.end())
    {
        return false;
    }

    const std::vector<PublicationID> &targetRefs = _publications[publicationid]._references;
    const std::vector<AffiliationID> &targetAffs = _publications[publicationid]._affiliations;

    if (!targetRefs.empty())
    {
        for (const PublicationID &pubId : targetRefs)
        {
            auto &parent = _publications[pubId]._parentId;
            parent = NO_PUBLICATION;
        }
    }

    if (!targetAffs.empty())
    {
        for (const AffiliationID &affId : targetAffs)
        {
            auto &publications = _affiliations[affId]._publications;
            publications.erase(std::remove(publications.begin(), publications.end(), publicationid),
                               publications.end());
        }
    }

    _publications.erase(target);
    return true;
}

// project2
void Datastructures::update_graph()
{
    for (const auto &pair : _connectedAffs)
    {
        for (auto it1 = pair.second.begin(); it1 != pair.second.end(); ++it1)
        {
            for (auto it2 = std::next(it1); it2 != pair.second.end(); ++it2)
            {
                if (_graph.find(*it1) == _graph.end())
                {
                    _graph[*it1].neighbors[*it2].first = _graph[*it2].neighbors[*it1].first = 1;
                    _graph[*it1].neighbors[*it2].second = _graph[*it2].neighbors[*it1].second = get_distance(_affiliations[*it1]._xy, _affiliations[*it2]._xy);
                }
                else if (_graph[*it1].neighbors.find(*it2) == _graph[*it1].neighbors.end() ||
                         _graph[*it1].neighbors[*it2].first == NO_WEIGHT)
                {
                    _graph[*it1].neighbors[*it2].first = _graph[*it2].neighbors[*it1].first = 1;
                    _graph[*it1].neighbors[*it2].second = _graph[*it2].neighbors[*it1].second = get_distance(_affiliations[*it1]._xy, _affiliations[*it2]._xy);
                }
                else
                {
                    _graph[*it1].neighbors[*it2].first += 1;
                    _graph[*it2].neighbors[*it1].first += 1;
                    _graph[*it1].neighbors[*it2].second = _graph[*it2].neighbors[*it1].second = get_distance(_affiliations[*it1]._xy, _affiliations[*it2]._xy);
                }
            }
        }
    }

    for (const auto &pair1 : _addedAffs)
    {
        AffiliationID aff1 = pair1.first;
        for (const auto &aff2 : pair1.second)
        {
            _graph[aff1].neighbors[aff2].first = _graph[aff2].neighbors[aff1].first = 1;
            _graph[aff1].neighbors[aff2].second = _graph[aff1].neighbors[aff2].second = get_distance(_affiliations[aff1]._xy, _affiliations[aff2]._xy);
        }
    }
    _connectedAffs.clear();
    _addedAffs.clear();
}

std::vector<Connection> Datastructures::get_connected_affiliations(AffiliationID id)
{

    if (!(_connectedAffs.empty() && _addedAffs.empty()))
    {
        update_graph();
    }

    std::vector<Connection> connected_affiliations = {};
    for (const auto &pair : _graph[id].neighbors)
    {
        if (pair.second.first > 0)
        {
            connected_affiliations.push_back({id, pair.first, pair.second.first});
        }
    }

    return connected_affiliations;
}

std::vector<Connection> Datastructures::get_all_connections()
{

    if (!(_connectedAffs.empty() && _addedAffs.empty()))
    {
        update_graph();
    }

    std::vector<Connection> all_connections = {};
    for (const auto &pair1 : _graph)
    {
        AffiliationID aff1 = pair1.first;
        for (const auto &pair2 : _graph[aff1].neighbors)
        {
            AffiliationID aff2 = pair2.first;
            Weight weight = _graph[aff1].neighbors[aff2].first;
            if (aff1 < aff2 && weight > 0)
            {
                all_connections.push_back({aff1, aff2, weight});
            }
        }
    }
    return all_connections;
}

Path Datastructures::get_any_path(AffiliationID source, AffiliationID target)
{
    if (!(_connectedAffs.empty() && _addedAffs.empty()))
    {
        update_graph();
    }

    std::unordered_map<AffiliationID, bool> visited;
    std::stack<AffiliationID> stack;
    std::unordered_map<AffiliationID, AffiliationID> parent;
    Path path;

    stack.push(source);

    while (!stack.empty())
    {
        AffiliationID current = stack.top();
        stack.pop();

        if (current == target)
        {
            // Found the target, build and return the path
            AffiliationID nodeID = current;
            while (nodeID != source)
            {
                // Replace with the correct way to access the edge weight
                path.push_back({parent[nodeID], nodeID, _graph[parent[nodeID]].neighbors[nodeID].first});
                nodeID = parent[nodeID];
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        if (!visited[current])
        {
            visited[current] = true;

            for (const auto &pair : _graph[current].neighbors)
            {
                AffiliationID next = pair.first; // Replace with the correct way to access the neighbor
                if (!visited[next])
                {
                    stack.push(next);
                    parent[next] = current;
                }
            }
        }
    }
    path.clear();
    return path;
}

Path Datastructures::reconstruct_path(const std::unordered_map<AffiliationID, AffiliationID> &parent,
                                      AffiliationID source, AffiliationID target)
{
    Path path;
    AffiliationID current = target;

    while (current != source)
    {
        if (parent.find(current) == parent.end())
        {
            return {}; // No path exists
        }
        AffiliationID prev = parent.at(current);
        path.push_back({prev, current, _graph[prev].neighbors[current].first});
        current = prev;
    }

    std::reverse(path.begin(), path.end());
    return path;
}

Path Datastructures::get_path_with_least_affiliations(AffiliationID source, AffiliationID target)
{
    if (!(_connectedAffs.empty() && _addedAffs.empty()))
    {
        update_graph();
    }

    std::queue<AffiliationID> q;
    std::unordered_map<AffiliationID, AffiliationID> parent;
    std::unordered_map<AffiliationID, bool> visited;

    q.push(source);
    visited[source] = true;

    while (!q.empty())
    {
        AffiliationID current = q.front();
        q.pop();

        for (const auto &pair : _graph[current].neighbors)
        {
            AffiliationID next = pair.first;

            if (!visited[next])
            {
                q.push(next);
                visited[next] = true;
                parent[next] = current;
            }
        }
    }

    return reconstruct_path(parent, source, target);
}

Path Datastructures::get_path_of_least_friction(AffiliationID source, AffiliationID target)
{
    if (!(_connectedAffs.empty() && _addedAffs.empty()))
    {
        update_graph();
    }

    std::unordered_map<AffiliationID, Weight> min_weights;
    std::unordered_map<AffiliationID, int> node_counts;
    std::unordered_map<AffiliationID, AffiliationID> parent;

    std::priority_queue<std::pair<Weight, AffiliationID>,
                        std::vector<std::pair<Weight, AffiliationID>>,
                        std::greater<>>
        pq;

    // Initialization
    pq.push({std::numeric_limits<Weight>::max(), source});
    min_weights[source] = std::numeric_limits<Weight>::max();
    node_counts[source] = 0;

    while (!pq.empty())
    {
        auto current = pq.top().second;
        pq.pop();

        for (const auto &neighbor : _graph[current].neighbors)
        {
            AffiliationID next = neighbor.first;
            Weight edge_weight = neighbor.second.first;
            Weight min_weight = std::min(min_weights[current], edge_weight);

            if (min_weight > min_weights[next])
            {
                min_weights[next] = min_weight;
                node_counts[next] = node_counts[current] + 1;
                parent[next] = current; // Update parent information
                pq.push({min_weight, next});
            }
            else if (min_weight == min_weights[next] && node_counts[next] > node_counts[current] + 1)
            {
                // Update if the current path has fewer nodes
                node_counts[next] = node_counts[current] + 1;
                parent[next] = current; // Update parent information
            }
        }
    }

    // Reconstruct the path
    return reconstruct_path(parent, source, target);
}

void Datastructures::update_dist()
{
    for (const auto &id1 : _distChangedAffs)
    {
        for (const auto &connection : get_connected_affiliations(id1))
        {
            AffiliationID id2 = connection.aff2;
            _graph[id1].neighbors[id2].second = _graph[id2].neighbors[id1].second = get_distance(_affiliations[id1]._xy, _affiliations[id2]._xy);
        }
    }
    _distChangedAffs.clear();
}

PathWithDist Datastructures::reconstruct_pathWithDist(const std::unordered_map<AffiliationID, AffiliationID> &parent,
                                                      AffiliationID source, AffiliationID target)
{
    PathWithDist pathWithDist;
    AffiliationID current = target;

    while (current != source)
    {
        if (parent.find(current) == parent.end())
        {
            return {}; // No path exists
        }
        AffiliationID prev = parent.at(current);
        Weight weight = _graph[prev].neighbors[current].first;
        Distance dist = _graph[prev].neighbors[current].second;
        pathWithDist.push_back({{prev, current, weight}, dist});
        current = prev;
    }

    std::reverse(pathWithDist.begin(), pathWithDist.end());
    return pathWithDist;
}

PathWithDist Datastructures::get_shortest_path(AffiliationID source, AffiliationID target)
{
    if (!(_connectedAffs.empty() && _addedAffs.empty()))
    {
        update_graph();
    }

    if (!(_distChangedAffs.empty()))
    {
        update_dist();
    }

    using P = std::pair<int, AffiliationID>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
    std::unordered_map<AffiliationID, int> distance;
    std::unordered_map<AffiliationID, AffiliationID> parent;

    // Initialization
    pq.push(std::make_pair(0, source));
    distance[source] = 0;
    for (const auto &pair : _graph)
    {
        AffiliationID node = pair.first;
        if (node != source)
        {
            distance[node] = std::numeric_limits<int>::max();
        }
    }

    while (!pq.empty())
    {
        P top_pair = pq.top();
        pq.pop();

        int current_dist = top_pair.first;
        AffiliationID current_node = top_pair.second;

        if (current_node == target)
        {
            // Reconstruct and return the path
            return reconstruct_pathWithDist(parent, source, target);
        }

        for (const auto &pair : _graph[current_node].neighbors)
        {
            AffiliationID neighbor = pair.first;
            Distance dist = pair.second.second;

            Distance new_dist = current_dist + dist;

            if (new_dist < distance[neighbor])
            {
                distance[neighbor] = new_dist;
                parent[neighbor] = current_node;
                pq.push(std::make_pair(new_dist, neighbor));
            }
        }
    }

    // No path found
    return {};
}
