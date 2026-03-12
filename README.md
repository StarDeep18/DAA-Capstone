# 💧 HYDRA-24: Dynamic Water Distribution Optimization

## 📌 Overview

HYDRA-24 is a simulation program that models a city water distribution network and determines how water should be delivered through pipes over 24 hours while minimizing the total transportation cost.

Each pipe in the network has:

• A maximum capacity (how much water it can carry per hour)

• A base cost per liter


However, pipes experience mechanical stress under continuous operation. This increases the pipe cost dynamically. The program, therefore, updates pipe costs hourly based on recent usage and selects the pipe with the lowest dynamic cost to deliver water.

The objective is to deliver the required water volume while keeping the total cost as low as possible and ensuring pipe capacities are not exceeded.

---

## 🌐 Problem Model

The water distribution network is modeled as a directed graph.

• Nodes represent water junctions in the city

• Edges (pipes) represent connections between nodes

• Source (S) represents the central reservoir

• Sink (T) represents the residential district


Each pipe stores the following information:
• Capacity

• Base cost

• Dynamic cost

• Flow history for the previous three hours


---

## ⚙ Dynamic Cost Formula

The cost of using a pipe changes depending on how much it has been used recently.

C(e,t) = BaseCost + (3 × Flow(t−1) + 2 × Flow(t−2) + Flow(t−3)) / 6

Where:
• Flow(t−1) is the flow in the previous hour

• Flow(t−2) is the flow two hours ago

• Flow(t−3) is the flow three hours ago


Recent usage contributes more stress to the pipe, which increases its cost temporarily.
If a pipe is not used for several hours, its cost gradually returns to its base cost.

---

## 🧠 Algorithm Used

The program uses a Greedy Dynamic Cost Flow Scheduling algorithm.

Core idea:

1. At each hour, update pipe costs using the stress formula.
2. Calculate the remaining water demand.
3. Select the pipe with the minimum dynamic cost.
4. Send water through that pipe without exceeding its capacity.
5. Update flow history.
6. Repeat the process for the next hour until the required water volume is delivered.

This strategy prevents overusing the same pipe and distributes load across the network.

---

## 🧾 Pseudocode

Start
Input the number of nodes and pipes
Input pipe details (from, to, capacity, base cost)
Input source node and sink node
Input total water demand

Initialize flow history for all pipes
Set delivered volume = 0
Set total cost = 0

FOR hour = 1 to 24

 Update the dynamic cost of each pipe

 remainingVolume = totalVolume − deliveredVolume
 remainingHours = 24 − hour + 1
 demand = remainingVolume / remainingHours

 Find the pipe with the minimum dynamic cost

 flow = minimum(demand, pipe capacity)

 Send flow through the selected pipe

 deliveredVolume += flow
 totalCost += flow × dynamicCost

 Update pipe flow history

END FOR

Display total delivered water
Display total cost

End

---

## 🖥 Implementation Details

Programming Language Used:
C

Compiler:
GCC (GNU C Compiler)

Libraries Used:
stdio.h
stdlib.h

Graph Representation:

Edge List Representation

Each pipe is stored using a structure that contains its capacity, cost, and flow history.

---

## ⏱ Time Complexity

For each hour:

Dynamic cost update = O(E)

Pipe selection = O(E)

Where E represents the number of pipes.

Total simulation:

24 × O(E)

Final time complexity:

O(E)

---

## 💾 Space Complexity

The program stores pipe information and flow history for each pipe.

Space required:

O(E)

---

## 📊 Example Input

Enter number of nodes: 4

Enter number of pipes: 5


Pipe 1: 1 2 120 1

Pipe 2: 1 3 100 1.2

Pipe 3: 2 4 110 0.8

Pipe 4: 3 4 90 0.9

Pipe 5: 2 3 60 1.5


Enter source node: 1

Enter sink node: 4


Enter total water volume: 1000

---

## 📈 Example Output

HYDRA-24 Water Distribution Simulation

Hour 1

Pipe 1 → 2 used

Flow = 41.67

Cost = 41.67


...

Simulation Complete

Total Delivered = 1000.00 L

Total Cost = 932.87

---

## 🚀 Key Features

• Dynamic pipe cost modeling

• Stress-aware water distribution

• Capacity constraint handling

• 24-hour simulation

• Cost-optimized water flow


---

## 🌍 Applications

• Smart city water management systems

• Infrastructure stress monitoring

• Utility cost optimization

• Resource scheduling in networks


---

## 👨‍💻 Author

Deepak Bharathwaj S

CH.SC.U4CSE24015

HYDRA-24 - Dynamic Water Distribution Optimization
