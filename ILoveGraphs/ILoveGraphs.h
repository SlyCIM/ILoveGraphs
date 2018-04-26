//#pragma onces
//
//
//#include <string>
//#include <vector>
//#include <map>
//#include <queue>
//#include <functional>
//#include <fstream>
//#include <sstream>
//#include <algorithm>
//using namespace std;
//
//class Graph;
//class AdjMatrixGraphRepresentation;
//class EdgeListGraphRepresentation;
//class AdjListGraphRepresentation;
/////typedef
//typedef map<int, int>* Vertexes;
//typedef vector<vector<int>*>* AdjacencyMatrix;
//typedef vector<map<int, bool>*>* BridgesList;
//typedef vector<map<int, int>*>* AdjacencyList;
//typedef map<pair<int, int>, int>* EdgeList;
///// //typedef
//class StringParser {
//public:
//	static vector<string> split(const string& str, char ch) {
//		istringstream stream(str);
//		vector<string> res;
//		string tok;
//		while (getline(stream, tok, ch))
//			res.push_back(tok);
//		return res;
//	}
//};
//class DSU {
//private:
//	vector<int>* parent;
//	vector<int>* size;
//public:
//	DSU() {	}
//	DSU(int n) {
//		size = new vector<int>(n);
//		parent = new vector<int>(n);
//	}
//	~DSU() {
//		delete parent;
//		delete size;
//	}
//	void makeSet(int v) {
//		(*parent)[v] = v;
//		(*size)[v] = 1;
//	}
//	int find(int x) {
//		if ((*parent)[x] == x)
//			return x;
//		int Root = find((*parent)[x]);
//		(*parent)[x] = Root;
//		return Root;
//	}
//	void unite(int x, int y) {
//		int yRoot = find(y);
//		int xRoot = find(x);
//
//		if (xRoot != yRoot) {
//			if ((*size)[xRoot] >= (*size)[yRoot]) {
//				(*size)[xRoot] += (*size)[yRoot];
//				(*parent)[yRoot] = xRoot;
//			}
//			else {
//				(*size)[yRoot] += (*size)[xRoot];
//				(*parent)[xRoot] = yRoot;
//			}
//		}
//	}
//	map<int, int> getRoots() {
//		map<int, int> root = map<int, int>();
//		for (int i = 0; i < parent->size(); ++i)
//			if (i == (*parent)[i])
//				root[i] = (*size)[i];
//		return root;
//	}
//};
//class GraphRepresentation {
//protected:
//	bool isOriented, isWeighted;
//	Vertexes vertexDegrees = nullptr;
//	virtual DSU* buildDSU() = 0;
//
//public:
//	int edgesAmount = 0;
//	GraphRepresentation() = default;
//	virtual ~GraphRepresentation() = default;
//
//	virtual void readGraph(istream& stream, vector<string> parameters) = 0;
//	virtual void addEdge(int from, int to, int weight) = 0;
//	virtual int changeEdge(int from, int to, int newWeight) = 0;
//	virtual void removeEdge(int from, int to) = 0;
//
//	virtual AdjMatrixGraphRepresentation* transformToAdjMatrix() = 0; //Матрица смежности
//	virtual AdjListGraphRepresentation* transformToAdjList() = 0;     //Список смежности
//	virtual EdgeListGraphRepresentation* transformToListOfEdges() = 0;//Список ребер
//
//	virtual void writeGraph(string fileName) = 0;
//	virtual bool isAdjMatrixGraph() = 0;
//	virtual bool isAdjListGraph() = 0;
//	virtual bool isEdgeListGraph() = 0;
//	int getBeginVertex(bool& circleExists) {
//		int oddVertex = -1;
//		int evenVertexesAmount = 0;
//		for (auto it = vertexDegrees->begin(); it != vertexDegrees->end(); ++it) {
//			if (it->second % 2 == 0)
//				++evenVertexesAmount;
//			else
//				oddVertex = it->first;
//		}
//		circleExists = evenVertexesAmount == vertexDegrees->size();
//		if (circleExists)
//			return 0;
//		if (vertexDegrees->size() - evenVertexesAmount <= 2)
//			return oddVertex;
//		return -1;
//	}
//	bool connectedComponentsCheck() {
//		DSU* dsu = buildDSU();
//		map<int, int> roots = dsu->getRoots();
//		if (roots.size() <= 1)
//			return true;
//		int nonEmptyComponentsAmount = 0;
//		for (auto it = roots.begin(); it != roots.end(); ++it)
//			if (it->second > 1)
//				nonEmptyComponentsAmount++;
//		return nonEmptyComponentsAmount <= 1;
//	}
//	virtual int calc() = 0;
//};
//class AdjMatrixGraphRepresentation : GraphRepresentation {
//	AdjacencyMatrix adjacencyMatrix = nullptr;
//	AdjacencyMatrix readMatrix(istream& stream, int vertexAmount) {
//		vertexDegrees = new map<int, int>();
//		const AdjacencyMatrix matrix = new vector<vector<int>*>(vertexAmount);
//		for (size_t i = 0; i < vertexAmount; ++i) {
//			(*vertexDegrees)[i] = 0;
//			(*matrix)[i] = new vector<int>(vertexAmount);
//			string str;
//			getline(stream, str);
//			vector<string> tokens = StringParser::split(str, ' ');
//			for (size_t j = 0; j < vertexAmount; ++j) {
//				int weight = stoi(tokens[j]);//Извлекаем int из j-й строки
//				(*(*matrix)[i])[j] = weight;
//				if (weight > 0) {
//					++(*vertexDegrees)[i];
//					++edgesAmount;
//				}
//			}
//		}
//		return matrix;
//	}
//	void copy(const AdjMatrixGraphRepresentation& graph) {
//		this->isWeighted = graph.isWeighted; //Быстренько все определяем
//		this->isOriented = graph.isOriented;
//		this->edgesAmount = graph.edgesAmount;
//		this->vertexDegrees = new map<int, int>(*graph.vertexDegrees);
//		this->adjacencyMatrix = new vector<vector<int>*>(graph.adjacencyMatrix->size());
//		for (size_t i = 0; i<adjacencyMatrix->size(); ++i) //Копируем
//			(*adjacencyMatrix)[i] = new vector<int>(*(*graph.adjacencyMatrix)[i]);
//	}
//	static void writeMatrix(ostream& stream, AdjacencyMatrix matrix) {
//		for (size_t i = 0; i<matrix->size(); ++i) {
//			for (size_t j = 0; j<matrix->size(); ++j) {
//				stream << (*(*matrix)[i])[j];
//				if (j < matrix->size() - 1)
//					stream << " ";
//			}
//			if (i < matrix->size() - 1)
//				stream << endl;
//		}
//	}
//	DSU* buildDSU() {
//		DSU* dsu = new DSU(adjacencyMatrix->size());
//		for (int i = 0; i<adjacencyMatrix->size(); ++i)
//			dsu->makeSet(i);
//		for (int i = 0; i<adjacencyMatrix->size(); ++i)
//			for (int j = 0; j<adjacencyMatrix->size(); ++j)
//				dsu->unite(i, j);
//		return dsu;
//	}
//
//public:
//	AdjMatrixGraphRepresentation() = default;
//	AdjMatrixGraphRepresentation(int vertexAmount, int edgesAmount, bool isOriented, bool isWeighted)
//	{
//		this->vertexDegrees = new map<int, int>();
//		this->adjacencyMatrix = new vector<vector<int>*>(vertexAmount);
//		for (int i = 0; i < vertexAmount; ++i)
//			(*adjacencyMatrix)[i] = new vector<int>(vertexAmount, 0);
//		this->isOriented = isOriented;
//		this->isWeighted = isWeighted;
//		this->edgesAmount = edgesAmount;
//	}
//	AdjMatrixGraphRepresentation(const AdjMatrixGraphRepresentation& graph) {
//		copy(graph);
//	}
//	~AdjMatrixGraphRepresentation() {
//		delete vertexDegrees;
//		for (int i = 0; i < adjacencyMatrix->size(); ++i)
//			delete (*adjacencyMatrix)[i];
//		delete adjacencyMatrix;
//	};
//	AdjMatrixGraphRepresentation& operator=(const AdjMatrixGraphRepresentation& graph) { //Переопределяем =
//		copy(graph);
//		return *this;
//	}
//
//	bool isAdjMatrixGraph() override { return true; }
//	bool isAdjListGraph() override { return false; }
//	bool isEdgeListGraph() override { return false; }
//
//	void readGraph(istream& stream, vector<string> parameters) override
//	{
//		const int vertexAmount = stoi(parameters[1]);
//		isOriented = parameters[2] == "1";
//		isWeighted = parameters[3] == "1";
//		adjacencyMatrix = readMatrix(stream, vertexAmount);
//	}
//	void addEdge(int from, int to, int weight) override {
//		++edgesAmount;
//		++(*vertexDegrees)[from];
//		(*(*adjacencyMatrix)[from])[to] = weight;
//		if (!isOriented) {
//			++(*vertexDegrees)[to];
//			(*(*adjacencyMatrix)[to])[from] = weight;
//		}
//	}
//	int changeEdge(int from, int to, int newWeight)  override {
//		const int oldWeight = (*(*adjacencyMatrix)[from])[to];
//		addEdge(from, to, newWeight);
//		return oldWeight;
//	}
//	void removeEdge(int from, int to)  override {
//		--edgesAmount;
//		--(*vertexDegrees)[from];
//		(*(*adjacencyMatrix)[from])[to] = 0;
//		if (!isOriented) {
//			--(*vertexDegrees)[to];
//			(*(*adjacencyMatrix)[to])[from] = 0;
//		}
//	}
//	AdjMatrixGraphRepresentation* transformToAdjMatrix()  override { return this; }
//	AdjListGraphRepresentation* transformToAdjList()  override;
//	EdgeListGraphRepresentation* transformToListOfEdges()  override;
//	void writeGraph(string fileName) override { //
//		ofstream file(fileName);
//		file << "C " << adjacencyMatrix->size() << endl;
//		file << (isOriented ? "1 " : "0 ") << (isWeighted ? "1" : "0") << endl;
//		writeMatrix(file, adjacencyMatrix);
//		file.close();
//	}
//	int calc() {
//		return 0;
//	}
//	friend Graph;
//};
//class AdjListGraphRepresentation : GraphRepresentation {
//	AdjacencyList adjacencyList = nullptr;
//	AdjacencyList readList(istream& stream, int vertexAmount, bool isWeighted)
//	{
//		const AdjacencyList adjList = new vector<map<int, int>*>(vertexAmount);
//		vertexDegrees = new map<int, int>();
//		for (size_t i = 0; i<vertexAmount; ++i) {
//			(*vertexDegrees)[i] = 0;
//			(*adjList)[i] = new map<int, int>();
//			string str;
//			getline(stream, str);
//			vector<string> tokens = StringParser::split(str, ' ');
//			for (size_t j = 0; j < tokens.size(); ++j) {
//				int vertexId, weight = 1;
//				if (isWeighted) {
//					vertexId = stoi(tokens[j]) - 1;
//					weight = stoi(tokens[++j]);
//				}
//				else
//					vertexId = stoi(tokens[j]) - 1;
//				++edgesAmount;
//				++(*vertexDegrees)[i];
//				(*(*adjList)[i])[vertexId] = weight;
//			}
//		}
//		return adjList;
//	}
//	static void writeList(ostream& stream, AdjacencyList list, bool isWeighted) {
//		for (size_t i = 0; i < list->size(); ++i) {
//			map<int, int>* curVertexMap = (*list)[i];
//			for (auto it = curVertexMap->begin(); it != curVertexMap->end(); ++it) {
//				stream << it->first;
//				if (isWeighted)
//					stream << "," << it->second;
//				if (next(it) != curVertexMap->end())
//					stream << " ";
//			}
//			if (i < list->size() - 1)
//				stream << endl;
//		}
//	}
//	void removeEdgeSimplex(AdjacencyList adjacencyList, int from, int to) {
//		const auto it = (*(*adjacencyList)[from]).find(to);
//		(*(*adjacencyList)[from]).erase(it);
//		--(*vertexDegrees)[from];
//	}
//	void copy(const AdjListGraphRepresentation& graph) {
//		this->isOriented = graph.isOriented;//Быстренько все переопределяем
//		this->isWeighted = graph.isWeighted;
//		this->edgesAmount = graph.edgesAmount;
//		this->vertexDegrees = new map<int, int>(*graph.vertexDegrees);
//		this->adjacencyList = new vector<map<int, int>*>(graph.adjacencyList->size());
//		for (size_t i = 0; i < adjacencyList->size(); ++i) //Копируем
//			(*adjacencyList)[i] = new map<int, int>(*(*graph.adjacencyList)[i]);
//	}
//	DSU* buildDSU() {
//		DSU* dsu = new DSU(adjacencyList->size());
//		for (int i = 0; i < adjacencyList->size(); ++i)
//			dsu->makeSet(i);
//		for (int i = 0; i < adjacencyList->size(); ++i) {
//			map<int, int>* edgs = (*adjacencyList)[i];
//			for (auto it = edgs->begin(); it != edgs->end(); ++it)
//				dsu->unite(i, it->first);
//		}
//		return dsu;
//	}
//
//public:
//	AdjListGraphRepresentation() = default;
//	AdjListGraphRepresentation(int vertexAmount, int edgesAmount, bool isOriented, bool isWeighted) {
//		this->vertexDegrees = new map<int, int>();
//		this->edgesAmount = edgesAmount;
//		this->adjacencyList = new vector<map<int, int>*>(vertexAmount);
//		for (int i = 0; i<adjacencyList->size(); ++i)
//			(*adjacencyList)[i] = new map<int, int>();
//		this->isWeighted = isWeighted;
//		this->isOriented = isOriented;
//	}
//	AdjListGraphRepresentation(const AdjListGraphRepresentation& graph) {
//		copy(graph);
//	}
//	~AdjListGraphRepresentation()
//	{
//		delete vertexDegrees;
//		for (size_t i = 0; i < adjacencyList->size(); ++i)
//			delete (*adjacencyList)[i];
//		delete adjacencyList;
//	}
//	AdjListGraphRepresentation& operator=(const AdjListGraphRepresentation& graph) {
//		copy(graph);
//		return *this;
//	}
//
//	bool isAdjMatrixGraph() override { return false; }
//	bool isAdjListGraph() override { return true; }
//	bool isEdgeListGraph() override { return false; }
//	void readGraph(istream& stream, vector<string> parameters) override {
//		const int vertexAmount = stoi(parameters[1]);
//		isOriented = parameters[2] == "1";
//		isWeighted = parameters[3] == "1";
//
//		adjacencyList = readList(stream, vertexAmount, isWeighted);
//	}
//
//	void addEdge(int from, int to, int weight) override
//	{
//		++edgesAmount;
//		++(*vertexDegrees)[from];
//		(*(*adjacencyList)[from])[to] = weight;
//		if (!isOriented) {
//			++(*vertexDegrees)[to];
//			(*(*adjacencyList)[to])[from] = weight;
//		}
//	}
//	int changeEdge(int from, int to, int newWeight)  override
//	{
//		const int oldWeight = (*(*adjacencyList)[from])[to];
//		addEdge(from, to, newWeight);
//		return oldWeight;
//	}
//	void removeEdge(int from, int to)  override
//	{
//		--edgesAmount;
//		removeEdgeSimplex(adjacencyList, from, to);
//		if (!isOriented)
//			removeEdgeSimplex(adjacencyList, to, from);
//	}
//
//	AdjMatrixGraphRepresentation* transformToAdjMatrix()  override;
//	AdjListGraphRepresentation* transformToAdjList()  override { return this; }
//	EdgeListGraphRepresentation* transformToListOfEdges()  override;
//
//	void writeGraph(string fileName) override {
//		ofstream file(fileName);
//		file << "L " << adjacencyList->size() << endl;
//		file << (isOriented ? "1 " : "0 ") << (isWeighted ? "1" : "0") << endl;
//		writeList(file, adjacencyList, isWeighted);
//		file.close();
//	}
//	int calc() {
//		return 0;
//	}
//	AdjacencyList copyListWithDuplicates() {
//		AdjacencyList adjList = new vector<map<int, int>*>(adjacencyList->size());
//		for (size_t i = 0; i < adjacencyList->size(); ++i)
//			(*adjList)[i] = new map<int, int>();
//		for (size_t i = 0; i < adjacencyList->size(); ++i)
//			for (auto it = adjacencyList->at(i)->begin(); it != adjacencyList->at(i)->end(); ++it) {
//				(*(*adjList)[i])[it->first] = it->second;
//				(*(*adjList)[it->first])[i] = it->second;
//			}
//		return adjList;
//	}
//	friend Graph;
//};
//class EdgeListGraphRepresentation : GraphRepresentation {
//	int vertexAmount;
//	EdgeList edgeList = nullptr;
//	EdgeList readList(istream& stream, int edgeAmount) {
//		const EdgeList edgeList = new map<pair<int, int>, int>();
//		vertexDegrees = new map<int, int>();
//		for (size_t i = 0; i < vertexAmount; ++i)
//			(*vertexDegrees)[i] = 0;
//		for (size_t i = 0; i < edgeAmount; ++i) {
//			string str;
//			getline(stream, str);
//			vector<string> edgeParameters = StringParser::split(str, ' ');
//			const int weight = edgeParameters.size() > 2 ? stoi(edgeParameters[2]) : 1;
//			const int from = stoi(edgeParameters[0]) - 1;
//			const int to = stoi(edgeParameters[1]) - 1;
//			(*edgeList)[make_pair(from, to)] = weight;
//			++(*vertexDegrees)[from];
//			if (!isOriented)
//				++(*vertexDegrees)[to];
//		}
//		edgesAmount = edgeList->size();
//		return edgeList;
//	}
//	static void writeList(ostream& stream, EdgeList edgeList, bool isWeighted) {
//		for (auto it = edgeList->begin(); it != edgeList->end(); ++it) {
//			stream << it->first.first + 1 << " " << it->first.second + 1;
//			if (isWeighted)
//				stream << " " << it->second;
//			if (next(it) != edgeList->end())
//				stream << endl;
//		}
//	}
//	void copy(const EdgeListGraphRepresentation& graph) {
//		this->isWeighted = graph.isWeighted;
//		this->isOriented = graph.isOriented;
//		this->edgesAmount = graph.edgesAmount;
//		this->vertexAmount = graph.vertexAmount;
//		this->vertexDegrees = new map<int, int>(*graph.vertexDegrees);
//		this->edgeList = new map<pair<int, int>, int>(*(graph.edgeList));
//	}
//	int getEdgesAmount() {
//		return edgesAmount;
//	}
//	DSU* buildDSU() {
//		DSU* dsu = new DSU(vertexAmount);
//		for (int i = 0; i<vertexAmount; ++i)
//			dsu->makeSet(i);
//		for (auto it = edgeList->begin(); it != edgeList->end(); ++it)
//			dsu->unite(it->first.first, it->first.second);
//		return dsu;
//	}
//
//public:
//	EdgeListGraphRepresentation() = default;
//	EdgeListGraphRepresentation(bool isOriented, bool isWeighted, int vertexAmount, int edgesAmount) {
//		this->vertexDegrees = new map<int, int>();
//		this->edgeList = new map<pair<int, int>, int>();
//		this->isOriented = isOriented;
//		this->isWeighted = isWeighted;
//		this->vertexAmount = vertexAmount;
//		this->edgesAmount = edgesAmount;
//	}
//	EdgeListGraphRepresentation(const EdgeListGraphRepresentation& graph) {
//		copy(graph);
//	}
//	~EdgeListGraphRepresentation() {
//		delete vertexDegrees;
//		delete edgeList;
//	}
//	EdgeListGraphRepresentation& operator=(const EdgeListGraphRepresentation& graph) {
//		copy(graph);
//		return *this;
//	}
//	bool isAdjMatrixGraph() override { return false; }
//	bool isAdjListGraph() override { return false; }
//	bool isEdgeListGraph() override { return true; }
//	void readGraph(istream& stream, vector<string> parameters) override {
//		vertexAmount = stoi(parameters[1]);
//		int edgeAmount = stoi(parameters[2]);
//
//		isOriented = parameters[3] == "1";
//		isWeighted = parameters[4] == "1";
//		edgeList = readList(stream, edgeAmount);
//	}
//
//	void addEdge(int from, int to, int weight) override {
//		++edgesAmount;
//		(*edgeList)[make_pair(from, to)] = weight;
//		++(*vertexDegrees)[from];
//		++(*vertexDegrees)[to];
//	}
//	int changeEdge(int from, int to, int newWeight)  override {
//		const pair<int, int> edge = make_pair(from, to);
//		const int oldWeight = (*edgeList)[edge];
//		(*edgeList)[edge] = newWeight;
//		return oldWeight;
//	}
//	void removeEdge(int from, int to)  override {
//		--edgesAmount;
//		const pair<int, int> edge = make_pair(from, to);
//		const auto it = edgeList->find(edge);
//		edgeList->erase(it);
//		--(*vertexDegrees)[from];
//		--(*vertexDegrees)[to];
//	}
//
//	AdjMatrixGraphRepresentation* transformToAdjMatrix()  override;
//	AdjListGraphRepresentation* transformToAdjList()  override;
//	EdgeListGraphRepresentation* transformToListOfEdges()  override { return this; }
//
//	void writeGraph(string fileName) override {
//		ofstream file(fileName);
//		file << "E " << vertexAmount << " " << edgesAmount << endl;
//		file << (isOriented ? "1 " : "0 ") << (isWeighted ? "1" : "0") << endl;
//
//		writeList(file, edgeList, isWeighted);
//		file.close();
//	}
//	int calc() {
//		int result = 0;
//		for (auto it = edgeList->begin(); it != edgeList->end(); ++it) {
//			result += it->second;
//		}
//		return result;
//	}
//	friend Graph;
//};
//
//EdgeListGraphRepresentation* AdjMatrixGraphRepresentation::transformToListOfEdges() {
//	EdgeListGraphRepresentation* edgeListGraph = new EdgeListGraphRepresentation(isOriented, isWeighted, adjacencyMatrix->size(), 0);
//	for (size_t i = 0; i < adjacencyMatrix->size(); ++i)
//		for (size_t j = 0; j < adjacencyMatrix->size(); ++j) {
//			int weight = (*(*adjacencyMatrix)[i])[j];
//			if (weight > 0)
//				edgeListGraph->addEdge(i, j, weight);
//		}
//	return edgeListGraph;
//}
//AdjListGraphRepresentation* AdjMatrixGraphRepresentation::transformToAdjList()
//{
//	AdjListGraphRepresentation* adjListGraph = new AdjListGraphRepresentation(adjacencyMatrix->size(), 0, isOriented, isWeighted);
//	for (size_t i = 0; i<adjacencyMatrix->size(); ++i) {
//		for (size_t j = 0; j<adjacencyMatrix->size(); ++j) {
//			int weight = (*(*adjacencyMatrix)[i])[j];
//			if (weight > 0)
//				adjListGraph->addEdge(i, j, weight);
//		}
//	}
//	return adjListGraph;
//}
//AdjMatrixGraphRepresentation* AdjListGraphRepresentation::transformToAdjMatrix() {
//	AdjMatrixGraphRepresentation* adjMatrixGraph = new AdjMatrixGraphRepresentation(adjacencyList->size(), 0, isOriented, isWeighted);
//	for (size_t i = 0; i < adjacencyList->size(); ++i) {
//		map<int, int>* currentVertexMap = (*adjacencyList)[i];
//		for (auto it = currentVertexMap->begin(); it != currentVertexMap->end(); ++it)
//			adjMatrixGraph->addEdge(i, it->first, it->second);
//	}
//	return adjMatrixGraph;
//}
//
//EdgeListGraphRepresentation* AdjListGraphRepresentation::transformToListOfEdges() {
//	EdgeListGraphRepresentation* edgeListGraph = new EdgeListGraphRepresentation(isOriented, isWeighted, adjacencyList->size(), 0);
//	for (size_t i = 0; i<adjacencyList->size(); ++i) {
//		map<int, int>* currentVertexMap = (*adjacencyList)[i];
//		for (auto it = currentVertexMap->begin(); it != currentVertexMap->end(); ++it)
//			edgeListGraph->addEdge(i, it->first, it->second);
//	}
//	return edgeListGraph;
//}
//AdjListGraphRepresentation* EdgeListGraphRepresentation::transformToAdjList() {
//	AdjListGraphRepresentation* adjListGraph = new AdjListGraphRepresentation(vertexAmount, 0, isOriented, isWeighted);
//	for (auto it = edgeList->begin(); it != edgeList->end(); ++it)
//		adjListGraph->addEdge(it->first.first, it->first.second, it->second);
//	return adjListGraph;
//}
//AdjMatrixGraphRepresentation* EdgeListGraphRepresentation::transformToAdjMatrix() {
//	AdjMatrixGraphRepresentation* adjMatrixGraph = new AdjMatrixGraphRepresentation(vertexAmount, 0, isOriented, isWeighted);
//	for (auto it = edgeList->begin(); it != edgeList->end(); ++it)
//		adjMatrixGraph->addEdge(it->first.first, it->first.second, it->second);
//	return adjMatrixGraph;
//}
//
//class Graph {
//	GraphRepresentation* graphRepresentation = nullptr;
//	static vector<string> getGraphParameters(istream &stream) {
//		vector<string> params;
//		string str;
//		for (size_t i = 0; i < 2; i++) {
//			getline(stream, str);
//			for (const string tok : StringParser::split(str, ' '))
//				params.push_back(tok);
//		}
//		return params;
//	}
//	static GraphRepresentation* decideRepresentationType(string code) {
//		if (code == "C")
//			return (GraphRepresentation*) new AdjMatrixGraphRepresentation();
//		if (code == "E")
//			return (GraphRepresentation*) new EdgeListGraphRepresentation();
//		if (code == "L")
//			return (GraphRepresentation*) new AdjListGraphRepresentation();
//		return nullptr;
//	}
//	void copy(const Graph& graph) {
//		GraphRepresentation* newGraph = nullptr;
//		if (graph.graphRepresentation->isAdjListGraph())
//			newGraph = (AdjListGraphRepresentation*)graph.graphRepresentation;
//		else if (graph.graphRepresentation->isAdjMatrixGraph())
//			newGraph = (AdjMatrixGraphRepresentation*)graph.graphRepresentation;
//		else if (graph.graphRepresentation->isEdgeListGraph())
//			newGraph = (EdgeListGraphRepresentation*)graph.graphRepresentation;
//		delete graphRepresentation;
//		graphRepresentation = newGraph;
//	}
//	BridgesList initBridgesList(AdjacencyList adjList) {
//		BridgesList bridges = new vector<map<int, bool>*>(adjList->size());
//		for (int i = 0; i < bridges->size(); ++i) {
//			(*bridges)[i] = new map<int, bool>();
//			for (auto it = adjList->at(i)->begin(); it != adjList->at(i)->end(); ++it) {
//				(*(*bridges)[i])[it->first] = false;
//			}
//		}
//		return bridges;
//	}
//	BridgesList findBridges() {
//		AdjListGraphRepresentation* graph = (AdjListGraphRepresentation*)graphRepresentation;
//		BridgesList bridges = initBridgesList(graph->adjacencyList);
//		vector<bool>* isVisited = new vector<bool>(graph->adjacencyList->size(), false);
//		vector<int>* discoveryTime = new vector<int>(graph->adjacencyList->size());
//		vector<int>* minTime = new vector<int>(graph->adjacencyList->size());
//		vector<int>* parent = new vector<int>(graph->adjacencyList->size(), -1);
//
//		int time = 0;
//		for (int i = 0; i < graph->adjacencyList->size(); ++i)
//			if (!isVisited->at(i))
//				bridgeRecursiveStep(i, time, graph->adjacencyList, isVisited,
//					discoveryTime, minTime, parent, bridges);
//		return bridges;
//	}
//	void bridgeRecursiveStep(int u, int& time, AdjacencyList adjList, vector<bool>* isVisited, vector<int>* discoveryTime,
//															vector<int>* minTime, vector<int>* parent, BridgesList bridges) {
//		(*isVisited)[u] = true;
//		(*discoveryTime)[u] = (*minTime)[u] = ++time;
//		for (auto it = adjList->at(u)->begin(); it != adjList->at(u)->end(); ++it) {
//			int v = it->first;
//			if (!isVisited->at(v)) {
//				(*parent)[v] = u;
//				bridgeRecursiveStep(v, time, adjList, isVisited, discoveryTime, minTime, parent, bridges);
//				(*minTime)[u] = min((*minTime)[u], (*minTime)[v]);
//				if ((*minTime)[v] > (*discoveryTime)[u]) {
//					//(*(*bridges)[v])[u] = true;
//					(*(*bridges)[u])[v] = true;
//				}
//			}
//			else if (v != parent->at(u))
//				(*minTime)[u] = min((*minTime)[u], (*discoveryTime)[v]);
//		}
//	}
//
//public:
//	Graph() {	}
//	Graph(int n) {
//		graphRepresentation = (GraphRepresentation*) new EdgeListGraphRepresentation(false, true, n, 0);
//	}
//	Graph(const Graph& graph) {
//		copy(graph);
//	}
//	~Graph()
//	{
//		delete graphRepresentation;
//	};
//	Graph& operator=(const Graph& graph) {
//		copy(graph);
//		return *this;
//	}
//	void readGraph(string fileName) {
//		ifstream file(fileName);
//		const vector<string> params = getGraphParameters(file);
//		graphRepresentation = decideRepresentationType(params[0]);
//		graphRepresentation->readGraph(file, params);
//		file.close();
//	}
//	void addEdge(int from, int to, int weight) const {
//		graphRepresentation->addEdge(from, to, weight);
//	}
//	int changeEdge(int from, int to, int newWeight) const {
//		return graphRepresentation->changeEdge(from, to, newWeight);
//	}
//	void removeEdge(int from, int to) const {
//		graphRepresentation->removeEdge(from, to);
//	}
//
//	void transformToAdjList() {
//		if (!graphRepresentation->isAdjListGraph()) {
//			GraphRepresentation* adjListGraph = (GraphRepresentation*)graphRepresentation->transformToAdjList();
//			delete graphRepresentation;
//			graphRepresentation = adjListGraph;
//		}
//	}
//	void transformToListOfEdges() {
//		if (!graphRepresentation->isEdgeListGraph()) {
//			GraphRepresentation* edgeListGraph = (GraphRepresentation*)graphRepresentation->transformToListOfEdges();
//			delete graphRepresentation;
//			graphRepresentation = edgeListGraph;
//		}
//	}
//	void transformToAdjMatrix() {
//		if (!graphRepresentation->isAdjMatrixGraph()) {
//			GraphRepresentation* adjMatrixGraph = (GraphRepresentation*)graphRepresentation->transformToAdjMatrix();
//			delete graphRepresentation;
//			graphRepresentation = adjMatrixGraph;
//		}
//	}
//	void writeGraph(string fileName) const {
//		graphRepresentation->writeGraph(fileName);
//	}
//
//	Graph getSpaingTreeKruscal() {
//		transformToListOfEdges();
//		EdgeListGraphRepresentation* edgeListGraph = (EdgeListGraphRepresentation*)graphRepresentation;
//
//		auto compare = [](pair<pair<int, int>, int> a, pair<pair<int, int>, int> b) {
//			return a.second < b.second;
//		};
//		auto edgeVector = vector<pair<pair<int, int>, int>>(edgeListGraph->edgeList->begin(),
//			edgeListGraph->edgeList->end());
//		sort(edgeVector.begin(), edgeVector.end(), compare);
//		DSU dsu = DSU(edgeListGraph->vertexAmount);
//		for (size_t i = 0; i < edgeListGraph->vertexAmount; ++i)
//			dsu.makeSet(i);
//		EdgeListGraphRepresentation* newEdgeListGraph = new EdgeListGraphRepresentation(false, true,
//			edgeListGraph->vertexAmount, 0);
//		for (size_t i = 0; i < edgeVector.size(); i++) {
//			int from = edgeVector[i].first.first;
//			int to = edgeVector[i].first.second;
//			if (dsu.find(from) != dsu.find(to)) {
//				newEdgeListGraph->addEdge(from, to, edgeVector[i].second);
//				dsu.unite(from, to);
//			}
//		}
//		Graph* graph = new Graph();
//		graph->graphRepresentation = newEdgeListGraph;
//		return *graph;
//	}
//	Graph getSpaingTreePrima() {
//		transformToAdjList();
//		AdjacencyList adjList = ((AdjListGraphRepresentation*)graphRepresentation)->adjacencyList;
//		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pr_que;
//		int src = 0;
//		vector<int> parent(adjList->size(), -1);
//		vector<int> distances(adjList->size(), INT32_MAX);
//		vector<bool> inMST(adjList->size(), false);
//		pr_que.push(make_pair(0, src));
//		distances[src] = 0;
//
//		while (!pr_que.empty()) {
//			int u = pr_que.top().second;
//			pr_que.pop();
//			inMST[u] = true;
//			for (auto it = adjList->at(u)->begin(); it != adjList->at(u)->end(); ++it) {
//				int v = it->first;
//				int weight = it->second;
//				if (inMST[v] == false && distances[v] > weight) {
//					distances[v] = weight;
//					pr_que.push(make_pair(distances[v], v));
//					parent[v] = u;
//				}
//			}
//		}
//		EdgeListGraphRepresentation* newEdgeListGraph = new EdgeListGraphRepresentation(false, true, adjList->size(), 0);
//		for (size_t i = 1; i<parent.size(); ++i)
//			newEdgeListGraph->addEdge(parent[i], i, distances[i]);
//		Graph* graph = new Graph();
//		graph->graphRepresentation = newEdgeListGraph;
//		return *graph;
//	}
//	Graph getSpaingTreeBoruvka() {
//		transformToListOfEdges();
//		EdgeListGraphRepresentation* edgeListGraph = (EdgeListGraphRepresentation*)graphRepresentation;
//		EdgeList edgeList = edgeListGraph->edgeList;
//		int vertexAmount = edgeListGraph->vertexAmount;
//		auto edgeVector = vector<pair<pair<int, int>, int>>(edgeListGraph->edgeList->begin(), edgeListGraph->edgeList->end());
//
//		DSU dsu = DSU(vertexAmount);
//		for (size_t i = 0; i<edgeListGraph->vertexAmount; ++i)
//			dsu.makeSet(i);
//		EdgeListGraphRepresentation* newEdgeListGraph = new EdgeListGraphRepresentation(false, true, vertexAmount, 0);
//		while (newEdgeListGraph->edgesAmount < vertexAmount - 1) {
//			auto minEdge = map<int, int>();
//			for (int i = 0; i < vertexAmount; ++i)
//				minEdge[i] = -1;
//			for (int i = 0; i<edgeVector.size(); ++i) {
//				auto edge = edgeVector[i];
//				int from = edge.first.first;
//				int to = edge.first.second;
//				int weight = edge.second;
//				int fromCompon = dsu.find(from);
//				int toCompon = dsu.find(to);
//				if (fromCompon != toCompon) {
//					if (minEdge[fromCompon] == -1 || edgeVector[minEdge[fromCompon]].second > weight)
//						minEdge[fromCompon] = i;
//					if (minEdge[toCompon] == -1 || edgeVector[minEdge[toCompon]].second > weight)
//						minEdge[toCompon] = i;
//				}
//			}
//			for (int i = 0; i<minEdge.size(); i++) {
//				if (minEdge[i] != -1) {
//					pair<pair<int, int>, int> edge = edgeVector[minEdge[i]];
//					dsu.unite(edge.first.first, edge.first.second);
//					newEdgeListGraph->addEdge(edge.first.first, edge.first.second, edge.second);
//				}
//			}
//		}
//		Graph* graph = new Graph();
//		graph->graphRepresentation = newEdgeListGraph;
//		return *graph;
//	}
//
//	int calc() {
//		return graphRepresentation->calc();
//	};
//};