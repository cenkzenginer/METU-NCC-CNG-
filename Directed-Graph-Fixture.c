//*2385789  Cenk Zenginer *//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct graphVertex Vertex;
struct graphVertex
{
    Vertex *next;
    char team[81];
    int inDegree;
    int outDegree;
    int isVisited;
    struct graphEdge *firstArc;
};

typedef struct graphEdge Edge;
struct graphEdge
{
    Vertex *destination;
    int weight;
    Edge *nextArc;
};

typedef struct graphHead graphHead;
struct graphHead
{
    int count;
    Vertex *first;
};

graphHead *readTeams(FILE *);
void readMatches(FILE *, graphHead *);
graphHead *createGraph(void);
void createVertex(graphHead *, char[]);
void createEdge(graphHead *, char[], char[], int);
void printGraph(graphHead *);
void getMostWins(graphHead *);
void getMostLosses(graphHead *);
void getMaxGoals(graphHead *);
void getMinGoals(graphHead *);
int checkwinChain(graphHead *, char[], char[]);
int checkPath(graphHead *, char[], char[]);

int breadthFirstSearch(graphHead *graph, Vertex *start, Vertex *destination);

int main(int argc, char *argv[])
{
    FILE *inFile;
    graphHead *graph;
    inFile = fopen("teams.txt", "r");
    if (inFile == NULL)
    {
        printf("File could not be opened.\n");
        exit(1);
    }
    printf("Teams File has been opened successfully; the graph with no edges can be seen below:\n");
    graph = readTeams(inFile);
    printGraph(graph);
    printf("***************************************************************************************************************\n");

    fclose(inFile);
    inFile = fopen("matches2.txt", "r");
    if (inFile == NULL)
    {
        printf("File could not be opened.\n");
        exit(1);
    }
    printf("Matches File has been opened successfully; the graph with edges can be seen below:\n");
    readMatches(inFile, graph);
    printGraph(graph);
    printf("***************************************************************************************************************\n");

    getMostWins(graph);
    getMostLosses(graph);
    getMaxGoals(graph);
    getMinGoals(graph);
    printf("***************************************************************************************************************\n");
    if (argc < 3)
    {
        printf("Two teams are not given in the command line arguments!");
    }
    else
    {
        char str1[81], str2[81];
        int i = 0;
        while (argv[1][i] != '\0')
        {
            if (argv[1][i] == '_')
                str1[i] = ' ';
            else
                str1[i] = argv[1][i];
            i++;
        }
        str1[i] = '\0';
        i = 0;
        while (argv[2][i] != '\0')
        {
            if (argv[2][i] == '_')
                str2[i] = ' ';
            else
                str2[i] = argv[2][i];
            i++;
        }
        str2[i] = '\0';

        int result = checkwinChain(graph, str1, str2);
        if (result)
            printf("%s have beaten a team that beat %s.\n", str1, str2);

        else
            printf("%s have NOT beaten a team that beat %s.\n", str1, str2);

        int result2 = checkPath(graph, str1, str2);
        if (result2)
            printf("There is a path from %s to %s", str1, str2);
        else
            printf("There is no path from %s to %s", str1, str2);
    }
    return 0;
}

graphHead *createGraph(void)
{
    graphHead *graph;
    graph = (graphHead *)malloc(sizeof(graphHead));
    if (graph == NULL)
    {
        printf("Memory allocation is failed.");
        exit(1);
    }
    graph->count = 0;
    graph->first = NULL;
    return graph;
}

void createVertex(graphHead *graph, char teamName[])
{
    Vertex *vertex = (struct graphVertex *)malloc(sizeof(struct graphVertex));
    vertex->next = NULL;
    strcpy(vertex->team, teamName);
    vertex->inDegree = 0;
    vertex->outDegree = 0;
    vertex->firstArc = NULL;
    vertex->isVisited = 0;

    graph->count++;

    if (graph->first == NULL)
    {
        graph->first = vertex;
    }
    else
    {
        struct graphVertex *temp = graph->first;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = vertex;
    }
}

graphHead *readTeams(FILE *file)
{
    char teamName[81];
    // Creating an empty graph
    graphHead *graph = createGraph();
    while (fscanf(file, "%80[^\n]", teamName) != EOF)
    {
        createVertex(graph, teamName); // Create a vertex
        fgetc(file);                   // read the new line character
    }

    return graph;
}

void readMatches(FILE *inFile, graphHead *graph)
{
    char line[256]; // buffer to read the line
    char winner[81], loser[81];
    char home[81], away[81];
    int homeGoals = 0, awayGoals = 0, difference = 0;

    while (fgets(line, sizeof(line), inFile) != NULL)
    {
        sscanf(line, "%*[^;];%*[^;];%*[^;];%[^;];%d;%d;%[^;];%*s", home, &homeGoals, &awayGoals, away);
        // Read match data from the file until the end of the file
        if (homeGoals > awayGoals){
            // Determine the winning and losing teams
            strcpy(winner, home);
            strcpy(loser, away);
            difference = homeGoals - awayGoals;
        }
        else if (awayGoals > homeGoals){
            strcpy(winner, away);
            strcpy(loser, home);
            difference = awayGoals - homeGoals;
        }
        else{
            continue;
        }
        createEdge(graph, winner, loser, difference); // Create an edge for each match
    }
}

void createEdge(graphHead *graph, char winningTeam[], char losingTeam[], int goalDiff)
{
    Vertex *Vertexlose = NULL;
    Vertex *Vertexwin = NULL;
    Vertex *Vertexcurrent = graph->first;

    // Find the vertices corresponding to the winning and losing teams
    while (Vertexcurrent != NULL)
    {
        if (strcmp(Vertexcurrent->team, winningTeam) == 0)
        {
            Vertexwin = Vertexcurrent;
        }
        else if (strcmp(Vertexcurrent->team, losingTeam) == 0)
        {
            Vertexlose = Vertexcurrent;
        }
        Vertexcurrent = Vertexcurrent->next; // Move to the next vertex
    }

    // Create a new edge if both winning and losing vertices are found
    if (Vertexwin != NULL && Vertexlose != NULL)
    {
        Edge *newEdge = (Edge *)malloc(sizeof(Edge)); // Allocate memory for a new edge

        // Set the edge properties
        newEdge->destination = Vertexlose;
        newEdge->weight = goalDiff;
        newEdge->nextArc = Vertexwin->firstArc;
        Vertexwin->firstArc = newEdge;

        // Update the inDegree and outDegree
        Vertexwin->outDegree++;
        Vertexlose->inDegree++;
    }
}

void printGraph(graphHead *graph)
{
    Vertex *VertexCurrent = graph->first;
    Edge *currentEdge;

    while (VertexCurrent != NULL)
    { // Iterate over each vertex in the graph

        currentEdge = VertexCurrent->firstArc; // Get the first outgoing edge of the vertex

        if (currentEdge == NULL)
        {
            // If the vertex has no outgoing edges, print the vertex name only
            printf("%s -> \n", VertexCurrent->team);
            printf("------------------------------------------------\n");
        }
        else
        {
            // Print the vertex name and its outgoing edges
            printf("%s ", VertexCurrent->team);

            while (currentEdge != NULL)
            {
                printf("-> %s | %d", currentEdge->destination->team, currentEdge->weight);
                currentEdge = currentEdge->nextArc;
            }

            printf("\n------------------------------------------------\n");
        }

        printf("\n");
        VertexCurrent = VertexCurrent->next;
    }
}

void getMostWins(graphHead *graph)
{
    Vertex *VertexCurr = graph->first;
    Vertex *WinVertexMax = NULL;

    while (VertexCurr != NULL)
    {
        if (WinVertexMax == NULL) // If this is the first vertex
        {

            WinVertexMax = VertexCurr;
        }
        else if (VertexCurr->outDegree > WinVertexMax->outDegree) // If this vertex has more wins than the current max
        {
            WinVertexMax = VertexCurr;
        }
        VertexCurr = VertexCurr->next;
    }
    printf("Team with the most victories:\n%s has won %d matches.\n", WinVertexMax->team, WinVertexMax->outDegree);
    // Print the team with the most wins
}

void getMostLosses(graphHead *graph)
{
    Vertex *VertexCurr = graph->first;
    Vertex *LoseVertexMax = NULL;

    while (VertexCurr != NULL)
    {
        if (LoseVertexMax == NULL){ // If this is the first vertex
            LoseVertexMax = VertexCurr;
        }
        else if (VertexCurr->outDegree < LoseVertexMax->outDegree) // If this vertex has more wins than the current max
        {
            LoseVertexMax = VertexCurr;
        }
        VertexCurr = VertexCurr->next;
    }
    printf("Team with the most losses:\n%s has lost %d matches.\n", LoseVertexMax->team, LoseVertexMax->inDegree);
    // Print the team with the most wins
}

void getMaxGoals(graphHead *graph)
{
    Vertex *currentVertex = graph->first;
    int maxTotalGoals = 0;
    char maxTeamName[81];

    while (currentVertex != NULL)
    {
        Edge *currentEdge = currentVertex->firstArc;
        int totalGoals = 0;

        // sum of the weights of the edges. I know it must be substract if the team losses but i could not find a way to do it. Because the weight must be always positive
        while (currentEdge != NULL){
            totalGoals += currentEdge->weight;
            currentEdge = currentEdge->nextArc;
        }

        if (totalGoals > maxTotalGoals){ // if the total goals is bigger than the max total goals, update the max total goals and the team name.

            maxTotalGoals = totalGoals;
            strcpy(maxTeamName, currentVertex->team);
        }

        currentVertex = currentVertex->next;
    }

    printf("Team with the highest goal difference:\n");
    printf("%s have a goal difference of %d\n", maxTeamName, maxTotalGoals);
}

void getMinGoals(graphHead *graph)
{
    Vertex *currentVertex = graph->first;
    int minTotalGoals = INT_MAX; // Initialize with the maximum possible value
    char minTeamName[81];

    while (currentVertex != NULL)
    {
        Edge *currentEdge = currentVertex->firstArc;
        int totalGoals = 0;

        // sum of the weights of the edges. I know it must be substract if the team losses but i could not find a way to do it. Because the weight must be always positive
        while (currentEdge != NULL)
        {
            totalGoals += currentEdge->weight;
            currentEdge = currentEdge->nextArc;
        }

        if (totalGoals < minTotalGoals) // if the total goals is smaller than the min total goals, update the min total goals and the team name.
        {
            minTotalGoals = totalGoals;
            strcpy(minTeamName, currentVertex->team);
        }

        currentVertex = currentVertex->next;
    }

    if (minTotalGoals == INT_MAX)
    {
        //set minTotalGoals to 0 if there is no match
        minTotalGoals = 0;
        strcpy(minTeamName, "No Team");
    }
    printf("Team with the lowest goal difference:\n");
    printf("%s have a goal difference of %d\n", minTeamName, minTotalGoals);
}

int breadthFirstSearch(graphHead *graph, Vertex *start, Vertex *destination)
{
    int found = 0;
    // Allocate memory for the queue
    Vertex **queue = (Vertex **)malloc(sizeof(Vertex *) * graph->count);
    int front = 0, rear = 0;

    // Enqueue the starting vertex
    queue[rear++] = start;
    start->isVisited = 1;

    while (front < rear)
    {
        Vertex *currentVertex = queue[front++];

        Edge *edge = currentVertex->firstArc;
        while (edge != NULL)
        {
            Vertex *adjacentVertex = edge->destination;

            if (adjacentVertex->isVisited != 1)
            {
                // Enqueue the adjacent vertex if not visited
                queue[rear++] = adjacentVertex;
                adjacentVertex->isVisited = 1;
            }

            edge = edge->nextArc;
        }
    }

    free(queue);

    return found;
}

int checkwinChain(graphHead *graph, char team1[], char team2[])
{
    Vertex *team1Vertex = NULL, *team2Vertex = NULL;
    Vertex *temp = graph->first; // used to reset the visited flag for all vertices after the check

    while (temp != NULL) // find the vertices for the winning and losing teams
    {
        if (strcmp(temp->team, team1) == 0)
        {
            team1Vertex = temp;
        }
        else if (strcmp(temp->team, team2) == 0)
        {
            team2Vertex = temp;
        }
        temp = temp->next;
    }
    int result = breadthFirstSearch(graph, team1Vertex, team2Vertex); //BreadtFirstTraversal to check if there is a winning chain
    return result;
}

int checkPath(graphHead *graph, char team1[], char team2[])
{
    Vertex *team1Vertex = NULL, *team2Vertex = NULL;
    Vertex *temp = graph->first;

    while (temp != NULL) // Finding the vertices for the teams
    {
        if (strcmp(temp->team, team1) == 0){
            team1Vertex = temp;
        }
        else if (strcmp(temp->team, team2) == 0){
            team2Vertex = temp;
        }
        temp = temp->next;
    }
    temp = graph->first;
    while (temp != NULL) // Reset the visited flags for all vertices
    {
        temp->isVisited = 0;
        temp = temp->next;
    }
    int result = breadthFirstSearch(graph, team1Vertex, team2Vertex);
    return result;
}
