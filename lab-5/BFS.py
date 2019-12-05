from graph import Graph
import sys
from queue import Queue



def bfs_1(g, start_v, end_v):
    flag = False
    q = Queue()
    v = start_v
    q.put(v)
    g.setVertexColor(v, g.gray)
    while not q.empty():
        v = q.get()
        if v == end_v:
            flag = True
            break
        l = g.getVertexAdjacent(v)
        for u in l:
            if g.getVertexColor(u) == g.white:
                g.setVertexColor(u, g.gray)
                g.setVertexDistance(u, g.getVertexDistance(v) + 1)
                g.setVertexParent(u, v)
                q.put(u)
        g.setVertexColor(v, g.black)

    if flag == True:
        v = end_v
        l = []
        while v != start_v:
            l.append(v)
            v = g.getVertexParent(v)
        print(v, end='')
        for x in l[::-1]:
            print('-> ', end='')
            print(x, end='')
    else: 
        print("not find path")
    return

def bfs_2(g, start_v, end_v):
    flag = False
    q1 = Queue()
    q2 = Queue()
    v1 = start_v
    v2 = end_v
    q1.put(v1)
    q2.put(v2)
    g.setVertexColor(v1, g.gray)
    g.setVertexColor(v2, g.gray)
    while not q1.empty() and not q2.empty():
        v1 = q1.get()
        v2 = q2.get()
        l1 = g.getVertexAdjacent(v1)
        l2 = g.getVertexAdjacent(v2)
        if v1 in l2:
            flag =True
            break
        for u1 in l1:
            if g.getVertexColor(u1) == g.white:
                g.setVertexColor(u1, g.gray)
                g.setVertexDistance(u1, g.getVertexDistance(v1) + 1)
                g.setVertexParent(u1, v1)
                q1.put(u1)
        g.setVertexColor(v1, g.black)

        for u2 in l2:
            if g.getVertexColor(u2) == g.white:
                g.setVertexColor(u2, g.gray)
                g.setVertexDistance(u2, g.getVertexDistance(v2) + 1)
                g.setVertexParent(u2, v2)
                q2.put(u2)

        g.setVertexColor(v2, g.black)
    
    if flag == True:
        l = []
        v = v1
        while v != start_v:
            l.append(v)
            v = g.getVertexParent(v)
        l.append(v)
        l = l[::-1]
        v = v2
        while v != end_v:
            l.append(v)
            v = g.getVertexParent(v)
        for x in l:
            print(x, end='')
            print('-> ', end='')
        print(v)
    else:
        print("not find path")
    return

def main():
    if len(sys.argv) != 5:
        return
    g = Graph(sys.argv[1])
    if sys.argv[4] == '1':
        bfs_1(g, int(sys.argv[2]), int(sys.argv[3]))
    elif sys.argv[4] == '2':
        bfs_2(g, int(sys.argv[2]), int(sys.argv[3]))
    return 

if __name__ == "__main__":
    main()
