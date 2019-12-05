from operator import itemgetter


class Vertex(object):

    def __init__(self, color, parent, distance):
        self.color = color
        self.parent = parent
        self.distance = distance



class Graph(object):

    def __init__(self, filename):
        with open(filename, "r") as f:
            content = f.read()
        content = content.split("\n")
        pairs = list(map(lambda x:[int(e) for e in x.split(" ")], content))
        pairs = pairs + [[x[1], x[0]] for x in pairs]
        pairs = sorted(pairs, key = itemgetter(0,1))
        self.__val = []
        self.__col_ind = []
        self.__row_ptr = []
        prev_row = -1
        for p in pairs:
            if p[0] != prev_row:
                self.__row_ptr.append(len(self.__val))
                prev_row = p[0]
            self.__val.append(1)
            self.__col_ind.append(p[1])
        
        # add end
        self.__row_ptr.append(len(self.__val))
        self.black = -1
        self.gray = 0
        self.white = 1
        self.nil = 0
        self.inf = 10000000
        self.__vertex = [Vertex(self.white, self.nil, self.inf) for x in range(len(self.__row_ptr) - 1)]
        return 
    

    def getVertexAdjacent(self, v_index):
        if v_index >= len(self.__vertex):
            return False
        s = self.__row_ptr[v_index]
        e = self.__row_ptr[v_index+1]
        v_list = [x for x in self.__col_ind[s:e]]
        return v_list

    def getVertexColor(self, v_index):
        if v_index >= len(self.__vertex):
            return False
        return self.__vertex[v_index].color

    def setVertexColor(self, v_index, color):
        if color != self.white and color != self.white and color != self.gray:
            return False
        if v_index >= len(self.__vertex):
            return False
        self.__vertex[v_index].color = color
        return True
    
    def getVertexParent(self, v_index):
        if v_index >= len(self.__vertex):
            return False
        return self.__vertex[v_index].parent

    def setVertexParent(self, v_index, p_index):
        if v_index >= len(self.__vertex) or p_index >= len(self.__vertex):
            return False
        self.__vertex[v_index].parent = p_index
        return True

    def getVertexDistance(self, v_index):
        if v_index >= len(self.__vertex):
            return False
        return self.__vertex[v_index].distance

    def setVertexDistance(self, v_index, distance):
        if v_index >= len(self.__vertex):
            return False
        self.__vertex[v_index].distance = distance
        return True