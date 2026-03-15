class Node:
    def __init__(self, point):
        self.point = point
        self.nodes = {}
        self.queue = []

class City:
    def __init__(self):
        self.nodes = {}
    def add_city(self, point):
        self.nodes[point] = Node(point)
    def add_road(self, from_city, to_city, distance):
        self.nodes[from_city].nodes[to_city] = distance
    def dijkstra(self, start):
        distances = {node: float("inf") for node in self.nodes}
        previous = {node: None for node in self.nodes}
        distances[start] = 0

        unvisited = list(self.nodes.keys())

        while unvisited:
            curr = min(unvisited, key=lambda node: distances[node])
            unvisited.remove(curr)

            for neighbor, weight in self.nodes[curr].nodes.items():
                if neighbor in unvisited:
                    new_dist = distances[curr] + weight
                    if new_dist < distances[neighbor]:
                        distances[neighbor] = new_dist
                        previous[neighbor] = curr

        return distances, previous

citta = City()
citta.add_city("A")
citta.add_city("B")
citta.add_city("C")
citta.add_city("D")
citta.add_city("E")

citta.add_road("A", "B", 20)
citta.add_road("A", "C", 10)
citta.add_road("B", "E", 40)
citta.add_road("B", "D", 5)
citta.add_road("C", "D", 10)
citta.add_road("D", "E", 5)
print(citta.dijkstra("A"))