citta = {
    "A": {"B": 20, "C": 10},
    "B": {"E": 40, "D": 5, "A": 20},
    "C": {"D": 10, "A": 10},
    "D": {"E": 5, "B": 5, "C": 10},
    "E": {"D": 5, "B": 40},
}

def dijkstra(cit: dict, start: str):
    distances = {n: float('inf') for n in cit.keys()}
    distances[start] = 0
    visited = {}
    visit_order = []
    current = start

    while len(visited) < len(cit):
        visit_order.append(current)
        road = cit[current]
        visited[current] = road

        for ne, weight in road.items():
            new_dist = distances[current] + weight
            if new_dist < distances[ne]:
                distances[ne] = new_dist
        
        unvisited = [n for n in distances if n not in visited]
        if unvisited:  # <-- fix: aggiorna solo se ci sono ancora nodi
            current = min(unvisited, key=lambda n: distances[n])
    
    print(distances)
    print(visit_order)

dijkstra(citta, "A")