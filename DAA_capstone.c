#include <stdio.h>
#include <stdlib.h>

#define MAXE 50
#define HOURS 24

typedef struct {
    int from, to;
    float capacity;
    float baseCost;
    float dynamicCost;
    float flowHistory[3];
    float currentFlow;
} Edge;

Edge edges[MAXE];

int nodes;
int edgesCount;
int source, sink;

float totalVolume;
float delivered = 0;
float totalCost = 0;

void updateDynamicCosts() {
	int i;
    for(i=0;i<edgesCount;i++) {

        float f1 = edges[i].flowHistory[0];
        float f2 = edges[i].flowHistory[1];
        float f3 = edges[i].flowHistory[2];

        float u1 = f1 / edges[i].capacity;
        float u2 = f2 / edges[i].capacity;
        float u3 = f3 / edges[i].capacity;

        edges[i].dynamicCost = edges[i].baseCost + (3*u1 + 2*u2 + u3)/6;
    }
}

void shiftFlowHistory() {
	int i;
    for(i=0;i<edgesCount;i++) {

        edges[i].flowHistory[2] = edges[i].flowHistory[1];
        edges[i].flowHistory[1] = edges[i].flowHistory[0];
        edges[i].flowHistory[0] = edges[i].currentFlow;

        edges[i].currentFlow = 0;
    }
}

int findCheapestEdge() {

    float minCost = 999999;
    int index = -1;
	int i;
    for(i=0;i<edgesCount;i++) {

        if(edges[i].dynamicCost < minCost) {
            minCost = edges[i].dynamicCost;
            index = i;
        }
    }

    return index;
}

void runHour(int hour) {

    updateDynamicCosts();

    float remaining = totalVolume - delivered;
    int hoursLeft = HOURS - hour + 1;

    float demand = remaining / hoursLeft;

    int bestEdge = findCheapestEdge();

    if(bestEdge == -1) return;

    float flow = demand;

    if(flow > edges[bestEdge].capacity)
        flow = edges[bestEdge].capacity;

    edges[bestEdge].currentFlow = flow;

    float cost = flow * edges[bestEdge].dynamicCost;

    delivered += flow;
    totalCost += cost;

    printf("\nHour %d\n",hour);
    printf("Pipe %d -> %d used\n",edges[bestEdge].from,edges[bestEdge].to);
    printf("Flow = %.2f\n",flow);
    printf("Cost = %.2f\n",cost);

    shiftFlowHistory();
}

int main() {

    printf("HYDRA-24 Water Distribution Simulation\n\n");

    printf("Enter number of nodes: ");
    scanf("%d",&nodes);

    printf("Enter number of pipes: ");
    scanf("%d",&edgesCount);

    printf("\nEnter pipe details:\n");
    printf("(from to capacity baseCost)\n\n");
	int i;
    for(i=0;i<edgesCount;i++) {

        printf("Pipe %d: ",i+1);

        scanf("%d %d %f %f",
        &edges[i].from,
        &edges[i].to,
        &edges[i].capacity,
        &edges[i].baseCost);

        edges[i].dynamicCost = edges[i].baseCost;
        edges[i].flowHistory[0] = 0;
        edges[i].flowHistory[1] = 0;
        edges[i].flowHistory[2] = 0;
        edges[i].currentFlow = 0;
    }

    printf("\nEnter source node: ");
    scanf("%d",&source);

    printf("Enter sink node: ");
    scanf("%d",&sink);

    printf("Enter total water volume: ");
    scanf("%f",&totalVolume);

    printf("\nStarting Simulation...\n");
	int h;
    for(h=1; h<=HOURS; h++) {

        if(delivered >= totalVolume)
            break;

        runHour(h);
    }

    printf("\nSimulation Complete\n");
    printf("Total Delivered = %.2f L\n",delivered);
    printf("Total Cost = %.2f\n",totalCost);

    return 0;
}
