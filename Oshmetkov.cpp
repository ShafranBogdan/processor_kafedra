#include "Entity.h"
#include "Oshmetkov.h"

#include <algorithm>
#include <unordered_map>
#include <iostream>

template<typename T>
void additionToVector (std::vector<T>& mainVector, const std::vector<T>& addition) {
    mainVector.insert(mainVector.end(), addition.begin(), addition.end());
}

double crossProduct (const Point& A, const Point& B, const Point& P) {
    return (B.x - A.x) * (P.y - A.y) - (B.y - A.y) * (P.x - A.x);
}


void erasecCollinearPoints (AbstractPolygon* polygon) {
	for (int i = 0; i < (*polygon).get_points().size(); i++) {
		int size = (*polygon).get_points().size();
		if (!crossProduct((*polygon)[(i-1+size) % size], (*polygon)[i], (*polygon)[(i+1) % size])) {
			(*polygon).remove(i);
			i--;
		}
	}
}


namespace FunctionalForSplit {

double straightLine (const Point& A, const Point& B, double y) {
	return (B.x - A.x)/(B.y - A.y) * y + (B.y*A.x - A.y*B.x)/(B.y - A.y);
}

void setTwoEdges (int& leftBottom, int& leftTop, int& rightBottom, int& rightTop, 
				  int lBottom, int lTop, int rBottom, int rTop) {
	leftBottom = lBottom;
	leftTop = lTop;
	rightBottom = rBottom;
	rightTop = rTop;
}

void findTwoEdges (double yMin, int indexMin, int& leftBottom, int& leftTop, int& rightBottom, 
				   int& rightTop, const AbstractPolygon* polygon) {
	int size = (*polygon).get_points().size(); 
	indexMin += size;

	if ((*polygon)[(indexMin-1) % size].y == yMin) {
		indexMin--;
	}
	int bottom = indexMin % size;
	int next = (indexMin+1) % size;
	int doubleNext = (indexMin+2) % size;
	int prev = (indexMin-1) % size;

	if ((*polygon)[next].y == yMin) {
		if ( (*polygon)[doubleNext].x > (*polygon)[prev].x ||
		     (  (*polygon)[doubleNext].x == (*polygon)[prev].x &&
		        (*polygon)[next].x > (*polygon)[bottom].x  ) ) {
			setTwoEdges(leftBottom, leftTop, rightBottom, rightTop, bottom, prev, next, doubleNext);
			return;
		}
		setTwoEdges(leftBottom, leftTop, rightBottom, rightTop, next, doubleNext, bottom, prev);
		return;
	}
	if (crossProduct((*polygon)[prev], (*polygon)[bottom], (*polygon)[next]) > 0) {
		setTwoEdges(leftBottom, leftTop, rightBottom, rightTop, 
					bottom, prev, bottom, next);
		return;
	}
	setTwoEdges(leftBottom, leftTop, rightBottom, rightTop, 
				bottom, next, bottom, prev);
}

void findBottomAndTop (double& yMin, double& yMax, int& indexMin, const AbstractPolygon* polygon) {
	yMin = (*polygon)[0].y;
	yMax = (*polygon)[0].y;
	indexMin = 0;

	for (int i = 1; i < (*polygon).get_points().size(); i++) {
		yMax = std::max(yMax, (*polygon)[i].y);
		if (yMin > (*polygon)[i].y) {
			yMin = (*polygon)[i].y;
			indexMin = i;
		}
	}
}

void updateTradepoid (Trapezoid& trapezoid0, double y0, double yNew, const int& leftBottom, 
					  const int& leftTop, const int& rightBottom, const int& rightTop, 
					  const AbstractPolygon* polygon) {
	trapezoid0.x1_bottom = trapezoid0.x1_top;
	trapezoid0.x2_bottom = trapezoid0.x2_top;
	trapezoid0.y_bottom = y0;
	trapezoid0.y_top = yNew;
	trapezoid0.x1_top = straightLine((*polygon)[leftBottom], (*polygon)[leftTop], yNew);
	trapezoid0.x2_top = straightLine((*polygon)[rightBottom], (*polygon)[rightTop], yNew);
}

void updatePairOfVertex (double x, double y, int& vertexBottom, int& vertexTop,
						 const AbstractPolygon* polygon) {
	if (x == (*polygon)[vertexTop].x && y == (*polygon)[vertexTop].y) {
		vertexBottom = vertexTop;
		int size = (*polygon).get_points().size();
		int next = (vertexTop+1) % size;
		int prev = (vertexTop-1+size) % size;

		vertexTop = ( (*polygon)[prev].y > (*polygon)[vertexTop].y ) ? prev : next;
	}
}

std::vector<Trapezoid> splitConvexPolygon (const AbstractPolygon* polygon) {
	std::vector<Trapezoid> trapezoids;

	double y0; // start y0 == yMin
	double yNew, yMax;
	int indexMin;
	int leftBottom, leftTop, rightBottom, rightTop;

	findBottomAndTop(y0, yMax, indexMin, polygon);
	findTwoEdges(y0, indexMin, leftBottom, leftTop, rightBottom, rightTop, polygon);

	Trapezoid trapezoid0{(*polygon)[leftBottom].x, (*polygon)[rightBottom].x, -1, -1, y0, -1};
	while (y0 < yMax) {

		yNew = ( (*polygon)[leftTop].y < (*polygon)[rightTop].y ) ? 
				 (*polygon)[leftTop].y : (*polygon)[rightTop].y;

		updateTradepoid(trapezoid0, y0, yNew, leftBottom, leftTop, rightBottom, rightTop, polygon);

		trapezoids.push_back( trapezoid0 );

		y0 = yNew;

		updatePairOfVertex(trapezoid0.x1_top, y0, leftBottom, leftTop, polygon);
		updatePairOfVertex(trapezoid0.x2_top, y0, rightBottom, rightTop, polygon);
	}

	return trapezoids;
}

double polygonArea(const AbstractPolygon* polygon) {
    double area = 0.0;
    int size = (*polygon).get_points().size();
    for (int i = 0; i < size; ++i) {
        Point p1 = (*polygon)[i];
        Point p2 = (*polygon)[(i + 1) % size];
        area += (p1.x * p2.y - p2.x * p1.y);
    }
    return area / 2.0;
}

bool isPointInTriangle (const Point& A, const Point& B, const Point& C, const Point& P) {
    double cross1 = crossProduct(A, B, P);
    double cross2 = crossProduct(B, C, P);
    double cross3 = crossProduct(C, A, P);

    return (cross1 > 0 && cross2 > 0 && cross3 > 0) || 
           (cross1 < 0 && cross2 < 0 && cross3 < 0);
}

bool isConcaveVertex (const AbstractPolygon* polygon, int index, bool isClockwise) {
    int size = (*polygon).get_points().size();

    Point prevPoint = (*polygon)[(index + size - 1) % size];
    Point currentPoint = (*polygon)[index];
    Point nextPoint = (*polygon)[(index + 1) % size];

    double cross = crossProduct(prevPoint, currentPoint, nextPoint);

    return ( isClockwise ) ? cross > 0 : cross < 0;
}

std::vector<int> findConcaveVertexIndexes (const AbstractPolygon* polygon) {
	std::vector<int> ConcaveVertex;
	bool isClockwise = polygonArea(polygon) < 0;
	for (int index = 0; index < (*polygon).get_points().size(); index++) {
		if (isConcaveVertex(polygon, index, isClockwise)) {
			ConcaveVertex.push_back(index);
		}
	}
	return ConcaveVertex;
}

bool isFullTriangle (int i, const std::vector<Point>& smoothPolygonVec) {
	int size = smoothPolygonVec.size();
	for (int j = 0; j < smoothPolygonVec.size(); j++) {
		if (j == i-1 || j == i || j == i+1) {
			continue;
		}
		if ( isPointInTriangle(smoothPolygonVec[(i-1+size) % size], smoothPolygonVec[i],
						  smoothPolygonVec[(i+1) % size], smoothPolygonVec[j]) ) {
			return true;
		}

	}
	return false;
}

void addPosibleConcaveVertex (int posibleConcaveIndex, std::vector<int>& ConcaveVertex, 
							  const std::vector<Point>& smoothPolygonVec, bool isClockwise) {
	Polygon smoothPolygon{smoothPolygonVec};
	if (find(ConcaveVertex.begin(), ConcaveVertex.end(), posibleConcaveIndex) == ConcaveVertex.end() && 
		isConcaveVertex(&smoothPolygon, posibleConcaveIndex, isClockwise)) {
		ConcaveVertex.push_back(posibleConcaveIndex);
	}
}

void updateConcaveVertex (int concaveIndex, std::vector<int>& ConcaveVertex) {
	for (int k = 0; k < ConcaveVertex.size(); k++) {
		if (ConcaveVertex[k] > concaveIndex) {
			ConcaveVertex[k]--;
		}
		if (ConcaveVertex[k] == concaveIndex) {
			ConcaveVertex.erase( ConcaveVertex.begin() + k );
			k--;
		}
	}
}

std::vector<Trapezoid> splitConcavePolygon (const AbstractPolygon* polygon) {
	std::vector<Trapezoid> triangles;
	std::vector<Point> smoothPolygonVec = (*polygon).get_points();
	std::vector<int> ConcaveVertex = findConcaveVertexIndexes(polygon);
	bool isClockwise = polygonArea(polygon) < 0;
	int size = smoothPolygonVec.size();

	while (true) {
		if (!ConcaveVertex.size()) {
			break;
		}
		int concaveIndex = -1;
		for (int i : ConcaveVertex) {
			if ( !isFullTriangle(i, smoothPolygonVec) ) {
				Polygon triangle{ { smoothPolygonVec[(i-1+size) % size], smoothPolygonVec[i], 
									smoothPolygonVec[(i+1) % size] } };
				smoothPolygonVec.erase( smoothPolygonVec.begin() + i );
				size--;
				additionToVector( triangles, splitConvexPolygon(&triangle) );
				concaveIndex = i;
				break;
			}
		}
		updateConcaveVertex(concaveIndex, ConcaveVertex);
		addPosibleConcaveVertex((concaveIndex-1+size) % size, ConcaveVertex, 
								 smoothPolygonVec, isClockwise);
		addPosibleConcaveVertex(concaveIndex, ConcaveVertex, smoothPolygonVec, isClockwise);
	}
	Polygon smoothPolygon{ smoothPolygonVec };
	erasecCollinearPoints(&smoothPolygon);
	std::vector<Trapezoid> smoothPolygonTrapezoids = splitConvexPolygon(&smoothPolygon);

	return TrapezoidOperations::subtract(smoothPolygonTrapezoids, triangles);
}

bool isConcavePolygon (const AbstractPolygon* polygon) {
	int size = (*polygon).get_points().size();
	bool isClockwise = polygonArea(polygon) < 0;
	for (int k = 0; k < size; k++) {
		if (isConcaveVertex(polygon, k, isClockwise)) {
			return true;
		}
	}
	return false;
}

std::vector<Trapezoid> splitPolygonIntoTrapezoids (const Polygon& polygon){
	std::vector<Trapezoid> trapezoids = (isConcavePolygon(&polygon)) ? splitConcavePolygon(&polygon)
														   			: splitConvexPolygon(&polygon);
	std::vector<Trapezoid> holes;

	for (const Hole& hole : polygon.get_holes()) {
		std::vector<Trapezoid> holeTrapezoids = (isConcavePolygon(&hole)) ? splitConcavePolygon(&hole)
														   				 : splitConvexPolygon(&hole);
		additionToVector( holes, holeTrapezoids );
	}

	return TrapezoidOperations::subtract(trapezoids, holes);
}

};


std::vector<Trapezoid> PolygonOperations::splitPolygonIntoTrapezoids (const Polygon& polygon) {
	return FunctionalForSplit::splitPolygonIntoTrapezoids(polygon);
}


////////////////////////////////////////////////////////////////////////////////////////


namespace FunctionalForReconnection {

bool areCollinear (const Point& A, const Point& B, const Point& P) {
    return crossProduct(A, B, P) == 0;
}

bool onInterval (const Point& p, const Point& q, const Point& r) {
    return std::min(p.x, r.x) <= q.x && q.x <= std::max(p.x, r.x) &&
           std::min(p.y, r.y) <= q.y && q.y <= std::max(p.y, r.y) && !(p==q) && !(r==q);
}

bool areSimilar (const Point& A, const Point& B, const Point& C, const Point& D) {
	return (A==C && B==D) || (A==D && B==C);
}

bool IntervalsOverlap (const Point& A, const Point& B, const Point& C, const Point& D) {
	if (areSimilar(A, B, C, D)) return true;
    if (areCollinear(A, B, C) && areCollinear(A, B, D)) {
        return onInterval(A, C, B) || onInterval(A, D, B) || onInterval(C, A, D) || onInterval(C, B, D);
    }
    return false;
}

bool areAdjacent(const Trapezoid& t1, const Trapezoid& t2) {

	if (IntervalsOverlap(Point{t1.x1_bottom, t1.y_bottom}, Point{t1.x2_bottom, t1.y_bottom},
					 	 Point{t2.x1_top, t2.y_top}, Point{t2.x2_top, t2.y_top}) ||

		IntervalsOverlap(Point{t1.x1_top, t1.y_top}, Point{t1.x2_top, t1.y_top},
					 	 Point{t2.x1_bottom, t2.y_bottom}, Point{t2.x2_bottom, t2.y_bottom}) ||

		IntervalsOverlap(Point{t1.x2_bottom, t1.y_bottom}, Point{t1.x2_top, t1.y_top},
					 Point{t2.x1_bottom, t2.y_bottom}, Point{t2.x1_top, t2.y_top}) ||

		IntervalsOverlap(Point{t1.x1_bottom, t1.y_bottom}, Point{t1.x1_top, t1.y_top},
					 Point{t2.x2_bottom, t2.y_bottom}, Point{t2.x2_top, t2.y_top})
	   ) {
		return true;
	}
    return false;
}

std::unordered_map<int, std::vector<int>> createEdgeList (const std::vector<Trapezoid>& trapezoids) {
	std::unordered_map<int, std::vector<int>> edgeList;
	std::vector<int> neighbors;
	for (int i = 0; i < trapezoids.size(); i++){
		edgeList[i] = neighbors;
	}
    for (int i = 0; i < trapezoids.size(); i++) {
        for (int j = i + 1; j < trapezoids.size(); j++) {
            if (areAdjacent(trapezoids[i], trapezoids[j])) {
                edgeList[i].push_back(j);
                edgeList[j].push_back(i);
            }
        }
    }
    return edgeList;
}

void findComponent (const std::vector<Trapezoid>& trapezoids, const std::unordered_map<int, std::vector<int>>& edgeList,
		  int vertex, std::vector<bool>& marked, std::vector<Trapezoid>& component) {

	if (marked[vertex]) return;
	marked[vertex] = true;
	component.push_back(trapezoids[vertex]);

	for (int neighbor : edgeList.at(vertex)) {
		findComponent (trapezoids, edgeList, neighbor, marked, component);
	}
}

std::vector<std::vector<Trapezoid>> findConnectedComponents (const std::vector<Trapezoid>& trapezoids) {
    std::vector<std::vector<Trapezoid>> components;
    std::unordered_map<int, std::vector<int>> edgeList = createEdgeList(trapezoids); 
    std::vector<bool> marked(trapezoids.size(), false);


    for (int vertex = 0; vertex < trapezoids.size(); vertex++) {
    	std::vector<Trapezoid> component;
    	findComponent(trapezoids, edgeList, vertex, marked, component);
    	if (component.size() > 0) {
    		components.push_back(component);
    	}
    }
    return components;
}

Polygon createPolygonFromTrapezoid(const Trapezoid& tr) {
	Polygon poly({Point{tr.x1_bottom, tr.y_bottom}, Point{tr.x1_top, tr.y_top},
				  Point{tr.x2_top, tr.y_top}, Point{tr.x2_bottom, tr.y_bottom}});
	erasecCollinearPoints(&poly);
	return poly;
}

struct Node {
	Polygon polygon;
	std::vector<Node*> neighbors;
	int marked = 0;
	static int currMarked;

	Node (Polygon poly) : polygon{poly} {}

	void addNeighbor (Node* neighbor) {
		for (Node* node : neighbors) {
			if (node == neighbor) {
				return;
			}
		}
		neighbors.push_back(neighbor);
	}
	void eraseNeighbor (Node* neighbor) {
		auto iterator = std::find(neighbors.begin(), neighbors.end(), neighbor);
		if (iterator != neighbors.end()) {
			neighbors.erase(iterator);
		}
	}
};

int Node::currMarked = 0;

Node* createGraph (const std::vector<Trapezoid>& component) {
	std::vector<Node*> polygons;

	for (const Trapezoid& tr : component) {
		Node* node = new Node(createPolygonFromTrapezoid(tr));
		polygons.push_back(node);
	}
	std::unordered_map<int, std::vector<int>> edgeList = createEdgeList(component);

	for (int k = 0; k < component.size(); k++) {
		for (int neighbor : edgeList[k]) {
			polygons[k]->addNeighbor(polygons[neighbor]);
		}		
	}
	return polygons[0];
}

std::pair<int, int> findInsertIndexes (AbstractPolygon* mainPolygon, AbstractPolygon* leaf) {
	std::pair<int, int> insertIndexes(-1, -1);
	int sizeMain = mainPolygon->get_points().size();
	int sizeLeaf = leaf->get_points().size();

	for (int i = 0; i < sizeMain; i++) {
		for (int j = 0; j < sizeLeaf; j++) {
			if (IntervalsOverlap( (*mainPolygon)[i], (*mainPolygon)[(i+1) % sizeMain],
								  (*leaf)[j], (*leaf)[(j+1) % sizeLeaf])) {
				insertIndexes.first = i;
				insertIndexes.second = (j + 1) % sizeLeaf;
				return insertIndexes;
			}
		}
	}
	return insertIndexes;
}

void updateNodes (Node*& root, Node* mainNode, Node* leaf) {
	for (Node* neighbor : leaf->neighbors) {
		if (neighbor == mainNode ) {
			continue;
		}
		neighbor->eraseNeighbor(leaf);
		neighbor->addNeighbor(mainNode);
	}
	if (root == leaf) {
		root = root->neighbors[0];
	}
	delete leaf;
}

void unionPolygons (Node*& root, Node* mainNode, Node* leaf) {
	std::pair<int, int> insertIndexes = findInsertIndexes(&(mainNode->polygon), &(leaf->polygon));
	int sizeLeaf = leaf->polygon.get_points().size();
	for (int k = 0; k < sizeLeaf; k++) {
		mainNode->polygon.insert( leaf->polygon[(insertIndexes.second + k) % sizeLeaf], 
								  insertIndexes.first + k + 1 );
	}
	erasecCollinearPoints(&(mainNode->polygon));
	mainNode->eraseNeighbor(leaf);

	updateNodes(root, mainNode, leaf);
}

void findThreeCycle (Node* root, std::vector<Node*>& threeCycle) {
	if (threeCycle[2] != nullptr) return;

	if (threeCycle[1] != nullptr) {
		for (Node* neighbor : root->neighbors) {
			if (neighbor == threeCycle[0]) {
				threeCycle[2] = root;
				return;
			}
		}
		return;
	}
	if (threeCycle[0] != nullptr) {
		threeCycle[1] = root;
		for (Node* neighbor : root->neighbors) {
			if (neighbor != threeCycle[0]) {
				findThreeCycle(neighbor, threeCycle);
				if (threeCycle[2] != nullptr) {
					return;
				}
			}
		}
		threeCycle[1] = nullptr;
		return;
	}

	root->marked = Node::currMarked;
	threeCycle[0] = root;

	for (Node* neighbor : root->neighbors){
		findThreeCycle(neighbor, threeCycle);
		if (threeCycle[2] != nullptr) {
			return;
		}
	}
	threeCycle[0] = nullptr;
	for (Node* neighbor : root->neighbors) {
		if (neighbor->marked != Node::currMarked) {
			findThreeCycle(neighbor, threeCycle);
		}
	}
}

void threeCycleProcess (Node*& root) {
	std::vector<Node*> threeCycle = {nullptr, nullptr, nullptr};
	Node::currMarked++;
	findThreeCycle(root, threeCycle);
	while (threeCycle[2] != nullptr) {
		unionPolygons(root, threeCycle[0], threeCycle[1]);
		unionPolygons(root, threeCycle[0], threeCycle[2]);

		threeCycle = {nullptr, nullptr, nullptr};
		Node::currMarked++;
		findThreeCycle(root, threeCycle);
	}
}

void findLeaf(Node* root, Node*& leaf) {
	if (leaf != nullptr) return;

	root->marked = Node::currMarked;
	if (root->neighbors.size() == 1) {
		leaf = root;
		return;
	}
	for (Node* neighbor : root->neighbors) {
		if (neighbor->marked != Node::currMarked) {
			findLeaf(neighbor, leaf);
		}
	}
}

void leafProcess (Node*& root) {
	Node* leaf  = nullptr;
	Node::currMarked++;
	findLeaf(root, leaf);

	while (leaf != nullptr) {
		Node* mainNode = leaf->neighbors[0];
		unionPolygons(root, mainNode, leaf);

		leaf = nullptr;
		Node::currMarked++;
		findLeaf(root, leaf);
	}
}

void dfsNodesToPolygons (Node* root, std::vector<Polygon>& polygons) {
	if (root->marked == Node::currMarked) {
		return;
	}
	root->marked = Node::currMarked;
	polygons.push_back(root->polygon);

	for (Node* neighbor : root->neighbors) {
		dfsNodesToPolygons(neighbor, polygons);
	}
	delete root;
}

std::vector<Polygon> mergeTrapezoidsToPolygon (const std::vector<Trapezoid>& component) {
	Node* root = createGraph(component);
	std::vector<Polygon> polygons;

	threeCycleProcess(root);
	leafProcess(root);

	Node::currMarked++;
	dfsNodesToPolygons(root, polygons);

	return polygons;
}

std::vector<Polygon> reconnection (std::vector<Trapezoid>& trapezoids) {
    std::vector<Polygon> polygons;
    auto components = findConnectedComponents(trapezoids);

    for (const auto& component : components) {
    	std::vector<Polygon> polygonsInComponent = mergeTrapezoidsToPolygon(component);
    	for (Polygon& poly: polygonsInComponent) {
    		polygons.push_back(poly);
    	}
    }
    return polygons;
}

};


std::vector<Polygon> PolygonOperations::reconnection (std::vector<Trapezoid>& trapezoids) {
	return FunctionalForReconnection::reconnection(trapezoids);
}


/////////////////////////////////////////////////////////////////////////


std::vector<Trapezoid> splitLayerIntoTrapezoids (const std::vector<Polygon>& polygons) {
	std::vector<Trapezoid> layer;
	for (const Polygon& polygon : polygons) {
		additionToVector( layer, PolygonOperations::splitPolygonIntoTrapezoids(polygon) );
	}
	return layer;
}

std::vector<Polygon> PolygonOperations::processPolygons (const std::vector<Polygon>& polygons1, 
										 				 const std::vector<Polygon>& polygons2, 
										 				 OperationType operation) {

	std::vector<Trapezoid> layer1 = splitLayerIntoTrapezoids(polygons1);
	// std::cout << "size layer1 " << layer1.size() << "\n";
	// for (auto trap : layer1) {
	// 	std::cout << trap.x1_bottom << " " << trap.x2_bottom << " " << trap.y_bottom << "\n";
	// 	std::cout << trap.x1_top << " " << trap.x2_top << " " << trap.y_top <<  "\n";
	// }
	std::vector<Trapezoid> layer2 = splitLayerIntoTrapezoids(polygons2);
	// std::cout << "size layer2 " << layer2.size() << "\n";
	// for (auto trap : layer2) {
	// 	std::cout << trap.x1_bottom << " " << trap.x2_bottom << " " << trap.y_bottom << "\n";
	// 	std::cout << trap.x1_top << " " << trap.x2_top << " " << trap.y_top <<  "\n";
	// }
	std::vector<Trapezoid> newLayer;

	switch (operation)
	{
	case OperationType::UNION:
		newLayer = TrapezoidOperations::unite(layer1, layer2);
		// std::cout << "size after op " << newLayer.size() << "\n";
		// for (auto trap : newLayer) {
		// 	std::cout << trap.x1_bottom << " " << trap.x2_bottom << " " << trap.y_bottom << "\n";
		// 	std::cout << trap.x1_top << " " << trap.x2_top << " " << trap.y_top <<  "\n";
		// }
		break;
	case OperationType::INTERSECTION:
		newLayer = TrapezoidOperations::intersect(layer1, layer2);
		break;
	case OperationType::SUBTRACTION:
		newLayer = TrapezoidOperations::subtract(layer1, layer2);
		break;
	}
	return PolygonOperations::reconnection(newLayer);
}